#ifndef CUSTOMALLOCATOR_H
#define CUSTOMALLOCATOR_H

#include <memory>
#include <iostream>
#include <stack>
#include <queue>
#include <cassert>

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
        : m_itemCnt(0)
    {
        assert(BlockSize > 0);
        T *p = reinterpret_cast<T *>(std::malloc(BlockSize * sizeof(T)));
        if (p == nullptr) {
            throw std::bad_alloc();
        }
        m_blocks.push(p);
    }

    ~CustomAllocator()
    {
        while (m_blocks.size() > 0) {
            T *p = m_blocks.top();
            std::free(p);
            m_blocks.pop();
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
//        auto p = std::malloc(n * sizeof(T));
//        if (!p) {
//            throw std::bad_alloc();
//        }
//        return reinterpret_cast<T *>(p);
        assert(n == 1);

        if (m_freeItems.size() > 0) {
            T *p = m_freeItems.front();
            m_freeItems.pop();
            return p;
        }

        if (m_itemCnt == BlockSize) {
            T *p = reinterpret_cast<T *>(std::malloc(BlockSize * sizeof(T)));
            if (p == nullptr) {
                throw std::bad_alloc();
            }
            m_blocks.push(p);
            m_itemCnt = 0;
            return p;
        } else {
            T *p = &(m_blocks.top()[m_itemCnt]);
            m_itemCnt += n;
            return p;
        }
    }

    void deallocate (T* p, std::size_t n)
    {
#ifndef PRINT_OFF
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#else
        UNUSED(n);
#endif
        assert(n == 1);
        m_freeItems.push(p);
//        std::free(p);
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
    std::queue<T *> m_freeItems;
    std::stack<T *> m_blocks;
    std::size_t m_itemCnt;

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
