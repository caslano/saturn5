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
tlNOKhzZXrD6zZFGGYwlo91C5kwa7+iPzde0qEakQNh8iY/SBag7AEqCuMN6oS7FigbKRjIDWcKlUhmHq+VAfZg7VGVNmmur/QWPJP7ZZl0SE+vQIbaIbfQRzrX4I9J7jsqYGR6jyp4GpgeLxBG/07q4Tg7Z/gAcrxbW5KTJ6T5zkwqG49Sad1gsaTbAL9SdOYiZ3LuM3hcokyzZQAS5dY5M3U+zeVgMBgOLBbSeny9jP1KpH0Zq7wEHrNUCw/wdayAPWDTQD1sXTVi0KEExSyj9F7ZR+iOKBT+gtwVSLTpnJCWPRa6lItfQsSndyjY5OkM0kfvXdp/cHL8S5L7OXCfTm/egJ5T2oMZjg5m6bG2JYp5HM6Uiyen40Bkwi38lG72/avTUWR5PQ8rOfVSrkvfu1EdLw7KPonXoo+fJ5GrVCJ8p+NU56qt4chW5j8W6id9xKEkz0l+dhY+v94f539mU1E5LIVM9oU8Jw/FYCdSoSvWwYMyiexRhAkK5WchJulkgORzc/pK1xqwP2DWFazmrK8tNKyCHWSsRKWeYuf21CaFKfxbbX6nhE///heyZQm5Jv5L9OdPaVmtPd4pwdjI4BQ5OMUaVYgRNxeewaYePEUb4Vh98aut5tNYwyOUo1P4eGoHqQw0fKuvypik+fAk0IRqTFzoWr93vdikTZD/nGImGmYYnqD9L5fb4pXKrehcJWzPEWPuV2qoGdNmqDmOJWIuvzfWtwKeFTtNYW5ijUhCV/2bj1NwHBFJtHF+2lZi0GAUrywW3cJhbcOe3loffIt57mI2pepteB+67qaJkgzErz00kGmIMY/3l+oZAdKyFx61GAaHdVLaDaKkEtp19DJnSJJC/AQgkEso6JP7cYsyi2AA/L9dfwG1HeWELBBc6AEzAEQClGV8i8wkYva/oMHdg5RPrnTiHF0Kp/S0qbkQrOgiC3zoFkXSkibIgQ5MF2cYjgVMQHg2GIw2g+8sLW1kC4Tvtl9LhpPkazgoE7TU32CWzfjpHjJUhukKFX3KJ77cSq8aWOVNGl9rRT0htDPMFokDfkZF+O5JHZomdk1w0QsZW2rFhxCpxmTteEhvxWQ2/7rRif0fuopX32Sv2M9bCmVIb/Je2N8NKebwVCkAHCBDowcO6rOK5szVWp9JGPNsfTVmchVaFzPPFn7ldKI1EGdsjCFmDEFE0hsu0Z3eZJu/dyMIlC/UfrJWU1E/GlFN8/JteVzhXessflMEVoAfhZULtAZ4MMf2C/bz1llRjW3+vG7deWeg8qxQNY9JRJiOWIWLwLmi+nBUbXWkNuNHmAwZPAbFujPkMYnxIdiuSWRpjJQv+dJw4RgLhRtR0Ru0AV02e6gpoTePaN1E4R9PZ1gqDncbppURIWkf5FVuzOlAVjojH8zzW6z/VhPe+b0EsX1OC2sJUHuwuYTRxyOgRUmxKTH4ThGWYD5CG9hcxHNqPUWlMkSbclC2TsRU6ZLL3kQwlXvVTlHjoDZqLH8hxL7+JjklTQcbSCNnxE6NjPHbIkkgBlYiN1lHZLHynzHzR6bnRMTkI41eQvcrD4xD5mI/HfPlYwI1EPhbhMS+HGflBgEA+Q2jJJF/QiY2lozx6Y+GoXOpc+wYeaywZ5XE3njAqFy/HWe++gbblKZbnnXNe25uIhwXiZKI4yrBqHtHJthf2KkXbK/7dxWVKzydlRu4hD2wV4xoj2Beb8AhGsfXwJrEe9Qq3JTibeToDIyb6mO0s1m8uF6vJm/iyeO5AVHnaoUxrqhTON+HlYnJwIk0JneQN7+8DbZK5YrA0ZheHxWDpi2P79zFGfv4TMWHW42YZ12mAslzoeJIW4g8OoYKoJvW3D7EOQTw=
*/