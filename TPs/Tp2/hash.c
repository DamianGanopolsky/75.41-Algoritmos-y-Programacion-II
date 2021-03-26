/* ******************************************************************
 *      Alumnos: Giadas Juan Ignacio y Damian
        Padrones: 101713 y 101168
        Ayudante a cargo: Tomas Lofano
 * *****************************************************************/
#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include "lista.h"
#include "hash.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MIN_TAM 17
#define A 54059 //Constantes que usa la funcion de hash
#define B 76963 
#define C 86969 
#define FIRSTH 37 
#define FACTOR_DE_REDIMENSION1 2
#define FACTOR_DE_REDIMENSION2 0.25

struct hash{
    lista_t** listas;
    size_t capacidad;
    size_t cantidad;
    hash_destruir_dato_t destruir_dato;
};

struct campo{
    const char* clave;
    void* valor;
};

typedef struct campo campo_t;

struct hash_iter{
    const hash_t* hash;
    size_t pos;
    size_t elementos_recorridos;
    lista_iter_t* iter_lista;
};

/* *****************************************************************
 *                    FUNCIONES AUXILIARES  
 * *****************************************************************/


size_t hash_str( const char *clave) {

    size_t largo = strlen(clave);
    unsigned int n = 0;

    for (unsigned int i = 0; i < largo; i++) {
        n = 31 * n +(unsigned int)clave[i];
    }
    return n ;
}


void* crear_campo(const char* clave, void* dato){

    campo_t* campo = malloc(sizeof(campo_t));

    if (campo == NULL) return NULL;

    campo->clave = strdup(clave);
    if(campo->clave==NULL) return NULL;
    campo->valor = dato;

    return campo;
}

void avanzar_en_hash(hash_iter_t* iter){

    if (iter->hash->cantidad > 0){

        while (iter->hash->listas[iter->pos] == NULL && iter->pos < iter->hash->capacidad - 1)

            iter->pos += 1;
        
    }
}

void redimensionar(hash_t* hash,size_t nuevo_tam){
  
    lista_t** listaz=malloc(nuevo_tam * sizeof(lista_t*));
    if(!listaz) return;

    for(int j=0;j<nuevo_tam;j++)

        listaz[j]=NULL;

    for(int i=0;i<hash->capacidad;i++){

        if(hash->listas[i]==NULL) continue;
                           
        while(lista_largo(hash->listas[i])!=0){

            campo_t* campo=(campo_t*)lista_borrar_primero(hash->listas[i]);
            size_t clave_hasheada = hash_str(campo->clave) % nuevo_tam; 
                
            if(listaz[clave_hasheada]==NULL){

                listaz[clave_hasheada]=lista_crear();    
                if(!listaz[clave_hasheada]) return;
            }     
                           
            lista_insertar_ultimo(listaz[clave_hasheada],campo);

        }                        
     }
    lista_t** listas_aux=hash->listas;
    hash->listas=listaz;  

    for(int i=0;i<hash->capacidad;i++){

        if(listas_aux[i]==NULL) continue;                                
        
        lista_destruir(listas_aux[i],NULL);
    }  
  
    free(listas_aux);
    hash->capacidad=nuevo_tam;              
}


bool comparar(const char* clave1,const char* clave2){

    bool devolucion=true;

    if(strlen(clave1)!=strlen(clave2)) devolucion=false;

    if(devolucion==false) return false;
    
    for(int i=0;i<strlen(clave1);i++){

        if(*(clave1+i)!=*(clave2+i))  devolucion=false;
    }
    
    return devolucion;
}
        

 /* ******************************************************************
 *                    PRIMITIVAS DEL HASH
 * *****************************************************************/

/* Crea el hash
 */
