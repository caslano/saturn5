/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_09172005_0730)
#define FUSION_DISTANCE_09172005_0730

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion { namespace distance_detail
{
    // Default distance implementation, linear
    // search for the Last iterator.

    template <typename First, typename Last>
    struct linear_distance;

    template <typename First, typename Last>
    struct next_distance
    {
        typedef typename 
            mpl::next<
                typename linear_distance<
                    typename result_of::next<First>::type
                  , Last
                >::type
            >::type 
        type;
    };

    template <typename First, typename Last>
    struct linear_distance
        : mpl::eval_if<
            result_of::equal_to<First, Last>
          , mpl::identity<mpl::int_<0> >
          , next_distance<First, Last>
        >::type
    {
        typedef typename
            mpl::eval_if<
                result_of::equal_to<First, Last>
              , mpl::identity<mpl::int_<0> >
              , next_distance<First, Last>
            >::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const&, Last const&)
        {
            return type();
        }
    };

}}}

#endif

/* distance.hpp
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
*/