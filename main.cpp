#include <drogon/drogon.h>
#include "DataController.h"

int main() {
	drogon::app().addListener("0.0.0.0", 8848);
	drogon::app().setThreadNum(4);
	drogon::app().run();

	return 0;
}
