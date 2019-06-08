#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "configuration.h"

/* Connection establishes a read/write connection to the exchange,
   and facilitates communication with it */
class Connection {
  private:
    FILE * in;
    FILE * out;
    int socket_fd;
  public:
    Connection(Configuration& configuration);

    /** Send a string to the server */
    void send_to_exchange(std::string& input);

    /** Read a line from the server, dropping the newline at the end */
    std::string read_from_exchange();
};

#endif