import grafo
import csv
import sys
import random
import heapq
import operator
from collections import deque


#Muestra los aeropuertos si no tiene un rango predefinido
def mostrar_recorrido_en_orden(padres,vertice_actual):   

    padres_cola=deque()                                                         
    while(vertice_actual!=None):                         

        padres_cola.append(vertice_actual)
        vertice_actual=padres[vertice_actual]


    while(padres_cola):
        
        v=padres_cola.pop()
        print v,

        if(padres_cola):

            print "->",
    print ""


#Muestra la cantidad de aeropuertos que es pasada como parametro, por "aeropuertos_a_mostrar"
def mostrar_aeropuertos(centr,aeropuertos_a_mostrar):    

    ord_ver=sorted(centr.items(), key=operator.itemgetter(1),reverse=True)

    for i in range(0,aeropuertos_a_mostrar):

        oracion=str(ord_ver[i])
        separadas=oracion.split("'")
        sys.stdout.write(separadas[1])

        if(i+1==aeropuertos_a_mostrar):

            continue

        sys.stdout.write(", ")

    print ""

#Muestra los elementos de la lista resultado con una coma de por medio
def mostrar_lista_resultado(resultado):             

    cadena=str(resultado)
    parseo=cadena.split("'")

    for i in range(len(parseo)):

        if((parseo[i]=="[") or (parseo[i]==", ") or (parseo[i]=="]")): continue
            
        sys.stdout.write(parseo[i])

        if(i+2==len(parseo)): continue
                       
        sys.stdout.write(", ")

    print("")


#Genera un vertice aleatorio ponderando el peso de las aristas   
def vertice_aleatorio(pesos):     

    total = sum(pesos.values())
    rand = random.uniform(0, total)
    acum = 0
    for vertice, peso_arista in pesos.items():

        if acum + peso_arista >= rand: return vertice           

        acum += peso_arista


#Ordena todos los vertices de mayor a menor en un diccionario
def vertices_ordenados(grafo,distancias):   

    vertices_ord=sorted(distancias.items(), key=operator.itemgetter(1),reverse=True)
    
    return vertices_ord


#Genera una lista de listas, de modo que se pueda usar en el comando nueva_aerolinea para escribir el archivo
def generar_l_de_l(arbol):  

    agregados={} 
    lista_de_listas=[] 
        
    for v in arbol.vertices():
    
        cont=0

        for w in arbol.obtener_adyacentes(v):

            if(cont==0):

                cont=cont+1
                continue
                           
            tupla=[v,w[0]]
            invertida=[w[0],v]
            invertida2=tuple(invertida)
            tupla2=tuple(tupla)

            if invertida2 not in agregados:

                agregados[tupla2]=True
                lista_a_escribir=[w[0],v,w[1],w[2],w[3]]
                lista_de_listas.append(lista_a_escribir)

    return lista_de_listas


def escribir_nueva_aerolinea(oracion,lista_de_listas):    #Escribe en un nuevo archivo, la nueva aerolinea

    with open(oracion,'wb') as csv_file:

        writer = csv.writer(csv_file)

        for elemento in lista_de_listas:

            elemento2=list(elemento)
            writer.writerow(elemento)

#Crea un grafo con las ciudades pasadas en el parametro "oracion", para luego ser usadas en el orden topo.
def crear_grafo_ciudades(oracion):     

    diccionario={}

    with open(oracion,'r') as file:

        cont=0
        reader = csv.reader(file,delimiter=',')
        grafo_ciudades=grafo.Graph()

        for row in reader:
 
            cont=cont+1   
            cadena=str(row)
            ciudades=cadena.split("'") 
            i=0       

            if(cont==1):

                for ciudad in ciudades:                       

                    if((ciudad==', ')or(ciudad==']')or(ciudad=='[')): continue                       

                    grafo_ciudades.agregar_vertice(ciudad,"nada")
                    diccionario[ciudad]=0                       

                continue

            grafo_ciudades.agregar_arista(ciudades[1],ciudades[3],0,0,0,True)

    return grafo_ciudades



