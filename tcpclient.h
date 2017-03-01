#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


/*
  Returns a socket file descriptor,
  from/to which one can read() or write().
  To be close()'d after use.
  Useful for clients wanting to connect to a specific server
  The server must be already listening using connect_to_client().
  This function does not return until a server
  accepted the connection on the specified port.
*/

int tcp_client(const char *hostname, const char *port);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TCPCLIENT_H */