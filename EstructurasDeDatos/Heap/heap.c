#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"
#define MIN_TAM 10
#define FACTOR_DE_REDIMENSION 2
#define CRITERIO_DE_REDIMENSION 4


                            /* ESTRUCTURA DEL HEAP */

struct heap{

    void** datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
};

                               /* FUNCIONES AUXILIARES */

bool heap_redimensionar(heap_t* heap, size_t nuevo_tam){

    if (nuevo_tam < heap->tam) 
        nuevo_tam = heap->tam;

    void **nuevo = realloc(heap->datos, nuevo_tam * sizeof(void *));
    if (nuevo==NULL) 
        return false;

    heap->datos = nuevo;
    heap->tam = nuevo_tam;
    return true;
}


void downheap(void** arreglo,size_t tam,size_t pos,cmp_func_t cmp){

	if (pos >= tam) return;

	size_t min = pos; 
	size_t izq = 2 * pos + 1;
	size_t der = 2 * pos + 2;

	if ((izq < tam )&& (cmp(arreglo[izq], arreglo[min]) > 0))
		min = izq;

	if ((der < tam) && (cmp(arreglo[der], arreglo[min]) > 0))
		min = der;

	if (min != pos){
		void* aux=arreglo[min];
        arreglo[min]=arreglo[pos];
        arreglo[pos]=aux;
		downheap(arreglo,tam, min,cmp);
    }

}


void upheap(void** arreglo,size_t pos,cmp_func_t cmp){

	if (pos == 0) return;

	size_t padre = (pos-1) / 2;

	if (cmp(arreglo[padre], arreglo[pos]) < 0){ 

        void* aux=arreglo[padre];
        arreglo[padre]=arreglo[pos];
        arreglo[pos]=aux;
		upheap(arreglo, padre, cmp);

    }

}

                                    /* PRIMITIVAS A ENTREGAR */

heap_t *heap_crear(cmp_func_t cmp){

    heap_t* heap=malloc(sizeof(heap_t));

    if(!heap) return NULL;

    heap->datos=malloc(sizeof(void*)*MIN_TAM);

    if(!heap->datos){

        free(heap);
        return NULL;
    }

    heap->tam=MIN_TAM;
    heap->cant=0;
    heap->cmp=cmp;
    
    return heap;
}


bool heap_encolar(heap_t *heap, void *elem){

    if(heap==NULL) return false;

    if (heap->cant == heap->tam) { 
        
        if (!heap_redimensionar(heap, FACTOR_DE_REDIMENSION * heap->tam))  
            return false;
    }

    heap->datos[heap->cant]=elem;
    size_t pos=heap->cant;
    heap->cant++;    
    upheap(heap->datos,pos,heap->cmp);

    return true;
}


void *heap_desencolar(heap_t *heap){

    if (heap_esta_vacio(heap)==true)  return NULL; 

    heap->cant--;
    void* apunto_al_primero=heap->datos[0];
    heap->datos[0]=heap->datos[heap->cant];
    downheap(heap->datos,heap->cant,0,heap->cmp);

    if ((heap->tam > MIN_TAM) && (heap->cant <= (heap->tam/CRITERIO_DE_REDIMENSION))) {
        
        heap_redimensionar(heap, heap->tam / FACTOR_DE_REDIMENSION);
    }

    return apunto_al_primero;
}
           


size_t heap_cantidad(const heap_t *heap){

    return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap){

    return heap->cant==0;
}


void *heap_ver_max(const heap_t *heap){

    if (heap_esta_vacio(heap)) return NULL;

    else return heap->datos[0];
}


void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){

    if(destruir_elemento!=NULL){

        for(int i=0;i<heap->cant;i++){

            destruir_elemento(heap->datos[i]);
        }
    }

    free(heap->datos);
    free(heap);
}


heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){

    heap_t* heap=heap_crear(cmp);
    heap_redimensionar(heap,n);

    for(size_t j=0;j<n;j++){

        heap->datos[j]=arreglo[j];
    }
    
    for(size_t i=n-1;i>=0;i--){

        downheap(heap->datos,n,i,cmp);

        if(i==0) break;
    }
  
    heap->cant=n;

    return heap;       

} 


void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){

    heap_t* heap=heap_crear_arr(elementos,cant,cmp);

    for(size_t i=cant-1;i>=0;i--){

        void* aux=heap->datos[0];
        heap->datos[0]=heap->datos[i];
        heap->datos[i]=aux;
        elementos[i]=aux;
        downheap(heap->datos,i,0,heap->cmp);
        if(i==0) break;
    }
    heap_destruir(heap,NULL);

}  
