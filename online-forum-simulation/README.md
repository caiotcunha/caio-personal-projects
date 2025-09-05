## Online Forum Simulation (C — Client / Server)

This project was developed as part of a Computer Networks course. Its goal was to implement a client–server system using sockets to simulate the basic functionalities of an online forum. The server is responsible for storing topics and posts, managing client subscriptions, processing commands, and notifying users when new posts are published. It was also designed to support multiple simultaneous clients. The client validates user input, forwards commands to the server, and constantly listens for responses, displaying them on the terminal when needed.

The program was developed in C on a Linux environment and uses multiple data structures to model forum behavior, including linked queues for posts and topics, subscription tracking arrays, and auxiliary structures for thread communication. The server and client communicate through a custom structure (BlogOperation) passed over sockets, containing fields for client ID, operation type, response flags, and message data (topic title and post content).

Skills practiced: socket programming in C (IPv4/IPv6), multithreaded server–client architecture, synchronization with mutexes, linked data structures, and low-level network protocol handling.
