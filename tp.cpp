
// Trabajo practico de la escuela de verano algoritmos.

#include<iostream>
#include<stdlib.h>
#include<string.h>

using namespace std;

// 1- Declarar el campo de la informacion del Nodo.

struct tipoInfo
{
    int ID_Accesorio;
    int cantidad;
};

// 2- Declarar struct Nodo()

struct Nodo
{
    tipoInfo info;
    Nodo* sgte;
};

// 3- Declarar struct registro de modelos.

struct registroModelos
{
    int ID_modelo;
    char descripcion[100+1];
    float precio_base;
    char temporada;
    Nodo* ListaDeCompon = NULL;
};

// 4- Declarar vector de modelos.

registroModelos vectorModelos[50];

// Los puntos 1 al 4 son los necesarios para declarar las estructuras del primero de los vectores.

// 5- Declarar struct tipoInfo de proveedores.

struct tipoInfoProveedores
{
    int ID;
    char nombre[50];
    float valor_unitario;
};

// 6- Declarar struct Nodo de proveedores.

struct NodoProveedores
{
    tipoInfoProveedores info;
    NodoProveedores* sgte;
};

struct componentes 
{
    int ID;
    char descripcion[100+1];
    NodoProveedores* listaProveedores;
    int stock;
};

componentes vectorComponentes[1000];

struct pedido
{
    int ID_Pedido;
    int ID_Linea;
    int ID_Modelo;
    int Cantidad;
    float costo;
};

// Resolucion estrategica del problema:
// 1- Abrir archivo

int main()
{
    system("PAUSE");
    return 0;
}
