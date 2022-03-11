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