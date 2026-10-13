#include <iostream>
#include <chrono>

using namespace std;

// O(n)
long long potenciaLineal(long long base, int n) {
    long long resultado = 1;
    for (int i = 0; i < n; i++) {
        resultado = resultado * base;
    }
    return resultado;
}
// O(log n)
long long potenciaBinaria(long long base, int n) {
    long long resultado = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            resultado = resultado * base;
        }
        base = base * base;
        n = n / 2;
    }
    return resultado;
}

int main() {
    int valores[] = { 10000, 20000, 40000, 8000,16000, 32000, 64000, 128000, 256000, 512000, 1024000 };
    cout << "---------------------------------------------" << endl;
    cout << "n\tLineal(ns)\tBinaria(ns)\tCorrecto" << endl;
    for (int i = 0; i < 11; i++) {
        int n = valores[i];
        long long base = 2;

        // O(n)

        auto inicio1 = chrono::high_resolution_clock::now();
        long long resultado1 = potenciaLineal(base, n);
        auto fin1 = chrono::high_resolution_clock::now();
        long long tiempo1 = chrono::duration_cast<chrono::nanoseconds> (fin1 - inicio1).count();

        // O(log n)

        auto inicio2 = chrono::high_resolution_clock::now();
        long long resultado2 = potenciaBinaria(base, n);
        auto fin2 = chrono::high_resolution_clock::now();
        long long tiempo2 =chrono::duration_cast<chrono::nanoseconds>(fin2 - inicio2).count();

        cout << n << "\t"<< tiempo1 << "\t\t"<< tiempo2 << "\t\t";

        if (resultado1 == resultado2) {
            cout << "SI";
        }
        else {
            cout << "NO";
        }
        cout << endl;
    }

    return 0;
}