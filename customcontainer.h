#ifndef CUSTOMCONTAINER_H
#define CUSTOMCONTAINER_H

#include <memory>
#include <cstring>
#include <iostream>

template <class T, class Alloc = std::allocator<T>>
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

        T &operator*() const
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


    CustomContainer(std::size_t capacity = 0)
        : m_size(0)
        , m_capacity(capacity)
        , m_data(nullptr)
        , m_alloc(new Alloc)
    {
        if (m_capacity > 0) {
            m_data = m_alloc->allocate(capacity);
        }
    }

    ~CustomContainer()
    {
        delete m_alloc;
    }

    void push_back(const T &value)
    {
        if (m_size >= m_capacity) {
            T *data = m_alloc->allocate(1);
            m_alloc->construct(data, value);
            if (m_data == nullptr) {
                m_data = data;
            }
            m_size++;
        } else {
            m_alloc->construct(&m_data[m_size++], value);
        }
    }

    iterator begin() const
    {
        return iterator(m_data);
    }

    iterator end() const
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
            throw std::out_of_range("Error: Container index out of bound");
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
