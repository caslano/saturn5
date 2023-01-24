// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISJOINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISJOINT_HPP

#include <cstddef>

#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/reverse_dispatch.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry1, typename Geometry2,
    std::size_t DimensionCount = dimension<Geometry1>::type::value,
    typename Tag1 = typename tag_cast
        <
            typename tag<Geometry1>::type,
            segment_tag, box_tag, linear_tag, areal_tag
        >::type,
    typename Tag2 = typename tag_cast
        <
            typename tag<Geometry2>::type,
            segment_tag, box_tag, linear_tag, areal_tag
        >::type,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct disjoint
    : not_implemented<Geometry1, Geometry2>
{};


// If reversal is needed, perform it
template
<
    typename Geometry1, typename Geometry2,
    std::size_t DimensionCount,
    typename Tag1, typename Tag2
>
struct disjoint<Geometry1, Geometry2, DimensionCount, Tag1, Tag2, true>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& g1, Geometry2 const& g2, Strategy const& strategy)
    {
        return disjoint
            <
                Geometry2, Geometry1,
                DimensionCount,
                Tag2, Tag1
            >::apply(g2, g1, strategy);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISJOINT_HPP

/* disjoint.hpp
YaSZlRuHqWiSUtztWL40Te5uBejFIM/KicV7vyoPpTou5VX6sQdK0G53I4pzzcochQigAII+nIi4ku9zdTtDifGx1gHykX6p6MVpdmjI3punoRkMq9eWA79fJYhbXe6pEZgGu25Fru2/e6IsEZyl9PFENAMReB/65ebIqTwH1J6mt1SWe10aK7RtIJNd4TzWahLVBfKCzgU7PBTBM4uLqnlELCsuO4d1Z3eX3znVpcK2X7p3wT0RFa1MDw9RK8CvOfVkFj6LcJG7GdDhtLcPsIHMK1fJwtL1NLL8rojWXWX8VcIgFh1ew3x2rQOxqQym2JInl0QXtzg85OQqGyJjlRtvHIKIL5kPqZYDj0giuScC9PcwJXeZZ/7Geez9uKJ7xnjJc4XTSypjIXGZLo5mOV//TGHP47DEQ8mb8lJv+aJLCu8bfkkf9eCbchBV5GV07z9wZ68CTQCH+xXZdEj88Rt46U0Qzc63RRTaggKX8IfhkZmM5VwEqfoFeZe7W/oqqfokLDE8BE/Jh4YwLyXcW84lSW2iGHKPATb8FIimd7+wnaRVT8qNfZBOMcScH/1ABKrgL6O8inwXQLHGfFH6kKFdwJx8cW0GlRNUIfVpjfUwgN0yjHQI0SO3XezF7Ba4XfvqFPVANmSDDk5LULvSOqroocCAd8j7GRZFbK5vyXyGKeWuSeRfkK24E8W0RDX0MeqgnnLlDP3GOrC7
*/