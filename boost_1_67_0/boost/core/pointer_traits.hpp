/*
Copyright 2017-2018 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_POINTER_TRAITS_HPP
#define BOOST_CORE_POINTER_TRAITS_HPP

#include <boost/config.hpp>
#if !defined(BOOST_NO_CXX11_POINTER_TRAITS)
#include <memory>
#else
#include <boost/core/addressof.hpp>
#include <cstddef>
#endif

namespace boost {

#if !defined(BOOST_NO_CXX11_POINTER_TRAITS)
template<class T>
struct pointer_traits
    : std::pointer_traits<T> {
    template<class U>
    struct rebind_to {
        typedef typename std::pointer_traits<T>::template rebind<U> type;
    };
};

template<class T>
struct pointer_traits<T*>
    : std::pointer_traits<T*> {
    template<class U>
    struct rebind_to {
        typedef U* type;
    };
};
#else
namespace detail {

template<class>
struct ptr_void {
    typedef void type;
};

template<class T>
struct ptr_first;

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
struct ptr_element<T, typename ptr_void<typename T::element_type>::type> {
    typedef typename T::element_type type;
};

template<class, class = void>
struct ptr_difference {
    typedef std::ptrdiff_t type;
};

template<class T>
struct ptr_difference<T,
    typename ptr_void<typename T::difference_type>::type> {
    typedef typename T::difference_type type;
};

template<class T, class V>
struct ptr_transform;

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
struct ptr_rebind {
    typedef typename ptr_transform<T, U>::type type;
};

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
template<class T, class U>
struct ptr_rebind<T, U,
    typename ptr_void<typename T::template rebind<U> >::type> {
    typedef typename T::template rebind<U> type;
};
#endif

template<class T>
struct ptr_value {
    typedef T type;
};

template<>
struct ptr_value<void> {
    typedef struct { } type;
};

} /* detail */

template<class T>
struct pointer_traits {
    typedef T pointer;
    typedef typename detail::ptr_element<T>::type element_type;
    typedef typename detail::ptr_difference<T>::type difference_type;
    template<class U>
    struct rebind_to {
        typedef typename detail::ptr_rebind<T, U>::type type;
    };
#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
    template<class U>
    using rebind = typename detail::ptr_rebind<T, U>::type;
#endif
    static pointer
    pointer_to(typename detail::ptr_value<element_type>::type& v) {
        return pointer::pointer_to(v);
    }
};

template<class T>
struct pointer_traits<T*> {
    typedef T* pointer;
    typedef T element_type;
    typedef std::ptrdiff_t difference_type;
    template<class U>
    struct rebind_to {
        typedef U* type;
    };
#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
    template<class U>
    using rebind = U*;
#endif
    static T*
    pointer_to(typename detail::ptr_value<T>::type& v) BOOST_NOEXCEPT {
        return boost::addressof(v);
    }
};
#endif

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