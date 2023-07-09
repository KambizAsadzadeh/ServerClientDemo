#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
# endif
#else
#error There is no PT's common file!
#endif

#include <iostream>
#include <cstring>      // For string manipulation

#ifdef _WIN32
#include <winsock2.h> // For Windows sockets
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h> // For Unix-like sockets
#include <unistd.h>     // For Unix-like close()
#include <arpa/inet.h>  // For Unix-like sockaddr_in and inet_ntoa
#endif

#ifdef _WIN32
#define CLOSE_SOCKET(s) closesocket(s)
using socklen_t = int;
#else
#define CLOSE_SOCKET(s) close(s)
#endif

/**
 * @brief The private structure holding server-related data.
 */
struct PrivateServer final
{
    int port;               //!< The port number.
    int socketDescriptor;   //!< The socket descriptor.
    int clientSocket;       //!< The client socket descriptor.
};

/**
 * @brief The Server class for handling server-side operations.
 */
class Server {
public:
    /**
     * @brief Constructs a Server object with the specified port.
     * @param port The port number to listen on.
     */
    Server(int port);

    /**
     * @brief Starts the server and initializes the necessary resources.
     * @return True if the server starts successfully, false otherwise.
     */
    bool start();

    /**
     * @brief Accepts a client connection.
     * @return True if the connection is accepted successfully, false otherwise.
     */
    bool acceptConnection();

    /**
     * @brief Receives data from the connected client.
     * @param buffer The buffer to store the received data.
     * @param bufferSize The size of the buffer.
     * @return True if data is received successfully, false otherwise.
     */
    bool receiveData(char* buffer, int bufferSize);

    /**
     * @brief Sends data to the connected client.
     * @param data The data to send.
     * @return True if data is sent successfully, false otherwise.
     */
    bool sendData(const char* data);

    /**
     * @brief Closes the connection and cleans up resources.
     */
    void closeConnection();

protected:
    /**
     * @brief Initializes the necessary resources.
     * @return True if initialization is successful, false otherwise.
     */
    bool initialize();

    /**
     * @brief Creates a socket.
     * @return True if socket creation is successful, false otherwise.
     */
    bool createSocket();

    /**
     * @brief Binds the socket to the specified port.
     * @return True if socket binding is successful, false otherwise.
     */
    bool bindSocket();

    /**
     * @brief Listens for incoming connections.
     * @return True if listening is successful, false otherwise.
     */
    bool listenForConnections();

private:
    PrivateServer m_structure;    //!< The private structure holding server-related data.
};

