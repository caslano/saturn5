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
x/QBPNsXx/I5QxjgHqehwKS8Mg8ZWuyhx+dOTUuXKT8R/HnqbbneUsaTS/HeO7MqgrC/cnbWT204ZhgfXqCFb6G4FWlxKK4huDstUNy1uGsKFGe4FC9Q3N0JFCvuLgnuluCQZHK722632+72y/s/fO7zvM8jH/+dQGOAPOa3yotPkzd8hWg5HBha2rdHOm77yOSGIV/DfWRBOgQ4D3uKNAhGaWYHoVyNVrd+3a2d0iEesYaetg6iF/gfgMwa8Kfjp/xA2AKzifjTzvDm8/7YgcmubcFUUKZp9vpBkldbUHbuDVfwAbk23JytM/8THJbcgGJXjff7NXQh9M6YTzTEy5b1Pi4KH4ts6KzodibClwUpqP0G+AaCtf3gPH1pN3x4WSYWjL/db7ZkR1mdbrFk8NKE0qU3a8iek0WjOnrOLc9MzS0P6iPShAcsqlzhbUE3SkjzJvZomPhC5TgU0EnsQmDqxF9/bhwrUEpwMW3Np1kSlCdJzVdtKsvXnCBPk8RI4NE7uclwxiT+UVhlI/VhPCtjIjvcVPW8S2jmQpOwuvhPIkcfxMujj5VKGecTMl165/6EVb0h8u1ACs8yI376D3+WIkO71t4/BULiQ9VizGtp5dXfPVJI0Xktu6k+vqUpXZsxFTmuGuQDxeDz64ZkwVrREda3SNXn11WvKDeUwApgDdxHDMqiFM+Y2zk6i2o72U7lR2HEawPlqkul
*/