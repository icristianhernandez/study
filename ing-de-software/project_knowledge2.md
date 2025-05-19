# Proyecto: Servicio de Cine en PSeInt - Especificaciones

## 1. Descripción General del Proyecto

El proyecto consiste en desarrollar un sistema de gestión para un servicio de cine utilizando PSeInt. El sistema permitirá a los usuarios realizar todas las operaciones comunes esperadas en una aplicación de cine, desde consultar la cartelera y seleccionar asientos hasta comprar entradas y combos.

**Plataforma de Desarrollo:** PSeInt

## 2. Funcionalidades Principales

### 2.1. Gestión de Películas

* **Catálogo de Películas:**
    * El sistema debe poder almacenar y gestionar un número N de películas.
    * **Información por Película:** Cada película deberá contar con los siguientes datos:
        * Título
        * Sinopsis
        * Género
        * Clasificación por edad (ej: Apta para todo público, +12, +18)
        * Duración
        * Director
        * Reparto principal
        * Formato (ej: 2D, 3D - si aplica)
        * Idioma y subtítulos
* **Diferenciación y Filtros:**
    * Las películas podrán ser filtradas o categorizadas según su información, como por ejemplo:
        * Género (acción, comedia, drama, etc.)
        * Edad mínima requerida.

### 2.2. Cartelera y Funciones

* **Visualización de Cartelera:**
    * Mostrar las películas que se encuentran actualmente en exhibición.
    * Para cada película en cartelera, se mostrará su información relevante (título, sinopsis breve, clasificación).
* **Horarios y Funciones:**
    * Mostrar los horarios y las salas disponibles para cada película en cartelera.
    * Indicar claramente la fecha, hora de inicio y sala de cada función.

### 2.3. Sistema de Selección de Butacas

* **Interfaz Gráfica (Representación):**
    * Se debe presentar una interfaz que muestre la distribución de las butacas de la sala seleccionada.
    * La distribución será en forma de matriz rectangular.
    * **Estado de Butacas:**
        * Las butacas disponibles deben ser claramente distinguibles de las no disponibles/ocupadas.
        * El usuario podrá seleccionar una o más butacas disponibles.

### 2.4. Compra de Entradas

* **Proceso de Compra:**
    * Permitir al usuario seleccionar la película, función y butacas.
    * Proceder al pago de las entradas seleccionadas.
* **Precios y Demografía:**
    * Los precios de las entradas variarán según la edad del espectador:
        * Niños: $1.00 USD
        * Adulto Mayor: $1.50 USD
        * Adultos: $2.00 USD
    * **Restricción de Compra:** Las entradas solo podrán ser adquiridas por personas mayores de edad. El sistema deberá contemplar cómo manejar esta restricción (ej. solicitando confirmación o datos del comprador).

### 2.5. Métodos de Pago

* **Opciones de Pago:**
    * El sistema deberá ofrecer múltiples métodos de pago:
        * Pago en caja (simulado, para efectos del sistema en PSeInt)
        * Transferencia bancaria
        * Pago móvil
* **Gestión de Moneda:**
    * El sistema debe poder manejar precios y pagos en dos monedas:
        * Moneda local (Bolívares - VES)
        * Dólares (USD)
    * **Tasa de Cambio:** Se debe implementar un mecanismo para definir y utilizar una tasa de cambio para las conversiones entre bolívares y dólares. Esta tasa podría ser configurable.

### 2.6. Menú de Alimentos y Bebidas (Combos)

* **Visualización de Menús:**
    * El sistema debe incluir un menú de combos, un menú de bebidas y un menú de comidas individuales.
* **Información Detallada:**
    * Para cada ítem del menú (combo, bebida, comida):
        * Nombre del producto
        * Descripción (qué contiene, ej: "Combo Mediano: Cotufas medianas + 1 Refresco Mediano")
        * Precio (expresado en ambas monedas o con la conversión visible).
* **Integración con la Compra:**
    * Opcional (a definir): Permitir agregar ítems del menú al proceso de compra de entradas.

### 2.7. Métricas y Estadísticas de Sala (Interfaz Administrativa o de Reportes)

El sistema deberá ser capaz de calcular y mostrar las siguientes métricas para cada sala de cine y función:

* **Fila Más Vendida:**
    * Identificar y mostrar cuántas butacas se vendieron en la fila que tuvo la mayor cantidad de ventas.
* **Ventas en Diagonal Principal:**
    * Calcular la cantidad de butacas vendidas que se encuentran en la diagonal principal de la matriz de la sala (asumiendo una matriz cuadrada o la diagonal principal de la submatriz cuadrada más grande posible si es rectangular).
* **Ventas en Columnas Fibonacci:**
    * Calcular la cantidad total de butacas vendidas en columnas cuyos índices (empezando desde 0 o 1, a definir) pertenezcan a la serie de Fibonacci (ej: columnas 0, 1, 2, 3, 5, 8,...).
* **Ventas por Fila:**
    * Mostrar la cantidad de butacas vendidas para cada fila de la sala.
* **Distribución Demográfica de Ventas:**
    * Mostrar la distribución de la cantidad de butacas vendidas, desglosada por tipo de entrada:
        * Cantidad de entradas vendidas a adultos mayores.
        * Cantidad de entradas vendidas a adultos.
        * Cantidad de entradas vendidas a niños.
* **Ventas en Filas Primas:**
    * Calcular la cantidad de butacas vendidas en filas cuyos números de índice (empezando desde 0 o 1, a definir) sean números primos (ej: filas 2, 3, 5, 7, 11,...).

## 3. Consideraciones Adicionales (PSeInt)

* **Interfaz de Usuario:** Dado que PSeInt es principalmente para lógica algorítmica, la "interfaz" será basada en texto y menús de consola. La representación de la matriz de butacas deberá ser creativa usando caracteres.
* **Persistencia de Datos:** PSeInt no maneja bases de datos complejas. Se podría simular la persistencia guardando y leyendo datos desde arreglos o estructuras de datos internas del programa durante su ejecución. Para persistencia entre ejecuciones, se podría considerar la exportación/importación a archivos de texto si PSeInt lo permite de forma sencilla o si se complementa con alguna herramienta externa (lo cual excede PSeInt puro).
* **Modularidad:** Se recomienda estructurar el código en PSeInt utilizando subprocesos (funciones/procedimientos) para una mejor organización y mantenibilidad.

## 4. Estructura de Datos Sugerida (Conceptual)

* **Películas:** Arreglo de registros/estructuras, donde cada registro contiene (título, sinopsis, género, etc.).
* **Funciones:** Arreglo de registros, donde cada registro podría contener (ID_Pelicula, ID_Sala, fecha, hora, matriz_butacas).
* **Salas:** Arreglo de registros, con (ID_Sala, capacidad_filas, capacidad_columnas).
* **Ventas:** Arreglo de registros, con (ID_Funcion, fila, columna, tipo_entrada, precio_pagado, metodo_pago).
* **Combos/Productos:** Arreglo de registros con (nombre, descripcion, precio_ves, precio_usd).