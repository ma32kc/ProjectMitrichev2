#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <omp.h>
#include <chrono>
#include <map>

// Функция для чтения данных из файла
std::vector<double> readFile(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<double> values;
    double value;
    while (file >> value) {
        values.push_back(value);
    }
    return values;
}

// Функция для нахождения x методом наименьших квадратов
double findExponent(const std::vector<double> &values, int num_threads) {
    double sum_i_log_y = 0.0;
    double sum_i_squared = 0.0;
    int n = values.size();

    // Указываем количество потоков
    omp_set_num_threads(num_threads);

    #pragma omp parallel for reduction(+:sum_i_log_y, sum_i_squared)
    for (int i = 1; i <= n; ++i) {
        double y = values[i - 1];
        sum_i_log_y += i * log(y);
        sum_i_squared += i * i;
    }

    // Рассчитываем x
    double x = sum_i_log_y / sum_i_squared;
    return x;
}

int main() {
    // Пример файла с данными
    std::string filename = "data.txt";
    std::vector<double> values = readFile(filename);

    // Карта для хранения времени выполнения для каждого количества потоков
    std::map<int, double> time_results;

    // Измерение времени выполнения для разного количества потоков
    for (int num_threads = 1; num_threads <= omp_get_max_threads(); ++num_threads) {
        // Засекаем время начала
        auto start_time = std::chrono::high_resolution_clock::now();

        // Вызываем функцию для нахождения экспоненты x
        double x = findExponent(values, num_threads);

        // Засекаем время окончания
        auto end_time = std::chrono::high_resolution_clock::now();
        
        // Вычисляем затраченное время в секундах
        double duration = std::chrono::duration<double>(end_time - start_time).count();

        // Сохраняем результаты в карту
        time_results[num_threads] = duration;

        // Выводим результат для каждого количества потоков
        std::cout << "Threads: " << num_threads << ", Time: " << duration << " seconds, Calculated x: " << x << std::endl;
    }

    // Выводим результаты для построения графика
    std::cout << "\nResults for plotting:\n";
    for (const auto &entry : time_results) {
        std::cout << "Threads: " << entry.first << ", Time: " << entry.second << " seconds\n";
    }

    return 0;
}