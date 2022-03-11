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