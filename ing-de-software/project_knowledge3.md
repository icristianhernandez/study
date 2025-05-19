# Project Knowledge: Servicio de Cine en PSeInt

## 1. Descripción General del Proyecto

El proyecto consiste en el desarrollo de un servicio de cine simulado utilizando PSeInt. Este sistema permitirá a los usuarios realizar todas las operaciones típicas de un cine, desde la consulta de la cartelera y la información de las películas, hasta la selección de asientos, compra de entradas y combos de alimentos. El sistema se enfocará en la lógica de negocio y la gestión de datos, adaptándose a las capacidades y limitaciones de PSeInt.

## 2. Objetivos Principales

* Simular la experiencia de usuario de un servicio de cine.
* Gestionar la información de películas, funciones, salas y ventas.
* Implementar la lógica de selección y reserva de butacas.
* Calcular métricas de ventas y ocupación de las salas.
* Manejar diferentes tipos de precios y métodos de pago, incluyendo conversión de moneda.
* Ofrecer un menú de comidas, bebidas y combos.

## 3. Funcionalidades Detalladas

### 3.1. Gestión de Películas

* **Almacenamiento de Películas:** El sistema deberá manejar una cantidad 'N' de películas.
* **Información por Película:** Cada película contará con:
    * Título
    * Sinopsis
    * Género
    * Clasificación por edad (ej: ATP, +13, +16, +18)
    * Duración
    * Formato (ej: 2D, 3D)
    * Director
    * Reparto principal
    * (Otros campos relevantes que se definan)
* **Diferenciación de Películas:** Las películas podrán ser filtradas o agrupadas por:
    * Género
    * Edad mínima recomendada

### 3.2. Cartelera y Funciones

* **Visualización de Cartelera:** Mostrar las películas que se encuentran actualmente en exhibición.
* **Horarios y Funciones:**
    * Para cada película en cartelera, mostrar los horarios disponibles.
    * Cada función estará asociada a una sala específica y un horario.

### 3.3. Gestión de Butacas

* **Interfaz de Sala:**
    * Representación visual de la distribución de butacas de una sala en forma de matriz rectangular.
    * Las butacas deberán mostrar su estado:
        * Disponibles
        * No disponibles (ocupadas o bloqueadas)
* **Selección de Butacas:** Permitir al usuario seleccionar una o más butacas disponibles para su compra.

### 3.4. Métricas de Salas de Cine

El sistema deberá ser capaz de calcular y mostrar las siguientes métricas por sala para cada función o al final del día:

* **Fila más Vendida:** Identificar la fila con la mayor cantidad de butacas vendidas y el número de estas.
* **Diagonal Principal:** Cantidad de butacas vendidas en la diagonal principal de la matriz de la sala (si aplica, considerando salas cuadradas o la diagonal más larga posible).
* **Columnas Fibonacci:** Cantidad total de butacas vendidas en columnas cuyos números de índice pertenezcan a la serie de Fibonacci (ej: columnas 1, 2, 3, 5, 8,...).
* **Ventas por Fila:** Cantidad de butacas vendidas para cada fila de la sala.
* **Distribución Demográfica:**
    * Cantidad de butacas vendidas a adultos mayores.
    * Cantidad de butacas vendidas a adultos.
    * Cantidad de butacas vendidas a niños.
* **Filas Primas:** Cantidad total de butacas vendidas en filas cuyos números de índice sean números primos (ej: filas 2, 3, 5, 7, 11,...).

### 3.5. Precios y Venta de Entradas

* **Precios Diferenciados:**
    * Niños: $1.00 USD
    * Adulto Mayor: $1.50 USD
    * Adultos: $2.00 USD
* **Restricción de Compra:** Las entradas solo pueden ser adquiridas/procesadas en el sistema por una persona que se identifique como mayor de edad (quien realiza la transacción), aunque las entradas puedan ser para niños.
* **Proceso de Compra:** Guiar al usuario a través de la selección de película, función, butacas y tipo de entrada por demografía.

### 3.6. Métodos de Pago

* **Opciones de Pago:**
    * Pago en caja (simulado)
    * Transferencia bancaria (simulado, se registrará la referencia)
    * Pago móvil (simulado, se registrará la referencia)
* **Manejo de Moneda:**
    * El sistema operará con precios base en dólares (USD).
    * Deberá permitir mostrar los montos y procesar pagos en la moneda local (Bolívares - VES).
    * Se deberá implementar un mecanismo para ingresar y utilizar una tasa de cambio VES/USD, la cual podría ser actualizada periódicamente (simulado).

### 3.7. Menú de Alimentos y Bebidas

* **Menú de Combos:**
    * Listado de combos disponibles (ej: Combo 1: Cotufa mediana + Refresco pequeño).
    * Precio de cada combo.
    * Descripción del contenido de cada combo.
* **Menú de Bebidas:**
    * Listado de bebidas individuales (ej: Agua, Refresco, Jugo).
    * Precio de cada bebida.
    * Tamaños disponibles (si aplica).
* **Menú de Comidas:**
    * Listado de alimentos individuales (ej: Cotufas, Nachos, Tequeños, Hot Dogs).
    * Precio de cada alimento.
    * Tamaños disponibles (si aplica).
* **Selección y Adición al Pedido:** Permitir al usuario agregar ítems del menú a su compra total.

## 4. Consideraciones Tecnológicas

* **Plataforma:** PSeInt. Todas las interfaces y lógica se implementarán dentro de las capacidades de este pseudointérprete.
* **Estructuras de Datos:** Se utilizarán arreglos (vectores y matrices) para gestionar la información de películas, salas, butacas, ventas, etc.
* **Interfaz de Usuario:** Basada en texto y menús navegables mediante entrada por teclado, típico de PSeInt.

## 5. Flujo General de Usuario (Ejemplo)

1.  Usuario inicia el programa.
2.  Se muestra menú principal: Ver Cartelera, Comprar Entradas, Ver Mis Compras (opcional), Salir.
3.  **Ver Cartelera:**
    * Listar películas.
    * Seleccionar película para ver detalles (sinopsis, horarios, etc.).
4.  **Comprar Entradas:**
    * Seleccionar película.
    * Seleccionar función (horario y sala).
    * Mostrar distribución de butacas de la sala.
    * Usuario selecciona butacas.
    * Usuario indica cantidad y tipo de entradas (niño, adulto, adulto mayor) para las butacas seleccionadas.
    * Sistema calcula subtotal de entradas.
    * **Menú de Alimentos/Bebidas (Opcional):**
        * Preguntar si desea agregar algo del menú.
        * Mostrar menú de combos, bebidas, comidas.
        * Usuario selecciona ítems.
        * Sistema calcula subtotal de alimentos/bebidas.
    * Sistema calcula total general.
    * **Selección de Método de Pago:**
        * Mostrar opciones de pago.
        * Si es moneda local, mostrar monto en VES (aplicando tasa de cambio).
        * Usuario selecciona método y confirma pago (simulado).
    * Sistema registra la venta, actualiza disponibilidad de butacas y genera un comprobante (simulado).
5.  Salir.

## 6. Posibles Extensiones (Fuera del Alcance Inicial)

* Sistema de puntos o fidelidad.
* Reservas online con tiempo límite para pago.
* Gestión de usuarios registrados.
* Reportes de ventas más avanzados.
* Módulo de administración para cargar películas, actualizar precios, etc.