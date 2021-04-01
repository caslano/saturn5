/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_NOINIT_ADAPTOR_HPP
#define BOOST_CORE_NOINIT_ADAPTOR_HPP

#include <boost/config.hpp>
#if !defined(BOOST_NO_CXX11_ALLOCATOR)
#include <memory>
#endif
#include <new>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

namespace boost {

template<class A>
struct noinit_adaptor
    : A {
    template<class U>
    struct rebind {
#if !defined(BOOST_NO_CXX11_ALLOCATOR)
        typedef noinit_adaptor<typename std::allocator_traits<A>::template
            rebind_alloc<U> > other;
#else
        typedef noinit_adaptor<typename A::template rebind<U>::other> other;
#endif
    };

    noinit_adaptor()
        : A() { }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template<class U>
    noinit_adaptor(U&& u) BOOST_NOEXCEPT
        : A(std::forward<U>(u)) { }
#else
    template<class U>
    noinit_adaptor(const U& u) BOOST_NOEXCEPT
        : A(u) { }
#endif

    template<class U>
    noinit_adaptor(const noinit_adaptor<U>& u) BOOST_NOEXCEPT
        : A(static_cast<const U&>(u)) { }

    template<class U>
    void construct(U* p) {
        ::new((void*)p) U;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<class U, class V, class... Args>
    void construct(U* p, V&& v, Args&&... args) {
        ::new((void*)p) U(std::forward<V>(v), std::forward<Args>(args)...);
    }
#else
    template<class U, class V>
    void construct(U* p, V&& v) {
        ::new((void*)p) U(std::forward<V>(v));
    }
#endif
#else
    template<class U, class V>
    void construct(U* p, const V& v) {
        ::new((void*)p) U(v);
    }

    template<class U, class V>
    void construct(U* p, V& v) {
        ::new((void*)p) U(v);
    }
#endif

    template<class U>
    void destroy(U* p) {
        p->~U();
    }
};

template<class T, class U>
inline bool
operator==(const noinit_adaptor<T>& lhs,
    const noinit_adaptor<U>& rhs) BOOST_NOEXCEPT
{
    return static_cast<const T&>(lhs) == static_cast<const U&>(rhs);
}

template<class T, class U>
inline bool
operator!=(const noinit_adaptor<T>& lhs,
    const noinit_adaptor<U>& rhs) BOOST_NOEXCEPT
{
    return !(lhs == rhs);
}

template<class A>
inline noinit_adaptor<A>
noinit_adapt(const A& a) BOOST_NOEXCEPT
{
    return noinit_adaptor<A>(a);
}

} /* boost */

#endif

/* noinit_adaptor.hpp
j1u2uj4IGq+9NcGFXI1GiIVENbZEv5cznIF22wlNaG3fwW5zGHp7bASaKSwIYj4Bwn/c0uAgOcZ1tGn5wmVBvIGMd/ekkjOKsGEFqAs1B2B3SGqhhv06UU1BGAegl35D3C5oSGZE5d8qP/egegx/9XuSn/Uq/4KsW6JyCon6/ZE/8FvUuqvGQAqGdJAvFLoBqNd2E8tZCk+omvMjTXYtd5K81JM3AK9mnX1bx5jQhM4w6JZeNSR/z83gy6UNOnTttyb8Rs/pLQjQagID7Niz7DaaKjv6CPKylBSOz1zJH91KDSGvfzMDR+ZbH+TT+o6u7Q5z1bZPJpA44bagnd2qbPnENSFftjZuDD7TpsFE6LGiZXBFdQYo1IHP6vwwS7la0UnL7x0DVQOF2TmnvvH8G9ESZ6HPjcl0woFhjp93RAPAcTQToMwpPD9nxg4sAOEmp7v0nS4l/djWthg/5CZa6fAjvkbBGM/oBIkI08NH1fX7i+ofbaFSVL2rDtaD1jTXYvfFL2/DasN2EkP4Hvs61URyaBD4rB7RWJcrtO9I0louHgNz6UvAAdqCGQ==
*/