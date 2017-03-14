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

#ifndef BYTES_HPP
#define BYTES_HPP

#include "common.h"
#include <string>

class Bytes {
private:
    void* m_ptr;
    size_t m_pos;
    size_t m_size;
    size_t m_capacity;

public:
    Bytes();
    Bytes(const Bytes& b);
    Bytes(const void* ptr, size_t size);
    Bytes(const std::string& str);
    ~Bytes();

    void* Ptr() const;
    size_t Size() const;

    void Write(unsigned char c);
    void Write(unsigned short s);
    void Write(const void* ptr, size_t size);

    bool Read(unsigned char &c);
    bool Read(unsigned short &s);
    bool Read(void* ptr, size_t size);
};

#endif