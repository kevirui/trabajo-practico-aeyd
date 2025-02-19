#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cfloat>

#define MAX_MODELOS 50
#define MAX_COMPONENTES 1000

struct Proveedor {
    int id;
    char nombre[100];
    float valor_unitario;
};

struct Componente {
    int id;
    char descripcion[100];
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
    char descripcion[100];
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

Modelo modelos[MAX_MODELOS];
Componente componentes[MAX_COMPONENTES];
int num_modelos = 0, num_componentes = 0;

void cargar_datos_prueba() {
    // Cargar algunos modelos de prueba
    modelos[0] = {1, "Modelo Deportivo", 1500.0, "verano", {{1000, 2}, {1001, 1}}, 2};
    modelos[1] = {2, "Modelo Invierno", 2000.0, "invierno", {{1002, 3}}, 1};
    num_modelos = 2;

    // Cargar algunos componentes de prueba
    componentes[0] = {1000, "Cordones", {{1, "Proveedor A", 10.0}, {2, "Proveedor B", 9.5}}, 2, 50};
    componentes[1] = {1001, "Suela", {{3, "Proveedor C", 25.0}}, 1, 30};
    componentes[2] = {1002, "Plantilla", {{4, "Proveedor D", 5.0}}, 1, 100};
    num_componentes = 3;
}

void actualizar_stock_y_costo(Pedido &pedido) {
    for (int i = 0; i < num_modelos; i++) {
        if (modelos[i].id == pedido.id_modelo) {
            float costo_total = 0;
            std::cout << "\nProcesando pedido ID " << pedido.id_pedido << " (Modelo: " << modelos[i].descripcion << ")\n";
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
                            std::cout << "  - " << componentes[k].descripcion << ": Se usaron " << cantidad_necesaria << " unidades. Stock restante: " << componentes[k].stock << "\n";
                        } else {
                            std::cout << "  - Stock insuficiente para " << componentes[k].descripcion << " (Requiere: " << cantidad_necesaria << ", Disponible: " << componentes[k].stock << ")\n";
                        }
                        
                        costo_total += menor_precio * cantidad_necesaria;
                    }
                }
            }
            pedido.costo = costo_total;
            std::cout << "  -> Costo total del pedido ID " << pedido.id_pedido << ": " << costo_total << "\n";
            return;
        }
    }
}

void procesar_pedidos(const char *archivo_pedidos) {
    FILE *file = fopen(archivo_pedidos, "r+b");
    if (!file) {
        std::cout << "Error al abrir el archivo de pedidos.\n";
        return;
    }
    
    Pedido pedido;
    float costo_total_pedidos = 0;
    
    while (fread(&pedido, sizeof(Pedido), 1, file)) {
        actualizar_stock_y_costo(pedido);
        costo_total_pedidos += pedido.costo;
        fseek(file, -sizeof(Pedido), SEEK_CUR);
        fwrite(&pedido, sizeof(Pedido), 1, file);
    }
    
    fclose(file);
    std::cout << "\nCosto total de todos los pedidos: " << costo_total_pedidos << "\n";
}

int main() {
    cargar_datos_prueba();
    procesar_pedidos("pedidos.dat");
    return 0;
}
