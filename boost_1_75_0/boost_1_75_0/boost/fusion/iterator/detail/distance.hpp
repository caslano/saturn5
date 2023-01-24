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
P1yU5Q9PtbPpLXny6thm7I3ArUiR6g0XqWoGRVGgWZpVR2InbmukKguQMp9m01igzuvjjsRJ05DNe3Qk+f3+GSbdvsxxU7N1B2Inm+Br2QS/dZWR1IAOhqjVQDxd9Hb5lZmdeYoFpEapWnKEhdBSCg1fvJr9A72OHVLVfeR5WysgRSPoYle4qjLYw124MnulVHWzmTF2nYS+i6b4Aspr6FZ2UdTqjhqrST2/zUTCYkVWPCC4E/j7L+G2lsleCAVxIhYmG88RVcuGH0MER5JlnIyp8CSBVx8hwIWKpQz/S14LXD+6A9iofvTn+VT46NBbbhS1FWvFpSAB/tRAoHTiUq81sTcRptYtw37mBWXj0R7iPZQewx2eyG9E/wnRVryx0fCqoOJOIYrvimbDI8O7rMulnI++ihXiLI68InwM3t/FPga17GMAzVtqBOrNu2M+To6XhmKYwF71T0M5XOBXNFmcs+bEablwmb20IrbM/ChZoIId+R8GDwHfTDOwZPN3k6rKHfGYNZt1JcUdGfOBMgTDYznIJqEoOkZ5LDQ55B8wQLqdTvrPiWJ6Wok5SVTkeirCMeBLzDzpZNKCfXYJQ+qbQu2wGU2HO5v8t6F/mlWqxl197Ypx0KRMKTQGH1o4dZxs3bu2sNgDu271VVi6B3mzubKk6t5m4dTVzYzTcG07bdOuvnJkRpZsPeBW3nVLNTNSPKhq+ALuKTen
*/