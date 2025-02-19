#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<cfloat>

using namespace std;

/*
1. Declarar estructuras de los nodos, registros y vectores necesarios

2. Armar funciones para sincronizar la informacion de los registros, cargar vectores y mostrar datos en consola

3. 
*/

struct tipoInfo //Declarar informacion del nodo
{
  int ID_Accesorio;
  int cantidad;
};

struct nodoModelos //Declarar nodo de modelos, con su respectivo puntero 
{
  tipoInfo info;
  nodoModelos* sgte;
};

struct RegistroModelos //Declarar registro de modelos
{
  int ID_modelo;
  char descripcion[100 + 1];
  float precio_base;
  string temporada;
  nodoModelos* listaDeComponentes;
};

RegistroModelos vectorModelos[50 + 1]; //Declarar vector de modelos

struct tipoInfoProveedores // 5- Declarar registro de informacion de proveedores
{
  int ID;
  char nombre[50 + 1];
  float valor_unitario;
};

struct NodoProveedores //Declarar nodo de proveedores, con su respectivo puntero 
{
  tipoInfoProveedores info;
  NodoProveedores* sgte;
};

struct Componentes //Declarar registro de informacion de componentes
{
  int ID;
  char descripcion[100 + 1];
  NodoProveedores* listaProveedores;
  int stock;
};

Componentes vectorComponentes[1000];  //Declarar vector de componentes

struct registroPedidos  //Declarar registro de informacion de pedidos
{
  int ID_pedido;
  int ID_linea;
  int ID_modelo;
  int cantidad;
  float costo;
};

void agregarProveedorAComponente(Componentes &componente, int ID, const char* nombre, float valor_unitario)
{
  NodoProveedores* nuevoProveedor = new NodoProveedores;

  nuevoProveedor -> info.ID = ID;

  strcpy(nuevoProveedor -> info.nombre, nombre);

  nuevoProveedor -> info.valor_unitario = valor_unitario;
  nuevoProveedor -> sgte = componente.listaProveedores;

  componente.listaProveedores = nuevoProveedor;
}

void cargarComponentes()
{
  string nombresComponentes[] = {
    "Suela de goma", "Cordones resistentes", "Plantilla acolchada", "Forro transpirable", "Refuerzo de talón",
    "Cámara de aire", "Tejido impermeable", "Sistema de ajuste rápido", "Entresuela EVA", "Refuerzo lateral",
    "Cojín de impacto", "Placa de carbono", "Diseño ergonómico", "Malla transpirable", "Refuerzo en puntera",
    "Sistema de amortiguación", "Estructura de soporte", "Cuero sintético", "Espuma de memoria", "Costura reforzada"
  };

  string nombresProveedores[] = {"Proveedor A", "Proveedor B", "Proveedor C"};
  
  for(int i = 0; i < 10; i++)
  {
    vectorComponentes[i].ID = i + 1;

    strcpy(vectorComponentes[i].descripcion, nombresComponentes[i % 20].c_str());

    vectorComponentes[i].listaProveedores = nullptr; 
    vectorComponentes[i].stock = rand() % 500 + 50;

    for(int j = 0; j < 3; j++)
    {
      agregarProveedorAComponente(vectorComponentes[i], j + 1, nombresProveedores[j].c_str(), ((rand()%5000+500) / 100.0));
    }
  }
}

void mostrarComponentes()
{
  for(int i = 0; i < 10; i++)
  {
    cout << "ID: " << vectorComponentes[i].ID << endl;
    cout << "Componente: " << vectorComponentes[i].descripcion << endl;
    cout << "Stock: " << vectorComponentes[i].stock << endl;
    cout << "Proveedores: " << endl;

    NodoProveedores* temp = vectorComponentes[i].listaProveedores;

    while(temp)
    {
      cout << " - "<< temp->info.nombre << " ( Valor: $" << temp->info.valor_unitario << " )" << endl;

      temp = temp->sgte;
    }

    cout << "-- o --" << endl;
  }
}

void agregarComponenteAModelo(RegistroModelos& modelo, int ID_Componente, int cantidad)
{
  nodoModelos* nuevoNodo = new nodoModelos;

  nuevoNodo -> info.ID_Accesorio = ID_Componente;
  nuevoNodo -> info.cantidad = cantidad;
  nuevoNodo -> sgte = modelo.listaDeComponentes;

  modelo.listaDeComponentes = nuevoNodo;
}

