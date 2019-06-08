#include <string>

#include "connection.h"
#include "configuration.h"
#include "strategy.h"
#include "portfolio.h"

int main(int argc, char *argv[]) {
	bool isTest = true;
	int testEnv = 0;

	if (argc >= 1) {
		if (std::string(argv[1]) == "prod") {
			isTest = false;
		}
	}

	if (argc >= 2) {
		if (std::string(argv[2]) == "0") {
			testEnv = 0;
		}
		if (std::string(argv[2]) == "1") {
			testEnv = 1;
		}
		if (std::string(argv[2]) == "2") {
			testEnv = 2;
		}
	}

	Configuration cfg(isTest, testEnv);

	Connection cxn(cfg);

	Portfolio portfolio(cxn);

	portfolio.run();
}