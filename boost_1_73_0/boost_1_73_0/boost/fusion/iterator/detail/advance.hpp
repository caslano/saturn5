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
IBt/y/UAZupZu/Oh1mMbKZzIZKTu6rmL8EoNplqhom916f61B3ZoNP2Oweiydu2CkMGSnzp4UHCJTavtnLZbvUarZx+ot4Kp4Q22+r7ZRXvkBIIVdrdp2pO6gGyBf2O8xszB8l7v/CUeTI/BVQsGfLJcKbICdzGlEvuK+oxlruOCLQQ/jeqazQN798CO6ebOvdcQwX39P2KYGb3e3gF/pJJ+ObxaUOvIrvU0m7Kqo6eFGMIrG3j+YgKx6DDy8bRPh0cvrjLlO9Mk0gXpFXS6ZBIH6mCnPlIKAPS4MY4jts2JNwCEFNUdHZh+1OVOhy90Ac7aF561L+juVfEdl7UdldXIHJuSFBnoqsI35W0/jB8eHH3Ff8AZX37dfgn/MY+oed2nTZ5PXwqTTear6e1jXWOc3qoDvdoPYFR7JzZ+SIBdq+R7Eceo2xEypwUpGruIm0kGZNg5A4+jVvrSBRMXAVxK6daIf1VWOSTfcxcr6nWM1xhYtypiliQUH7l+qWxf/2ouMTH5lGZbW20q0O42cCptgOPRVhe3Bcb3OtNODkwup8miVCtz7AfoMdCx/KFPt3yYvEwyu8jLwev1CDDe0CrwLpnwZjaN90UOKO5CSTegy3fvwugG4N5Ik+Np9zsIZYy0p2t/OWcKRJ13
*/