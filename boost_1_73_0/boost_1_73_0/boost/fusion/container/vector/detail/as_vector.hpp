/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_AS_VECTOR_11052014_1801
#define FUSION_AS_VECTOR_11052014_1801

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/vector/detail/cpp03/as_vector.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/index_sequence.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <cstddef>

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

    template <typename Indices>
    struct as_vector_impl;

    template <std::size_t ...Indices>
    struct as_vector_impl<index_sequence<Indices...> >
    {
        template <typename Iterator>
        struct apply
        {
            typedef vector<
                typename result_of::value_of<
                    typename result_of::advance_c<Iterator, Indices>::type
                >::type...
            > type;
        };

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator i)
        {
            typedef typename apply<Iterator>::type result;
            return result(*advance_c<Indices>(i)...);
        }
    };

    template <int size>
    struct as_vector
        : as_vector_impl<typename make_index_sequence<size>::type> {};

BOOST_FUSION_BARRIER_END
}}}

#endif
#endif



/* as_vector.hpp
vPvlQfNTg/8BUEsDBAoAAAAIAC1nSlJkoug92wUAAGwUAAAbAAkAY3VybC1tYXN0ZXIvbGliL2Nvbm5jYWNoZS5oVVQFAAG2SCRgzVhtb9s4DP6eX8FrvySB26zF7stlN1yWeGuxnDPkBbsCAwzFVmrdZCuQ5LTZy38/Uk6bNHWcLt2Ac7Hak8WH5ENSpHssZlnMZ3Dhd3r+MOxOhv2wOwiCbqd74YcXtWN8KTK+832r+fOuGjRh7xW6fyFeeHcSH7T6l0e2fHcYfoPiB6U+4X2fkhasRb6FDdgv8g3qTiRcaXlFz2G4T9Enso1+tUjyU0iPuIJiJNlV86UW14mFercB5y/OfocTvJ2fedBjmeASRpZnU66vPXgVu5W/EnZ7e2r4aw+4BSZPS3HOHc7ZSw/6IssNBChpeAZvubRfREZwkl7co60MGifCgFEze8M0B3yWIuKZ4TEwAzE3kRZT/I/IwCYcZkJy6A4+XF0G7zy4SUSUEMhS5WASlcsYErbgoHnExaLAmDNtQc1QHMFjYSwC5lao7BR1c7Bcp4YwSD2TRgFbMCHZFBUxC4m1c/NHqxXlWqLVrVhFphXdOX+a2NTxQQBXaETKlqDmFqyC3HAPaKcHqYrFjO5IKy7O86kUJvHW1qCqLG4pDYZL
*/