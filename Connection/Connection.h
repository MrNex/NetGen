#ifndef CONNECTION
#define CONNECTION

#include <sys/socket.h>
#include <sys/types.h>

typedef struct Connection Connection;


///
//Allocates memory needed for a TCP Connection
//
//Returns:
//	Pointer to newly allocated, uninitialized, TCPConnection.
Connection* Connection_Allocate();

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
void Connection_Initialize(Connection* conn, int domain, int type, int protocol, char* host, short port);

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
void Connection_Open(Connection* conn);

///
//Closes a connection terminating the transfer of data
//
//Parameters:
//	conn: Pointer to The connection to terminate
void Connection_Close(Connection* conn);

#endif
