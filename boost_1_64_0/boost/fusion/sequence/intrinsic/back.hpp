/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BACK_09162005_0350)
#define FUSION_BACK_09162005_0350

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;

    namespace result_of
    {
        template <typename Sequence>
        struct back
            : result_of::deref<typename result_of::prior<typename result_of::end<Sequence>::type>::type>
        {};
    }
    
    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::back<Sequence>::type
    back(Sequence& seq)
    {
        return *fusion::prior(fusion::end(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::back<Sequence const>::type
    back(Sequence const& seq)
    {
        return *fusion::prior(fusion::end(seq));
    }
}}

#endif

/* back.hpp
djSbeVr6T1SMl3FbyImzLDqViyYo9N52TNNb43+haL/XuycD742zuXnSTIDG2uUVQKPtgtUudH1lo671bTR0jOha6HhC15HkD2PlZA9tE8Ar5Rwl8bzKusxodUE2nDNjWHOPDNaND7n3/pqOAQ3Y9hgxsG+sw1Db/c/WYtB2H+15dAy13X8fYrSxiuvPfYph2sp9yBChaTFwv03p5eK90F5V177uMMGQe4RblEbykb16i6CR4AXIe3QrpcPOAt9DbhQ0lsOBp2IoDdGR9+4I0Iv1HPmxTh/chjTatkrZB7YDBtddyv9JpGn8qN/4DoFh0yJXTjlfQP4toIPR4NwSvL3XDh20kfwwwTZnD34c4wUAHu9YdVvhC4RObYWPCP12c0zjqMOTEOq5/nAe0EKWcf+heKwalvGxPQ/lgctkiT80+jA8zeV8neM1GH0bBZuielzd3finGfYR8kOP7QXcI+aHvtyIpXbNU0+uxYltPOJuNuCqcbMW9jEcrvfYsYHO46NQensZdp0K/2f3E7pYhpF+Zkyj07dYnQ6DTPLfeppGhy8i58uPPEbouBUh/sz/GlZ9sLPEt9I8sA26n6B31vm/yf4w8TLXBLorrrj5/vAg5jf4N91Ph3aSFJkpaCHTGGdC7M0K3ShI7uCgnvwO6WINjm8JSUz6w4OaLLIGrddg+HKHmDs1mKoP1ulBHQNFyXWmjk5jR8L9OWBw3pY4EhejATOtYM4MAQbn73o5txGjy8Fcuv8k/cS3nCR30gBuDd8FczV7J4BEF5VYYpdUntSAsM9RZjqpuJt8fRa5TvXO6KrKExtQiB2aQWIsgXv2qe4CliFzZxO8lWSm5YNZynJ7neDhjMb9BNT3syQIPTOxnKIaT7QXqP7fUHXJjABku5GdG7gHl3ereD57y1vV2NiQcd7LzDA2IGE91fumKnsqbHlW7phSNL6FYYwtFQ/vcnBYTOOklW30ICXGzIXiPKx+Cfoew84afpEPgp1dQP0iyVvJ/zfg7xY0ka0X6JglTt6ljf4dy4Aq0bvj68+Ab6fR9bvjKYKhd8fdf6g0cneMdp8Tg0ivvTseGiQY7e54XaeTfAc3CV29ZpN6+Jt1TDV+zfgQwYCtwMQs75S4T7tOMPSe+tAwoTEFZDsQWrmtPfueIsuHfHPaUospn3+Vu617Gq748GhnhHl7txIcuRv/EaFxf1ixDx4htB7I550MOxjqckXDUl1w772N4N4FdToHZoFyf410HAtgkCT5/e0aHdpeuXfX6az9kX5wh0aH9lBshHU6tIm897pX0GGMwaWXGmPs1bvE73ilL/3akMZ7EY89xc2Pse43dwscNB/H9JRvNTYKdLnGQPsp+WqRRsYH0o0nIV2pm5KvraS3QXcof2ll5Ym1LvE53KvS8bOhbs6TgY7rFtXtOqHpujn7kE502y/KLujQJmtdiHzclbFmn1L8TuMdTeNOGHFfq8Xh7hb3aKf31+NgZyvtvxGjx01DOU/VMeKkg3IEprr1AElYv7FajBZD6g7iSLcnNnPdp9VhOmC7VETDRFm/rcXRs//CY3UY2gY36zBos8z33E+vwVD/O5R3rx4LykvM4oEaDJ6z+B7lvroniGw/CyGWhgGF0v3GoorLjcCK0tSLDXp1VrLge9S3/8Z4KISvhMQe7mWDFMMtSBED9ugaprr3PTioY6p734/VYNS9787NOr26911iGJw3JE7FDA0BBscvweD88WGGwbP/zBtz7kDA7sheBH6/QMns6Xw2S114K6X3oEcU+jQYyccAgX/KezTAHKvH4FUgK+e1CoZRA4fSA10PVgbST0p6mZ288v7nwzhM3Zlp24TaTedRwO8z36A=
*/