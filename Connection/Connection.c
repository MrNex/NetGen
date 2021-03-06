#include "Connection.h"

#include <stdlib.h>
#include <stdio.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

///
//Allocates memory needed for a Connection
//
//Returns:
//	Pointer to newly allocated, uninitialized, TCPConnection.
Connection* Connection_Allocate() 
{
	Connection * new = malloc(sizeof(Connection));
	new->socketFD = -1;
	new->connAddr;
	return(new);
}


///
//Initializes a Connection from a human readable IP Address
//
//Parameters:
//	conn: A pointer to the Connection to initialize
//	domain: The domain this connection should use 
//		(AF_UNIX | AF_INET | AF_INET6 | AF_IPX | AF_NETLINK | AF_X25 | AF_AX25 | AF_ATMPVC | AF_APPLETALK | AF_PACKET)
//	type: The type this connection shoud use
//		(SOCK_STREAM | SOCK_DGRAM | SOCK_SEQPACKET | SOCK_RAW | SOCK_RDM | SOCK_PACKET)
//		With modifiers [SOCK_NONBLOCK | SOCK_CLOEXEC]
//	protocol: Specifies a protocol defined by the domain (0 specifies the default)
//	host: The host name in IP form to connect to (Null Terminated)
//	port: The port to connect to
void Connection_InitializeFromIP(Connection* conn, int domain, int type, int protocol, char* host, short port)
{
	conn->socketFD = socket(domain, type, protocol);
	conn->connAddr.sin_family = domain;
	int successful = inet_pton(domain, host, &conn->connAddr.sin_addr.s_addr);
	conn->connAddr.sin_port = htons(port);
}

///
//Initializes a Connection from a human readable IP Address
//
//Parameters:
//	conn: A pointer to the Connection to initialize
//	domain: The domain this connection should use 
//		(AF_UNIX | AF_INET | AF_INET6 | AF_IPX | AF_NETLINK | AF_X25 | AF_AX25 | AF_ATMPVC | AF_APPLETALK | AF_PACKET)
//	type: The type this connection shoud use
//		(SOCK_STREAM | SOCK_DGRAM | SOCK_SEQPACKET | SOCK_RAW | SOCK_RDM | SOCK_PACKET)
//		With modifiers [SOCK_NONBLOCK | SOCK_CLOEXEC]
//	protocol: Specifies a protocol defined by the domain (0 specifies the default)
//	host: The host name in domain name form to connect to (Null Terminated)
//	port: The port to connect to
void Connection_InitializeFromHost(Connection* conn, int domain, int type, int protocol, char* host, short port)
{
	conn->socketFD = socket(domain, type, protocol);
	

	// Use getaddrinfo() from <netdb.h> to get the server IP
	
	// initialize struct parameters of getaddrinfo()
	struct addrinfo * addr_info = NULL;
	//struct addrinfo hints;
	int error;
    
	// initialize 'hints'
	
	//memset(&hints, 0, sizeof(struct addrinfo));
	//hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	//hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	//hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	//hints.ai_protocol = 0;          /* Any protocol */
	//hints.ai_canonname = NULL;
	//hints.ai_addr = NULL;
	//hints.ai_next = NULL;
														   
	error = getaddrinfo(host, NULL, NULL, &addr_info);
	if (error != 0) 
	{    
		printf("Error getting address info: %d\n", error);
		return;
	}

	// pull struct sockAddr data pointer from 'addr_info'	
	conn->connAddr = *(struct sockaddr_in*)addr_info->ai_addr;

	
	freeaddrinfo(addr_info);
	//conn->connAddr.sin_addr.s_addr = inet_pton(host);
	//conn->connAddr.sin_port = htons(port);
	//conn->connAddr.sin_family = domain;
}



///
//Initializes a Connection from a human readable IP Address
//
//Parameters:
//	conn: A pointer to the Connection to initialize
//	domain: The domain this connection should use 
//		(AF_UNIX | AF_INET | AF_INET6 | AF_IPX | AF_NETLINK | AF_X25 | AF_AX25 | AF_ATMPVC | AF_APPLETALK | AF_PACKET)
//	type: The type this connection shoud use
//		(SOCK_STREAM | SOCK_DGRAM | SOCK_SEQPACKET | SOCK_RAW | SOCK_RDM | SOCK_PACKET)
//		With modifiers [SOCK_NONBLOCK | SOCK_CLOEXEC]
//	protocol: Specifies a protocol defined by the domain (0 specifies the default)
//	host: The host name as an integer to connect to
//	port: The port to connect to
void Connection_InitializeFromInt(Connection* conn, int domain, int type, int protocol, int host, short port)
{
	conn->socketFD = socket(domain, type, protocol);
	conn->connAddr.sin_family = domain;
	conn->connAddr.sin_addr.s_addr = htonl(host);
	conn->connAddr.sin_port = htons(port);
}


///
//Frees the data used by this connection and terminates the connection if it was not already terminated.
//
//Parameters:
//	conn: Pointer to the connection to free
void Connection_Free(Connection* conn)
{
	free(conn);
}


///
//Opens a connection to allow the transfer of data
//
//Parameters:
//	conn: Pointer to The connection to open
void Connection_Open(Connection* conn)
{
	connect(conn->socketFD, (struct sockaddr *)&(conn->connAddr), sizeof(conn->connAddr));
}

///
//Closes a connection terminating the transfer of data
//
//Parameters:
//	conn: Pointer to The connection to terminate
void Connection_Close(Connection* conn)
{
	shutdown(conn->socketFD, SHUT_RDWR);
	close(conn->socketFD);
}












