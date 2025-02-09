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

struct nodoModelos
{
    tipoInfo info;
    nodoModelos* sgte;
};

// 3- Declarar struct registro de modelos.

struct RegistroModelos
{
    int ID_modelo;
    char descripcion[101];
    float precio_base;
    string temporada;
    nodoModelos* listaDeComponentes;
};

// 4- Declarar vector de modelos.

RegistroModelos vectorModelos[50];

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

struct Componentes 
{
    int ID;
    char descripcion[101];
    NodoProveedores* listaProveedores;
    int stock;
};

Componentes vectorComponentes[1000];

struct Pedido
{
    int ID_pedido;
    int ID_linea;
    int ID_modelo;
    int cantidad;
    float costo;
};

void agregarProveedorAComponente(Componentes &componente, int ID, const char* nombre, float valor_unitario){
  NodoProveedores* nuevoProveedor = new NodoProveedores;
  nuevoProveedor->info.ID = ID;
  strcpy(nuevoProveedor->info.nombre, nombre);
  nuevoProveedor->info.valor_unitario = valor_unitario;
  nuevoProveedor->sgte = componente.listaProveedores;
  componente.listaProveedores = nuevoProveedor;
}

void cargarComponentes(){
  string nombresComponentes[] = {
        "Suela de goma", "Cordones resistentes", "Plantilla acolchada", "Forro transpirable", "Refuerzo de talón",
        "Cámara de aire", "Tejido impermeable", "Sistema de ajuste rápido", "Entresuela EVA", "Refuerzo lateral",
        "Cojín de impacto", "Placa de carbono", "Diseño ergonómico", "Malla transpirable", "Refuerzo en puntera",
        "Sistema de amortiguación", "Estructura de soporte", "Cuero sintético", "Espuma de memoria", "Costura reforzada"
  };

  string nombresProveedores[] = {"Proveedor A", "Proveedor B", "Proveedor C"};
  
  for(int i=0; i<10; i++){
    vectorComponentes[i].ID = i+1;
    strcpy(vectorComponentes[i].descripcion, nombresComponentes[i%20].c_str());
    vectorComponentes[i].listaProveedores = nullptr; 
    vectorComponentes[i].stock = rand() % 500 + 50;

    for(int j=0; j<3; j++){
      agregarProveedorAComponente(vectorComponentes[i], j+1, nombresProveedores[j].c_str(), ((rand()%5000+500) / 100.0));
    }
  }
}

void mostrarComponentes(){
  for(int i=0; i<10; i++){
    cout<< "ID: "<< vectorComponentes[i].ID<< endl;
    cout<< "Componente: "<< vectorComponentes[i].descripcion<< endl;
    cout<< "Stock: "<< vectorComponentes[i].stock<< endl;
    cout<< "Proveedores: "<< endl;
    NodoProveedores* temp = vectorComponentes[i].listaProveedores;
    while(temp){
      cout<< " - "<< temp->info.nombre<< " ( Valor: $"<< temp->info.valor_unitario<< " )"<< endl;
      temp = temp->sgte;
    }
    cout<< "-- o --"<< endl;
  }
}

void agregarComponenteAModelo(RegistroModelos &modelo, int ID_Componente, int cantidad){
  nodoModelos* nuevoNodo = new nodoModelos;
  nuevoNodo->info.ID_Accesorio = ID_Componente;
  nuevoNodo->info.cantidad = cantidad;
  nuevoNodo->sgte = modelo.listaDeComponentes;
  modelo.listaDeComponentes = nuevoNodo;
}

void cargarModelos() {
    string nombres[] = {
        "Air Max 2025", "Classic Leather", "Sport Pro X", "Zeta Runner", "Urban Pulse", 
        "Aero Glide", "Trail Blazer", "Skyline Boost", "Velocity Grip", "Storm Breaker",
        "Hyperflex Alpha", "Momentum Edge", "Eco Stepper", "Fusion X", "Gravity Ride",
        "Stratus Flow", "Wave Runner", "Titan Core", "Zenith Trek", "Quantum Dash",
        "Nova Impact", "Epic Horizon", "Terra Stride", "Blizzard Force", "Aqua Storm",
        "Rapid Flux", "Nimbus Drift", "Inferno Sprint", "Shadow Pulse", "Eclipse Aero",
        "Glacier Trek", "Solar Shift", "Thunder Ace", "Cosmo Sprint", "Vortex Glide",
        "Nebula Runner", "Canyon Racer", "Falcon Drive", "Sonic Surge", "Stellar Drift",
        "Tornado Max", "Astro Pulse", "Aurora Blaze", "Comet Sprint", "Phantom Trek",
        "Echo Stride", "Supernova Glide", "Pioneer Dash", "Horizon Edge", "Hyper Drive"
    };
    
    string temporadas[] = {"verano", "invierno"};
    
    for (int i = 0; i < 5; i++) {
        vectorModelos[i].ID_modelo = i + 1;
        strcpy(vectorModelos[i].descripcion, nombres[i].c_str());
        vectorModelos[i].precio_base = (rand() % 15000 + 5000) / 100.0; 
        vectorModelos[i].temporada = temporadas[i % 2];
        vectorModelos[i].listaDeComponentes = nullptr; 

	int cantidadComponentes = rand() % 5 + 1;
	for(int j=0; j<cantidadComponentes; j++){
	  int idComponente = rand()%1000+1;
	  int cantidad = rand()%10+1;
	  agregarComponenteAModelo(vectorModelos[i], idComponente, cantidad);
	}
    }

}

void mostrarModelos(){
  for(int i=0; i < 5; i++){
    cout<< "ID: "<< vectorModelos[i].ID_modelo<< endl;
    cout<< "Modelo: "<< vectorModelos[i].descripcion<< endl;
    cout<< "Precio Base: $"<< vectorModelos[i].precio_base<< endl;
    cout<< "Tempoarada: "<< vectorModelos[i].temporada<< endl;
    cout<< "Componentes: "<< endl;
    nodoModelos* temp = vectorModelos[i].listaDeComponentes;
    while(temp){
      cout<< " - Componente ID: "<< temp->info.ID_Accesorio<< " ( Cantidad: "<< temp->info.cantidad<< " )"<< endl;
      temp = temp->sgte;
    }
    cout<< "-- o --"<< endl;
  }
}


// Resolucion estrategica del problema:
// 1- Abrir archivo
int main()
{
  srand(time(0));
  cargarModelos();
  cargarComponentes();
  mostrarModelos();
  mostrarComponentes();
  return 0;
}
