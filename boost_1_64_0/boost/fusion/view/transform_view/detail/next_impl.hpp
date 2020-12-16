/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07162005_1029)
#define FUSION_NEXT_IMPL_07162005_1029

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    template<typename First, typename F>
    struct transform_view_iterator;

    template <typename First1, typename First2, typename F>
    struct transform_view_iterator2;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        // Unary Version
        template <>
        struct next_impl<transform_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename result_of::next<first_type>::type next_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator<next_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::next(i.first), i.f);
                }
            };
        };

        // Binary Version
        template <>
        struct next_impl<transform_view_iterator2_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first1_type first1_type;
                typedef typename Iterator::first2_type first2_type;
                typedef typename result_of::next<first1_type>::type next1_type;
                typedef typename result_of::next<first2_type>::type next2_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator2<next1_type, next2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::next(i.first1), fusion::next(i.first2), i.f);
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
hcl9epyoP4UsBib3GbPm3hs+SzBzYT499NzbZJjse3fXprXJ0pT1sJGTZFdg8jn8o/2mzWS3Feu2Z/hZzlPZy4eP2z6SvVPGzdJX3Ur2VclsS5flw7kPI42zTu9laiDzglUStuxLz8r0Mw6hMHqfukarVudqssGffj4gAUbvb9dqUcOy6830oe/dZwj7jxYR1WZF23b8fe+ownvWOi0qwr3NjqFkepi7MKf0HjqyQJirsN9Sn5UjC1Msw+/7S7I4Zc6dHR/0IEuGlRe2b2zLw2RZMCdhm6u/nUKWCzMXVmFou6Vk2ijcQ4QlNPFbTOYFcxAWOPG6CVkAzEVYqapNBpOFwkoLS9vg7cD1wbyE2R8+XY/rg3kI044uiSbLhDkL69i8xWquD2YlLCts40MyLRrPAcJ2Z0V5kelgtsK+lsspz7XDZI82HnBM497CZB9O9TE5R2aAycyelLn+iSweJntr98BiN1kqTNZ+2v0M55kFKy3X29Sfa9BG43laWGfXD4PI9DC5l/QpsW3I/GHlhGnro1+ThcHkmZhffd9l7p+y3v1fWoaSJcLKCJv67swXsnSYm7CAuUPiyLJhOmHNuowrQpYHk31vsstxEtc3xngv6UsNPbk+mLmwf8vd5R4FwmQuLRJyK5KFKua3d/hp7i3MQpizzYIIzgXmJSzhuD/3NhlmKezPBiNHkaXB5NnNmzeUz1mGspdh9fI4z2yYPLsb/qz1nCx3DN938+03T78jnCfMTowbOT9oLpkuxjjPGm+acC4+MBdhoybVCSYLUuzgtIq9yMJhsrdeRwZ/5cxg1sKKHV08nywBJvfpOmd4Jc4TJmuPelUljPNUagj+kMW5ZMJk1hcTy+RynrAKwm4EfpvCuYw1PoOTs25akvnDZH2X75buzbnA5DW98npiYzKDMq5xQOMDZPEwe2FlD19dSJakWNEPw1Zy7TBXYY+HzdhClgWTmR3zv3eSLAdWQth0s9UGMvNxeF0n7BfTYHsyH8X65er+4NphJYX52C3dRBYOk70dNq1babI4Zc7Xv39uxLXDZP+e9hrJ/UuFlRE27nhkHtcOk7nEXb7EWefB3KRV+VKdTD/e+B45aWKXX7k+mKwvc6P5C64P5iks5nCT02QJMBthM+aOqcr1wWQu9c4+P869hckzWOvUgjVcH0zmUuzbhRbcW5jse+j1nY25dsU6Ty+/hPsea3wmTF+0MeW+w9yFLXjWpT1ZMEz2z6rOxsdkBsXa/7jtybnAdMLWHH5ReL3DZO33Fp7+SpYBk3lubnmvC+cCk71t/D7yAdeu1DB0+II4Mq/fja+xlVdH/ZcsACZzmfm9+FiyUJiFsDHjQsaRhcNk1h8WLnxCFgOTNUydcrIJWTzMWljO/tJ+ZIkwmcu29sc+8nmBydp3RXTbzbnAXIR510rtxrnAPIT96PS5LOcywdjextZeRRYEk+vVWzNrNdcOcxA2sYR2gywO5iizXn0wkOuDydrnvJpznywZJq+xZNOlnckylb1M/1HEnixXsfub/7pLpptofE07XOt1jswf5iqs0Y6+iWTByrh3DWdwngaYXvb9R5VSZAkwmcvjERs/cX0wS5nZP+1+497CZB9evo58Q5YNk2d3+cSrS7i3sBLCPm4I60qmjzPuQ+aJ2L+4dpi8VgIjHyeQhcJ0wk7emDOea4e5CHvobJjBtccp989+CZFkqcpe5vazuc3XO0z2r0OZ6KVkOYrVHp3Vhcx8kolWStj8AT3cuT6Yl7C+/ym3heuDlRV2b6X5cr42YaWF9QoJfsc1wLyFfXmwIIN7pKz3zKWKGe9zsrHN+3VK4RlULO/5me28T5isr8HHvGNkccq4cwc=
*/