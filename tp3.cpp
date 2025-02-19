#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cfloat>
using namespace std;

// 1- Declarar el campo de la informacion del Nodo.

struct RegistroAccesorios 
{
  int ID_Accesorio;
  char descripcion[101];
  int stock;
};

// 2- Declarar struct Nodo()

struct NodoComponente
{
  RegistroAccesorios info;
  NodoComponente *sgte;
};

// 3- Declarar struct registro de modelos.

struct RegistroModelos
{
  int ID_modelo;
  char nombre[101];
  float precio_base;
  string temporada;
  NodoComponente *listaDeComponentes;
};

// 4- Declarar vector de modelos.


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
  NodoProveedores *sgte;
};

struct Componentes
{
  NodoComponente *listaDeComponentes;
  NodoProveedores *listaProveedores;
};

struct RegistroArchivoPedidos
{
  int ID_pedido;
  int ID_linea;
  int ID_modelo;
  int fecha;
  int cantidadPedidos;
  float costo;
  Componentes* componente;
};

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
      "Echo Stride", "Supernova Glide", "Pioneer Dash", "Horizon Edge", "Hyper Drive"};

string temporadas[] = {"verano", "invierno"};

string nombresComponentes[] = {
      "Suela de goma", "Cordones resistentes", "Plantilla acolchada", "Forro transpirable", "Refuerzo de talón",
      "Cámara de aire", "Tejido impermeable", "Sistema de ajuste rápido", "Entresuela EVA", "Refuerzo lateral",
      "Cojín de impacto", "Placa de carbono", "Diseño ergonómico", "Malla transpirable", "Refuerzo en puntera",
      "Sistema de amortiguación", "Estructura de soporte", "Cuero sintético", "Espuma de memoria", "Costura reforzada"};

string nombresProveedores[] = {"Proveedor A", "Proveedor B", "Proveedor C"};
RegistroModelos vectorModelos[50];
Componentes* vectorComponentes[1000];
int cantModelos = 0, cantComponentes = 0;

void inicializarComponentes(){
  for(int i=0; i<1000; i++){
    vectorComponentes[i] = nullptr;
  }
}

void cargarComponentes(int cantidadComponentes, RegistroModelos vectorModelos)
{
  int IDAccesorio = vectorModelos.listaDeComponentes->info.ID_Accesorio;
  for (int i = 0; i < cantidadComponentes; i++)
  {
    vectorComponentes[i]->listaDeComponentes->info.ID_Accesorio = IDAccesorio;
    strcpy(vectorComponentes[i]->listaDeComponentes->info.descripcion, nombresComponentes[IDAccesorio].c_str());
    vectorComponentes[i]->listaProveedores = nullptr;
    vectorComponentes[i]->listaDeComponentes->info.stock = rand() % 100 + 1;

    // Agregar Proveedores al Componente
    for (int j = 0; j < 3; j++)
    {
      NodoProveedores *nuevoProveedor = new NodoProveedores;
      nuevoProveedor->info.ID = j;
      strcpy(nuevoProveedor->info.nombre, nombresProveedores[j].c_str());
      nuevoProveedor->info.valor_unitario = ( (rand() % 5000 + 50) / 100.0 );
      nuevoProveedor->sgte = vectorComponentes[i]->listaProveedores;
      vectorComponentes[i]->listaProveedores = nuevoProveedor;
    }
  }
}

