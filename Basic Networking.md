2 main models:

Open Systems interconnection(OSI)

TCP/IP

Both are basic models to break down the transfer of data and communication into distinct layers

Looking at OSI:

There are 7 layers of the OSI Model. Here they are with a brief description:

Physical Layer:
Function: Transmits raw bits (1s and 0s) over a physical medium.
 Focus: Hardware, cables, electrical signals.
 Examples:
Ethernet cables (Cat5e, Cat6)


Fiber optics


Hubs, repeaters


Data Link layer:
Function: Ensures reliable transmission of data across a physical link; handles framing, addressing, and error detection.
 Focus: Node-to-node communication (on the same network).
 Examples:
MAC addresses


Switches and bridges


Ethernet, Wi-Fi (802.11)


ARP (Address Resolution Protocol)

Network Layer:
Function: Handles logical addressing and routing of packets between different networks.
 Focus: How data travels from one network to another.
 Examples:
IP (Internet Protocol)


Routers


ICMP (ping/traceroute)


IPv4, IPv6


Transport Layer:
Function: Provides end-to-end communication, flow control, and error recovery.
 Focus: Reliable or best-effort delivery of data between applications.
 Examples:
TCP (Transmission Control Protocol)


UDP (User Datagram Protocol)


Port numbers (e.g., 80, 443)
Session Layer:
Function: Manages sessions (connections) between applications — establishes, maintains, and terminates them.
 Focus: Organizing and synchronizing dialog between systems.
 Examples:
NetBIOS


RPC (Remote Procedure Call)


Session setup in HTTPS/SSH
Presentation Layer:
Function: Translates, encrypts, or compresses data for the application layer.
 Focus: Data format and representation — ensures compatibility between systems.
 Examples:
SSL/TLS (encryption)


JPEG, PNG (data formats)


ASCII, UTF-8 (text encoding)
Presentation Layer:
Function: Provides network services directly to the user or application.
 Focus: Interface between user applications and network.
 Examples:
HTTP/HTTPS (web)


FTP, SFTP (file transfer)


DNS (name resolution)


SMTP, POP3, IMAP (email)


TCP/IP:
This model is very similar but it groups some of these layers into a more abstracted view
4 Layers:


Network Access
Internet layer
Transport Layer
Application Layer
There are a few basic protocols that are good to know when it comes to cybersecurity applications.

SSH:
This stands for Secure Shell, it allows a user to create a secure TCP connection to another machine. It can be used to forward information and access different services, data is encrypted
https://www.cloudflare.com/learning/access-management/what-is-ssh/

TCP(Transmission control protocol):
TCP is a connection-oriented, reliable data transfer protocol that operates at Layer 4 (Transport Layer) of the OSI model.
It’s one of the main protocols of the Internet Protocol Suite (TCP/IP), and it ensures that data sent from one computer to another arrives accurately, in order, and without loss or duplication.
Uses a 3 way handshake:
SYN
SYN-ACK
ACK
UDP(User Datagram Protocol):
UDP is a connectionless, unreliable, and fast data transfer protocol that operates at the Transport Layer (Layer 4) of the OSI model.
 Unlike TCP, UDP sends messages called datagrams without first establishing a connection or guaranteeing delivery. It’s designed for applications where speed matters more than reliability.

DNS(Domain naming system):
This is the protocol that is used to translate domain names ie. Google.com into the IP address so the browser know where to go. Translation can also occur in the opposite direction.

https://www.cloudflare.com/learning/dns/what-is-dns/




