#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cfloat>
#include <ctime>
#include <iomanip> // Para formatear la salida de los precios

using namespace std;

struct Proveedor {
    int id;
    char nombre[101];
    float valor_unitario;
};

struct Componente {
    int id;
    char descripcion[101];
    Proveedor proveedores[3];
    int num_proveedores;
    int stock;
};

struct ComponenteModelo {
    int id_accesorio;
    int cantidad;
};

struct Modelo {
    int id;
    char descripcion[101];
    float precio_base;
    char temporada[10];
    ComponenteModelo componentes[5];
    int num_componentes;
};

struct Pedido {
    int id_pedido;
    int id_linea;
    int id_modelo;
    char fecha[11];
    int cantidad;
    float costo;
};

string nombreComp[] = {
  "Suela de goma", "Cordones resistentes", "Plantilla acolchada", "Forro transpirable", "Refuerzo de talón",
  "Cámara de aire", "Tejido impermeable", "Sistema de ajuste rápido", "Entresuela EVA", "Refuerzo lateral",
  "Cojín de impacto", "Placa de carbono", "Diseño ergonómico", "Malla transpirable", "Refuerzo en puntera",
  "Sistema de amortiguación", "Estructura de soporte", "Cuero sintético", "Espuma de memoria", "Costura reforzada"
};

