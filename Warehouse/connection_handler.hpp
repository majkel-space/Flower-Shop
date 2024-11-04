class ConnectionHandler
{
  public:
    explicit ConnectionHandler(int);

    void operator()()
    {
        HandleConnection();
    }

  private:
    void HandleConnection();
    void ReadMessage();
    void WriteMessage();

    int client_socket_{};
};

void* HandleClient(void* arg);
