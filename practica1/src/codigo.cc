/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial Avanzada
 *
 * @author Andrés David Riera Rivera, Alejandro Feo Martín e Isaac Domínguez Fajardo
 * @since Feb 04 2026
 * @brief Programa principal para el cálculo de probabilidades condicionadas.
 *        Por ahora, genera o carga una distribución conjunta y permite seleccionar
 *        variables condicionadas y variables de interés de forma intutiva.
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <cmath>
#include <string>
#include <ctime>
#include "data.h"


/**
 * @brief Punto de entrada del programa.
 *        Permite generar o cargar una distribución de probabilidad,
 *        seleccionar variables condicionadas y de interés, e identificar
 *        las variables a marginalizar.
 * @return int: 0 si todo va bien, 1 si hay error.
 */
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
    // semilla para el numero aleatorio
    std::srand(std::time(nullptr));
    datos.generateRandomDistribution(n_variables);
  } else if (opcion == 2) {
    std::string ruta_archivo;
    std::cout << "Introduzca la ruta del archivo: ";
    std::cin >> ruta_archivo;
    datos.cargarArchivo(ruta_archivo);
  } else {
    std::cerr << "Opción inválida" << std::endl;
    return 1;
  }

  datos.printDistribution();
  
  // selección variables condicionadas
  int n_variables{datos.getVariableCount()};
  std::cout << "Número de variables: " << n_variables << std::endl;
  std::vector<bool> variables_condicionadas(n_variables, false);
  std::vector<int> valores_condicionadas(n_variables, 0);
  opcion = -1;
  while (opcion != 0) {
    int variable;
    std::cout << "Seleccione una variable condicionada: ";
    std::cin >> variable;
    if (variable > n_variables || variable <= 0) {
      std::cerr << "Error: variable no existente" << std::endl;
      continue;
    }
    variables_condicionadas[variable - 1] = true;
    
    // asignar valor a la variable
    int valor = -1;
    while (valor != 0 && valor != 1) {
      std::cout << "Asigne un valor a la variable (0 o 1): ";
      std::cin >> valor;
      if (valor != 0 && valor != 1) {
        std::cerr << "Error: valor inválido" << std::endl;
      } else {
        valores_condicionadas[variable - 1] = valor;
      }
    }
    
    std::cout << "Se ha añadido la variable X" << variable << " como variable condicionada con el valor " << valor << std::endl;

    std::cout << "Quiere añadir otra variable condicionada?" << std::endl << "No (0)." << std::endl << "Sí (1)." << std::endl;
    std::cin >> opcion;
  }

  std::cout << "Variables condicionadas (valor): ";
  for (int i = 0; i < variables_condicionadas.size(); i++) {
    if(variables_condicionadas[i]) {
      std::cout << "X" << i + 1 << " (" << valores_condicionadas[i] << ") ";
    }
  }
  std::cout << std::endl;

  // selección variables de interés
  std::vector<bool> variables_interes(n_variables, false);
  opcion = -1;
  while (opcion != 0) {
    int variable;
    std::cout << "Seleccione una variable de interés: ";
    std::cin >> variable;
    if (variable > n_variables || variable <= 0) {
      std::cout << "Error: variable no existente" << std::endl;
      continue;
    }
    variables_interes[variable - 1] = true;

    std::cout << "Se ha añadido la variable X" << variable << " como variable de interés" << std::endl;
    
    std::cout << "Quiere añadir otra variable de interés?" << std::endl << "No (0)." << std::endl << "Sí (1)." << std::endl;
    std::cin >> opcion;
  }
  
  std::cout << "Variables de interés: ";
  for (int i = 0; i < variables_interes.size(); i++) {
    if(variables_interes[i]) {
      std::cout << "X" << i + 1 << " ";
    }
  }
  std::cout << std::endl;

  // Resto de variables
  std::vector<bool> variables_a_marginalizar(n_variables, false);
  for (int i = 0; i < n_variables; i++) {
    if (variables_condicionadas[i] != true && variables_interes[i] != true) {
      variables_a_marginalizar[i] = true;
    }
  }
  std::cout << "Variables a marginalizar: ";
  for (int i = 0; i < variables_a_marginalizar.size(); i++) {
    if(variables_a_marginalizar[i]) {
      std::cout << "X" << i + 1 << " ";
    }
  }
  std::cout << std::endl;

  return 0;
}