def djkstra(grafo,origen,destino,modo):

    dist={}
    padre={}
    
    for v in grafo.vertices():
        dist[v]=999999

    dist[origen]=0
    padre[origen]=None
    heap=[]
    tupla=[dist[origen],origen]
    heap.append(tupla)
    heapq.heapify(heap)

    while heap:

        v=heapq.heappop(heap)
        cont=0

        for w in grafo.obtener_adyacentes(v[1]):
            
            if(cont==0):
                cont=cont+1                
                continue

            cont2=0

            if(modo=="rapido"): peso_actual=w[1]

            if(modo=="barato"): peso_actual=w[2]

            if dist[v[1]]+peso_actual<dist[w[0]]:

                dist[w[0]]=dist[v[1]]+peso_actual
                padre[w[0]]=v[1]
                tupla=[dist[w[0]],w[0]]
                heapq.heappush(heap,tupla)

    minimo=999999
    return dist,padre



def camino_con_menos_escalas(grafo2,origen,destino):   #Es ejecutado por el comando camino_escalas

    visitados={}
    padres={}
    orden={}
    queue=deque()
    v=grafo2.obtener_vertice_random()

    for v in grafo2.vertices():

        for w in grafo2.obtener_adyacentes(v):

            if(w==origen):

                padres[v]=None
                orden[v]=0
                visitados[v]=True
                queue.appendleft(v)

    while(queue):

        v=queue.pop()
        contador=0

        for w in grafo2.obtener_adyacentes(v):

            if(contador==0):

                contador+=1
                continue
                
            vertice_actual=w[0]

            if (vertice_actual not in visitados):

                visitados[vertice_actual]=True
                queue.appendleft(vertice_actual)
                padres[vertice_actual]=v
                orden[vertice_actual]=orden[v]+1

            else:

                if orden[vertice_actual] > orden[v]+1:    

                    orden[vertice_actual]=orden[v]+1
                    padres[vertice_actual]=v

    minimo=99

    for v in grafo2.vertices():

        for w in grafo2.obtener_adyacentes(v):

            if(w==destino):

                if(orden[v]<minimo):
                    
                    aeropuerto_del_destino=v
                    minimo=orden[v]

    vertice_actual=aeropuerto_del_destino

    mostrar_recorrido_en_orden(padres,vertice_actual)


 #Devuelve un tipo de camino minimo usado en Betweenness Centrality(tiene en cuenta las frecuencias de los vuelos)
def camino_minimo(grafo2,origen):   

    dist={}
    padre={}
    
    for v in grafo2.vertices():
        dist[v]=999999

    dist[origen]=0
    padre[origen]=None
    heap=[]
    tupla=[dist[origen],origen]
    heap.append(tupla)
    heapq.heapify(heap)

    while heap:

        v=heapq.heappop(heap)
        cont=0

        for w in grafo2.obtener_adyacentes(v[1]):
            
            if(cont==0):
                cont=cont+1
                continue

            conversion=10000000/w[3]

            if dist[v[1]]+conversion<dist[w[0]]:

                dist[w[0]]=dist[v[1]]+conversion
                padre[w[0]]=v[1]
                tupla=[dist[w[0]],w[0]]
                heapq.heappush(heap,tupla)

    return padre,dist



def mst_prim(grafo2):                     #Genera un arbol de tendido minimo

    vertice=grafo2.obtener_vertice_random()
    visitados={}
    visitados[vertice]=True
    heap=[]    
    heapq.heapify(heap)    
    cont=0

    for w in grafo2.obtener_adyacentes(vertice):

        if cont==0:

            cont=cont+1
            continue

        tupla=[w[2],vertice,w[0],w[1],w[3]]
        heapq.heappush(heap,tupla)
        visitados[vertice]=True

    arbol=grafo.Graph()

    for v in grafo2.vertices():

        cont=0
        for w in grafo2.obtener_adyacentes(v):

            if(cont==0):

                arbol.agregar_vertice(v,w)

    while heap:

        tupla=heapq.heappop(heap)
        vertice_desencolado=tupla[2]


        if(tupla[2] in visitados):

            continue

        arbol.agregar_arista(tupla[1],tupla[2],tupla[3],tupla[0],tupla[4],False)

        visitados[tupla[2]]=True
        cont=0

        for x in grafo2.obtener_adyacentes(vertice_desencolado):

            
            if cont==0:
    
                cont=cont+1
                continue
            
            tupla=[x[2],vertice_desencolado,x[0],x[1],x[3]]
            heapq.heappush(heap,tupla)

    return arbol
               
    

