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
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
*/