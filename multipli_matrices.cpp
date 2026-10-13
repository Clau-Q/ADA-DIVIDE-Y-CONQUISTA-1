#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;

typedef vector<vector<long long>> Matriz;

Matriz crearMatriz(int n) {
    return Matriz(n, vector<long long>(n, 0));
}

Matriz matrizAleatoria(int n) {
    Matriz A = crearMatriz(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
        }
    }
    return A;
}

Matriz sumar(const Matriz& A, const Matriz& B) {
    int n = A.size();
    Matriz C = crearMatriz(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

Matriz restar(const Matriz& A, const Matriz& B) {
    int n = A.size();
    Matriz C = crearMatriz(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// O(n^3)
Matriz multiplicacionNormal(const Matriz& A, const Matriz& B) {
    int n = A.size();
    Matriz C = crearMatriz(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

Matriz obtenerParte(const Matriz& A, int fila, int columna, int tam) {
    Matriz parte = crearMatriz(tam);
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            parte[i][j] = A[fila + i][columna + j];
        }
    }
    return parte;
}

Matriz unir(const Matriz& C11, const Matriz& C12, const Matriz& C21, const Matriz& C22) {
    int mitad = C11.size();
    int n = mitad * 2;
    Matriz C = crearMatriz(n);
    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mitad] = C12[i][j];
            C[i + mitad][j] = C21[i][j];
            C[i + mitad][j + mitad] = C22[i][j];
        }
    }
    return C;
}

// O(n^2.81)
Matriz strassen(const Matriz& A, const Matriz& B) {
    int n = A.size();
    if (n <= 64) {
        return multiplicacionNormal(A, B);
    }
    int mitad = n / 2;

    Matriz A11 = obtenerParte(A, 0, 0, mitad);
    Matriz A12 = obtenerParte(A, 0, mitad, mitad);
    Matriz A21 = obtenerParte(A, mitad, 0, mitad);
    Matriz A22 = obtenerParte(A, mitad, mitad, mitad);

    Matriz B11 = obtenerParte(B, 0, 0, mitad);
    Matriz B12 = obtenerParte(B, 0, mitad, mitad);
    Matriz B21 = obtenerParte(B, mitad, 0, mitad);
    Matriz B22 = obtenerParte(B, mitad, mitad, mitad);

    Matriz P1 = strassen(A11, restar(B12, B22));
    Matriz P2 = strassen(sumar(A11, A12), B22);
    Matriz P3 = strassen(sumar(A21, A22), B11);
    Matriz P4 = strassen(A22, restar(B21, B11));
    Matriz P5 = strassen(sumar(A11, A22), sumar(B11, B22));
    Matriz P6 = strassen(restar(A12, A22), sumar(B21, B22));
    Matriz P7 = strassen(restar(A11, A21), sumar(B11, B12));

    Matriz C11 = sumar(restar(sumar(P5, P4), P2), P6);
    Matriz C12 = sumar(P1, P2);
    Matriz C21 = sumar(P3, P4);
    Matriz C22 = restar(restar(sumar(P5, P1), P3), P7);

    return unir(C11, C12, C21, C22);
}

bool iguales(const Matriz& A, const Matriz& B) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] != B[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int valores[] = { 64, 128, 256, 512, 1024 };
    cout << "---------------------------------------------" << endl;
    cout << "n\tNormal(ns)\t\tStrassen(ns)\tCorrecto" << endl;
    for (int i = 0; i < 5; i++) {
        int n = valores[i];
        Matriz A = matrizAleatoria(n);
        Matriz B = matrizAleatoria(n);

        // O(n^3)

        auto inicio1 = chrono::high_resolution_clock::now();
        Matriz resultado1 = multiplicacionNormal(A, B);
        auto fin1 = chrono::high_resolution_clock::now();
        long long tiempo1 = chrono::duration_cast<chrono::nanoseconds>(fin1 - inicio1).count();

        // O(n^2.81)

        auto inicio2 = chrono::high_resolution_clock::now();
        Matriz resultado2 = strassen(A, B);
        auto fin2 = chrono::high_resolution_clock::now();
        long long tiempo2 = chrono::duration_cast<chrono::nanoseconds>(fin2 - inicio2).count();

        cout << n << "\t" << tiempo1 << "\t\t" << tiempo2 << "\t\t";

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