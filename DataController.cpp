#include "DataController.h"

void DataController:generateDataFile(const std::string filename&, int dataSize, double expo){
   	std::ofstream file(filename);
    	if (!file.is_open()) {
        	throw std::runtime_error("Не удалось открыть файл для записи данных.");
    	}
    	std::srand(static_cast<unsigned>(std::time(0)));

    	for (int i = 1; i <= dataSize; ++i) {
        	double noise = static_cast<double>(std::rand() % 10000 - 5000) / 500.0;
        	double value = i * std::exp(exponent) + noise;
        	file << value << '\n';
    	}
    	file.close();
}

void DataController::readFile(const std::string& filename, std::vector<double>& values) {
	std::ifstream file(filename);
	double value;
	while (file >> value) {
		values.push_back(value);
	}
}

double DataController::findExponent(const std::vector<double>& values, int num_threads) {
    	double sum_i_log_y = 0.0;
    	double sum_i_squared = 0.0;
    	omp_set_num_threads(num_threads);

	for (int i = 1; i <= values.size(); ++i) {
		double y = values[i - 1];
		sum_i_log_y += i * log(y);
        	sum_i_squared += i * i;
	}

	return sum_i_log_y / sum_i_squared;	
}

void DataController::generateAndProcessData(const drogon::HttpRequestPtr& req,
                                            std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

	const std::string fileName = "input_data.txt";
	const int dataSize = 100000;
    	const double exponent = 0.05; 
	std::vector<double> values;
    	generateDataFile(filename, dataSize, exponent);	

	readFile(fileName, values);

    	std::stringstream result;
   	result << "Calc results:\n";
    	for (int num_threads = 1; num_threads <= omp_get_max_threads(); ++num_threads) {
        	double calculatedExponent = findExponent(values, num_threads);
        	result << "Threads: " << num_threads << ", Calculated Exponent: " << calculatedExponent << "\n";
    	}

	auto resp = drogon::HttpResponse::newHttpResponse();
    	resp->setBody(result.str());
    	callback(resp);
}