def orden_topologico(grafo_ciudades):

    grado={}

    for v in grafo_ciudades.vertices():

        grado[v]=0

    for v in grafo_ciudades.vertices():

        cont=0

        for w in grafo_ciudades.obtener_adyacentes(v):

            if(cont==0):
                cont=cont+1
                continue

            ciudad_adyacente=w[0]
            grado[ciudad_adyacente]=grado[ciudad_adyacente]+1

    cola=deque()

    for v in grafo_ciudades.vertices():

        if (grado[v]==0):

            cola.append(v)

    resultado=[]

    while cola:

        v=cola.pop()
        resultado.append(v)
        cont=0

        for w in grafo_ciudades.obtener_adyacentes(v):            

            if(cont==0):
                cont=cont+1
                continue
            
            ciudad_adyacente=w[0]

            grado[ciudad_adyacente]=grado[ciudad_adyacente]-1
            if(grado[ciudad_adyacente]==0):

                cola.append(ciudad_adyacente)

    return resultado



def centralidad_exacta(grafo2,cant_a_mostrar):

    cent={}

    for v in grafo2.vertices(): cent[v]=0

    for v in grafo2.vertices():

        padre,dist=camino_minimo(grafo2,v)      
        cent_aux={}
        del padre[v]    
        del dist[v]

        for w in grafo2.vertices():

            cent_aux[w]=0

        vertices_ord=vertices_ordenados(grafo,dist)

        for clave,valor in vertices_ord:

            cent_aux[padre[clave]] += 1+ cent_aux[clave]

        for w in grafo2.vertices():

            if w==v: continue

            cent[w] += cent_aux[w]

    return cent
        
      

def centralidad_aprox(grafo2,cantidad):

    
    k=10
    l=100
    cont=0    
    veces={}

    for v in grafo2.vertices():

        veces[v]=0

    for i in range(k):

        v=grafo2.obtener_vertice_random()

        for j in range(l):

            pesos_dic={}
            cont=0

            for w in grafo2.obtener_adyacentes(v):

                if(cont==0):
                    cont=cont+1
                    continue            

                pesos_dic[w[0]]=w[3]

            v=vertice_aleatorio(pesos_dic)
            veces[v]=veces[v]+1

    mostrar_aeropuertos(veces,cantidad)


#Ejecutado por el comando camino_mas , se le paso por parametro si es mas rapido o mas barato
def camino_mas_r(grafo,origen,destino,modo):            

    minimo=999999
    padres_final={}
    dist_final={}
    aeropuerto_de_destino="Nulo"

    for v in grafo.vertices():  #Entro a los aeropuertos del grafo

        cont=0

        for w in grafo.obtener_adyacentes(v):

            if(cont==0):   #Entro a la ciudad del aeropuerto

                cont=cont+1

                if(w==origen):  #SI la ciudad es el origen

                    if (modo=="barato"): dist,padre=djkstra(grafo,v,destino,"barato")                          
        
                    if(modo=="rapido"): dist,padre=djkstra(grafo,v,destino,"rapido")                       

                    for clave,valor in dist.items():

                        cont2=0
                            
                        for w in grafo.obtener_adyacentes(clave):
                    
                            if(cont2==0):
                        
                                if(w==destino):

                                    if(valor<minimo):
                                        aeropuerto_de_destino=clave
                                        minimo=valor
                                        dist_final=dist
                                        padres_final=padre
                                        
                                    
                                cont2=cont2+1
                                break

                cont=cont+1
                break        

    mostrar_recorrido_en_orden(padres_final,aeropuerto_de_destino)
    
