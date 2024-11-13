#include <iostream>
#include <string>
#include <stdexcept>

// Assuming DataController is in the same directory or properly included in the project
#include "DataController.h"

void testGenerateAndProcessData(const std::string& fileName, int dataSize, double exponent) {
    try {
        // Print a message indicating the start of the test
        std::cout << "Running test for generateAndProcessData with dataSize=" << dataSize
                  << " and exponent=" << exponent << std::endl;

        // Create a DataController instance
        DataController controller;

        // Call the function to be tested
        controller.generateAndProcessData(fileName, dataSize, exponent);

        // Print a success message if no exceptions were thrown
        std::cout << "Test passed: generateAndProcessData completed successfully.\n" << std::endl;
    }
    catch (const std::exception& e) {
        // Print an error message if an exception was thrown
        std::cerr << "Test failed: " << e.what() << "\n" << std::endl;
    }
}

int main() {
    // Test parameters
    const std::string fileName = "test_data.txt";
    const int dataSize = 10000;
    const double exponent = 0.05;

    // Run the test three times
    for (int i = 1; i <= 3; ++i) {
        std::cout << "Starting test run #" << i << std::endl;
        testGenerateAndProcessData(fileName, dataSize, exponent);
    }

    return 0;
}

