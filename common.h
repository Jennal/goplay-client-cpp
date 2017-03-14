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
    PKG_NOTIFY,
	PKG_REQUEST,
	PKG_RESPONSE,
	PKG_HEARTBEAT,
	PKG_HEARTBEAT_RESPONSE,

	PKG_RPC_NOTIFY,
	PKG_RPC_REQUEST,
	PKG_RPC_RESPONSE
} PackageType;

typedef enum _encoding_type {
	ENCODING_NONE,
    ENCODING_GOB,
	ENCODING_JSON,
	ENCODING_BSON,
	ENCODING_PROTOBUF
} EncodingType;

typedef unsigned char PackageIDType;
typedef unsigned short PackageSizeType;

#endif /* COMMON_H */