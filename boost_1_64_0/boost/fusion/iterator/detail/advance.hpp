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
L8EI9Qa1/QcRmubD44g0g/Cqg6W/KXkZTUPHWSEg+oTLnYiOVWdyu7doVGpXBNderPBYEZP+ZH2wo1IvtDyzG+UEhSHluwFh6LZSUbDKkD4G6h6B7+AuMd187HRTOSDhvKUJP/UEMeLA4C8XxXspLk7vpI/ggFEhGsbmKuVQXZVRCpL37mHY4Dg5yHxe15FY4+MISgV/sKn7nUkcALSaAh23y3vuEAr94ERJaUFL0AaEe/LfqXVxyNnvXCDV/Z4VouiXuWwPsXbi/zKXFHMZZ62ig1VVXM83kZpC99zC+ip/fnB9zpRbOP2xqaBuc0/6j9vNRLZ3EyNjvMElZ9Xvw67SQE8ebuVW468EDvqqeriNUFEsUMYIPSislpOaMCtiGN4/Rl/HQGKsVAAa//yPrf0QOo5JJbY44USVcLLHKWvmXUjMqMb8Ol6zwv3Mw6vzjYPE+t40us3AJabdsoOual1Mo5PONcPPWei3VGdtnb4T0k3VL9DGlyki/EOc67hIcsf+H97JQoZj76jCDlM9BFSjJk0jBK6Azc2mYRMhmgGkLQIofE2o3iGmVQ==
*/