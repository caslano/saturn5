// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2021.
// Modifications copyright (c) 2013-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_AREAL_HPP

#include <iterator>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/point_on_border.hpp>

#include <boost/geometry/algorithms/detail/disjoint/linear_linear.hpp>
#include <boost/geometry/algorithms/detail/disjoint/linear_segment_or_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/multirange_geometry.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/segment_box.hpp>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{

template <typename Geometry1, typename Geometry2,
          typename Tag1 = typename tag<Geometry1>::type,
          typename Tag1OrMulti = typename tag_cast<Tag1, multi_tag>::type>
struct disjoint_no_intersections_policy
{
    /*!
    \tparam Strategy point_in_geometry strategy
    */
    template <typename Strategy>
    static inline bool apply(Geometry1 const& g1, Geometry2 const& g2, Strategy const& strategy)
    {
        typedef typename point_type<Geometry1>::type point1_type;
        point1_type p;
        geometry::point_on_border(p, g1);

        return ! geometry::covered_by(p, g2, strategy);
    }
};

template <typename Geometry1, typename Geometry2, typename Tag1>
struct disjoint_no_intersections_policy<Geometry1, Geometry2, Tag1, multi_tag>
{
    /*!
    \tparam Strategy point_in_geometry strategy
    */
    template <typename Strategy>
    static inline bool apply(Geometry1 const& g1, Geometry2 const& g2, Strategy const& strategy)
    {
        // TODO: use partition or rtree on g2
        typedef typename boost::range_iterator<Geometry1 const>::type iterator;
        for ( iterator it = boost::begin(g1) ; it != boost::end(g1) ; ++it )
        {
            typedef typename boost::range_value<Geometry1 const>::type value_type;
            if ( ! disjoint_no_intersections_policy<value_type const, Geometry2>
                    ::apply(*it, g2, strategy) )
            {
                return false;
            }
        }
        return true;
    }
};


template<typename Geometry1, typename Geometry2,
         typename NoIntersectionsPolicy
                    = disjoint_no_intersections_policy<Geometry1, Geometry2> >
struct disjoint_linear_areal
{
    /*!
    \tparam Strategy relate (segments intersection) strategy
    */
    template <typename Strategy>
    static inline bool apply(Geometry1 const& g1, Geometry2 const& g2, Strategy const& strategy)
    {
        // if there are intersections - return false
        if ( !disjoint_linear<Geometry1, Geometry2>::apply(g1, g2, strategy) )
        {
            return false;
        }

        return NoIntersectionsPolicy::apply(g1, g2, strategy);
    }
};




template
<
    typename Segment,
    typename Areal,
    typename Tag = typename tag<Areal>::type
>
struct disjoint_segment_areal
    : not_implemented<Segment, Areal>
{};


template <typename Segment, typename Polygon>
class disjoint_segment_areal<Segment, Polygon, polygon_tag>
{
    
    template <typename InteriorRings, typename Strategy>
    static inline
    bool check_interior_rings(InteriorRings const& interior_rings,
                              Segment const& segment,
                              Strategy const& strategy)
    {
        using ring_type = typename boost::range_value<InteriorRings>::type;

        using unary_predicate_type = unary_disjoint_geometry_to_query_geometry
            <
                Segment,
                Strategy,
                disjoint_range_segment_or_box<ring_type, Segment>
            >;

        return std::all_of(boost::begin(interior_rings),
                           boost::end(interior_rings),
                           unary_predicate_type(segment, strategy));
    }


public:
    template <typename IntersectionStrategy>
    static inline bool apply(Segment const& segment,
                             Polygon const& polygon,
                             IntersectionStrategy const& strategy)
    {
        if (! disjoint_range_segment_or_box
                <
                    typename geometry::ring_type<Polygon>::type,
                    Segment
                >::apply(geometry::exterior_ring(polygon), segment, strategy))
        {
            return false;
        }

        if (! check_interior_rings(geometry::interior_rings(polygon), segment, strategy))
        {
            return false;
        }

        typename point_type<Segment>::type p;
        detail::assign_point_from_index<0>(segment, p);

        return ! geometry::covered_by(p, polygon, strategy);
    }
};


template <typename Segment, typename MultiPolygon>
struct disjoint_segment_areal<Segment, MultiPolygon, multi_polygon_tag>
{
    template <typename IntersectionStrategy>
    static inline bool apply(Segment const& segment, MultiPolygon const& multipolygon,
                             IntersectionStrategy const& strategy)
    {
        return multirange_constant_size_geometry
            <
                MultiPolygon, Segment
            >::apply(multipolygon, segment, strategy);
    }
};


template <typename Segment, typename Ring>
struct disjoint_segment_areal<Segment, Ring, ring_tag>
{
    template <typename IntersectionStrategy>
    static inline bool apply(Segment const& segment,
                             Ring const& ring,
                             IntersectionStrategy const& strategy)
    {
        if (! disjoint_range_segment_or_box<Ring, Segment>::apply(ring, segment, strategy))
        {
            return false;
        }

        typename point_type<Segment>::type p;
        detail::assign_point_from_index<0>(segment, p);

        return ! geometry::covered_by(p, ring, strategy);
    }
};


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Linear, typename Areal>
struct disjoint<Linear, Areal, 2, linear_tag, areal_tag, false>
    : public detail::disjoint::disjoint_linear_areal<Linear, Areal>
{};


template <typename Areal, typename Linear>
struct disjoint<Areal, Linear, 2, areal_tag, linear_tag, false>
{
    template <typename Strategy>
    static inline bool apply(Areal const& areal, Linear const& linear,
                             Strategy const& strategy)
    {
        return detail::disjoint::disjoint_linear_areal
            <
                Linear, Areal
            >::apply(linear, areal, strategy);
    }
};


template <typename Areal, typename Segment>
struct disjoint<Areal, Segment, 2, areal_tag, segment_tag, false>
{
    template <typename Strategy>
    static inline bool apply(Areal const& g1, Segment const& g2,
                             Strategy const& strategy)
    {
        return detail::disjoint::disjoint_segment_areal
            <
                Segment, Areal
            >::apply(g2, g1, strategy);
    }
};


template <typename Segment, typename Areal>
struct disjoint<Segment, Areal, 2, segment_tag, areal_tag, false>
    : detail::disjoint::disjoint_segment_areal<Segment, Areal>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_AREAL_HPP

/* linear_areal.hpp
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
*/