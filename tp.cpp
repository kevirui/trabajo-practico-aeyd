#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cfloat>
#include <ctime>

using namespace std;

struct Proveedor
{ // Estructura para almacenar los proveedores de un componente
    int id;
    char nombre[101];
    float valor_unitario;
};

struct Componente
{ // Estructura para almacenar los componentes de un modelo
    int id;
    char descripcion[101];
    Proveedor proveedores[3];
    int num_proveedores;
    int stock;
};

struct ComponenteModelo
{ // Estructura para almacenar los componentes de un modelo
    int id_accesorio;
    int cantidad;
};

struct Modelo
{ // Estructura para almacenar los modelos de zapatillas
    int id;
    char descripcion[101];
    float precio_base;
    char temporada[10];
    ComponenteModelo componentes[5];
    int num_componentes;
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

Modelo modelos[50];
Componente componentes[1000];

int num_modelos = 50, num_componentes = 20; // Cantidad de modelos y componentes

void inicializar_datos()
{                      // Inicializa los datos de los componentes y modelos
    srand(time(NULL)); // Inicializa el generador de números aleatorios
    for (int i = 0; i < num_componentes; i++)
    {                          // Inicializa los componentes
        componentes[i].id = i; // Asigna un ID de componente
        strcpy(componentes[i].descripcion, nombreComp[i].c_str());
        componentes[i].num_proveedores = 3;         // Cantidad de proveedores por componente
        componentes[i].stock = 50 + (rand() % 500); // Stock aleatorio entre 50 y 550
        for (int j = 0; j < 3; j++)
        {                                                                         // Inicializa los proveedores de cada componente
            componentes[i].proveedores[j].id = j;                                 // Asigna un ID de proveedor
            strcpy(componentes[i].proveedores[j].nombre, nombresProv[j].c_str()); // Asigna un nombre de proveedor
            componentes[i].proveedores[j].valor_unitario = 10.0 + (rand() % 100); // Precio aleatorio entre 10 y 110
        }
    }

    for (int i = 0; i < num_modelos; i++)
    {                                                                       // Inicializa los modelos
        modelos[i].id = i;                                                  // Asigna un ID de modelo
        strcpy(modelos[i].descripcion, nombreMod[i].c_str());               // Asigna una descripción de modelo
        modelos[i].precio_base = 50.0 + (rand() % 200);                     // Precio base aleatorio entre 50 y 250
        strcpy(modelos[i].temporada, (i % 2 == 0) ? "Verano" : "Invierno"); // Asigna una temporada de modelo
        modelos[i].num_componentes = 3 + (rand() % 3);                      // Cantidad de componentes por modelo
        for (int j = 0; j < modelos[i].num_componentes; j++)
        {                                                                      // Inicializa los componentes de cada modelo
            modelos[i].componentes[j].id_accesorio = rand() % num_componentes; // Asigna un ID de componente
            modelos[i].componentes[j].cantidad = 1 + (rand() % 10);            // Cantidad aleatoria entre 1 y 10
        }
    }
}

void mostrar_componentes()
{                                                         // Muestra la información de los componentes
    cout << "=== Información de Componentes ===" << endl; // Muestra la información de los componentes
    for (int i = 0; i < num_componentes; i++)
    { // Recorre los componentes
        cout << endl;
        cout << "ID: " << componentes[i].id << endl;                  // Muestra el ID del componente
        cout << "Componente: " << componentes[i].descripcion << endl; // Muestra la descripción del componente
        cout << "Stock: " << componentes[i].stock << endl;            // Muestra el stock del componente
        cout << "Proveedores:" << endl;                               // Muestra los proveedores del componente
        for (int j = 0; j < componentes[i].num_proveedores; j++)
        { // Recorre los proveedores del componente
            double valor = componentes[i].proveedores[j].valor_unitario;
            cout << " - " << componentes[i].proveedores[j].nombre << " ( Valor: $" << (int)(valor * 100 + 0.5) / 100.0 << " )" << endl; // Muestra datos del proveedor
        }
    }
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
        int id_mod = pedido.id_modelo;                                      // ID del modelo del pedido
        float costo_pedido = modelos[id_mod].precio_base * pedido.cantidad; // Costo base del pedido

        cout << endl;
        cout << "=== Pedido ID: " << pedido.id_pedido << " ===" << endl; // Muestra el ID del pedido
        cout << "Modelo: " << modelos[id_mod].descripcion << endl;       // Muestra la descripción del modelo
        cout << "Cantidad: " << pedido.cantidad << endl;                 // Muestra la cantidad del pedido
        double precioBase = (int)(modelos[id_mod].precio_base * 100 + 0.5) / 100.0;
        cout << "Precio Base: $" << precioBase << endl;             // Muestra el precio base del modelo
        cout << "Temporada: " << modelos[id_mod].temporada << endl; // Muestra la temporada del modelo
        cout << endl;
        cout << "Componentes necesarios:" << endl; // Muestra los componentes necesarios

        for (int j = 0; j < modelos[id_mod].num_componentes; j++)
        {                                                                                       // Recorre los componentes del modelo
            int id_comp = modelos[id_mod].componentes[j].id_accesorio;                          // ID del componente
            int cantidad_necesaria = modelos[id_mod].componentes[j].cantidad * pedido.cantidad; // Cantidad necesaria del componente

            cout << endl;
            cout << "ID: " << componentes[id_comp].id + 1 << endl;              // Muestra el ID del componente
            cout << "Componente: " << componentes[id_comp].descripcion << endl; // Muestra la descripción del componente
            cout << "Stock actual: " << componentes[id_comp].stock << endl;     // Muestra el stock del componente
            cout << "Cantidad necesaria: " << cantidad_necesaria << endl;       // Muestra la cantidad necesaria del componente
            cout << "Proveedores:" << endl;                                     // Muestra los proveedores del componente

            float menor_precio = FLT_MAX;                                  // Precio del proveedor más barato
            int proveedor_elegido = -1;                                    // ID del proveedor elegido
            for (int p = 0; p < componentes[id_comp].num_proveedores; p++) // Recorre los proveedores del componente
            {
                double valor = componentes[id_comp].proveedores[p].valor_unitario;
                cout
                    << " - " << componentes[id_comp].proveedores[p].nombre                // Muestra el nombre del proveedor
                    << " ( Valor: $" << (int)(valor * 100 + 0.5) / 100.0 << " )" << endl; // Muestra el precio del proveedor

                if (componentes[id_comp].proveedores[p].valor_unitario < menor_precio)
                {                                                                      // Si el precio es menor al precio mínimo
                    menor_precio = componentes[id_comp].proveedores[p].valor_unitario; // Actualiza el precio mínimo
                    proveedor_elegido = p;                                             // Actualiza el proveedor elegido
                }
            }

            if (componentes[id_comp].stock < cantidad_necesaria)
            {                                                                                   // Si no hay stock suficiente
                cout << "Error: Stock insuficiente para el componente " << id_comp + 1 << endl; // Muestra un mensaje de error
                continue;                                                                       // Continúa con el siguiente componente
            }

            componentes[id_comp].stock -= cantidad_necesaria;           // Actualiza el stock del componente
            float costo_componente = menor_precio * cantidad_necesaria; // Costo del componente
            costo_pedido += costo_componente;                           // Actualiza el costo del pedido

            cout << "Proveedor elegido: " << componentes[id_comp].proveedores[proveedor_elegido].nombre << endl; // Muestra el proveedor elegido
            costo_componente = (int)(costo_componente * 100 + 0.5) / 100.0;
            cout << "Costo del componente: $" << costo_componente << endl; // Muestra el costo del componente
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
    generar_pedidos("pedidos.dat");                              // Genera pedidos de ejemplo
    procesar_pedidos("pedidos.dat", "pedidos_actualizados.dat"); // Procesa los pedidos
    return 0;
}
