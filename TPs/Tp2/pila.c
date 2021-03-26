//CORRECTOR: EZEQUIEL GENENDER
//ALUMNO: DAMIAN GANOPOLSKY
//TP: PILA

#include "pila.h"
#include <stdlib.h>
#define MIN_TAM 10
#define FACTOR_DE_REDIMENSION 2
#define CRITERIO_DE_REDIMENSION 4

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/


pila_t* pila_crear(void){
    pila_t* pila = malloc(sizeof(pila_t));
    
    if (pila==NULL) 
        return NULL;
    pila->datos = malloc(MIN_TAM * sizeof(void *));
    
    if (pila->datos==NULL) {
        free(pila);
        return NULL;
            }

    pila->cantidad = 0;
    pila->capacidad = MIN_TAM;
    return pila;
}

void pila_destruir(pila_t *pila)
{
    free(pila->datos);
    free(pila);
}


bool pila_esta_vacia(const pila_t *pila){
    
    if(pila->cantidad==0)
        return true;
    else
        return false;
}



bool pila_redimensionar(pila_t *pila, size_t nuevo_tam)
{

    if (nuevo_tam < pila->capacidad) 
        nuevo_tam = pila->capacidad;

    void **nuevo = realloc(pila->datos, nuevo_tam * sizeof(void *));
    if (nuevo==NULL) 
        return false;

    pila->datos = nuevo;
    pila->capacidad = nuevo_tam;
    return true;
}

bool pila_apilar(pila_t *pila, void* valor)
{
    if (pila==NULL) 
        return false;

    if (pila->cantidad == pila->capacidad) { //Verifica si esta en el caso limite
        
        if (!pila_redimensionar(pila, FACTOR_DE_REDIMENSION * pila->capacidad)) { 
            return false;
    }
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}


void* pila_ver_tope(const pila_t *pila){
    
    if(pila_esta_vacia(pila)==true){
        return NULL;}

    else{
        void *r=pila->datos[pila->cantidad-1];
        return r;
}
}


void * pila_desapilar(pila_t *pila)
{
    if (pila_esta_vacia(pila)==true) 
        return NULL;
    // Desapila y se guarda el tope.
    pila->cantidad--;
    void *r = pila->datos[pila->cantidad]; // Apunto al nuevo tope  
    
    if ((pila->capacidad > MIN_TAM) && (pila->cantidad <= (pila->capacidad/CRITERIO_DE_REDIMENSION))) {
        
        pila_redimensionar(pila, pila->capacidad / FACTOR_DE_REDIMENSION);
    }
    return r;
}





