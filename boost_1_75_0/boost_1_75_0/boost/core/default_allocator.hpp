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
cTeq7i29gfsNcZ747UtS+3OFu5Ofr4ooG/q2/T3cg4hzPlfjx9R6lE1J3jhH81XoIsdncF8iGq+HP37hdmrqB0nz9myMX5+7eh76tThfUHFtwdxBrxeNe/G1NiH3h+8ahY4JzrPt6WncNOO96uh5Vw0dRiWVLcY9jbgOlVk3/7my8OTI2uO+pa/PvBSD+xxxL8iart7LZHOvjZ89LObwJyUfP4l2KO4F27bsolI/6WLcxlNui77cviAc90Oif+8e/3SVm+br2HnZSwK9RzVm4B5J9MmfOta/pufAtlFPh3a8fvuJkDW4bxLl54V/OiSOudwt6vl1nyrre0fX4V5KXNMN1nx9ZOSWZeMP998a/uyxa7Nx/Qp9ydfv93eR7f1j3D/buQXGbUjbgnsu0Tf7I6Xgmzlj98W88OaZPf07zO+H+zBxreV3nzrf53v6pWwrfPdq1LzTp3FvJq6P9GnTvepXxfbx+w5eqs0+OPl13K+J9v7VN76lsaN0qa+NOfRkm/Z2WtzDif7Mu0H2Q26+7Dx+xTiHvDNZA31wXyf6nWuj+3x18ubVcfUfXkmSFMzti3s9USd+6BrwufeApRO2e6blbfgjYDTu/8Ty3i5LWNY2WZP8asd2HyqOFL+Ne0LRD9/i3+v7xr01KUs+cS7d0q/t57hPFOevdj84mxr8fFzsIqlbgeeFHYtx7yjm0/hS8jK7m3fjXu3yem1k
*/