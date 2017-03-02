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

Bytes::Bytes(void* ptr, size_t size)
    : m_ptr(ptr),
      m_pos(0),
      m_size(size),
      m_capacity(size)
{}

Bytes::~Bytes() {
    free(m_ptr);
    m_ptr = NULL;
    m_size = 0;
    m_capacity = 0;
}

void* Bytes::Ptr() {
    return m_ptr;
}

size_t Bytes::Size() {
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

void Bytes::Write(short s) {
    Write((unsigned char)(s >> 8));
    Write((unsigned char)(s & 0x00FF));
}

void Bytes::Write(const void* ptr, size_t size) {
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

    c = ((char*)m_ptr)[m_pos];
    m_pos++;

    return true;
}

bool Bytes::Read(short &s) {
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
    if((m_pos + size) > m_size) return false;

    memcpy(ptr, (void*)((size_t)m_ptr+m_pos), size);
    m_pos += size;

    return true;
}
