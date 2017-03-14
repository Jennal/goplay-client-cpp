// Copyright (C) 2017 Jennal(jennalcn@gmail.com). All rights reserved.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

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