## Actividad 4 - CC232

### Estudiante
- Nombre: Cabello Quevedo Yaimar Alexis
- Código: 20244712D

### Bloque 1 - Núcleo conceptual

1. LIFO vs FIFO: LIFO (Last In First Out) extrae el último elemento agregado (pila); FIFO (First In First Out) extrae el primero que entró (cola). Se usan según si lo relevante es procesar lo más reciente o respetar orden de llegada.
2. `Stack` resuelve bien problemas donde lo último pendiente determina la siguiente acción (ej.: evaluación de expresiones, retroceso en DFS, devolución de llamadas pendientes).
3. `Queue` modela filas y procesos en espera: mantiene orden de llegada y permite simular atención por turnos.
4. Reemplazar recursión implícita por estructura explícita significa gestionar manualmente el estado que el call stack habría guardado (variables locales, punto de retorno) usando por ejemplo una pila propia.
5. Información mínima en la pila: punto de ejecución (o decisión), valores temporales necesarios para continuar, y contexto parcial suficiente para recomponer la solución.
6. Conversión de base: la recursiva deja residuos en el call stack; la iterativa usa una pila explícita para almacenar residuos. Comparten cociente/residuo; cambian la forma en que se guarda y recupera el orden.
7. La verificación iterativa de paréntesis debe almacenar las aperturas pendientes porque cada cierre debe emparejarse con la última apertura no cerrada.
8. El evaluador necesita dos pilas (operadores y operandos) para separar prioridades y valores intermedios y construir RPN/valor respetando precedencia y asociatividad.
9. N-Reinas y laberinto requieren backtracking: se prueban opciones, se avanza cuando son válidas y se retrocede al encontrar callejón sin salida.
10. Simulación bancaria modela colas de clientes; una pila no refleja llegada y servicio por orden.
11. La estructura auxiliar guarda estado parcial; la correctitud se demuestra mostrando que la información guardada es suficiente para reconstruir o avanzar sin pérdida.
12. "Resolver" produce un resultado correcto; "simular" reproduce un proceso que evoluciona en el tiempo (historia), no solo una solución final.

### Bloque 2 - Demostración y trazado guiado

| Archivo | Observación clave en consola | Estructura | Concepto defendido |
| :--- | :--- | :--- | :--- |
| `demo_stack_queue.cpp` | Se observa que la pila extrae los números en orden inverso al ingresado, mientras la cola respeta el orden original de llegada. | Stack y Queue | Diferencia fundamental de invariantes LIFO vs FIFO. |
| `demo_base_conversion.cpp` | Las salidas de ambas funciones coinciden. Los residuos se imprimen del último al primero. | Stack explícito e implícito | La pila revierte el orden natural de los residuos obtenidos matemáticamente. |
| `demo_paren_rpn.cpp` | Expresiones como `{[()]}` son aceptadas, pero `{[}]` arrojan error en el momento en que el tope de la pila no coincide con el cierre. | Stack | Emparejamiento por LIFO: el último abierto es el primero en cerrarse. |
| `demo_nqueens.cpp` | La cantidad de validaciones (checks) es inmensamente mayor a la cantidad de soluciones impresas. | Recursión (Call Stack) | Backtracking: el algoritmo retrocede muchas veces antes de hallar una ruta segura. |
| `demo_maze.cpp` | Las coordenadas muestran avances seguidos de estados `BACKTRACKED` cuando choca con muros. | Stack (DFS) | Exploración exhaustiva mediante retroceso local. |
| `demo_bank.cpp` | Los clientes se distribuyen dinámicamente y las listas por ventanilla crecen y decrecen en instantes `t` simulados. | Queue | Modelado de eventos en el tiempo respetando la política FIFO. |

### Bloque 3 - Pruebas y correctitud

1. Pruebas públicas validan operaciones básicas de `push/pop/peek` para `Stack` y `enqueue/dequeue/peek` para `Queue`.
2. Las aserciones garantizan que las estructuras no lancen excepciones inesperadas en flujos normales.
3. Conversión de base: prueba de ejemplos concretos (p. ej. 10 en base 2) y coincidencia exacta entre la versión recursiva e iterativa.
4. Paréntesis: validación de casos balanceados (ej. `()[]{}`) y casos no balanceados (ej. `(]`, `((()`).
5. Evaluador: comprobación de precedencia correcta, asegurando que `2+3*4` arroje 14 y no 20.
6. NQueens se valida verificando que la cantidad de soluciones para un tablero N=8 sea exactamente 92.
7. Maze se evalúa comprobando que el camino final reportado realmente conecta el inicio con la salida sin atravesar muros.
8. `bestWindow` se valida asegurando que el nuevo cliente siempre ingrese a la ventanilla con la menor cantidad de personas en espera en ese instante de la simulación.
9. Pruebas internas cubren casos límite y mayor diversidad (vacíos, un solo elemento, saturación de datos).
10. Pasar pruebas no reemplaza el razonamiento sobre invariantes y complejidad; las pruebas solo son evidencia empírica parcial de casos específicos.
11. Un error de desbordamiento (overflow) al usar números masivos o un error lógico con caracteres delimitadores no contemplados podría pasar desapercibido en tests mínimos.

