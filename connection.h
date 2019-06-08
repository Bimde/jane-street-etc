/* Connection establishes a read/write connection to the exchange,
   and facilitates communication with it */
class Connection {
  private:
    FILE * in;
    FILE * out;
    int socket_fd;
  public:
    Connection(Configuration configuration);

    /** Send a string to the server */
    void send_to_exchange(std::string input);

    /** Read a line from the server, dropping the newline at the end */
    string read_from_exchange();
};