## Actividad 5 - CC232

### Estudiante
- Nombre: Cabello Quevedo Yaimar Alexis
- Código: 20244712D

### Bloque 1 - Núcleo conceptual

1. **Árbol binario enlazado vs arreglo implícito:** El árbol enlazado utiliza nodos dinámicos en memoria conectados por punteros (`left`, `right`, `parent`), lo que permite flexibilidad para modificar su estructura (ej. rotaciones). El arreglo implícito almacena el árbol de forma contigua en memoria (típico en Heaps), usando índices matemáticos para ubicar a los hijos, optimizando el uso de caché pero limitando la flexibilidad estructural.
2. **`BinNode`:** Almacena el dato (o clave/valor), y punteros hacia el `parent`, el hijo izquierdo (`left`) y el hijo derecho (`right`). También suele incluir la `height` o tamaño del subárbol para acelerar consultas sin tener que recalcularlas.
3. **Puntero `parent`:** Es crucial para navegar el árbol "hacia arriba". Permite implementar funciones iterativas eficientes como `succ()` (sucesor inorden) y `pred()` sin necesidad de mantener una pila explícita de ancestros.
4. **`BinTree` vs `BinaryTree`:** `BinTree` es la estructura de bajo nivel que gestiona la raíz, el tamaño total y la memoria (creación/destrucción de nodos). `BinaryTree` es una capa superior que proporciona iteradores y algoritmos genéricos de recorrido sobre esa base.
5. **`BinarySearchTree` (BST):** Añade la invariante de ordenamiento: para cualquier nodo, todos los elementos en su subárbol izquierdo son menores, y en su subárbol derecho son mayores (o iguales, dependiendo de la política).
6. **`BinaryHeap` mínimo:** Utiliza un arreglo implícito y garantiza la invariante de prioridad: el valor de cualquier nodo es menor o igual al de sus hijos. La raíz siempre es el mínimo global.
7. **Recorridos:** Un BST permite obtener los elementos completamente ordenados haciendo un simple recorrido inorden en tiempo O(n). Un Heap no está totalmente ordenado (solo parcialmente por niveles de prioridad), por lo que un recorrido inorden en un Heap produciría basura desordenada; para obtener orden en un Heap hay que destruir la estructura extrayendo el mínimo repetidamente (Heapsort).

### Bloque 2 - Navegación, altura, profundidad y tamaño

- **Atributos de posición:** `hasLeft` y `hasRight` verifican si los punteros a los hijos no son nulos. `isRoot` verifica si `parent` es nulo. `isLeaf` verifica que tanto `left` como `right` sean nulos.
- **`succ()` (Sucesor inorden):** Si el nodo tiene hijo derecho, el sucesor es el nodo más a la izquierda de ese subárbol derecho. Si no tiene hijo derecho, se sube por el árbol usando `parent` hasta encontrar el primer nodo del cual somos descendientes por la rama izquierda.
- **`depth(u)` (Profundidad):** Número de aristas desde la raíz hasta el nodo `u`. Se calcula iterando `u = u->parent` hasta llegar a la raíz.
- **`height(u)` (Altura):** Distancia máxima en aristas desde `u` hasta una hoja descendiente. Se define recursivamente como `1 + max(height(left), height(right))`.

**Trazado manual de sucesor (`succ`):**
      (10)
      /  \
    (5)  (15)
    / \
  (2) (8)
      /
    (7)

- El sucesor de `(5)` es `(7)` (el más a la izquierda de su subárbol derecho).
- El sucesor de `(8)` es `(10)` (subiendo, es el primer ancestro del cual `(8)` es hijo izquierdo).

### Bloque 3 - Recorridos y trazado guiado

Trazado manual de inserciones y recorridos para la secuencia `7, 3, 10, 1, 5, 8, 12, 4, 6`.

**Árbol resultante:**
           7
         /   \
       3      10
      / \     / \
     1   5   8   12
        / \
       4   6

**Secuencias de recorrido obtenidas:**
- **Preorden (Raíz, Izq, Der):** 7, 3, 1, 5, 4, 6, 10, 8, 12
- **Inorden (Izq, Raíz, Der):** 1, 3, 4, 5, 6, 7, 8, 10, 12 (Nótese que queda perfectamente ordenado, confirmando la invariante BST).
- **Postorden (Izq, Der, Raíz):** 1, 4, 6, 5, 3, 8, 12, 10, 7
- **Por niveles (BFS usando Cola):** 7, 3, 10, 1, 5, 8, 12, 4, 6

**Complejidad:** Todos los recorridos visitan cada nodo exactamente una vez, realizando operaciones de tiempo constante O(1) en cada uno. Por ende, la complejidad de tiempo es estrictamente O(n). La complejidad espacial depende de la estructura auxiliar: O(h) para la pila implícita/explícita en recorridos en profundidad, y O(w) (donde w es la anchura máxima) para la cola en BFS.

