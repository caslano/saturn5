/*=============================================================================
    Copyright (c) 2012-2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CONVERT_IMPL_10172012_0940)
#define BOOST_FUSION_CONVERT_IMPL_10172012_0940

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/std_tuple/detail/build_std_tuple.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef detail::build_std_tuple<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type
                > gen;

                typedef typename gen::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return gen::call(begin(seq), end(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
9ajya6aVB1eSBIthQjhqg0/+7WQ0WC5NTiTNdPPOPvcSuXYQGNZB47lUbBFgKDHSdRRNbGYKyVbumNHDdlaVxDxNEoq4Y9tiMyECvEeBTY5ITrXd4OHRlqCt/NYYVjjAG2SPQVfIO+JSK114lhQSW/hI+8fGuHZG+P4ETPwwnAfT3QiQu72no+DDcBwHRjTCgylRhImIVaG0W7SpxKONZtGc20jje86rtt94qiAmVks8o4BlKB80+a2s4NA6u9FrherKn40iZ1Ww8t6sTKZBFFwEo9C5lUqbJdsjI62tUBpl/3NPRmkOuih+IuvSYg/+Qcl8prK0sKeu05ELnd1bwl7H+5mU3kqUHXT4Ajc7kcYjpmD1vbWq8bVpHyEe9cTAFt6R36TgrGyq3bN/HS8TJnP/oz8c+e+Ho2G0cPw0bWXyzDs9907Nhukgmk3H8NEfzQbOlGt8U1AG2SAObkC0zLMqSed/S06eunbTbHwzDua7tpMB9tTFQXKsk1kUB1fx7eA2mC6sP3x92CBZRamaLBOJQA5DzlmFpGUJb/vaCQcD8EdhgKfr+ykcaTB0kF9YLzhm5u7BgRHNmj/DQ/+Z1TT4tHh80nH+A1BLAwQKAAAACAAtZ0pSpOScI3EGAAAKDgAALwAJAGN1cmwt
*/