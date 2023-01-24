// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014.
// Modifications copyright (c) 2013, 2014, Oracle and/or its affiliates.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_RANGE_BY_SECTION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_RANGE_BY_SECTION_HPP

#include <boost/mpl/assert.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
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
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_OR_NOT_YET_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
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
TyDejwaF+XCzSTaZ3LQ9/DVzqPlDRfYwhv9MydbuFe5xNzu1CBhzKNHYjfT78462i6WJezFqNdp9Eeaca5QEtjoWneAb4II9BV102JjMSXEA+6/c8n2uXA2NyEUyh2nd0vLaCkqETnhrT36QZv1F2vkjZoT+8XdukL7Ly2qBSr3nFrxzibeiYNSfR5nNdfk87ECN636SrmQ+r2Hvjrprus9LvuUlISnPoYWdLcdTP8fWESqBGnNpzZFkuQ4gM591M2OzZ1lWc/0ssrgV/uc9x8huuQGNYxaq2us4Hr57koFvuByjF+cxmIDhYjp9DWXqZMs/dDkFidRJQkG8i4pbuJ/+6EBP5qZZXXOVpXdS6Q9ONMxqkPncEDIcha16A/+mY7NyCnog4nBC3Wr20siTN0UC0AIRE9qydrbbIazBZbc0buk8HrAS2hyMTtDqfBclDaR+iOKaZOl9XORAND6OPDdvF0ef41ykfDb1POVBb8m02NuTHy8/RWnL4BL/XLJUG66/QjquOPmGiemesFpD8GvupyX4PrZZXKuNROF08A745J9WE02avoQwtTDn4j+UuPO1ubxGm3jcPvgEWOjrl2H/GSezgSUWz4baHOp4+yL7GHRIJEw4StkAs3PRr0SGvhtiZoLxDsBQR2EgROoD3Mdr2VZt5fBcq7tmQyH9leb19tUjmptt9uyZ53pJAeExmtz4P0RPA5MyQK/D
*/