hash_t *hash_crear(hash_destruir_dato_t destruir_dato){

    hash_t* hash = malloc(sizeof(hash_t));

    if (!hash) return NULL;        

    hash->listas = malloc(MIN_TAM * sizeof(lista_t*));

    if (hash->listas == NULL){
        free(hash);
        return NULL;
    }

    hash->capacidad = MIN_TAM;
    hash->cantidad = 0;
    hash->destruir_dato =destruir_dato;

    for(int i=0;i<hash->capacidad;i++)

        hash->listas[i]=NULL;

    return hash;
}

/* Guarda un elemento en el hash, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura hash fue inicializada
 * Post: Se almacenó el par (clave, dato)
 */
bool hash_guardar(hash_t *hash, const char *clave, void *dato){
   
    size_t clave_hasheada = hash_str(clave) % hash->capacidad;  
    bool devuelve=false;
    bool paso=false; 
    
    if(hash->listas[clave_hasheada]==NULL){

        hash->cantidad += 1; 
        hash->listas[clave_hasheada]=lista_crear();
        if(!hash->listas[clave_hasheada]) return false;
        campo_t* campo = crear_campo(clave, dato);
        if(!campo) return false;

        paso=true;         
        devuelve=lista_insertar_ultimo(hash->listas[clave_hasheada],campo);
    }

    else{
        
        lista_iter_t* iter=lista_iter_crear(hash->listas[clave_hasheada]);

        if(!iter) return false;
        
        while(!lista_iter_al_final(iter)){

            campo_t* campo_actual=(campo_t*)lista_iter_ver_actual(iter);
            
            if(comparar(campo_actual->clave,clave)){

                void* dato_a_liberar=campo_actual->valor;
                paso=true;                
                campo_actual->valor=dato;
                lista_iter_destruir(iter);
                if(hash->destruir_dato!=NULL) hash->destruir_dato(dato_a_liberar);
                devuelve=true;
                break;
            }          
            lista_iter_avanzar(iter);                 
        } 

        if(paso!=true){
            
            campo_t* campo = crear_campo(clave, dato); 
            if(!campo) return false;
            devuelve=lista_insertar_ultimo(hash->listas[clave_hasheada],campo);
            lista_iter_destruir(iter);
            hash->cantidad+=1;
        }
    }

    if (hash->cantidad / hash->capacidad >= FACTOR_DE_REDIMENSION1) redimensionar(hash,hash->capacidad*FACTOR_DE_REDIMENSION1);
             
    return devuelve;
}


