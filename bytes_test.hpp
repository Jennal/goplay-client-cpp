#ifndef BYTES_TEST_HPP
#define BYTES_TEST_HPP

#include <cstdio>
#include "bytes.hpp"
#include "test_common.hpp"

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
    unsigned short sval = 18;
    printf("%04x => %d\n", sval, sval);
    b3.Write(sval);

    sval = 256*16*2+256;
    printf("%04x => %d\n", sval, sval);
    b3.Write(sval);
    
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
        unsigned short val = 0;
        bool ok = b3.Read(val);
        printf("%d %d\n", ok, val);
    }
    printf("\n");
}

#endif