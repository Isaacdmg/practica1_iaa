#include "data.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

Data::Data() : variable_count(0) {}

void Data::inicializarEstructura(int n) {
    variable_count = n;
    // Punto 3: Tamaño 2^N para p[k]
    probability_distribution.assign(1 << n, 0.0);
}

// Implementación manual del cálculo del índice k 
int Data::stringBinarioAInt(const std::string& bin) const {
    int decimal = 0;
    int base = 1;
    // Recorremos de derecha a izquierda: Bit 0 (derecha) es X1 
    for (int i = bin.length() - 1; i >= 0; --i) {
        if (bin[i] == '1') {
            decimal += base;
        }
        base *= 2;
    }
    return decimal;
}

void Data::cargarArchivo(const std::string& ruta_archivo) {
    std::ifstream ifs(ruta_archivo);
    if (!ifs.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    std::string linea;
    bool primera_linea = true;

    while (std::getline(ifs, linea)) {
        if (linea.empty()) continue;

        std::string binary_str = "";
        std::string prob_str = "";
        int counter = 0;
        while (counter < linea.size() && linea[counter] != ',') {
            binary_str += linea[counter];
            ++counter;
        }
        ++counter; // Saltamos la coma
        while (counter < linea.size()) {
            prob_str += linea[counter];
            ++counter;
        }

        if (primera_linea) {
            inicializarEstructura(binary_str.length()); 
            primera_linea = false;
        }

        // Convertimos la máscara al índice decimal k 
        int k = stringBinarioAInt(binary_str);
        if (k < probability_distribution.size()) {
            probability_distribution[k] = std::stod(prob_str); 
        }
    }
    ifs.close();
}

void Data::generacionAleatoria(int n) {
    inicializarEstructura(n);
    double suma = 0.0;
    for (int i = 0; i < (1 << n); ++i) {
        double val = static_cast<double>(rand() % 100) + 1.0; // Evitamos 0s totales
        probability_distribution[i] = val;
        suma += val;
    }
    // Normalización: suma de todas debe ser 1 
    for (double &p : probability_distribution) {
        p /= suma;
    }
}

void Data::mostrarDistribucion() const {
    std::cout << "\n--- Distribución Conjunta Cargada ---" << std::endl;
    for (int i = 0; i < (int)probability_distribution.size(); ++i) {
        std::cout << "Índice " << i << ": " << std::fixed << std::setprecision(5) 
                  << probability_distribution[i] << std::endl;
    }
}

int Data::getVariableCount() const { return variable_count; }
const std::vector<double>& Data::getProbs() const { return probability_distribution; }