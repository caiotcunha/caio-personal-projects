## Networked Minesweeper (C — Client / Server)

This project implements a networked Minesweeper game in C, composed of a TCP server and a client that communicate using a shared struct action. The server is responsible for storing and updating the game state, handling client commands in a loop (start, reveal, flag, reset, exit) and signaling win/lose conditions.

The client parses and validates user input, sends actions to the server, and prints a user-friendly view of the board (using character symbols rather than raw integers). Error checking for invalid commands/coordinates and handling of game messages (win / game over) are implemented on the client side.

Communication between client and server is standardized through the action struct (type, coordinates, and a 4×4 board), which ensures compatibility across implementations. The project also addresses IPv4/IPv6 support and the required host/network byte-order conversions for network programming.

Skills practiced: low-level socket programming (bind/listen/accept/connect), protocol design using C structs, input validation and terminal UI, basic server loop design and state management, and cross-protocol compatibility (IPv4/IPv6)
