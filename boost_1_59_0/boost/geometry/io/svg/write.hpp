// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2009-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2016-2020.
// Modifications copyright (c) 2016-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_IO_SVG_WRITE_HPP
#define BOOST_GEOMETRY_IO_SVG_WRITE_HPP

#include <ostream>
#include <string>

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>

#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace svg
{


template <typename Point>
struct svg_point
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Point const& p, std::string const& style, double size)
    {
        os << "<circle cx=\"" << geometry::get<0>(p)
            << "\" cy=\"" << geometry::get<1>(p)
            << "\" r=\"" << (size < 0 ? 5 : size)
            << "\" style=\"" << style << "\"/>";
    }
};


template <typename Box>
struct svg_box
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Box const& box, std::string const& style, double)
    {
        // Prevent invisible boxes, making them >=1, using "max"
        BOOST_USING_STD_MAX();

        typedef typename coordinate_type<Box>::type ct;
        ct x = geometry::get<geometry::min_corner, 0>(box);
        ct y = geometry::get<geometry::min_corner, 1>(box);
        ct width = max BOOST_PREVENT_MACRO_SUBSTITUTION (ct(1),
                    geometry::get<geometry::max_corner, 0>(box) - x);
        ct height = max BOOST_PREVENT_MACRO_SUBSTITUTION (ct(1),
                    geometry::get<geometry::max_corner, 1>(box) - y);

        os << "<rect x=\"" << x << "\" y=\"" << y
           << "\" width=\"" << width << "\" height=\"" << height
           << "\" style=\"" << style << "\"/>";
    }
};

template <typename Segment>
struct svg_segment
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
        Segment const& segment, std::string const& style, double)
    {
        typedef typename coordinate_type<Segment>::type ct;
        ct x1 = geometry::get<0, 0>(segment);
        ct y1 = geometry::get<0, 1>(segment);
        ct x2 = geometry::get<1, 0>(segment);
        ct y2 = geometry::get<1, 1>(segment);
        
        os << "<line x1=\"" << x1 << "\" y1=\"" << y1
            << "\" x2=\"" << x2 << "\" y2=\"" << y2
            << "\" style=\"" << style << "\"/>";
    }
};

/*!
\brief Stream ranges as SVG
\note policy is used to select type (polyline/polygon)
*/
template <typename Range, typename Policy>
struct svg_range
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
        Range const& range, std::string const& style, double)
    {
        typedef typename boost::range_iterator<Range const>::type iterator;

        bool first = true;

        os << "<" << Policy::prefix() << " points=\"";

        for (iterator it = boost::begin(range);
            it != boost::end(range);
            ++it, first = false)
        {
            os << (first ? "" : " " )
                << geometry::get<0>(*it)
                << ","
                << geometry::get<1>(*it);
        }
        os << "\" style=\"" << style << Policy::style() << "\"/>";
    }
};



template <typename Polygon>
struct svg_poly
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
        Polygon const& polygon, std::string const& style, double)
    {
        typedef typename geometry::ring_type<Polygon>::type ring_type;
        typedef typename boost::range_iterator<ring_type const>::type iterator_type;

        bool first = true;
        os << "<g fill-rule=\"evenodd\"><path d=\"";

        ring_type const& ring = geometry::exterior_ring(polygon);
        for (iterator_type it = boost::begin(ring);
            it != boost::end(ring);
            ++it, first = false)
        {
            os << (first ? "M" : " L") << " "
                << geometry::get<0>(*it)
                << ","
                << geometry::get<1>(*it);
        }

        // Inner rings:
        {
            typename interior_return_type<Polygon const>::type
                rings = interior_rings(polygon);
            for (typename detail::interior_iterator<Polygon const>::type
                    rit = boost::begin(rings); rit != boost::end(rings); ++rit)
            {
                first = true;
                for (typename detail::interior_ring_iterator<Polygon const>::type
                        it = boost::begin(*rit); it != boost::end(*rit);
                    ++it, first = false)
                {
                    os << (first ? "M" : " L") << " "
                        << geometry::get<0>(*it)
                        << ","
                        << geometry::get<1>(*it);
                }
            }
        }
        os << " z \" style=\"" << style << "\"/></g>";

    }
};



struct prefix_linestring
{
    static inline const char* prefix() { return "polyline"; }
    static inline const char* style() { return ";fill:none"; }
};


struct prefix_ring
{
    static inline const char* prefix() { return "polygon"; }
    static inline const char* style() { return ""; }
};


