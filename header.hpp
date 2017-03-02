#ifndef HEADER_HPP
#define HEADER_HPP

#include "common.h"
#include "bytes.hpp"

class Header {
public:
    static const size_t HeaderSize;

public:
    PackageType Type;
    EncodingType Encoding;
    PackageIDType ID;
    PackageSizeType ContentSize;

public:
    Header(PackageType t, EncodingType e, PackageIDType id, PackageSizeType size);
    ~Header();

    void GetBytes(Bytes& bytes);
};

#endif /* HEADER_HPP */
