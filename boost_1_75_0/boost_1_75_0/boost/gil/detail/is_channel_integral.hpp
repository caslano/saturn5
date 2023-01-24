//
// Copyright 2019 Mateusz Loskot <mateusz at loskot dot net>
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_DETAIL_IS_CHANNEL_INTEGRAL_HPP
#define BOOST_GIL_DETAIL_IS_CHANNEL_INTEGRAL_HPP

#include <boost/gil/channel.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template <typename ChannelValue>
struct is_channel_integral : std::is_integral<ChannelValue> {};

template <int NumBits>
struct is_channel_integral<boost::gil::packed_channel_value<NumBits>> : std::true_type {};

template <typename BitField, int FirstBit, int NumBits, bool IsMutable>
struct is_channel_integral
    <
        boost::gil::packed_channel_reference<BitField, FirstBit, NumBits, IsMutable>
    > : std::true_type
{};

template <typename BitField, int NumBits, bool IsMutable>
struct is_channel_integral
    <
        boost::gil::packed_dynamic_channel_reference<BitField, NumBits, IsMutable>
    > : std::true_type
{};

template <typename BaseChannelValue, typename MinVal, typename MaxVal>
struct is_channel_integral
    <
        boost::gil::scoped_channel_value<BaseChannelValue, MinVal, MaxVal>
    > : std::is_integral<BaseChannelValue>
{};

}}} //namespace boost::gil::detail

#endif

/* is_channel_integral.hpp
tqD6MWNiA55y0N+p9kUsHaya/lTJ4s41WNbiDovVShfHSY5lwB32PKTZvd1rQUw8nPZ0d03w+eXF2rcASrp3zL+ERBAzzYlqgw1+e1W1XQEoAZDzXnRxZQDZcDs9vQ9EY9VhIPXPnz125y1Cf6vX3p04zhSd0rYMbwc6bs9HI8vkW6RNq1E1mKX7/oDezkzQqM1NaAoB4t2ZicO6rbm6+Uo716WRTsptE9t2vcG3shEMez7D7U5grz/3D9GkR0ejd1FchXSwfFcB9SdeTpTkpM0nD/BfboxLTrP47TdE1hq/T16Dw690j0g1K41Vgep+56zXGZPJbaAjeK7TPFrIpyRfX2D4ZPbKCSkQWx3GhC+lCNAq4zCg2GdiRhKFh8p2hLCazunlGhv4ZFdIXxxkT7/0JxKS2rq3rMFQkyU7lS0Qd1gpJxjwzf9ZaGYWX/Bg2AIM1vmh+eZTMlTzk53Ht185blYl+QoNi8QZ8odJNZTcqo/a4x/bV35XKOdCuehQHlnGODwf7W4WJBNjSJwF/H6amucyFoEBhoTX2PIQDdXaVxE9p3DnZCnEYLAYpQJcjzc/X0hS09sIXC1tHrTrKKOjr/TqMoCO4Bs/wBr7cnTKNsBefWEUMRQfYNb6zmW7L46kmupTZ53ZCnzdafwHn+DjGD4j+veA/SUW82UXkYgxfsBxi/KWxO14UmfN+SlZ6VgTTskPveHEPryf
*/