
#ifndef BOOST_MPL_REPLACE_HPP_INCLUDED
#define BOOST_MPL_REPLACE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright John R. Bandela 2000-2002
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/replace_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Sequence
    , typename OldType
    , typename NewType
    , typename Inserter 
    >
struct replace_impl
    : replace_if_impl< Sequence, same_as<OldType>, NewType, Inserter >
{
};

template<
      typename Sequence
    , typename OldType
    , typename NewType
    , typename Inserter 
    >
struct reverse_replace_impl
    : reverse_replace_if_impl< Sequence, same_as<OldType>, NewType, Inserter >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(4, replace)

}}

#endif // BOOST_MPL_REPLACE_HPP_INCLUDED

/* replace.hpp
bfFBNElskXB7Au+zi6jX4Ha+ES0o1t4+SlaCTlIH1g4i0yU5/xLc1wDxoi3MQm9fLYVOJr5DmaEHINb9L8Nqe8+8YW/fkfPWR+2wK30tR9uQIczsFyqoFfOx+0ICVXfJfLTPKdGW6AWrLKH0DaGE1tSM9V/iwnePmh/katOTzfMDLFifFxHIu5NkmO9UYb5LltpUYQ7/SjAUJ370QxiFLAcfcphGQkTj+wqb3t8jfX+QXKNLg2KEEPim5/v7Kv6nwkuf7ntcNsD6cYNsEEaDsL8kh8GAdwNJ8t2AcPcdiYgQpd8m+L8ks//DoSaXOs3kFLryWENsD8Bp9YuVbM4PYlCEazKC7MKuoOHtiL7u6gqlr4MGyslerQ950BnjIfbQ2Cj6mlikxVEiJ9ZHnQzjVPHB7YFyafJtsMEVtkyDgNLb7bV/8d7OhN8ieq5Ejksix4kFXSdNm8Aw2TZ1aqd84dOZAC6Vf3mfxa90CTVeHsvHwEoH2ZWXOQPv7EV2gV36GX2TAGdev9LiW5yhx3rvDvX3J1q+GJzRON765uOx37eh/aAXg6J9D++L3c3Srahy7Wkav5Fhovfz5J75GdYNP0t3JsbPglei+TkjBj+OBPhZ6YjPT2dTYvy0vRzNz69To/m50dkzP19NlvzELn/Hrsqj7eHczqAx/i/lnL60O9bszW+xvr/ACk4l1ZEhX44Ar3iJupgLsL4/Vr7L+UyMgcVyHAvpaWxguLoT9Tl+RvtxqZD3cy/KqPWsKz4LCv+fdnulmw4P33aTq2prV3CcHWF51lOu6ufKRwVK6Ze9KpzHYzr97Ft1IK08Q5RX7U+vyKAKWCf3hLZhLPjrnXhpoq/MLuBAZ2KRewFIv2qsF5OIE0s7KqdSG0dBJxEr8Xmq8j1d/QvfyvewnWPbDqk5NCREr5vab9/DxaQoqr2E18pwsUJn6E9q6W2BDVT9FGrRszXhUTroBOaT7K3oe/eLnfSDKWCYchR13tF3CatW1L05OcivJEQJfQah6i3HprdSRHW+6H8b9aijNLwknRwNWoRNVSdtOmAXVQVvQeKNKf6MKKIdVeMrqTe1ONEqzN9ZaDJahNEibKo6dlNYr7qELwfAqcTOm+2h84UK8EkCu2CJb9bfZNQNo25YEKfpoeSHWycH9+Ku0DDp/rZcKRx1NPdjGP0YDrUY++QmFnTcNlTIKZ51h50eIZVvNNn1uRB5dP/UfsgrwjzeeVY/4eDzrfsJOM+S4M8WHKT/H6L/dyXhDDF5iw6BRls5r6Xay/uHzlTvMQrcd7g9S4oOhU4CzHABqPuOHNuS0oMNNrzMUBmHkMHbb6bRj6w/FnXe/mYnV9lv9zMiSruqX6xIQRSNWKAofMedDPolHnUvATFl44ZVbzo2vemkJgdvf6udSRxwZmwDkYKu6kZFBMHYHYtAxEYpdBuIcFO6p5X2u1OTQ8MamUY4JaOJOpPod1U/J2kgDgjfsQQ00uVtA6DBLataJvsLEm9CqpxY4FnA855JpBZHUQfZIBbEIV+HkXcwRt4hlRd8lGFMotiSzHdG/EdAUPnXg7TFlHtuvAg5L+SFzkKfaxLeHYzYH4x8d3AKVRABd8Dmt9PskKOvqS7/NFdgKsfwgQs89O6H5T3HeWs6UeYXlh2IrfFGE3qkemUz8RAs8buph2dpoz7DwygHgWcnAs8TykpQD4PLj9/Q59VY1lQXaagLbEA8PNGeVcPbtTB+OdkRTlrEEWyzygi4F5V0lboxALRzIxKBW7f7c5bAn09W7nP+UHAoyZRnI2kQ8fBS0U4MhZu2BvWhzxX8Ho1UR9XbqHjgtA4RD5R7eNRcgB6gjS+uBczYVWKNhzICOUs=
*/