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
g2eQ1Tih83MVjK5b9+9kRBmIHt99Ylm7gEQu9RR4jdLutEw5GJctcMcBp6WeaER4lozR0790Q9PQyfGK5l+YoT5EKWToLT2TUq8MNrA2rGimMo15Yw6QRIYmJPfWkR6mo++Hq3aqYh/z+IzuXiSszdC5JMrbiCqsG+yVOBnZpEJShMZQVCsDuF9jJ6R3KVuTyr/3NmM0Txxt+4AU5CtM0FuttEb+LaagLHAx28F2hIcc7M8+3dIb/NP7S03g7e53JQsoSSE8VW3sUKNn3w4O6KwY7sQdJhD5VDnoifTP0TiUcg34ndIErps2XpHk3AwVmDYLOsWV+QWt9dUNrCsBnzNNUTZPHkgxLxpnu/q5QriXBVMxuLPMjA2nQQaGfAQPb4w0Ejt3Pjovhh2NtwPV3LNv/c/yIQqPmSn4MG6Dbmj8I1b+0EN5ROHK6ZoYQ5RzaOhTz8V95/N4r3PDgrH16WPxfClJ9vwStQf4bP2fmQInCeJkPi914XleN9F0UTA6c2wwxq7v4em3hfkpfvLcBRcn7CGvzYdMI+xZDJhmZnH5shzSVu1TkoRpnA==
*/