#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cfloat>
#include <ctime>

using namespace std;

struct Proveedor // InfoP
{ // Estructura para almacenar los proveedores de un componente
    int id;
    char nombre[101];
    float valor_unitario;
};

struct NodoProveedor{ // NodoP
	Proveedor info;
	NodoProveedor* sgte;
};

struct ListaProveedores{
  NodoProveedor* primero;
  ListaProveedores(){
    primero = nullptr;
  }
};

struct Componente // InfoC
{ // Estructura para almacenar los componentes de un modelo
    int id;
    char descripcion[101];
    int stock;
    ListaProveedores* lista_proveedores;
};

struct NodoComponentes{ // NodoC
	Componente info;
	NodoComponentes* sgte;
};

struct ListaComponentes{
	NodoComponentes* primero;
	ListaComponentes(){
	  primero = nullptr;
	}
};

struct ComponenteModelo // InfoCM
{ // Estructura para almacenar los componentes de un modelo
    int id_accesorio;
    int cantidad;
};

struct NodoComponenteModelo // NodoCM
{
	ComponenteModelo info;
	NodoComponenteModelo* sgte;
};

struct ListaComponentesModelo{
  NodoComponenteModelo* primero;
  ListaComponentesModelo(){
    primero = nullptr;
  }
};

struct Modelo
{ // Estructura para almacenar los modelos de zapatillas
    int id;
    char descripcion[101];
    float precio_base;
    char temporada[10];
    ListaComponentesModelo* componentes;
};

struct NodoModelo{
  Modelo info;
  NodoModelo* sgte;
};

struct ListaModelos{
  NodoModelo* primero;
  ListaModelos(){
    primero = nullptr;
  }
};

struct Pedido
{ // Estructura para almacenar los pedidos de zapatillas
    int id_pedido;
    int id_linea;
    int id_modelo;
    char fecha[11];
    int cantidad;
    float costo;
};

string nombreComp[] = { // Descripciones de los componentes
    "Suela de goma", "Cordones resistentes", "Plantilla acolchada", "Forro transpirable", "Refuerzo de talón",
    "Cámara de aire", "Tejido impermeable", "Sistema de ajuste rápido", "Entresuela EVA", "Refuerzo lateral",
    "Cojín de impacto", "Placa de carbono", "Diseño ergonómico", "Malla transpirable", "Refuerzo en puntera",
    "Sistema de amortiguación", "Estructura de soporte", "Cuero sintético", "Espuma de memoria", "Costura reforzada"};

