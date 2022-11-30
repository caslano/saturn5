/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_AS_SET_11062014_2121
#define FUSION_AS_SET_11062014_2121

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/set_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
# include <boost/fusion/container/set/detail/cpp03/as_set.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/index_sequence.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <cstddef>

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

    template <int size
            , typename = typename detail::make_index_sequence<size>::type>
    struct as_set;

    template <int size, std::size_t ...Indices>
    struct as_set<size, detail::index_sequence<Indices...> >
    {
        template <typename I>
        struct apply
        {
            typedef set<
                typename result_of::value_of<
                    typename result_of::advance_c<I, Indices>::type
                >::type...
            > type;
        };

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            return result(*advance_c<Indices>(i)...);
        }
    };

BOOST_FUSION_BARRIER_END
}}}

#endif
#endif


/* as_set.hpp
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
*/