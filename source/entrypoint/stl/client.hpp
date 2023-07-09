#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
# endif
#else
#error There is no PT's common file!
#endif

#include <iostream>
#include <cstring>      // For string manipulation

#ifdef PLATFORM_WINDOWS
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
 * @brief The private structure holding client-related data.
 */
struct PrivateClient final
{
    std::string serverIP;       //!<The server IP address.
    int port;                   //!<The server port number.
    int socketDescriptor;       //!<The socket descriptor.
};

/**
 * @brief The Client class for handling client-side operations.
 */
class Client {
public:
    /**
     * @brief Constructs a Client object with the specified server IP and port.
     * @param serverIP The IP address of the server to connect to.
     * @param port The port number to connect to.
     */
    Client(const std::string& serverIP, int port);

    /**
     * @brief Connects to the server.
     * @return True if the connection is successful, false otherwise.
     */
    bool connectToServer();

    /**
     * @brief Sends data to the server.
     * @param data The data to send.
     * @return True if the data is sent successfully, false otherwise.
     */
    bool sendData(const char* data);

    /**
     * @brief Receives data from the server.
     * @param buffer The buffer to store the received data.
     * @param bufferSize The size of the buffer.
     * @return True if data is received successfully, false otherwise.
     */
    bool receiveData(char* buffer, int bufferSize);

    /**
     * @brief Closes the connection.
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
     * @brief Connects to the server socket.
     * @return True if connection is successful, false otherwise.
     */
    bool connectToServerSocket();

private:
    PrivateClient m_structure;    //!<The private structure holding client-related data.
};
