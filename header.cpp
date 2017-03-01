#include "header.hpp"

Header::Header(PackageType t, EncodingType e, PackageIDType id, PackageSizeType size)
    : Type(t),
      Encoding(e),
      ID(id),
      ContentSize(size)
{}

Header::~Header() {}