#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "strutil.h"
#include "abb.h"
#include "hash.h"
#include "pila.h"
#include "heap.h"
#define RANGO_MENOR_A_DESDE 0
#define RANGO_MAYOR_A_HASTA 1
#define RANGO_CORRECTO 2
#define RANGO_ERRONEO 3

typedef struct hash_y_abb{
    abb_t* abb;
    hash_t* hash;
}hash_y_abb_t;


void modificar_ultimo_caracter(char* string){
    char* pos;
    if ((pos = strchr(string, '\n')) != NULL) *pos = '\0'; 
}

int comparar_abb(const char* clave1, const char* clave2){                //FUncion de comparacion que se usa en el abb, usa la linea completa del archivo

    char** palabras1 = split(clave1,',');
    char** palabras2 = split(clave2,',');
    int bandera = 0;

    if (strcmp(palabras1[6],palabras2[6]) == 0){

        if(strcmp(palabras1[0], palabras2[0]) < 0) bandera = -1;
        if(strcmp(palabras1[0], palabras2[0]) > 0) bandera = 1;

    }
    else bandera = strcmp(palabras1[6], palabras2[6]);

    free_strv(palabras1);
    free_strv(palabras2);
    return bandera;
}


int comparar_heap_minimos(const char* clave1, const char* clave2){                 //FUncion de comparacion del heap, compara la prioridad, y si no son iguales
                                                                                  //compara por codigo de vuelo
    char** palabras = split(clave1,',');
    char** palabras2 = split(clave2,',');
    int bandera = 0;
    int prioridad_clave_1 = atoi(palabras[0]);
    int prioridad_clave_2 = atoi(palabras2[0]);

    if (prioridad_clave_1==prioridad_clave_2){

        bandera = strcmp(palabras[1],palabras2[1]);        
    }

    if(prioridad_clave_1 < prioridad_clave_2) bandera = 1;
    if(prioridad_clave_1 > prioridad_clave_2) bandera = -1;

    free_strv(palabras2);
    free_strv(palabras);

    return bandera;
}
cmp_func_t comp_heap = &comparar_heap_minimos;

abb_comparar_clave_t comparacion = &comparar_abb;

int visitar(const char* clave_actual, char* desde, char* hasta, char* modo){          // FUncion que se usa desde el "lado barbara" para poder iterar el abb por rangos
    char** palabras = split(clave_actual,',');
    
    if (strcmp(palabras[6],desde) < 0){
         free_strv(palabras);
         return RANGO_MENOR_A_DESDE;
    }

    if (strcmp(palabras[6],hasta) > 0){
         free_strv(palabras);
         return RANGO_MAYOR_A_HASTA;
    }

    if ((strcmp(palabras[6],desde) >= 0)&&(strcmp(palabras[6],hasta) <= 0)){

        free_strv(palabras);
        return RANGO_CORRECTO;
    }
    return RANGO_ERRONEO;
}


bool agregar_archivo(hash_y_abb_t* hash_y_abb, char** palabras){                            //Agrega o actualiza archivos
    char* linea = NULL;
    ssize_t read;
    size_t len = 0;
    char* linea_del_abb;
    char* linea_del_hash;
    FILE* fp;

    modificar_ultimo_caracter(palabras[1]);
                                                                  
    fp = fopen(palabras[1], "r");

    if(fp == NULL){
         return false;
    }
    while ((read = getline(&linea, &len, fp)) != -1){       //Leo linea a linea el archivo CSV
                
        linea_del_abb = strdup(linea);
        linea_del_hash = strdup(linea);
        char** parseo=split(linea_del_abb, ',');
                
        if (hash_pertenece(hash_y_abb->hash,parseo[0])){
            char* linea2 = hash_obtener(hash_y_abb->hash, parseo[0]);
            char** parseo2 = split(linea2, ',');
            free(abb_borrar(hash_y_abb->abb, linea2));                    
            free_strv(parseo2);

        }
        if((!abb_guardar(hash_y_abb->abb, linea_del_abb, linea_del_abb)) || (!hash_guardar(hash_y_abb->hash, parseo[0] ,linea_del_hash))){
            free_strv(parseo);
            free(linea);
            fclose(fp);
            return false;
        }
        free_strv(parseo);
    }
    free(linea);
    fclose(fp);
    return true;
}


void ver_tablero(hash_y_abb_t* hash_y_abb, int k, char* modo, char* desde, char* hasta){
    modificar_ultimo_caracter(hasta);
    accion_por_rangos(hash_y_abb->abb, hash_y_abb->hash, visitar, desde, hasta, modo, k);   //Llama a la funcion accion por rangos con el modo asc o desc
}                                                                                           //como parametro


void mostrar_info_vuelo(hash_t* hash, char* codigo){
    char* linea = hash_obtener(hash,codigo);
    char** palabras = split(linea, ',');
    char* linea_a_mostrar = join(palabras, ' ');
    fprintf(stdout, "%s", linea_a_mostrar);
    free_strv(palabras);
    free(linea_a_mostrar);
}


