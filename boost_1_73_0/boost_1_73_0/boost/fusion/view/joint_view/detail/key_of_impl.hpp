/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/key_of.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<joint_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::key_of<typename It::first_type>
        {};
    };
}}}

#endif

/* key_of_impl.hpp
f1ks9ZdpnC/vifNVsdB30zhflRH6bo7Qd1RCf1VC6DsKUlYWuodrVkFC6q+Lpd5Mk/D6nhJ4Uyz1jK6/SeJcAetv+XJPI+TNQ63I9dJ+qxI2hzfMGfRbBQ0rOjgRauIeNM7w0BFFNR4/IOGy/BACJ0RNEc1owLPM4JZsYrSqcbbnvzJJFv7loV1eeTIwybg0R3/h6g7ETEvKqD7x9PiYBtDrEUSqZyxeisRZTudgANBkE95py+tR/XDue6HI6+TB0AU1ssneACi2RUrxewqkNvegeAAF/Y6dLj3PIeZ4DHXD/kVbgjOScxFMN/EN0FKW1A/xjYoK7HLmfcVlNGww9yBQo5GGHrnk2NFco2iORGDL+uFllL3yApF+cmEcICXkBRHpD88Xt+QslffE1XD3KtiiqSn2TPdhFX/PUQI1LtZvj2dUGXyon0SFj1Ysj45202JjybMCWzK7XgFvCoCeAptKRycZMQ9I9cIZhJJLtGJ5amk3QSPTQKR65Pk+bvBxGyWRjTIFZIYKVDBjBEhbvCV3sk94E+as4vZHkuELfKCDoOVAWQhvbp2ixtkunQsLBeWR6ogvv4ObivxGhfokApZmVTl6jrCSIc9gbZndUnwpZ5Yynyo66h3h9oHYsR3Q+TqXMl+1hhk9X7NG
*/