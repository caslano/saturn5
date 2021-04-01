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
ovyd3fhGJviKvTlonOl28Oq7XBk4YuO2wVekx3ti7OZAmM2dPbkhnlPVpYCl9ekFv1svzj1uOIWReSUT2eVYjjA2S1V/KWqQoPHJQiS2If8SBzUDL4UI7yhIjNoaopEkpBS1ITbPcc5/9ZfX1dfNV/zUQglPWmT8VvxuCmJLPaSRpNRU/AzD51EFQeWu0LziPBjGMyjtLqowEAobJzAn+8eNdmFv4DdiRSwdSxxR+dvqCefdnKo/1utHrKVbdgCFOIkeoIw9FvK/kmUUOx3SnoM+mi9Tx+AauWMFNeNAUfhFzO7OGrK5Yp/nigaeGOGgOmyCJ92YvsDbtuILodqTqFwitcSGIdov39oHo6hcDd0W3QsVflvJmECpqlZRfG4wAKusW3FtXeBLwkI3O8zTSRIc1tVY6mELd7jzResQfEDpL3VQTqw2O4Cfcs038ZKzG7rD7XH+mvmJA3u1RbuqgQ9XHzSsJ5sYr6mZ1IO/+OiYBAd5hbByEYRcrgr8e24AoW04aiIqjTldRwaYVstJ8GaGgzjgGUXMvGmcAmPOCf5t9H9PYtPz8MZKzg==
*/