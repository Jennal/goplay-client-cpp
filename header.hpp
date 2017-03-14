#ifndef HEADER_HPP
#define HEADER_HPP

#include "common.h"
#include "bytes.hpp"
#include <string>

class Header {
public:
    static const size_t HeaderSize;

public:
    PackageType Type;
    EncodingType Encoding;
    PackageIDType ID;
    Status Stat;
    PackageSizeType ContentSize;
    std::string Route;

public:
    Header();
    Header(Bytes& bytes);
    Header(PackageType t, EncodingType e, PackageSizeType size, const std::string& route);
    Header(PackageType t, EncodingType e, PackageIDType id, Status status, PackageSizeType size, const std::string& route);
    ~Header();

    bool SetBytes(Bytes& bytes);
    void GetBytes(Bytes& bytes) const;
};

#endif /* HEADER_HPP */
