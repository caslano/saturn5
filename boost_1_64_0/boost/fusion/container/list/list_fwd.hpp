/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_LIST_FORWARD_10262014_0528
#define FUSION_LIST_FORWARD_10262014_0528

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>

#if  defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_LIST)
#   undef BOOST_FUSION_HAS_VARIADIC_LIST
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
#   define BOOST_FUSION_HAS_VARIADIC_LIST
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/list/detail/cpp03/list_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    struct void_;

    template <typename ...T>
    struct list;
}}

#endif
#endif

/* list_fwd.hpp
SdNoZavD4vrI4MuwZD3BWRVCvoOxA3JEB0mSq7MqW0b7aUimsFWszHx/MCFLV+11w2kTf1r/q/tXMA3MUxiCWcougz73Ri2jVurGOZrUneQojbcEAlUwWfWGNJMJCHijdX5RjgsX3L+JuaYG4xmuNJTXQugfXiEJ71qzKkTJW9cO9sPMi0usDj1ImklNNxsD8Bk86rSHmSF9PpS3Wb7tooK58QV8/0uG4qioRPcr3+s0fPa01Dc4NQtx2hgSQ31iyy2LsSMB7hnFX8ZGf8rDAKP4MdSbveWXzrv69dWWBukeNDD0541nhAwlo+aV7oDRRWgvVBUf4fy1idH2Sg7yA3Ys4EXcu4rDAxqY0UnHnBOH2r3xJbcBT6s7s0dmZxsJ+s5y2UcRCqlYXkGQf/yo6u9DHtyCqh+2ABOk1x/t9ljoJOy8SXo7qDGIbRxMA3R4w9AwcsnEoqB485XWk1rVNj7CbJZRJo6EnGv7S5pFZ9jbQWpMzr3CGhQQlrZQ+Da/sJIvz22K5cwJTQjauO+dXPcSQ2WlsoHE7NlxXRN9JAHtwf//Y6U/HL+vOw==
*/