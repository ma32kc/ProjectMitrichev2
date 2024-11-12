#pragma once
#include <drogon/HttpController.h>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <omp.h>

class DataController : public drogon::HttpController<DataController> {
public:
	METHOD_LIST_BEGIN
    	ADD_METHOD_TO(DataController::generateAndProcessData, "/processData", drogon::Get);
    	METHOD_LIST_END

	void generateAndProcessData(const drogon::HttpRequestPtr& req,
                                std::function<void(const drogon::HttpResponsePtr&)>&& callback);

private:
	void generateDataFile(const std::string& filename, int dataSize, double exponent);
	void readFile(const std::string& filename, std::vector<double>& values);
	double findExponent(const std::vector<double>& values, int num_threads);
};
