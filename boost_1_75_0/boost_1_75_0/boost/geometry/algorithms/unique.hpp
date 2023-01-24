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
SD9YFUIehYOPlQozr4TZ9qfZGvUlu7bPxOzvqxi2cDUbHpNU7VvwR9eNO+APNtzfo3/6cqe9u+RsdLGHkM+0ZGVkm7Ka1l0ZSVFN+3eVbHSnktOOL5CJUoV8QJmtTlYajcXSGFjVxjNhTJEaMIqk5ciJg9y4Sshh1gDRIjWTNTiCU8hr9pj3HV5F5TU7YGNE3cVyeWuV4JE+AOIbSNHV5rmlna/T7fmLWBvsIhLwZvBfOLn4Vyc/unktfM6ZdFPdMbtnNnpAcr+OgceTz0qV7JNKKCBp13pWrRb1nAZEm0TruRQjO6+uJ3n1xtU2Xv0RyDyxmvMCm1Y7p8FdRLuKKUqEjVe/rQfwP7koMy3I/ZjEt19YLeI6XQGi/5oQumNN0maaHw1Tmkl32MxfxWmxaTqzHx24xqmsGN7LWI+lx+U9ylCiZxFUxQ/vbKzm9EBGTV9kAP9oQJ+YcsU5a0R/LATil5D2rzH3zbaEsGrlJznLF6Wd75uPWm9vfgm64ajqfwGOk3G5UClUr0jKDuiLKr5pwsSrMX1ghyJfPI58abEuMs7PocAfUhln+s9D6OeQHoMU4yinQsZ5wvTZpZnppIgcS6PyG9E0tCGFEXA7j55xjgvFbA+F+EPCf3SEy/7QCS52qi6g5hztM1pfgOu9mN5+giyRMY5E/+fnlqatVs1G4wLF7+K/SSXyAqVRbdSGYyPf/aanxLvAt8Df
*/