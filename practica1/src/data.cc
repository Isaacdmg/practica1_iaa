/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial Avanzada
 *
 * @author Andrés David Riera Rivera, Alejandro Feo Martín e Isaac Domínguez Fajardo
 * @since Feb 04 2026
 * @brief Implementación de la clase Data.
 */

#include "data.h"
#include <bitset>

/**
 * @brief Carga una distribución desde un archivo CSV.
 * @param ruta_archivo Ruta del archivo.
 */
void Data::cargarArchivo(const std::string& ruta_archivo) {
  std::ifstream ifs;
  ifs.open(ruta_archivo, std::ios_base::in);
  if (!ifs.is_open()) {
    std::cerr << "Error al abrir el archivo." << std::endl;
    return;
  }
  int line_count{0};
  std::string linea;
  while (std::getline(ifs, linea)) {
    std::string binary = "";
    std::string prob_str = "";

    int counter{0};
    while (linea[counter] != ',') {
        binary += linea[counter];
        ++counter;
    }
    ++counter;
    while (counter < linea.size()) {
        prob_str += linea[counter];
        ++counter;
    }
    ++line_count;
    if (line_count == 1) {
      int n = binary.size();
      variable_count = n;
      eraseChangeSize(variable_count);
    }
    probability(std::stoi(binary)) = std::stod(prob_str);
  }
}

/**
 * @brief Redimensiona el vector de probabilidades, borrando sus elementos.
 * @param amount_variables Número de variables.
 */
void Data::eraseChangeSize(int amount_variables) {
  probability_distribution.clear();
  probability_distribution.resize(pow(2, amount_variables));
}

/**
 * @brief Convierte un número binario a decimal.
 * @param binary Número binario representado como entero.
 * @return Valor decimal equivalente.
 */
int Data::binaryToDecimal(int binary) {
  int number = binary;
  int decimal_value = 0;
  int base = 1;
  int temporal = number;
  while (temporal) {
    int last_digit = temporal % 10;
    temporal = temporal / 10;
    decimal_value += last_digit * base;
    base = base * 2;
  }
  return decimal_value;
}

/**
 * @brief Cambia el valor del número de variables de nuestra distribución 
 * @param n Nuevo valor
 */
void Data::setVariableCount(int n) {
  variable_count = n;
}

/**
 * @brief Genera una distribución conjunta aleatoria 
 * @param n Número de variables
 */
void Data::generateRandomDistribution(int n) {
  setVariableCount(n);
  eraseChangeSize(n);
  std::vector<double> random_double;
  double suma = 0.0;
  for (int i = 0; i < pow(2, n); ++i) {
    double number = static_cast<double>(std::rand() % 100);
    suma += number;
    random_double.push_back(number);
  }
  for (double& rnd : random_double) {
    rnd = rnd / suma;
  }

  probability_distribution = random_double;
}

/**
 * @brief Imprime en pantalla la distribución conjunta, el vector con sus componentes. 
 */
void Data::printDistribution() {
  std::cout << std::endl << "- Distribución conjunta actual - " << std::endl;
  for (int i = 0; i < probability_distribution.size(); ++i) {
    std::cout << "p[" << i << "] : " << std::fixed << std::setprecision(5) 
              << probability_distribution[i] << std::endl;
  }
}
