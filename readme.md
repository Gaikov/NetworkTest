# NetworkTest

**Language**: C++  
**Standard**: C++20
**Based on**: [GROmEngine](https://github.com/Gaikov/GROmEngine)
#### Source Folders:
ServerSources - server source code
GameSources - client game source code

---

## Overview

**NetworkTest** is a project template designed for creating client-server applications, particularly multiplayer games. It provides a basic structure for client-side server connections, packet handling, connection management, and multithreading logic. The code uses modern C++20 features, offering better performance, safety, and usability.

---

## Main Components

### 1. **Client**
- Manages the client’s connection to the server.
- Uses asynchronous threads to initiate connections and handle data transmission.
- Processes and distributes incoming packets through a callback system for flexibility.

### 2. **Packet Handling Pattern**
The project includes a packet management system with:
- An object pool to reduce memory allocation overhead.
- Asynchronous packet reception and processing.
- A system of handler callbacks for attaching functions to specific packet types.

### 3. **Multithreading**
- Separation of connection establishment and data reception into dedicated threads, improving performance and responsiveness.

### 4. **Logging**
- Captures debug and monitoring information, covering important events like connection establishment, packet reception, disconnection, and errors.

### 5. **Networking**
- Manages connections with sockets, handling states like `CONNECTING`, `CONNECTED`, and `DISCONNECTED`.

---

## Features and Technologies

- **Data Processing**:
  `reinterpret_cast` is used to treat raw incoming buffers (e.g., network data) as structured types like `nsPacket`.

- **Object Pool**:
  Implements an object pool to optimize packet management, reducing allocation overhead and improving performance in high-load scenarios.

- **Multithreaded Design**:
  Core network operations (e.g., connection, data reception) are isolated into separate threads, allowing the client to stay responsive under high network traffic.

- **Packet Handler Management**:
  The callback mechanism enables developers to register functions for specific packet types, simplifying the addition of new functionality without modifying client logic.

---

## Advantages and Goals

1. **Ease of Integration**:
   The template provides a foundation for client-server applications, focusing on easy data processing and distribution.

2. **Flexibility**:
   Adding new packet types or modifying logic is simple, thanks to the callback-based architecture.

3. **Performance**:
   The object pool and the separation of threads reduce memory management overhead and improve overall responsiveness.

4. **Modern C++**:
   The project leverages C++20 features like enhanced lambdas, strong typing, and improved multithreading capabilities.

---

## Problems Solved by the Project

- **Universal Template for Multiplayer Games**:
  Simplifies the development of client-side network handling for multiplayer games, with ready-to-use implementations for packet and connection management.

- **Reduced Overhead**:
  The object pool minimizes memory allocation and improves performance.

- **Extensibility**:
  By registering new packet handlers and callbacks, functionality can be extended without major overhauls to the codebase.

---

## Usage

### 1. Creating the Client
- Initialize the client (`nsClient`) and connect it to the server using the `Connect(ip, port)` method.

### 2. Adding Packet Handlers
```c++
client.AddPacketHandler(packetId, [](const nsPacket* packet) {
    // Logic for handling the packet
});
```

### 3. Asynchronous Packet Processing
- Incoming data is automatically pushed into the object pool, processed asynchronously, and forwarded to registered handlers.

### 4. Disconnecting
- The client cleans up resources, closes connections, and safely terminates threads when disconnected.

---

## Potential Improvements

- **Error Handling**:
  Implement advanced logging and exception handling (e.g., timeouts, malformed packets).

- **Protocol Support**:
  Expand to include support for UDP or other transport protocols.

- **Testing and Debugging**:
  Add unit tests to validate core components like the packet pool, data handling, and safe disconnection logic.

---
