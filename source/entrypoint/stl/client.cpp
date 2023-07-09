#ifdef __has_include
# if __has_include("client.hpp")
#   include "client.hpp"
# endif
#else
#error There is no PT's client file!
#endif


Client::Client(const std::string& serverIP, int port)
{
    m_structure.serverIP = serverIP;
    m_structure.port = port;
    m_structure.socketDescriptor = -1;
}

bool Client::connectToServer()
{
    if (!initialize()) {
        return false;
    }

    if (!createSocket()) {
        return false;
    }

    if (!connectToServerSocket()) {
        return false;
    }

    return true;
}

bool Client::sendData(const char* data)
{
    ssize_t bytesSent = send(m_structure.socketDescriptor, data, strlen(data), 0);
    if (bytesSent == -1) {
        std::cerr << "Failed to send data" << std::endl;
        CLOSE_SOCKET(m_structure.socketDescriptor);
        return false;
    }

    return true;
}

bool Client::receiveData(char* buffer, int bufferSize)
{
    memset(buffer, 0, bufferSize);
    ssize_t bytesRead = recv(m_structure.socketDescriptor, buffer, bufferSize - 1, 0);
    if (bytesRead == -1) {
        std::cerr << "Failed to receive data" << std::endl;
        CLOSE_SOCKET(m_structure.socketDescriptor);
        return false;
    }

    return true;
}

void Client::closeConnection()
{
    CLOSE_SOCKET(m_structure.socketDescriptor);
}

bool Client::initialize()
{
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return false;
    }
#endif
    return true;
}

bool Client::createSocket()
{
    m_structure.socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (m_structure.socketDescriptor == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return false;
    }
    return true;
}

bool Client::connectToServerSocket()
{
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(m_structure.port);
    serverAddress.sin_addr.s_addr = inet_addr(m_structure.serverIP.c_str());

    if (connect(m_structure.socketDescriptor, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to connect to server" << std::endl;
        CLOSE_SOCKET(m_structure.socketDescriptor);
        return false;
    }

    return true;
}
