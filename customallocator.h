#ifndef CUSTOMALLOCATOR_H
#define CUSTOMALLOCATOR_H

#include <memory>
#include <iostream>

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

//    CustomAllocator(const int &part_size)

    template <typename U>
//    CustomAllocator(const CustomAllocator<U>&);
    CustomAllocator(const CustomAllocator<U>&)
    {
        // should we make a copy of the rhs.m_buffer ?
        // No, we should not!
    }

//    T* allocate (std::size_t n);
    T* allocate (std::size_t n)
    {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        auto p = std::malloc(n * sizeof(T));
        if (!p) {
            throw std::bad_alloc();
        }
        return reinterpret_cast<T *>(p);
    }

//    void deallocate (T* p, std::size_t n);
    void deallocate (T* p, std::size_t n)
    {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        std::free(p);
    }

    template<typename U, typename ...Args>
//    void construct(U *p, Args &&...args);
    void construct(U *p, Args &&...args)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        new(p) U(std::forward<Args>(args)...);
    }

//    void destroy(T *p);
    void destroy(T *p)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        p->~T();
    }

//private:
//    int m_size;

};

template <class T, class U>
constexpr bool operator== (const CustomAllocator<T>&, const CustomAllocator<U>&) noexcept
{
    return false;
}

template <class T, class U>
constexpr bool operator!= (const CustomAllocator<T>&, const CustomAllocator<U>&) noexcept
{
    return false;
}

#endif // CUSTOMALLOCATOR_H
