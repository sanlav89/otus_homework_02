#ifndef CUSTOMALLOCATOR_H
#define CUSTOMALLOCATOR_H

#include <memory>
#include <iostream>
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
//    static constexpr int BlockSize = 10;

    template<typename U>
    struct rebind {
        using other = CustomAllocator<U>;
    };

    CustomAllocator()
        : m_blockSize(BlockSize)
        , m_cntOfFreeBlocks(0)
        , m_p(nullptr)
    {
//        m_p = reinterpret_cast<T *>(std::malloc(m_blockSize * sizeof(T)));
//        if (m_p == nullptr) {
//            throw std::bad_alloc();
//        }
    }

    ~CustomAllocator()
    {
//        if (m_p != nullptr) {
//            std::free(m_p);
//        }
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
//        if (m_blockSize - m_cntOfFreeBlocks >= n) {
//            T *p = &m_p[m_cntOfFreeBlocks];
//            m_cntOfFreeBlocks += n;
//            return p;
//        } else {
//            throw std::bad_alloc();
//        }
        auto p = std::malloc(n * sizeof(T));
        if (!p) {
            throw std::bad_alloc();
        }
        return reinterpret_cast<T *>(p);
    }

    void deallocate (T* p, std::size_t n)
    {
#ifndef PRINT_OFF
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#else
        UNUSED(n);
#endif
        std::free(p);
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
    std::size_t m_blockSize;
    std::size_t m_cntOfFreeBlocks;
    T *m_p;

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
