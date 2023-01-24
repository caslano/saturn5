/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/value_of_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                value_of_impl<map_iterator_tag>::
                    template apply<It>::type::second_type
            type;
        };
    };
}}}

#endif

/* value_of_data_impl.hpp
gzniKF4Fox8cKH5FxP+GFuJ/gwn/2T1LZPx/Da+oayFjNpuky4FDUloAdVQBvjf8r/hOazvLRrXGyVp1GJtBrAYTYnUFB2doGaJxS8tQod/7rf5HVHg3JhQVYkJR4VRkVIiJiArjyA3LptdbgAq9erF2VEwIKqQ2iwpp4ahwOak5B8GogvjTClDggsAtMY0dV5Fm0CrSDFolNYMYOcqSwdEf4AYtTkKPsuSn6PfwfPb3QEhSljydfg+F32X0Oxt+P0m/b8xnm6GEMOz9BnGGbEZmKw+Km8LgJPiuwzTCnEoyeZet3JuYU/4DrL+YZLRL6gDi0rTMcirvTfTiEzcJs6s3CRQSESnSNKOaQRFJEAFNqFeIiJzy36DSLPRWh5WmhVT6YJookiG91qj/dI0VXSDw892Vgz3wMY0/boSPJ/kjGz7K+GMofEznDx98VPDHcPh4ij9GKDTY4meuu/LO2yDtaU7LE7ScXKahewev7tvfbcV7hzPq/yGVcMZd4r8t2iX+Z6qAdgmPNdIu0bLj10yEgh/7ww56DDloMeU/GJp/oZH/Esjf6HRWbAPsqOAdL1T6fdlKugpYrM1cBYD+P5fpfw4nnYuk/cMU3E/BWApup2AUZx1Kn4PPZbGf/hzfl8PLOezB4YUyo4sjWnNo4/CUi8LDLrOOTRPeAe5Diu3oBIP9hTFfZivB3lqmchQZCGACCRhN3jT1CRuI
*/