#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

class Data {
public:
    Data();
    
    // Punto 1.1: Carga desde archivo CSv
    void cargarArchivo(const std::string& ruta_archivo);
    
    // Punto 1.2: Generación aleatoria y normalización
    void generacionAleatoria(int n);
    
    // Punto 3: Acceso a la distribución conjunta p[k]
    void mostrarDistribucion() const;
    
    // Getters
    int getVariableCount() const;
    const std::vector<double>& getProbs() const;
    // Utilidad para convertir máscara binaria a índice decimal
    int stringBinarioAInt(const std::string& binario) const;

private:
    std::vector<double> probability_distribution; // El array p[k] 
    int variable_count;
    
    // Utilidad para limpiar y redimensionar el vector
    void inicializarEstructura(int n);
};

#endif