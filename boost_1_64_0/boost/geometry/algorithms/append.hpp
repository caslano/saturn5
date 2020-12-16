// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_APPEND_HPP
#define BOOST_GEOMETRY_ALGORITHMS_APPEND_HPP


#include <boost/range.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/num_interior_rings.hpp>
#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/geometries/variant.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace append
{

template <typename Geometry, typename Point>
struct append_no_action
{
    static inline void apply(Geometry& , Point const& ,
                int = 0, int = 0)
    {
    }
};

template <typename Geometry, typename Point>
struct append_point
{
    static inline void apply(Geometry& geometry, Point const& point,
                int = 0, int = 0)
    {
        typename geometry::point_type<Geometry>::type copy;
        geometry::detail::conversion::convert_point_to_point(point, copy);
        traits::push_back<Geometry>::apply(geometry, copy);
    }
};


template <typename Geometry, typename Range>
struct append_range
{
    typedef typename boost::range_value<Range>::type point_type;

    static inline void apply(Geometry& geometry, Range const& range,
                int = 0, int = 0)
    {
        for (typename boost::range_iterator<Range const>::type
            it = boost::begin(range);
             it != boost::end(range);
             ++it)
        {
            append_point<Geometry, point_type>::apply(geometry, *it);
        }
    }
};


template <typename Polygon, typename Point>
struct point_to_polygon
{
    typedef typename ring_type<Polygon>::type ring_type;
    typedef typename ring_return_type<Polygon>::type exterior_ring_type;
    typedef typename interior_return_type<Polygon>::type interior_ring_range_type;

    static inline void apply(Polygon& polygon, Point const& point,
                int ring_index, int = 0)
    {
        if (ring_index == -1)
        {
            exterior_ring_type ext_ring = exterior_ring(polygon);
            append_point<ring_type, Point>::apply(
                        ext_ring, point);
        }
        else if (ring_index < int(num_interior_rings(polygon)))
        {
            interior_ring_range_type int_rings = interior_rings(polygon);
            append_point<ring_type, Point>::apply(
                        range::at(int_rings, ring_index), point);
        }
    }
};


template <typename Polygon, typename Range>
struct range_to_polygon
{
    typedef typename ring_type<Polygon>::type ring_type;
    typedef typename ring_return_type<Polygon>::type exterior_ring_type;
    typedef typename interior_return_type<Polygon>::type interior_ring_range_type;

    static inline void apply(Polygon& polygon, Range const& range,
                int ring_index, int = 0)
    {
        if (ring_index == -1)
        {
            exterior_ring_type ext_ring = exterior_ring(polygon);
            append_range<ring_type, Range>::apply(
                        ext_ring, range);
        }
        else if (ring_index < int(num_interior_rings(polygon)))
        {
            interior_ring_range_type int_rings = interior_rings(polygon);
            append_range<ring_type, Range>::apply(
                        range::at(int_rings, ring_index), range);
        }
    }
};


}} // namespace detail::append
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

namespace splitted_dispatch
{

template <typename Tag, typename Geometry, typename Point>
struct append_point
    : detail::append::append_no_action<Geometry, Point>
{};

template <typename Geometry, typename Point>
struct append_point<linestring_tag, Geometry, Point>
    : detail::append::append_point<Geometry, Point>
{};

template <typename Geometry, typename Point>
struct append_point<ring_tag, Geometry, Point>
    : detail::append::append_point<Geometry, Point>
{};


template <typename Polygon, typename Point>
struct append_point<polygon_tag, Polygon, Point>
        : detail::append::point_to_polygon<Polygon, Point>
{};


template <typename Tag, typename Geometry, typename Range>
struct append_range
    : detail::append::append_no_action<Geometry, Range>
{};

template <typename Geometry, typename Range>
struct append_range<linestring_tag, Geometry, Range>
    : detail::append::append_range<Geometry, Range>
{};

template <typename Geometry, typename Range>
struct append_range<ring_tag, Geometry, Range>
    : detail::append::append_range<Geometry, Range>
{};


template <typename Polygon, typename Range>
struct append_range<polygon_tag, Polygon, Range>
        : detail::append::range_to_polygon<Polygon, Range>
{};

} // namespace splitted_dispatch


// Default: append a range (or linestring or ring or whatever) to any geometry
template
<
    typename Geometry, typename RangeOrPoint,
    typename TagRangeOrPoint = typename tag<RangeOrPoint>::type
