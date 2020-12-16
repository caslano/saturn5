/*=============================================================================
    Copyright (c) 2014,2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VALUE_AT_IMPL_16122014_1641
#define FUSION_VALUE_AT_IMPL_16122014_1641

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/vector/detail/cpp03/value_at_impl.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/type_traits/declval.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace vector_detail
    {
        template <std::size_t I, typename T>
        struct store;

        template <std::size_t N, typename U>
        static inline BOOST_FUSION_GPU_ENABLED
        mpl::identity<U> value_at_impl(store<N, U> const volatile*);
    }

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<vector_tag>
        {
            template <typename Sequence, typename N>
            struct apply : BOOST_FUSION_DECLTYPE_N3031((
                    vector_detail::value_at_impl<N::value>(boost::declval<Sequence*>())
                ))
            {};
        };
    }
}}

#endif
#endif


/* value_at_impl.hpp
xBrmNTtti89yQfolbauF8zXklkKX78T2BvrfiXj7d0I5hv3HvxNnbc9zrX073w5vJd3afs03S6/908QVl4/f4h/te4KysKUvf/Dudz5+2Wxe+vLYwqz1D5yq/fOmh9rmj/s2tEfyuaJVO0dODDjVaO1iz+1njW3bfXjCgpRTDW/dtmh7y8pDD/xhf+3b/zy18w23KOn1n2tumT6n971/enjX+J+CD6V5bifjul7SX3wr5Ysd2R1O/nxb6bB3uz5OI9XJAlv53D78pQ9a3n1dXH7xzPf3PMmFuN/b5i/7aEKXu6Y+1HhFk0Nebc49+LS9vS3WJOcfHENk8sIbwwhlCnS49mU4dsLR2NmhXSxJlo+R5V3bxdpiCzRjS1kuxSTHb5wly/lgYtWHUZ4jOxRjcDiOwhE4FkdiKiZgGo7GTLxKzZccc7G7Tr7ayPqrrrMPkOWmKiHHnXmynC8my3LBzNcGu2In7I5DsAdOxZ44Ay/HmRiGszAc87CPbCfIJMcl6CLPTffCVrKd/g7zmWW+nheZL4WIv0h5Rsv+xmAM9pPyjMWxsp5UHIBpGCflOQj3KAX3OW1r9/ia4onMONoWif1ENn8fx8m5tK2h0o4ZNIj2NP7eSMQP0to1vefQrkhUhJGOmYNYD1FGHCQspJ1En8G0JxJxxDrSthOHicn8bcqj/Y4o5HUIKm2ipYOR1+VYhIdJOzmY+a7g3/h7D1FBXCDi8skPkXwFeSLOMm8JribNO5xt8bpM+fdw8sTrSiLASn4JC6F0dLwd08AUhEVWliUSeL0Tz7PMIZwab29f3TObNkVenyJtWISPaTuv9xOBBfVMx/EsUcZ8Fv6uwCLcSOwkAq5kXTiV5WJ5HTiXfGMuEcfrycRGXi/HTUQ5QfssH1r2QVmW2Mrfp7Eco4ewDBHHvycTy4kl/F1KbOJ1OZ4gfIayf/x9mgjldSHb9ymkLZiwRLAsJpA+mVhCnCWtBEMisZD9IE4TcfxdRvp+ImC+vZ03CU/wtwV9hpF/DMMkwkoUE3uICuI84T+cfyf2M98wzCbWEWVK7OJ9xpPz7W3Dp3ntM4Lykrbh6AXsE5pJS+L1cmI7kTCCdLTgCVyN24lDxEkiIJp8KPs80t6GHIhNF5IPIpbXyZiMhVhMFPF6E7Gb1/uwAh3bmw+TFlhkb3eOVuTvFCwiWiWwLO4mjhNm/jbdRH7Yfgim8HcCFmJxAvK6DA8lIK/3M18h37+NRBnxNnGaaFXqazITiaVGG7Yx/W9Nv27/v63+PzdjvlL5/+V1/wcd+vkzpR7dia94W2yHHyj1r/ds52zlJ/rQ5BSl7z0rY778Tk+46O/0Bs1n/t0+vj49x6L+Jv97Vb2/UHt2WUhVmkO94uqWznVHs0P9yip1jb7UNRzvWxhJ4ffCIPyQdfq/b6/rUGasKLUg1zLNmn7x6xbUe+AlyD3w5LoAt/xk6uxLrsu+tJF9+YctzTord3pBhvvz0Sy8G1I/UdNybcuG2n7HyTz2aoxabznv5bkeol/f8FQ/qf24grqqn+jXK+qu3qI/nqH29Rb9+onncQ764xNqX898w19JT3xocdyYb2Ylf1O0/oc2Y1fE2+tF503y3ZTvbKWXvZ59ilCmaVKvmY5BmIahmIFpmImrMAtvxZlYgtm4D2fhizgbf8A52Jlt5GF3tOIALMAbcC6m43ycjQtwHi7EIrwJt+IifACXyP2llmI5LsdKXImf4ipswn7dgq1xLbbDdWirF3rJ91u+9yxrqzuFoUnqgb2wD/ZFMw7CCEzGSJyE0ZiOMbgU++Kd2A9f9WI72JbtDsBBOBCH4SAcg4NxCl6BMzEeZ+GVuB6H4EYcivfhMCw=
*/