string nombreMod[] = { // Descripciones de los modelos
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

string nombresProv[] = {"Proveedor A", "Proveedor B", "Proveedor C"}; // Nombres de los proveedores

int num_modelos = 50, num_componentes = 20; // Cantidad de modelos y componentes

// Variables globales para las listas 
ListaComponentes* lista_componentes;
ListaModelos* lista_modelos;
					
void agregar_proveedor(int id, const char* nombre, float valor, ListaProveedores* lista){
  NodoProveedor* nuevo = new NodoProveedor;
	nuevo->info.id = id;
	strcpy(nuevo->info.nombre, nombre);
	nuevo->info.valor_unitario= valor;
	nuevo->sgte = nullptr;

	// Insertar al final
	if(lista->primero == nullptr){
		lista->primero = nuevo;
	}else{
	  NodoProveedor* actual = lista->primero;
	  while(actual->sgte != nullptr){
	    actual = actual->sgte;
	  }
	  actual->sgte = nuevo;
	}
}

void agregar_componente(int id, const char* descripcion, int stock){
  NodoComponentes* nuevo = new NodoComponentes;
	nuevo->info.id = id+1000; 
	strcpy(nuevo->info.descripcion, descripcion);
	nuevo->info.stock = stock;
	nuevo->info.lista_proveedores = new ListaProveedores();
	nuevo->sgte = nullptr;

	// Insertar al final
	if(lista_componentes->primero == nullptr){
		lista_componentes->primero = nuevo;
	}else{
	  NodoComponentes* actual = lista_componentes->primero;
	  while(actual->sgte != nullptr){
	    actual = actual->sgte;
	  }
	  actual->sgte = nuevo;
	}
}

void agregar_componente_modelo(int id_accesorio, int cantidad, ListaComponentesModelo* lista){
  NodoComponenteModelo* nuevo = new NodoComponenteModelo;
	nuevo->info.id_accesorio = id_accesorio + 1000;
	nuevo->info.cantidad = cantidad; 
	nuevo->sgte = nullptr;

	// Insertar al final
	if(lista->primero == nullptr){
		lista->primero = nuevo;
	}else{
	  NodoComponenteModelo* actual = lista->primero;
	  while(actual->sgte != nullptr){
	    actual = actual->sgte;
	  }
	  actual->sgte = nuevo;
	}
}

void agregar_modelo(int id, const char* descripcion, float precio_base, const char* temporada){
  NodoModelo* nuevo = new NodoModelo;
	nuevo->info.id = id;
	strcpy(nuevo->info.descripcion, descripcion);
	nuevo->info.precio_base = precio_base;
	strcpy(nuevo->info.temporada, temporada);
	nuevo->info.componentes = new ListaComponentesModelo();
	nuevo->sgte = nullptr;

	// Insertar al final
	if(lista_modelos->primero == nullptr){
		lista_modelos->primero = nuevo;
	}else{
	  NodoModelo* actual = lista_modelos->primero;
	  while(actual->sgte != nullptr){
	    actual = actual->sgte;
	  }
	  actual->sgte = nuevo;
	}
}

void inicializar_datos()
{                      // Inicializa los datos de los componentes y modelos
    lista_componentes = new ListaComponentes();
    lista_modelos = new ListaModelos();
    
    srand(time(NULL)); // Inicializa el generador de números aleatorios
    
    for (int i = 0; i < num_componentes; i++)
    {                          // Inicializa los componentes
      agregar_componente(i, nombreComp[i].c_str(), 50 + (rand() % 500)); // Agrega un componente

      // Obtener el componente recien agregado
      NodoComponentes* comp = lista_componentes->primero;
      while(comp->sgte != nullptr){
	comp = comp->sgte;
      }
        for (int j = 0; j < 3; j++)
        {                                                                         // Inicializa los proveedores de cada componente
	  agregar_proveedor(j, nombresProv[j].c_str(), 10.0 + (rand() % 100), comp->info.lista_proveedores); // Agrega un proveedor
        }
    }

    for (int i = 0; i < num_modelos; i++)
    {                                                                       // Inicializa los modelos
      agregar_modelo(i, nombreMod[i].c_str(), 50.0 + (rand() % 200), (i%2==0) ? "Verano" : "Invierno"); // Agrega un modelo
      // Obtener el modelo recien agregado
      NodoModelo* mod = lista_modelos->primero;
      while(mod->sgte != nullptr){
	mod = mod->sgte;
      }
      int num_comp = 3 + (rand() % 3);
        for (int j = 0; j < num_comp; j++)
        {                                                                      // Inicializa los componentes de cada modelo
	  agregar_componente_modelo(rand() % num_componentes, 1 + (rand() % 10), mod->info.componentes); // Agrega un componente al modelo
        }
    }
}

void mostrar_componentes()
{                                                         // Muestra la información de los componentes
    cout << "=== Información de Componentes ===" << endl; // Muestra la información de los componentes
    NodoComponentes* comp = lista_componentes->primero;
    while(comp != nullptr){
        cout << endl;
        cout << "ID: " << comp->info.id << endl;                  // Muestra el ID del componente
        cout << "Componente: " << comp->info.descripcion << endl; // Muestra la descripción del componente
        cout << "Stock: " << comp->info.stock << endl;            // Muestra el stock del componente
        cout << "Proveedores:" << endl;                               // Muestra los proveedores del componente
	NodoProveedor* prov = comp->info.lista_proveedores->primero;
        while(prov!=NULL)
        { // Recorre los proveedores del componente
            double valor = prov->info.valor_unitario;
            cout << " - " << prov->info.nombre << " ( Valor: $" << (int)(valor * 100 + 0.5) / 100.0 << " )" << endl; // Muestra datos del proveedor
	    prov = prov->sgte;
        }
	comp = comp->sgte;
    }
}

void liberar_memoria(){
  // Liberar memoria de lista componentes
  NodoComponentes* comp = lista_componentes->primero;
  while(comp != nullptr){
    NodoProveedor* prov = comp->info.lista_proveedores->primero;
    while(prov != NULL){
      NodoProveedor* aux = prov;
      prov = prov->sgte;
      delete aux;
    }
    delete comp->info.lista_proveedores;
    NodoComponentes* aux = comp;
    comp = comp->sgte;
    delete aux;
  }
  delete lista_componentes;

  // Liberar memoria de lista modelos
  NodoModelo* mod = lista_modelos->primero;
  while(mod != nullptr){
    NodoComponenteModelo* comp_mod = mod->info.componentes->primero;
    while(comp_mod != NULL){
      NodoComponenteModelo* aux = comp_mod;
      comp_mod = comp_mod->sgte;
      delete aux;
    }
    delete mod->info.componentes;
    NodoModelo* aux = mod;
    mod = mod->sgte;
    delete aux;
  }
  delete lista_modelos;
}

void generar_pedidos(const char *archivo_pedidos)
{                                                 // Genera pedidos de ejemplo
    FILE *archivo = fopen(archivo_pedidos, "wb"); // Abre el archivo de pedidos en modo escritura binaria
    if (!archivo)
    {                                                            // Si no se pudo abrir el archivo
        cout << "Error al abrir el archivo de pedidos." << endl; // Muestra un mensaje de error
        return;
    }

    for (int i = 0; i < 5; i++)
    {                                                                                         // Genera 5 pedidos de ejemplo
        Pedido pedido = {i + 1, i, rand() % num_modelos, "2025-02-20", (rand() % 10) + 1, 0}; // Genera un pedido aleatorio
        fwrite(&pedido, sizeof(Pedido), 1, archivo);                                          // Escribe el pedido en el archivo
    }

    fclose(archivo);                                                       // Cierra el archivo de pedidos
    cout << "Se han generado 5 pedidos de ejemplo en pedidos.dat" << endl; // Muestra un mensaje de éxito
}

void procesar_pedidos(const char *archivo_entrada, const char *archivo_salida)
{                                                    // Procesa los pedidos
    FILE *archivo_in = fopen(archivo_entrada, "rb"); // Abre el archivo de pedidos en modo lectura binaria
    FILE *archivo_out = fopen(archivo_salida, "wb"); // Abre el archivo de pedidos actualizados en modo escritura binaria
    if (!archivo_in || !archivo_out)
    {                                                              // Si no se pudieron abrir los archivos
        cout << "Error al abrir los archivos de pedidos." << endl; // Muestra un mensaje de error
        return;
    }

    Pedido pedido;                 // Estructura para almacenar los pedidos
    float costo_total_pedidos = 0; // Costo total de los pedidos
    while (fread(&pedido, sizeof(Pedido), 1, archivo_in) == 1)
    {                                                                       // Lee los pedidos del archivo
      NodoModelo* mod = lista_modelos->primero;
      while(mod!=NULL && mod->info.id != pedido.id_modelo){
	mod = mod->sgte;
      }
      if(mod ==NULL){
	cout<< "Modelo no encontrado"<< endl;
	continue;
      }

        float costo_pedido = mod->info.precio_base * pedido.cantidad; // Costo base del pedido

        cout << endl;
        cout << "=== Pedido ID: " << pedido.id_pedido << " ===" << endl; // Muestra el ID del pedido
        cout << "Modelo: " << mod->info.descripcion << endl;       // Muestra la descripción del modelo
        cout << "Cantidad: " << pedido.cantidad << endl;                 // Muestra la cantidad del pedido
        double precioBase = (int)(mod->info.precio_base * 100 + 0.5) / 100.0;
        cout << "Precio Base: $" << precioBase << endl;             // Muestra el precio base del modelo
        cout << "Temporada: " << mod->info.temporada << endl; // Muestra la temporada del modelo
        cout << endl;
        cout << "Componentes necesarios:" << endl; // Muestra los componentes necesarios

	NodoComponenteModelo* comp_mod = mod->info.componentes->primero;
	while(comp_mod != NULL){
	  NodoComponentes* comp = lista_componentes->primero;
	  while(comp != NULL && comp->info.id != comp_mod->info.id_accesorio){
	    comp = comp->sgte;
	  }
	  if(comp==NULL){
	    cout<< "Componente no encontrado"<< endl;
	    comp_mod = comp_mod->sgte;
	    continue;
	  }
            int cantidad_necesaria = comp_mod->info.cantidad * pedido.cantidad; // Cantidad necesaria del componente

            cout << endl;
            cout << "ID: " << comp->info.id + 1 << endl;              // Muestra el ID del componente
            cout << "Componente: " << comp->info.descripcion<< endl; // Muestra la descripción del componente
            cout << "Stock actual: " << comp->info.stock << endl;     // Muestra el stock del componente
            cout << "Cantidad necesaria: " << cantidad_necesaria << endl;       // Muestra la cantidad necesaria del componente
            cout << "Proveedores:" << endl;                                     // Muestra los proveedores del componente
            float menor_precio = FLT_MAX;                                  // Precio del proveedor más barato
            NodoProveedor* proveedor_elegido = NULL;                                    // ID del proveedor elegido
	    NodoProveedor* prov = comp->info.lista_proveedores->primero;
	    while(prov !=NULL)
            {
                double valor = prov->info.valor_unitario;
                cout
                    << " - " << prov->info.nombre // Muestra el nombre del proveedor
                    << " ( Valor: $" << (int)(valor * 100 + 0.5) / 100.0 << " )" << endl; // Muestra el precio del proveedor

                if (prov->info.valor_unitario < menor_precio)
                {                                                                      // Si el precio es menor al precio mínimo
                    menor_precio = prov->info.valor_unitario; // Actualiza el precio mínimo
                    proveedor_elegido = prov;                                             // Actualiza el proveedor elegido
                }
		prov = prov->sgte;
            }

            if (comp->info.stock < cantidad_necesaria)
            {                                                                                   // Si no hay stock suficiente
                cout << "Error: Stock insuficiente para el componente " << comp->info.id + 1 << endl; // Muestra un mensaje de error
		comp_mod = comp_mod->sgte;
                continue;                                                                       // Continúa con el siguiente componente
            }

            comp->info.stock -= cantidad_necesaria;           // Actualiza el stock del componente
            float costo_componente = menor_precio * cantidad_necesaria; // Costo del componente
            costo_pedido += costo_componente;                           // Actualiza el costo del pedido

            cout << "Proveedor elegido: " << proveedor_elegido->info.nombre << endl; // Muestra el proveedor elegido
            costo_componente = (int)(costo_componente * 100 + 0.5) / 100.0;
            cout << "Costo del componente: $" << costo_componente << endl; // Muestra el costo del componente

	    comp_mod = comp_mod->sgte;
        }

        pedido.costo = costo_pedido;                     // Actualiza el costo del pedido
        costo_total_pedidos += costo_pedido;             // Actualiza el costo total de los pedidos
        fwrite(&pedido, sizeof(Pedido), 1, archivo_out); // Escribe el pedido actualizado en el archivo

        costo_pedido = (int)(costo_pedido * 100 + 0.5) / 100.0;
        cout << "\nCosto total del pedido: $" << costo_pedido << endl; // Muestra el costo total del pedido
    }

    fclose(archivo_in);  // Cierra el archivo de pedidos
    fclose(archivo_out); // Cierra el archivo de pedidos actualizados

    cout << endl;
    cout << "=== Resumen de pedidos actualizados ===" << endl; // Muestra un resumen de los pedidos actualizados
    archivo_out = fopen(archivo_salida, "rb");                 // Abre el archivo de pedidos actualizados en modo lectura binaria
    while (fread(&pedido, sizeof(Pedido), 1, archivo_out) == 1)
    { // Lee los pedidos actualizados del archivo
        double pedidoCosto = (int)(pedido.costo * 100 + 0.5) / 100.0;
        cout << "ID Pedido: " << pedido.id_pedido << ", ID Modelo: " << pedido.id_modelo + 1 // Muestra el ID del pedido y del modelo
             << ", Cantidad: " << pedido.cantidad << ", Costo: $" << pedidoCosto << endl;    // Muestra la cantidad y el costo del pedido
    }
    fclose(archivo_out); // Cierra el archivo de pedidos actualizados

    costo_total_pedidos = (int)(costo_total_pedidos * 100 + 0.5) / 100.0;
    cout << endl;
    cout << "Costo total de todos los pedidos: $" << costo_total_pedidos << endl; // Muestra el costo total de los pedidos
}

int main()
{                                                                // Función principal
    inicializar_datos();                                         // Inicializa los datos de los componentes y modelos
    mostrar_componentes();                                       // Muestra la información de los componentes
    generar_pedidos("pedidos.dat");                              // Genera pedidos de ejemplo
    procesar_pedidos("pedidos.dat", "pedidos_actualizados.dat"); // Procesa los pedidos
    liberar_memoria(); // Libera la memoria de los componentes y modelos
    return 0;
}
