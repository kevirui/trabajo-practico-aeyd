## Descripción General
Este programa simula un sistema de gestión para una fábrica de zapatos. Calcula la cantidad de accesorios necesarios para la producción basándose en los pedidos recibidos, maneja el inventario de componentes, y calcula los costos considerando múltiples proveedores.

## Estructura del Código

### Estructuras de Datos
1. `Proveedor`: Almacena información de cada proveedor.
   - `id`: Identificador único del proveedor.
   - `nombre`: Nombre del proveedor.
   - `valor_unitario`: Precio por unidad del componente.

2. `Componente`: Representa cada accesorio o parte del zapato.
   - `id`: Identificador único del componente.
   - `descripcion`: Descripción del componente.
   - `proveedores`: Array de proveedores para este componente.
   - `num_proveedores`: Número de proveedores disponibles.
   - `stock`: Cantidad disponible en inventario.

3. `ComponenteModelo`: Relaciona un componente con un modelo de zapato.
   - `id_accesorio`: ID del componente.
   - `cantidad`: Cantidad necesaria para el modelo.

4. `Modelo`: Representa un modelo de zapato.
   - `id`: Identificador único del modelo.
   - `descripcion`: Descripción del modelo.
   - `precio_base`: Precio base del modelo.
   - `temporada`: Temporada del modelo (verano/invierno).
   - `componentes`: Array de ComponenteModelo.
   - `num_componentes`: Número de componentes en el modelo.

5. `Pedido`: Representa un pedido de zapatos.
   - `id_pedido`: Identificador único del pedido.
   - `id_linea`: Identificador de línea en el pedido.
   - `id_modelo`: ID del modelo de zapato.
   - `fecha`: Fecha del pedido.
   - `cantidad`: Cantidad de zapatos solicitados.
   - `costo`: Costo total del pedido (calculado por el programa).

### Funciones Principales

1. `inicializar_datos()`
   - Propósito: Genera datos de ejemplo para modelos y componentes.
   - Proceso:
     - Inicializa componentes con descripciones, stock y proveedores aleatorios.
     - Crea modelos de zapatos con descripciones, precios base y componentes aleatorios.

2. `mostrar_componentes()`
   - Propósito: Muestra la información de todos los componentes.
   - Proceso: Itera sobre el array de componentes y muestra sus detalles.

3. `generar_pedidos(const char *archivo_pedidos)`
   - Propósito: Crea un archivo binario con pedidos de ejemplo.
   - Proceso: Genera 5 pedidos aleatorios y los escribe en el archivo.

4. `procesar_pedidos(const char *archivo_entrada, const char *archivo_salida)`
   - Propósito: Procesa los pedidos, calcula costos y actualiza el inventario.
   - Proceso:
     - Lee cada pedido del archivo de entrada.
     - Para cada pedido:
       - Calcula el costo base multiplicando el precio base del modelo por la cantidad.
       - Para cada componente del modelo:
         - Muestra información detallada del componente y sus proveedores.
         - Selecciona el proveedor con el precio más bajo.
         - Actualiza el stock del componente.
         - Añade el costo del componente al costo total del pedido.
     - Actualiza el pedido con el costo calculado.
     - Escribe el pedido actualizado en el archivo de salida.
     - Muestra un resumen de todos los pedidos procesados.

### Flujo del Programa

1. Inicialización:
   - Se generan datos de ejemplo para componentes y modelos.

2. Generación de Pedidos:
   - Se crea un archivo con pedidos de ejemplo.

3. Procesamiento de Pedidos:
   - Se lee cada pedido del archivo.
   - Para cada pedido, se calculan los costos y se actualizan los stocks.
   - Se muestra información detallada de cada componente y proveedor.
   - Se selecciona el proveedor más económico para cada componente.
   - Se actualiza el archivo de pedidos con los costos calculados.

4. Resumen Final:
   - Se muestra un resumen de todos los pedidos procesados.
   - Se calcula y muestra el costo total de todos los pedidos.
