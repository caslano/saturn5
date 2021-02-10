/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_07162005_1030)
#define FUSION_VALUE_OF_IMPL_07162005_1030

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        // Unary Version
        template <>
        struct value_of_impl<transform_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::value_of<typename Iterator::first_type>::type
                value_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value_type)>::type type;
            };
        };

        // Binary Version
        template <>
        struct value_of_impl<transform_view_iterator2_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::value_of<typename Iterator::first1_type>::type
                value1_type;
                typedef typename
                    result_of::value_of<typename Iterator::first2_type>::type
                value2_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;
            };
        };
    }
}}

#endif



/* value_of_impl.hpp
iLxrqeCYwwlDBOVEFhj/YiuQSirrOiC4e/WZUxcY+9uhEhHBwVFwSnBy3f/p7k0TvvmmXuWh601/Muy97w+Gr0dNZsfzXaAxjCncOIzX9nh/u+thU3375gLWVycfbvpu1ez37q4Dz/BALNO9Z1bB3955/vklN0CPkzAyn+8lQQ8Pkdh17FsIYzEze8+QLWO0c3sjjR3EccGo51AsQM8xyHLsvo0IV6hVw1thqqGQxycK93KSYhAzjyASovxzr+oM8tPDpZxCh8KFejlHTWP/Wh3fXyq4qLSyXFvt69grS0Zzs8utBMO2P46ngttMhFrWj8fEhXQqubaUZr1SUe53RWyXPCG9RRPEkvAn4GSiPVwisVnHLNYEATyOD7C3yGlSV6SghjpfmR3XHCtswSP0w3ER68JCBcwJW20ytEq5GFKjoNB/fHvA3Kv5nQTwdZLF0jqd+DanRKWwiKmPphnJ3ed0t0z90D5fWkHInU61x/fuwRG15bwMH1i69auAaH1agfppVaare7MLYyu0I1IzNUc/l5eVJyo7qStrpxxZTBHbepqla5DV5ea0CF3z4/oF/GhwqHYXFjBVM2fTFTw/FPkQcqrssK1cyiBTbIyQrWcrAbYMFUrrR0wXLcQfaO6Hk82qhorHlPLLSrmN
*/