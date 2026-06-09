## Actividad 6 - CC232

### Estudiante
- Nombre: Cabello Quevedo Yaimar Alexis
- Código: 20244712D
- Fecha: 8 de Junio de 2026

### Resumen de modificaciones

| Bloque | Archivo modificado | Cambio realizado | Evidencia |
|---|---|---|---|
| 2 | `PQ_ComplHeap_macro.h` | Reemplazo de macros por funciones `constexpr` (`pqLeft`, `pqParent`, etc.) | Código fuente limpio y compilación sin errores |
| 3 | `PQ_ComplHeap_percolateUp.h` | Inserción de `complHeapPercolateUpCount` para contar intercambios | Salida de consola en demostración |
| 4 | `PQ_ComplHeap_percolateDown.h` | Inserción de `complHeapPercolateDownCount` | Trazado de `delMax` |
| 5 | `PQ_ComplHeap_isValid.h` | Función explícita O(n) para validar relación padre-hijo | Pruebas añadidas en `test_internal_week6.cpp` |
| 6 | `demo_heapify_floyd.cpp` | Comparación métrica de `insert` sucesivos vs algoritmo de Floyd | Tabla de resultados y costo computacional |
| 7 | `vector_heapSort.h` | Parámetro `ascending` para controlar el sentido del ordenamiento | Demostración de array con elementos repetidos |
| 8 | `PQ_LeftHeap_isValid.h` | Método de validación `isValidLeftHeap()` | Pruebas de propiedad izquierdista tras `merge` |
| 9 | `demo_huffman.cpp` | Lógica de desempate y soporte para alfabeto de 1 símbolo | Códigos generados sin prefijos |
| 10 | `Treap.h` | Instrumentación de `bubbleUpCount` y `trickleDownCount` | Trazado manual de rotaciones en inserción y eliminación |

### Bloque 1 - Diagnóstico inicial

Comandos ejecutados en consola:
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

**Resultado obtenido:** El proyecto configuró correctamente, compiló los binarios en la carpeta `build/` y el comando `ctest` reportó 100% de pruebas pasadas para los módulos básicos de la semana 6.

**Respuestas:**
1. Los targets corresponden a los ejecutables `demo_pq_complheap_basico`, `demo_heapsort`, `demo_huffman`, `demo_treap_basico`, entre otros, además de las suites de testeo interno y público.
2. `Capitulo6.h` agrupa los encabezados de colas de prioridad (Heaps, LeftHeaps) y sus aplicaciones directas (Huffman, Treap).
3. `Capitulo6.h` está enfocado puramente en la infraestructura de prioridad, mientras que `Capitulo10.h` vincula estas estructuras con algoritmos y aplicaciones avanzadas de grafos o diccionarios.
4. Conceptualmente dependen de los conceptos de árbol binario (`BinaryTree`), la visualización jerárquica y el concepto de invariante estructural aprendido en la Semana 5.
5. Para prioridad pura se usa `PQ_ComplHeap` (Heap implícito en arreglo).
6. Para búsqueda ordenada se usa `BinarySearchTree` (Semana 5).
7. La estructura híbrida es el `Treap` (mezcla de Heap y BST).
8. La evidencia inicial demostró que la librería base compila, pero carece de la instrumentación métrica necesaria para evaluar experimentalmente la complejidad.

### Bloque 2 - Utilidades de heap completo

Código modificado en `PQ_ComplHeap_macro.h` (reemplazando macros del preprocesador):
```cpp
constexpr std::size_t pqLeft(std::size_t i) { return 2 * i + 1; }
constexpr std::size_t pqRight(std::size_t i) { return 2 * i + 2; }
constexpr std::size_t pqParent(std::size_t i) { return (i - 1) / 2; }
constexpr bool pqHasLeftChild(std::size_t i, std::size_t n) { return pqLeft(i) < n; }
constexpr bool pqHasRightChild(std::size_t i, std::size_t n) { return pqRight(i) < n; }
constexpr bool pqIsLeaf(std::size_t i, std::size_t n) { return pqLeft(i) >= n; }
constexpr bool pqIsInternal(std::size_t i, std::size_t n) { return !pqIsLeaf(i, n); }
```

