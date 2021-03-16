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
t/rirLjBKt+zuKMnhRICRU5nJru40EeC/FBYoDUuFjpFkIO26rfY6hNOIcSSqcx5si3ZfF7xQFLU2ITorwaQzOLJdh45cqPX6+SNhqUVekjEt9mHcANDHK+WclhcsdHqipZgeotp1GSwNe6tx/V7MNCkYL26wBRnGe0ytSKvB7oPi1O4wU/P/ghmFW4LJYN+XyJJT1DZmli2t4rvVBFk2gvP180y3UM1XZbb4+ANV9A+Vcg+ZBVfY3g4I3Mx8L4=
*/