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
3yvt/yT3KZc6XvdE+Xdn69Qoz/Np43SB+eJXzlvj8C3Xh3k+j3zXOnK711l0qfPTcZ10i/1nfC9q8/nnObbLftmW7/1vdN2MMd+eYf57w/XNef3eBK9jPfau823bpxzPFOfJcvO4+8sF1/p3z3zn2c3OK/Px3ucCrpM+R7X+unCr9cBlxmnYcd7v84o3vZ710xTja+vr5rMyx9W6eNkV3u9S2/M518Pp7tudrzPC9p919JRq
*/