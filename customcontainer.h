#ifndef CUSTOMCONTAINER_H
#define CUSTOMCONTAINER_H

#include <memory>

template <class T, class A = std::allocator<T> >
class CustomContainer {
public:
    typedef A allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;

    class iterator {
    public:
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference reference;
        typedef typename A::pointer pointer;
        typedef std::random_access_iterator_tag iterator_category; //or another tag

        iterator();
        iterator(const iterator&);
        ~iterator();

        iterator& operator=(const iterator&);
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;

        iterator& operator++();

        reference operator*() const;
        pointer operator->() const;

    };

    class const_iterator {
    public:
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference reference;
        typedef typename A::pointer pointer;
        typedef std::random_access_iterator_tag iterator_category; //or another tag

        const_iterator ();
        const_iterator (const const_iterator&);
        const_iterator (const iterator&);
        ~const_iterator();

        const_iterator& operator=(const const_iterator&);
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;

        const_iterator& operator++();

        reference operator*() const;
        pointer operator->() const;
    };

    CustomContainer();
    CustomContainer(const CustomContainer &other);
    ~CustomContainer();

    CustomContainer& operator=(const CustomContainer&);
    bool operator==(const CustomContainer &) const;
    bool operator!=(const CustomContainer &) const;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    void push_back(const T&); //optional
    void push_back(T&&); //optional

    void swap(CustomContainer &);
    size_type size() const;
    size_type max_size() const;
    bool empty() const;

};

#endif // CUSTOMCONTAINER_H
