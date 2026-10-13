//CLIENT SIDE CODE
#include <iostream> 
#include <string> 
#include <winsock2.h> // inet_addr is available here

#pragma comment(lib, "ws2_32.lib") 
 
using namespace std; 
 
 
class MyClient { 
 
private: 
    SOCKET clientSocket; 
    string serverIP; 
    int port; 
 
public: 
 
    // Simple constructor
    MyClient(string ip, int portNumber) { 
        serverIP = ip; 
        port = portNumber; 
        clientSocket = INVALID_SOCKET; 
    } 
 
 
    void connectToServer() { 
 
        // 1. Initialize Winsock
        WSADATA wsaData; 
 
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) { 
            cout << "Winsock initialization failed!" << endl; 
            return; 
        } 
 
 
        // 2. Create the socket
        clientSocket = socket(AF_INET, SOCK_STREAM, 0); 
 
        if (clientSocket == INVALID_SOCKET) { 
            cout << "Socket creation failed!" << endl; 
            return; 
        } 
 
 
        // 3. Load the server specifications
        sockaddr_in serverAddress{}; 
 
        serverAddress.sin_family = AF_INET; 
        serverAddress.sin_port = htons(port); 
 
        // Convert the IP address
        serverAddress.sin_addr.s_addr = inet_addr(serverIP.c_str()); 
 
 
        // 4. Connect to the server
        if (connect( 
                clientSocket, 
                (sockaddr*)&serverAddress, 
                sizeof(serverAddress) 
            ) == SOCKET_ERROR) { 
 
            cout << "Connection to server failed!" << endl; 
            return; 
        } 
 
        cout << "Connected to the server successfully!" << endl; 
 
 
        // Start the chat loop
        chatLoop(); 
    } 
 
 
private: 
 
    void chatLoop() { 
 
        char buffer[1024]; // Safe buffer size
        string clientMessage; 
 
        while (true) { 
 
            // The client will always type first
            // (Turn-by-turn communication logic)
            cout << "You (Client): "; 
            getline(cin, clientMessage); 
 
 
            // Send the message to the server
            send( 
                clientSocket, 
                clientMessage.c_str(), 
                clientMessage.length(), 
                0 
            ); 
 
 
            if (clientMessage == "exit") { 
 
                cout << "You ended the chat." << endl; 
                break; 
            } 
 
 
            // Wait for the server's reply
            int bytesReceived = recv( 
                clientSocket, 
                buffer, 
                sizeof(buffer) - 1, 
                0 
            ); 
 
 
            // Safe check to prevent the program from crashing
            if (bytesReceived <= 0) { 
 
                cout << "Server disconnected." << endl; 
                break; 
            } 
 
 
            // Properly terminate the string
            buffer[bytesReceived] = '\0'; 
 
 
            // Convert the buffer into a simple string
            string serverMsg = buffer; 
 
            cout << "Server: " << serverMsg << endl; 
 
 
            if (serverMsg == "exit") { 
 
                cout << "Server ended the chat." << endl; 
                break; 
            } 
        } 
    } 
 
 
public: 
 
    // Destructor for automatic cleanup
    ~MyClient() { 
 
        if (clientSocket != INVALID_SOCKET) { 
            closesocket(clientSocket); 
        } 
 
        WSACleanup(); 
    } 
}; 
 
 
int main() { 
 
    MyClient client("127.0.0.1", 8080); 
 
    client.connectToServer(); 
 
    return 0; 
}

