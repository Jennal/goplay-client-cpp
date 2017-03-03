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
    Header(Bytes& bytes);
    Header(PackageType t, EncodingType e, PackageSizeType size);
    Header(PackageType t, EncodingType e, PackageIDType id, PackageSizeType size);
    ~Header();

    bool SetBytes(Bytes& bytes);
    void GetBytes(Bytes& bytes) const;
};

#endif /* HEADER_HPP */
