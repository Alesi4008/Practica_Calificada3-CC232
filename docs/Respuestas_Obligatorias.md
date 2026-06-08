# Respuestas Obligatorias - CSES 1077 (Sliding Window Cost)

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