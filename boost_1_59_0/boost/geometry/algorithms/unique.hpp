// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_UNIQUE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_UNIQUE_HPP

#include <algorithm>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/policies/compare.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace unique
{


struct range_unique
{
    template <typename Range, typename ComparePolicy>
    static inline void apply(Range& range, ComparePolicy const& policy)
    {
        typename boost::range_iterator<Range>::type it
            = std::unique
                (
                    boost::begin(range),
                    boost::end(range),
                    policy
                );

        traits::resize<Range>::apply(range, it - boost::begin(range));
    }
};


struct polygon_unique
{
    template <typename Polygon, typename ComparePolicy>
    static inline void apply(Polygon& polygon, ComparePolicy const& policy)
    {
        range_unique::apply(exterior_ring(polygon), policy);

        typename interior_return_type<Polygon>::type
            rings = interior_rings(polygon);

        for (typename detail::interior_iterator<Polygon>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            range_unique::apply(*it, policy);
        }
    }
};


template <typename Policy>
struct multi_unique
{
    template <typename MultiGeometry, typename ComparePolicy>
    static inline void apply(MultiGeometry& multi, ComparePolicy const& compare)
    {
        for (typename boost::range_iterator<MultiGeometry>::type
                it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, compare);
        }
    }
};


}} // namespace detail::unique
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct unique
{
    template <typename ComparePolicy>
    static inline void apply(Geometry&, ComparePolicy const& )
    {}
};


template <typename Ring>
struct unique<Ring, ring_tag>
    : detail::unique::range_unique
{};


template <typename LineString>
struct unique<LineString, linestring_tag>
    : detail::unique::range_unique
{};


template <typename Polygon>
struct unique<Polygon, polygon_tag>
    : detail::unique::polygon_unique
{};


// For points, unique is not applicable and does nothing
// (Note that it is not "spatially unique" but that it removes duplicate coordinates,
//  like std::unique does). Spatially unique is "dissolve" which can (or will be)
//  possible for multi-points as well, removing points at the same location.


template <typename MultiLineString>
struct unique<MultiLineString, multi_linestring_tag>
    : detail::unique::multi_unique<detail::unique::range_unique>
{};


template <typename MultiPolygon>
struct unique<MultiPolygon, multi_polygon_tag>
    : detail::unique::multi_unique<detail::unique::polygon_unique>
{};


} // namespace dispatch
#endif


/*!
\brief \brief_calc{minimal set}
\ingroup unique
\details \details_calc{unique,minimal set (where duplicate consecutive points are removed)}.
\tparam Geometry \tparam_geometry
\param geometry \param_geometry which will be made unique

\qbk{[include reference/algorithms/unique.qbk]}
*/
template <typename Geometry>
inline void unique(Geometry& geometry)
{
    concepts::check<Geometry>();

    // Default strategy is the default point-comparison policy
    typedef geometry::equal_to
        <
            typename geometry::point_type<Geometry>::type
        > policy;


    dispatch::unique<Geometry>::apply(geometry, policy());
}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_UNIQUE_HPP

/* unique.hpp
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
*/