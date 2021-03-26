
#include "cola.h"
#include<stdlib.h>

typedef struct nodo{
    void *dato;
    struct nodo* prox;
}nodo_t;

struct cola{
    nodo_t* prim;
    nodo_t* ult;
};


cola_t* cola_crear(void){
    cola_t* cola = malloc(sizeof(cola_t));
    
    if(cola==NULL)
        return NULL;
    
    cola->prim=NULL;
    cola->ult=NULL;   
    return cola;
}


bool cola_esta_vacia(const cola_t *cola){
    
    if((cola->prim==NULL)&&(cola->ult==NULL))
        return true;
    else
        return false;
}
   

bool cola_encolar(cola_t *cola, void* valor){

    if(cola==NULL)
        return false;

    nodo_t* nodo= malloc(sizeof(nodo_t));

    if(nodo==NULL)
        return false;
    
    nodo->dato=valor;
    nodo->prox=NULL;
    
    if(cola_esta_vacia(cola)==true){
               
        cola->prim=nodo;
        cola->ult=nodo;
}

    else{
              
        cola->ult->prox=nodo;
        cola->ult=nodo;
}
    return true;
}


void* cola_desencolar(cola_t *cola){
    
    nodo_t* nodo_a_liberar;
    
    if((cola==NULL)||(cola_esta_vacia(cola)))
        return NULL;
  
    nodo_a_liberar=cola->prim;
    void* dato_a_devolver=cola->prim->dato;

    if(cola->prim==cola->ult){

        cola->prim=NULL;
        cola->ult=NULL;     
}
    else            
        cola->prim=cola->prim->prox;   

    free(nodo_a_liberar);
    return dato_a_devolver;
}


void* cola_ver_primero(const cola_t *cola){

    if(cola->prim==NULL)
        return NULL;
    else
        return cola->prim->dato;
}   


void cola_destruir(cola_t *cola, void destruir_dato(void*)){
    
    while(cola_esta_vacia(cola)==false){
            
        void* dato=cola_desencolar(cola);

        if(destruir_dato!=NULL)
            destruir_dato(dato);
     }
     free(cola);
}