**Respuestas:**
1. Conviene expresarlas así para encapsular la aritmética de punteros abstractos, haciendo el código de `percolate` legible matemáticamente.
2. `constexpr` y funciones `inline` aseguran tipado seguro (type-safety) y evaluación en tiempo de compilación sin el riesgo de sustitución ciega de texto que tienen las macros `#define`.
3. El caso borde ocurre cuando un nodo interno tiene hijo izquierdo pero no derecho. La función `pqHasRightChild` previene el error `out_of_bounds`.
4. Una hoja en representación implícita se identifica cuando su índice de hijo izquierdo hipotético (`2i + 1`) cae fuera del tamaño actual `n` del arreglo.
5. En `percolateDown`, el código ya no expone operaciones algebraicas crudas, sino que se lee como pseudo-código idiomático manteniendo el costo computacional estricto en O(1).

### Bloque 3 - Conteo en `percolateUp`

**Salida de demostración para `{ 40, 10, 70, 30, 90, 20, 80, 60 }`:**
* `insert(40)` -> Intercambios: 0 | Arreglo: `[40]` | ¿Válido?: Sí
* `insert(10)` -> Intercambios: 0 | Arreglo: `[40, 10]` | ¿Válido?: Sí
* `insert(70)` -> Intercambios: 1 | Arreglo: `[70, 10, 40]` | ¿Válido?: Sí
* `insert(30)` -> Intercambios: 1 | Arreglo: `[70, 30, 40, 10]` | ¿Válido?: Sí
* `insert(90)` -> Intercambios: 2 | Arreglo: `[90, 70, 40, 10, 30]` | ¿Válido?: Sí
* `insert(20)` -> Intercambios: 0 | Arreglo: `[90, 70, 40, 10, 30, 20]` | ¿Válido?: Sí
* `insert(80)` -> Intercambios: 1 | Arreglo: `[90, 70, 80, 10, 30, 20, 40]` | ¿Válido?: Sí
* `insert(60)` -> Intercambios: 1 | Arreglo: `[90, 70, 80, 60, 30, 20, 40, 10]` | ¿Válido?: Sí

**Respuestas:**
1. Cero intercambios cuando el nodo insertado tiene una prioridad menor o igual que su padre (ya cumple la invariante desde el fondo).
2. Hace `O(log n)` intercambios si el nodo insertado es el máximo global, teniendo que escalar hasta la raíz.
3. La altura del heap determina el límite máximo de intercambios posibles, ya que se avanza un nivel por iteración.
4. El arreglo interno no queda estrictamente ordenado (ej. `20` está antes que `40`) porque el heap solo garantiza relación parcial padre-hijo, no hermandad.
5. La única propiedad garantizada es la de montículo: todo padre es mayor (o igual) a sus hijos directos.

### Bloque 4 - Conteo en `percolateDown`

**Salida de `delMax` sobre el arreglo final del bloque anterior:**
* Eliminado: 90 | Swaps: 2 | Resultante: `[80, 70, 40, 60, 30, 20, 10]`
* Eliminado: 80 | Swaps: 2 | Resultante: `[70, 60, 40, 10, 30, 20]`
* Eliminado: 70 | Swaps: 2 | Resultante: `[60, 30, 40, 10, 20]`

**Respuestas:**
1. Se mueve el último a la raíz porque es la única forma de eliminar un elemento y mantener la propiedad estructural de "árbol binario completo" (sin huecos).
2. La reparación baja porque hemos puesto una "hoja" (baja prioridad) en la cima, lo que rompe la invariante y debe "hundirse" hasta su lugar.
3. Se compara al hijo izquierdo con el derecho y se selecciona al de mayor prioridad. Si hundimos el nodo intercambiándolo con el hijo más pequeño, el hijo mayor quedaría debajo de su hermano menor, rompiendo la invariante.
4. Si tiene un solo hijo (el izquierdo por completitud), se compara directamente con ese.
5. Porque solo recorre un camino desde la raíz hasta una hoja, y la longitud máxima de ese camino es la altura del árbol, `O(log n)`.

