#ifndef CUSTOMALLOCATOR_H
#define CUSTOMALLOCATOR_H

#include <memory>
#include <cassert>

#define PRINT_OFF

#ifndef PRINT_OFF
#include <iostream>
#endif

template <typename T, std::size_t BlockSize = 10>
class CustomAllocator
{
public:

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;

    template<typename U>
    struct rebind {
        using other = CustomAllocator<U>;
    };

    CustomAllocator()
        : m_itemsCnt(0)
        , m_ptr(nullptr)
    {
    }

    ~CustomAllocator()
    {
        if (m_ptr != nullptr) {
            std::free(m_ptr);
        }
    }

    template <typename U>
    CustomAllocator(const CustomAllocator<U> &)
    {
        // should we make a copy of the rhs.m_buffer ?
        // No, we should not!
    }

    T* allocate (std::size_t n)
    {
#ifndef PRINT_OFF
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
        assert(BlockSize - m_itemsCnt >= n);
        if (m_ptr == nullptr) {
            m_ptr = reinterpret_cast<T *>(std::malloc(BlockSize * sizeof(T)));
            if (m_ptr == nullptr) {
                throw std::bad_alloc();
            }
        }
        T *p = &m_ptr[m_itemsCnt];
        m_itemsCnt += n;
        return p;
    }

    void deallocate ([[maybe_unused]] T* p, [[maybe_unused]] std::size_t n)
    {
#ifndef PRINT_OFF
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args)
    {
#ifndef PRINT_OFF
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p)
    {
#ifndef PRINT_OFF
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        p->~T();
    }

private:
    size_type m_itemsCnt;
    T *m_ptr;

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
