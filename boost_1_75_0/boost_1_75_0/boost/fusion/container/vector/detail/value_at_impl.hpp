/*=============================================================================
    Copyright (c) 2014,2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VALUE_AT_IMPL_16122014_1641
#define FUSION_VALUE_AT_IMPL_16122014_1641

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/vector/detail/cpp03/value_at_impl.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/type_traits/declval.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace vector_detail
    {
        template <std::size_t I, typename T>
        struct store;

        template <std::size_t N, typename U>
        static inline BOOST_FUSION_GPU_ENABLED
        mpl::identity<U> value_at_impl(store<N, U> const volatile*);
    }

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<vector_tag>
        {
            template <typename Sequence, typename N>
            struct apply : BOOST_FUSION_DECLTYPE_N3031((
                    vector_detail::value_at_impl<N::value>(boost::declval<Sequence*>())
                ))
            {};
        };
    }
}}

#endif
#endif


/* value_at_impl.hpp
ukZn2WrWeCacC+XICg+BBCoWGCwLUk5KbOpW8lUUEsau+62aDCFSFdMvlPBvjwbcJhRxgQXzEf5nLU9JfBMvsMqIXsQ4UDIiZOjDS1Xp1VSJapD5dIgOWRxPJ8nveOr3WE1rUk6sjTKJe0HB2arj+vuQM/jjPayU6rjiPiN3cN2vM5fdFp07cNGAqaw5Y3UWIfnjOrPmrmIVKX3GRmv9UB1PlAPReZpbM14UTMKTiKdXy0z89Oqhcr25iay54G1wdDILt+Syxdr5lHcxnpFm8E6+aIDq1WQn1+TDCRWDoOMp6CccTz2Yb+zjX2V6H9F/RTck38QNyS44iM9NVeYk45lIBkz49iiDAEJBl8vIsu8n2VF17CwTxjl6kyN/hDXtJTORqGmRwb4IxcC+CJsXzXRQI9oXyWzpWJISo4k4yg9v6fZF2u4hRh5owGiViWbyXhnZelrj7Ynf3LGFzjSPyV4ec35L6V9e3dRYhytHQ1llGMrOyHBTaWa34lA7aSmN4/fehnFcoo0jE2SK8w1isJcGMS7c6tgngnbJGn2XrBG7RBJ97BVJhSjFerSmwsiiMGg3onALvNzk+KCOrI+ScvebaH0UeipkdiXr4yH6Lr9J1kcVrI8HFpL1kbGd6oVG62PgPl36eivE+iiB/FU/Ktz6eEj5ehRZHyU2/vvI+igZrI943hSCVrfyyVhr0iyQa8X42otCA/BymmX/
*/