//#include "customallocator.h"

//template <typename T>
//template <typename U>
//CustomAllocator<T>::CustomAllocator(const CustomAllocator<U>&)
//{
//    // should we make a copy of the rhs.m_buffer ?
//    // No, we should not!
//}

//template <typename T>
//T* CustomAllocator<T>::allocate(std::size_t n)
//{
//    std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
//    auto p = std::malloc(n * sizeof(T));
//    if (!p) {
//        throw std::bad_alloc();
//    }
//    return reinterpret_cast<T *>(p);
//}

//template <typename T>
//void CustomAllocator<T>::deallocate(T* p, std::size_t n)
//{
//    std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
//    std::free(p);
//}

//template <typename T>
//template<typename U, typename ...Args>
//void CustomAllocator<T>::construct(U *p, Args &&...args)
//{
//    std::cout << __PRETTY_FUNCTION__ << std::endl;
//    new(p) U(std::forward<Args>(args)...);
//}


//template<typename T>
//void CustomAllocator<T>::destroy(T *p)
//{
//    std::cout << __PRETTY_FUNCTION__ << std::endl;
//    p->~T();
//}

//template <class T, class U>
//constexpr bool operator== (const CustomAllocator<T>&, const CustomAllocator<U>&) noexcept
//{
//    return false;
//}

//template <class T, class U>
//constexpr bool operator!= (const CustomAllocator<T>&, const CustomAllocator<U>&) noexcept
//{
//    return false;
//}

//template class CustomAllocator<int>;
//template void CustomAllocator<int>::construct<int, int const &>(int *, int const &);
//template void CustomAllocator<int>::construct<int, int>(int *, int &&);

//using type1 = std::pair<int, int>;
//template class CustomAllocator<type1>;
//template void CustomAllocator<type1>::construct<type1, type1 const &>(type1 *, type1 const &);
//template void CustomAllocator<type1>::construct<type1, type1>(type1 *, type1 &&);
