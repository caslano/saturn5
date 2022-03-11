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
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
*/