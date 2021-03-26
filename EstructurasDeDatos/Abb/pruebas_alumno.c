#include "pila.h"
#include "cola.h"
#include "abb.h"
#include "testing.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


int comparar_abb(const char* clave1,const char* clave2){

    return strcmp(clave1,clave2);
}

abb_comparar_clave_t comparacion=&comparar_abb;


static void prueba_crear_abb_vacio()
{
    printf("PRUEBA CREAR ABB VACIO \n");
    abb_t* abb = abb_crear(comparacion,NULL);

    print_test("Prueba abb crear abb vacio", abb);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

    abb_destruir(abb);
}

static void prueba_abb_insertar()
{
    printf("PRUEBA ABB INSERTAR \n");
    abb_t* abb = abb_crear(comparacion,NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";


    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);


    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

    abb_destruir(abb);
}


static void prueba_borrar_sin_hijos()
{
    printf("PRUEBAS BORRAR SIN HIJOS \n");
    abb_t* abb = abb_crear(comparacion,NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";
    char* clave4="z", *valor4="capo";


    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    //print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    //print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);


    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave4) == valor4);

    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es false", !abb_pertenece(abb, clave2));
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}



void prueba_borrar_con_un_hijo(){

    printf("PRUEBAS BORRAR CON UN HIJO \n");
    abb_t* abb = abb_crear(comparacion,NULL);

    char *clave1 = "a", *valor1 = "guau";
    char *clave2 = "b", *valor2 = "miau";
    char *clave3 = "d", *valor3 = "mu"; 
    char *clave4 = "c", *valor4 = "ma";    

    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb la cantidad de elementos es 4", abb_cantidad(abb) == 4);    
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(abb) == 3);

    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb pertenece clave2, es false", !abb_pertenece(abb, clave2));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave4) == valor4);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}    

void prueba_borrar_con_dos_hijos(){

    printf("PRUEBAS BORRAR CON DOS HIJOS \n");

    abb_t* abb = abb_crear(comparacion,NULL);
/*
    char *clave1 = "e", *valor1 = "guau";
    char *clave2 = "a", *valor2 = "miau";
    char *clave3 = "s", *valor3 = "mu"; 
    char *clave4 = "r", *valor4 = "ma";  
    char *clave5 = "q", *valor5 = "me";  



    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
*/


    char *clave1 = "d", *valor1 = "guau";
    char *clave2 = "g", *valor2 = "miau";
    char *clave3 = "m", *valor3 = "mu"; 
    char *clave4 = "e", *valor4 = "ma";  
    char *clave5 = "n", *valor5 = "me";  

    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 5);
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 4);

    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 3);
    print_test("Prueba abb pertenece clave2, es false", !abb_pertenece(abb, clave3));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave4) == valor4);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 2);
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave5) == valor5);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 1);
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);


    
/*
    char *clave1 = "b", *valor1 = "guau";
    char *clave2 = "a", *valor2 = "miau";
    char *clave3 = "c", *valor3 = "mu"; 


    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));

    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);

    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave5) == valor5);
    print_test("Prueba abb pertenece clave2, es false", !abb_pertenece(abb, clave5));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave4) == valor4);
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);

    //print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 1);
*/
    abb_destruir(abb);    
}

static void prueba_abb_reemplazar()
{
    printf("PRUEBA ABB REEMPLAZAR \n");
    abb_t* abb = abb_crear(comparacion,NULL);

    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";


    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

static void prueba_abb_reemplazar_con_destruir()
{
    printf("PRUEBAS ABB REEMPLAZAR CON DESTRUIR \n");
    abb_t* abb = abb_crear(comparacion,free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;


    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));


    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);


    abb_destruir(abb);
}

