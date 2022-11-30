/*
Copyright 2017-2021 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_POINTER_TRAITS_HPP
#define BOOST_CORE_POINTER_TRAITS_HPP

#include <boost/config.hpp>
#include <boost/core/addressof.hpp>
#include <cstddef>

namespace boost {
namespace detail {

struct ptr_none { };

template<class>
struct ptr_valid {
    typedef void type;
};

template<class>
struct ptr_first {
    typedef ptr_none type;
};

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
template<template<class, class...> class T, class U, class... Args>
struct ptr_first<T<U, Args...> > {
    typedef U type;
};
#else
template<template<class> class T, class U>
struct ptr_first<T<U> > {
    typedef U type;
};

template<template<class, class> class T, class U1, class U2>
struct ptr_first<T<U1, U2> > {
    typedef U1 type;
};

template<template<class, class, class> class T, class U1, class U2, class U3>
struct ptr_first<T<U1, U2, U3> > {
    typedef U1 type;
};
#endif

template<class T, class = void>
struct ptr_element {
    typedef typename ptr_first<T>::type type;
};

template<class T>
struct ptr_element<T, typename ptr_valid<typename T::element_type>::type> {
    typedef typename T::element_type type;
};

template<class, class = void>
struct ptr_difference {
    typedef std::ptrdiff_t type;
};

template<class T>
struct ptr_difference<T,
    typename ptr_valid<typename T::difference_type>::type> {
    typedef typename T::difference_type type;
};

template<class, class>
struct ptr_transform { };

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
template<template<class, class...> class T, class U, class... Args, class V>
struct ptr_transform<T<U, Args...>, V> {
    typedef T<V, Args...> type;
};
#else
template<template<class> class T, class U, class V>
struct ptr_transform<T<U>, V> {
    typedef T<V> type;
};

template<template<class, class> class T, class U1, class U2, class V>
struct ptr_transform<T<U1, U2>, V> {
    typedef T<V, U2> type;
};

template<template<class, class, class> class T,
    class U1, class U2, class U3, class V>
struct ptr_transform<T<U1, U2, U3>, V> {
    typedef T<V, U2, U3> type;
};
#endif

template<class T, class U, class = void>
struct ptr_rebind
    : ptr_transform<T, U> { };

template<class T, class U>
struct ptr_rebind<T, U,
    typename ptr_valid<typename T::template rebind<U> >::type> {
    typedef typename T::template rebind<U> type;
};

#if !defined(BOOST_NO_CXX11_DECLTYPE_N3276)
template<class T, class E>
class ptr_to_expr {
    template<class>
    struct result {
        char x, y;
    };

    static E& source();

    template<class O>
    static auto check(int) -> result<decltype(O::pointer_to(source()))>;

    template<class>
    static char check(long);

public:
    BOOST_STATIC_CONSTEXPR bool value = sizeof(check<T>(0)) > 1;
};

template<class T, class E>
struct ptr_to_expr<T*, E> {
    BOOST_STATIC_CONSTEXPR bool value = true;
};

template<class T, class E>
struct ptr_has_to {
    BOOST_STATIC_CONSTEXPR bool value = ptr_to_expr<T, E>::value;
};
#else
template<class, class>
struct ptr_has_to {
    BOOST_STATIC_CONSTEXPR bool value = true;
};
#endif

template<class T>
struct ptr_has_to<T, void> {
    BOOST_STATIC_CONSTEXPR bool value = false;
};

template<class T>
struct ptr_has_to<T, const void> {
    BOOST_STATIC_CONSTEXPR bool value = false;
};

template<class T>
struct ptr_has_to<T, volatile void> {
    BOOST_STATIC_CONSTEXPR bool value = false;
};

template<class T>
struct ptr_has_to<T, const volatile void> {
    BOOST_STATIC_CONSTEXPR bool value = false;
};

template<class T, class E, bool = ptr_has_to<T, E>::value>
struct ptr_to { };

template<class T, class E>
struct ptr_to<T, E, true> {
    static T pointer_to(E& v) {
        return T::pointer_to(v);
    }
};

template<class T>
struct ptr_to<T*, T, true> {
    static T* pointer_to(T& v) BOOST_NOEXCEPT {
        return boost::addressof(v);
    }
};

template<class T, class E>
struct ptr_traits
    : ptr_to<T, E> {
    typedef T pointer;
    typedef E element_type;
    typedef typename ptr_difference<T>::type difference_type;

    template<class U>
    struct rebind_to
        : ptr_rebind<T, U> { };

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
    template<class U>
    using rebind = typename rebind_to<U>::type;
#endif
};

template<class T>
struct ptr_traits<T, ptr_none> { };

} /* detail */

template<class T>
struct pointer_traits
    : detail::ptr_traits<T, typename detail::ptr_element<T>::type> { };

template<class T>
struct pointer_traits<T*>
    : detail::ptr_to<T*, T> {
    typedef T* pointer;
    typedef T element_type;
    typedef std::ptrdiff_t difference_type;

    template<class U>
    struct rebind_to {
        typedef U* type;
    };

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
    template<class U>
    using rebind = typename rebind_to<U>::type*;
#endif
};

template<class T>
BOOST_CONSTEXPR inline T*
to_address(T* v) BOOST_NOEXCEPT
{
    return v;
}

#if !defined(BOOST_NO_CXX14_RETURN_TYPE_DEDUCTION)
namespace detail {

template<class T>
inline T*
ptr_address(T* v, int) BOOST_NOEXCEPT
{
    return v;
}

template<class T>
inline auto
ptr_address(const T& v, int) BOOST_NOEXCEPT
-> decltype(boost::pointer_traits<T>::to_address(v))
{
    return boost::pointer_traits<T>::to_address(v);
}

template<class T>
inline auto
ptr_address(const T& v, long) BOOST_NOEXCEPT
{
    return boost::detail::ptr_address(v.operator->(), 0);
}

} /* detail */

template<class T>
inline auto
to_address(const T& v) BOOST_NOEXCEPT
{
    return boost::detail::ptr_address(v, 0);
}
#else
template<class T>
inline typename pointer_traits<T>::element_type*
to_address(const T& v) BOOST_NOEXCEPT
{
    return boost::to_address(v.operator->());
}
#endif

} /* boost */

#endif

/* pointer_traits.hpp
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
*/