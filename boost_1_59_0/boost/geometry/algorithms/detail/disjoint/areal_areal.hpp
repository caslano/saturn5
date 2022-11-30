// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_AREAL_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_AREAL_AREAL_HPP

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/detail/for_each_range.hpp>
#include <boost/geometry/algorithms/detail/point_on_border.hpp>

#include <boost/geometry/algorithms/detail/disjoint/linear_linear.hpp>
#include <boost/geometry/algorithms/detail/disjoint/segment_box.hpp>

#include <boost/geometry/algorithms/for_each.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{

template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool point_on_border_covered_by(Geometry1 const& geometry1,
                                       Geometry2 const& geometry2,
                                       Strategy const& strategy)
{
    typename geometry::point_type<Geometry1>::type pt;
    return geometry::point_on_border(pt, geometry1)
        && geometry::covered_by(pt, geometry2, strategy);
}


/*!
\tparam Strategy point_in_geometry strategy
*/
template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool rings_containing(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
{
    return geometry::detail::any_range_of(geometry2, [&](auto const& range)
    {
        return point_on_border_covered_by(range, geometry1, strategy);
    });
}



template <typename Geometry1, typename Geometry2>
struct areal_areal
{
    /*!
    \tparam Strategy relate (segments intersection) strategy
    */
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        if ( ! disjoint_linear<Geometry1, Geometry2>::apply(geometry1, geometry2, strategy) )
        {
            return false;
        }

        // If there is no intersection of segments, they might located
        // inside each other

        // We check that using a point on the border (external boundary),
        // and see if that is contained in the other geometry. And vice versa.

        if ( rings_containing(geometry1, geometry2, strategy)
          || rings_containing(geometry2, geometry1, strategy) )
        {
            return false;
        }

        return true;
    }
};


template <typename Areal, typename Box>
struct areal_box
{
    /*!
    \tparam Strategy relate (segments intersection) strategy
    */
    template <typename Strategy>
    static inline bool apply(Areal const& areal,
                             Box const& box,
                             Strategy const& strategy)
    {
        if (! geometry::all_segments_of(areal, [&](auto const& s)
              {
                  return disjoint_segment_box::apply(s, box, strategy);
              }) )
        {
            return false;
        }

        // If there is no intersection of any segment and box,
        // the box might be located inside areal geometry

        if ( point_on_border_covered_by(box, areal, strategy) )
        {
            return false;
        }

        return true;
    }
};


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Areal1, typename Areal2>
struct disjoint<Areal1, Areal2, 2, areal_tag, areal_tag, false>
    : detail::disjoint::areal_areal<Areal1, Areal2>
{};


template <typename Areal, typename Box>
struct disjoint<Areal, Box, 2, areal_tag, box_tag, false>
    : detail::disjoint::areal_box<Areal, Box>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_AREAL_AREAL_HPP

/* areal_areal.hpp
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
*/