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
BUDtEzCAQhIIgOrBzy+fu8TPlUec4QccCIvvSHv8bH2kIfjpdc0ZfiY/XS9+unzuDj9PP+IMPwVahp8fQzB+VjYCP69r7gk/3i7w01lTFz8Dk93hx9sVfh57mOFnT1BD8PPllfrxc1rC+DkqOcXPW2tc4ue7Ls7wA964pTTZHj8zujQEP3cuO8NPV6le/Fz8zB1+/Ls4w09SEMPPrFYYP7WNwE+fpveEnxYu8FMZWBc/mmHu8NPCFX6u/YfhJz+wIfiZUF0/flb0w/hZ1s8pfp751CV+Xv2PM/yAo2yZP8wePzH/aQh+frzkDD+X4jl+8JrPcBq3kODHZ9VqFrcAb/Endi/bdHM7w4w+DV0WdSQOeyyELil4W0DTgC44dJl4Cocu15eQ0CXW4hVGQpdYmy66M+V5rEUXAKEL0IfgmQL9mvCQCM8UcJVs2FVSYj3kKpUaIspdukpZyFPRb/dFJaLv2x6lU2VNhu+hd6DUIkfGk4QXsZb1L/jiybgJ6A64ZqgnkTBgoXQ49AoPXpvHtFVhlzwW71BSoxotyyf6QohFujHAX63Sm+564sZrPBjy0wVkxjpBfrqCfB+O/PMeBPnp2f4Y79ZVeJEM88AgH7G0GWwH+rC6oPcRQK9Z8AEsR5ruNtHkReJ9XIgKXZ9HdVQ063dW2woQg4pDCYMkuJ1h0y14mOzBSvMg3MqA+5JlaDs1iRpINDRoEJ7y
*/