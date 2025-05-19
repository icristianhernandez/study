# project_knowledge.md

## Descripción General

Este proyecto es un **servicio de cine desarrollado en Pseint** que simula la experiencia completa de compra y gestión de entradas, visualización de cartelera, selección de butacas y adquisición de combos, bebidas y comidas. El sistema está diseñado para ofrecer una experiencia interactiva y detallada, cubriendo todas las funcionalidades esperadas en un cine moderno.

---

## Funcionalidades Principales

### 1. Gestión de Películas

- **N Películas**: El sistema permite gestionar múltiples películas, cada una con información relevante como título, sinopsis, género y edad mínima recomendada.
- **Clasificación**: Las películas pueden diferenciarse por género (acción, comedia, drama, etc.) o por edad mínima (infantil, adolescente, adulto).

### 2. Cartelera y Funciones

- **Visualización de Cartelera**: Muestra las películas disponibles actualmente, junto con sus horarios y funciones.
- **Horarios Disponibles**: Permite consultar los horarios y funciones de cada película.

### 3. Selección de Butacas

- **Distribución de Butacas**: Interfaz tipo matriz rectangular que muestra butacas disponibles y ocupadas.
- **Selección Interactiva**: El usuario puede elegir sus asientos visualizando la disponibilidad en tiempo real.

### 4. Métricas de Sala

El sistema calcula y muestra métricas avanzadas sobre la ocupación de las salas:

- **Fila más vendida**: Indica cuántas butacas se vendieron en la fila con mayor ventas.
- **Diagonal principal**: Muestra la cantidad de butacas vendidas en la diagonal principal de la matriz de butacas.
- **Columnas Fibonacci**: Cuenta las butacas vendidas en columnas cuyo índice pertenece a la serie de Fibonacci.
- **Butacas por Fila**: Desglose de butacas vendidas por cada fila.
- **Distribución Demográfica**: Cantidad de butacas vendidas a adultos mayores, adultos y niños.
- **Filas Primas**: Cantidad de butacas vendidas en filas cuyo número es primo.

### 5. Compra de Entradas

- **Precios Variables**:
  - Niños: $1
  - Adultos mayores: $1.5
  - Adultos: $2
- **Restricción de Edad**: Solo personas mayores pueden adquirir entradas.
- **Métodos de Pago**:
  - En caja
  - Transferencia bancaria
  - Pago móvil
- **Monedas Soportadas**:
  - Bolívares (moneda local)
  - Dólares estadounidenses
  - Conversión automática según tasa de cambio actual.

### 6. Menús de Consumo

- **Combos**: Listado de combos disponibles, con descripción y precio.
- **Bebidas**: Menú de bebidas con precios y detalles.
- **Comidas**: Menú de comidas con precios y descripción de cada platillo.

---

## Consideraciones Técnicas

- **Interfaz en Pseint**: El sistema está diseñado para ejecutarse en Pseint, utilizando menús y estructuras de control propias del pseudolenguaje.
- **Estructuras de Datos**: Uso de matrices para la gestión de butacas y arreglos para películas, menús y métricas.
- **Validaciones**: Control de edad mínima para compra de entradas y validación de disponibilidad de butacas.
- **Conversión de Moneda**: Implementación de lógica para calcular precios en ambas monedas según la tasa de cambio ingresada por el usuario o definida por el sistema.

---

## Resumen de Requerimientos

- Gestión dinámica de películas y cartelera.
- Visualización y selección de butacas en matriz.
- Cálculo de métricas avanzadas sobre ventas y ocupación.
- Compra de entradas con precios diferenciados y métodos de pago variados.
- Menús de combos, bebidas y comidas.
- Soporte para múltiples monedas y tasas de cambio.
- Restricciones y validaciones de edad y disponibilidad.

---

## Público Objetivo

- Usuarios mayores de edad interesados en adquirir entradas de cine y productos asociados de manera virtual y sencilla.

---

## Objetivo del Proyecto

Ofrecer una simulación completa y realista de un sistema de cine, permitiendo practicar lógica de programación, manejo de estructuras de datos y desarrollo de interfaces interactivas en Pseint.