void borrar(hash_y_abb_t* hash_y_abb, char* desde, char* hasta){                        //Llama a la funcion accion por rangos con el modo borrar como parametro
    modificar_ultimo_caracter(hasta);   
    char* modo="borrar";    
    accion_por_rangos(hash_y_abb->abb, hash_y_abb->hash, visitar, desde, hasta,modo, 0);   
}


char* obtener_linea_del_heap(char* linea){             //Funcion auxiliar de prioridad_vuelos del heap, recibe una linea y devuelve una cadena resultante que 
                                                       //solo contiene la prioridad, y el codigo de vuelo. Es lo unico que se muestra en la funcion prioridad_vuelos
    char** palabras = split(linea,',');
    char** palabras2 = malloc(sizeof(char*)*3);
    palabras2[0] = strdup(palabras[5]);
    palabras2[1] = strdup(palabras[0]);
    palabras2[2] = NULL;
    free_strv(palabras);
    char* resultante = join(palabras2, ',');
    free_strv(palabras2);
    return resultante;
}

void apilar_lineas(heap_t* heap, pila_t* pila, size_t cantidad_heap){
    for(size_t i = 0; i < cantidad_heap; i++){

        pila_apilar(pila, heap_desencolar(heap));
    }
}

void encolar_lineas_heap(hash_y_abb_t* hash_y_abb, int k, heap_t* heap, hash_iter_t* iter){
    for(int i = 0; i < k; i++){

        const char* actual = hash_iter_ver_actual(iter);

        if (actual == NULL) break;

        char* linea = hash_obtener(hash_y_abb->hash, actual);
        char* linea_del_heap = obtener_linea_del_heap(linea);      
        heap_encolar(heap, linea_del_heap);

        if (hash_iter_avanzar(iter) == false) break;
    }
}

void filtrar_mayor_prioridad(hash_y_abb_t* hash_y_abb, int k, heap_t* heap, hash_iter_t* iter){
    for(size_t j = k; j < hash_cantidad(hash_y_abb->hash); j++){

        const char* actual = hash_iter_ver_actual(iter);  

        if (actual == NULL){
             if (!hash_iter_avanzar(iter)) break;
             continue; 
        }    
        char* linea = hash_obtener(hash_y_abb->hash, actual);
        char* linea_del_heap = obtener_linea_del_heap(linea);
        char* minimo = heap_ver_max(heap);
    
        if (comparar_heap_minimos(linea_del_heap, minimo) < 0){

            char* linea_a_borrar = heap_desencolar(heap);
            heap_encolar(heap, linea_del_heap);
            free(linea_a_borrar);
        }
        else free(linea_del_heap);

        if(!hash_iter_avanzar(iter)) break;
    }
}

void imprimir_lineas_apiladas(pila_t* pila, heap_t* heap, size_t cantidad_heap){
    for(size_t i = 0; i < cantidad_heap; i++){
        char* linea_desapilada = pila_desapilar(pila);
        char** palabras = split(linea_desapilada,',');
        fprintf(stdout,"%s - %s\n", palabras[0], palabras[1]);
        free(linea_desapilada);
        free_strv(palabras);
    } 
}

bool prioridad_vuelos(hash_y_abb_t* hash_y_abb, int k){           
    heap_t* heap = heap_crear(comp_heap);           //Creo el heap y lo destruyo en la misma funcion, sino deberia actualizarlo al mismo tiempo que las demas estructuras
    if (!heap) return false;                             //de datos
    pila_t* pila = pila_crear();
    if (!pila){
        free(heap);
        return false;
    }
    redimensionar(hash_y_abb->hash, hash_cantidad(hash_y_abb->hash));
    hash_iter_t* iter = hash_iter_crear(hash_y_abb->hash);
    if (!iter){
        free(heap);
        free(pila);
        return false;
    }

    encolar_lineas_heap(hash_y_abb, k, heap, iter);

    filtrar_mayor_prioridad(hash_y_abb, k, heap, iter);

    size_t cantidad_heap = heap_cantidad(heap);
    apilar_lineas(heap, pila, cantidad_heap);

    imprimir_lineas_apiladas(pila, heap, cantidad_heap);

    hash_iter_destruir(iter);
    pila_destruir(pila);
    heap_destruir(heap, free);
    return true;      
}

bool comando_agregar_archivo(char** palabras, hash_y_abb_t* hash_y_abb){
    if ((palabras[1] == NULL)||(palabras[2] != NULL)){
        fprintf(stderr, "Error en comando agregar_archivo\n");
        free_strv(palabras);
        return false;
    }

    if(hash_y_abb->abb == NULL) hash_y_abb->abb = abb_crear(comparacion,free);         //Si no esta creado el abb, lo creo       
            
    if(hash_y_abb->hash == NULL) hash_y_abb->hash = hash_crear(free); 
  
    if (!agregar_archivo(hash_y_abb, palabras)){
        fprintf(stderr, "Error en comando agregar_archivo\n");
        free_strv(palabras);
        return false;
    }
    fprintf(stdout,"OK\n");
    return true;
}

