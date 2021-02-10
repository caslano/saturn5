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
n8MpWbFlF35wHL1OuM8D4FG2hD8cMM73hxej+az32ww60G6UFz/1uue9ybw/bBg2OYBDOGjtEcCtaViBox2B8+6sW+gbgTf7BHJ9I/B2R2A6HZRQUOAfjwkYFBT4545Ab3ju3INJt4iCmHJw4jgi0jaN8yKNLmnAQYiHQnLKw4NPBQPoz36xkKVw4DPN9j5W4nc+1+ay9/ltLHw4wCOfJjqto6vklxfjbu6WTNXj/ZW410T+qcaPpqiQznvTs0l/TLrOmOFJYpDEmC064zHRZLopPKSDyKOizam0INAl0/iFSCBJY22y5eCjOzzai/gW2cC5Dvp7vXXf1K+DMZJvIpmHjEUYSmN8LPXzqi9sEin6aJdHZbTPvcnH0bSX4yC3IPHzIMC22rS8s/E9J3hlYR3a1hQdN9Eg56uEeyIQ29aBRigQgmXpTbbkUQG58WiZKe2kXCNJQtv2BtSiQiAtm0XDnIu1gbSFgu1FKbuuK3Bf+oOBMxzNYMEhyqR8TfwqIoYgDUC2hDshJT3kK+ZpuS6YF21ScRlPidBxR6xBp/ykiMFxcj/ziis/pASabcwLAMsOjeoQdvePDqDNOeJ1N62vemBumcy4Onaa/XGVeIwHlCa7YZuNYBJbygpdrGhsWKmiFnJGbchF3re3
*/