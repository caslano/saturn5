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
UDXwdIeTmARJkoMUXodyAflBsKYw8FIXsm2sEUpMVa56TPgZRJDMSmLbJMcPjXfIaCFgFruP13mkA3j9pW9lIewAe2iHL2GGuWRFcmxmPE+DIDNhh21Pr56xffs1WVmIE7HPNtu5s1LhRdHYvn+ItdfWfg6VrNcEVv46MQ1tdo8Nu/Zm2G15meEEJZVxJZFmjaN9hHbWW+wo723sHu42ty9flZt3w3YNsXu8W7S3EQC0jd2TcuONDCCpuSHFjD6BOz+rcLOXpmW94Bd/phFqQ5uqRHhdHc0GqFuzMexN+pN81Syoc7vvN6pBTTttVlPUmJCjnUoUEo0Xp0Sbq1uUrGvKLptU1EFhx3OiGSdqJqhzd9pDJjA9S8C1jQ1UXG3FmPT6S8UoruVs5RJrNmSZCsmiouuHMskzWi2WyRqkJ+T4N2VrVhSnYX/s9IZX/+6Pxkj8MeFvb65cxkia3h33BoNipx3S5QPoxE3kmwwDDSFbDMa/ng7OBxPKS+m60QJwBi0ElQ0rI9IJ8AIa6ASWcoFxUQCVb1mww7Wl4c5lbFZq7vy9Q8mcgGOIBjeJVyfi8PbnQ/H0qRkjXnLD8yYVpMP2cxJOjv3ypTLjl6PajF+e8Yxu+2zLjGf1Gc+eNY9pimxzaf2684MKtNr5
*/