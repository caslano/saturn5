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
mF0Qc3kjx5lY4l7lRPSj7iO3R4oCaC4yKv7DMpNZRTb2OnzxgB86HtZJsk/DpO6YOjcFqw8+vxEWADrFVAOMjoOLbK7a1aqLsnXHg90wJtKUlwRJ+iIj4I7EbZcx9kvIlpIhB0e6YgRp26AWLzsLjsI+d/xqZJ0NFkPr1ZMAQxTE3NLiB6NzbKNzJU3OCKyCpuO59DJ9iTtRkilRjauYbYLVyeXcLvKffGzLdzbscWbZuf+/CHIpDchXbbUL2/HkJlS837iCHlRXBNjOnWoFRVT6Mvo9/QX3Muaa00W8EjUcd/QnqfNc/T0LkQhCemHKYnl7MR02/s0AERKP5+RNtV4WMLZXke837PpY4muUr1s2AGTaEIJ7CRXYJZuV9eOp9RPIJQ+oAulz9k6Fg1oZ3KQQ4veyHq5Sc32Ol2PzobTfHQBJZ+T3CEQrQCZ6ey5yQ4pewybndPzr8u3ATiOi1FUsctmGquzsEoPWocqtTBC6qPnJhCz/So8k5Zw1hAVJCbPJa7mrlZYLBhxnBZ3YHCGKBVRSz8t31er1RmqnJkSJRqeTwqN88NQeMQ==
*/