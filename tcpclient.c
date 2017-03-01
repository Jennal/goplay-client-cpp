#include "common.h"
#include "tcpclient.h"

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
		sockfd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (sockfd < 0) {
			/* error, couldn't create socket, so try another */
			continue;
		}

		status = connect(sockfd, tmp->ai_addr, tmp->ai_addrlen);
		if (status < 0) {
			/* error, couldn't connect, so try another */
			close(sockfd);
			continue;
		}

		break;
	}

	freeaddrinfo(servinfo);

	if (tmp == NULL) {
		/* couldn't connect anywhere */
		return (int)STAT_ERR_CONNECT_FAILED;
	}

	return sockfd;
}