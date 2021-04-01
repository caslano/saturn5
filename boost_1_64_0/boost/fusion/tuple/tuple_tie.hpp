/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_TUPLE_TIE_14122014_0115
#define FUSION_TUPLE_TIE_14122014_0115

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/tuple/tuple_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
# include <boost/fusion/tuple/detail/tuple_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/tuple/tuple.hpp>

namespace boost { namespace fusion
{
    template <typename ...T>
    BOOST_FUSION_GPU_ENABLED
    inline tuple<T&...>
    tie(T&... arg)
    {
        return tuple<T&...>(arg...);
    }
}}

#endif
#endif


/* tuple_tie.hpp
P9tGh+K4w9CAMOjdYIZow2vJcNc2c+Z20Ja7UE2NoJPsHeXynGjBJhM9ZmVER1JT5vIX3CJB7XLaG88C5uYcxYV0LKGmgLaRc0f/OqSUQsc1uK65lbTNsyagMoxdg6m5LyebiVZVv+lrXa9riNvv428KvFR+8F9ZBJm52oIM3+OesvrXRC6c3ElMxuAA0jKesFyWBulJKaGLcVs1nV9S0iQW1rlPwrZd/56Lu9cpvdWtrePd3v5cU2OiNzUnLy4EqoRdNLCBABIbZ2e2ebnUjMSPOVeMegfNKSOmV0G3yrvXpPRXXDFhgd8Rr3l8ZQdVGx7dsl29WLoCP4Q2HaMZ2GCQDnmHjfOpEXoQREeryshZ97GuuEE5WiP55lJgbW0nWZDNjLX+ysdL9y7wFQyRUPkTWSVeRlkWpARD2OVWwx3B/J0IqkXcAmGKR0FPYKvQwSoiOPDJsGS6AfRDUEKcpBwv2HOenM2AS4mzjFFLX0UPpcwFfo3TrGTmB/vl2ZCxyF28Q/ae8l+ZZE9LYp/PveAbUKFXA/ObIQanCeZP2UNxdj9CBn1HjEdcLw==
*/