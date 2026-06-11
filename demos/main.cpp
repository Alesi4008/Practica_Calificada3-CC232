#include <iostream>
#include <vector>
#include "SlidingWindow.h"
using namespace std;
int main() {
    // Optimizacion de lectura/escritura para evitar el TLE en CSES
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<long long> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    SlidingWindow sw;
    
    // Cargamos la primera ventana
    for (int i = 0; i < k; i++) {
        sw.add_val(arr[i]);
    }
    cout << sw.get_cost();

    // Empezamos a deslizar la ventana por el resto del arreglo
    for (int i = k; i < n; i++) {
        sw.remove_val(arr[i - k]); // sacamos el elemento que quedo atras
        sw.add_val(arr[i]);        // metemos el nuevo
        cout << " " << sw.get_cost();
    }
    cout << "\n";
    
    return 0;
}