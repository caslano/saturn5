/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LESS_EQUAL_05052005_0432)
#define FUSION_LESS_EQUAL_05052005_0432

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

#if defined(FUSION_DIRECT_OPERATOR_USAGE)
#include <boost/fusion/sequence/comparison/detail/less_equal.hpp>
#else
#include <boost/fusion/sequence/comparison/less.hpp>
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    less_equal(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return detail::sequence_less_equal<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return !(b < a);
#endif
    }

    namespace operators
    {
        template <typename Seq1, typename Seq2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
            boost::enable_if<
                traits::enable_comparison<Seq1, Seq2>
              , bool
            >::type
        operator<=(Seq1 const& a, Seq2 const& b)
        {
            return fusion::less_equal(a, b);
        }
    }
    using operators::operator<=;
}}

#endif

/* less_equal.hpp
z7yJCRsxv7dvm7BqryAZ9tCChFlG1Xq/Wdxj4UDk1GX8gODcuNrk4R17CUdyrun37tMwSNmNPFziOBYPeBrjcOJByxO3upnGGc309139XfQOyRnfE9/1XYrwi/3i+xr2j5KG2niVvsu+Nuqe3FzAYNpYo/ktfSca2qfWbyFg8/e6n1pwe69bu6XEoeFHAQb8BzW43JIJfvJWHC4roD76aQXHpBfOOtv0/Qe31t+x05IsciGV60Q6G5ixzBYzLmvA5CGFli78P9ck7WvR+/cZe3AeQ0WItzpHZA8hfepd5fpt4us+hp7nKXSHY84VhOPfROA0OmBof8EFiWNUQvYKPW4fKUwPYI/pQPzGo3LpFGnlwbraY7kTE/gMeNi30TtEwOx1rvM6iszPYJ0aVXVgm8QhYtXRSliurSCGL0XRFXUwAnrDW0y4TUO7CLpFp4sH5+EMgrwIKWpVp/h7oEkr3O2iCO+IgTOe1qtrPZ/svkyaAlPGD9oe9vPl449MoQ2lpDHKB0G1q2DtAouwD4Glx3RztDkUJBL/LPlyJVz2xhmNZ+yOpysajjEP2UMf+dyYtBm6JOwGcHmoKpNkyneMcurxvkiDXtJFrEwHKtB6m8Zqvr81MeWIGFEOfRexeuEXQS0inj7Iy89SofLHUeqO8WxdkElNWb46+z+TmPIEFK9oB546ByBhZV+ulR0U6CAIP3mZTnJ9uDGhgRxTTreE+w2mCJ7The2R0IWZFJTTLam9uybCiCJuOyujTTHHZoPNSa2jiL8/J+z9NHXhFBLjCX8mxl4Q6u4ak7yQ8r2pDaN8BNP9v9/DROzDH+FsX3yPuMPsorrxGi6d5fcr+H7w5+X3yUy8wMtYC2/Hd0SdOfm0PgWD07dtqcdfeVyrZbnOSL32W4i+cpQw9/9f4ufJCxjL/unpcIA3yz6Syxh3jRffRMDrxuS0NyJWgwVfFeaSO4aO6e82Do7oJdJHT/Y0wmWEQUNvPQdvWiES3qm9TXj903LLBR7JHc14VYmE975mvFXYZszMc2L/TRvxUKmu88XNOHivnLI73p9svGklV2qZ5cmmTnrwXNSj5a31/TX46kDrwmuwyuFnjdrxppvX4NLEzuy7tVsQjhgDcqORBxvprq8wvMrvZW24VuLtTAdnzXErbslwyWCjSiGq+/krDI8VRW08ciuGI6x7IMTpui5yeGmvo7F0XXe8NeFNCU/wY/D9chPHLovw9t+G8Mi+Q7dSy1SfKfFo2EBPMTLkdxoS4fQmo2xovdxvG/DG0zK8QnWKGrgXF23c8lzqy4PJuOuv3G4eruBA4+29vY2nYztovIs2nskk8fj4O9h4tFfLuvXbAeFWdQ50v14sYdjfKhU48XHHOxnf++3lwD3hRQg9WSBlrKl3vFzhyXcLXWdyg/guTqp+dVS1NOynJYz1FsEu3FnAMGV2JqXz4sSoC++3BAOAZP4fiO+kI6keP6VMT+2J7mLjaJWMLutKA56U7+l8OHVXiUMPvlV1xI8Nt/Tmz7ybxLH15oTzvSYcWRKVc3eJY26LlTaccH7ZhCPvvFTOPWycuh7/e404tl7r1D2b8Lhe61ojDtf1z+4lcISUgDvI6gAzjHYG9r7394Ml3kROYZpLk3uL71JukDxS/rPNlpnDIYYAj/TIpImxfLWuP8K0rfA7oQsJyQe+n0LBufI0Cl5u6JCOmbHED8PAPUugnoH9ho5Xnit+TvZMfZPnwZYUDtaVxubG6i+eo5bhI7GdD6tP1+SfSOguud7j9kshckng/fL/Fde039vzTL1bB646kZf5nAcjmcMR1db1H+8z8wm022mA7CWQyUczM0THcYU/A76hi4N/My40GKs=
*/