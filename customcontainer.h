#ifndef CUSTOMCONTAINER_H
#define CUSTOMCONTAINER_H

#include <memory>
#include <cstring>

template <class T, class A = std::allocator<T>, std::size_t Capacity = 10 >
class CustomContainer {
public:
    typedef A allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;

    // Iterator Class
    class iterator {
    public:
        iterator()
            : m_ptr(nullptr)
        {
        }
        iterator(T* p)
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
        T* m_ptr;
    };


    CustomContainer(std::size_t = Capacity)
        : m_size(0)
        , m_capacity(Capacity)
        , m_data(new T[Capacity])
    {
    }

    ~CustomContainer()
    {
        if (m_capacity) {
            delete [] m_data;
        }
    }

    void push_back(const T &value)
    {
        if (m_size == m_capacity) {
            T *old = m_data;
            if (m_capacity == 0) {
                m_capacity = 1;
            } else {
                m_capacity *= 2;
            }
            m_data = new T[m_capacity];
            std::memcpy(m_data, old, m_size);
            delete [] old;
        }
        m_data[m_size++] = value;
    }

    iterator begin()
    {
        return iterator(m_data);
    }

    iterator end()
    {
        return iterator(m_data + m_size);
    }

    size_type size() const
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

};

#endif // CUSTOMCONTAINER_H
