#include <iostream>
#include <vector>
#include "SlidingWindow.h"
using namespace std;
void test_caso_minimo() {
    cout << "--- Prueba 1: Caso Minimo (k=1) ---\n";
    SlidingWindow sw;
    sw.add_val(10);
    cout << "Esperado: 0 | Obtenido: " << sw.get_cost() << "\n\n";
}
void test_duplicados() {
    cout << "--- Prueba 2: Caso con Duplicados ---\n";
    SlidingWindow sw;
    vector<long long> arr = {5, 5, 5, 5};
    for(long long x : arr) {
        sw.add_val(x);
    }
    cout << "Esperado: 0 | Obtenido: " << sw.get_cost() << "\n\n";
}
void test_caso_extremo() {
    cout << "--- Prueba 3: Caso Extremo Pequeno ---\n";
    SlidingWindow sw;
    // Valores: 1, 1000000, 2. Mediana es 2.
    // Costo: |1-2| + |1000000-2| + |2-2| = 1 + 999998 + 0 = 999999
    vector<long long> arr = {1, 1000000, 2};
    for(long long x : arr) {
        sw.add_val(x);
    }
    cout << "Esperado: 999999 | Obtenido: " << sw.get_cost() << "\n\n";
}
int main() {
    cout << "=== EJECUTANDO PRUEBAS OBLIGATORIAS ===\n\n";
    test_caso_minimo();
    test_duplicados();
    test_caso_extremo();
    cout << "Todas las pruebas finalizaron correctamente.\n";
    return 0;
}