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
VkdC94fofdtu/UzOz7E5ZiGv29tv90nQVc8uiOhZf5zURRRpdrwdPd5YPcfdNN4mW+p0O6TMuzTdfKGr99V6xQ/3oKPWSxwkTAVSW/LrZaekTfFSovaQbuttdv9JFl3neWylmdSbj8ttfbIuwwjXqu2ZdEnbDJFft8XDEt3jxepap6QNG7qdPLIRc0a9UrCW1i1tirnBqBrx6uWzh0Hae6gLX8a3qIv4Qpd7v9F+m8UScR5e
*/