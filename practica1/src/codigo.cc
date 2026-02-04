#include <iostream>
#include "data.h"

int main() {
    Data datos;
    int opcion;
    // Menú simple para elegir carga o generación
    std::cout << "Inferencia Condicional - Distribuciones Binarias\n";
    std::cout << "1. Generar aleatoriamente\n2. Cargar desde CSV\nSeleccion: ";
    std::cin >> opcion;

    if (opcion == 1) {
        int n;
        std::cout << "Introduce el número de variables (N): ";
        std::cin >> n;
        datos.generacionAleatoria(n);
    } else {
        std::string ruta;
        std::cout << "Introduce la ruta del archivo .csv: ";
        std::cin >> ruta;
        datos.cargarArchivo(ruta);
    }

    datos.mostrarDistribucion();

    return 0;
}