/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_TUPLE_FORWARD_14122014_0051
#define FUSION_TUPLE_FORWARD_14122014_0051

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

#if  !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
#   undef BOOST_FUSION_HAS_VARIADIC_TUPLE
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
#   define BOOST_FUSION_HAS_VARIADIC_TUPLE
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
# include <boost/fusion/tuple/detail/tuple_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    template <typename ...T>
    struct tuple;
}}

#endif
#endif


/* tuple_fwd.hpp
ivvmErvJsuJlj5/99ZGotCKFFgl/3vU4uKQ5tEUCz7E9g7u7PpL05YsMg5COxscPp6Skm7ZZhSuM4WVEqDosFtPSP9r8vd1LQHMUnlng1V11bBxYzqcRmzDjTcD8yiK6gf0K1YfiORbz0u3HOP8oRKIrCLCz9vZoE41sZgYLvemWuWxjCbCEdXVkwTYMh/dER+L+vuJ6kplJ2J05qHo3dxHPjUW90EYi9lIFssnqGXy13twj3tsrXoqoIof+cJDiJaabqCYUvGQOGX7pVBiAfN2i/LTQ8WPGCMJ34KU0JMoCJW+sij+2o1On2gsF3Rq9yUdCM2d3QHzg69YTgbBNYg0KqZw1Eq66AspJ5LHheB3TEQ//CPbX8ys+ns93FqKZ5iyPC7HquLkOwAVAQ6T71LGIRoFmGCvxPHOW3LsleIgeJ+uX0zEYmkHh8OjrdtiCqHi2mdfhAqVRq4OIX5hLpl9kGEj9fSYXvjUnr46OHgokSuXZThQXaNnJ4v751rSashoJ0jaDJK3GJvEW+ed+5uwt2pasblCmUzoh8tmDkgYmZmd35J6h1nOEHw==
*/