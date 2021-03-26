#!/usr/bin/env python2

import grafo
import csv
import sys
import random
import heapq
import operator
import biblioteca

from collections import deque



grafo2=grafo.Graph()

with open(sys.argv[1], 'r') as file:    #Leo el archivo pasado como primer argumento

    reader = csv.reader(file)
    for row in reader:

        grafo2.agregar_vertice(row[1],row[0])

with open(sys.argv[2],'r') as file:     #Leo el archivo pasado como segundo argumento

    reader = csv.reader(file)
    for row in reader:

        tiempo=int(row[2])
        precio=int(row[3])
        cant_vuelos=int(row[4])
        grafo2.agregar_arista(row[0],row[1],tiempo,precio,cant_vuelos,False)


for line in sys.stdin:

    line = line.rstrip()
    separadas=line.split(" ")

    if(separadas[0]=='listar_operaciones'):

        print("camino_mas")
        print("camino_escalas")
        print("centralidad")
        print("centralidad_aprox")
        print("nueva_aerolinea")
        print("itinerario")

    if(separadas[0]=='camino_mas'):

        oracion=line[11:]
        parseo=oracion.split(",")

        if(parseo[0]=="rapido"): biblioteca.camino_mas_r(grafo2,parseo[1],parseo[2],"rapido")            

        elif(parseo[0]=="barato"): biblioteca.camino_mas_r(grafo2,parseo[1],parseo[2],"barato")           

    if(separadas[0]=='camino_escalas'):

        oracion=line[15:]
        parseo=oracion.split(",")
        biblioteca.camino_con_menos_escalas(grafo2,parseo[0],parseo[1])

    if(separadas[0]=='centralidad_aprox'):

        oracion=line[18:]
        cantidad=int(oracion)
        biblioteca.centralidad_aprox(grafo2,cantidad)

    if(separadas[0]=='centralidad'):

        oracion=line[12:]
        aeropuertos_a_mostrar=int(oracion)
        cent={}
        cent=biblioteca.centralidad_exacta(grafo2,aeropuertos_a_mostrar)
        biblioteca.mostrar_aeropuertos(cent,aeropuertos_a_mostrar)

    if(separadas[0]=='nueva_aerolinea'):

        oracion=line[16:]
        arbol=biblioteca.mst_prim(grafo2)               
        lista_de_listas=biblioteca.generar_l_de_l(arbol)  
        biblioteca.escribir_nueva_aerolinea(oracion,lista_de_listas)     
        print("OK") 

    if(separadas[0]=='itinerario'):

        oracion=line[11:]        
        grafo_ciudades=biblioteca.crear_grafo_ciudades(oracion)       
        resultado=[]
        resultado=biblioteca.orden_topologico(grafo_ciudades)
        biblioteca.mostrar_lista_resultado(resultado)

        for i in range(0,len(resultado)):

            if(i+1==len(resultado)): break

            biblioteca.camino_con_menos_escalas(grafo2,resultado[i],resultado[i+1])


