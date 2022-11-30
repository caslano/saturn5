// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISJOINT_BOX_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISJOINT_BOX_BOX_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/disjoint.hpp>


namespace boost { namespace geometry { namespace strategy { namespace disjoint
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template
<
    typename Box1, typename Box2,
    std::size_t Dimension = 0,
    std::size_t DimensionCount = dimension<Box1>::value
>
struct box_box
{
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        if (get<max_corner, Dimension>(box1) < get<min_corner, Dimension>(box2))
        {
            return true;
        }
        if (get<min_corner, Dimension>(box1) > get<max_corner, Dimension>(box2))
        {
            return true;
        }
        return box_box
            <
                Box1, Box2,
                Dimension + 1, DimensionCount
            >::apply(box1, box2);
    }
};


template <typename Box1, typename Box2, std::size_t DimensionCount>
struct box_box<Box1, Box2, DimensionCount, DimensionCount>
{
    static inline bool apply(Box1 const& , Box2 const& )
    {
        return false;
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


struct cartesian_box_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return detail::box_box<Box1, Box2>::apply(box1, box2);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


namespace services
{

template <typename Box1, typename Box2, int TopDim1, int TopDim2>
struct default_strategy<Box1, Box2, box_tag, box_tag, TopDim1, TopDim2, cartesian_tag, cartesian_tag>
{
    typedef disjoint::cartesian_box_box type;
};


} // namespace services


#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}}}} // namespace boost::geometry::strategy::disjoint


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISJOINT_BOX_BOX_HPP

/* disjoint_box_box.hpp
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
*/