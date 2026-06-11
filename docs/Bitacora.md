# Bitácora del Proyecto

### Día 1 (02/06/2026)
* Creación del repositorio en GitHub y primera lectura del problema asignado (CSES 1077).
* Armé la estructura básica de carpetas (`src`, `include`, `tests`) para mantener el orden de la PC3.

### Día 2 (05/06/2026)
* Implementé la lógica principal de la ventana deslizante. 
* Decidí usar dos `std::multiset` para ir dividiendo los datos en dos mitades y así mantener la mediana accesible.
* Creé el `CMakeLists.txt` inicial para probar la compilación del `main.cpp`.

### Día 3 (06/06/2026)
* Me trabé un poco viendo cómo manejar los datos repetidos (duplicados), así que agregué `test.cpp` para aislar casos manuales.
* Ajusté el `CMakeLists.txt` para que compile correctamente el ejecutable de pruebas (`test_pc3`).

### Día 4 (07/06/2026)
* Día dedicado a la documentación. Llené el `README.md` siguiendo estrictamente la plantilla de las indicaciones.
* Resolví las preguntas del problema en `respuestas_obligatorias.md`.
* Agregué el `.gitignore` porque me di cuenta de que se estaban subiendo binarios al repositorio por error. Guardé las salidas de las pruebas en la carpeta `resultados/`.

### Día 5 (09/06/2026)
* Revisión e integración de las actividades teóricas de las semanas 4, 5 y 6.
* Última limpieza de código, probé clonar el repositorio en una carpeta limpia para ver si el build de CMake seguía funcionando sin errores. Todo listo para grabar.