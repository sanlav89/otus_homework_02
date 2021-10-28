#ifndef CUSTOMALLOCATOR_H
#define CUSTOMALLOCATOR_H

#include <memory>
#include <iostream>
#include <stack>
#include <queue>
#include <cassert>
#include <list>

#define PRINT_OFF
#define UNUSED(value) (void)value

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
    {
    }

    ~CustomAllocator()
    {
        while (m_blocks.size() > 0) {
            T *p = m_blocks.front();
            std::free(p);
            m_blocks.pop_front();
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
//        assert()
        if (m_addresses.size() < n) {
            T *p = reinterpret_cast<T *>(std::malloc(BlockSize * sizeof(T)));
            if (p == nullptr) {
                throw std::bad_alloc();
            }
            m_blocks.push_back(p);
            for (auto i = 0u; i < BlockSize; i++) {
                m_addresses.push_back(p++);
            }
        }
        T *p = m_addresses.front();
        for (auto i = 0u; i < n; i++) {
            m_addresses.pop_front();
        }
        return p;
    }

    void deallocate (T* p, std::size_t n)
    {
#ifndef PRINT_OFF
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#else
        UNUSED(n);
#endif
        for (auto i = 0u; i < n; i++) {
            m_addresses.push_back(p++);
        }
        m_addresses.sort();
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
    std::list<T *> m_blocks;
    std::list<T *> m_addresses;

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
