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

template<class A, class T>
inline void
alloc_destroy(A& a, T* p)
{
    boost::allocator_destroy(a, p);
}

template<class A, class T>
inline void
alloc_destroy_n(A& a, T* p, std::size_t n)
{
    while (n > 0) {
        boost::allocator_destroy(a, p + --n);
    }
}

template<class A, class T>
inline void
alloc_destroy(noinit_adaptor<A>&, T* p)
{
    p->~T();
}

template<class A, class T>
inline void
alloc_destroy_n(noinit_adaptor<A>&, T* p, std::size_t n)
{
    while (n > 0) {
        p[--n].~T();
    }
}

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

template<class A, class T>
inline void
alloc_construct(A& a, T* p)
{
    boost::allocator_construct(a, p);
}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
template<class A, class T, class U, class... V>
inline void
alloc_construct(A& a, T* p, U&& u, V&&... v)
{
    boost::allocator_construct(a, p, std::forward<U>(u),
        std::forward<V>(v)...);
}
#else
template<class A, class T, class U>
inline void
alloc_construct(A& a, T* p, U&& u)
{
    boost::allocator_construct(a, p, std::forward<U>(u));
}
#endif
#else
template<class A, class T, class U>
inline void
alloc_construct(A& a, T* p, const U& u)
{
    boost::allocator_construct(a, p, u);
}

template<class A, class T, class U>
inline void
alloc_construct(A& a, T* p, U& u)
{
    boost::allocator_construct(a, p, u);
}
#endif

template<class A, class T>
inline void
alloc_construct_n(A& a, T* p, std::size_t n)
{
    detail::alloc_destroyer<A, T> hold(a, p);
    for (std::size_t& i = hold.size(); i < n; ++i) {
        boost::allocator_construct(a, p + i);
    }
    hold.size() = 0;
}

template<class A, class T>
inline void
alloc_construct_n(A& a, T* p, std::size_t n, const T* l, std::size_t m)
{
    detail::alloc_destroyer<A, T> hold(a, p);
    for (std::size_t& i = hold.size(); i < n; ++i) {
        boost::allocator_construct(a, p + i, l[i % m]);
    }
    hold.size() = 0;
}

template<class A, class T, class I>
inline void
alloc_construct_n(A& a, T* p, std::size_t n, I b)
{
    detail::alloc_destroyer<A, T> hold(a, p);
    for (std::size_t& i = hold.size(); i < n; void(++i), void(++b)) {
        boost::allocator_construct(a, p + i, *b);
    }
    hold.size() = 0;
}

template<class A, class T>
inline void
alloc_construct(noinit_adaptor<A>&, T* p)
{
    ::new(static_cast<void*>(p)) T;
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

} /* boost */

#endif

/* alloc_construct.hpp
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
*/