/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05062005_1226)
#define FUSION_END_IMPL_05062005_1226

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<iterator_range_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::end_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return s.last;
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
SCDlkX0zZzz8nr3KkJl8GvDwE4Cg5RlB9uJdOpbMVkP5J0dABCWBjTR/Zchb/iulUsMzBNsnTvnE5FPHB9WXF4HNk0KsX7BNIjTBeFWhzfeCX2D21PnU6tdDCui9Nsb3ganqp+/pDIa1aBiXdvjkWT9+XU8uovcLkTQz8uOPQlCBBJaav4ky8cRU0i77RiaCIp/yO5M+O9Kxsbo4EaKPHPRlVHAB0sPbCLpO8KYPEJX+yioI89nSOpveGT7lb4F7U+Q9gh46RQwc/CNgJkYoNh7nxMxAQBKgyOJkS5nlTvZdqTKd9MjMpTWliy+enxbTqP7Is/q8QZUJWa/0M0Q8nHRr848U3NZC1fvKSEAhFdqFDXyANkAQVhmj1821tUWo8+An4MFbH5EY55P3JmmRxc9yktMvYZ2v37jhjj/2EO7AZsnW+NXM/BOVGBWNbaUP9ESs+8BXGvfbQ34vLDnIjMR2KG9DizzXWYpHGS4JUeQrnoFXx6lT+fGHK71RA+YbzJy945A6aW1syQlVSQ+P4D/syekY++JHa7CHE6c279H/ntdu2plTulV3+Q==
*/