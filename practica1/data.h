#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <cmath>
#include <string>

class Data {
 public:
  Data() {};
  double& probability(int binary_index) { return probability_distribution[binaryToDecimal(binary_index) - 1]; }
  void cargarArchivo(const std::string& ruta_archivo);
  void eraseChangeSize(int amount_variables);
  void generacionAleatoria(int n);
  void setVariableCount(int n);
  int getVariableCount() { return variable_count;};
  void randomVector(int n);
 private:
  std::vector<double> probability_distribution;
  int binaryToDecimal(int binary);
  int variable_count{0};
};

void Data::cargarArchivo(const std::string& ruta_archivo) {
  std::ifstream ifs;
  ifs.open(ruta_archivo, std::ios_base::in);
  int line_count{0};
  std::string linea;
  while (std::getline(ifs, linea)) {
    std::string binary = "";
    std::string probability = "";

    int counter{0};
    while (linea[counter] != ',') {
        binary += linea[counter];
        ++counter;
    }
    ++counter;
    while (counter < linea.size()) {
        probability += linea[counter];
        ++counter;
    }
    ++line_count;
    if (line_count == 1) {
      int n = binary.size();
      variable_count = n;
      eraseChangeSize(variable_count);
    }
    probability(std::stoi(binary)) = std::stod(probability);
  }
  
}

void Data::eraseChangeSize(int amount_variables) {
  probability_distribution.clear();
  probability_distribution.resize(pow(2, amount_variables));
}


int Data::binaryToDecimal(int binary) {
  int num = binary;
  int dec_value = 0;
  int base = 1;
  int temp = num;
  while (temp) {
    int last_digit = temp % 10;
    temp = temp / 10;
    dec_value += last_digit * base;
    base = base * 2;
  }
  return dec_value;
}

void Data::setVariableCount(int n) {
  variable_count = n;
}

void Data::randomVector(int n) {
  setVariableCount(n);
  eraseChangeSize(n);
  std::vector<double> random_double;
  double suma;
  for (int i = 0; i < pow(2, n); ++i) {
    double number = static_cast<double>(std::rand() % 100);
    suma += number;
    random_double.push_back(number);
  }
  for (double rnd : random_double) {
    rnd = rnd / suma;
  }

  probability_distribution = rnd;
}


#endif