### Bloque 4 - Demos

| Archivo ejecutable | Observación de evidencia en consola |
| :--- | :--- |
| `demo_binary_tree.cpp` | La impresión generada usando `asciiArt()` refleja correctamente las ramificaciones, coincidiendo con los recorridos manuales. |
| `demo_bst.cpp` | Al iterar usando el método `succ()` desde `leftmost()`, la consola imprime los números en orden estrictamente creciente, confirmando el correcto funcionamiento de los punteros `parent`. |
| `demo_heap.cpp` | Tras invocar repetidamente `add()`, el método `top()` siempre imprime el número menor de la colección sin importar el orden en que se ingresaron los datos. |

### Bloque 5 - Pruebas e invariantes

- Las pruebas unitarias garantizan que operaciones como `insert`, `remove` y `find` mantengan los punteros íntegros.
- Funciones como `checkParentLinks` son vitales en las pruebas internas para asegurar que si un nodo A apunta a B como hijo, B obligatoriamente apunta a A como padre. Esto previene ciclos infinitos y fugas de memoria por enlaces huérfanos.
- Las pruebas sobre el Heap validan que, tras extraer la raíz (`pop`), la operación `trickleDown` (o `heapifyDown`) empuje el nuevo elemento raíz hacia abajo hasta restaurar la propiedad de prioridad mínima en todos los niveles.

### Bloque 6 - Lectura de código

- En la clase base, `insertAsLC` y `insertAsRC` arrojan error si se intenta sobrescribir un hijo existente, protegiendo la estructura de pérdidas de subárboles no controladas.
- La función `size()` usa recursión directa sumando `1 + left->size() + right->size()`.
- La función `leftmost()` baja usando un bucle `while(curr->left != nullptr) { curr = curr->left; }`. Es la base para encontrar el mínimo en un BST.

### Bloque 7 - BST

- **Propiedad BST:** Se mantiene comparando la clave a insertar con el nodo actual, bajando por la izquierda si es menor, y por la derecha si es mayor, hasta encontrar un puntero nulo.
- **Búsqueda:** `findEQ` busca una coincidencia exacta y devuelve nulo si no existe. `lowerBound` devuelve el primer nodo cuya clave no sea menor a la buscada (útil para consultas de rangos o sucesores inmediatos).
- **Eliminación y `splice`:** Eliminar una hoja es trivial. Eliminar un nodo con un hijo usa `splice` para "puentear" el nodo eliminado, conectando directamente al abuelo con el nieto. Eliminar un nodo con dos hijos requiere buscar su sucesor inorden, copiar su valor al nodo actual y luego eliminar el sucesor (que a lo sumo tendrá un hijo).

### Bloque 8 - Heap

- **Navegación en el arreglo:** El padre de la posición `i` es `(i-1)/2`. El hijo izquierdo es `2i+1` y el derecho `2i+2`.
- **`bubbleUp` (Inserción):** Se inserta al final del arreglo y se compara con su padre. Si el nuevo elemento es menor, se intercambian. Esto sube en O(log n).
- **`trickleDown` (Extracción):** Se remueve la raíz, se coloca el último elemento del arreglo en la raíz, y se compara con sus hijos, intercambiándolo con el menor de ellos repetidamente hasta restaurar el orden. Costo: O(log n).
- **Heapsort:** Insertar `n` elementos cuesta O(n log n). Si usamos el algoritmo Floyd (`heapify` de abajo hacia arriba), construirlo cuesta O(n). Extraer el mínimo `n` veces para ordenarlos da el costo final de O(n log n).

### Bloque 9 - Cierre comparativo

Pasar de estructuras lineales (listas, colas) a estructuras jerárquicas (árboles) permite reducir el tiempo de búsqueda y modificación de O(n) a O(log n), siempre que el árbol mantenga un balance razonable (la altura h sea logarítmica). Esto introduce un costo de ingeniería mayor: hay que mantener activamente múltiples invariantes simultáneas (como la propiedad de orden y la integridad de los punteros dobles hijo-padre) cada vez que la estructura muta. 

### Autoevaluación breve
- **Qué puedo defender con seguridad:** La diferencia fundamental entre un BST (enfocado en ordenamiento total) y un Heap (enfocado en encontrar el mínimo rápido sin ordenar todo). También domino el trazado manual de los recorridos inorden, postorden y preorden.
- **Qué todavía confundo:** La lógica interna exacta de las rotaciones para auto-balancear árboles (aunque entiendo teóricamente que sirven para reducir la altura).
- **Qué evidencia usaría en una sustentación:** El trazado en papel de la función `succ()`, ya que demuestra que entiendo cómo un algoritmo iterativo sube y baja por los enlaces `parent` sin necesidad de recursión.
- **Qué parte del código me parece más importante para revisar:** El proceso de eliminación en el BST con dos hijos, ya que es el escenario de punteros más complejo de la semana.