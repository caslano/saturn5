/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_09242011_1744)
#define BOOST_FUSION_VALUE_AT_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <tuple>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<std_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply : std::tuple_element<N::value, Sequence> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
3rA2HACbwYGwheq3h4NgNzgUDoFXwJlwJJwLR8GVcDR8GI6BT8BxcAscD/8GJ8JXYBY8C6dBjzPeh03gTNgZ5sPusBD2g0VwIpwFp8PZsBBeBZfAeXAFvBaug9fBDXA+/Bu8B9b1UP9Byoyom6m6G3wA9oIPwgL4MJwHN8Lr4V/gcvgovBk+Bv8In4CPwL/Cx+CTcD/cAg/AZ+FX8Dl4DG6FJ+A2+DPcDhOceR9YEb4Im8Kd
*/