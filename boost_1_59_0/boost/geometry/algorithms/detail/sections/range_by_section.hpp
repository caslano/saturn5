// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_RANGE_BY_SECTION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_RANGE_BY_SECTION_HPP

#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace section
{


template <typename Range, typename Section>
struct full_section_range
{
    static inline Range const& apply(Range const& range, Section const& )
    {
        return range;
    }
};


template <typename Polygon, typename Section>
struct full_section_polygon
{
    static inline typename ring_return_type<Polygon const>::type apply(Polygon const& polygon, Section const& section)
    {
        return section.ring_id.ring_index < 0
            ? geometry::exterior_ring(polygon)
            : range::at(geometry::interior_rings(polygon),
                        static_cast<std::size_t>(section.ring_id.ring_index));
    }
};


template
<
    typename MultiGeometry,
    typename Section,
    typename Policy
>
struct full_section_multi
{
    static inline typename ring_return_type<MultiGeometry const>::type apply(
                MultiGeometry const& multi, Section const& section)
    {
        typedef typename boost::range_size<MultiGeometry>::type size_type;

        BOOST_GEOMETRY_ASSERT
            (
                section.ring_id.multi_index >= 0
                && size_type(section.ring_id.multi_index) < boost::size(multi)
            );

        return Policy::apply(range::at(multi, size_type(section.ring_id.multi_index)), section);
    }
};


}} // namespace detail::section
#endif


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Tag,
    typename Geometry,
    typename Section
>
struct range_by_section
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not or not yet implemented for this Geometry type.",
        Tag, Geometry, Section);
};


template <typename LineString, typename Section>
struct range_by_section<linestring_tag, LineString, Section>
    : detail::section::full_section_range<LineString, Section>
{};


template <typename Ring, typename Section>
struct range_by_section<ring_tag, Ring, Section>
    : detail::section::full_section_range<Ring, Section>
{};


template <typename Polygon, typename Section>
struct range_by_section<polygon_tag, Polygon, Section>
    : detail::section::full_section_polygon<Polygon, Section>
{};


template <typename MultiPolygon, typename Section>
struct range_by_section<multi_polygon_tag, MultiPolygon, Section>
    : detail::section::full_section_multi
        <
            MultiPolygon,
            Section,
            detail::section::full_section_polygon
                <
                    typename boost::range_value<MultiPolygon>::type,
                    Section
                >
       >
{};

template <typename MultiLinestring, typename Section>
struct range_by_section<multi_linestring_tag, MultiLinestring, Section>
    : detail::section::full_section_multi
        <
            MultiLinestring,
            Section,
            detail::section::full_section_range
                <
                    typename boost::range_value<MultiLinestring>::type,
                    Section
                >
       >
{};


} // namespace dispatch
#endif


/*!
    \brief Get full ring (exterior, one of interiors, one from multi)
        indicated by the specified section
    \ingroup sectionalize
    \tparam Geometry type
    \tparam Section type of section to get from
    \param geometry geometry to take section of
    \param section structure with section
 */
template <typename Geometry, typename Section>
inline typename ring_return_type<Geometry const>::type
            range_by_section(Geometry const& geometry, Section const& section)
{
    concepts::check<Geometry const>();

    return dispatch::range_by_section
        <
            typename tag<Geometry>::type,
            Geometry,
            Section
        >::apply(geometry, section);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_RANGE_BY_SECTION_HPP

/* range_by_section.hpp
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
*/