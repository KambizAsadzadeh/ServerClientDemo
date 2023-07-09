/*!
 * @name Project Template as known PT.
 * @details A template for modern C++ projects with useful features for developing cross-platform products.
 *
 * @copyright (c) 2021 Kambiz Asadzadeh
 * @copyright (c) 2023 Genyleap
 * @url https://github.com/genyleap/Project-Template
 */

#ifdef __has_include
# if __has_include("server.hpp")
#   include "server.hpp"
# endif
#else
#error There is no PT's server file!
#endif

Server::Server(int port)
{
    m_structure.port = port;
    m_structure.socketDescriptor = -1;
    m_structure.clientSocket = -1;
}

bool Server::start()
{
    if (!initialize()) {
        return false;
    }

    if (!createSocket()) {
        return false;
    }

    if (!bindSocket()) {
        return false;
    }

    if (!listenForConnections()) {
        return false;
    }

    return true;
}

bool Server::acceptConnection()
{
    sockaddr_in clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);
    m_structure.clientSocket = accept(m_structure.socketDescriptor, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);
    if (m_structure.clientSocket == -1) {
        std::cerr << "Failed to accept client connection" << std::endl;
        CLOSE_SOCKET(m_structure.socketDescriptor);
        return false;
    }

    return true;
}

bool Server::receiveData(char* buffer, int bufferSize)
{
    memset(buffer, 0, bufferSize);
    ssize_t bytesRead = recv(m_structure.clientSocket, buffer, bufferSize - 1, 0);
    if (bytesRead == -1) {
        std::cerr << "Failed to receive data" << std::endl;
        CLOSE_SOCKET(m_structure.clientSocket);
        CLOSE_SOCKET(m_structure.socketDescriptor);
        return false;
    }

    return true;
}

bool Server::sendData(const char* data)
{
    ssize_t bytesSent = send(m_structure.clientSocket, data, strlen(data), 0);
    if (bytesSent == -1) {
        std::cerr << "Failed to send data" << std::endl;
        CLOSE_SOCKET(m_structure.clientSocket);
        CLOSE_SOCKET(m_structure.socketDescriptor);
        return false;
    }

    return true;
}

void Server::closeConnection()
{
    CLOSE_SOCKET(m_structure.clientSocket);
    CLOSE_SOCKET(m_structure.socketDescriptor);
}

bool Server::initialize()
{
#ifdef PLATFORM_WINDOWS
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return false;
    }
#endif
    return true;
}

bool Server::createSocket()
{
    m_structure.socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (m_structure.socketDescriptor == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return false;
    }
    return true;
}

bool Server::bindSocket()
{
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(m_structure.port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (::bind(m_structure.socketDescriptor, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
        CLOSE_SOCKET(m_structure.socketDescriptor);
        return false;
    }

    return true;
}

bool Server::listenForConnections()
{
    if (listen(m_structure.socketDescriptor, 1) == -1) {
        std::cerr << "Failed to listen" << std::endl;
        CLOSE_SOCKET(m_structure.socketDescriptor);
        return false;
    }

    std::cout << "Waiting for a connection..." << std::endl;

    return true;
}
