// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_BOX_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>
#include <boost/geometry/strategies/disjoint.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


/*!
    \brief Internal utility function to detect if point/box are disjoint
 */
template <typename Point, typename Box, typename Strategy>
inline bool disjoint_point_box(Point const& point, Box const& box, Strategy const& )
{
    // ! covered_by(point, box)
    return ! Strategy::apply(point, box);
}


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Point, typename Box, std::size_t DimensionCount>
struct disjoint<Point, Box, DimensionCount, point_tag, box_tag, false>
{
    template <typename Strategy>
    static inline bool apply(Point const& point, Box const& box, Strategy const& )
    {
        // ! covered_by(point, box)
        return ! Strategy::apply(point, box);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_BOX_HPP

/* point_box.hpp
2r3WnQ8MbgTqrcaexmOloBxT5qgb9GU4ApurXA0oY2hQoz4Ea2OMddpUFFN0PUgDhpkPBJxBFgJVeh0RY33jl+Iceh8qA/eF0bB95j4RPrycj9thd99sE5YbHrf+pX2p8XUuhfG93z/wMT4nD8FKARwvxdqtRG2HrUJjwStZXnKG5TgoA2k77VIkH8/8fYLO0HXYAo0H93FdyJp9Tjpzu0tLw7icJHA1SvLgQ063BjjjH/fZsJvPQuNvor9X9jk3yitYO48LRXceHsvYxxi9j9vGOBgaX3+c9zn0cecYT7m0t3EViHXjOapEH3qamY/bxrgAGveJ/u553DnGQS7tCPRXhivQNHOMFNPrDUeeqquM/j0u6MWT/wv7GRp/oX1hRT37uPPwuzPDewKfllcp29UZQFWrSRgtIh7FUAO92hDd+230LASNov2cng3Z7xzri9JVATHdq5/Y5P22Z74TGnP382e+VhJCKs2G4RaRqD3j/LfsF76Vs9tCaAc0pDm4iOT2jn9tH+/wv8Ia2M/wvpuRDxenaKHzGdHxEPsNt9H40fXxgeh62Od2G43/VyJe79pzITQEGjf/io5f04f9yjqxpvkorxW9gJOkXKqTh2NpqTLCpS3XG7WpygzgvqrRVJZdtlbSQVALaDpfH+ec62P1r4StZDNU/gjlzV+l8H3bbRkIRZLTaZbeUvgO27UtLQzd92XbKBkOihob
*/