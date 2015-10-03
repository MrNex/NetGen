#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER INADDR_LOOPBACK
#define PORT 8476
#define BSIZE	1024





typedef struct tcpConnection 
{
	int socketFD;// File descriptor that represents this connection stream
	struct sockaddr_in clientAddr;// the connection holder specifics
		/*struct sockaddr_in {
			    short            sin_family;   // e.g. AF_INET
			    unsigned short   sin_port;     // e.g. htons(3490)
			    struct in_addr   sin_addr;     // see struct in_addr, below
			    char             sin_zero[8];  // zero this if you want to
		};

		struct in_addr {
			    unsigned long s_addr;  // load with inet_aton()
		};*/

} Connection;



///
//Allocates memory needed for a TCP Connection
//
//Returns:
//	Pointer to newly allocated, uninitialized, TCPConnection.
Connection* Connection_Allocate() 
{
	Connection * new = malloc(sizeof(Connection));
	new->socketFD = 0;
	new->clientAddr = NULL;
	return(new);
}


///
//Initializes a TCPConnection
//
//Parameters:
//	conn: A pointer to the TCP Connection to initialize
//	domain: The domain this connection should use 
//		(AF_UNIX | AF_INET | AF_INET6 | AF_IPX | AF_NETLINK | AF_X25 | AF_AX25 | AF_ATMPVC | AF_APPLETALK | AF_PACKET)
//	type: The type this connection shoud use
//		(SOCK_STREAM | SOCK_DGRAM | SOCK_SEQPACKET | SOCK_RAW | SOCK_RDM | SOCK_PACKET)
//		With modifiers [SOCK_NONBLOCK | SOCK_CLOEXEC]
//	protocol: Specifies a protocol defined by the domain (0 specifies the default)
//	host: The host name to connect to
//	port: The port to connect to
void Connection_Initialize(Connection* conn, int domain, int type, int protocol, char* host, short port)
{
	conn->socketFD = socket(domain, type, protocol);
	conn->clientAddr.sin_family = domain;
	conn->clientAddr.sin_addr.s_addr = inet_addr(host);
	conn->clientAddr.sin_port = htons(port);
}




///
//Frees the data used by this connection and terminates the connection if it was not already terminated.
//
//Parameters:
//	conn: Pointer to the connection to free
void Connection_Free(Connection* conn);




///
//Opens a connection to allow the transfer of data
//
//Parameters:
//	conn: Pointer to The connection to open
void Connection_Open(Connection* conn)
{
	connect(conn->socketFD, (struct sockaddr *)&(conn->servAddress), sizeof(conn->servAddress));
}



///
//Closes a connection terminating the transfer of data
//
//Parameters:
//	conn: Pointer to The connection to terminate
void Connection_Close(Connection* conn)
{
	close(conn->socketFD);
}

