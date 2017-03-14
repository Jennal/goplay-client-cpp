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

#include "bytes.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define DEFAULT_SIZE 8

Bytes::Bytes()
    : m_ptr(NULL),
      m_pos(0),
      m_size(0),
      m_capacity(DEFAULT_SIZE)
{
    m_ptr = malloc(DEFAULT_SIZE);
}

Bytes::Bytes(const Bytes& b)
    : Bytes(b.Ptr(), b.Size())
{}

Bytes::Bytes(const void* ptr, size_t size)
    : m_pos(0),
      m_size(size),
      m_capacity(size)
{
    m_ptr = malloc(size);
    memcpy(m_ptr, ptr, size);
}

Bytes::Bytes(const std::string& str)
    : Bytes(str.c_str(), str.size())
{}

Bytes::~Bytes() {
    free(m_ptr);
    m_ptr = NULL;
    m_size = 0;
    m_capacity = 0;
}

void* Bytes::Ptr() const {
    return m_ptr;
}

size_t Bytes::Size() const {
    return m_size;
}

void Bytes::Write(unsigned char c) {
    if(m_size == m_capacity) {
        m_capacity += m_capacity / 2;
        m_ptr = realloc(m_ptr, m_capacity);
    }

    ((char*)m_ptr)[m_size] = c;
    m_size++;
}

void Bytes::Write(unsigned short s) {
    Write((unsigned char)(s >> 8));
    Write((unsigned char)(s & 0x00FF));
}

void Bytes::Write(const void* ptr, size_t size) {
    if(size <= 0) return;

    size_t newCap = m_capacity;
    while(newCap < (m_size + size)) {
        newCap += newCap / 2;
    }
    if (newCap > m_capacity) {
        m_capacity = newCap;
        m_ptr = realloc(m_ptr, m_capacity);
    }

    memcpy((void*)((size_t)m_ptr+m_size), ptr, size);
    m_size += size;
}

bool Bytes::Read(unsigned char &c) {
    if(m_pos > m_size) return false;

    c = ((unsigned char*)m_ptr)[m_pos];
    m_pos++;

    return true;
}

bool Bytes::Read(unsigned short &s) {
    if((m_pos + 2) > m_size) return false;

    unsigned char h = 0;
    unsigned char l = 0;
    
    if ( ! Read(h)) return false;
    if ( ! Read(l)) return false;

    s = h;
    s = (s << 8) | l;

    return true;
}

bool Bytes::Read(void* ptr, size_t size) {
    if(size <= 0) return true;
    if((m_pos + size) > m_size) return false;

    memcpy(ptr, (void*)((size_t)m_ptr+m_pos), size);
    m_pos += size;

    return true;
}