>
struct append
    : splitted_dispatch::append_range<typename tag<Geometry>::type, Geometry, RangeOrPoint>
{};

// Specialization for point to append a point to any geometry
template <typename Geometry, typename RangeOrPoint>
struct append<Geometry, RangeOrPoint, point_tag>
    : splitted_dispatch::append_point<typename tag<Geometry>::type, Geometry, RangeOrPoint>
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace append
{

template <typename MultiGeometry, typename RangeOrPoint>
struct append_to_multigeometry
{
    static inline void apply(MultiGeometry& multigeometry,
                             RangeOrPoint const& range_or_point,
                             int ring_index, int multi_index)
    {

        dispatch::append
            <
                typename boost::range_value<MultiGeometry>::type,
                RangeOrPoint
            >::apply(range::at(multigeometry, multi_index), range_or_point, ring_index);
    }
};

}} // namespace detail::append
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

namespace splitted_dispatch
{

template <typename Geometry, typename Point>
struct append_point<multi_point_tag, Geometry, Point>
    : detail::append::append_point<Geometry, Point>
{};

template <typename Geometry, typename Range>
struct append_range<multi_point_tag, Geometry, Range>
    : detail::append::append_range<Geometry, Range>
{};

template <typename MultiGeometry, typename RangeOrPoint>
struct append_point<multi_linestring_tag, MultiGeometry, RangeOrPoint>
    : detail::append::append_to_multigeometry<MultiGeometry, RangeOrPoint>
{};

template <typename MultiGeometry, typename RangeOrPoint>
struct append_range<multi_linestring_tag, MultiGeometry, RangeOrPoint>
    : detail::append::append_to_multigeometry<MultiGeometry, RangeOrPoint>
{};

template <typename MultiGeometry, typename RangeOrPoint>
struct append_point<multi_polygon_tag, MultiGeometry, RangeOrPoint>
    : detail::append::append_to_multigeometry<MultiGeometry, RangeOrPoint>
{};

template <typename MultiGeometry, typename RangeOrPoint>
struct append_range<multi_polygon_tag, MultiGeometry, RangeOrPoint>
    : detail::append::append_to_multigeometry<MultiGeometry, RangeOrPoint>
{};

} // namespace splitted_dispatch

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_variant {

template <typename Geometry>
struct append
{
    template <typename RangeOrPoint>
    static inline void apply(Geometry& geometry,
                             RangeOrPoint const& range_or_point,
                             int ring_index,
                             int multi_index)
    {
        concepts::check<Geometry>();
        dispatch::append<Geometry, RangeOrPoint>::apply(geometry,
                                                        range_or_point,
                                                        ring_index,
                                                        multi_index);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct append<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename RangeOrPoint>
    struct visitor: boost::static_visitor<void>
    {
        RangeOrPoint const& m_range_or_point;
        int m_ring_index;
        int m_multi_index;

        visitor(RangeOrPoint const& range_or_point,
                int ring_index,
                int multi_index):
            m_range_or_point(range_or_point),
            m_ring_index(ring_index),
            m_multi_index(multi_index)
        {}

        template <typename Geometry>
        void operator()(Geometry& geometry) const
        {
            append<Geometry>::apply(geometry,
                                    m_range_or_point,
                                    m_ring_index,
                                    m_multi_index);
        }
    };

    template <typename RangeOrPoint>
    static inline void apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& variant_geometry,
                             RangeOrPoint const& range_or_point,
                             int ring_index,
                             int multi_index)
    {
        boost::apply_visitor(
            visitor<RangeOrPoint>(
                range_or_point,
                ring_index,
                multi_index
            ),
            variant_geometry
        );
    }
};

} // namespace resolve_variant;


/*!
\brief Appends one or more points to a linestring, ring, polygon, multi-geometry
\ingroup append
\tparam Geometry \tparam_geometry
\tparam RangeOrPoint Either a range or a point, fullfilling Boost.Range concept or Boost.Geometry Point Concept
\param geometry \param_geometry
\param range_or_point The point or range to add
\param ring_index The index of the ring in case of a polygon:
    exterior ring (-1, the default) or  interior ring index
\param multi_index The index of the geometry to which the points are appended

\qbk{[include reference/algorithms/append.qbk]}
}
 */
