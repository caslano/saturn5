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
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
*/