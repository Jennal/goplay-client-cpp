#include "test_common.hpp"

void bytes_print(Bytes& b) {
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

void header_print(Header& header) {
    printf("Header(%p) => {", &header);

    printf("Type: %d, ", header.Type);
    printf("Encoding: %d, ", header.Encoding);
    printf("ID: %d, ", header.ID);
    printf("ContentSize: %d", header.ContentSize);
    printf("Route: %s", header.Route.c_str());

    printf("}\n");
}