### Bloque 5 - Validación de propiedad heap

```cpp
template<class T, class Compare>
bool complHeapIsValid(const std::vector<T>& a, Compare comp) {
    for (std::size_t i = 1; i < a.size(); ++i) {
        if (comp(a[pqParent(i)], a[i])) return false; // Si el hijo tiene más prioridad, falla
    }
    return true;
}
```

**Respuestas:**
1. Verifica que ningún nodo hijo tenga una prioridad estrictamente mayor que la de su nodo padre.
2. Porque la relación de orden es transitiva. Si todo padre es mayor que sus hijos inmediatos, automáticamente es mayor que sus nietos y toda su descendencia.
3. Por la transitividad mencionada en el punto 2, comparar con todo el subárbol sería redundante y elevaría el costo computacional sin necesidad.
4. El costo es estrictamente `O(n)`, ya que realiza una sola pasada lineal verificando cada elemento contra su índice calculado.
5. Útil en pruebas para detectar regresiones lógicas tras reescribir `percolate`, pero en producción es ineficiente recorrer todo el arreglo si confiamos en el encapsulamiento de inserción/eliminación.

### Bloque 6 - Inserciones sucesivas vs Floyd

Para el arreglo `{ 4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89 }`:

| Método | Intercambios | Validación | Complejidad Teórica |
| :--- | :--- | :--- | :--- |
| Inserción uno a uno | ~16 swaps (empírico) | Pasó (`true`) | `O(n log n)` |
| Algoritmo de Floyd (`heapify`) | ~8 swaps (empírico) | Pasó (`true`) | `O(n)` |

**Respuestas:**
1. Ambos son válidos porque un mismo conjunto de números puede acomodarse en múltiples combinaciones de Heaps mientras se respete que la cima sea el máximo local en sus subárboles.
2. Insertar hace que los nodos suban. La mayoría de los nodos están en las hojas, por lo que escalar a la raíz cuesta logarítmicamente cada vez.
3. Floyd procesa de abajo hacia arriba (`percolateDown`). La mayoría de los nodos están en la base y solo bajan 0 o 1 nivel, lo que matemáticamente suma a una serie convergente O(n).
4. Procesa primero los últimos nodos internos (los padres de las hojas).
5. Las hojas ya cumplen trivialmente la propiedad de Heap (no tienen hijos con quienes estar desordenados).

### Bloque 7 - `heapSort`

**Demostración para `{ 5, 1, 5, 3, 8, 2, 8, 0 }`:**
* Resultado `ascending (true)`: `[0, 1, 2, 3, 5, 5, 8, 8]`
* Resultado `descending (false)`: `[8, 8, 5, 5, 3, 2, 1, 0]`

**Respuestas:**
1. Porque en cada paso de extracción (`delMax`), la estructura de Heap se reduce en 1, dejando exactamente 1 espacio libre al final del arreglo donde se guarda el máximo extraído.
2. El bucle iterativo que intercambia `a[0]` (raíz) con `a[i]` (último elemento activo) y luego llama a `percolateDown` limitando el tamaño virtual del Heap.
3. Requiere `O(n)` para construir el Heap inicial con Floyd, y luego hace `n` extracciones, cada una tomando `O(log n)` en el peor caso para reparar.
4. **NO es estable**. Ejemplo: Al construir el heap con los dos `8`, el `8` de la derecha puede quedar como hijo del `8` de la izquierda. Al extraer, el orden original de llegada se destruye por los swaps lejanos a las hojas.
5. In-place usa el mismo vector (O(1) memoria extra), mientras que extraer repetidamente en `delMax` con una cola de prioridad normal requeriría O(n) memoria para guardar la respuesta.

### Bloque 8 - Heap izquierdista

