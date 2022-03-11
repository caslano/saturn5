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