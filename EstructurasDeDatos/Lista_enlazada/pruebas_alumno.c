#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include<stdio.h>
#include <stdlib.h>

typedef int t_vec[1000];

typedef struct syc{
    int suma;
    size_t contador;
} t_syc;

void prueba_apilar_null(){

    printf("PRUEBAS CON NULL \n");
    lista_t* lista=lista_crear();
    print_test("Se pudo enlistar null",lista_insertar_ultimo(lista,NULL));
    lista_destruir(lista,NULL);
}


void pruebas_dinamicas(){

    printf("INICIO PRUEBAS DINAMICAS \n");
    lista_t* lista=lista_crear();
    print_test("Se pudo crear la lista",lista!=NULL);
    print_test("lista esta vacia es verdadero",lista_esta_vacia(lista));
    print_test("Lista borrar primero devuelve false ",!lista_borrar_primero(lista));
    print_test("LIsta ver primero devuelve false",!lista_ver_primero(lista));
    int* p1=malloc(sizeof(int));
    *p1=3;
    int* p2=malloc(sizeof(int));
    *p2=4;
    int* p3=malloc(sizeof(int));
    *p3=5;
    bool ok=true;
    ok&=lista_insertar_ultimo(lista,p1);
    ok&=lista_insertar_ultimo(lista,p2);
    ok&=lista_insertar_ultimo(lista,p3);
    print_test("Se pudieron insertar 3 valores dinamicos correctamente a la lista",ok);
    int* p1_devuelto=lista_borrar_primero(lista);
    int* p2_devuelto=lista_borrar_primero(lista);
    int* p3_devuelto=lista_borrar_primero(lista);
    print_test("El primer elemento enlistado  es el primero que se borra",p1==p1_devuelto);
    print_test("El segundo elemento enlistado es el segundo en borrarse",p2==p2_devuelto);
    print_test("EL tercer elemento enlistado es el tercero en borrarse",p3==p3_devuelto);
    print_test("Se pueden enlistar elementos despues de borrar todos los anteriores",lista_insertar_primero(lista,p1));
    free(p2);
    free(p3);
    lista_destruir(lista, free);
 }

void condiciones_de_borde_estatico(){

    lista_t* lista=lista_crear();
    printf("INICIO PRUEBAS DE CONDICIONES DE BORDE CON VALORES ESTATICOS INSERTANDO ULTIMOS \n");
    print_test("Se pudo crear la lista",lista!=NULL);
    print_test("lista esta vacia es verdadero",lista_esta_vacia(lista));
    print_test("Borrar primero devuelve false ",!lista_borrar_primero(lista));
    print_test("Ver primero devuelve false",!lista_ver_primero(lista));
    int valor1=5;
    int valor2=4;
    int valor3=3;
    bool ok=true;
    ok&=lista_insertar_ultimo(lista,&valor1);
    ok&=lista_insertar_ultimo(lista,&valor2);
    ok&=lista_insertar_ultimo(lista,&valor3);
    print_test("Se pudieron insertar 3 elementos correcamente a la lista",ok);
    int* a =lista_borrar_primero(lista);
    int *b =lista_borrar_primero(lista);
    int* c = lista_borrar_primero(lista);
    print_test("El primer elemento enlistado  es el primero que se borra",&valor1==a);
    print_test("El segundo elemento enlistado es el segundo que se borra",&valor2==b);
    print_test("EL tercer elemento enlistado es el tercero que se borra",&valor3==c);
    print_test("La prueba ver primero es invalida",lista_ver_primero(lista)==NULL);
    print_test("La prueba borrar primero es invalida",lista_borrar_primero(lista)==NULL);
    print_test("Se pueden enlistar elementos despues de borrar todos los anteriores",lista_insertar_ultimo(lista,&valor1));
    printf("PRUEBA DE DESTRUCCION CON LISTA VACIA \n");
    lista_destruir(lista, NULL);
 }

