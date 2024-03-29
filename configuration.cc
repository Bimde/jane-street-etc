#include <string>

#include "configuration.h"

Configuration::Configuration(bool test_mode, int exchange_index) : 
	team_name(TEAMNAME) {
    exchange_port = 20000; /* Default text based port */
    if(true == test_mode) {
      exchange_hostname = "test-exch-" + team_name;
      exchange_port += test_exchange_index;
    } else {
      exchange_hostname = "production";
    }
  }