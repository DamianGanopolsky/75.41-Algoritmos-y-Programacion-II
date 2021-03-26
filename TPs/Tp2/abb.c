#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "pila.h"
#include "cola.h"
#include "strutil.h"
#include "hash.h"
#include "abb.h"
#define RANGO_MENOR_A_DESDE 0
#define RANGO_MAYOR_A_HASTA 1
#define RANGO_CORRECTO 2

                           /* ESTRUCTURAS DEL ARBOL */
typedef struct n_abb{

    struct n_abb* izq;
    struct n_abb* der;
    void* dato;
    const char* clave;

}n_abb_t;


struct abb{

    n_abb_t* raiz;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
    size_t cant;

};

struct abb_iter{

    pila_t* pila;
};

                                 /* FUNCIONES AUXILIARES */

n_abb_t* crear_nodo(const char* clave,void* dato){  //Crea un nodo del arbol dinamicamente

    n_abb_t* nodo=malloc(sizeof(n_abb_t));

    if (nodo==NULL) return NULL;

    nodo->clave=strdup(clave);

    if(nodo->clave==NULL) return NULL;

    nodo->dato=dato;
    nodo->izq=NULL;
    nodo->der=NULL;
    return nodo;
}


n_abb_t* abb_buscar_nodo(n_abb_t* nodo,const char* clave,abb_comparar_clave_t cmp){   //Busca un nodo especifico en el arbol a partir de una clave

    if(nodo==NULL) return NULL;

    if(cmp(clave,nodo->clave)<0) return abb_buscar_nodo(nodo->izq,clave,cmp);
            
    if(cmp(clave,nodo->clave)>0) return abb_buscar_nodo(nodo->der,clave,cmp);        
    
    if(cmp(clave,nodo->clave)==0) return nodo;
            
    return NULL;
}


void obtener_post_order(n_abb_t* nodo,abb_destruir_dato_t destruir_dato){  //Recorre de manera post order y libera la memoria de los nodos, se usa en la
                                                                            // primitiva abb_destruir
    if(nodo==NULL) return ;

    obtener_post_order(nodo->izq,destruir_dato);
    obtener_post_order(nodo->der,destruir_dato);
    void* dato_a_liberar=nodo->dato;

    if(destruir_dato!=NULL) destruir_dato(dato_a_liberar);

    free((char*)nodo->clave);
    free(nodo);      
    return ;
}


n_abb_t* devolver_padre(n_abb_t* nodo,const char* clave,abb_comparar_clave_t cmp){   //Devuelve el padre o posible padre a partir de una clave

    if(cmp(clave,nodo->clave)<0){

        if(nodo->izq==NULL) return nodo;

        if(cmp(clave,nodo->izq->clave)==0) return nodo;
        
        return devolver_padre(nodo->izq,clave,cmp);
    }

    if(cmp(clave,nodo->clave)>0){

        if(nodo->der==NULL) return nodo;

        if(cmp(clave,nodo->der->clave)==0) return nodo;
        
        return devolver_padre(nodo->der,clave,cmp);
    }

    return NULL;
        
}   


void* liberar_y_devolver_nodo(n_abb_t* nodo_a_borrar,abb_destruir_dato_t destruir_dato){     //Libera un nodo y devuelve su dato asociado

        void* dato_a_devolver=nodo_a_borrar->dato;          
        free((char*)nodo_a_borrar->clave);
        free(nodo_a_borrar);
        return dato_a_devolver;
} 


void recorrido_inorder(n_abb_t* nodo,cola_t* cola){            //Encola todos los elementos del arbol de manera inorder,
                                                                //se usa en la primitiva del iterador interno 
    if(nodo==NULL) return;

    recorrido_inorder(nodo->izq,cola);
    cola_encolar(cola,nodo);
    recorrido_inorder(nodo->der,cola);  
}  

                                   /* PRIMITIVAS DEL ARBOL */

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

    abb_t* abb=malloc(sizeof(abb_t));
    
    if(!abb) return NULL;

    abb->raiz=NULL;
    abb->cmp=cmp;    
    abb->destruir_dato=destruir_dato;
    abb->cant=0;
    
    return abb;
}


bool abb_pertenece(const abb_t *arbol, const char *clave){

    n_abb_t* nodo=abb_buscar_nodo(arbol->raiz,clave,arbol->cmp);

    if(nodo!=NULL) return true;

    else return false;
}
 

void *abb_obtener(const abb_t *arbol, const char *clave){

    if(abb_pertenece(arbol,clave)==false) return NULL;

    else{

        n_abb_t* nodo=abb_buscar_nodo(arbol->raiz,clave,arbol->cmp);
        return nodo->dato;
    }
}


