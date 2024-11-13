#include "DataController.h"

void DataController::generateDataFile(const std::string& filename, int dataSize, double exponent){
   	std::ofstream file(filename, std::ios::out | std::ios::trunc);
    	if (!file.is_open()) {
        	throw std::runtime_error("Unable to open file");
    	}
    	std::srand(static_cast<unsigned>(std::time(0)));

    	for (int i = 1; i <= dataSize; ++i) {
        	double noise = static_cast<double>(std::rand() % 5000) / 500.0;
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
	
	/* #pragma omp parallel
    	{
        	#pragma omp single
        	std::cout << "Actual threads used: " << omp_get_num_threads() << std::endl;
    	}*/

	#pragma omp parallel for reduction(+:sum_i_log_y, sum_i_squared)
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
    	generateDataFile(fileName, dataSize, exponent);	

	readFile(fileName, values);

    	/*std::stringstream result;
   	result << "Calc results:\n";*/
	//result << "Max OpenMP threads available: " << omp_get_max_threads()<< '\n';
	Json::Value resultArray(Json::arrayValue);
    	for (int num_threads = 1; num_threads <= 4; ++num_threads) {
        	auto start_time = std::chrono::high_resolution_clock::now();
		double calculatedExponent = findExponent(values, num_threads);
		auto end_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end_time - start_time;
        	//result << "Threads: " << num_threads << ", Calculated Exponent: " << calculatedExponent << "; It took: "<< duration.count() << " seconds\n";
		
        	Json::Value resultObject;
        	resultObject["exponent"] = calculatedExponent;         
        	resultObject["threads"] = num_threads;                   
		resultObject["duration"] = duration.count();             

        	resultArray.append(resultObject);
	}

	/*auto resp = drogon::HttpResponse::newHttpResponse();
    	resp->setBody(result.str());*/
    	auto resp = drogon::HttpResponse::newHttpJsonResponse(resultArray);
    	callback(resp);
}


void DataController::generateAndProcessData(const std::string& fileName, const int dataSize, const double exponent) {

	std::vector<double> values;
    	generateDataFile(fileName, dataSize, exponent);	

	readFile(fileName, values);

    	for (int num_threads = 1; num_threads <= 4; ++num_threads) {
        	auto start_time = std::chrono::high_resolution_clock::now();
		double calculatedExponent = findExponent(values, num_threads);
		auto end_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end_time - start_time;
		std::cout << "Threads: " << num_threads << ", Calculated Exponent: " << calculatedExponent << "; It took: "<< duration.count() << " seconds\n";
		
	}
}
