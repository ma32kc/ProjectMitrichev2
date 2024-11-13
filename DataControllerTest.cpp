#include <gtest/gtest.h>
#include <drogon/HttpAppFramework.h>
#include "DataController.h"

class DataControllerTest : public ::testing::Test {
protected:
    DataController controller;
};

// Тест для generateDataFile
TEST_F(DataControllerTest, GenerateDataFile) {
    std::string filename = "test_data.txt";
    int dataSize = 100;
    double exponent = 2.0;

    controller.generateDataFile(filename, dataSize, exponent);

    // Проверяем, что файл существует и не пуст
    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());
    file.seekg(0, std::ios::end);
    ASSERT_GT(file.tellg(), 0);
    file.close();

    // Удаляем файл после теста
    std::remove(filename.c_str());
}

// Тест для readFile
TEST_F(DataControllerTest, ReadFile) {
    std::string filename = "test_data.txt";
    std::vector<double> values = {1.0, 2.0, 3.0};

    // Записываем тестовые данные
    std::ofstream file(filename);
    for (const auto& value : values) {
        file << value << "\n";
    }
    file.close();

    std::vector<double> result;
    controller.readFile(filename, result);

    // Проверяем, что данные прочитаны корректно
    ASSERT_EQ(result.size(), values.size());
    for (size_t i = 0; i < values.size(); ++i) {
        ASSERT_EQ(result[i], values[i]);
    }

    std::remove(filename.c_str());
}

// Тест для findExponent
TEST_F(DataControllerTest, FindExponent) {
    std::vector<double> values = {1.0, 4.0, 9.0, 16.0};
    int num_threads = 2;

    double exponent = controller.findExponent(values, num_threads);

    // Проверяем, что найденное значение корректно
    ASSERT_NEAR(exponent, 2.0, 0.1);
}
