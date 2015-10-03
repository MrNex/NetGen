#ifndef TCPCONNECTION
#define TCPCONNECTION

#include "Connection.h"

///
//Initializes a TCP Connection which has a domain of AF_INET, a type of SOCK_STREAM,
//and uses the default AF_INET protocol.
//
//Parameters:
//	conn: A pointer to the connection to initialize
//	host: The host to connect to in IP form (null terminated)
//	port: The port to connect to
void TCPConnection_InitializeFromIP(Connection* conn, char* host, short port);

///
//Initializes a TCP Connection which has a domain of AF_INET and a type of SOCK_STREAM
//which uses the default AF_INET protocol.
//
//Parameters:
//	conn: A pointer to the connection to initialize
//	host: The host to connect to in Domain name form (Null terminated)
//	port: The port to connect to
void TCPConnection_InitializeFromHost(Connection* conn, char* host, short port);

///
//Initializes a TCP Connection which has a domain of AF_INET and a type of SOCK_STREAM
//which uses the default AF_INET protocol.
//
//Parameters:
//	conn: A pointer to the connection to initialize
//	host: The host to connect to in integer form
//	port: The port to connect to
void TCPConnection_InitializeFromInt(Connection* conn, int host, short port);


///
//Sends information from a buffer through a TCP Connection
//
//Parameters:
//	conn: A pointer to the connection to transmit data through
//	buffer: The character array of data to send
//	length:	The number of bytes to send
int TCPConnection_Write(Connection* conn, char* buffer, int length);

///
//Recieves information from a TCP Connection and places it in a buffer
//
//Parameters:
//	conn: A pointer to the connection to read data from
//	buffer: A pointer to the buffer to place the data read from the connection in
//	length: The maximum amount of data to read
//
//Returns:
//	The amount of characters read
int TCPConnection_Read(Connection* conn, char* buffer, int length);

#endif