### Bloque 4 - Comparación recursivo vs iterativo

- Cociente y residuo: El residuo se apila para producir dígitos desde el menos significativo hacia el más significativo, permitiendo leer el número final en el orden correcto.
- Call stack vs pila explícita: Tienen una semántica equivalente si se gestiona el mismo contexto. La elección impacta los límites de profundidad (evitando Stack Overflow) y la claridad del control del flujo.
- En los paréntesis, la versión iterativa detecta fallos inmediatamente en el momento del cierre incorrecto. La recursiva es más compacta pero más compleja de adaptar si se añaden nuevas reglas.

**Resultados de la experimentación con conversiones de base:**
- Número 10 a base 2: Salida recursiva `1010` | Salida iterativa `1010`. Coincidencia confirmada.
- Número 255 a base 16: Salida recursiva `FF` | Salida iterativa `FF`. Coincidencia confirmada.
- Número 100 a base 8: Salida recursiva `144` | Salida iterativa `144`. Coincidencia confirmada.

### Bloque 5 - Evaluación de expresiones

1. `EvaluationResult` guarda el valor numérico calculado y la representación RPN o el estado de error en caso de sintaxis inválida.
2. Se eliminan los espacios para simplificar el proceso de tokenización y análisis léxico.
3. Detectar el menos unario requiere contexto: se identifica si el `-` aparece justo al inicio de la expresión o inmediatamente después de otro operador o paréntesis de apertura.
4. El operador factorial (`!`) es unario y postfijo; tiene la restricción matemática de aplicar solo a enteros no negativos y tiene la mayor prioridad en la evaluación.
5. La RPN se construye incrementalmente a medida que se procesan tokens de izquierda a derecha y se aplican las reglas de prioridad mediante la pila de operadores.
6. La comparación de la prioridad del operador actual frente a la prioridad del operador en el tope de la pila decide si apilamos el nuevo operador o si aplicamos los pendientes.
7. Las expresiones mal formadas (desequilibrio de paréntesis, operadores faltantes) interrumpen el flujo y reportan error claramente para evitar resultados basura.
8. Obtener RPN y valor simultáneamente es eficiente porque evita recorrer dos veces la estructura, aprovechando el mismo paso de análisis sintáctico.

**Evidencia de evaluación de expresiones matemáticas:**
- Expresión 1: `3 + 4` -> RPN: `3 4 +` -> Valor: `7`
- Expresión 2: `( 3 + 4 ) * 2` -> RPN: `3 4 + 2 *` -> Valor: `14`
- Expresión 3: `10 - 2 * 3` -> RPN: `10 2 3 * -` -> Valor: `4`
- Expresión 4: `( 10 - 2 ) * 3` -> RPN: `10 2 - 3 *` -> Valor: `24`
- Expresión 5: `5 !` -> RPN: `5 !` -> Valor: `120`
- Expresión 6: `( 2 + 3 ) !` -> RPN: `2 3 + !` -> Valor: `120`

### Bloque 6, 7, 8 - Backtracking, simulación y cierre

- N-Queens: El conflicto principal ocurre cuando dos reinas comparten la misma fila, columna o diagonal. `solution` guarda las posiciones parciales del tablero; `checks` mide los intentos. El algoritmo poda ramas muertas rápidamente.
- Maze: Los estados `AVAILABLE`, `ROUTE`, `BACKTRACKED` y `WALL` permiten marcar el progreso visualmente en la consola y evidenciar los retrocesos de la búsqueda en profundidad (DFS).
- Bank: `windows` es un vector de colas. La función `bestWindow` elige la cola más corta para simular una política de atención eficiente. La semilla aleatoria fija permite reproducir exactamente la misma secuencia temporal en cada ejecución.

**Cierre comparativo:** Pasar de usar pilas y colas como meras colecciones de datos (ADT) a utilizarlas como mecanismos de control de flujo transforma la abstracción. LIFO nos da el poder de "deshacer" acciones temporalmente para buscar caminos alternativos (backtracking), mientras que FIFO nos permite respetar líneas de tiempo lógicas (simulación). Las decisiones de diseño sobre qué estructura auxiliar usar condicionan por completo la correctitud, el rendimiento y la facilidad para razonar sobre el estado del algoritmo.

### Autoevaluación breve
- Qué puedo defender con seguridad: La comprensión conceptual teórica de las políticas LIFO/FIFO y la justificación de por qué el uso de pilas permite eliminar la recursión implícita.
- Qué todavía confundo: Los detalles finos de la implementación de algoritmos de optimización para la búsqueda en tableros muy grandes, como heurísticas avanzadas en N-Reinas.
- Qué experimento me dio mejor evidencia: Las pruebas de evaluación de expresiones, ya que ver el RPN generarse en tiempo real confirma que la precedencia de operadores se está manejando de forma perfecta a nivel algorítmico.
- Qué evidencia usaría en una sustentación: Las trazas resultantes de las conversiones de base y las expresiones evaluadas en el Bloque 5, ya que son datos objetivos y reproducibles que demuestran la teoría.