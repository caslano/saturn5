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
hjd3lCaO4HGjJBhO5VGMCWaCLU4ch5liS6y7/IlNEzaVTHVrJvBjNuXg8QQM3jRsqOqg2cA/FLxpnkeYGldiPO6P9vdDG2jh+k2tdcTjaPbD8XU7E2w3TAFzYbHBZ95CNZRrRzl4wObdvdIJszQlo5BxglqCOhhOHxs8bks41hEvsamtx1ArnQ72K306cFeNGhbaPCAHjR7EjhItpYDLrG8ZTQSf4PZ59RnhPZOLZ3jNs9revnkJg+i5FcifS8r9NJKhrMAYDmLbeMKm1/FNSyxBkvJ+OHFjbesb9wyAOJcDHTsfxClINQrY4sMzfMjkguUgzoA645xUv0xp7Tr9g/RZnfZhJSIFYzBpggI+LIkn1nJ2DAAe0zhcKNsI3T7VU5zPXFmSUOH9sLjZ0v2t2szEItAiHsXBXc7eHTvPTOazGImPivqD098O1HN6HOJvP/fJ2hVeDtRwvlwB1ntAvhUXDpwWgqEb114BxOsVTITkj0DBUM8Q8Bg3EMAoWKGhFIB8KsMIdBbO+EATGcGzBXIOULcAxorJIBkyNFK+YA4JJ/a0yZeBjLoALZx1gi2E2zUu9Hpfo8nN9YFay83NLzd6E6g2N/mo6DYH1eOBpDD6embK/gWjcIj5ZgoTaRLDlO1D0kXa1EvHpmix
*/