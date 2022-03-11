/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_ALLOC_CONSTRUCT_HPP
#define BOOST_CORE_ALLOC_CONSTRUCT_HPP

#include <boost/core/noinit_adaptor.hpp>

namespace boost {

#if !defined(BOOST_NO_CXX11_ALLOCATOR)
template<class A, class T>
inline void
alloc_destroy(A& a, T* p)
{
    std::allocator_traits<A>::destroy(a, p);
}

template<class A, class T>
inline void
alloc_destroy_n(A& a, T* p, std::size_t n)
{
    while (n > 0) {
        std::allocator_traits<A>::destroy(a, p + --n);
    }
}
#else
template<class A, class T>
inline void
alloc_destroy(A&, T* p)
{
    p->~T();
}

template<class A, class T>
inline void
alloc_destroy_n(A&, T* p, std::size_t n)
{
    while (n > 0) {
        p[--n].~T();
    }
}
#endif

namespace detail {

template<class A, class T>
class alloc_destroyer {
public:
    alloc_destroyer(A& a, T* p) BOOST_NOEXCEPT
        : a_(a),
          p_(p),
          n_(0) { }

    ~alloc_destroyer() {
        boost::alloc_destroy_n(a_, p_, n_);
    }

    std::size_t& size() BOOST_NOEXCEPT {
        return n_;
    }

private:
    alloc_destroyer(const alloc_destroyer&);
    alloc_destroyer& operator=(const alloc_destroyer&);

    A& a_;
    T* p_;
    std::size_t n_;
};

} /* detail */

#if !defined(BOOST_NO_CXX11_ALLOCATOR)
template<class A, class T>
inline void
alloc_construct(A& a, T* p)
{
    std::allocator_traits<A>::construct(a, p);
}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
template<class A, class T, class U, class... V>
inline void
alloc_construct(A& a, T* p, U&& u, V&&... v)
{
    std::allocator_traits<A>::construct(a, p, std::forward<U>(u),
        std::forward<V>(v)...);
}
#else
template<class A, class T, class U>
inline void
alloc_construct(A& a, T* p, U&& u)
{
    std::allocator_traits<A>::construct(a, p, std::forward<U>(u));
}
#endif
#else
template<class A, class T, class U>
inline void
alloc_construct(A& a, T* p, const U& u)
{
    std::allocator_traits<A>::construct(a, p, u);
}

template<class A, class T, class U>
inline void
alloc_construct(A& a, T* p, U& u)
{
    std::allocator_traits<A>::construct(a, p, u);
}
#endif

template<class A, class T>
inline void
alloc_construct_n(A& a, T* p, std::size_t n)
{
    detail::alloc_destroyer<A, T> hold(a, p);
    for (std::size_t& i = hold.size(); i < n; ++i) {
        std::allocator_traits<A>::construct(a, p + i);
    }
    hold.size() = 0;
}

template<class A, class T>
inline void
alloc_construct_n(A& a, T* p, std::size_t n, const T* l, std::size_t m)
{
    detail::alloc_destroyer<A, T> hold(a, p);
    for (std::size_t& i = hold.size(); i < n; ++i) {
        std::allocator_traits<A>::construct(a, p + i, l[i % m]);
    }
    hold.size() = 0;
}

template<class A, class T, class I>
inline void
alloc_construct_n(A& a, T* p, std::size_t n, I b)
{
    detail::alloc_destroyer<A, T> hold(a, p);
    for (std::size_t& i = hold.size(); i < n; void(++i), void(++b)) {
        std::allocator_traits<A>::construct(a, p + i, *b);
    }
    hold.size() = 0;
}
#else
template<class A, class T>
inline void
alloc_construct(A&, T* p)
{
    ::new(static_cast<void*>(p)) T();
}

template<class A, class T>
inline void
alloc_construct(noinit_adaptor<A>&, T* p)
{
    ::new(static_cast<void*>(p)) T;
}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
template<class A, class T, class U, class... V>
inline void
alloc_construct(A&, T* p, U&& u, V&&... v)
{
    ::new(static_cast<void*>(p)) T(std::forward<U>(u), std::forward<V>(v)...);
}
#else
template<class A, class T, class U>
inline void
alloc_construct(A& a, T* p, U&& u)
{
    ::new(static_cast<void*>(p)) T(std::forward<U>(u));
}
#endif
#else
template<class A, class T, class U>
inline void
alloc_construct(A&, T* p, const U& u)
{
    ::new(static_cast<void*>(p)) T(u);
}

template<class A, class T, class U>
inline void
alloc_construct(A&, T* p, U& u)
{
    ::new(static_cast<void*>(p)) T(u);
}
#endif

template<class A, class T>
inline void
alloc_construct_n(A& a, T* p, std::size_t n)
{
    detail::alloc_destroyer<A, T> hold(a, p);
    for (std::size_t& i = hold.size(); i < n; ++i) {
        ::new(static_cast<void*>(p + i)) T();
    }
    hold.size() = 0;
}

template<class A, class T>
inline void
alloc_construct_n(noinit_adaptor<A>& a, T* p, std::size_t n)
{
    detail::alloc_destroyer<noinit_adaptor<A>, T> hold(a, p);
    for (std::size_t& i = hold.size(); i < n; ++i) {
        ::new(static_cast<void*>(p + i)) T;
    }
    hold.size() = 0;
}

template<class A, class T>
inline void
alloc_construct_n(A& a, T* p, std::size_t n, const T* l, std::size_t m)
{
    detail::alloc_destroyer<A, T> hold(a, p);
    for (std::size_t& i = hold.size(); i < n; ++i) {
        ::new(static_cast<void*>(p + i)) T(l[i % m]);
    }
    hold.size() = 0;
}

template<class A, class T, class I>
inline void
alloc_construct_n(A& a, T* p, std::size_t n, I b)
{
    detail::alloc_destroyer<A, T> hold(a, p);
    for (std::size_t& i = hold.size(); i < n; void(++i), void(++b)) {
        ::new(static_cast<void*>(p + i)) T(*b);
    }
    hold.size() = 0;
}
#endif

} /* boost */

#endif

/* alloc_construct.hpp
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
*/