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
RFwuxfC5iPH/hHrOrHwSpfqlZtbMXOQu/xPiFsYyjEBY5XEFd0FixVf1usAAGU2JGqijBbP0I6I3EDWLWzv2TI5yyZGcrj++6pv4U3GKn6KzOiFcxVRG+Py6/U1tEmvDBue6g5oMAjqHBa0peg/mf29h0uRkPE2Tm7L0TihFtM9u0Cy1PFEmm+rMPLS05SQesB7gCEPwgC9ysbxewRkIdbATDGifqgQbvLOCh3VhwrFwtC0TYDdtNydYD7EGGBzb2EDwWklBSvkbZROqwczGiWbUEKK1s53ZRzaVodI5zJbzmj8DExl5HTU4Kq40v2trynEdhp2wmyYv5uzr1GsK4CvNaboKCplRl2/JdPinEjzyHUJTfCDD1HRMmHY+3nr/ZEc1h0h8t+SWg7GSpiNjw91v6AgsVRPiDwLdQRpmQRkBhXl+S8EzQSZFtCNi7F0Qo0vK67habYfGhnri4XooRia6SdqFJV7SILjwDln42FCJm33Nw08h5elLOEFK0fBXRpF6h+jyUARXdw7l6dsMgSs5e/M3TwP/f6Ogegx4N1Q6RA6kIhbVvoIlZg==
*/