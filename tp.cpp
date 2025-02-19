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

Modelo modelos[50];
Componente componentes[1000];
int num_modelos = 0, num_componentes = 0;

void cargarDatosPrueba() {
    modelos[0] = {1, "Modelo Deportivo", 1500.0, "verano", {{1000, 2}, {1001, 1}}, 2};
    modelos[1] = {2, "Modelo Invierno", 2000.0, "invierno", {{1002, 3}}, 1};
    num_modelos = 2;

    componentes[0] = {1000, "Cordones", {{1, "Proveedor A", 10.0}, {2, "Proveedor B", 9.5}}, 2, 50};
    componentes[1] = {1001, "Suela", {{3, "Proveedor C", 25.0}}, 1, 30};
    componentes[2] = {1002, "Plantilla", {{4, "Proveedor D", 5.0}}, 1, 100};
    num_componentes = 3;
}

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
        {2, 2, "2025-02-19", 2, 1, 0.0}
    };

    fwrite(pedidos, sizeof(Pedido), 2, archivo);
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

	fseek(archivo, 0, SEEK_CUR);
      }
    }
    
    fclose(archivo);
    cout << "Costo total de todos los pedidos: " << costo_total_pedidos << endl;
}

int main() {
    cargarDatosPrueba();
    generarArchivoPedido("pedidos.dat");
    procesar_pedidos("pedidos.dat");
    return 0;
}
