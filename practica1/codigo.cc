#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <cmath>
#include <string>

#include "data.h"



int main() {
  // interfaz inicial
  std::cout << "Generar (1) o cargar (2) tabla" << std::endl;
  int opcion;
  std::cin >> opcion;
  Data datos;
  if (opcion == 1) {
    int n_variables;
    std::cout << "Introduzca el número de variables: ";
    std::cin >> n_variables;
    datos.generacionAleatoria(n_variables);
  } else if (opcion == 2) {
    std::string ruta_archivo;
    std::cout << "Introduzca la ruta del archivo: ";
    std::cin >> ruta_archivo;
    datos.cargarArchivo(ruta_archivo);
  } else {
    std::cout << "Opción inválida" << std::endl;
    return 1;
  }

  // print tabla

  int n_variables{datos.getVariableCount};
  std::vector<bool> mascara_condicionadas(n_variables, false);
  std::vector<bool> mascara_interes(n_variables, false);
  
  opcion = -1;
  while (opcion != 0) {
    // selección variables
    int variable;
    std::cout << "Seleccione una variable condicionada: ";
    std::cin >> variable;
    if (variable > n_variables) {
      std::cout << "Error: variable no existente" << std::endl;
      continue;
    }
    mascara_condicionadas[variable - 1] = true;
    
    std::cout << "Quiere añadir otra variable condicionada?" << std::endl << "No (0)." << std::endl << "Sí (1)." << std::endl;
    std::cin >> opcion;
  }

  


  return 0;
}

