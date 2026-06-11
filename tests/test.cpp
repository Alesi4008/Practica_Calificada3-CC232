#include <iostream>
#include <vector>
#include "SlidingWindow.h"

using namespace std;

void test_caso_minimo() {
    SlidingWindow sw;
    sw.add_val(10);
    long long res = sw.get_cost();
    if (res == 0) {
        cout << "Test 1 (minimo): OK\n";
    } else {
        cout << "Test 1 fallo. Esperaba 0, dio " << res << "\n";
    }
}

void test_duplicados() {
    SlidingWindow sw;
    vector<long long> arr = {5, 5, 5, 5};
    for(long long x : arr) sw.add_val(x);
    
    long long res = sw.get_cost();
    if (res == 0) {
        cout << "Test 2 (duplicados): OK\n";
    } else {
        cout << "Test 2 fallo. Dio " << res << "\n";
    }
}

void test_caso_extremo() {
    SlidingWindow sw;
    // Valores: 1, 1000000, 2 -> Mediana es 2.
    // Costo: |1-2| + |1000000-2| + |2-2| = 1 + 999998 + 0 = 999999
    sw.add_val(1);
    sw.add_val(1000000);
    sw.add_val(2);
    
    long long res = sw.get_cost();
    if (res == 999999) {
        cout << "Test 3 (extremo): OK\n";
    } else {
        cout << "Test 3 fallo! dio " << res << "\n";
    }
}

int main() {
    cout << "Corriendo pruebas manuales...\n";
    test_caso_minimo();
    test_duplicados();
    test_caso_extremo();
    cout << "Fin de las pruebas.\n";
    return 0;
}