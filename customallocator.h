#ifndef CUSTOMALLOCATOR_H
#define CUSTOMALLOCATOR_H

#include <cstdint>

template <typename T>
class CustomAllocator
{
public:

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    CustomAllocator() = default;
    ~CustomAllocator() = default;

    template <typename U>
    CustomAllocator(const CustomAllocator<U>&);

    T* allocate (std::size_t n);

    void deallocate (T* p, std::size_t n);

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args);

    void destroy(T *p);

};

#endif // CUSTOMALLOCATOR_H
