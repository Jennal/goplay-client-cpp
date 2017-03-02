#ifndef BYTES_HPP
#define BYTES_HPP

#include "common.h"

class Bytes {
private:
    void* m_ptr;
    size_t m_pos;
    size_t m_size;
    size_t m_capacity;

public:
    Bytes();
    Bytes(void* ptr, size_t size);
    ~Bytes();

    void* Ptr();
    size_t Size();

    void Write(unsigned char c);
    void Write(short s);
    void Write(const void* ptr, size_t size);

    bool Read(unsigned char &c);
    bool Read(short &s);
    bool Read(void* ptr, size_t size);
};

#endif