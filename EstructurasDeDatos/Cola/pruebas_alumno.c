#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include<stdio.h>
#include <stdlib.h>

typedef int t_vec[1000];

void prueba_apilar_null(){
    printf("PRUEBAS CON NULL \n");
    cola_t* cola=cola_crear();
    print_test("Se pudo encolar null",cola_encolar(cola,NULL));
    cola_destruir(cola,NULL);
}


void pruebas_dinamicas(){
    printf("INICIO PRUEBAS DINAMICAS \n");
    cola_t* cola=cola_crear();
    print_test("Se pudo crear la cola",cola!=NULL);
    print_test("cola esta vacia es verdadero",cola_esta_vacia(cola));
    print_test("Desencolar devuelve false ",!cola_desencolar(cola));
    print_test("Ver primero devuelve false",!cola_ver_primero(cola));
    int* p1=malloc(sizeof(int));
    *p1=3;
    int* p2=malloc(sizeof(int));
    *p2=4;
    int* p3=malloc(sizeof(int));
    *p3=5;
    cola_encolar(cola,p1);
    cola_encolar(cola,p2);
    cola_encolar(cola,p3);
    int* p1_devuelto=cola_desencolar(cola);
    int* p2_devuelto=cola_desencolar(cola);
    int* p3_devuelto=cola_desencolar(cola);
    print_test("El primer elemento encolado  es el primero que se desencola",p1==p1_devuelto);
    print_test("El segundo elemento encolado es el segundo en desencolarse",p2==p2_devuelto);
    print_test("EL tercer elemento encolado es el tercero en desencolarse",p3==p3_devuelto);
    print_test("Se pueden encolar elementos despues de desencolar todos los anteriores",cola_encolar(cola,p1));
    free(p2);
    free(p3);
    cola_destruir(cola, free);
 }

void condiciones_de_borde_estatico(){
    cola_t* cola=cola_crear();
    printf("INICIO PRUEBAS DE CONDICIONES DE BORDE CON VALORES ESTATICOS \n");
    print_test("Se pudo crear la cola",cola!=NULL);
    print_test("cola esta vacia es verdadero",cola_esta_vacia(cola));
    print_test("Desencolar devuelve false ",!cola_desencolar(cola));
    print_test("Ver primero devuelve false",!cola_ver_primero(cola));
    int valor1=5;
    int valor2=4;
    int valor3=3;
    cola_encolar(cola,&valor1);
    cola_encolar(cola,&valor2);
    cola_encolar(cola,&valor3);
    int* a =cola_desencolar(cola);
    int *b =cola_desencolar(cola);
    int* c = cola_desencolar(cola);
    print_test("El primer elemento encolado  es el primero que se desencola",&valor1==a);
    print_test("El segundo elemento encolado es el segundo en desencolarse",&valor2==b);
    print_test("EL tercer elemento encolado es el tercero en desencolarse",&valor3==c);
    print_test("La prueba ver primero es invalida",cola_ver_primero(cola)==NULL);
    print_test("La prueba desencolar es invalida",cola_desencolar(cola)==NULL);
    print_test("Se pueden encolar elementos despues de desencolar todos los anteriores",cola_encolar(cola,&valor1));
    printf("PRUEBA DE DESTRUCCION CON COLA VACIA \n");
    cola_destruir(cola, NULL);
 }

void encolar_vector_estatico(){
    printf("PRUEBAS CON VECTOR ESTATICO \n");
    int arreglo[2] = {1, 2};
    cola_t *cola = cola_crear();

    print_test("Se pudo encolar el primer elemento",cola_encolar(cola, &arreglo[0]));
    print_test("Se pudo encolar el segundo elemento",cola_encolar(cola, &arreglo[1]));
    cola_destruir(cola, NULL);
}

void prueba_de_volumen(){
    printf("INICIO PRUEBAS DE VOLUMEN \n");
    cola_t* cola=cola_crear();
    t_vec vec1;
    bool ok=true;

    for(int i=0;i<1000;i++){
        vec1[i]=i;
        ok&=cola_encolar(cola,&vec1[i]); //Si algun elemento no se pudo encolar ok pasa a ser false

}
    print_test("Se pudieron encolar todos los elementos de la prueba de volumen",ok==true);
    ok=true;

    for(int k=0;k<1000;k++){

        int* j=cola_desencolar(cola);
        if(j!=&vec1[k]) //Si algun elemento desencolado no se desencola en el orden correcto, ok pasa a ser false
            ok=false;
}
    print_test("Todos los elementos se desencolaron y encolaron respentando el orden de la cola",ok);
    cola_destruir(cola, NULL);
}

void destruccion_con_null(){
    
    printf("PRUEBAS DE DESTRUCCION DE COLA CON FUNCION NULL \n");
    cola_t* cola=cola_crear();
    int valor1=5;
    int valor2=4;
    int valor3=3;
    int valor4=2;
    print_test("Encolar valor 1",cola_encolar(cola,&valor1));
    print_test("Encolar valor 2",cola_encolar(cola,&valor2));
    print_test("Encolar valor 3",cola_encolar(cola,&valor3));
    print_test("Encolar valor 4",cola_encolar(cola,&valor4));
    print_test("La cola no esta vacia",!cola_esta_vacia(cola));
    print_test("Ver primero es el valor 1",cola_ver_primero(cola)==&valor1);
    cola_destruir(cola,NULL);
}

void destruccion_con_free(){    

    printf("PRUEBA DE DESTRUCCION DE COLA CON FREE \n");
    cola_t* cola=cola_crear();
    int* p1=malloc(sizeof(int));
    *p1=3;
    int* p2=malloc(sizeof(int));
    *p2=4;
    int* p3=malloc(sizeof(int));
    *p3=5;
    bool ok =true;
    ok&=cola_encolar(cola,p1);
    ok&=cola_encolar(cola,p2);
    ok&=cola_encolar(cola,p3);
    print_test("Prueba encolar 3 punteros",ok);
    cola_destruir(cola,free);
}

void pruebas_cola_alumno(){

    encolar_vector_estatico();
    condiciones_de_borde_estatico();
    pruebas_dinamicas();
    prueba_apilar_null();
    prueba_de_volumen();
    destruccion_con_null();
    destruccion_con_free();

}


