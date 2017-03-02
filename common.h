#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <errno.h>

#define SOCKET_TIMEOUT_SEC 2

typedef enum _status {
    STAT_OK = 0,
    STAT_ERR_RESOLVE_HOSTNAME = -1,
	STAT_ERR_CONNECT_FAILED   = -2,
	STAT_ERR_NOT_CONNECTED    = -3,
	/* socket recv error */
	STAT_ERR_AGAIN            = EAGAIN,
	STAT_ERR_BADF             = EBADF,
	STAT_ERR_CONNREFUSED      = ECONNREFUSED,
	STAT_ERR_FAULT            = EFAULT,
	STAT_ERR_INTR             = EINTR,
	STAT_ERR_INVAL            = EINVAL,
	STAT_ERR_NOMEM            = ENOMEM,
	STAT_ERR_NOTCONN          = ENOTCONN,
	STAT_ERR_NOTSOCK          = ENOTSOCK,
} Status;

typedef enum _package_type {
    PKG_NOTIFY,
	PKG_NOTIFY_RESPONSE,
	PKG_REQUEST,
	PKG_RESPONSE,
	PKG_HEARTBEAT,
	PKG_HEARTBEAT_RESPONSE
} PackageType;

typedef enum _encoding_type {
    ENCODING_GOB,
	ENCODING_JSON,
	ENCODING_BSON,
	ENCODING_PROTOBUF
} EncodingType;

typedef unsigned char PackageIDType;
typedef unsigned short PackageSizeType;

#endif /* COMMON_H */