bool abb_guardar(abb_t *arbol, const char* clave, void *dato){
    
    arbol->cant++;

    if(arbol->raiz==NULL){

        n_abb_t* nodo=crear_nodo(clave,dato);
        arbol->raiz=nodo;
        return true;
    }

    if(abb_pertenece(arbol,clave)==true){

        n_abb_t* nodo=abb_buscar_nodo(arbol->raiz,clave,arbol->cmp);
        void* dato_a_liberar=nodo->dato;
        nodo->dato=dato;
        arbol->cant--;

        if(arbol->destruir_dato!=NULL) arbol->destruir_dato(dato_a_liberar);
    }
                                       
    else{

        n_abb_t* padre=devolver_padre(arbol->raiz,clave,arbol->cmp);
        
        if(arbol->cmp(clave,padre->clave)<0){

            n_abb_t* nodo=crear_nodo(clave,dato);
            padre->izq=nodo;
        }

        if(arbol->cmp(clave,padre->clave)>0){

            n_abb_t* nodo=crear_nodo(clave,dato);
            padre->der=nodo;
        }
    }
    
    return true;
}            


size_t abb_cantidad(abb_t *arbol){

    return arbol->cant;

}
   

void* abb_borrar(abb_t *arbol, const char *clave){

    if(!abb_pertenece(arbol,clave)) return NULL;             

    arbol->cant--;
    n_abb_t* padre=devolver_padre(arbol->raiz,clave,arbol->cmp);    
    n_abb_t* nodo_a_borrar=abb_buscar_nodo(arbol->raiz,clave,arbol->cmp);

    if((nodo_a_borrar->izq==NULL)&&(nodo_a_borrar->der==NULL)){     //Contemplo el caso en el que se trate de que el nodo a borrar tengo 0 hijos

        if(padre!=NULL){

            if(padre->izq==nodo_a_borrar) padre->izq=NULL;

            if(padre->der==nodo_a_borrar) padre->der=NULL; 
        }

        else arbol->raiz=NULL;
                   
        return liberar_y_devolver_nodo(nodo_a_borrar,arbol->destruir_dato);   

    }
    if((nodo_a_borrar->izq!=NULL)&&(nodo_a_borrar->der!=NULL)){     // Nodo a borrar con 2 hijos

        n_abb_t* nodo_reemplazante=nodo_a_borrar->der;

        while(nodo_reemplazante->izq!=NULL){

            nodo_reemplazante=nodo_reemplazante->izq;
        }

        const char* clave_aux=strdup(nodo_reemplazante->clave);       
        void* dato_a_devolver=nodo_a_borrar->dato;
        arbol->cant++;
        void* dato_aux=abb_borrar(arbol,nodo_reemplazante->clave);  
        free((char*)nodo_a_borrar->clave);
        nodo_a_borrar->clave=clave_aux;
        nodo_a_borrar->dato=dato_aux;
                       
        return dato_a_devolver;
    }

    else{                                                        //Nodo a borrar con 1 hijo

        n_abb_t* hijo_del_nodo_a_borrar;

        if(nodo_a_borrar->izq!=NULL) hijo_del_nodo_a_borrar=nodo_a_borrar->izq;

        if(nodo_a_borrar->der!=NULL) hijo_del_nodo_a_borrar=nodo_a_borrar->der;

        if(padre==NULL) arbol->raiz=hijo_del_nodo_a_borrar;                    
        
        else{

            if(padre->der==nodo_a_borrar) padre->der=hijo_del_nodo_a_borrar;

            if(padre->izq==nodo_a_borrar) padre->izq=hijo_del_nodo_a_borrar;
        }

        return liberar_y_devolver_nodo(nodo_a_borrar,arbol->destruir_dato); 

    }        

    return NULL;
}
        

void abb_destruir(abb_t *arbol){
    
    obtener_post_order(arbol->raiz,arbol->destruir_dato);
    free(arbol);
}

                    /* PRIMITIVAS DEL ITERADOR EXTERNO */

abb_iter_t* abb_iter_in_crear(const abb_t *arbol){

    abb_iter_t* abb_iter=malloc(sizeof(abb_iter_t));

    if(!abb_iter) return NULL;

    abb_iter->pila=pila_crear();

    if(!abb_iter->pila){

        free(abb_iter);
        return NULL;
    }
    
    if(arbol->raiz!=NULL){
        pila_apilar(abb_iter->pila,arbol->raiz);    
        n_abb_t* n_aux=arbol->raiz->izq;
    

        while(n_aux!=NULL){
           
            pila_apilar(abb_iter->pila,n_aux);
            n_aux=n_aux->izq;
        }
    }
    
    return abb_iter;
}


