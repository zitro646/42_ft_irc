
# IRC Server (ft_irc) - C++ 98 Implementation

This project is the implementation of an IRC server in C++98 that can handle multiple clients and supports basic IRC functionalities. It uses a non-blocking I/O approach and leverages a single `poll()` (or equivalent like `select()`, `kqueue()`, or `epoll()`) to handle multiple connections efficiently. 

![Texto alternativo](/req/group_chat.gif)

## Requirements

![Texto alternativo](/req/requisites.png)


- **No client implementation**: This server is only responsible for handling client connections and communications.
- **No server-to-server communication**: The server does not need to communicate with other IRC servers.
- **Non-blocking I/O**: All I/O operations must be non-blocking.
- **Single poll() (or equivalent)**: The server must handle all I/O operations (read, write, listen, etc.) using a single `poll()` (or equivalent) call.

### Executable Usage

To run the server, execute the following command:

```bash
./ircserv <port> <password> <network_port> <network_pass>
```


- **port**: The port number the IRC server will listen on.
- **password**: The password required for clients to authenticate with the server.

## Features Implemented

- **Multiple Client Connections**: The server can handle multiple clients simultaneously without blocking or forking.
- **Password Authentication**: Clients must authenticate using the specified password.
- **Nickname and Username**: Clients can set their nickname and username upon connecting.
- **Channel Support**: Clients can join channels and send messages to them.
- **Private Messages**: Clients can send private messages to each other.
- **Channel Operators**: Operators have special privileges such as kicking users, inviting users, and modifying the channel's topic or modes.

## Channel Operator Commands

The server supports the following commands specific to channel operators:

- **KICK**: Eject a client from a channel.
- **INVITE**: Invite a client to a channel.
- **TOPIC**: View or change the channel's topic.
- **MODE**: Change the channel's mode:
  - `i`: Set/remove invite-only channel.
  - `t`: Set/remove topic restrictions to channel operators.
  - `k`: Set/remove a channel key (password).
  - `o`: Give or take channel operator privileges.
  - `l`: Set/remove user limit for a channel.

## Client-Server Communication

- The server uses TCP/IP (v4 or v6) for communication between clients and the server.
- All messages sent to a channel are forwarded to every other client in that channel.
- Clients must be able to connect, authenticate, set a nickname, join a channel, and exchange private messages.

## Non-Blocking I/O

- The server must use non-blocking file descriptors, allowing for efficient handling of multiple clients without blocking.
- The server can use `read/recv` and `write/send` with `poll()` (or equivalent) to handle all I/O operations in a non-blocking manner.



# Documents to take a look

- [Wikipedia - Internet Relay Chat](https://en.wikipedia.org/wiki/Internet_Relay_Chat) - General Info
- [IRC Documentation](https://modern.ircdocs.horse) - IRC Documentation
- [RFC 2812 - Client Protocol](https://www.rfc-editor.org/rfc/rfc2812) - Client Protocol
- [RFC 2813 - Server Protocol](https://www.rfc-editor.org/rfc/rfc2813) - Server Protocol
- [RFC 2810 - Architecture](https://www.rfc-editor.org/rfc/rfc2810) - Architecture
- [Port Range & Security Measures](https://www.w3.org/Addressing/draft-mirashi-url-irc-01.txt#:~:text=IRC%20servers%20often%20use%20the,for%20clients%20to%20connect%20to.) - Port Range - Security Measures

## Socket Stuff

- [YouTube - Socket Programming Tutorial](https://www.youtube.com/watch?v=k_P2E7ZvhYs)
- [GTA/UFRJ - Sockets Documentation](https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html)
- [The Open Group - inet_addr](https://pubs.opengroup.org/onlinepubs/009695399/functions/inet_addr.html)
- [GNU - Socket-Level Options](https://www.gnu.org/software/libc/manual/html_node/Socket_002dLevel-Options.html#Socket_002dLevel-Options)

## Client IRC (for Linux) Colloquy (for Mac)

- **IRSSI**: Install with `brew install irssi`
- **Colloquy**: Install from [Colloquy github](https://github.com/colloquy/colloquy/releases/tag/mac%2F2021%2F2.5-prerelease-7097)

## Connection Protocol

- [Client to Server](https://modern.ircdocs.horse/#client-to-server)
- [RPLWELCOME - 001](https://modern.ircdocs.horse/#rplwelcome-001)

## IRSSI Documentation

- [IRSSI Rawlog Help](https://irssi.org/documentation/help/rawlog/)
