# Respuestas Obligatorias - CSES 1077 (Sliding Window Cost)

## Preguntas Comunes Obligatorias

**1. ¿Cuál es el problema exacto asignado?**
CSES 1077 - Sliding Window Cost. Consiste en calcular el costo mínimo necesario para igualar todos los elementos dentro de una ventana de tamaño $k$ a medida que se desliza por un arreglo. Este costo es mínimo cuando todos los elementos cambian al valor de la mediana actual.

**2. ¿Qué recibe la entrada y qué produce la salida?**
Recibe dos enteros $n$ (tamaño del arreglo) y $k$ (tamaño de la ventana), seguidos de los $n$ elementos del arreglo. Produce $n - k + 1$ valores, donde cada uno es el costo de alinear los elementos de esa ventana específica a su respectiva mediana.

**3. ¿Cuál es la restricción que vuelve insuficiente una solución ingenua?**
Los límites del problema establecen que $n$ y $k$ pueden llegar a $2 \cdot 10^5$. Una solución ingenua excedería el límite de tiempo de ejecución del juez en línea (TLE).

**4. ¿Cuál sería la solución ingenua y cuál es su complejidad?**
La solución más obvia es aislar los $k$ elementos por cada ventana, ordenarlos para buscar la mediana, y luego iterar sobre esos $k$ elementos sumando la diferencia absoluta contra esa mediana. Esto daría una complejidad temporal de $O(n \cdot k \log k)$, inviable para los casos grandes.

**5. ¿Qué estructura de datos elegiste?**
Implementé una abstracción con dos conjuntos ordenados auto-balanceados (`std::multiset` en C++): uno llamado `left_set` (que almacena la mitad inferior y contiene la mediana) y un `right_set` (que almacena la mitad superior). 

**6. ¿Qué estructura de la librería `cc232` se parece más?**
Mi implementación se comporta matemáticamente igual a utilizar dos colas de prioridad (`PQ_ComplHeap` de la Semana 6, un Max-Heap para la izquierda y un Min-Heap para la derecha). La principal diferencia es que uso las facilidades del iterador de C++ para remover elementos obsoletos, mientras que con los Heaps de la librería usaría la técnica de *Lazy Deletion* (marcar el elemento como borrado hasta que flote a la raíz).

**7. ¿Qué operación domina el tiempo?**
Las operaciones dominantes por cada ventana son la inserción de un elemento, la búsqueda/eliminación del elemento saliente y el reequilibrio `balance()`. Todas se realizan en tiempo logarítmico.

**8. ¿Qué invariante mantiene tu estructura?**
Mantengo un balance de tamaños estricto: el `left_set` siempre tiene la misma cantidad de elementos que el `right_set`, o exactamente un elemento más si $k$ es impar. Además, conservo la invariante de sumatorias, donde las variables `left_sum` y `right_sum` siempre reflejan de forma exacta la suma total de los elementos en sus respectivos conjuntos.

**9. ¿Dónde se actualiza ese invariante en el código?**
Las sumas se actualizan al insertar o remover elementos individuales. El invariante principal de tamaños se restaura dentro del método `balance()`, que mueve iteradores de los extremos de un set al otro cuando se rompe la diferencia de tamaños.

**10. ¿Qué caso borde puede romper una solución superficial?**
Un caso típico es recibir secuencias de números exactamente iguales (ej. `5 5 5 5`). Si el borrado no está bien manejado y se busca eliminar "por valor" en lugar de "por iterador o nodo", la estructura eliminaría múltiples datos válidos a la vez, descuadrando el tamaño $k$ de la ventana.

**11. ¿Cómo manejas duplicados, empates o elementos obsoletos?**
El `multiset` admite valores repetidos internamente. Para eliminar el elemento obsoleto que sale de la ventana, busco primero su iterador exacto con `find()` y luego elimino únicamente esa instancia con `erase(it)`, evitando afectar a otros elementos con el mismo valor.

**12. ¿Cuál es la complejidad temporal por operación?**
Tanto insertar un valor nuevo como remover el valor saliente y realizar el balanceo cuestan $O(\log k)$.

**13. ¿Cuál es la complejidad total?**
El costo de procesar la entrada y deslizar la ventana a lo largo de los $n$ números es de $O(n \log k)$.