void cargarModelos(int pedidos)
{
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
  
  string temporadas[] = {"Verano", "Invierno"};
  
  for (int i = 0; i < pedidos; i++)
  {
    vectorModelos[i].ID_modelo = i + 1;

    strcpy(vectorModelos[i].descripcion, nombres[i % 50].c_str());

    vectorModelos[i].precio_base = (rand() % 15000 + 5000) / 100.0; 
    vectorModelos[i].temporada = temporadas[i % 2];
    vectorModelos[i].listaDeComponentes = nullptr; 

    int cantidadComponentes = rand() % 5 + 1;
    for(int j = 0; j < cantidadComponentes; j++)
    {
      int idComponente = rand() % 1000 + 1;
      int cantidad = rand() % 10 + 1;

      agregarComponenteAModelo(vectorModelos[i], idComponente, cantidad);
    }
  }

}

void mostrarModelos(int pedidos)
{
  for(int i = 0; i < pedidos; i++)
  {
    cout << "ID: " << vectorModelos[i].ID_modelo << endl;
    cout << "Modelo: " << vectorModelos[i].descripcion << endl;
    cout << "Precio Base: $" << vectorModelos[i].precio_base << endl;
    cout << "Tempoarada: " << vectorModelos[i].temporada << endl;
    cout << "Componentes: " << endl;

    nodoModelos* temp = vectorModelos[i].listaDeComponentes;

    while(temp)
    {
      cout << " - Componente ID: " << temp->info.ID_Accesorio << " (Cantidad: " << temp->info.cantidad << ")"<< endl;

      temp = temp->sgte;
    }

    cout<< "-- o --" << endl;
  }
}

// Resolucion estrategica del problema:

int main()
{
  FILE* archivoPedidos = fopen("pedidos.dat", "ab"); //Abrir archivo
  
  int cantPedidos;

  if(fseek(archivoPedidos, 0, SEEK_SET) == 0)
  {
    cout << "Ingresar cantidad de pedidos: ";

    cin >> cantPedidos;
  }

  srand(time(0));
  cargarModelos(cantPedidos);
  cargarComponentes();

  if(!archivoPedidos) //Si el archivo no se pudo leer, termina el programa
  {
    cout << "Error al abrir el archivo" << endl;
    return 1;
  }

  registroPedidos pedido;

  for(int i = 0; i < cantPedidos; i++)
  {
    cout <<"Cargar informacion del Pedido " << i + 1 << ":" << endl;

    pedido.ID_pedido = i + 1;

    cout<<"Ingresar ID de Linea: ";
    
    cin>>pedido.ID_linea;

    cout<<"Ingresar ID de Modelo: ";
    
    cin>>pedido.ID_modelo;

    cout<<"Ingresar Cantidad: ";
    
    cin>>pedido.cantidad;

    fwrite(&pedido, sizeof(pedido), 1, archivoPedidos);
  }

  cout << "Pedidos guardados correctamente" << endl << endl;

  fseek(archivoPedidos, 0, SEEK_SET); //Leer y asociar los pedidos

  while(fread(&pedido, sizeof(pedido), 1, archivoPedidos))
  {
    for(int i = 0; i < cantPedidos; i++) //Recorrer modelos
    {
      if(pedido.ID_modelo == vectorModelos[i].ID_modelo) //Busqueda del modelo
      {
	      nodoModelos* componentes = vectorModelos[i].listaDeComponentes;

        while(componentes != nullptr) //Recorrer componentes del modelo
        {
          for(int j = 0; j < cantPedidos; j++)
          {
            if(componentes -> info.ID_Accesorio == vectorComponentes[j].ID) //Buscar componente
            {
              NodoProveedores* proveedor = vectorComponentes[j].listaProveedores;

              float menorValor = FLT_MAX; //Inicializa con el mayor valor posible

              NodoProveedores* proveedorMenor = nullptr;

              while(proveedor != nullptr)
              {
                if(proveedor -> info.valor_unitario < menorValor)
                {
                  menorValor = proveedor -> info.valor_unitario;

                  proveedorMenor = proveedor;
                }

                proveedor = proveedor -> sgte;
              }
	          }
	        }

	        componentes = componentes -> sgte;
	      }
      }
    }
  }

  mostrarModelos(cantPedidos);

  fclose(archivoPedidos);

  return 0;
}
