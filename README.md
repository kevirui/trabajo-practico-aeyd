# Procesamiento de Pedidos de Modelos y Componentes

## Descripción
Este programa en C++ permite gestionar el procesamiento de pedidos de modelos de productos, verificando la disponibilidad de componentes y calculando el costo total basado en los proveedores más económicos.

## Funcionalidades
- Carga de modelos de productos con sus componentes.
- Asociación de componentes con proveedores y sus precios.
- Registro de pedidos en un archivo binario (`pedidos.dat`).
- Lectura y procesamiento de pedidos:
  - Verificación de stock antes de aceptar un pedido.
  - Cálculo del costo total basado en el proveedor más barato.
  - Reducción del stock de componentes en caso de aceptación del pedido.
  - Rechazo de pedidos si no hay stock suficiente.
- Visualización de pedidos con su costo final o motivo de rechazo.

## Estructuras de Datos
### `struct Modelo`
Representa un modelo de producto y los componentes asociados.
```cpp
struct Modelo {
    int ID_modelo;
    char descripcion[30];
    nodoModelos* listaDeComponentes;
};
```

### `struct Componente`
Representa un componente y sus proveedores.
```cpp
struct Componente {
    int ID;
    char descripcion[30];
    int stock;
    NodoProveedores* listaProveedores;
};
```

### `struct Proveedor`
Representa un proveedor y el costo de un componente.
```cpp
struct Proveedor {
    int ID_proveedor;
    float valor_unitario;
};
```

### `struct Pedido`
Representa un pedido con la cantidad requerida de un modelo.
```cpp
struct Pedido {
    int ID_pedido;
    int ID_linea;
    int ID_modelo;
    int cantidad;
};
```

## Archivo de Pedidos (`pedidos.dat`)
El archivo binario almacena los pedidos en formato estructurado. El programa lee estos datos y los procesa.

## Requisitos
- Compilador C++ compatible con C++11 o superior.
- Uso de MSYS2, MinGW o cualquier entorno compatible con C++.

## Ejecución
1. Compilar el programa:
   ```sh
   g++ main.cpp -o pedidos
   ```
2. Ejecutar:
   ```sh
   ./pedidos
   ```

## Notas
- Se deben cargar previamente los modelos y componentes en la estructura de datos.
- El programa debe ejecutarse en un entorno donde se pueda leer y escribir en archivos binarios.

## Autores
Desarrollado por [Tu Nombre].

