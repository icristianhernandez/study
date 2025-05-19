# Especificaciones del Proyecto: Servicio de Cine en Pseint

Este documento describe las características y funcionalidades esperadas para el proyecto, que consiste en un servicio de cine implementado en Pseint. Se abordan aspectos como la visualización de cartelera, manejo de butacas, compra de entradas, gestión de salas y métodos de pago.

## Funcionalidades Principales

- **Gestión de Películas**  
    - El sistema debe manejar N películas.
    - Cada película contará con información descriptiva (título, sinopsis, etc.).
    - Las películas pueden tener formatos variados según:
        - Género.
        - Edad mínima requerida para su visualización.

- **Cartelera y Horarios**  
    - Mostrar la cartelera con las películas actuales.
    - Visualización de horarios y funciones disponibles por película.

- **Interfaz para Gestión de Butacas**  
    - Distribución de butacas en forma de matriz rectangular.
    - Visualización de butacas disponibles y no disponibles.

- **Métricas de Ventas y Distribución de Butacas**  
    - Número de butacas vendidas en:
        - La fila más vendida.
        - La diagonal principal de la sala.
        - Columnas que correspondan a la serie de Fibonacci.
        - Cada fila en general.
    - Distribución de ventas según demografía:
        - Adultos mayores.
        - Adultos.
        - Niños.
    - Total de butacas vendidas en las filas cuyo número sea primo.

## Precios y Restricciones de Compra

- **Precios de las entradas**  
    - Niños: $1.
    - Adultos mayores: $1.5.
    - Adultos: $2.
- **Restricción**  
    - Las entradas solo pueden ser adquiridas por personas mayores.

## Métodos de Pago

- **Opciones disponibles**  
    - Pago en caja.
    - Transferencia.
    - Pago móvil.
- **Monedas soportadas**  
    - Moneda local (bolívares).
    - Dólares (con tasa BCV).

## Menús Adicionales

- **Combos**
- **Bebidas**
- **Comidas**  
    Cada uno con sus respectivos precios y componentes.

