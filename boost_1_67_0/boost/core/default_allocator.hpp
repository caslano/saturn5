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
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
*/