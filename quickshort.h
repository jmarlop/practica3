#ifndef DYNV_H
#define DYNV_H

#include <vector>
#include <cstdlib> // Para std::rand()

// Función para particionar el vector
int Partition(std::vector<int>& v, int ini, int fin, int pivotIndex) {
    std::swap(v[pivotIndex], v[fin]); // Colocar el pivote al final
    int pivot = v[fin]; // Pivote
    int i = ini - 1;

    // Reorganizar elementos alrededor del pivote
    for (int j = ini; j < fin; j++) {
        if (v[j] <= pivot) {
            i++;
            std::swap(v[i], v[j]);
        }
    }
    std::swap(v[i + 1], v[fin]); // Colocar pivote en su posición final
    return i + 1;
}

// Función QuickSort con pivote dinámico
void QuickSort(std::vector<int>& v, int ini, int fin, const std::string& pivotType = "last") {
    if (ini < fin) {
        int pivotIndex = fin; // Último elemento por defecto

        // Selección del pivote basada en `pivotType`
        if (pivotType == "first") {
            pivotIndex = ini; // Primer elemento
        } else if (pivotType == "random") {
            pivotIndex = ini + std::rand() % (fin - ini + 1); // Aleatorio
        } else if (pivotType == "middle") {
            pivotIndex = ini + (fin - ini) / 2; // Central
        }

        // Particionar vector
        int pivot = Partition(v, ini, fin, pivotIndex);

        // Recursión
        QuickSort(v, ini, pivot - 1, pivotType);
        QuickSort(v, pivot + 1, fin, pivotType);
    }
}

#endif // DYNV_H
