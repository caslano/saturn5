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
8pTfoZ32uU8C9l343PnIQ8ckf7teYC8h2Gd0vor/LOwLgN37Pvi2tsvCviKwJxHsG9L23MMt7EbAHg26LuL3HaE7QHK/K3R3KH7tzoky/lO19HrMNp+Oxp4fdev3WAY2bhxNS3JojoUwcd5r82km87PlGftd+K0e3r/3eZuPV+++kA4+f9Qxqo0qbqkTzS98mgRrInTlb6x+3IpG/zAleM1B570PcjvRSNXK4H7DOLFFtJ2yA+l3B+PULxiq+3SyxHDe/nvQKbXN6kO4PzKP2fwe1vlOxiEKc874J8YhyZ+O/N7Sn5mmnt+XuUKG/4uHV+K5/V89fK1aN/eT/P5jNtb3lgum++Zsg2hiY/z3GB736AuIjOxTPEaeH9j3ejQN1vvqHj6XQR4AuHYL/72kf6s9Sb6s1E5f9z+N/PzwJbqdPBmJAVadtHzvvoR/F6LinAU9ADilIgr36j2lfM3b5+GqNaa3qOrmTMj3Yvhcmnq3HVdV7Ehfs43FjtuicfW4JfQGbsHmxd1LgrdxgbZ2P57xk7Uu7kcOubTyG/gPEpL045bJfHkGhyBdtm4U4T9JtnyQ4PHGibiXlX0McOaNV/QlgINTZzZLi66Rte+OqM0eJrrtTZtNmrhxYgZPKhpDdehHAoe79rU68XnUEjXm+VodHyBgx96V0fYBPjnbAAd77rVaw9Axy3OthsE8lu5k5YMTiSp6GX7rAatV9+X6ei3dKYDVsU0qkm8/ZondIyvnVt8jqXXscUv0mvp2rG1PkbXtCQJ7K8GGluj1bmYBYB2td2qWxnz2X1H7bxY75wuFUo32ocMOPFfiOsYZR1M8SKarzZmivFoGmS4NlopqUlKE9F3bFuGN5DnjrylIr21CIwgD3y5w9TwiTGrkPZl4qkiTK9uazBjhJAbbd8stDs2yH8ey+IdksQ9tG4VaDrNrJn8AcmO2SCOgxT2d+pCeQBLfSe4ftMVTSTO8rkEu4ysYW6d2gv+f4sx2tYOzH+sn/ZF5+oBj2E98u2NdqeDjsNSXDyzROd7TgD+9Ex/VDz9HZB/Fsp33EPVL0e6zhrxXedORlgYoM/bniN4wT9DmEtPGPWs7x8jTLwdG6JFNWJ8sG3r9KqB9E9DA01BKslmGKgOl9nwOdD0P9uxVftWZPWfAK2LPZceE+w16dxKzqFKyb3CvJHtbjG9zfkvS0vl2v8TBuXcMzhH+bON4O/estSzt2NbLyNYK59vbl+nb/HzY/MOw+fGgeWpnNldzMmLzE9nmwPk2V83wQQGyM36zU0EnPVNb3zZ4BSb/Fbh3R+Ecw0+ZNkKva2/svwJXJo3w0eby392kL3nAy4yDtNFD0NadmMyeqKbGviP34pFvTzSDTRxbAjKnLYGP2hLwqC0Bj9oS8KgtAY/aEnCxpWsvwDu2F5yoMBFb5weic/6zktsXMQOmjG3arGmIvHjtcOMx89YOITjbu3W0RqkEvjwRkbk5OsculliPyZU5pv3+VXBq1HOQWOS9no/fJwSGt31vF5sUVRwsV8i2b7T7GKCRK+lvfWychJbZY/uoQLoxVMvVn49jz825x5stX9XUMM7wb7W5ixlR3l9eGsHn8nVnb/02ovH5X2blM5reyrVtscNy8qrLLV+dGyonsP6Btj4e8yKp8lkY0yDNbDaK1X0V1v0KkTGrcrdiDpmbXWOuZJxY1nyHavuFyUv98nwB904msrViWRynJq2Th74n2/M29ILI/bk6y/lajNf7HXx8vK4hGn+8rqX9dGy8PkRtVcmJZHNMD8fDp/HGY5E3Xs0aGk8ixnn+v9eeeXAea85QlxE94I7Tdxo31LiH5w27o7HxOvJV5RCYis5+5+NL/DM=
*/