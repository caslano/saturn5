/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR_TIE_11112014_2302
#define FUSION_VECTOR_TIE_11112014_2302

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/generation/detail/pp_vector_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct vector_tie
        {
            typedef vector<T&...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T&...>
    vector_tie(T&... arg)
    {
        return vector<T&...>(arg...);
    }
 }}


#endif
#endif


/* vector_tie.hpp
gtYP6W/0O1bvb6r0OWoXuI8V+pqoOpb82miCWiMHubLw/uD6z9xibpFp121t112/0fQ+pJp3HMfv+FLefIqDv2kWi7tT3b/b7netr6ZOrZTr9Sm3qm71Hf8nN0fo5ClF81RTylr7+pC0a7kHl3GFskyva8nvKo1kDtKFurijvCyDX1dD3wFN3a/1gOikdS3bHYGy1f6Yt8nxRVNGlxZkF7v2ycaP6cfmJJI+ZG/8ib27Pyn+
*/