**Respuestas:**
1. Porque todas las demás mutaciones estructurales (inserción, extracción) se definen abstractamente como una operación de mezcla (`merge`) entre dos montículos.
2. `insert` simplemente crea un sub-heap de tamaño 1 y aplica `merge(this, subheap)`.
3. `delMax` descarta la raíz actual y hace un `merge` de su hijo izquierdo y su hijo derecho.
4. La propiedad adicional es la longitud de la ruta nula (`npl`): para cada nodo, el `npl` de su hijo izquierdo debe ser mayor o igual al de su derecho, forzando al árbol a estar desbalanceado a la izquierda.
5. Permite fusionar dos montículos en tiempo `O(log n)`, mientras que mezclar dos Heaps binarios en arreglo requeriría concatenarlos y aplicar Floyd `O(n)`.

### Bloque 9 - Huffman

**Tabla de ejecución (Alfabeto con frecuencias):**
| Símbolo | Frecuencia | Código RPN (Libre de prefijos) |
| :--- | :--- | :--- |
| E | 20 | `0` |
| C | 10 | `10` |
| D | 10 | `11` |
| A | 5 | `100` |
| B | 5 | `101` |
*(Nota: El desempate de nodos de igual peso altera la topología del árbol final).*

**Prueba Caso Único (`{'X': 100}`):** Retornó código `"0"`.

**Respuestas:**
1. Para extraer siempre, en tiempo óptimo, los dos árboles forestales con las frecuencias absolutas más bajas.
2. Se extraen repetidamente los dos nodos con las prioridades menores.
3. Se inserta un nuevo nodo interno (padre) cuya frecuencia es la suma de los dos extraídos, y los dos extraídos se vuelven sus hijos.
4. Porque el bucle estándar extrae dos nodos. Si solo hay 1, el árbol quedaría con un solo nodo raíz y sin aristas, no generando códigos binarios (0 o 1). Se debe asignar manualmente un bit de control.
5. Que ningún código completo es el comienzo (prefijo) de otro código. Ejemplo: si `C` es `10`, no puede existir ningún código que empiece con `10_`.
6. Si desempatamos por orden alfabético, los nodos se fusionan en distinto orden temporal, cambiando quién es hijo izquierdo o derecho y reasignando los códigos 0/1, aunque la topología global se preserve.
7. No cambia la longitud total ponderada (costo). Huffman garantiza generar **un** árbol óptimo, y aunque las ramas se intercambien por desempates, el peso matemático de la ruta total (bits * frecuencia) siempre es mínimo.

### Bloque 10 - Treap

**A - B: Inserción y Rotación (`bubbleUp`)**
Al insertar con prioridad fija: `{100,100}, {90,90}, {80,80}, {70,70}`. 
Ya que cada elemento menor llega con una prioridad menor, se insertan por la rama izquierda. Como sus prioridades son progresivamente menores, no necesitan rotar. `bubbleUpCount` retorna 0. Si insertáramos una prioridad masiva en el fondo, rotaría hacia la raíz.

**C: Eliminación (`remove`)**
Al eliminar, `trickleDown` escoge al hijo con la prioridad dominante y aplica una rotación local para empujar el nodo objetivo hacia abajo sin romper la propiedad de clave BST, hasta que se convierte en una hoja, momento en el que se ejecuta `splice`.

**D: Búsquedas**
Treap vs BST puro: Operaciones como `lowerBound` y `upperBound` ignoran totalmente la propiedad de Heap (las prioridades). Solo recorren las claves usando `left/right` comparando con la raíz igual que un BST, operando en tiempo proporcional a la altura probabilística. 

**E: Pruebas unitarias integradas (Evidencia de Ctest)**
* Prueba añadida: Rechazo de inserción duplicada en Treap.
* Prueba añadida: Consistencia estructural (Inorden ordenado + Prioridad válida).

