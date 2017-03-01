#ifndef HEADER_HPP
#define HEADER_HPP

#include "common.hpp"
#include "tcpclient.h"

class Header {
public:
    PackageType Type;
    EncodingType Encoding;
    PackageIDType ID;
    PackageSizeType ContentSize;

public:
    Header(PackageType t, EncodingType e, PackageIDType id, PackageSizeType size);
    ~Header();
};

#endif /* HEADER_HPP */