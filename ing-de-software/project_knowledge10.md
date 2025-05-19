# Conocimiento del Proyecto: Servicio de Cine en Pseint

## Generalidades del Proyecto

Este proyecto consiste en el desarrollo de un servicio de cine utilizando Pseint. El sistema permitirá a los usuarios realizar todas las acciones esperables en una aplicación de este tipo, desde consultar la cartelera hasta comprar entradas y combos.

## Películas

### Información de las Películas
El sistema manejará N cantidad de películas, cada una con la siguiente información:
* Título
* Sinopsis
* Duración
* Clasificación (ej. PG, R, G)
* Género
* Director
* Reparto principal
* Idioma
* Formato (ej. 2D, 3D)

### Categorización de Películas
Las películas podrán ser diferenciadas o filtradas por:
* Género (ej. Acción, Comedia, Drama, Ciencia Ficción, etc.)
* Edad mínima recomendada.

## Cartelera y Funciones

* **Visualización de Cartelera:** Se mostrarán las películas actualmente en exhibición.
* **Horarios y Funciones:** Se detallarán los horarios y las salas disponibles para cada película.

## Interfaz de Usuario

### Distribución de Butacas
* Se presentará una interfaz gráfica (simulada en Pseint) con la distribución de las butacas en forma de matriz rectangular.
* Se indicarán claramente las butacas disponibles y las no disponibles (ocupadas).

### Métricas por Sala de Cine
Se mostrarán las siguientes métricas para cada sala:
* Cantidad de butacas vendidas en la fila más vendida.
* Cantidad de butacas vendidas en la diagonal principal de la matriz de butacas.
* Cantidad de butacas vendidas en columnas cuyo índice pertenezca a la serie de Fibonacci.
* Cantidad de butacas vendidas en cada fila.
* Distribución de la cantidad de butacas vendidas por tipo de espectador: adulto mayor, adulto y niño.
* Cantidad de butacas vendidas en filas cuyo índice sea un número primo.

## Precios y Adquisición de Entradas

### Precios por Demografía
Los precios de las entradas variarán según la edad del espectador:
* Niños: $1.00
* Adulto Mayor: $1.50
* Adultos: $2.00

### Restricciones de Compra
* Las entradas solo podrán ser adquiridas por personas mayores de edad.

## Métodos de Pago

### Opciones de Pago
Se incluirán los siguientes métodos de pago:
* Pago en caja (efectivo o tarjeta).
* Transferencia bancaria.
* Pago móvil.

### Manejo de Moneda
* El sistema deberá adaptarse para procesar pagos en la moneda local (bolívares) y en dólares.
* Se implementará un sistema para manejar las tasas de cambio correspondientes.

## Menú de Alimentos y Bebidas

Se incluirán los siguientes menús con sus respectivos precios y contenido:
* **Menú de Combos:** Diferentes combinaciones de palomitas, bebidas y snacks.
* **Menú de Bebidas:** Gaseosas, agua, jugos, etc.
* **Menú de Comidas:** Palomitas de maíz de diferentes tamaños y sabores, nachos, hot dogs, etc.