static void prueba_abb_clave_vacia()
{
    printf("PRUEBA ABB CLAVE VACIA \n");
    abb_t* abb = abb_crear(comparacion,NULL);

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_valor_null()
{
    printf("PRUEBA ABB VALOR NULL \n");
    abb_t* abb = abb_crear(comparacion,NULL);

    char *clave = "", *valor = NULL;


    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
   // print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
//    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

void prueba_avanzar_iterador_externo(){

    printf("PRUEBAS ABB ITERADOR EXTERNO \n");    

    abb_t* abb = abb_crear(comparacion,NULL);

    char *clave1 = "e", *valor1 = "guau";
    char *clave2 = "a", *valor2 = "miau";
    char *clave3 = "s", *valor3 = "mu"; 
    char *clave4 = "r", *valor4 = "ma";  
    char *clave5 = "q", *valor5 = "me"; 

    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));


    abb_iter_t* abb_iter=abb_iter_in_crear(abb);

    printf("CLave del tope deberia ser a y es %s \n",abb_iter_in_ver_actual(abb_iter));
    print_test("Son distintos los punteros",abb_iter_in_ver_actual(abb_iter)!=clave2);
    print_test("Iter no esta al final",!abb_iter_in_al_final(abb_iter));

    print_test("Se pudo avanzar con el iterador",abb_iter_in_avanzar(abb_iter));

    printf("CLave del tope deberia ser e y es %s \n",abb_iter_in_ver_actual(abb_iter));
    print_test("Son distintos los punteros",abb_iter_in_ver_actual(abb_iter)!=clave1);
    print_test("Iter no esta al final",!abb_iter_in_al_final(abb_iter));

    print_test("Se pudo avanzar con el iterador",abb_iter_in_avanzar(abb_iter));

    printf("CLave del tope deberia ser q y es %s \n",abb_iter_in_ver_actual(abb_iter));
    print_test("Son distintos los punteros",abb_iter_in_ver_actual(abb_iter)!=clave5);
    print_test("Iter no esta al final",!abb_iter_in_al_final(abb_iter));

    print_test("Se pudo avanzar con el iterador",abb_iter_in_avanzar(abb_iter));

    printf("CLave del tope deberia ser r y es %s \n",abb_iter_in_ver_actual(abb_iter));
    print_test("Son distintos los punteros",abb_iter_in_ver_actual(abb_iter)!=clave4);
    print_test("Iter no esta al final",!abb_iter_in_al_final(abb_iter));

    print_test("Se pudo avanzar con el iterador",abb_iter_in_avanzar(abb_iter));

    printf("CLave del tope deberia ser s y es %s \n",abb_iter_in_ver_actual(abb_iter));
    print_test("Son distintos los punteros",abb_iter_in_ver_actual(abb_iter)!=clave3);
    print_test("Iter no esta al final",!abb_iter_in_al_final(abb_iter));

    print_test("Se pudo avanzar con el iterador",abb_iter_in_avanzar(abb_iter));

    print_test("Iter esta al final",abb_iter_in_al_final(abb_iter));
    
    abb_iter_in_destruir(abb_iter);
    abb_destruir(abb);
}

bool visitar(const char* clave,void* dato,  void* extra){

    *(int*)extra+=*(int*)dato;
    return true;

}

bool visitar2(const char* clave,void* dato,  void* extra){

    if(*(size_t*) extra>=2)
        return false;
    
    *(size_t*) extra=*(size_t*)extra+1;
    return true;
}

void prueba_abb_iterador_interno(){

    abb_t* abb=abb_crear(comparacion,NULL);

    int valor1=5;
    int valor2=4;
    int valor3=3;
    int valor4=2;
    char* clave1="c";
    char* clave2="a";
    char* clave3="d";
    char* clave4="f";

    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, &valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, &valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, &valor3));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, &valor4)); 
    int suma=0;
    abb_in_order(abb,visitar,&suma);
    print_test("SUma es 14",suma==14);
    size_t contador=0;
    abb_in_order(abb,visitar2,&contador);
    print_test("Contador no supera 2",contador==2);
    abb_destruir(abb);
}   

static void prueba_iterar_abb_vacio()
{
    abb_t* abb = abb_crear(comparacion,NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iter crear iterador abb vacio", iter);
    print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}


void pruebas_abb_alumno(){


    prueba_crear_abb_vacio();
    prueba_abb_insertar();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_con_destruir();
    prueba_abb_clave_vacia();
    prueba_abb_valor_null(); 
    prueba_borrar_sin_hijos();  
    prueba_borrar_con_un_hijo(); 
    prueba_borrar_con_dos_hijos();
    prueba_avanzar_iterador_externo();
    prueba_abb_iterador_interno();
    prueba_iterar_abb_vacio();
    
    
}

    