void *hash_borrar(hash_t* hash, const char *clave){

    size_t clave_hasheada = hash_str(clave) % hash->capacidad;

    if(hash->listas[clave_hasheada] == NULL) return NULL;
    
    lista_iter_t* iter=lista_iter_crear(hash->listas[clave_hasheada]);

    if(iter==NULL) return NULL;

    void* dato_asociado=NULL;   

    while(!lista_iter_al_final(iter)){

        campo_t* campo_actual=(campo_t*)lista_iter_ver_actual(iter);
        
        if((comparar(campo_actual->clave,clave))){
           
            hash->cantidad = hash->cantidad-1;            
            campo_t* campo_a_borrar=lista_iter_borrar(iter); 
            dato_asociado=campo_a_borrar->valor;
            free((char*)campo_a_borrar->clave);
            free(campo_a_borrar); 
            break;          
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    if(((hash->cantidad/hash->capacidad)<=FACTOR_DE_REDIMENSION2)&&(hash->capacidad>MIN_TAM)){
        
         redimensionar(hash,hash->capacidad/FACTOR_DE_REDIMENSION1);
    }
    return dato_asociado;
}

        
void *hash_obtener(const hash_t *hash, const char *clave){

    size_t clave_hasheada = hash_str(clave) % hash->capacidad;
    
    if(hash->listas[clave_hasheada] == NULL) return NULL;

    lista_iter_t* iter=lista_iter_crear(hash->listas[clave_hasheada]);

    if(iter==NULL) return NULL;

    while(!lista_iter_al_final(iter)){

        campo_t* campo_actual=(campo_t*)lista_iter_ver_actual(iter);
        
        if(comparar(campo_actual->clave,clave)){

            lista_iter_destruir(iter);                      
            return campo_actual->valor;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return NULL;
}        
        

bool hash_pertenece(const hash_t *hash, const char *clave){

    size_t clave_hasheada = hash_str(clave) % hash->capacidad;
    
    if(hash->listas[clave_hasheada] == NULL) return false;

    lista_iter_t* iter=lista_iter_crear(hash->listas[clave_hasheada]);

    if(iter==NULL) return false;

    while(!lista_iter_al_final(iter)){

        campo_t* campo_actual=(campo_t*)lista_iter_ver_actual(iter);
        
        if(comparar(campo_actual->clave,clave)){
            lista_iter_destruir(iter);                    
            return true;
        }
        lista_iter_avanzar(iter);
    }     
    lista_iter_destruir(iter);
    return false;
}


size_t hash_cantidad(const hash_t *hash){

    return hash->cantidad;
}


void hash_destruir(hash_t *hash){

    for(int i=0;i<hash->capacidad;i++){

        if(hash->listas[i]==NULL) continue;
                           
        while(lista_largo(hash->listas[i])!=0){

            campo_t* campo=(campo_t*)lista_borrar_primero(hash->listas[i]);

            if(hash->destruir_dato!=NULL) hash->destruir_dato(campo->valor);
            free((char*)campo->clave);
            free(campo);            
        }
        lista_destruir(hash->listas[i],free);
    }
    free(hash->listas);
    free(hash);
}
            
 /* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

// Crea iterador
hash_iter_t *hash_iter_crear(const hash_t *hash){

    hash_iter_t* iter = malloc(sizeof(hash_iter_t));

    if (iter == NULL) return NULL;

    iter->hash = hash;
    iter->pos = 0;
    iter->elementos_recorridos = 0;
    iter->iter_lista = NULL;

    if (iter->hash->cantidad > 0){

        avanzar_en_hash(iter);

        if (iter->hash->listas[iter->pos] != NULL) iter->iter_lista = lista_iter_crear(iter->hash->listas[iter->pos]);
    }

    return iter;
}

// Avanza iterador
bool hash_iter_avanzar(hash_iter_t *iter){

    if (iter->iter_lista == NULL) return false;

    if(hash_iter_al_final(iter)) return false;

    lista_iter_avanzar(iter->iter_lista);
    iter->elementos_recorridos += 1; 

    if (lista_iter_al_final(iter->iter_lista)){

        lista_iter_destruir(iter->iter_lista);
        iter->iter_lista = NULL;

        if (iter->pos < iter->hash->capacidad - 1) iter->pos += 1;

        avanzar_en_hash(iter);

        if (iter->pos < iter->hash->capacidad && iter->hash->listas[iter->pos] != NULL){ 
            iter->iter_lista = lista_iter_crear(iter->hash->listas[iter->pos]);
            if(iter->iter_lista==NULL) return false;
            return true; 
        }
        else{
            return false; 
        }
    }
    return true;
}

// Devuelve clave actual, esa clave no se puede modificar ni liberar.
const char *hash_iter_ver_actual(const hash_iter_t *iter){

    if (iter->iter_lista == NULL) return NULL;

    if (lista_iter_ver_actual(iter->iter_lista) == NULL) return NULL;

    if(hash_iter_al_final(iter)) return NULL;

    campo_t* dato = (campo_t*) lista_iter_ver_actual(iter->iter_lista);

    return dato->clave;
}

// Comprueba si terminó la iteración
bool hash_iter_al_final(const hash_iter_t *iter){

    if (iter->iter_lista == NULL) return true;
    return (iter->elementos_recorridos == iter->hash->cantidad);
}

// Destruye iterador
void hash_iter_destruir(hash_iter_t* iter){
    if (iter->iter_lista != NULL) free(iter->iter_lista);
    free(iter);
} 


