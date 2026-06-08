### PC3 - CC232

#### Estudiante
- Nombre: CABELLO QUEVEDO YAIMAR ALEXIS
- Código: 20244712D
- Problema asignado: CSES - Sliding Window Cost
- Enlace oficial: https://cses.fi/problemset/task/1077

#### Referencia oficial
- CSV oficial: https://github.com/kapumota/CC-232/blob/main/Practicas/Practica3_CC232/Problemas-Evaluacion3.csv

#### Relación con Semanas 4-6
- Semana principal: Semana 5 y 6
- Estructura usada: Dos conjuntos ordenados auto-balanceados con sumas acumuladas dinámicas.
- Estructura de la librería `cc232` relacionada: Equivalente a mantener la mediana dinámica mediante dos Heaps mezclables (min-heap y max-heap) con lazy deletion, o un Treap aumentado con suma de subárboles.

#### Resumen de la solución
El problema exige calcular el costo mínimo para igualar todos los elementos de una ventana deslizante de tamaño 'k'. Ese costo se minimiza igualando todos a la mediana actual. Para no recalcular la mediana ni el costo desde cero en cada movimiento (lo cual daría Time Limit Exceeded), dividimos los elementos activos en dos mitades (`left_set` y `right_set`). Manteniendo estas mitades balanceadas y actualizando sus sumatorias en tiempo real, obtenemos la mediana y calculamos el costo algebraicamente en O(log k).

#### Invariante principal
- **Balance de tamaños:** El `left_set` siempre tiene igual o exactamente un elemento más que el `right_set`.
- **Propiedad de orden:** El mayor elemento del `left_set` es siempre menor o igual al menor elemento del `right_set`.
- **Consistencia de sumas:** Las variables `left_sum` y `right_sum` siempre reflejan la sumatoria exacta de los elementos en sus respectivos sets.

#### Complejidad
- Tiempo por operación: O(log k) para insertar, eliminar y balancear.
- Tiempo total: O(n log k) donde n es el número total de elementos.
- Espacio: O(k) para almacenar los elementos activos en la ventana.

#### Archivos relevantes
- `include/`: Contiene la cabecera `SlidingWindow.h` con la API pública.
- `src/`: Contiene la implementación lógica en `SlidingWindow.cpp` y el programa principal `main.cpp`.
- `tests/`: Contiene el archivo de pruebas `test_pc3.cpp` y el archivo `input.txt` para probar el main.
- `docs/respuestas_obligatorias.md`: Sustento teórico y respuestas específicas de CSES 1077.
- `docs/bitacora.md`: Registro del avance diario y commits.
- `resultados/`: Evidencia física reproducible en `.txt` de que las pruebas y ejecuciones compilan y corren.

#### Limpieza del repositorio
El repositorio se ha mantenido libre de binarios. Se implementó un archivo CMakeLists.txt y un .gitignore para evitar versionar carpetas de compilación como build/ o archivos objeto.

#### Compilación
El proyecto se compila desde una copia limpia del repositorio usando:
```bash
cmake -G "MinGW Makefiles" -S . -B build
cmake --build build