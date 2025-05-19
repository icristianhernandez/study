# Conocimiento del Proyecto: Servicio de Cine en Pseint

## Descripción General

Este proyecto consiste en el desarrollo de un servicio de cine utilizando Pseint. El sistema permitirá a los usuarios realizar todas las acciones esperables en una aplicación de este tipo, desde consultar la cartelera hasta comprar entradas y combos.

## Funcionalidades Principales

### Gestión de Películas
- **Listado de Películas:** El sistema deberá manejar un catálogo de N películas.
- **Información Detallada:** Cada película contará con información como título, sinopsis, duración, etc.
- **Clasificación:** Las películas podrán ser diferenciadas por:
    - Género (acción, comedia, drama, etc.)
    - Edad mínima recomendada.

### Cartelera y Horarios
- **Visualización de Cartelera:** Mostrar las películas que se encuentran actualmente en exhibición.
- **Horarios y Funciones:** Presentar los horarios y las diferentes funciones disponibles para cada película.

### Gestión de Butacas
- **Visualización de Distribución:** Interfaz gráfica (representada en Pseint) que muestre la distribución de las butacas en una sala en forma de matriz rectangular.
- **Estado de Butacas:** Indicar claramente cuáles butacas están disponibles y cuáles no.

### Métricas de Sala
El sistema deberá proveer una interfaz con las siguientes métricas por sala:
- **Fila Más Vendida:** Cantidad de butacas vendidas en la fila con mayor ocupación.
- **Diagonal Principal:** Cantidad de butacas vendidas en la diagonal principal de la matriz de butacas.
- **Columnas Fibonacci:** Cantidad de butacas vendidas en las columnas cuyo índice pertenezca a la serie de Fibonacci (considerando el inicio de la serie según convenga, ej: 0, 1, 1, 2, 3, 5...).
- **Ventas por Fila:** Cantidad de butacas vendidas en cada una de las filas.
- **Distribución Demográfica:** Cantidad de butacas vendidas distribuidas entre:
    - Adultos mayores
    - Adultos
    - Niños
- **Filas Primas:** Cantidad de butacas vendidas en filas cuyo número de fila sea un número primo.

### Precios y Venta de Entradas
- **Precios Diferenciados:**
    - Niños: $1
    - Adulto Mayor: $1.5
    - Adultos: $2
- **Restricción de Compra:** Solo las personas mayores de edad pueden adquirir las entradas.

### Métodos de Pago
- **Opciones de Pago:**
    - Pago en caja (efectivo)
    - Transferencia bancaria
    - Pago móvil
- **Manejo de Moneda:**
    - El sistema debe adaptarse para mostrar precios y procesar pagos tanto en la moneda local (Bolívares) como en Dólares.
    - Se deberá considerar una tasa de cambio para las conversiones.

### Menú de Confitería
- **Combos:** Mostrar un menú con los combos disponibles, incluyendo su contenido y precio.
- **Bebidas:** Listar las bebidas disponibles con sus respectivos precios.
- **Comidas:** Presentar las opciones de comida (snacks, etc.) con sus precios.

## Consideraciones Adicionales
- La interfaz, aunque en Pseint, debe ser lo más clara e intuitiva posible.
- Se deben validar las entradas del usuario para evitar errores.
- El manejo de la "base de datos" (que en Pseint será probablemente mediante arreglos o matrices) debe ser eficiente.
