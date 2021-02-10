/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_DEFAULT_ALLOCATOR_HPP
#define BOOST_CORE_DEFAULT_ALLOCATOR_HPP

#include <boost/config.hpp>
#include <new>
#include <climits>

#if defined(BOOST_LIBSTDCXX_VERSION) && BOOST_LIBSTDCXX_VERSION < 60000
#define BOOST_CORE_NO_CXX11_ALLOCATOR
#endif

namespace boost {

#if defined(BOOST_NO_EXCEPTIONS)
BOOST_NORETURN void throw_exception(const std::exception&);
#endif

namespace default_ {

struct true_type {
    typedef bool value_type;
    typedef true_type type;

    BOOST_STATIC_CONSTANT(bool, value = true);

    BOOST_CONSTEXPR operator bool() const BOOST_NOEXCEPT {
        return true;
    }

    BOOST_CONSTEXPR bool operator()() const BOOST_NOEXCEPT {
        return true;
    }
};

template<class T>
struct add_reference {
    typedef T& type;
};

template<>
struct add_reference<void> {
    typedef void type;
};

template<>
struct add_reference<const void> {
    typedef const void type;
};

template<class T>
struct default_allocator {
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef typename add_reference<T>::type reference;
    typedef typename add_reference<const T>::type const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef true_type propagate_on_container_move_assignment;
    typedef true_type is_always_equal;

    template<class U>
    struct rebind {
        typedef default_allocator<U> other;
    };

#if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
    default_allocator() = default;
#else
    BOOST_CONSTEXPR default_allocator() BOOST_NOEXCEPT { }
#endif

    template<class U>
    BOOST_CONSTEXPR default_allocator(const default_allocator<U>&)
        BOOST_NOEXCEPT { }

#if defined(PTRDIFF_MAX) && defined(SIZE_MAX)
    BOOST_CONSTEXPR std::size_t max_size() const BOOST_NOEXCEPT {
        return PTRDIFF_MAX < SIZE_MAX / sizeof(T)
            ? PTRDIFF_MAX : SIZE_MAX / sizeof(T);
    }
#else
    BOOST_CONSTEXPR std::size_t max_size() const BOOST_NOEXCEPT {
        return ~static_cast<std::size_t>(0) / sizeof(T);
    }
#endif

#if !defined(BOOST_NO_EXCEPTIONS)
    T* allocate(std::size_t n) {
        if (n > max_size()) {
            throw std::bad_alloc();
        }
        return static_cast<T*>(::operator new(sizeof(T) * n));
    }

    void deallocate(T* p, std::size_t) {
        ::operator delete(p);
    }
#else
    T* allocate(std::size_t n) {
        if (n > max_size()) {
            boost::throw_exception(std::bad_alloc());
        }
        void* p = ::operator new(sizeof(T) * n, std::nothrow);
        if (!p) {
            boost::throw_exception(std::bad_alloc());
        }
        return static_cast<T*>(p);
    }

    void deallocate(T* p, std::size_t) {
        ::operator delete(p, std::nothrow);
    }
#endif

#if defined(BOOST_NO_CXX11_ALLOCATOR) || defined(BOOST_CORE_NO_CXX11_ALLOCATOR)
    template<class U, class V>
    void construct(U* p, const V& v) {
        ::new(p) U(v);
    }

    template<class U>
    void destroy(U* p) {
        p->~U();
    }
#endif
};

template<class T, class U>
BOOST_CONSTEXPR inline bool
operator==(const default_allocator<T>&,
    const default_allocator<U>&) BOOST_NOEXCEPT
{
    return true;
}

template<class T, class U>
BOOST_CONSTEXPR inline bool
operator!=(const default_allocator<T>&,
    const default_allocator<U>&) BOOST_NOEXCEPT
{
    return false;
}

} /* default_ */

using default_::default_allocator;

} /* boost */

#endif

/* default_allocator.hpp
YdoojIZNdlHd/m6FBYMKzUqefQZ2w4TUpLCV7QGv+JZL8zjQzwFG4PA4oiA2YgArq0L3J/bAJwWUyvAOfuzwCxaN3+51/cZcNKYPyIITssFzktksTuf+Yhn60fTMD2dkO9acP4+ElmlsSZd00fZAC+pCP2xHh94BdpxbEspHEDftDaJtJagbO9TZz6iNmi4NVB8s5Y5a0eru1sjUdiN6Hj7S80UZl8EiPF3Pg2DRn6uLjHn8fmxFBrxpkEd24sa9f2C9qU8n/geCxZ6CBJEXQmL+x4R9QAgNbTfcoA7TPlX6ks5Q4M2DBOIZIwJbLR56lDGJbXE2HCrFcmoV+Na+bewg7QzRc6IOQGLuQXAcJL6dRNovFF4DA8UpXa44DQnOEd5xN/aCINXfQcM2Au+rGnV6yDO42UsYM37mvLZBe9lgjc3EClQU4rLpJhpvqAH0TpJO/VW0dGarKLIL80W8jKdxlDg+Ug5HeR+vFkQQB9CoTFXaWgWf/It5FDieLJxOBS2Zfn+mkUIKM0bhE8WYFvfgHwf+L6G08CSd+HBhNPwI4PcMGc89ZNZkhJG+6v6ovKMJN9mEeoS/HlDGa77tAiAhdorEy5xa01W4myGrOJNtPWz963iFsGf3L/0w8k/CKFyuHT/PO/ofeYfH
*/