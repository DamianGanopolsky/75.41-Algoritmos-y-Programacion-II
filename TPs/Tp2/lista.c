#include <stdlib.h>
#include "lista.h"
#include <stdbool.h>


typedef struct nodo{
    void *dato;
    struct nodo* prox;
}nodo_t;

struct lista_iter{
    nodo_t* actual;
    nodo_t* anterior;
    lista_t* lista;
};


struct lista{
    nodo_t* prim;
    nodo_t* ult;
    size_t largo;
};

//typedef struct lista lista_t;

lista_t* lista_crear(void){

    lista_t* lista=malloc(sizeof(lista_t));
    
    if(!lista) return NULL;
            
    lista->prim=NULL;
    lista->ult=NULL;
    lista->largo=0;
    return lista;
}  


bool lista_esta_vacia(const lista_t *lista){

    return (lista->prim==NULL)&&(lista->ult==NULL);
}


bool lista_insertar_primero(lista_t *lista, void *dato){
    
    if(!lista) return false;
        
    nodo_t* nodo= malloc(sizeof(nodo_t));

    if(!nodo) return false;
        
    nodo->dato=dato;
    nodo->prox=lista->prim;
    lista->prim=nodo;

    if(lista->ult==NULL) lista->ult=nodo;        

    lista->largo++;
    return true;
}


bool lista_insertar_ultimo(lista_t *lista, void *dato){
    
    if(!lista) return false;      

    nodo_t* nodo= malloc(sizeof(nodo_t));

    if(!nodo) return false;        

    nodo->dato=dato;
    nodo->prox=NULL;
    nodo_t* ult_anterior=lista->ult;
    lista->ult=nodo;

    if(lista->prim==NULL) lista->prim=nodo;        
    
    else 
        ult_anterior->prox=nodo;
  
    lista->largo++;
    return true;
}


void* lista_borrar_primero(lista_t *lista){

    if((!lista)||(lista_esta_vacia(lista))) return NULL;
        
    nodo_t* nodo_a_liberar=lista->prim;
    void* valor_a_devolver=lista->prim->dato;

    if(lista->prim==lista->ult){
        
        lista->prim=NULL;
        lista->ult=NULL;
    }

    else
        lista->prim=lista->prim->prox;
        
    free(nodo_a_liberar);
    lista->largo--;
    return valor_a_devolver;
}


void* lista_ver_primero(const lista_t *lista){
    
    if(lista_esta_vacia(lista)) return NULL;
        
    else
        return lista->prim->dato;
}


void* lista_ver_ultimo(const lista_t *lista){

    if(lista_esta_vacia(lista)) return NULL;
        
    else
        return lista->ult->dato;

}


size_t lista_largo(const lista_t *lista){

    return lista->largo;
}


void lista_destruir(lista_t *lista, void destruir_dato(void *)){

    while(lista_esta_vacia(lista)==false){
            
        void* dato=lista_borrar_primero(lista);

        if(destruir_dato!=NULL)
            destruir_dato(dato);
     }
     free(lista);
}
               

lista_iter_t* lista_iter_crear(lista_t *lista){
    
    lista_iter_t* lista_iter=malloc(sizeof(lista_iter_t));

    if(!lista_iter) return NULL;
        
    lista_iter->anterior=NULL;
    lista_iter->actual=lista->prim;
    lista_iter->lista=lista;  
    return lista_iter;
}


void lista_iter_destruir(lista_iter_t* iter){

    free(iter);
}


bool lista_iter_avanzar(lista_iter_t *iter){
    
    if(iter->actual==NULL) return false;        

    else{
        iter->anterior=iter->actual;  
        iter->actual=iter->actual->prox;  
        return true;
        
    }   
}
    

void* lista_iter_ver_actual(const lista_iter_t *iter){
    
    if(iter->actual==NULL) return NULL;
        
    else 
        return iter->actual->dato;
            
}


bool lista_iter_al_final(const lista_iter_t *iter){
    
    return !iter->actual;

}


bool lista_iter_insertar(lista_iter_t *iter, void *dato){

    if(!iter) return false;     
    bool devolucion=true;     

    if(lista_esta_vacia(iter->lista)||(lista_iter_al_final(iter))){
       
        devolucion=lista_insertar_ultimo(iter->lista,dato);
        iter->actual=iter->lista->ult;           
    }

    else{
        if(iter->lista->prim==iter->actual){
               
            devolucion=lista_insertar_primero(iter->lista,dato);  
            iter->actual=iter->lista->prim;    
         }
    
        else{
            nodo_t* nodo= malloc(sizeof(nodo_t));
            if(!nodo) return false;            
            nodo->dato=dato;
            nodo->prox=NULL;
            iter->lista->largo++;
            nodo->prox=iter->actual;
            iter->actual=nodo;
            iter->anterior->prox=nodo;        
        }       
    }   
    return devolucion;           
}
        


              
        
void *lista_iter_borrar(lista_iter_t *iter){
    
    if(iter->actual==NULL) return NULL;
           
    void* dato_a_devolver=iter->actual->dato;
    nodo_t* nodo_aux=iter->actual;    

    if(iter->lista->prim==iter->actual){

        dato_a_devolver=lista_borrar_primero(iter->lista);
        iter->actual=iter->lista->prim;
    }

    else{       
        iter->lista->largo--;      
        iter->anterior->prox=iter->actual->prox;
       
        if(iter->actual==iter->lista->ult) iter->lista->ult=iter->anterior;            
    
        iter->actual=iter->actual->prox;                      
        free(nodo_aux);
    }
    return dato_a_devolver;            
}


void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    
    nodo_t* actual=lista->prim;
    while(actual!=NULL){

        if(visitar(actual->dato,extra)==false)
            break;
        actual=actual->prox;
    }
}
    
              
    




    
