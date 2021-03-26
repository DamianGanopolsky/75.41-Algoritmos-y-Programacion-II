#define _POSIX_C_SOURCE 200809L
#include "heap.h"
#include "testing.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef int t_vec[10];




int comparar_heap(const void* clave1,const void* clave2){

    if(*(int*)clave1<*(int*)clave2){

         return -1;
    }

    if(*(int*)clave1>*(int*)clave2) {

        return 1;
    }

    return 0;


}

cmp_func_t comp=&comparar_heap;


static void prueba_crear_heap_vacio()
{
    heap_t* heap = heap_crear(comp);
  //  int* valor1=5;
    //int* valor2=3;

    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap obtener clave A, es NULL, no existe", !heap_ver_max(heap));
    print_test("Prueba heap borrar clave A, es NULL, no existe", !heap_desencolar(heap));

   // print_test("Heap encolar devuelve true",heap_encolar(heap,valor1));
    //print_test("Heap encolar devuelve true",heap_encolar(heap,valor2));
    //print_test("Heap desencolar",heap_desencolar(heap)==valor2);



    

    heap_destruir(heap,NULL);
}


void pruebas_heap_estatico(){

    int valor1=5;
    int valor2=3;
    int valor3=2;
    int valor4=1;
    int valor5=9;

    heap_t* heap=heap_crear(comp);
    
    print_test("El heap creado esta vacio",heap_esta_vacio(heap));

    print_test("Heap cantidad devuelve 0",heap_cantidad(heap)==0);

    print_test("Heap encolar devuelve true",heap_encolar(heap,&valor1));

    print_test("El heap dejo de estar vacio",!heap_esta_vacio(heap));

    print_test("Heap cantidad devuelve 0",heap_cantidad(heap)==1);

   // print_test("Heap maximo devuelve 5",heap_ver_max(heap)==&valor1);

    print_test("Heap encolar devuelve true",heap_encolar(heap,&valor2));

    print_test("Heap cantidad devuelve 0",heap_cantidad(heap)==2);

   // print_test("Heap maximo devuelve 3",heap_ver_max(heap)==&valor2);

    print_test("Heap encolar devuelve true",heap_encolar(heap,&valor3));

    //print_test("Heap maximo devuelve 2",heap_ver_max(heap)==&valor3);

    print_test("Heap encolar devuelve true",heap_encolar(heap,&valor4));

    //print_test("Heap maximo devuelve 1",heap_ver_max(heap)==&valor4);

    print_test("Heap encolar devuelve true",heap_encolar(heap,&valor5));

    print_test("Heap cantidad devuelve 0",heap_cantidad(heap)==5);

    //print_test("Heap maximo devuelve 1",heap_ver_max(heap)==&valor4);

    //print_test("Heap desencolar devuelve a 1",heap_desencolar(heap)==&valor4);

    //print_test("Heap cantidad devuelve 4",heap_cantidad(heap)==4);

    //print_test("Heap ver max devuelve a 2",heap_ver_max(heap)==&valor3);

    //print_test("Heap desencolar devuelve a 2",heap_desencolar(heap)==&valor3);

    heap_destruir(heap,NULL);

}


void pruebas_heap_dinamico(){

    int* valor1=malloc(sizeof(int*));
    int* valor2=malloc(sizeof(int*));

    *valor1=5;
    *valor2=4;

    heap_t* heap=heap_crear(comp);

    printf("PRUEBAS HEAP DINAMICO \n");

    print_test("Heap encolar devuelve true",heap_encolar(heap,valor1));

    print_test("El heap dejo de estar vacio",!heap_esta_vacio(heap));

    print_test("Heap cantidad devuelve 0",heap_cantidad(heap)==1);

    //print_test("Heap maximo devuelve 5",heap_ver_max(heap)==valor1);

    print_test("Heap encolar devuelve true",heap_encolar(heap,valor2));


    heap_destruir(heap,free);
}


void prueba_heapify(){


    void** vector=malloc(sizeof(void*)*5);
    t_vec vec;

    for(int i=0;i<5;i++){

        vec[i]=5-i;
        vector[i]=&vec[i];
        
    }

    heap_t* heap=heap_crear_arr(vector,5,comp);

    //print_test("Heap cantidad devuelve 10",heap_cantidad(heap)==5);

    //print_test("Heap maximo devuelve 1",heap_ver_max(heap)==vector[4]);    
    
    heap_destruir(heap,NULL);

    free(vector);
}

/*
void prueba_heapsort(){

    void** vector=malloc(sizeof(void*)*5);
    t_vec vec;
    vec[0]=3;
    vec[1]=1;
    vec[2]=4;
    vec[3]=2;
    vec[4]=5;
    vector[0]=&vec[0];
    vector[1]=&vec[1];
    vector[2]=&vec[2];
    vector[3]=&vec[3];
    vector[4]=&vec[4];

    for(int i=0;i<5;i++){

        vec[i]=i;
        vector[i]=&vec[i];
        
    } 

    heap_sort(vector,5,comp);

    for(int i=0;i<5;i++){

        printf("Vector i es %i \n",*(int*)vector[i]);
    }
    free(vector);
}    
*/


void pruebas_heap_alumno(){

    pruebas_heap_estatico();
    pruebas_heap_dinamico();
    prueba_heapify();
    prueba_crear_heap_vacio();
   // prueba_heapsort();   

}


