#include <stdio.h>
#include "tcpclient.h"


int main(int argv, char * argc [])
{
	int socket_id = tcp_client("127.0.0.1", 9999);
	
	int numbytes = 0;
	char buf[10];
	numbytes = recv(socket_id,buf,10,0);
	if(numbytes == -1)
	{
		fprintf(stderr, "Error receive \n");
		exit(4);
	}
	buf[numbytes] = '\0';
	printf("Received %s \n", buf);	
	freeaddrinfo(res);
	close(socket_id);	
	return 0;
}