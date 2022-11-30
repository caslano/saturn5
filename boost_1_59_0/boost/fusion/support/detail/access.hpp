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
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
*/