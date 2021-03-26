

#ifndef lista_h
#define lista_h

#include <stdbool.h>
#include <stddef.h>
#include<stdio.h>
#include <stdlib.h>


typedef struct lista lista_t;

typedef struct lista_iter lista_iter_t;

/* PRIMITIVAS DE LA LISTA*/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);


// Devuelve verdadero si la lista no tiene elementos , false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);


// Agrega un nuevo elemento a la lista, que va a ser el primero de dicha lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al inicio
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);


// Agrega un nuevo elemento a la lista, que va a ser el ultimo de dicha lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);


// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);


// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);


// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);


//Obtiene el valor del largo de la lista
//Pre: la lista fue creada
//Post: Se devolvio el valor entero del largo de la lista
size_t lista_largo(const lista_t *lista);


// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));





/*PRIMITIVAS DEL ITERADOR EXTERNO */ 


// Crea un  iterador.
// Post: devuelve un iterador,cuyo actual apunta al primero y anterior a NULL.
lista_iter_t *lista_iter_crear(lista_t *lista);

//Avanza una posicion con el iterador, los punteros apuntan al proximo nodo
//Pre: la lista fue creada, el iterador fue creado
//post: devuelve true si se pudo avanzar 1 posicion, o false si no se pudo
bool lista_iter_avanzar(lista_iter_t *iter);

//Devuelve un puntero apuntando al elemento actual del iterador
//Pre: la lista fue creada y el iterador tambien
//Post: devuelve el puntero al valor actual, o NULL si se apunta a NULL
void *lista_iter_ver_actual(const lista_iter_t *iter);

//Devuelve verdadero si actual apunta a NULL
//Pre: la lista fue creada y el iterador tambien
//Post: devolvio verdadero si el iterador se encuentra al final, o falso si no es el caso
bool lista_iter_al_final(const lista_iter_t *iter);

//Destruye el iterador de lista
//Pre: EL iterador de lista fue creado
// Post: se destruyo el iterador de lista
void lista_iter_destruir(lista_iter_t *iter);

//Inserta un nodo en el actual del iterador
//Pre: La lista fue creada y el iterador tambien
//Post: Devuelve verdadero si se pudo insertar el dato dentro del nodo en el nuevo nodo
// o falso si no se pudo insertar
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

//Borra el nodo actual del iterador
//Pre: La lista fue creada y el iterador tambien
//Post: Devuelve el valor del nodo borrado o NULL si no se pudo borrar el nodo
void *lista_iter_borrar(lista_iter_t *iter);



/* PRIMITIVA DEL ITERADOR INTERNO*/

// Itera la lista internamente
//Pre: La lista fue creada
//Post: Itera la lista y en cada iteracion ejecuta la funcion visitar,
//la cual puede devolver true en caso de que se siga debiendo iterar o false en caso de corte
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);




#endif // COLA_H
