# MiniServ

MiniServ is a small, educational C++ TCP server built with POSIX sockets and `poll()`. It listens for client connections, receives raw request data, and sends a minimal response back to connected clients.

This project is designed to demonstrate the basics of socket programming, non-blocking I/O, and multi-client handling in a compact C++98 implementation.

## Features

- TCP server built with POSIX sockets
- listens on port `4646` by default
- accepts multiple client connections
- uses `poll()` to monitor file descriptors
- reads incoming request data from clients
- sends a basic response to connected clients
- tracks active file descriptors and cleans them up on shutdown
- handles graceful shutdown with signal handling
- built with strict `-Wall -Wextra -Werror -std=c++98` flags

## Requirements

A Unix-like operating system with:

- a C++ compiler
- GNU Make
- POSIX socket APIs
- `poll()` support
- optional: Valgrind for debugging leaks and file descriptor issues

## Build

Clone the repository and build it:

```bash
git clone https://github.com/Pendragon46/mini-serv.git
cd mini-serv
make
```

This creates an executable named `MiniServ`.

## Run

Start the server with:

```bash
./MiniServ
```

By default, the server listens on:

```text
0.0.0.0:4646
```

You can test the server using `curl`, `nc`, or another TCP client:

```bash
curl http://localhost:4646/
```

or:

```bash
nc 127.0.0.1 4646
```

The server prints the received request data to standard output and responds with a basic message.

## Make targets

```bash
make      # build the project
make all  # same as make
make clean
make fclean
make re
make val
```

- `make clean` removes object files
- `make fclean` removes object files and the executable
- `make re` rebuilds the project from scratch
- `make val` runs the project under Valgrind

## Project structure

- `main.cpp` — starts the server and runs the polling loop
- `MiniServ.cpp` / `MiniServ.hpp` — server setup and main logic
- `Client.cpp` / `Client.hpp` — client connection data
- `FdCollector.cpp` / `FdCollector.hpp` — tracks active file descriptors
- `WrapperFunction.cpp` / `WrapperFunction.hpp` — safe wrappers around socket operations
- `signal.cpp` — signal handling for clean shutdown
- `Makefile` — build and utility commands

## Architecture overview

1. `MiniServ` creates a TCP socket and binds it to the configured port.
2. The server starts listening for incoming connections.
3. The listening socket is registered in a `pollfd` array.
4. The main loop waits for activity with `poll()`.
5. New clients are accepted when the listening socket becomes readable.
6. Client sockets are monitored for incoming data.
7. Requests are received and stored as raw request content.
8. A basic response is sent back to the client.
9. The connection is closed after the response is handled.
10. Signals allow the program to shut down gracefully and close tracked descriptors.

## Configuration

The main server constants are defined in `MiniServ.hpp`:

- `PORT` — listening port, currently `4646`
- `LISTENQ` — listen backlog
- `DATALEN` — receive buffer size
- `OPEN_MAX` — maximum number of monitored file descriptors

These values can be adjusted and the project rebuilt if you want different limits.

## Development notes

The implementation is compiled with:

```bash
-Wall -Wextra -Werror -std=c++98
```

It is intended primarily for learning and experimentation with low-level networking. It is not a complete HTTP/1.1 server and does not provide full routing, parsing, static file serving, or production-grade request handling.

## License

This project is distributed under the MIT License. See the repository license file for more details.

## About

MiniServ is a minimal, educational server project created to practice:

- socket creation and binding
- listening and accepting clients
- monitoring sockets with `poll()`
- reading and responding to raw network data
- graceful shutdown and resource cleanup

It is a good companion project for a minimal raw TCP client such as `MiniClient`.