template <typename Geometry, typename RangeOrPoint>
inline void append(Geometry& geometry, RangeOrPoint const& range_or_point,
                   int ring_index = -1, int multi_index = 0)
{
    resolve_variant::append<Geometry>
                   ::apply(geometry, range_or_point, ring_index, multi_index);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_APPEND_HPP

/* append.hpp
fju0WovmCsbr9GWp1IMvmD2z3pEHPNECwfhZvgz2G0m5CDa36huabRKYA7PL7Z5+o97B+PyqLXo3Fa0AjM/Ia2016k8DVptZi98F26i/Btr9Tcoc1IH6A+NnCRw25xb1B+bIzG1xqyDqD4yfUxbQ+QeaSrCsD/oz0dRgFsyi6o8PQ8sRztnMITec5g7Gr4k9zvOMaO5gNZjpTajmgObWUPssde95UmZKwdLf6p6k3sF473vOKqmHWDB+TsP24QrqHQzvrZvBcveVeKHlMdsCFuxc7wCapBHcJ/58X7AV7PD8qSWUWVO6T1TYogmLPdCyBNtax7An7QdmyqzjDJuJlCeYO7PStpNfo8l9tNc0KMnVQ3P1oXtdhe3bt5Lq3MD0mdUfVsMAzRsMM9sGltcyzRDNH0zB7Hu8WXe0UDAjZsrwWp/Qon3omVNhm7a/74sWByZjdROityynGYHJmXW6M7wVZQ1mzmxYv7qj0XLATJiNnzFpBFqBsGarZS/i0UqFNdef8mhKc/eF+yczK5eFVCcH43UBxwI+U9ZC3dk2bei69gXjWYc1vrQJLQAMn0fbwYYuCnuAFgQmY/Zs5Zl8tAih7tL7N9cpazALZr8nrluCliRY9pTSb2jpYApmj+c0MaI8weyY6WTm56K99qXPjRX2o8/z1mhlYCasbt3aizQjaTPIk9kxdZeHaK5gvM521K2/1y6YGbNrbXLOoynBeGaPdrW8QFkLdbmeJt0pazCe5+WGq09S1sKaLhcOt6OshbpNB/eWoamE/c4oGmjQUsEsmVX51nk7WpaQy7Tzr9Q0BzArZt/D8qj3UjALnqesuAGapLn2WTIuqQ6hycH43Df3/+pIWYMZMeuR1EFGWYOZMou9On0OZQ1my8zMynsL5Sns53e8RyFlJpjyyc/jaOlgPLMjz+KvouWBWTOzTttXhFYs9H7IsXgymgbMmFmf5zOuUWYttOtmNexvRJmB2TCr+0vjR5mB8RnVHNbXAs0fzI7bKIcotFAw3rtl56lhaPFgvHcXyfgUtFQwPofDL56vpcwEmxK7qgAtB8yC2dfh82uiFQr7/Vj4JYsyE/rz/mdxMZq0pXbdbbuYRDRXMHNmcfXb9kHzBavKrPuuWrfRgsAcmU2uf2kvWhyYA8+z4YaqlAuYNbP0k4nz0bKENd947HWg3oUelCOaDKTehR7q13l0lHpvpZ31hgZSqlOAmTHb4nfWB81NsB0NvAwoF8FqHBpujeYPxnt3clw4CS0UjM9oke42e8pMWHO31bHLaCowI2ZPin4GU55CfzYzdr1DSwfjmY22GfYULQ+MX/PlVc/4o5WC8TncGtbqMuXZ+u870Q6w4XtbX0NTglkwG2KWfREtEMyaWc/76k5oEWADKyygwt75JX5GKwZr++c7ATXYeXWPVmjefthDpcXajIpHCwCrxyxxw78n0OLBGjOz2Jr6gXIBM2aW/7h6HlqhYEft7/eizMCMmB1s2nM0WplgWyx15lGeSpg7s4RozV40BZgJM2mjlcZobmByZg3X+7jQHMBsmdX+tCgbLQhMxmzK84Q5NAdhP8vUV/3Q4sCsmd1s+vIBWpKw5rYZaQPR1GB+zNr55V1E+6Sk70oqbOfPxBeUGZgBswGOv3qgSdrAOzSz8pfdHdD0BXP5fW01ZQ3Gz3lv7CFzyhqsCqsreueeieYKxufu5fntMJo3GF5nO8EmDc+/ghbKbBfY+eKv1mipYPhztBts5JqQtmiFYObMqhzNckLTgJkxs5lRQ6/SsvQkbf+uuUcnS2+/vPMiNF+wun8sDczevngoWgSY5x9LB3v6ZexctHSwAv3Kz1wZYK+qvo5Ci/WnXCos8cE=
*/