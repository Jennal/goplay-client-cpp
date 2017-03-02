#include "header.hpp"

const size_t Header::HeaderSize = 5;

Header::Header(PackageType t, EncodingType e, PackageIDType id, PackageSizeType size)
    : Type(t),
      Encoding(e),
      ID(id),
      ContentSize(size)
{}

Header::~Header() {}

void Header::GetBytes(Bytes& bytes) {

}