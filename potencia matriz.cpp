#include <iostream>
#include <chrono>

using namespace std;

struct Matriz {

    long long a;
    long long b;
    long long c;
    long long d;
};

Matriz multiplicar(Matriz A, Matriz B) {
    Matriz C;
    C.a = A.a * B.a + A.b * B.c;
    C.b = A.a * B.b + A.b * B.d;
    C.c = A.c * B.a + A.d * B.c;
    C.d = A.c * B.b + A.d * B.d;
    return C;
}

Matriz identidad() {
    Matriz I;
    I.a = 1;
    I.b = 0;
    I.c = 0;
    I.d = 1;
    return I;
}

// O(n)
Matriz potenciaLineal(Matriz A, int n) {
    Matriz resultado = identidad();
    for (int i = 0; i < n; i++) {
        resultado = multiplicar(resultado, A);
    }
    return resultado;
}

// O(log n)
Matriz potenciaBinaria(Matriz A, int n) {
    Matriz resultado = identidad();
    while (n > 0) {
        if (n % 2 == 1) {
            resultado = multiplicar(resultado, A);
        }
        A = multiplicar(A, A);
        n = n / 2;
    }
    return resultado;
}

bool iguales(Matriz A, Matriz B) {
    return A.a == B.a &&
           A.b == B.b &&
           A.c == B.c &&
           A.d == B.d;
}

int main() {
    int valores[] = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000, 1024000};
    Matriz A;
    A.a = 1;
    A.b = 1;
    A.c = 1;
    A.d = 0;
    cout << "POTENCIA DE MATRIZ 2x2" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "n\tLineal(ns)\tBinaria(ns)\tCorrecto" << endl;
    for (int i = 0; i < 11; i++) {
        int n = valores[i];

        // O(n)
        auto inicio1 = chrono::high_resolution_clock::now();
        Matriz resultado1 = potenciaLineal(A, n);
        auto fin1 = chrono::high_resolution_clock::now();
        long long tiempo1 = chrono::duration_cast<chrono::nanoseconds>(fin1 - inicio1).count();
        // O(log n)
        auto inicio2 = chrono::high_resolution_clock::now();
        Matriz resultado2 = potenciaBinaria(A, n);
        auto fin2 = chrono::high_resolution_clock::now();
        long long tiempo2 =  chrono::duration_cast<chrono::nanoseconds>(fin2 - inicio2).count();

        cout << n << "\t"<< tiempo1 << "\t\t"<< tiempo2 << "\t\t";

        if (iguales(resultado1, resultado2)) {
            cout << "SI";
        }
        else {
            cout << "NO";
        }
        cout << endl;
    }

    return 0;
}