void condiciones_de_borde_estatico_dos(){

    lista_t* lista=lista_crear();
    printf("INICIO PRUEBAS DE CONDICIONES DE BORDE CON VALORES ESTATICOS INSERTANDO PRIMEROS \n");
    print_test("Se pudo crear la lista",lista!=NULL);
    int valor1=5;
    int valor2=4;
    int valor3=3;
    bool ok=true;
    ok&=lista_insertar_primero(lista,&valor1);
    ok&=lista_insertar_primero(lista,&valor2);
    ok&=lista_insertar_primero(lista,&valor3);
    print_test("Se pudieron insertar 3 elementos a la lista correctamente",ok);
    int* a =lista_borrar_primero(lista);
    int *b =lista_borrar_primero(lista);
    int* c = lista_borrar_primero(lista);
    print_test("El tercer elemento enlistado  es el primero que se borra",&valor3==a);
    print_test("El segundo elemento enlistado es el segundo que se borra",&valor2==b);
    print_test("EL primer elemento enlistado es el tercero que se borra",&valor1==c);
    lista_destruir(lista,NULL);
 }

void prueba_de_volumen(){

    printf("INICIO PRUEBAS DE VOLUMEN \n");
    lista_t* lista=lista_crear();
    t_vec vec1;
    bool ok=true;

    for(int i=0;i<1000;i++){
        vec1[i]=i;
        ok&=lista_insertar_ultimo(lista,&vec1[i]); //Si algun elemento no se pudo encolar ok pasa a ser false

}
    print_test("Se pudieron enlistar todos los elementos de la prueba de volumen",ok==true);
    ok=true;

    for(int k=0;k<1000;k++){

        int* j=lista_borrar_primero(lista);
        if(j!=&vec1[k]) //Si algun elemento desencolado no se desencola en el orden correcto, ok pasa a ser false
            ok=false;
}
    print_test("Todos los elementos se enlistar y desenlistaron respetando el orden previsto",ok);
    lista_destruir(lista, NULL);
}


void destruccion_con_null(){
    
    printf("PRUEBAS DE DESTRUCCION DE LISTA CON FUNCION NULL \n");
    lista_t* lista=lista_crear();
    int valor1=5;
    int valor2=4;
    int valor3=3;
    int valor4=2;
    print_test("Enlistar valor 1",lista_insertar_ultimo(lista,&valor1));
    print_test("Enlistar valor 2",lista_insertar_ultimo(lista,&valor2));
    print_test("Enlistar valor 3",lista_insertar_ultimo(lista,&valor3));
    print_test("Enlistar valor 4",lista_insertar_ultimo(lista,&valor4));
    print_test("EL largo es 4",lista_largo(lista)==4);
    print_test("La lista no esta vacia",!lista_esta_vacia(lista));
    print_test("Ver primero es el valor 1",lista_ver_primero(lista)==&valor1);
    lista_destruir(lista,NULL);
}

void destruccion_con_free(){    

    printf("PRUEBA DE DESTRUCCION DE COLA CON FREE \n");
    lista_t* lista=lista_crear();
    int* p1=malloc(sizeof(int));
    *p1=3;
    int* p2=malloc(sizeof(int));
    *p2=4;
    int* p3=malloc(sizeof(int));
    *p3=5;
    bool ok =true;
    ok&=lista_insertar_ultimo(lista,p1);
    ok&=lista_insertar_ultimo(lista,p2);
    ok&=lista_insertar_ultimo(lista,p3);
    print_test("Prueba enlistar 3 punteros",ok);
    lista_iter_t* iter=lista_iter_crear(lista);
    print_test("Se pudo crear el iterador",iter!=NULL);
    print_test("Se pudo avanzar con el iterador",lista_iter_avanzar(iter));
    print_test("Ver primero devuelve el segundo elemento insertado",lista_iter_ver_actual(iter)==p2);
    print_test("LIsta iter al final devuelve false",lista_iter_al_final(iter)==false);
    print_test("Se pudo avanzar con el iterador",lista_iter_avanzar(iter));
    print_test("Se pudo avanzar con el iterador",lista_iter_avanzar(iter));
    print_test("LIsta iter al final devuelve true",lista_iter_al_final(iter)==true);    
    print_test("EL largo es 3",lista_largo(lista)==3);
    lista_destruir(lista,free);
    lista_iter_destruir(iter);
}

