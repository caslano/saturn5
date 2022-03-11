// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_UNIQUE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_UNIQUE_HPP

#include <algorithm>

#include <boost/range.hpp>
#include <boost/type_traits/remove_reference.hpp>

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