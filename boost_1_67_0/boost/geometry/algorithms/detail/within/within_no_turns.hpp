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