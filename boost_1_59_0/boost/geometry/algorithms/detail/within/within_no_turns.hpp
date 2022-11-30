// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2013.
// Modifications copyright (c) 2013, Oracle and/or its affiliates.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_WITHIN_NO_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_WITHIN_NO_TURNS_HPP

#include <boost/geometry/algorithms/detail/point_on_border.hpp>
#include <boost/geometry/algorithms/detail/within/point_in_geometry.hpp>

namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DETAIL
namespace detail_dispatch { namespace within {

// returns true if G1 is within G2
// this function should be called only if there are no intersection points
// otherwise it may return invalid result
// e.g. when non-first point of G1 is outside G2 or when some rings of G1 are the same as rings of G2

template <typename Geometry1,
          typename Geometry2,
          typename Tag1 = typename geometry::tag<Geometry1>::type,
          typename Tag2 = typename geometry::tag<Geometry2>::type>
struct within_no_turns
{
    template <typename Strategy> static inline
    bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        typedef typename geometry::point_type<Geometry1>::type point1_type;
        point1_type p;
        if ( !geometry::point_on_border(p, geometry1) )
            return false;

        return detail::within::point_in_geometry(p, geometry2, strategy) >= 0;
    }
};

template <typename Geometry1, typename Geometry2>
struct within_no_turns<Geometry1, Geometry2, ring_tag, polygon_tag>
{
    template <typename Strategy> static inline
    bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        typedef typename geometry::point_type<Geometry1>::type point1_type;
        typedef typename geometry::point_type<Geometry2>::type point2_type;
        point1_type p;
        if ( !geometry::point_on_border(p, geometry1) )
            return false;
        // check if one of ring points is outside the polygon
        if ( detail::within::point_in_geometry(p, geometry2, strategy) < 0 )
            return false;
        // Now check if holes of G2 aren't inside G1
        typedef typename boost::range_const_iterator
            <
                typename geometry::interior_type<Geometry2>::type
            >::type iterator;
        for ( iterator it = boost::begin(geometry::interior_rings(geometry2)) ;
              it != boost::end(geometry::interior_rings(geometry2)) ;
              ++it )
        {
            point2_type p;
            if ( !geometry::point_on_border(p, *it) )
                return false;
            if ( detail::within::point_in_geometry(p, geometry1, strategy) > 0 )
                return false;
        }
        return true;
    }
};

template <typename Geometry1, typename Geometry2>
struct within_no_turns<Geometry1, Geometry2, polygon_tag, polygon_tag>
{
    template <typename Strategy> static inline
    bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        typedef typename geometry::point_type<Geometry1>::type point1_type;
        typedef typename geometry::point_type<Geometry2>::type point2_type;
        point1_type p;
        if ( !geometry::point_on_border(p, geometry1) )
            return false;
        // check if one of ring points is outside the polygon
        if ( detail::within::point_in_geometry(p, geometry2, strategy) < 0 )
            return false;
        // Now check if holes of G2 aren't inside G1
        typedef typename boost::range_const_iterator
            <
                typename geometry::interior_type<Geometry2>::type
            >::type iterator2;
        for ( iterator2 it = boost::begin(geometry::interior_rings(geometry2)) ;
              it != boost::end(geometry::interior_rings(geometry2)) ;
              ++it )
        {
            point2_type p2;
            if ( !geometry::point_on_border(p2, *it) )
                return false;
            // if the hole of G2 is inside G1
            if ( detail::within::point_in_geometry(p2, geometry1, strategy) > 0 )
            {
                // if it's also inside one of the G1 holes, it's ok
                bool ok = false;
                typedef typename boost::range_const_iterator
                    <
                        typename geometry::interior_type<Geometry1>::type
                    >::type iterator1;
                for ( iterator1 it1 = boost::begin(geometry::interior_rings(geometry1)) ;
                      it1 != boost::end(geometry::interior_rings(geometry1)) ;
                      ++it1 )
                {
                    if ( detail::within::point_in_geometry(p2, *it1, strategy) < 0 )
                    {
                        ok = true;
                        break;
                    }
                }
                if ( !ok )
                    return false;
            }
        }
        return true;
    }
};

template <typename Geometry1,
          typename Geometry2,
          typename Tag1 = typename geometry::tag<Geometry1>::type,
          typename Tag2 = typename geometry::tag<Geometry2>::type,
          bool IsMulti1 = boost::is_base_of<geometry::multi_tag, Tag1>::value,
          bool IsMulti2 = boost::is_base_of<geometry::multi_tag, Tag2>::value>
struct within_no_turns_multi
{
    template <typename Strategy> static inline
    bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        return within_no_turns<Geometry1, Geometry2>::apply(geometry1, geometry2, strategy);
    }
};

template <typename Geometry1, typename Geometry2, typename Tag1, typename Tag2>
struct within_no_turns_multi<Geometry1, Geometry2, Tag1, Tag2, true, false>
{
    template <typename Strategy> static inline
    bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        // All values of G1 must be inside G2
        typedef typename boost::range_value<Geometry1>::type subgeometry1;
        typedef typename boost::range_const_iterator<Geometry1>::type iterator;
        for ( iterator it = boost::begin(geometry1) ; it != boost::end(geometry1) ; ++it )
        {
            if ( !within_no_turns<subgeometry1, Geometry2>::apply(*it, geometry2, strategy) )
                return false;
        }
        return true;
    }
};

template <typename Geometry1, typename Geometry2, typename Tag1, typename Tag2>
struct within_no_turns_multi<Geometry1, Geometry2, Tag1, Tag2, false, true>
{
    template <typename Strategy> static inline
    bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        // G1 must be within at least one value of G2
        typedef typename boost::range_value<Geometry2>::type subgeometry2;
        typedef typename boost::range_const_iterator<Geometry2>::type iterator;
        for ( iterator it = boost::begin(geometry2) ; it != boost::end(geometry2) ; ++it )
        {
            if ( within_no_turns<Geometry1, subgeometry2>::apply(geometry1, *it, strategy) )
                return true;
        }
        return false;
    }
};

template <typename Geometry1, typename Geometry2, typename Tag1, typename Tag2>
struct within_no_turns_multi<Geometry1, Geometry2, Tag1, Tag2, true, true>
{
    template <typename Strategy> static inline
    bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        // each value of G1 must be inside at least one value of G2
        typedef typename boost::range_value<Geometry1>::type subgeometry1;
        typedef typename boost::range_const_iterator<Geometry1>::type iterator;
        for ( iterator it = boost::begin(geometry1) ; it != boost::end(geometry1) ; ++it )
        {
            if ( !within_no_turns_multi<subgeometry1, Geometry2>::apply(*it, geometry2, strategy) )
                return false;
        }
        return true;
    }
};

}} // namespace detail_dispatch::within

namespace detail { namespace within {

template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool within_no_turns(Geometry1 const& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
{
    return detail_dispatch::within::within_no_turns_multi<Geometry1, Geometry2>::apply(geometry1, geometry2, strategy);
}

}} // namespace detail::within
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_WITHIN_NO_TURNS_HPP

/* within_no_turns.hpp
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
*/