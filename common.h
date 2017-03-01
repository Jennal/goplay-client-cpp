#ifndef COMMON_H
#define COMMON_H

typedef enum _status {
    STAT_OK = 0,
    STAT_ERR_RESOLVE_HOSTNAME = -1,
	STAT_ERR_CONNECT_FAILED = -2,
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
typedef void* Bytes;

#endif /* COMMON_H */