#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cfloat>
using namespace std;

struct Proveedor {
    int id;
    char nombre[100 + 1];
    float valor_unitario;
};

struct Componente {
    int id;
    char descripcion[100 + 1];
    Proveedor proveedores[10]; // Máximo 10 proveedores por componente
    int num_proveedores;
    int stock;
};

struct ComponenteModelo {
    int id_accesorio;
    int cantidad;
};

struct Modelo {
    int id;
    char descripcion[100 + 1];
    float precio_base;
    char temporada[10]; // "verano" o "invierno"
    ComponenteModelo componentes[10]; // Máximo 10 componentes por modelo
    int num_componentes;
};

struct Pedido {
    int id_pedido;
    int id_linea;
    char fecha[11];
    int id_modelo;
    int cantidad;
    float costo;
};

Modelo modelos[50 + 1];
Componente componentes[1000 + 1];

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

string temporadas[] = {"verano", "invierno"};
string proveedores[] = {"Proveedor A", "Proveedor B", "Proveedor C"};

int num_modelos = 50, num_componentes = 20;

void generarArchivoPedido(const char *archivo_pedidos) {
    FILE *archivo = fopen(archivo_pedidos, "rb");
    if (archivo) {
        fclose(archivo);
        return; // El archivo ya existe, no es necesario generarlo
    }
    
    archivo = fopen(archivo_pedidos, "wb");
    if (!archivo) {
        cout << "Error al crear el archivo de pedidos."<< endl;
        return;
    }

    Pedido pedidos[] = {
        {1, 1, "2025-02-19", 1, 2, 0.0},
        {2, 2, "2025-02-19", 2, 1, 0.0},
	{3, 3, "2025-02-19", 3, 3, 0.0},
	{3, 4, "2025-02-19", 4, 4, 0.0}
    };

    fwrite(pedidos, sizeof(Pedido), 4, archivo);
    fclose(archivo);
    cout << "Archivo de pedidos generado correctamente."<< endl;
}

void actualizar_stock_y_costo(Pedido &pedido) {
    for (int i = 0; i < num_modelos; i++) {
        if (modelos[i].id == pedido.id_modelo) {
            float costo_total = 0;
	    cout<< endl;
            cout << "Procesando pedido ID " << pedido.id_pedido << " (Modelo: " << modelos[i].descripcion << ")"<< endl;
            for (int j = 0; j < modelos[i].num_componentes; j++) {
                int id_componente = modelos[i].componentes[j].id_accesorio;
                int cantidad_necesaria = modelos[i].componentes[j].cantidad * pedido.cantidad;
                
                for (int k = 0; k < num_componentes; k++) {
                    if (componentes[k].id == id_componente) {
                        float menor_precio = FLT_MAX;
                        for (int p = 0; p < componentes[k].num_proveedores; p++) {
                            if (componentes[k].proveedores[p].valor_unitario < menor_precio) {
                                menor_precio = componentes[k].proveedores[p].valor_unitario;
                            }
                        }
                        
                        if (componentes[k].stock >= cantidad_necesaria) {
                            componentes[k].stock -= cantidad_necesaria;
                            cout << "  - " << componentes[k].descripcion << ": Se usaron " << cantidad_necesaria << " unidades. Stock restante: " << componentes[k].stock << endl;
                        } else {
                            cout << "  - Stock insuficiente para " << componentes[k].descripcion << " (Requiere: " << cantidad_necesaria << ", Disponible: " << componentes[k].stock << ")"<< endl;
                        }
                        
                        costo_total += menor_precio * cantidad_necesaria;
                    }
                }
            }
            pedido.costo = costo_total;
            cout << "  -> Costo total del pedido ID " << pedido.id_pedido << ": " << costo_total << endl;
            return;
        }
    }
}

void procesar_pedidos(const char *archivo_pedidos) {
    FILE *archivo = fopen(archivo_pedidos, "r+b");
    if (!archivo) {
        cout << "Error al abrir el archivo de pedidos."<< endl;
        return;
    }
    
    Pedido pedido;
    float costo_total_pedidos = 0;
    
    while (fread(&pedido, sizeof(Pedido), 1, archivo) == 1) {
      if(pedido.id_modelo > 0){
        actualizar_stock_y_costo(pedido);
        costo_total_pedidos += pedido.costo;

        fseek(archivo, -static_cast<long>(sizeof(Pedido)), SEEK_CUR);
        fwrite(&pedido, sizeof(Pedido), 1, archivo);
      }
    }
    
    fclose(archivo);
    cout << "Costo total de todos los pedidos: " << costo_total_pedidos << endl;
}

int main() {
  // Cargar modelos
    for(int i=0; i<num_modelos; i++){
      modelos[i].id = i+1;
      strcpy(modelos[i].descripcion, nombreMod[i].c_str());
      modelos[i].precio_base = 1000 + i*100;
      strcpy(modelos[i].temporada, temporadas[i%2].c_str());
      modelos[i].num_componentes = 10;
      for(int j=0; j<10; j++){
	modelos[i].componentes[j].id_accesorio = j + 1;
	modelos[i].componentes[j].cantidad = 1 + (i%3);
      }
    }

    // Cargar componentes
    for(int i=0; i<num_componentes; i++){
      componentes[i].id = i+1;
      strcpy(componentes[i].descripcion, nombreComp[i%20].c_str());
      componentes[i].stock = 100 + i;
      componentes[i].num_proveedores = 3;
      for(int j=0; j<3; j++){
	componentes[i].proveedores[j].id = j+1;
	strcpy(componentes[i].proveedores[j].nombre, proveedores[j].c_str());
	componentes[i].proveedores[j].valor_unitario = 10 + j;
      }
    }
    cout<< "Datos de prueba cargados correctamente."<< endl;
    
    generarArchivoPedido("pedidos.dat");

    FILE *archivo = fopen("pedidos.dat", "rb");
    if (!archivo) {
      cout << "Error al abrir el archivo de pedidos."<< endl;
      return 1;
    }

    Pedido pedido;
    cout << "Pedidos en el archivo:" << endl;
    while(fread(&pedido, sizeof(Pedido), 1, archivo) == 1){
      cout<< "ID Pedido: "<< pedido.id_pedido<< ", Modelo: "<< pedido.id_modelo<< ", Cantidad: "<< pedido.cantidad<< endl;
    }
    fclose(archivo);

    procesar_pedidos("pedidos.dat");
    return 0;
}
