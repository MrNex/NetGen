#include <stdlib.h>
#include <stdio.h>

#include "Connection.h"

int main(int argc, char * argv[])
{
	/* initialize three connections and close them 
	 first test of Connection.c */

	int test_domain = AF_INET;
	int test_type = SOCK_STREAM;
	int	test_protocol = 0;
	short test_port = 8476;

	// Connection one
	Connection * one;
	one = Connection_Allocate();
	Connection_InitializeFromIP(one, test_domain, test_type, test_protocol, "127.0.0.1", test_port);
	Connection_Open(one);
	Connection_Close(one);
	Connection_Free(one);
	
	// Connection two
	Connection * two;
	two = Connection_Allocate();
	Connection_InitializeFromHost(two, test_domain, test_type, test_protocol, "localhost", test_port);
	Connection_Open(two);
	Connection_Close(two);
	Connection_Free(two);

	// Connection three
	Connection * three;
	three = Connection_Allocate();
	int host_int = inet_pton("127.0.0.1");
	Connection_InitializeFromInt(three, test_domain, test_type, test_protocol, host_int, test_port);
	Connection_Open(three);
	Connection_Close(three);
	Connection_Free(three);



	return(EXIT_SUCCESS);
}
