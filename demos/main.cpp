#include <iostream>
#include <vector>
#include "SlidingWindow.h"
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<long long> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    SlidingWindow sw;
    for (int i = 0; i < k; i++) {
        sw.add_val(arr[i]);
    }
    cout << sw.get_cost();
    for (int i = k; i < n; i++) {
        sw.remove_val(arr[i - k]);
        sw.add_val(arr[i]);
        cout << " " << sw.get_cost();
    }
    cout << "\n";
    return 0;
}