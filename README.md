42_ft_irc

# Documents to take a look

https://www.rfc-editor.org/rfc/rfc2812  - Client Protocol
https://www.rfc-editor.org/rfc/rfc2813  - Server Protocol
https://www.rfc-editor.org/rfc/rfc2810  - Architecture

https://en.wikipedia.org/wiki/Internet_Relay_Chat - General Info
https://www.w3.org/Addressing/draft-mirashi-url-irc-01.txt#:~:text=IRC%20servers%20often%20use%20the,for%20clients%20to%20connect%20to.  - Port Range - Security Measures

## Socket stuff
https://www.youtube.com/watch?v=k_P2E7ZvhYs
https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
https://pubs.opengroup.org/onlinepubs/009695399/functions/inet_addr.html
https://www.gnu.org/software/libc/manual/html_node/Socket_002dLevel-Options.html#Socket_002dLevel-Options

## Client IRC
IRSSI $> brew install irssi

Poll
//fcntl(fd, F_SETFL, O_NONBLOCK);

## Connection Protocol
https://modern.ircdocs.horse/#client-to-server
https://modern.ircdocs.horse/#rplwelcome-001

## IRSSI msg 
CAP LS

NICK miguel

USER mortiz-d mortiz-d 10.11.15.4 :Miguel angel Ortiz del burgo

## IRSSI stuff
Ctrl+N : para cambiar entre salas 
Ctrl+X : para cambiar entre servidores

Orden de recibir datos RPL_1 pass -> nick -> user
Cuando le enviamos un mensaje tiene que responder el protocolo de bienvenida

https://irssi.org/documentation/help/rawlog/