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