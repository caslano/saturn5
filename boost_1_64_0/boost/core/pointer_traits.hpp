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
Rfo+ZYX2bfQ04L9U+pZ9UxeAbfll4HNn1FGIo4mFOChATE8VBNyuWRhH/aj6v4/qf/4K3a+2sc/mBqa9KKY10rcD77twP3CHo59WKH+QWqjHx6hsQwxzDBWDfQIwiJPiyQ/79k3/Je3KA+MsqngqKIpYgZZIC4SStqE3zbZAVTzSZGmjbRKTtBatrsnuJl2TzS77bUIKiqiIihfihaIoKIe3iBfihTcqKB6IoCJeiIoHoCIK+Oab9838ZuZ96W79I2k6vzdv3rx5M9+b6w3k41guRq6Folzsx+D87RjgAXFt2uFbK/Cp16Cs+RKNbTCWF+ksqNrth1SPWWq3BUTT3dQYSV+lYAwe5nb6YKs/Rhbc+X+A4VDR5mNo3feFfHEIaTW6Y4y0FeaR52LzGTMKCvNhT4nt/jbS31WkP4JbepoaC4jbBmksyIEO08+UwXkiCVewr4sNWhnuOGz4eWO1TCOP1fOBRvQ5AWev1WljOGMGuuXYce06hhGVJ/NT3LhOIjZ3nQLbEuRCW5HqbKss5w9s5g6ymZ/x+Jnl8fPXlHbwIv1+SrYpO1InzyQ7qqX6K8lZNb+//Y5k6O3JdsUYu/5QJ8iLSrP4XZxf44aDX7b4Pb6b8yrM5MRvEec1yoY2/xPnVdMwzqtJoM3vQZpCEWhC3WCDmbP+Sf4K1q3BO66qneJwoFI7vQzaKezPVJB506AV5FRpvk85n9ONjhp9SzyWrzIZxkI6N5RNPn+Wfk4p/TxPjEln+ig5/dyefI42RuY4fzvXWCnKmNh52vlKBcXvzZBdPJ377dYk7hOlnZ6kNfVNJc5BG1yY2o+JWvymPrBKxaXLON24zc2XOu49mORFMwedL+b88F1FvuJ39b/ME7q23YPnfGZ/uL63WszFobVm3Fi8mq48Ml7KU6QhHYQAxweNG9OHdnuYy+c4fUYXCzmPYkUsNW9Bxzh+c16aDmqeFU9Pfr0isV6Wbt7qYO26UiuNK4eSKPX34gCiuXSR/l70NmlPGwN7uhzsyR1TiDr0iTgd9apkegzJdPMifYbjWWz3j6W0gxfTnr5KazRWrZYTTmxLY+SHU+dHmNP3AZ9A8mzvMW69qesT43R224Hf4oAfGTnqiPP1erEG53v59m/8reVPDNrqGqi31vECkuFpi/V++TbWeyulnU5pR6q0pnwHdYpc0vdnU8cclUPyHRaTDEPZbM9cvgOcdQ/609Gcn3HDwi9b8h3aOG+q78B5Jd/0OM5rBgfOh2VK/sDSJF/FlVe1x3LCLqP2WER025tqj1mlvUK49vT11PZI7nsE6xuA+fP3lav1+atOoutrRr74LqB4tkaUbxWVQ1uNMzQA5kuljHr42WCrV+PdRN0TTbw2xuCOpFrEb/gMEP3ww2m+nDe5csLbXiOT4/CoV+N3ougn5U7jzX5Z8v1BrjdiPdo91SDp2sezU43jdDlR5I94IlvnapSt19m/OpEwyBuDgGG5vU3rT4x1cvtxTb9Ny/zkGE2/ENvjKSz75r209TxcUaGW7b7zMTGmAxadQVeoK2Vn//3nT9K4uoSnCDgsiX2fbLWE5+iJVzu/fQbR7OhVd/tsuV06jY55ckhdZpzw7TY4v1nPBOjzZDUNyZwvRpEt71Sd7sRTaE3Ob2I9m9Q5nY4RdH53uG4n79fj2Tqmk2M3Q+hgll/0oUoz+zg/UCrYcraG+SMsZxXT9Qp0fizpdvD/gNa4tyQY0YixvPXVUl4D7BBp3BDY1N5p5UVQnrH1Z6/W9wBJmPVaXJt/22o8b8ihknNjzvtZvQsNDcpq+G83PML3SF6+0mDmHO4q4IsYNrJfz77VAW2wh9wv0dAHBPkMhDTBXvJzQho=
*/