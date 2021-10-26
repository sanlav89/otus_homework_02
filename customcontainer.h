#ifndef CUSTOMCONTAINER_H
#define CUSTOMCONTAINER_H

#include <memory>
#include <cstring>
#include <iostream>

template <class T, class Alloc = std::allocator<T>, std::size_t Capacity = 0 >
class CustomContainer {
public:

    // Iterator Class
    class iterator {
    public:
        iterator()
            : m_ptr(nullptr)
        {
        }

        iterator(T *p)
            : m_ptr(p)
        {
        }

        bool operator==(const iterator& other) const
        {
            return m_ptr == other.m_ptr;
        }

        bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }

        T operator*() const
        {
            return *m_ptr;
        }

        iterator& operator++()
        {
            ++m_ptr;
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp(*this);
            ++*this;
            return temp;
        }

    private:
        T *m_ptr;
    };


    CustomContainer(std::size_t = Capacity)
        : m_size(0)
        , m_capacity(Capacity)
        , m_alloc(new Alloc)
    {
        m_data = m_alloc->allocate(Capacity);
    }

    ~CustomContainer()
    {
        for (std::size_t i = 0; i < m_size; i++) {
            m_alloc->destroy(&m_data[i]);
        }
        if (m_capacity > 0) {
            m_alloc->deallocate(m_data, m_capacity);
        }
        delete m_alloc;
    }

    void push_back(const T &value)
    {
        if (m_size == m_capacity) {
            T *ptr_old = m_data;
            T *ptr_new;
            if (m_capacity == 0) {
                m_capacity = 1;
            } else {
                m_capacity *= 2;
            }

            m_data = m_alloc->allocate(m_capacity);
            ptr_new = m_data;

            for (std::size_t i = 0; i < m_size; i++) {
                m_alloc->construct(ptr_new++, *ptr_old++);
            }

            m_alloc->construct(ptr_new, value);
            for (std::size_t i = 0; i < m_size; i++) {
                m_alloc->destroy(ptr_old--);
            }
            m_alloc->deallocate(ptr_old, m_size);

            m_size++;

        } else {
            m_alloc->construct(&m_data[m_size++], value);
        }
    }

    iterator begin()
    {
        return iterator(m_data);
    }

    iterator end()
    {
        return iterator(m_data + m_size);
    }

    std::size_t size() const
    {
        return m_size;
    }

    T &operator[](std::size_t index)
    {
        if (index >= m_size) {
            throw std::out_of_range("Error: Array index out of bound");
        }
        return m_data[index];
    }


private:
    std::size_t m_size;
    std::size_t m_capacity;
    T *m_data;
    Alloc *m_alloc;

};

#endif // CUSTOMCONTAINER_H
