# MiniServ

A small event-driven TCP server written in C++98. MiniServ is a lightweight networking project that demonstrates how to create a listening socket, accept multiple clients, monitor file descriptors with `poll()`, receive requests, and send responses.

> **Status:** This project is an educational/minimal server implementation. The current request handling is intentionally simple and is not a complete HTTP/1.1 server.

## Features

- TCP server built with POSIX sockets
- Listens on port `4646` by default
- Handles multiple file descriptors with `poll()`
- Accepts incoming client connections
- Receives client data and stores it as a request
- Sends a basic response to connected clients
- Tracks open file descriptors and closes them during shutdown
- Handles graceful shutdown through signal handling
- Builds with strict C++98 compiler flags

## Requirements

A Unix-like operating system with:

- A C++ compiler
- GNU Make
- POSIX socket APIs
- `poll()` support
- Optional: Valgrind for leak and file-descriptor checks

## Build

Clone the repository and build the executable:

```bash
git clone https://github.com/Pendragon46/mini-serv.git
cd mini-serv
make
```

The build creates an executable named `MiniServ`.

## Run

Start the server with:

```bash
./MiniServ
```

By default, the server listens on:

```text
0.0.0.0:4646
```

You can test the server with `curl` or `nc`:

```bash
curl http://localhost:4646/
```

```bash
nc 127.0.0.1 4646
```

The server prints received request data to standard output and returns a simple response to the client.

## Make targets

| Target | Description |
| --- | --- |
| `make` or `make all` | Build the `MiniServ` executable |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and the executable |
| `make re` | Clean and rebuild the project |
| `make val` | Run the server under Valgrind |

## Project structure

| File | Description |
| --- | --- |
| `main.cpp` | Starts the server and runs the polling event loop |
| `MiniServ.cpp/.hpp` | Server setup, connection handling, request reception, and responses |
| `Client.cpp/.hpp` | Client connection data structure |
| `FdCollector.cpp/.hpp` | Tracks and closes active file descriptors |
| `WrapperFunction.cpp/.hpp` | Error-checking wrappers around socket operations |
| `signal.cpp` | Signal handling for graceful shutdown |
| `Makefile` | Build and development commands |

## Architecture overview

1. `MiniServ` creates a TCP socket, binds it to port `4646`, and starts listening.
2. The listening socket is registered with a `pollfd` array.
3. The main loop waits for activity using `poll()`.
4. New connections are accepted when the listening socket becomes readable.
5. Connected clients are monitored for incoming data.
6. Received data is stored as a request and the client is switched to writable mode.
7. A response is sent and the client connection is removed.
8. Signals allow the server to exit cleanly and close tracked descriptors.

## Configuration

The main server constants are defined in `MiniServ.hpp`:

- `PORT`: listening port, currently `4646`
- `LISTENQ`: listen backlog, currently `46`
- `DATALEN`: receive buffer size, currently `1080`
- `OPEN_MAX`: maximum number of monitored file descriptors, currently `1024`

Change these values and rebuild if you need different server limits.

## Development notes

The project is compiled with:

```text
-Wall -Wextra -Werror -std=c++98
```

The implementation uses POSIX networking interfaces and is intended primarily for Unix-like systems. It currently provides a minimal response path rather than full HTTP parsing, routing, headers, status codes, or static-file serving.

## License

This project is distributed under the MIT License. See [LICENSE](LICENSE) for details.