const char *abb_iter_in_ver_actual(const abb_iter_t *iter){

    n_abb_t* nodo_aux=pila_ver_tope(iter->pila);

    if(nodo_aux==NULL) return NULL;

    return nodo_aux->clave;
}


bool abb_iter_in_al_final(const abb_iter_t *iter){

    return pila_esta_vacia(iter->pila);
}


bool abb_iter_in_avanzar(abb_iter_t *iter){

    n_abb_t* nodo_aux=pila_desapilar(iter->pila);

    if(nodo_aux==NULL) return false;

    if(!nodo_aux->der) return true;

    nodo_aux=nodo_aux->der;
    pila_apilar(iter->pila,nodo_aux);
    nodo_aux=nodo_aux->izq;

    while(nodo_aux!=NULL){

        pila_apilar(iter->pila,nodo_aux);
        nodo_aux=nodo_aux->izq;
    }

    return true;
}


void abb_iter_in_destruir(abb_iter_t* iter){

    pila_destruir(iter->pila);
    free(iter);
}


//Primitiva hecha en el TP2, recorre el arbol descartando mitades como en busqueda binaria

void recorrer_inorder(abb_t* abb, hash_t* hash, n_abb_t* nodo, cola_t* cola, pila_t* pila, int visitar(const char *, char*, char*, char*), char* desde, char* hasta, char* modo){   
 
    if(nodo == NULL) return;

    if(visitar(nodo->clave, desde, hasta, modo) == RANGO_MAYOR_A_HASTA){

          recorrer_inorder(abb, hash, nodo->izq, cola, pila, visitar, desde, hasta, modo);
    }

    if(visitar(nodo->clave, desde, hasta, modo) == RANGO_CORRECTO){

        recorrer_inorder(abb, hash, nodo->izq, cola, pila, visitar, desde, hasta, modo);
        if((strcmp(modo,"borrar")==0)||(strcmp(modo,"asc")==0)) cola_encolar(cola, (char*)nodo->dato);    //Si el modo no es el correcto, no completo
        if(strcmp(modo,"desc")==0) pila_apilar(pila, (char*)nodo->dato);                                  //la otra estructura auxiliar
        recorrer_inorder(abb, hash, nodo->der, cola, pila, visitar, desde, hasta, modo);

    }

    if(visitar(nodo->clave, desde, hasta, modo) == RANGO_MENOR_A_DESDE){

          recorrer_inorder(abb, hash, nodo->der, cola, pila, visitar, desde, hasta, modo);
    }

}  

                                /* PRIMITIVA DEL ITERADOR INTERNO */
void imprimir_linea(char* linea, size_t* cont){
    char** palabras = split(linea,',');            
    fprintf(stdout,"%s - %s\n", palabras[6], palabras[0]);
    free_strv(palabras);        
    *cont += 1;
}


void accion_por_rangos(abb_t *arbol,hash_t* hash, int visitar(const char *, char *, char *,char *), char* desde,char* hasta,char* modo,int k){

    cola_t* cola = NULL;
    pila_t* pila = NULL;
    cola = cola_crear();
    if (!cola) return;
    pila = pila_crear();
    if (!pila){
        cola_destruir(cola, free);
        return;
    }
    recorrer_inorder(arbol, hash, arbol->raiz, cola, pila, visitar, desde, hasta, modo);
    char* linea2;
    size_t cont = 0;

    if(strcmp(modo,"borrar")==0){   //Si el modo es NULL, significa que Barbara quiere borrar el rango que me paso

        while(!cola_esta_vacia(cola)){

            linea2 = cola_desencolar(cola);       
            char** palabras = split(linea2, ','); 
            char* linea_a_mostrar = join(palabras, ' ');
            free(hash_borrar(hash, palabras[0]));
            free(abb_borrar(arbol, linea2));
            fprintf(stdout,"%s", linea_a_mostrar);
            free_strv(palabras);
            free(linea_a_mostrar);
        }
        cola_destruir(cola, NULL);
        pila_destruir(pila);
        return;
    }
    
                   
    if(strcmp(modo,"asc") == 0){

        while((!cola_esta_vacia(cola))&&(cont<k)){

            linea2 = cola_desencolar(cola);
            imprimir_linea(linea2, &cont);
        }
    }

    if(strcmp(modo,"desc") == 0){

        while((!pila_esta_vacia(pila))&&(cont<k)){

            linea2 = pila_desapilar(pila);  
            imprimir_linea(linea2, &cont);
        }
    }
  
    cola_destruir(cola, NULL);
    pila_destruir(pila);
}
