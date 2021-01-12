/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_05052005_1128)
#define FUSION_VALUE_OF_IMPL_05052005_1128

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef typename value_at_impl<vector_tag>::template apply<vector, index>::type type;
            };
        };
    }
}}

#endif

/* value_of_impl.hpp
XOjI+1hIfykXqaiGMftYbG0Ga/VSd6hTvr0p1eW1rmoY+z1hbSPybG1EYVEFUjVpZ2LbBZMWWz133E20y0VWf11TVhofhZxQX9wkDidqHD5QQQC36nrs9Z4iDruscWBrycICtpebemut6zh3ClpJXGzxwO/q/Sw3ph3Ihh+JnQbWfpq6t9UTcful3Ocbg+a889ziOXPZiriwSGTVZEXmaMXeFU66yqrxzgm/KWZXOrY2U75j
*/