string nombreMod[] = {
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

string nombresProv[] = {"Proveedor A", "Proveedor B", "Proveedor C"};

Modelo modelos[50];
Componente componentes[1000];

int num_modelos = 50, num_componentes = 20;

void inicializar_datos() {
    srand(time(NULL));
    for (int i = 0; i < num_componentes; i++) {
        componentes[i].id = i;
        strcpy(componentes[i].descripcion, nombreComp[i].c_str());
        componentes[i].num_proveedores = 3;
        componentes[i].stock = 50 + (rand() % 500); // Stock aleatorio entre 50 y 549
        for (int j = 0; j < 3; j++) {
            componentes[i].proveedores[j].id = j;
            strcpy(componentes[i].proveedores[j].nombre, nombresProv[j].c_str());
            componentes[i].proveedores[j].valor_unitario = 10.0 + (rand() % 100); // Precio aleatorio entre 10 y 109
        }
    }

    for (int i = 0; i < num_modelos; i++) {
        modelos[i].id = i;
        strcpy(modelos[i].descripcion, nombreMod[i].c_str());
        modelos[i].precio_base = 50.0 + (rand() % 200);
        strcpy(modelos[i].temporada, (i % 2 == 0) ? "Verano" : "Invierno");
        modelos[i].num_componentes = 3 + (rand() % 3);
        for (int j = 0; j < modelos[i].num_componentes; j++) {
            modelos[i].componentes[j].id_accesorio = rand() % num_componentes;
            modelos[i].componentes[j].cantidad = 1 + (rand() % 10);
        }
    }
}

void mostrar_componentes() {
    cout << "=== Información de Componentes ===" << endl;
    for (int i = 0; i < num_componentes; i++) {
        cout << "\nID: " << componentes[i].id << endl;
        cout << "Componente: " << componentes[i].descripcion << endl;
        cout << "Stock: " << componentes[i].stock << endl;
        cout << "Proveedores:" << endl;
        for (int j = 0; j < componentes[i].num_proveedores; j++) {
            cout << " - " << componentes[i].proveedores[j].nombre 
                 << " ( Valor: $" << fixed << setprecision(2) << componentes[i].proveedores[j].valor_unitario << " )" << endl;
        }
    }
}

void generar_pedidos(const char *archivo_pedidos) {
    FILE *archivo = fopen(archivo_pedidos, "wb");
    if (!archivo) {
        cout << "Error al abrir el archivo de pedidos." << endl;
        return;
    }

    for (int i = 0; i < 5; i++) {
        Pedido pedido = {i + 1, i, rand() % num_modelos, "2025-02-20", (rand() % 10) + 1, 0};
        fwrite(&pedido, sizeof(Pedido), 1, archivo);
    }

    fclose(archivo);
    cout << "Se han generado 5 pedidos de ejemplo en pedidos.dat" << endl;
}

void procesar_pedidos(const char *archivo_entrada, const char *archivo_salida) {
    FILE* archivo_in = fopen(archivo_entrada, "rb");
    FILE* archivo_out = fopen(archivo_salida, "wb");
    if (!archivo_in || !archivo_out) {
        cout << "Error al abrir los archivos de pedidos." << endl;
        return;
    }

    Pedido pedido;
    float costo_total_pedidos = 0;
    while (fread(&pedido, sizeof(Pedido), 1, archivo_in) == 1) {
        int id_mod = pedido.id_modelo;
        float costo_pedido = modelos[id_mod].precio_base * pedido.cantidad;

        cout << "\n=== Pedido ID: " << pedido.id_pedido << " ===" << endl;
        cout << "Modelo: " << modelos[id_mod].descripcion << endl;
        cout << "Cantidad: " << pedido.cantidad << endl;
        cout << "Precio Base: $" << fixed << setprecision(2) << modelos[id_mod].precio_base << endl;
        cout << "Temporada: " << modelos[id_mod].temporada << endl;
        cout << "\nComponentes necesarios:" << endl;

        for (int j = 0; j < modelos[id_mod].num_componentes; j++) {
            int id_comp = modelos[id_mod].componentes[j].id_accesorio;
            int cantidad_necesaria = modelos[id_mod].componentes[j].cantidad * pedido.cantidad;
            
            cout << "\nID: " << componentes[id_comp].id + 1 << endl;
            cout << "Componente: " << componentes[id_comp].descripcion << endl;
            cout << "Stock actual: " << componentes[id_comp].stock << endl;
            cout << "Cantidad necesaria: " << cantidad_necesaria << endl;
            cout << "Proveedores:" << endl;

            float menor_precio = FLT_MAX;
            int proveedor_elegido = -1;
            for (int p = 0; p < componentes[id_comp].num_proveedores; p++) {
                cout << " - " << componentes[id_comp].proveedores[p].nombre 
                     << " ( Valor: $" << fixed << setprecision(2) 
                     << componentes[id_comp].proveedores[p].valor_unitario << " )" << endl;
                
                if (componentes[id_comp].proveedores[p].valor_unitario < menor_precio) {
                    menor_precio = componentes[id_comp].proveedores[p].valor_unitario;
                    proveedor_elegido = p;
                }
            }

            if (componentes[id_comp].stock < cantidad_necesaria) {
                cout << "Error: Stock insuficiente para el componente " << id_comp + 1 << endl;
                continue;
            }

            componentes[id_comp].stock -= cantidad_necesaria;
            float costo_componente = menor_precio * cantidad_necesaria;
            costo_pedido += costo_componente;

            cout << "Proveedor elegido: " << componentes[id_comp].proveedores[proveedor_elegido].nombre << endl;
            cout << "Costo del componente: $" << fixed << setprecision(2) << costo_componente << endl;
        }

        pedido.costo = costo_pedido;
        costo_total_pedidos += costo_pedido;
        fwrite(&pedido, sizeof(Pedido), 1, archivo_out);

        cout << "\nCosto total del pedido: $" << fixed << setprecision(2) << costo_pedido << endl;
    }

    fclose(archivo_in);
    fclose(archivo_out);

    cout << "\n=== Resumen de pedidos actualizados ===" << endl;
    archivo_out = fopen(archivo_salida, "rb");
    while (fread(&pedido, sizeof(Pedido), 1, archivo_out) == 1) {
        cout << "ID Pedido: " << pedido.id_pedido << ", ID Modelo: " << pedido.id_modelo + 1 
             << ", Cantidad: " << pedido.cantidad << ", Costo: $" << fixed << setprecision(2) << pedido.costo << endl;
    }
    fclose(archivo_out);

    cout << "\nCosto total de todos los pedidos: $" << fixed << setprecision(2) << costo_total_pedidos << endl;
}

int main() {
    inicializar_datos();
    generar_pedidos("pedidos.dat");
    procesar_pedidos("pedidos.dat", "pedidos_actualizados.dat");
    return 0;
}