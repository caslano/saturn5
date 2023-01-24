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
+gL3IiE8fPu+wdfaOKa8smLxjx3bt43C/UlYxd/trry84svwyH0ZN76uvP5Z/3t8fIcmfHrw+f/+Wv2t2G9fip0/zW1+3vWHudn21vpdiN+Jjx/5fq8B2thT7Z8aQnaRCQcn4j4o1HFRw8Le3HPlSOLhrYE9Z6UHLZ3Dt0nwO1f1Xb4dGL18Xy/pq3eT3QP5fH6adLv/3QyXxIbA0GvLY/dfwH1USOuPC0nxnT95KXbR8tDP++pPHMO9VUxe8l684NtDFvXisS9m7r+x7r19PPytyInlQ02n2tcOBn4KXB748m285twPv/stOpZwyGv+5f7hl5/CfVloH3b2/u3wvcYvEt8gJzvcOEccL/Hxx2U/uGgvuRC94tM1nVyvr43C/Vu4bhtxtPvX+zM/ab9yOjmSWjo0HvUl7uvIy81pK6lbmNSgT//UY4bnItzfhWuw7qNfUX2T8lzi3skrvNptDl6Oe75QH8zvvvbB0R9uxO7pYnhl8b/P/Yr7wHANfXjO9tX7Ai7HNnQd+c9+86ZIH/KO8uY1xUM+mft18hZ399ufODm8iPvFmFxl/Hbk7rBnIl8Jfvqr+UWhF4/z8LYLl578su8HMW8GfBCW987hDbivrADymZ88X62zuzF+V0p0zupndh3HvWa4Nhnmkb1amfZx0ksbJv3q9fUbLrj/DNfhui+f3nb0wGkT1vQtnfx62ulRuCcN819279tO
*/