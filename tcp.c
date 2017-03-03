#include <stdio.h>
#include "common.h"
#include "tcp.h"
#include <arpa/inet.h>

int tcp_client(const char *hostname, const char *port)
{
	int status = 0; /* return status of the inet/socket functions */

	struct addrinfo hints;
	struct addrinfo *servinfo = NULL;  /* will point to the results */
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_UNSPEC; /* AF_INET or AF_INET6 for IPv or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* TCP protocol */

	status = getaddrinfo(hostname, port, &hints, &servinfo);
	if (status < 0) {
		return (int)STAT_ERR_RESOLVE_HOSTNAME;
	}

	struct addrinfo *tmp = NULL;
	int sockfd = 0;

	for (tmp = servinfo; tmp != NULL; tmp = tmp->ai_next) {
		void* addr;
        char* ipver;
		char ipstr[INET6_ADDRSTRLEN];


        /* get pointer to the address itself */
        /* different fields in IPv4 and IPv6 */
        if(tmp->ai_family == AF_INET)  /* address is IPv4 */
        {
            struct sockaddr_in* ipv4 = (struct sockaddr_in*)tmp->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        }
        else  /* address is IPv6 */
        {
            struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)tmp->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }


        /* convert IP to a string and print it */
        inet_ntop(tmp->ai_family, addr, ipstr, sizeof ipstr);
        // printf("  %s: %s\n", ipver, ipstr);

		sockfd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (sockfd < 0) {
			/* error, couldn't create socket, so try another */
			printf("create socket  %s: %s => failed\n", ipver, ipstr);
			continue;
		}

		status = connect(sockfd, tmp->ai_addr, tmp->ai_addrlen);
		if (status < 0) {
			/* error, couldn't connect, so try another */
			printf("Connect to  %s: %s => failed %d => %d \n", ipver, ipstr, status, errno);
			close(sockfd);
			continue;
		}

		printf("Connect to  %s: %s => Success! \n", ipver, ipstr);
		break;
	}

	freeaddrinfo(servinfo);

	if (tmp == NULL) {
		/* couldn't connect anywhere */
		return (int)STAT_ERR_CONNECT_FAILED;
	}

	struct timeval timeout;
	timeout.tv_sec = SOCKET_TIMEOUT_SEC;
	timeout.tv_usec = 0;
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
	setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

	return sockfd;
}