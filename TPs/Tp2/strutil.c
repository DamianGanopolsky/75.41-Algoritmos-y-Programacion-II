#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stddef.h>
#include <stdlib.h>

typedef size_t t_vec[100000]; 

size_t contar_caracteres(char** strv,size_t* caracteres,t_vec vec){            // Funcion auxiliar del join 

    int i=0;
    size_t contador=0;
    size_t caracteres_totales=0;

    while(strv[i]!=NULL){

        *caracteres=*caracteres+strlen(strv[i]);
        caracteres_totales=caracteres_totales+strlen(strv[i]);
        if(contador>=1) caracteres_totales++;
        contador++;
        vec[i]=*caracteres;
        i++;
    }  

    return caracteres_totales;
}  

char* cadena_vacia(){
    
    char* cadena_a_devolver=strdup("");
    return cadena_a_devolver;
}
    


void free_strv(char *strv[]){

    size_t i=0;

    if(strv==NULL)
        return;

    while(strv[i]!=NULL){

        free(strv[i]);
        i++;
    }

    free(strv);
}


char* substr(const char *str, size_t n){

    int i=0;
    char* devolucion=malloc(sizeof(char)*(n+1));

    while((i<n)&&(i<strlen(str))){

        devolucion[i]=str[i];
        i++;
    }
    devolucion[i]='\0';
    return devolucion;
}


char** split(const char *str, char sep){

    size_t cont2=0;
    size_t cont=0;

    for(int j=0;j<strlen(str);j++){
        
        if(str[j]==sep) cont2++;                
   
    }

    char** strv=malloc(sizeof(char*)*(cont2+2));    
    char cadena[100]="";
    int j=0;

    if(strlen(str)==0){

        strv[0]=strdup(cadena);
        strv[1]=NULL;
    }

    if((strlen(str)==1)&&(str[0]==sep)){

        strv[0]=strdup(cadena);
        strv[1]=strdup(cadena);
        strv[2]=NULL;
        return strv;
    }

    for(int i=0;i<strlen(str);i++){

        if(str[i]==sep){
            cadena[j]='\0';
            strv[cont]=strdup(cadena);
            cont++;
            strcpy(cadena,"\0");
            j=0;

            if(i+1>=strlen(str)){

                strcpy(cadena,"\0");
                cadena[j]='\0'; 
                strv[cont]=strdup(cadena);
                cont++;
                strv[cont]=NULL;
            }                              
            continue;
        }

        cadena[j]=str[i];
        j++;
        if(i+1==strlen(str)){

            cadena[j]='\0';
            strv[cont]=strdup(cadena);
            cont++;
            strv[cont]=NULL;

        }
    }
    return strv;
}


char* join(char **strv, char sep){

    size_t caracteres=0;
    size_t cont2=0;
    int i=0;
    t_vec vec;

    if(strv==NULL) return cadena_vacia();

    size_t caracteres_totales=contar_caracteres(strv,&caracteres,vec);

    if(caracteres_totales==0) return cadena_vacia();

    char* cadena_a_devolver=malloc(sizeof(char)*(caracteres_totales+1));
    char* separador=malloc(sizeof(char)*2);   
    char* puntero_a_final=cadena_a_devolver;    
    *separador=sep;

    if(*separador!='\0') *(separador+1)='\0';      

    while(strv[i]!=NULL){

        strcpy(puntero_a_final,strv[i]);
        if(*separador!='\0') puntero_a_final=cadena_a_devolver+vec[i]+cont2;
        else puntero_a_final=cadena_a_devolver+vec[i];    
        cont2++;   
        i++;  

        if(strv[i]==NULL) break;
            
        strcpy(puntero_a_final,separador);

        if(*separador!='\0') puntero_a_final=puntero_a_final+1;        
        
    }
    free(separador);

    return cadena_a_devolver;
}
