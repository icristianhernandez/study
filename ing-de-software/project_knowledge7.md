# Conocimiento del Proyecto: Servicio de Cine en Pseint

## 1. Descripción General

Este proyecto consiste en el desarrollo de un sistema de gestión para un servicio de cine utilizando Pseint. El sistema permitirá a los usuarios realizar todas las operaciones esperadas en una experiencia de cine, desde la consulta de la cartelera y la selección de butacas hasta la compra de entradas y combos de comida.

## 2. Funcionalidades Principales

El sistema contará con las siguientes funcionalidades clave:

* **Gestión de Películas:** Almacenamiento y consulta de información detallada de las películas.
* **Visualización de Cartelera:** Muestra de las películas actualmente en exhibición.
* **Consulta de Horarios y Funciones:** Información sobre los horarios y salas disponibles para cada película.
* **Selección de Butacas:** Interfaz gráfica para la visualización y selección de asientos.
* **Compra de Entradas:** Proceso para adquirir entradas, considerando diferentes precios por edad.
* **Gestión de Pagos:** Soporte para múltiples métodos de pago y monedas.
* **Menú de Comida y Bebida:** Visualización y selección de combos, bebidas y comidas.
* **Métricas de Sala:** Generación de estadísticas sobre la venta de butacas.

## 3. Características Detalladas

### 3.1. Gestión de Películas

* El sistema manejará un número N de películas.
* Cada película tendrá información asociada como:
  * Título
  * Sinopsis
  * Etc. (otros datos relevantes como duración, director, actores)
* Las películas podrán diferenciarse por:
  * Género
  * Edad mínima recomendada

### 3.2. Cartelera y Horarios

* Se mostrará una cartelera con las películas actuales en exhibición.
* Se podrán consultar los horarios y las funciones disponibles para cada película y sala.

### 3.3. Selección de Butacas

* Se implementará una interfaz que represente la distribución de butacas de la sala en forma de matriz rectangular.
* Esta interfaz mostrará claramente las butacas disponibles y las no disponibles (ocupadas).

### 3.4. Compra de Entradas

* **Precios:**
  * Niños: $1.00
  * Adulto Mayor: $1.50
  * Adultos: $2.00
* **Restricción de Compra:** Solo las personas mayores de edad podrán adquirir las entradas.

### 3.5. Métodos de Pago

* Se aceptarán los siguientes métodos de pago:
  * En caja (efectivo o punto de venta)
  * Transferencia bancaria
  * Pago móvil
* **Manejo de Monedas:**
  * El sistema operará con la moneda local (Bolívares) y Dólares.
  * Se implementará un sistema para manejar las tasas de cambio correspondientes.

### 3.6. Menú de Comida y Bebida

* Se incluirá un menú detallado con:
  * **Combos:** Descripción de qué incluyen y sus precios.
  * **Bebidas:** Listado de bebidas disponibles y sus precios.
  * **Comidas:** Listado de opciones de comida (snacks, etc.) y sus precios.

### 3.7. Métricas de Sala

El sistema proporcionará las siguientes métricas sobre cada sala de cine:

* Cantidad de butacas vendidas en la fila más vendida.
* Cantidad de butacas vendidas en la diagonal principal de la matriz de butacas.
* Cantidad de butacas vendidas en columnas cuyo índice pertenezca a la serie de Fibonacci (considerando la primera columna como índice 1 o 0 según se defina).
* Cantidad de butacas vendidas en cada fila.
* Distribución de la cantidad de butacas vendidas por tipo de cliente:
  * Adulto Mayor
  * Adultos
  * Niños
* Cantidad de butacas vendidas en filas cuyo número de fila sea un número primo.

## 4. Tecnología Utilizada

* **Lenguaje de Programación:** Pseint

## 5. Consideraciones Adicionales

* Se deberá definir la estructura de datos para almacenar la información de las películas, funciones, salas, butacas, ventas, etc.
* La interfaz de usuario, aunque en Pseint, deberá ser lo más clara e intuitiva posible.
* Se debe prestar atención a la validación de entradas del usuario para evitar