**14. ¿Cuál es la complejidad espacial?**
La complejidad espacial es $O(k)$, ya que independientemente del tamaño de $n$, las estructuras auxiliares solo guardan los datos activos correspondientes a la ventana actual.

**15. ¿Qué parte del código sería más fácil de romper?**
El método `balance()` es crítico. Si las validaciones lógicas que deciden cuándo extraer un elemento de `left_set` y pasarlo a `right_set` no están bien acotadas, podríamos terminar intentando extraer el iterador de un set vacío, causando un *Segmentation Fault*.

**16. ¿Qué alternativa de estructura existe y qué perderías con ella?**
Podría haber usado un `Treap` al que se le aumente un atributo de "suma acumulada" en la clase `Node`. Esto habría requerido mucha más ingeniería de bajo nivel para instrumentar las rotaciones (`bubbleUp` y `trickleDown`), perdiendo legibilidad a cambio de no usar la STL, aunque la complejidad final sería la misma.

**17. ¿Qué prueba propia escribiste?**
Redacté una prueba de "Caso Extremo Pequeño" en `test.cpp` que inserta los valores $1$, $1000000$ y $2$. Me sirvió para comprobar que los cálculos no generan *overflow*, validando el uso de tipos de dato `long long`.

**18. ¿Qué cambiaste durante el bloque sin cortes?** *NOTA PARA EL VIDEO: Durante tu grabación sin cortes, entra a tu `SlidingWindow.cpp` y agrégale a la función `balance()` un simple `cout << "Balanceo completado. Left: " << left_set.size() << " Right: " << right_set.size() << "\n";` para que el código quede alterado en vivo.* (Para el texto pon esto): Modifiqué el código en tiempo real para imprimir el estado interno de las estructuras durante el proceso de balanceo, demostrando el control sobre la invariante de tamaños.

**19. ¿Cómo sabes que el cambio no rompió la solución?**
Porque después de realizar el cambio en código en vivo, recompilé el proyecto usando CMake desde cero (`build/`) y la salida del ejecutable continuó respondiendo a los casos lógicos de forma correcta sin desbordamientos de memoria.

**20. ¿Qué demuestra que no es una solución de caja negra?**
Demuestra conocimiento algorítmico porque el `multiset` solo está operando como un sistema confiable de punteros y ordenamiento; sin embargo, el motor central del problema —el mantenimiento del invariante de tamaños y el cálculo matemático dinámico mediante costo = $(right\_sum - size \cdot med) + (size \cdot med - left\_sum)$— es una lógica diseñada enteramente desde cero sin usar librerías externas.

## Preguntas Específicas del Problema

**1. ¿Por qué la mediana minimiza la suma de distancias absolutas?**
Matemáticamente, si elegimos un punto que no es la mediana y lo movemos hacia ella, nos estamos acercando a una mayor cantidad de puntos de los que nos alejamos, reduciendo el costo total. Al llegar exactamente a la mediana, la cantidad de elementos a la izquierda y a la derecha se equilibra, por lo que cualquier movimiento adicional aumentaría la distancia neta.

**2. ¿Dónde se actualiza la suma acumulada de cada lado?**
Se actualiza dinámicamente de forma O(1) en tres lugares de la clase `SlidingWindow`:
- En `add_val()`: al sumar el nuevo valor a `left_sum` o `right_sum` dependiendo de en qué set se insertó.
- En `remove_val()`: al restar el valor eliminado de la suma correspondiente.
- En `balance()`: cuando un elemento se mueve de un set a otro para equilibrar los tamaños, se resta de la suma de su set original y se añade a la suma de su nuevo set.

**3. ¿Cómo se eliminan correctamente duplicados al mover la ventana?**
Dado que estamos usando `std::multiset` (que emula a un Treap con duplicados o Heaps con lazy deletion), la eliminación no se hace por valor directo `set.erase(val)`, porque eso borraría todos los duplicados de golpe. En su lugar, usamos `find(val)` para obtener un iterador al primer elemento que coincida con ese valor, y pasamos ese iterador a `erase(it)`. Esto garantiza que solo eliminamos exactamente un elemento, el que salió de la ventana.