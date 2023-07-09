/*!
 * @name Project Template as known PT.
 * @details A template for modern C++ projects with useful features for developing cross-platform products.
 *
 * @copyright (c) 2021 Kambiz Asadzadeh
 * @copyright (c) 2023 Genyleap
 * @url https://github.com/genyleap/Project-Template
 */

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
# endif
#else
#error There is no PT's common file!
#endif

#ifdef COMPILE_AS_SERVER
#include "server.hpp"
#endif

#ifdef COMPILE_AS_CLIENT
#include "client.hpp"
#endif

PROJECT_USING_NAMESPACE std;

int main() {

#ifdef COMPILE_AS_SERVER
    // Create and start the server
    Server server(12345);
    if (!server.start()) {
        return 1;
    }

    // Accept client connection
    if (!server.acceptConnection()) {
        return 1;
    }

    // Receive data from the client
    char buffer[1024];
    if (!server.receiveData(buffer, sizeof(buffer))) {
        return 1;
    }

    std::cout << "Received data: " << buffer << std::endl;

    // Send a response to the client
    const char* response = "Hello from the server!";
    if (!server.sendData(response)) {
        return 1;
    }

    // Close the connection
    server.closeConnection();

#endif

#ifdef COMPILE_AS_CLIENT

    // Create and connect the client
    Client client("127.0.0.1", 12345);
    if (!client.connectToServer()) {
        return 1;
    }

    // Send data to the server
    const char* data = "Hello from the client!";
    if (!client.sendData(data)) {
        return 1;
    }

    // Receive response from the server
    char responseBuffer[1024];
    if (!client.receiveData(responseBuffer, sizeof(responseBuffer))) {
        return 1;
    }

    std::cout << "Received response: " << responseBuffer << std::endl;

    // Close the connection
    client.closeConnection();

    return 0;

#endif

}