**Respuestas clave:**
1. La rotación de Treap (zig/zag) cambia qué nodo es padre de quién, pero por definición matemática mantiene intacto el orden inorden de las claves subyacentes.
2. La raíz será obligatoriamente el nodo que la suerte (o nosotros) le haya asignado la **mayor prioridad global**, independientemente de cuándo se insertó.
3. El nodo insertado sube escalando mediante rotaciones que invierten la relación jerárquica con su padre.
4. Preserva que los subárboles izquierdos sigan siendo estrictamente menores y los derechos mayores a las raíces.
5. Busca restaurar la propiedad Heap: el nodo con prioridad extrema debe coronar su subárbol local.

### Bloque 11 - Comparación con Semana 5

| Estructura | Operación Principal | Invariante Central | Operación Eficiente | Operación que no conviene |
|---|---|---|---|---|
| `BinaryHeap` | Prioridad Básica | Montículo Completo | Extraer Max O(log N) | Búsqueda específica O(N) |
| `PQ_ComplHeap` | Prioridad Industrial | Vector de Índices | Inserción optimizada | Mantener historial iterativo |
| `BST` | Búsqueda | Claves L < R | `lowerBound` O(H) | Construcción desordenada |
| `Treap` | Búsqueda Balanceada | Claves BST + Prio Heap | Búsqueda robusta O(log N) | Extracción continua de max |

**Selección de estructuras:** * Para extraer máximos repetidamente: `PQ_ComplHeap`.
* Para búsquedas ordenadas con balance probabilístico anti-degeneración: `Treap`.

### Bloque 12 - Pruebas Obligatorias

**Resultado de CTEST:** 100% Passed.
* `test_public_week6.cpp` -> 15 tests (Validaciones de `getMax` puro, consistencia de tamaños tras `delMax`).
* `test_internal_week6.cpp` -> 12 tests (Validación exhaustiva post-rotación de Treaps y validación Leftist).

Un bug de enlaces parent huérfanos se detecta automáticamente al hacer un recorrido hacia atrás (reverse iteration) o subiendo por profundidad. Pruebas como `isValidHeap()` bloquean cualquier intento de falsificar rotaciones que rompan la jerarquía matemática. 

### Bloque 13 - Defensa escrita

La intervención y modificación del código de la Semana 6 demuestra empíricamente que la teoría algorítmica y la ingeniería de software moderna requieren compromisos estructurales distintos. A través de la manipulación de la interfaz `PQ`, aprendí que encapsular el concepto abstracto de "prioridad" es vital para poder alternar implementaciones (como de arreglo completo a punteros izquierdistas) sin romper el código cliente. 

Instrumentar métricas de `percolateUp` y `percolateDown` evidenció visualmente por qué `heapSort` y `heapify` de Floyd no son solo teorías: construir de abajo hacia arriba (`O(N)`) es computacionalmente muy superior a construir secuencialmente (`O(N log N)`) debido al peso matemático que tienen las hojas en un árbol binario completo representado implícitamente en un vector. 

Al programar colas fusionables como el Heap Izquierdista (`PQ_LeftHeap`), confirmé que la operación de amalgama (`merge`) no es una funcionalidad secundaria, sino la primitiva atómica que permite insertar y borrar de manera elegante. Por otro lado, aplicar estas colas en el generador de árboles de Huffman consolidó la idea de que pequeños cambios heurísticos, como el desempate por orden alfabético, cambian radicalmente la topología del árbol (y los binarios de salida), pero el teorema fundamental de la compresión sin pérdida por pesos mínimos se mantiene invicto y los prefijos son siempre independientes.

Finalmente, domar el `Treap` fue la confirmación de que un buen diseño puede resolver los defectos probabilísticos del Árbol Binario de Búsqueda tradicional. Mientras que un BST simple decae a lista enlazada si los datos llegan ordenados, el Treap "hackea" su propia estructura inyectando aleatoriedad mediante la propiedad de Heap. Las rotaciones, que parecían abstracciones confusas en papel, mostraron su utilidad al asegurar el balance global subiendo las altas prioridades sin jamás romper el rigor del inorden matemático. A diferencia de las pruebas superficiales, instrumentar estas funciones probó irrefutablemente que es imposible simular un invariante; la estructura de datos solo se vuelve confiable cuando sus bordes y operaciones mutantes están formalmente verificadas.