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
    Bytes(const void* ptr, size_t size);
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