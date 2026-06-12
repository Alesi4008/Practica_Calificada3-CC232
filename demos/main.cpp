#include <iostream>
#include <vector>
#include <algorithm>
#include "SlidingWindow.h"
using namespace std;
long long costo_ingenuo(vector<long long> arr){
    sort(arr.begin() , arr.end());
    long long med = arr[arr.size()/2];
    long long cost = 0 ;
    for (long long x : arr) cost += abs(x-med);
    return cost;
}
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
    cout << "\n Reto especifico\n";
    SlidingWindow sw2;
    vector<long long> duplicados = { 7 , 7 ,7 ,7 ,10 ,7 };
    for(long long x : duplicados) sw2.add_val(x);
    long long costo_optimo = sw2.get_cost();
    long long costo_in = costo_ingenuo(duplicados);
    cout << "Costo optimo : "<< costo_optimo << "\n" ;
    cout << "Costo ingenuo : "<< costo_in << "\n" ;
    if ( costo_optimo == costo_in) cout << "Correctitud validada \n";
    return 0;
}