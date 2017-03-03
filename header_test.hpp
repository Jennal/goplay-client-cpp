#ifndef HEADER_TEST_HPP
#define HEADER_TEST_HPP

#include "header.hpp"
#include "test_common.hpp"

void header_test() {
    Header header4((PackageType)128, (EncodingType)255, (PackageIDType)256, (PackageSizeType)32768);
    printf("header4: %d, %d, %d, %d\n", header4.Type, header4.Encoding, header4.ID, header4.ContentSize);

    Bytes b4;
    header4.GetBytes(b4);
    bytes_print(b4);

    for(int i=0; i<512; ++i) {
        Header header3((PackageType)1, (EncodingType)2, (PackageIDType)3);
        printf("header3: %d, %d, %d, %d\n", header3.Type, header3.Encoding, header3.ID, header3.ContentSize);
        Bytes b3;
        header3.GetBytes(b3);
        bytes_print(b3);
    }
}

#endif