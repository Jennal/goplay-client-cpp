#ifndef BYTES_TEST_HPP
#define BYTES_TEST_HPP

#include <cstdio>
#include "bytes.hpp"

void bytes_print(Bytes& b) {
    printf("Bytes(%p) => %p | %ld:\n", &b, b.Ptr(), b.Size());
    size_t size = b.Size();
    char* ptr = (char*)b.Ptr();
    for(int i=0; i<size; ++i) {
        printf("%02x ", ptr[i]);
        if ((i+1)%16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void bytes_test() {
    /* write byte */
    Bytes b;
    bytes_print(b);
    for(int i=0; i<26; ++i){
        b.Write((unsigned char)('a' + i));
    }
    
    bytes_print(b);
    printf("================\n");

    /* write []byte */
    Bytes b2;
    bytes_print(b2);
    for(int i=0; i<3; ++i){
        b2.Write("Hello", 6);
    }
    
    bytes_print(b2);
    printf("================\n");

    /* write short */
    Bytes b3;
    bytes_print(b3);
    printf("%04x => %d\n", (short)18, (short)18);
    b3.Write((short)18);

    printf("%04x => %d\n", (short)(256*16*2+256), (short)(256*16*2+256));
    b3.Write((short)(256*16*2+256));
    
    bytes_print(b3);
    printf("================\n");

    /* read byte */
    bytes_print(b);
    unsigned char c;
    for(int i=0; i<26; ++i){
        bool ok = b.Read(c);
        printf("%d %c\n", ok, c);
    }
    printf("\n");
    printf("================\n");

    /* read []byte */
    bytes_print(b2);
    for(int i=0; i<3; ++i){
        char str[6];
        bool ok = b2.Read(str, 6);
        printf("%d %s\n", ok, str);
    }
    printf("\n");
    printf("================\n");

    /* read short */
    bytes_print(b3);
    for(int i=0; i<2; ++i){
        short val = 0;
        bool ok = b3.Read(val);
        printf("%d %d\n", ok, val);
    }
    printf("\n");
}

#endif