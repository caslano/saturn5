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
sLZ4l4Y11WMPHl0zaU4EMDT2YSCzMfQKwKDUPrwHnK/Q2fO7NRzNzRvhPg58QtyHj1Y4TA1syQrYklVrbd4b17ZJwr3rUHRc3qt1KJb3Wh2W0fc/6Kf5nFkRMP59uu1scybevw9YPKb4RH5NV2vcelqnPmhxs9UKaiGBvFDWh8SWZ9VZVhy3nnAfMTjLU/nlx8QvfwGamsTXzwL2FsCOULB2c2E1HvB6nNFEcuGxRbFa0he1f23YOjyyEe/FqMoP9sD2PtqX43gnl/xqSuP+vv0NKQw2LcKGVCf6hsdP4oHJX2508XJ8oaMuj8G3PTqkJWbOfEfjnDuzN2lYHRNGXxclG9wMXPoYaCXVt6x6mECnSF8w5WxfvufqIHk83Zd38fa1zTnsX9bmNzx+EsVDD6pD3+rTJKa8oj+kI9qrj4x8f2jIy843hrcd79PCpTESJaFb1kK+Wn6Zz5j/nZZOCg3diS3sifXc7QjFup+ntGRS3lfLeyiEM/b8pSuDiFr3p1lJNQWPFv0RirbrCOk8TW+hR+ZpdVGs7vcr29/6ZKF/Te8p6Su5JVy27V/TDt3J69ZDvxZ0q9f2r8v4rV29rqsNuv7eNevboVvde3J/O3TQtC256/rWrGmHbn3fKf1ZXR40NyKWPlrlZAL7s8C2EOzvAnswwf4psEcoWEc5A761DNbFcxbF9rf/1n1QeVSJ1/OupSl8Bx6RzL4aNevT4Ro3Nj4wuEV/Txnj55453o3ayK/gGtw9SJagDL97apx802fh96Y2QJjYfx9Db881ffn0rYQvn+7L+Pz894/8/uoPbzkW3I9lyjfHRzl5jxanxvq4pXod/g9wSUdrbrFUi35HdWF0ze1eKj5bKdWxuGmHJfzxGo/X9QY36Oe8Z4ocw5bF2mNJYB/o0TRYChTW+sAKF45WNq492MNNYi+l7oux7JUtaBSj9udGMXL/5HXWVh3NM6STwTx7QzQ3f6TWHQ2sD6/SsJlkujwJf/Th9RTekT4otQT6vMX1g+g9wBFzDVD5Yr/44l2g29eZ/P01yP+L0PecNLzxVE1fbdYLJa9pgI5zLlcKM81iaR7qeckmmuWZohCftDfp7+072eD2r1tzUjKN5KJ4ksQ6oRAdetrStOs+C7J+b8w+Mdk5hgeEd+zAar4F0I1j23OnDY+s7se/8eTyhp2bLaks52MEGdme23jGyMC24cGc/vlwwu0YHsT/0+AxPLz42F0roCLraJQs4pMMr+Nt9HwXbnju2lWqTOFydnJSX65v1worfl6BxhaHIhloJey01T0n7Stibe7tOWlzov7YhP8O9JxUqaKqXyVjjJ0xZuya/p1LXz4eGNmY24Z/ALo1N4R8Kv1nbjD9kdLBnaNDqYWHduDVyoFxZVy8ozm4feOQIjL/3Lax56TtYPzUcs9JBe0IxdLeXaLrUwZ3jePFgWTXtjH8s2/Nqr7eVf1rFWZgfOu2TYPKLY0tlH92wMF69IrBU3ftqFfVkVzPJhyEJD0P279+3cN3nYbdVnVf0rMFu9ZdeD1o0+ljG7fsWrNq3aq+rPWu5uyKdjn09ZpWUKJ3Vd/a3nWrV/XuahbqjUNnsmb1KYqJHmvEprshNuEbQ0Sjy2CVd+C/y/HfO/HfGxA33oW//29Z/0+fhQWef0k7PY5pdnqQJ79dYuoVizjGr9FxG0HQxvhTj87WrGqxSLTrNC3248G+ArQoQ6jFN+SN/axdM9cv5b1hWkPIaheG5/XO/tGtM9zg4lCAwTeOrdvpXUMjzRdi/asAbr9N1bpt2z5iH1vIcI/xcKqni9x+ViqQzHnY4zS8UU1VmarOluoHODd4wlLe8xMR6TSQ0ugfOlLqhvw=
*/