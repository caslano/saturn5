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

namespace boost {

#if defined(BOOST_NO_EXCEPTIONS)
BOOST_NORETURN void throw_exception(const std::exception&);
#endif

namespace default_ {

template<bool V>
struct bool_constant {
    typedef bool value_type;
    typedef bool_constant type;

    static const bool value = V;

    operator bool() const BOOST_NOEXCEPT {
        return V;
    }

    bool operator()() const BOOST_NOEXCEPT {
        return V;
    }
};

template<bool V>
const bool bool_constant<V>::value;

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
    typedef bool_constant<true> propagate_on_container_move_assignment;
    typedef bool_constant<true> is_always_equal;

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

    BOOST_CONSTEXPR std::size_t max_size() const BOOST_NOEXCEPT {
        return static_cast<std::size_t>(-1) / (2 < sizeof(T) ? sizeof(T) : 2);
    }

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

#if defined(BOOST_NO_CXX11_ALLOCATOR)
    T* allocate(std::size_t n, const void*) {
        return allocate(n);
    }
#endif

#if (defined(BOOST_LIBSTDCXX_VERSION) && BOOST_LIBSTDCXX_VERSION < 60000) || \
    defined(BOOST_NO_CXX11_ALLOCATOR)
    template<class U, class V>
    void construct(U* p, const V& v) {
        ::new(p) U(v);
    }

    template<class U>
    void destroy(U* p) {
        p->~U();
        (void)p;
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