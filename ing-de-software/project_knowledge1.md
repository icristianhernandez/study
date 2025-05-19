
# Proyecto: Servicio de Cine en PSeInt

## Descripción General
Este proyecto implementa un sistema de servicio de cine utilizando PSeInt, permitiendo a los usuarios interactuar con una cartelera de películas, comprar entradas, seleccionar butacas, consultar menús de combos y comidas, y realizar pagos en diferentes métodos y monedas. El sistema está diseñado para simular la experiencia completa de compra y gestión de entradas en un cine moderno.

## Funcionalidades Principales

- **Gestión de Películas:**
  - El sistema permite registrar N películas, cada una con información relevante como título, sinopsis, género y edad mínima requerida.
  - Las películas pueden clasificarse por género (acción, comedia, drama, etc.) o por edad mínima (todo público, +13, +18, etc.).

- **Cartelera y Funciones:**
  - Visualización de la cartelera con las películas disponibles actualmente.
  - Consulta de horarios y funciones disponibles para cada película.

- **Gestión de Salas y Butacas:**
  - Cada sala tiene una matriz rectangular de butacas, mostrando cuáles están disponibles y cuáles ocupadas.
  - Interfaz para seleccionar butacas al momento de la compra.

- **Métricas y Estadísticas de Salas:**
  - Número de butacas vendidas en la fila más vendida.
  - Cantidad de butacas vendidas en la diagonal principal de la sala.
  - Número de butacas vendidas en columnas que pertenecen a la serie de Fibonacci.
  - Cantidad de butacas vendidas por fila.
  - Distribución de butacas vendidas según demografía: adultos mayores, adultos y niños.
  - Cantidad de butacas vendidas en filas cuyo número es primo.

- **Precios y Demografía:**
  - Precios diferenciados según el tipo de usuario:
    - Niños: 1$
    - Adultos mayores: 1.5$
    - Adultos: 2$
  - Solo personas mayores pueden adquirir entradas (adultos y adultos mayores).

- **Métodos de Pago:**
  - Pago en caja, transferencia bancaria o pago móvil.
  - Adaptación a dos monedas: bolívares (moneda local) y dólares, con gestión de tasas de cambio.

- **Menú de Combos, Bebidas y Comidas:**
  - Menú de combos con precios y descripción de lo que incluye cada combo.
  - Menú de bebidas y menú de comidas, cada uno con sus precios y detalles.

## Estructura del Sistema

1. **Películas:**
   - Estructura de datos para almacenar información de cada película.
   - Listado dinámico de películas en cartelera.

2. **Salas y Butacas:**
   - Matriz para representar la disposición de butacas en cada sala.
   - Estado de cada butaca (disponible/ocupada).

3. **Usuarios y Demografía:**
   - Registro de tipo de usuario para aplicar precios y restricciones.

4. **Métricas:**
   - Algoritmos para calcular estadísticas solicitadas sobre ventas de butacas.

5. **Pagos:**
   - Selección de método de pago y moneda.
   - Conversión de precios según tasa de cambio.

6. **Menús:**
   - Listados de combos, bebidas y comidas con sus precios y descripciones.

## Consideraciones Técnicas

- El sistema está diseñado para ejecutarse en PSeInt, utilizando estructuras como arreglos, matrices y registros.
- Se prioriza la interacción por menús y la validación de entradas del usuario.
- El sistema puede ser extendido para incluir nuevas métricas, menús o métodos de pago.

## Posibles Mejoras Futuras

- Integración de reportes gráficos de ventas.
- Soporte para reservas en línea.
- Personalización de combos y menús.

---
Este documento resume los conocimientos y requisitos clave para el desarrollo y mantenimiento del servicio de cine en PSeInt.