void cargarModelos(int cantPedidos, RegistroArchivoPedidos pedido)
{ 
  for (int i = 0; i < cantPedidos; i++)
  {
    vectorModelos[i].ID_modelo = pedido.ID_modelo;
    strcpy(vectorModelos[i].nombre, nombres[pedido.ID_modelo-1].c_str());
    vectorModelos[i].precio_base = (rand() % 15000 + 5000) / 100.0;
    vectorModelos[i].temporada = temporadas[i % 2];

    vectorModelos[i].listaDeComponentes = nullptr;
    NodoComponente* ultimo = nullptr;

    // Asociar componentes al modelo 
    cantComponentes = rand() % 5 + 1;
    for (int j = 0; j < cantComponentes; j++)
    {
      int idComponente = rand() % 5;
      NodoComponente* nuevo = new NodoComponente();
      nuevo->info.ID_Accesorio = idComponente;
      nuevo->info.stock = rand() % 10 + 1;
      nuevo->sgte = nullptr;

      if(vectorModelos[i].listaDeComponentes == nullptr){
	vectorModelos[i].listaDeComponentes = nuevo;
      }else{
	ultimo->sgte = nuevo;
      }
      ultimo = nuevo;
    }
    cargarComponentes(cantComponentes, vectorModelos[i]);
  }
}

void mostrarPedido(int cantPedidos, FILE* archivoPedidos)
{
  fseek(FILE* archivoPedidos, sizeof(archivoPedidos), SEEK_SET);

  while(fread()){}
  int idModeloSolicitado = pedido.ID_modelo;

  for (int i = 0; i < cantPedidos; i++)
  {
    cout << "ID: " << vectorModelos[idModeloSolicitado].ID_modelo << endl;
    cout << "Nombre del modelo: " << vectorModelos[idModeloSolicitado].nombre<< endl;
    cout << "Precio Base: $" << vectorModelos[idModeloSolicitado].precio_base << endl;
    cout << "Tempoarada: " << vectorModelos[idModeloSolicitado].temporada << endl;
    cout << "Componentes: "<< endl;
    NodoComponente *temp = vectorModelos[idModeloSolicitado].listaDeComponentes;
    while (temp != nullptr)
    {
      cout << " - Componente ID: " << temp->info.ID_Accesorio << " ( Cantidad: " << temp->info.stock<< " )" << endl;
      temp = temp->sgte;
    }
    cout << "-- o --" << endl;
  }

  cout<< "Lista de Componentes: "<< endl;
  for (int i = 0; i < pedido.componente->listaDeComponentes->info.stock; i++)
  {
    cout << "ID: " << vectorComponentes[idModeloSolicitado]->listaDeComponentes->info.ID_Accesorio << endl;
    cout << "Componente: " << vectorComponentes[idModeloSolicitado]->listaDeComponentes->info.descripcion << endl;
    cout << "Stock: " << vectorComponentes[idModeloSolicitado]->listaDeComponentes->info.stock << endl;
    cout << "Proveedores: " << endl;
    NodoProveedores *temp = vectorComponentes[idModeloSolicitado]->listaProveedores;
    while (temp)
    {
      cout << " - " << temp->info.nombre << " ( Valor: $" << temp->info.valor_unitario << " )" << endl;
      temp = temp->sgte;
    }
    cout << "-- o --" << endl;
  }
}

// Resolucion estrategica del problema:
// 1- Abrir archivo
int main()
{
  srand(time(0));

  FILE *archivoPedidos = fopen("pedidos.dat", "ab");

  if (!archivoPedidos)
  {
    cout << "Error al abrir el archivo" << endl;
    return 1;
  }

  int cantPedidos;
  cout<< "Cuantos pedidos quieres? "; cin>> cantPedidos;

  RegistroArchivoPedidos pedido;
  for (int i = 0; i < cantPedidos; i++)
  {
    cout << "Ingresa el pedido " << i + 1 << " a continuacion" << endl;
    pedido.ID_pedido = i;

    cout << "Ingresa el id linea que deseas: ";
    cin >> pedido.ID_linea;

    cout << "Ingresa el id modelo que deseas: ";
    cin >> pedido.ID_modelo;

    cout << "Ingresa la cantidad que deseas: ";
    cin >> pedido.cantidadPedidos;

    fwrite(&pedido, sizeof(pedido), 1, archivoPedidos);
  }
  
  cargarModelos(cantPedidos, pedido);

  cout << "Pedidos guardados correctamente" << endl;

  mostrarPedido(cantPedidos, archivoPedidos);

  fclose(archivoPedidos);


  return 0;
}
