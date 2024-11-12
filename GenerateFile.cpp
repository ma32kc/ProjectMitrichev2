#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

void generateDataFile(const std::string &filename, int dataSize, double exponent) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file!\n";
        return;
    }

    std::srand(static_cast<unsigned>(std::time(0)));

    for (int i = 1; i <= dataSize; ++i) {
        double noise = static_cast<double>(std::rand() % 10000 - 5000) / 500.0;
        double value = i * std::exp(exponent) + noise;
        file << value << "\n";
    }

    file.close();
   // std::cout << "data has been saved to: " << filename << std::endl;
}

int main() {
	std::string fileName = "input_data.txt";
	int dataSize = 100000;

	double expo = 0.05;
	generateDataFile(fileName, dataSize, expo);

	return 0;
}
