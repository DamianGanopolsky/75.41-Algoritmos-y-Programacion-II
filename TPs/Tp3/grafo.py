import random



class Graph(object):

    def __init__(self, graph_dict=None):

        if graph_dict == None:
            graph_dict = {}
        self.__graph_dict = graph_dict
        self.largo=0

    def vertices(self):

        return list(self.__graph_dict.keys())

    def agregar_vertice(self, vertice,ciudad):

        if vertice not in self.__graph_dict:
            self.largo+=1
            self.__graph_dict[vertice] = []
            self.__graph_dict[vertice].append(ciudad)

    def sacar_vertice(self,vertice):

        if vertice in self.__graph_dict:

            self.largo-=1
            self.__graph_dict.pop(vertice)

    def sacar_arista(self,v1,v2,e):

        temp1=[v2,e]
        self.__graph_dict[v1].remove(temp1)

    def ver_vertice(self,vertice):

        if vertice in self.__graph_dict:

            print("EL vertice esta y es ",vertice)

    def obtener_vertice_random(self):

        return random.choice(list(self.__graph_dict))

    
    def obtener_adyacentes(self,vertice):

        if vertice in self.__graph_dict:

            return list(self.__graph_dict[vertice])

    def estan_unidos(self,v1,v2):

        for vertice in self.__graph_dict[v1] :

            if (vertice[0]==v2):

                tupla=[v1,v2,vertice[1],vertice[2],vertice[3]]
                return tupla       


    def agregar_arista(self,v1, v2, tiempo,precio,cant_vuelos,dirigido):

      if v1 not in self.__graph_dict:
        print("vertice ", v1, " no existe.")

      elif v2 not in self.__graph_dict:
        print("vertice ", v2, " no existe.")

      else:
        temp1 = [v2, tiempo, precio, cant_vuelos]
        
        self.__graph_dict[v1].append(temp1)

        if(dirigido==False):
            temp2= [v1,tiempo,precio,cant_vuelos]
            self.__graph_dict[v2].append(temp2)

    def __generate_aristas(self):

        aristas = []
        for vertice in self.__graph_dict:
            for neighbour in self.__graph_dict[vertice]:
                if {neighbour, vertice} not in aristas:
                    aristas.append({vertice, neighbour})
        return aristas

    def __str__(self):
        res = "vertices: "
        for k in self.__graph_dict:
            res += str(k) + " "
        res += "\naristas: "
        for arista in self.__generate_aristas():
            res += str(arista) + " "
        return res

