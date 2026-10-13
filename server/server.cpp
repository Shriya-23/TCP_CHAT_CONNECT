#include <iostream>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

class MyServer {
private:
    SOCKET serverSocket;
    SOCKET clientSocket;
    int port;

public:
    // Simple Constructor 
    MyServer(int portNumber) {
        port = portNumber;
        serverSocket = INVALID_SOCKET;
        clientSocket = INVALID_SOCKET;
    }

    // Main function to start server
    void start() {

        // 1. Winsock library initialization
        WSADATA wsaData;

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            cout << "Winsock initialization failed!" << endl;
            return;
        }

        // 2. TCP Socket creation
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);

        if (serverSocket == INVALID_SOCKET) {
            cout << "Socket creation failed!" << endl;
            return;
        }

        // 3. Server address configurations
        sockaddr_in serverAddress{};

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(port);

        // 4. Bind function calling
        if (bind(
                serverSocket,
                (sockaddr*)&serverAddress,
                sizeof(serverAddress)
            ) == SOCKET_ERROR) {

            cout << "Bind failed!" << endl;
            return;
        }

        // 5. Server going to listen mode
        listen(serverSocket, 1);

        cout << "Server is waiting for client on port "
             << port << "..." << endl;

        // 6. Client connection accepting
        clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket == INVALID_SOCKET) {
            cout << "Client connection failed!" << endl;
            return;
        }

        cout << "Client connected successfully!" << endl;

        // Chat Loop trigger
        chatLoop();
    }

private:

    void chatLoop() {

        char buffer[1024];  // Buffer
        string serverMessage;

        while (true) {

            // Received message from client
            int bytesReceived = recv(
                clientSocket,
                buffer,
                sizeof(buffer) - 1,
                0
            );

            // Safe Check:
            // if client disconnect 
            // Or any network error 
            if (bytesReceived <= 0) {

                cout << "Client disconnected." << endl;
                break;
            }

            // Safe termination
            // to end string properly
            buffer[bytesReceived] = '\0';

            // Convert to Normal string
            // Easy usage 
            string clientMsg = buffer;

            cout << "Client: " << clientMsg << endl;

            if (clientMsg == "exit") {

                cout << "Client ended the chat." << endl;
                break;
            }

            // Server will type reply
            cout << "You (Server): ";
            getline(cin, serverMessage);

            // Reply send to cliemt
            send(
                clientSocket,
                serverMessage.c_str(),
                serverMessage.length(),
                0
            );

            if (serverMessage == "exit") {

                cout << "You ended the chat." << endl;
                break;
            }
        }
    }

public:

    // Destructor that automatically cleans sockets and Winsock resources 
    ~MyServer() {

        if (clientSocket != INVALID_SOCKET) {
            closesocket(clientSocket);
        }

        if (serverSocket != INVALID_SOCKET) {
            closesocket(serverSocket);
        }

        WSACleanup();
    }
};

int main() {

    MyServer server(8080);

    server.start();

    return 0;
}