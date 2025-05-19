# Documentación del Proyecto: Servicio de Cine en PSeInt

## Descripción General

El proyecto consiste en un sistema de cine implementado en PSeInt que simula la experiencia completa de consulta de cartelera, selección de butacas, compra de entradas y adquisición de productos.

## Objetivos

- Gestionar información de N películas con atributos como título, sinopsis, género y clasificación por edad.
- Mostrar la cartelera actual y las funciones disponibles.
- Visualizar la distribución de butacas y su estado (disponible/ocupada).
- Permitir la compra de entradas con precios variables según la demografía.
- Soportar métodos de pago en Bolívares y Dólares, aplicando tasa de cambio.
- Ofrecer un menú de combos, bebidas y comidas con sus precios y contenidos.
- Generar métricas de ocupación y ventas para análisis.

## Requisitos Funcionales

1. **Gestión de Películas**
   - Mantener un listado de películas con campos: `titulo`, `sinopsis`, `genero`, `edad_minima`.
2. **Cartelera y Funciones**
   - Listar todas las películas en cartelera.
   - Mostrar horarios y funciones disponibles para cada película.
3. **Distribución de Butacas**
   - Representación matricial de la sala (filas x columnas).
   - Mostrar butacas disponibles y ocupadas.
4. **Compra de Entradas**
   - Selección de película, función y asiento.
   - Precios: Niño = $1.00, Adulto = $2.00, Adulto Mayor = $1.50.
   - Validar que el cliente cumple la edad mínima de la película.
5. **Métodos de Pago**
   - Caja, transferencia y pago móvil.
   - Soporte para moneda local (Bs.) y dólares (USD) con tasa de cambio configurable.
6. **Menú de Productos**
   - Combos (popcorn + bebida), menú de bebidas y menú de comidas.
   - Gestión de precios y detalle de contenidos.

## Métricas y Estadísticas

- Butacas vendidas en la fila con mayor número de ventas.
- Total de butacas vendidas en la diagonal principal.
- Butacas vendidas en columnas cuyos índices pertenecen a la serie de Fibonacci.
- Cantidad de butacas vendidas por cada fila.
- Distribución de ventas por demografía (Niños, Adultos, Adultos Mayores).
- Butacas vendidas en filas cuyo número es primo.

## Estructura de Datos

- **Películas**: Vector de registros con `titulo`, `sinopsis`, `genero`, `edad_minima`.
- **Butacas**: Matriz de booleanos o enteros indicando estado (0=disponible, 1=ocupada).
- **Ventas**: Arreglo de registros (`fila`, `columna`, `tipo_cliente`, `precio`, `metodo_pago`).
- **Tasa de Cambio**: Variable `tasa_usd_bsf` para conversión.

## Interfaz de Usuario

- Menú principal numérico con opciones: Cartelera, Butacas, Compra, Pagos, Estadísticas, Productos, Salir.
- Submenús claros para cada funcionalidad.
- Representación gráfica simple de la matriz de butacas en consola.

## Algoritmos y Flujogramas

- **Validación de Compra**: Verificar edad, disponibilidad y método de pago.
- **Cálculo de Métricas**: Recorrido de matrices para diagonal, filas, columnas Fibonacci y filas primas.
- **Conversión de Moneda**: Multiplicación por la tasa de cambio.
- **Recorrido de Datos**: Uso de bucles anidados y funciones/procedimientos modulares.

## Consideraciones Técnicas

- Uso de vectores, matrices y registros en PSeInt.
- Modularidad: Procedimientos y funciones para cada tarea.
- Validación robusta de entradas y manejo de errores.
