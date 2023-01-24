// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INITIALIZE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INITIALIZE_HPP

#include <cstddef>

#include <boost/numeric/conversion/bounds.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{

template <std::size_t Dimension, std::size_t DimensionCount>
struct initialize_loop
{
    template <typename Box, typename CoordinateType>
    static inline void apply(Box& box,
                             CoordinateType min_value,
                             CoordinateType max_value)
    {
        geometry::set<min_corner, Dimension>(box, min_value);
        geometry::set<max_corner, Dimension>(box, max_value);

        initialize_loop
            <
                Dimension + 1, DimensionCount
            >::apply(box, min_value, max_value);
    }
};

template <std::size_t DimensionCount>
struct initialize_loop<DimensionCount, DimensionCount>
{
    template <typename Box, typename CoordinateType>
    static inline void apply(Box&, CoordinateType, CoordinateType)
    {
    }
};


template
<
    typename Box,
    std::size_t Dimension = 0,
    std::size_t DimensionCount = dimension<Box>::value
>
struct initialize
{
    typedef typename coordinate_type<Box>::type coordinate_type;

    static inline void apply(Box& box,
        coordinate_type min_value
            = boost::numeric::bounds<coordinate_type>::highest(),
        coordinate_type max_value
            = boost::numeric::bounds<coordinate_type>::lowest())
    {
        initialize_loop
            <
                Dimension, DimensionCount
            >::apply(box, min_value, max_value);
    }
};

}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INITIALIZE_HPP

/* initialize.hpp
tyfBm+4NrhSwQEwzdEbuH7hzFm3Tc0aG2vdChp4c4nsDnxXb5Upli3o7dpyVY9IegplD4Xq9howyGtozBO3p69OehZ5M9Beqf4PI0xBehRAaCGO4I+EF3IR80GNGQ+AVyqYtju+hO1JmPxzng5/V3038m+KM4GGPwc4TUGL7mPI3YY5okErlUiWu5muljlJnoSvujnvjvrg/nhEPjhyG84IHhIyP7DB5NBheTU04qpoXuAY/8A3BI5jz9nnDUfplw8Mclf+8mQzz4naI/BOEQ95Mju3VzjEvTLhG1gPfJhxwhg+7kZ6CPdxkPMr/Hi/QEdxBob3+xWsU9xtoyTVq6Su4W8pX8mFUFqt+OUeKOrNd+d6Yr9hRjvPcfmeOVOsv8NXgpf5GWNs2SMWohug+HH6/5oMgmX1dDYFyyglfVxkjTDpB4utqLNzAHrbXOgDWeNWITANvfxYk7iHvwBI0d4QxrxEw/ZN250ErmD6F0u/X/9OITANH/0lIHKI0BfHVO4NIfQhHxXUMOV/094sp/OGITAP7lvhiuwI3xHSCHhymZRnAz06Gz1T+sZD4vo/N0eN9Vv3t3TbhDO4G2TkZpcHcR70VmXwQzvHpsihEdkF4AgL37QxDov0fNB0Gkx4NZU7iGfdYMZ8CNT9sfPDw7A4P2prsfxVPFXdJr4jFSkytFefgAoKFzGCaxdwBzr+by0N8xd3wUb1wBT0l
*/