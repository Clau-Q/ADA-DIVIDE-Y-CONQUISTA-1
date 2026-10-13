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

// Potencia de matriz O(log n)
Matriz potenciaMatriz(Matriz A, int n) {
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

// Fibonacci O(n)
long long fibonacciLineal(int n) {
    if (n == 0)
        return 0;
    long long anterior = 0;
    long long actual = 1;
    for (int i = 2; i <= n; i++) {
        long long siguiente = (anterior + actual);
        anterior = actual;
        actual = siguiente;
    }
    return actual;
}
// Fibonacci O(log n)
long long fibonacciLog(int n) {
    if (n == 0) {
        return 0;
    }
    Matriz Q;
    Q.a = 1;
    Q.b = 1;
    Q.c = 1;
    Q.d = 0;
    Matriz resultado =
        potenciaMatriz(Q, n);
    return resultado.b;
}

int main() {
    int valores[] = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000, 1024000};
    cout << "FIBONACCI" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "n\tLineal(ns)\tLogaritmico(ns)\tCorrecto" << endl;
    for (int i = 0; i < 11; i++) {
        int n = valores[i];
        // O(n)

        auto inicio1 = chrono::high_resolution_clock::now();
        long long resultado1 = fibonacciLineal(n);
        auto fin1 = chrono::high_resolution_clock::now();
        long long tiempo1 = chrono::duration_cast<chrono::nanoseconds>(fin1 - inicio1).count();

        // O(log n)
        auto inicio2 = chrono::high_resolution_clock::now();
        long long resultado2 =fibonacciLog(n);
        auto fin2 =chrono::high_resolution_clock::now();
        long long tiempo2 =chrono::duration_cast<chrono::nanoseconds>(fin2 - inicio2).count();
        cout << n << "\t" << tiempo1 << "\t\t"<< tiempo2 << "\t\t";
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