bool comando_ver_tablero(char** palabras, hash_y_abb_t* hash_y_abb){
    if((palabras[1] == NULL) || (palabras[2] == NULL) || (palabras[3] == NULL) || (palabras[4] == NULL)){       //Hago 5 validaciones, por si me pasan parametros incorrectos
        fprintf(stderr, "Error en comando ver_tablero\n");
        free_strv(palabras);
        return false;
    }

    if(palabras[5] != NULL){
        fprintf(stderr, "Error en comando ver_tablero\n");
        free_strv(palabras);
        return false;
    }

    if(isdigit(*palabras[1]) == 0){
        fprintf(stderr, "Error en comando ver_tablero\n");
        free_strv(palabras);
        return false;
    }

    int n = atoi(palabras[1]);

    if( n < 0){
        fprintf(stderr, "Error en comando ver_tablero\n");
        free_strv(palabras);
        return false;
    }

    if(((strcmp(palabras[2], "asc") != 0) && (strcmp(palabras[2], "desc") !=0 )) || (strcmp(palabras[4], palabras[3]) <0 )){
        fprintf(stderr, "Error en comando ver_tablero\n");
        free_strv(palabras);
        return false;
    }
    ver_tablero(hash_y_abb,n, palabras[2], palabras[3], palabras[4]);
    fprintf(stdout, "OK\n");
    return true;
}

bool comando_info_vuelo(char** palabras, hash_y_abb_t* hash_y_abb){
    if(palabras[1] == NULL){                                    //Validaciones por si me pasan parametros incorrectos
        fprintf(stderr, "Error en comando info_vuelo\n");
        free_strv(palabras);
        return false;
    }
    if((isdigit(*palabras[1]) == 0) || (palabras[2] != NULL)){
        fprintf(stderr, "Error en comando info_vuelo\n");
        free_strv(palabras);
        return false;
    }
    int n = atoi(palabras[1]);

    if( n < 0){
        fprintf(stderr, "Error en comando info_vuelo\n");
        free_strv(palabras);
        return false;
    }
    modificar_ultimo_caracter(palabras[1]);
    
    if (!hash_pertenece(hash_y_abb->hash,palabras[1])){
        fprintf(stderr, "Error en comando info_vuelo\n");
        free_strv(palabras);
        return false;
    }
    mostrar_info_vuelo(hash_y_abb->hash,palabras[1]);    
    fprintf(stdout, "OK\n");
    return true; 
}

bool comando_prioridad_vuelos(char** palabras, hash_y_abb_t* hash_y_abb){
    if((isdigit(*palabras[1]) == 0) || (palabras[2] != NULL) || (palabras[1] == NULL)){   //Validacion por si me pasan parametros incorrectos
        fprintf(stderr, "Error en comando prioridad_vuelos\n");
        free_strv(palabras);
        return false;
    }

    int n=atoi(palabras[1]);      
    if (!prioridad_vuelos(hash_y_abb,n)) return false;
    fprintf(stdout, "OK\n");
    return true;
}

bool comando_borrar(char** palabras, hash_y_abb_t* hash_y_abb){
    if((palabras[1] == NULL)||(palabras[2] == NULL)){    //Validacion por si me pasan parametros incorrectos
        fprintf(stderr, "Error en comando borrar\n"); 
        free_strv(palabras);
        return false;
    }
    if((strcmp(palabras[1],palabras[2]) > 0)||(palabras[3] != NULL)){
        fprintf(stderr, "Error en comando borrar\n");
        free_strv(palabras);
        return false;
    }
    borrar(hash_y_abb, palabras[1], palabras[2]);
    fprintf(stdout, "OK\n");
    return true;
}

int main(){

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    hash_y_abb_t* hash_y_abb = malloc(sizeof(hash_y_abb_t));
    hash_y_abb->abb = NULL;
    hash_y_abb->hash = NULL;

    while ((read = getline(&line, &len, stdin)) != -1){              //Leo linea a linea los comandos

        char** palabras = split(line,' ');
        if((palabras[1]==NULL) && (palabras[0]!=NULL)) modificar_ultimo_caracter(palabras[0]);
            
        if(strcmp(palabras[0],"agregar_archivo") == 0){       //SI el comando es agregar archivo, creo un archivo

            if (!comando_agregar_archivo(palabras, hash_y_abb)) continue;
        }

        if(strcmp(palabras[0],"ver_tablero") == 0){ // El comando es ver_tablero

            if (!comando_ver_tablero(palabras, hash_y_abb)) continue;          
        }

        if(strcmp(palabras[0],"info_vuelo") == 0){                       //Comando informacion del vuelo

            if (!comando_info_vuelo(palabras, hash_y_abb)) continue;
        }

        if(strcmp(palabras[0],"prioridad_vuelos") == 0){                   //Comando prioridad vuelos

            if (!comando_prioridad_vuelos(palabras, hash_y_abb)) continue;
        }

        if(strcmp(palabras[0],"borrar") == 0){   //Comando borrar 

            if (!comando_borrar(palabras, hash_y_abb)) continue;
        }
        free_strv(palabras);   
    } 
    if(hash_y_abb->hash) hash_destruir(hash_y_abb->hash);
    if(hash_y_abb->abb) abb_destruir(hash_y_abb->abb);

    free(hash_y_abb);
    free(line);

    return 0;
}
