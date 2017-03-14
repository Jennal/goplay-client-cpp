// Copyright (C) 2017 Jennal(jennalcn@gmail.com). All rights reserved.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

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