template <typename MultiGeometry, typename Policy>
struct svg_multi
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
        MultiGeometry const& multi, std::string const& style, double size)
    {
        for (typename boost::range_iterator<MultiGeometry const>::type
                    it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(os, *it, style, size);
        }

    }

};


}} // namespace detail::svg
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

/*!
\brief Dispatching base struct for SVG streaming, specialized below per geometry type
\details Specializations should implement a static method "stream" to stream a geometry
The static method should have the signature:

template <typename Char, typename Traits>
static inline void apply(std::basic_ostream<Char, Traits>& os, G const& geometry)
*/
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct svg
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not or not yet implemented for this Geometry type.",
        Geometry, Tag);
};

template <typename Point>
struct svg<Point, point_tag> : detail::svg::svg_point<Point> {};

template <typename Segment>
struct svg<Segment, segment_tag> : detail::svg::svg_segment<Segment> {};

template <typename Box>
struct svg<Box, box_tag> : detail::svg::svg_box<Box> {};

template <typename Linestring>
struct svg<Linestring, linestring_tag>
    : detail::svg::svg_range<Linestring, detail::svg::prefix_linestring> {};

template <typename Ring>
struct svg<Ring, ring_tag>
    : detail::svg::svg_range<Ring, detail::svg::prefix_ring> {};

template <typename Polygon>
struct svg<Polygon, polygon_tag>
    : detail::svg::svg_poly<Polygon> {};

template <typename MultiPoint>
struct svg<MultiPoint, multi_point_tag>
    : detail::svg::svg_multi
        <
            MultiPoint,
            detail::svg::svg_point
                <
                    typename boost::range_value<MultiPoint>::type
                >

        >
{};

template <typename MultiLinestring>
struct svg<MultiLinestring, multi_linestring_tag>
    : detail::svg::svg_multi
        <
            MultiLinestring,
            detail::svg::svg_range
                <
                    typename boost::range_value<MultiLinestring>::type,
                    detail::svg::prefix_linestring
                >

        >
{};

template <typename MultiPolygon>
struct svg<MultiPolygon, multi_polygon_tag>
    : detail::svg::svg_multi
        <
            MultiPolygon,
            detail::svg::svg_poly
                <
                    typename boost::range_value<MultiPolygon>::type
                >

        >
{};


template <typename Geometry>
struct devarianted_svg
{
    template <typename OutputStream>
    static inline void apply(OutputStream& os,
                             Geometry const& geometry,
                             std::string const& style,
                             double size)
    {
        svg<Geometry>::apply(os, geometry, style, size);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct devarianted_svg<variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename OutputStream>
    struct visitor: static_visitor<void>
    {
        OutputStream& m_os;
        std::string const& m_style;
        double m_size;

        visitor(OutputStream& os, std::string const& style, double size)
            : m_os(os)
            , m_style(style)
            , m_size(size)
        {}

        template <typename Geometry>
        inline void operator()(Geometry const& geometry) const
        {
            devarianted_svg<Geometry>::apply(m_os, geometry, m_style, m_size);
        }
    };

    template <typename OutputStream>
    static inline void apply(
        OutputStream& os,
        variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
        std::string const& style,
        double size
    )
    {
        boost::apply_visitor(visitor<OutputStream>(os, style, size), geometry);
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief Generic geometry template manipulator class, takes corresponding output class from traits class
\ingroup svg
\details Stream manipulator, streams geometry classes as SVG (Scalable Vector Graphics)
*/
template <typename Geometry>
class svg_manipulator
{
public:

    inline svg_manipulator(Geometry const& g, std::string const& style, double size)
        : m_geometry(g)
        , m_style(style)
        , m_size(size)
    {}

    template <typename Char, typename Traits>
    inline friend std::basic_ostream<Char, Traits>& operator<<(
                    std::basic_ostream<Char, Traits>& os, svg_manipulator const& m)
    {
        dispatch::devarianted_svg<Geometry>::apply(os,
                                                   m.m_geometry,
                                                   m.m_style,
                                                   m.m_size);
        os.flush();
        return os;
    }

private:
    Geometry const& m_geometry;
    std::string const& m_style;
    double m_size;
};

/*!
\brief Manipulator to stream geometries as SVG
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\param style String containing verbatim SVG style information
\param size Optional size (used for SVG points) in SVG pixels. For linestrings,
    specify linewidth in the SVG style information
\ingroup svg
*/
template <typename Geometry>
inline svg_manipulator<Geometry> svg(Geometry const& geometry,
            std::string const& style, double size = -1.0)
{
    concepts::check<Geometry const>();

    return svg_manipulator<Geometry>(geometry, style, size);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_IO_SVG_WRITE_HPP

/* write.hpp
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
*/