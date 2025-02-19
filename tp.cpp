#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cfloat>
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
  nodoModelos *sgte;
};

// 3- Declarar struct registro de modelos.

struct RegistroModelos
{
  int ID_modelo;
  char descripcion[101];
  float precio_base;
  string temporada;
  nodoModelos *listaDeComponentes;
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
  NodoProveedores *sgte;
};

struct Componentes
{
  nodoModelos *componente;
  char descripcion[101];
  NodoProveedores *listaProveedores;
  int stock;
};

Componentes vectorComponentes[1000];

struct registroPedidos
{
  int ID_pedido;
  int ID_linea;
  int ID_modelo;
  int cantidad;
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

void agregarProveedorAComponente(Componentes &componente, int ID, const char *nombre, float valor_unitario)
{
  NodoProveedores *nuevoProveedor = new NodoProveedores;
  nuevoProveedor->info.ID = ID;
  strcpy(nuevoProveedor->info.nombre, nombre);
  nuevoProveedor->info.valor_unitario = valor_unitario;
  nuevoProveedor->sgte = componente.listaProveedores;
  componente.listaProveedores = nuevoProveedor;
}

void cargarComponentes(int cantidadComponentes, RegistroModelos vectorModelos)
{
  int IDAccesorio = vectorModelos.listaDeComponentes->info.ID_Accesorio;
  for (int i = 0; i < cantidadComponentes; i++)
  {
    vectorComponentes[i].componente->info.ID_Accesorio = IDAccesorio;
    strcpy(vectorComponentes[i].descripcion, nombresComponentes[IDAccesorio].c_str());
    vectorComponentes[i].listaProveedores = nullptr;
    vectorComponentes[i].stock = rand() % 100 + 1;

    for (int j = 0; j < 3; j++)
    {
      agregarProveedorAComponente(vectorComponentes[i], j + 1, nombresProveedores[j].c_str(), ((rand() % 5000 + 500) / 100.0));
    }
  }
}

void mostrarComponentes(registroPedidos pedido)
{
  for (int i = 0; i < pedido.componente->componente->info.cantidad; i++)
  {
    cout << "ID: " << vectorComponentes[i].componente->info.ID_Accesorio << endl;
    cout << "Componente: " << vectorComponentes[i].descripcion << endl;
    cout << "Stock: " << vectorComponentes[i].stock << endl;
    cout << "Proveedores: " << endl;
    NodoProveedores *temp = vectorComponentes[i].listaProveedores;
    while (temp)
    {
      cout << " - " << temp->info.nombre << " ( Valor: $" << temp->info.valor_unitario << " )" << endl;
      temp = temp->sgte;
    }
    cout << "-- o --" << endl;
  }
}

void agregarComponenteAModelo(RegistroModelos &modelo, int ID_Componente, int cantidad)
{
  nodoModelos *nuevoNodo = new nodoModelos;
  nuevoNodo->info.ID_Accesorio = ID_Componente;
  nuevoNodo->info.cantidad = cantidad;
  nuevoNodo->sgte = modelo.listaDeComponentes;
  modelo.listaDeComponentes = nuevoNodo;
}

void cargarModelos(int cantPedidos, registroPedidos pedido)
{ 
  for (int i = 0; i < cantPedidos; i++)
  {
    vectorModelos[i].ID_modelo = pedido.ID_modelo;
    strcpy(vectorModelos[i].descripcion, nombres[pedido.ID_modelo-1].c_str());
    vectorModelos[i].precio_base = (rand() % 15000 + 5000) / 100.0;
    vectorModelos[i].temporada = temporadas[i % 2];
    vectorModelos[i].listaDeComponentes = nullptr;

    int cantidadComponentes = rand() % 5 + 1;
    pedido.cantidadComponentes = cantidadComponentes;
    for (int j = 0; j < cantidadComponentes; j++)
    {
      int idComponente = rand() % 21;
      int cantidad = rand() % 10 + 1;
      agregarComponenteAModelo(vectorModelos[i], idComponente, cantidad);
    }
    cargarComponentes(cantidadComponentes, vectorModelos[i]);
  }
}

void mostrarModelos(int cantPedidos)
{
  for (int i = 0; i < cantPedidos; i++)
  {
    cout << "ID: " << vectorModelos[i].ID_modelo << endl;
    cout << "Modelo: " << vectorModelos[i].descripcion << endl;
    cout << "Precio Base: $" << vectorModelos[i].precio_base << endl;
    cout << "Tempoarada: " << vectorModelos[i].temporada << endl;
    cout << "Componentes: " << endl;
    nodoModelos *temp = vectorModelos[i].listaDeComponentes;
    while (temp)
    {
      cout << " - Componente ID: " << temp->info.ID_Accesorio << " ( Cantidad: " << temp->info.cantidad << " )" << endl;
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

  registroPedidos pedido;
  for (int i = 0; i < cantPedidos; i++)
  {
    cout << "Ingresa el pedido " << i + 1 << " a continuacion:" << endl;
    pedido.ID_pedido = i;

    cout << "Ingresa el id linea que deseas: ";
    cin >> pedido.ID_linea;

    cout << "Ingresa el id modelo que deseas: ";
    cin >> pedido.ID_modelo;

    cout << "Ingresa la cantidad que deseas: ";
    cin >> pedido.cantidad;

    fwrite(&pedido, sizeof(pedido), 1, archivoPedidos);
  }
  cargarModelos(cantPedidos, pedido);
  cout << "Pedidos guardados correctamente" << endl;

  // Leer y asociar los pedidos
  fseek(archivoPedidos, 0, SEEK_SET);

  // Recorrer modelos, buscar el modelo, componentes del modelo, el vector de componentes, buscar el componente
  while (fread(&pedido, sizeof(pedido), 1, archivoPedidos))
  {
    for (int i = 0; i < 5; i++)
    {
      if (pedido.ID_modelo == vectorModelos[i].ID_modelo)
      {
        nodoModelos *componentes = vectorModelos[i].listaDeComponentes;
        while (componentes != nullptr)
        {
          for (int j = 0; j < 10; j++)
          {
            if (componentes->info.ID_Accesorio == vectorComponentes[j].ID)
            {
              NodoProveedores *proveedor = vectorComponentes[j].listaProveedores;
              float menorValor = FLT_MAX; // Inicializa con el mayor valor posible
              NodoProveedores *proveedorMenor = nullptr;

              while (proveedor != nullptr)
              {
                if (proveedor->info.valor_unitario < menorValor)
                {
                  menorValor = proveedor->info.valor_unitario;
                  proveedorMenor = proveedor;
                }
                proveedor = proveedor->sgte;
              }
            }
          }
          componentes = componentes->sgte;
        }
      }
    }
  }

  fclose(archivoPedidos);

  mostrarModelos(cantPedidos);
  mostrarComponentes(pedido);

  return 0;
}
