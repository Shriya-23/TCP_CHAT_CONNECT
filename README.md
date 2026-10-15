# TCP Client-Server Chat Application in C++

This repository contains my practice work while learning C++ networking on Windows using the Winsock API.

I started with the basics of Winsock initialization and then moved on to building a simple TCP client-server chat application. While working on it, I focused on understanding how the connection is established, how messages travel between the client and server, and how Windows networking functions are used in C++.

## Key learning outcomes

This project helped me connect C++ fundamentals with practical networking.

While building it, I worked on understanding the client-server communication flow, socket functions, IP addresses and ports, message exchange, error checks, and basic resource cleanup.

I also used C++ classes to organize the client and server code and added comments to document what I was learning along the way.

## Repository Structure

```text
TCP_CHAT_CONNECT/
│
├── Practice/
│   └── winsock.cpp
│
├── client/
│   ├── client.cpp
│   └── client.exe
│
├── server/
│   ├── server.cpp
│   └── server.exe
│
└── README.md
```

## I] Practice: Learning Winsock Basics

The `Practice/winsock.cpp` file is where I started learning the basics of Windows networking.

Before working on the complete client-server application, I wanted to understand how Winsock is initialized and what the main networking-related files do.

Concepts explored:

- `winsock2.h` and `ws2tcpip.h`
- The `WSADATA` structure
- `MAKEWORD(2, 2)` and Winsock version selection
- `WSAStartup()` for initialization
- `WSACleanup()` for cleanup
- The difference between header files, import libraries, and DLLs
- Basic return-value checking

I added comments to record my understanding of these concepts and make the code easier to revisit while learning.

## II] Client: Connecting to the Server

The `client/client.cpp` file contains the client-side implementation.

Concepts covered:

- Creating a TCP socket with `socket()`
- Configuring the server address with `sockaddr_in`
- Using `htons()` for the port number
- Connecting to the server with `connect()`
- Sending messages using `send()`
- Receiving messages using `recv()`
- Organizing the client logic using a C++ class
- Basic connection and disconnection handling

The client sends a message first and then waits for the server's response.

## III] Server: Accepting Connections and Responding

The `server/server.cpp` file contains the server-side implementation.

The server prepares a socket on port `8080`, waits for a client connection, and then exchanges messages with the connected client.

Concepts covered:

- Creating a server socket
- Configuring the server address
- Binding the socket using `bind()`
- Listening for connections using `listen()`
- Accepting a client using `accept()`
- Receiving messages with `recv()`
- Sending replies with `send()`
- Closing sockets and cleaning up Winsock resources

For this version, the server handles one client connection at a time. The chat follows a simple turn-by-turn communication flow.

## How the Client and Server Work Together

1. Start the server first.
2. The server binds to port `8080` and waits for a client.
3. Start the client in a separate terminal.
4. The client connects to `127.0.0.1:8080`.
5. The client sends a message, and the server receives it.
6. The server sends a reply, which the client displays.
7. Type `exit` to end the chat.

## How to Compile and Run

These instructions assume Windows, MinGW-w64 `g++`, and a terminal opened at the repository root.

### Compile the server

```powershell
g++ server/server.cpp -o server/server.exe -lws2_32
```

### Compile the client

```powershell
g++ client/client.cpp -o client/client.exe -lws2_32
```

### Run the server

```powershell
.\server\server.exe
```

### Run the client

Open another terminal and run:

```powershell
.\client\client.exe
```

Wait for the client to connect before exchanging messages.


**Summary:** This project documents my hands-on learning journey with C++ networking on Windows, from understanding Winsock fundamentals to building a TCP client-server chat application using sockets and Object oriented programming in C++.
