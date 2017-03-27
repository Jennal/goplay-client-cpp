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

#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <errno.h>

#define SOCKET_TIMEOUT_SEC 2

#define HEARTBEAT_TIMEOUT (3000)
#define HEARTBEAT_INTERVAL (15000)
#define HEARTBEAT_MAX_TIMEOUT (3)

#define DEFAULT_ENCODING (ENCODING_JSON)

typedef enum _status {
    STAT_OK = 0,
    STAT_ERR_RESOLVE_HOSTNAME = -1,
	STAT_ERR_CONNECT_FAILED   = -2,
	STAT_ERR_NOT_CONNECTED    = -3,
	/* socket recv error */
	STAT_ERR_RECV_AGAIN       = EAGAIN,
	STAT_ERR_RECV_BADF        = EBADF,
	STAT_ERR_RECV_CONNREFUSED = ECONNREFUSED,
	STAT_ERR_RECV_FAULT       = EFAULT,
	STAT_ERR_RECV_INTR        = EINTR,
	STAT_ERR_RECV_INVAL       = EINVAL,
	STAT_ERR_RECV_NOMEM       = ENOMEM,
	STAT_ERR_RECV_NOTCONN     = ENOTCONN,
	STAT_ERR_RECV_NOTSOCK     = ENOTSOCK,
	/* socket send error */
	STAT_ERR_SEND_ACCES       = EACCES,
	STAT_ERR_SEND_AGAIN       = EAGAIN,
	STAT_ERR_SEND_BADF        = EBADF,
	STAT_ERR_SEND_CONNRESET   = ECONNRESET,
	STAT_ERR_SEND_DESTADDRREQ = EDESTADDRREQ,
	STAT_ERR_SEND_FAULT       = EFAULT,
	STAT_ERR_SEND_INTR        = EINTR,
	STAT_ERR_SEND_INVAL       = EINVAL,
	STAT_ERR_SEND_ISCONN      = EISCONN,
	STAT_ERR_SEND_MSGSIZE     = EMSGSIZE,
	STAT_ERR_SEND_NOBUFS      = ENOBUFS,
	STAT_ERR_SEND_NOMEM       = ENOMEM,
	STAT_ERR_SEND_NOTCONN     = ENOTCONN,
	STAT_ERR_SEND_NOTSOCK     = ENOTSOCK,
	STAT_ERR_SEND_OPNOTSUPP   = EOPNOTSUPP,
	STAT_ERR_SEND_PIPE        = EPIPE
} Status;

typedef enum _package_type {
    PKG_NOTIFY             = 0,
	PKG_REQUEST            = 1,
	PKG_RESPONSE           = 2,
	PKG_PUSH               = 3,
	PKG_HEARTBEAT          = 4,
	PKG_HEARTBEAT_RESPONSE = 5,

	PKG_RPC = 0x10,

	PKG_RPC_NOTIFY   = PKG_NOTIFY   | PKG_RPC,
	PKG_RPC_REQUEST  = PKG_REQUEST  | PKG_RPC,
	PKG_RPC_RESPONSE = PKG_RESPONSE | PKG_RPC,
	PKG_RPC_PUSH     = PKG_PUSH     | PKG_RPC
} PackageType;

typedef enum _encoding_type {
	ENCODING_NONE     = 0,
    ENCODING_GOB      = 1,
	ENCODING_JSON     = 2,
	ENCODING_BSON     = 3,
	ENCODING_PROTOBUF = 4
} EncodingType;

typedef unsigned char PackageIDType;
typedef unsigned short PackageSizeType;

#endif /* COMMON_H */