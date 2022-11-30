/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_LIST_MAIN_10262014_0447
#define FUSION_LIST_MAIN_10262014_0447

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/list_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/list/detail/cpp03/list_to_cons.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/support/detail/access.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename ...T>
    struct list_to_cons;

    template <>
    struct list_to_cons<>
    {
        typedef nil_ type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call() { return type(); }
    };

    template <typename Head, typename ...Tail>
    struct list_to_cons<Head, Tail...>
    {
        typedef Head head_type;
        typedef list_to_cons<Tail...> tail_list_to_cons;
        typedef typename tail_list_to_cons::type tail_type;

        typedef cons<head_type, tail_type> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(typename detail::call_param<Head>::type _h,
             typename detail::call_param<Tail>::type ..._t)
        {
            return type(_h, tail_list_to_cons::call(_t...));
        }
    };
}}}

#endif
#endif

/* list_to_cons.hpp
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
*/