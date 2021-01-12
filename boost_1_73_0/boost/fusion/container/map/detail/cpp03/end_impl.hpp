/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<map_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    map_iterator_tag
                  , typename Seq::category
                  , Seq
                  , Seq::size::value
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* end_impl.hpp
S1gGv7GRF/wWroDfwyvh047c4DPwFvgcvAc+D5+HO+Hv4UvwT/Bl+CF8Bf4V7oLfwt9DP3XpdRiGb8AsuBu2gG/DbvAd2Af+AY6E78Gx8EM4Be6BM+DfYBX8FC6Gn8Nq+AVcC/fB6+GX8AH4FXwYfg2fhN/A5+C38HfwO/gG5FVq4R/hUvgJvATuhU49jkvgfR97DmwM28AmsANsDjvBlvBk2AoOhDlwBGwNR8Gj4RjYBk6A
*/