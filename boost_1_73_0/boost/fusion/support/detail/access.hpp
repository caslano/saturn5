/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ACCESS_04182005_0737)
#define FUSION_ACCESS_04182005_0737

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename T>
    struct ref_result
    {
        typedef typename add_reference<T>::type type;
    };

    template <typename T>
    struct cref_result
    {
        typedef typename
            add_reference<
                typename add_const<T>::type
            >::type
        type;
    };

    template <typename T>
    struct call_param
    {
        typedef T const& type;
    };

    template <typename T>
    struct call_param<T&>
    {
        typedef T& type;
    };

    template <typename T>
    struct call_param<T const>
    {
        typedef T const& type;
    };

    template <typename T>
    struct call_param<T volatile>
    {
        typedef T const& type;
    };

    template <typename T>
    struct call_param<T const volatile>
    {
        typedef T const& type;
    };

}}}

#endif


/* access.hpp
nmQj92eakKRfaaR3MB13sgq2CFxF+l4jvZ1VpnanmsqYEqLjgCGT6cQM1sA5ZdRIOkuP7rabk5hnSlxNus9Ip/z2NHdP+pp3UzmHDLljbdl7dqvA5aS/QNJZBR3tPm6mPoa0BtKyzmvKbqB0tzXqOo/ZbTt6nFFJ8mX3+5pJr0s1Blj6p1NiR7uRp+dYqlNbXG9k0e14uaRnB9KUmailvdpsj2amTlvanUYaQ+SJjWx6mQMb
*/