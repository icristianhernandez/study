# Conocimiento del Proyecto: Servicio de Cine en Pseint

## Descripción General

Este proyecto consiste en el desarrollo de un servicio de cine utilizando Pseint. El sistema permitirá a los usuarios realizar todas las acciones típicas asociadas con la experiencia de ir al cine, desde consultar la cartelera hasta comprar entradas y combos.

## Características Principales

### Gestión de Películas
- El sistema almacenará información de **N películas**.
- Cada película tendrá atributos como:
    - Título
    - Sinopsis
    - Género
    - Edad mínima recomendada
    - Formato (e.g., 2D, 3D)
- Las películas se podrán diferenciar o filtrar por género o edad mínima.

### Cartelera y Funciones
- Se mostrará una **cartelera actualizada** con las películas actualmente en exhibición.
- Se podrán consultar los **horarios y funciones disponibles** para cada película.

### Selección de Butacas
- Se implementará una **interfaz gráfica (en modo texto)** para la distribución de butacas.
- Esta interfaz será una **matriz rectangular** que mostrará:
    - Butacas disponibles.
    - Butacas no disponibles (ocupadas).

### Métricas de Salas de Cine
Se proporcionarán las siguientes métricas por cada sala:
- Cantidad de butacas vendidas en la **fila más vendida**.
- Cantidad de butacas vendidas en la **diagonal principal** de la matriz de butacas.
- Cantidad de butacas vendidas en **columnas cuyo índice pertenezca a la serie de Fibonacci**.
- Cantidad de butacas vendidas **en cada fila**.
- Distribución de butacas vendidas por tipo de espectador:
    - Adultos mayores
    - Adultos
    - Niños
- Cantidad de butacas vendidas en **filas cuyo índice sea un número primo**.

### Precios y Venta de Entradas
- Los precios de las entradas variarán según la demografía del espectador:
    - Niños: $1.00
    - Adulto Mayor: $1.50
    - Adultos: $2.00
- **Restricción**: Solo las personas mayores de edad podrán adquirir las entradas.

### Métodos de Pago
- Se aceptarán los siguientes métodos de pago:
    - Pago en caja (efectivo)
    - Transferencia bancaria
    - Pago móvil
- El sistema deberá manejar **dos monedas**:
    - Moneda local (Bolívares)
    - Dólares ($)
- Se implementará la gestión de **tasas de cambio** para la conversión entre monedas.

### Menú de Confitería
- El sistema incluirá un menú detallado de:
    - **Combos**: Descripción de qué contienen y precio.
    - **Bebidas**: Listado de bebidas disponibles y precio.
    - **Comidas**: Listado de alimentos disponibles y precio.

## Consideraciones Tecnológicas
- **Lenguaje de Programación**: Pseint (pseudocódigo).
- **Interfaz de Usuario**: Basada en texto, simulando interacciones gráficas mediante la consola de Pseint.

## Futuras Mejoras (Opcional)
- Sistema de reservas online.
- Programa de fidelización de clientes.
- Notificaciones de próximos estrenos.
