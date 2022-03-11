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