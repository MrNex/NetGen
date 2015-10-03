#include <stdlib.h>
#include <stdio.h>

#include "Connection/TCPConnection.h"

int main(int argc, char * argv[])
{
	/* initialize three connections and close them 
	 first test of Connection.c */

	int test_domain = AF_INET;
	int test_type = SOCK_STREAM;

	char buf[1024];

	// Connection one
	Connection * one;
	one = Connection_Allocate();
	printf("Allocated\n");
	TCPConnection_InitializeFromIP(one, "24.56.178.140", 13);
	printf("Initialized\n");
	Connection_Open(one);
	printf("Opened\n");

	int charsRead = TCPConnection_Read(one, buf, 1024);
	buf[charsRead] = '\0';
	printf("Read:\n%s\n", buf);

	Connection_Close(one);
	printf("Closed\n");
	Connection_Free(one);
	printf("Freed\n");
	
	// Connection two
	/*
	Connection * two;
	two = Connection_Allocate();
	Connection_InitializeFromHost(two, test_domain, test_type, test_protocol, "localhost", test_port);
	Connection_Open(two);
	Connection_Close(two);
	Connection_Free(two);
	*/

	// Connection three
	/*
	Connection * three;
	three = Connection_Allocate();
	int host_int = inet_pton("127.0.0.1");
	Connection_InitializeFromInt(three, test_domain, test_type, test_protocol, host_int, test_port);
	Connection_Open(three);
	Connection_Close(three);
	Connection_Free(three);
	*/


	return(EXIT_SUCCESS);
}
