#include "header.hpp"

#define MAX_ID 255

const size_t Header::HeaderSize = 5;
static PackageIDType s_id = 0;

PackageIDType nextID() {
    PackageIDType result = s_id;

    if (s_id == MAX_ID) s_id = 0;
    else s_id++;

    return result;
}

Header::Header() {}

Header::Header(PackageType t, EncodingType e, PackageSizeType size)
    : Type(t),
      Encoding(e),
      ContentSize(size)
{
    ID = nextID();
}

Header::Header(PackageType t, EncodingType e, PackageIDType id, PackageSizeType size)
    : Type(t),
      Encoding(e),
      ID(id),
      ContentSize(size)
{}

Header::Header(Bytes& bytes) {
    SetBytes(bytes);
}

Header::~Header() {}

bool Header::SetBytes(Bytes& bytes) {
    unsigned char val = 0;
    if ( ! bytes.Read(val)) return false;
    Type = (PackageType)val;

    if ( ! bytes.Read(val)) return false;
    Encoding = (EncodingType)val;
    
    if ( ! bytes.Read(val)) return false;
    ID = (PackageIDType)val;

    unsigned short sval = 0;
    if ( ! bytes.Read(sval)) return false;
    ContentSize = (PackageSizeType)sval;

    return true;
}

void Header::GetBytes(Bytes& bytes) const {
    bytes.Write((unsigned char)Type);
    bytes.Write((unsigned char)Encoding);
    bytes.Write((unsigned char)ID);
    bytes.Write((unsigned short)ContentSize);
}
