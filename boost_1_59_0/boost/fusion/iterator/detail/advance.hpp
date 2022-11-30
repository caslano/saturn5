/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_09172005_1149)
#define FUSION_ADVANCE_09172005_1149

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion { namespace advance_detail
{
    // Default advance implementation, perform next(i)
    // or prior(i) N times.

    template <typename Iterator, int N>
    struct forward;

    template <typename Iterator, int N>
    struct next_forward
    {
        typedef typename
            forward<
                typename result_of::next<Iterator>::type
              , N-1
            >::type
        type;
    };

    template <typename Iterator, int N>
    struct forward
    {
        typedef typename
            mpl::eval_if_c<
                (N == 0)
              , mpl::identity<Iterator>
              , next_forward<Iterator, N>
            >::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type const&
        call(type const& i)
        {
            return i;
        }

        template <typename I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(I const& i)
        {
            return call(fusion::next(i));
        }
    };

    template <typename Iterator, int N>
    struct backward;

    template <typename Iterator, int N>
    struct next_backward
    {
        typedef typename
            backward<
                typename result_of::prior<Iterator>::type
              , N+1
            >::type
        type;
    };

    template <typename Iterator, int N>
    struct backward
    {
        typedef typename
            mpl::eval_if_c<
                (N == 0)
              , mpl::identity<Iterator>
              , next_backward<Iterator, N>
            >::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type const&
        call(type const& i)
        {
            return i;
        }

        template <typename I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(I const& i)
        {
            return call(fusion::prior(i));
        }
    };

}}}

#endif

/* advance.hpp
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
*/