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

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_AREAL_HPP

#include <iterator>

#include <boost/range.hpp>

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
#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>
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

        return !geometry::covered_by(p, g2, strategy);
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

        return NoIntersectionsPolicy
                ::apply(g1, g2,
                        strategy.template get_point_in_geometry_strategy<Geometry1, Geometry2>());
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
private:
    template <typename InteriorRings, typename Strategy>
    static inline
    bool check_interior_rings(InteriorRings const& interior_rings,
                              Segment const& segment,
                              Strategy const& strategy)
    {
        typedef typename boost::range_value<InteriorRings>::type ring_type;

        typedef unary_disjoint_geometry_to_query_geometry
            <
                Segment,
                Strategy,
                disjoint_range_segment_or_box
                    <
                        ring_type, closure<ring_type>::value, Segment
                    >
            > unary_predicate_type;
                
        return check_iterator_range
            <
                unary_predicate_type
            >::apply(boost::begin(interior_rings),
                     boost::end(interior_rings),
                     unary_predicate_type(segment, strategy));
    }


public:
    template <typename IntersectionStrategy>
    static inline bool apply(Segment const& segment,
                             Polygon const& polygon,
                             IntersectionStrategy const& strategy)
    {
        typedef typename geometry::ring_type<Polygon>::type ring;

        if ( !disjoint_range_segment_or_box
                 <
                     ring, closure<Polygon>::value, Segment
                 >::apply(geometry::exterior_ring(polygon), segment, strategy) )
        {
            return false;
        }

        if ( !check_interior_rings(geometry::interior_rings(polygon), segment, strategy) )
        {
            return false;
        }

        typename point_type<Segment>::type p;
        detail::assign_point_from_index<0>(segment, p);

        return !geometry::covered_by(p, polygon,
                    strategy.template get_point_in_geometry_strategy<Segment, Polygon>());
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
        if ( !disjoint_range_segment_or_box
                 <
                     Ring, closure<Ring>::value, Segment
                 >::apply(ring, segment, strategy) )
        {
            return false;
        }

        typename point_type<Segment>::type p;
        detail::assign_point_from_index<0>(segment, p);

        return !geometry::covered_by(p, ring,
                    strategy.template get_point_in_geometry_strategy<Segment, Ring>());
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