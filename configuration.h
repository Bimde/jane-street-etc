#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>

#define TEAMNAME "kek"

class Configuration {
private:
  /*
    0 = prod-like
    1 = slower
    2 = empty
  */
  static int const test_exchange_index = 0;
public:
  std::string team_name;
  std::string exchange_hostname;
  int exchange_port;
  /* replace REPLACEME with your team name! */
  Configuration(bool test_mode, int exchange_index = 0);
};

#endif