void pruebas_insertar_iterador_ext(){
    
    printf("PRUEBAS INSERTANDO ELEMENTOS CON EL ITERADOR EXERNO \n");
    lista_t* lista=lista_crear();
    int* p1=malloc(sizeof(int));
    *p1=3;
    int* p2=malloc(sizeof(int));
    *p2=4;
    int* p3=malloc(sizeof(int));
    *p3=5;
    int* p4=malloc(sizeof(int));
    *p4=3;
    int* p5=malloc(sizeof(int));
    *p5=4;
    print_test("Se pudo insertar p4 correctamente",lista_insertar_ultimo(lista,p4));
    print_test("Se pudo insertar p5 correctamente",lista_insertar_ultimo(lista,p5));
    lista_iter_t* iter=lista_iter_crear(lista);
    print_test("Se pudo insertar p1",lista_iter_insertar(iter,p1));
    print_test("EL primer elemento insertado se encuentra al principio",lista_ver_primero(lista)==p1);
    print_test("Se pudo avanzar con el iterador",lista_iter_avanzar(iter));      
    print_test("Se pudo insertar p2",lista_iter_insertar(iter,p2));
    print_test("Ver actual devuelve el valor deseado",lista_iter_ver_actual(iter)==p2);
    while(!lista_iter_al_final(iter))
        print_test("Se pudo avanzar con el iterador correctamente",lista_iter_avanzar(iter));
    print_test("Se pudo insertar",lista_iter_insertar(iter,p3));
    print_test("Insertar un elemento con el iterador al final hace que sea el ultimo",lista_ver_ultimo(lista)==p3);
    print_test("El largo es 5",lista_largo(lista)==5);
    lista_destruir(lista,free);
    printf("Paso por aca 2 \n");
    lista_iter_destruir(iter);
}


void pruebas_borrar_iterador_ext(){

    printf("PRUEBAS BORRANDO ELEMENTOS CON EL ITERADOR EXERNO \n");
    lista_t* lista=lista_crear();
    int* p1=malloc(sizeof(int));
    *p1=3;
    int* p2=malloc(sizeof(int));
    *p2=4;
    int* p3=malloc(sizeof(int));
    *p3=5;
    int* p4=malloc(sizeof(int));
    *p4=3;
    bool ok=true;
    ok&=lista_insertar_ultimo(lista,p1);
    ok&=lista_insertar_ultimo(lista,p2);
    ok&=lista_insertar_ultimo(lista,p3);
    ok&=lista_insertar_ultimo(lista,p4);
    print_test("Se pudieron insertar 4 valores dinamicos a la lista correctamente",ok);
    lista_iter_t* iter=lista_iter_crear(lista);
    print_test("El elemento borrado es el primer insertado",lista_iter_borrar(iter)==p1);
    print_test("Se pudo avanzar correctamente",lista_iter_avanzar(iter));
    print_test("El elemento borrado es el segundo insertado",lista_iter_borrar(iter)==p3);
    print_test("El elemento borrado es el ultimo",lista_iter_borrar(iter)==p4);
    print_test("El elemento devuelto al borrar es NULL",lista_iter_borrar(iter)==NULL); 
    free(p1);
    free(p3);
    free(p4);      
    lista_destruir(lista,free);
    lista_iter_destruir(iter);   
    
}

//Prueba con funcion sin corte
bool visitar(void* dato,  void* extra){

    *(int*)extra+=*(int*)dato;
    return true;

}
//Prueba con funcion con corte
bool visitar2(void* dato,  void* extra){

    if(*(size_t*) extra>=2)
        return false;
    
    *(size_t*) extra=*(size_t*)extra+1;
    return true;
}


    

void pruebas_iterador_interno(){

    printf("PRUEBAS ITERADOR INTERNO \n");    
    lista_t* lista=lista_crear();
    int valor1=5;
    int valor2=4;
    int valor3=3;
    int valor4=2;
    bool ok=true;
    ok&=lista_insertar_ultimo(lista,&valor1);
    ok&=lista_insertar_ultimo(lista,&valor2);
    ok&=lista_insertar_ultimo(lista,&valor3);
    ok&=lista_insertar_ultimo(lista,&valor4);
    print_test("Se pudieron insertar 4 elementos a la lista correctamente",ok);
    int suma=0;
    lista_iterar(lista,visitar,&suma);
    print_test("Suma es 14",suma==14);
    size_t contador=0;
    lista_iterar(lista,visitar2,&contador);
    print_test("COntador es 2",contador==2);
    lista_destruir(lista,NULL);
    
}

    

void pruebas_lista_alumno(){

    condiciones_de_borde_estatico();    
    pruebas_dinamicas();
    prueba_de_volumen();
    destruccion_con_null();
    destruccion_con_free();
    pruebas_insertar_iterador_ext();
    pruebas_borrar_iterador_ext();
    pruebas_iterador_interno();
    prueba_apilar_null();
    condiciones_de_borde_estatico_dos();

}
