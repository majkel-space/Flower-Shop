class ConnectionHandler
{
  public:
    ConnectionHandler(int);
    void HandleConnection();

  private:
    void ReadMessage();
    void WriteMessage();

    int client_socket_{};
};

void* HandleClient(void* arg);
