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
Jacx59aX73N5b0OwFcHyGdXLjAkaClRnoBEmKcx1l6xosqCmEu9jDnzO3Z841oQjkqpJWHUAhOaQ0iLpln5pvgK0ej2cOr/Af9n8r5zjN9LN9HloXHW/NCHXpxXn/wMU1iVZr+/6wLDZzJxfDffoA7/mIUSTdLJIOMb5/B0P/A5gHDyJm0pOheyo6nmD9Jsml/Sd4Pe4qYVymaiPVhhTLBY3z0znLbC1guort8yZT14aeOQxk4gSlBlhLts32wNh9UmKYsYD+T6LiQCc6X3m3zI/DFipkM7VInBbshc+wEkfZUBkgV7fisOrnzY1ha/4z4d3fZD0DIL3xvKMTaez2ElAiEvaypC0bjBJeM7G7x5UkaZd36RU0lhkfM1Z797VwXalxCOPxOZgLxBgNc9bXQBR/2nNNRKiJ1zXLiU8v7CufuD/0Y5Jv/CxAR9R0dMU6HkIbusRY9CNiqIC+qtGpgVazxGSfWB11C95627jQ6kSID3A2HtZbOXnqabutURDei/QpKoIOGMnNslQQgE+dGZUDczVnYxbuKA4vzN4fJEosWeyEbGqFZM7SQ==
*/