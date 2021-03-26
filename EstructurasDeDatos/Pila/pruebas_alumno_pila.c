#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include<stdio.h>
#include <stdlib.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
typedef int t_vec[1000];

typedef struct estructura{

    int dato;
} ab_t;


void prueba_con_estructura(){

    ab_t* ab=malloc(sizeof(ab_t));
    ab->dato=5;
    pila_t* pila=pila_crear();
    print_test("Se pudo apilar el valor 1 ",pila_apilar(pila,&ab->dato));
    int *a =pila_desapilar(pila);
    print_test("Tercer elemento apilado es el primero en desapilar, el elemento desapilado fue el correcto",&ab->dato==a);
    pila_destruir(pila);
    free(ab);
}
    

void prueba_apilar_null(){
    pila_t* pila=pila_crear();
    print_test("Se pudo apilar null",pila_apilar(pila,NULL));
    pila_destruir(pila);
}



void condiciones_de_borde(){
    
    pila_t* pila=pila_crear();
    print_test("Se pudo crear la pila",pila!=NULL);
    print_test("pila esta vacia es verdadero",pila_esta_vacia(pila));
    print_test("Desapilar devuelve false ",!pila_desapilar(pila));
    print_test("Ver tope devuelve false",!pila_ver_tope(pila));
    int valor1=5;
    int valor2=4;
    int valor3=3;
    print_test("Se pudo apilar el valor 1 ",pila_apilar(pila,&valor1));
    print_test("Se pudo apilar el valor 2 ",pila_apilar(pila,&valor2));
    print_test("Se pudo apilar el valor 3 ",pila_apilar(pila,&valor3));
    int *a =pila_desapilar(pila);
    int* b=pila_desapilar(pila);
    int *c=pila_desapilar(pila);
    print_test("La prueba ver tope es invalida",pila_ver_tope(pila)==NULL);
    print_test("La prueba desapilar es invalida",pila_desapilar(pila)==NULL);
    print_test("Se pueden apilar elementos despues de desapilar todos los anteriores",pila_apilar(pila,&valor1));
    print_test("Primer elemento apilado es el ultimo en desapilar, el elemento desapilado fue el correcto",&valor1==c);
    print_test("Segundo elemento apilado es el anteultimo en desapilar, el elemento desapilado fue el correcto",&valor2==b);
    print_test("Tercer elemento apilado es el primero en desapilar, el elemento desapilado fue el correcto",&valor3==a);

    pila_destruir(pila);

 }   


bool prueba_de_volumen(){
    pila_t* pila=pila_crear();
    t_vec vec1;

    for(int i=0;i<1000;i++){
        vec1[i]=i;
        pila_apilar(pila,&vec1[i]);
}

    for(int k=999;k>=0;k--){
        int *j =pila_desapilar(pila);

        if(&vec1[k]!=j) //Verifica si el elemento desapilado es el correcto para cada caso
            return false;
        

}

    pila_destruir(pila);
    return true;

}

void pruebas_pila_alumno() {

    prueba_con_estructura();

    prueba_apilar_null();
    condiciones_de_borde();
    print_test("El elemento desapilado fue el correcto en todos los casos de la prueba de volumen:",prueba_de_volumen()==true);

}


