#include "test_common.hpp"
#include <map>

void bytes_print(const Bytes& b) {
    printf("Bytes(%p) => %p | %ld:\n", &b, b.Ptr(), b.Size());
    size_t size = b.Size();
    unsigned char* ptr = (unsigned char*)b.Ptr();
    for(int i=0; i<size; ++i) {
        printf("%02x ", ptr[i]);
        if ((i+1)%16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void header_print(const Header& header) {
    printf("Header(%p) => {Type: %d, Encoding: %d, ID: %d, ContentSize: %d, Route: %s}\n", 
        &header,
        header.Type,
        header.Encoding,
        header.ID,
        header.ContentSize,
        header.Route.c_str()
    );
}

std::string status_str(Status s) {
    std::map<Status, std::string> m = {
        { STAT_OK, "STAT_OK" },
        { STAT_ERR_RESOLVE_HOSTNAME, "STAT_ERR_RESOLVE_HOSTNAME" },
        { STAT_ERR_CONNECT_FAILED, "STAT_ERR_CONNECT_FAILED" },
        { STAT_ERR_NOT_CONNECTED, "STAT_ERR_NOT_CONNECTED" },
        { STAT_ERR_RECV_AGAIN, "STAT_ERR_RECV_AGAIN" },
        { STAT_ERR_RECV_BADF, "STAT_ERR_RECV_BADF" },
        { STAT_ERR_RECV_CONNREFUSED, "STAT_ERR_RECV_CONNREFUSED" },
        { STAT_ERR_RECV_FAULT, "STAT_ERR_RECV_FAULT" },
        { STAT_ERR_RECV_INTR, "STAT_ERR_RECV_INTR" },
        { STAT_ERR_RECV_INVAL, "STAT_ERR_RECV_INVAL" },
        { STAT_ERR_RECV_NOMEM, "STAT_ERR_RECV_NOMEM" },
        { STAT_ERR_RECV_NOTCONN, "STAT_ERR_RECV_NOTCONN" },
        { STAT_ERR_RECV_NOTSOCK, "STAT_ERR_RECV_NOTSOCK" },
        { STAT_ERR_SEND_ACCES, "STAT_ERR_SEND_ACCES" },
        { STAT_ERR_SEND_AGAIN, "STAT_ERR_SEND_AGAIN" },
        { STAT_ERR_SEND_BADF, "STAT_ERR_SEND_BADF" },
        { STAT_ERR_SEND_CONNRESET, "STAT_ERR_SEND_CONNRESET" },
        { STAT_ERR_SEND_DESTADDRREQ, "STAT_ERR_SEND_DESTADDRREQ" },
        { STAT_ERR_SEND_FAULT, "STAT_ERR_SEND_FAULT" },
        { STAT_ERR_SEND_INTR, "STAT_ERR_SEND_INTR" },
        { STAT_ERR_SEND_INVAL, "STAT_ERR_SEND_INVAL" },
        { STAT_ERR_SEND_ISCONN, "STAT_ERR_SEND_ISCONN" },
        { STAT_ERR_SEND_MSGSIZE, "STAT_ERR_SEND_MSGSIZE" },
        { STAT_ERR_SEND_NOBUFS, "STAT_ERR_SEND_NOBUFS" },
        { STAT_ERR_SEND_NOMEM, "STAT_ERR_SEND_NOMEM" },
        { STAT_ERR_SEND_NOTCONN, "STAT_ERR_SEND_NOTCONN" },
        { STAT_ERR_SEND_NOTSOCK, "STAT_ERR_SEND_NOTSOCK" },
        { STAT_ERR_SEND_OPNOTSUPP, "STAT_ERR_SEND_OPNOTSUPP" },
        { STAT_ERR_SEND_PIPE, "STAT_ERR_SEND_PIPE" },
    };

    return m[s];
}
