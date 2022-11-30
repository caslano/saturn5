// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2009-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015-2021.
// Modifications copyright (c) 2015-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_IO_SVG_MAPPER_HPP
#define BOOST_GEOMETRY_IO_SVG_MAPPER_HPP

#include <cstdio>
#include <type_traits>
#include <vector>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/algorithms/is_empty.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/strategies/transform/map_transformer.hpp>
#include <boost/geometry/views/segment_view.hpp>

#include <boost/geometry/io/svg/write.hpp>

// Helper geometries (all points are transformed to svg-points)
#include <boost/geometry/geometries/geometries.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename GeometryTag, typename Geometry, typename SvgPoint>
struct svg_map
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not or not yet implemented for this Geometry type.",
        GeometryTag, Geometry);
};


template <typename Point, typename SvgPoint>
struct svg_map<point_tag, Point, SvgPoint>
{
    template <typename TransformStrategy>
    static inline void apply(std::ostream& stream,
                    std::string const& style, double size,
                    Point const& point, TransformStrategy const& strategy)
    {
        SvgPoint ipoint;
        geometry::transform(point, ipoint, strategy);
        stream << geometry::svg(ipoint, style, size) << std::endl;
    }
};

template <typename BoxSeg1, typename BoxSeg2, typename SvgPoint>
struct svg_map_box_seg
{
    template <typename TransformStrategy>
    static inline void apply(std::ostream& stream,
                    std::string const& style, double size,
                    BoxSeg1 const& box_seg, TransformStrategy const& strategy)
    {
        BoxSeg2 ibox_seg;

        // Fix bug in gcc compiler warning for possible uninitialization
#if defined(BOOST_GCC)
        geometry::assign_zero(ibox_seg);
#endif
        geometry::transform(box_seg, ibox_seg, strategy);

        stream << geometry::svg(ibox_seg, style, size) << std::endl;
    }
};

template <typename Box, typename SvgPoint>
struct svg_map<box_tag, Box, SvgPoint>
    : svg_map_box_seg<Box, model::box<SvgPoint>, SvgPoint>
{};

template <typename Segment, typename SvgPoint>
struct svg_map<segment_tag, Segment, SvgPoint>
    : svg_map_box_seg<Segment, model::segment<SvgPoint>, SvgPoint>
{};


template <typename Range1, typename Range2, typename SvgPoint>
struct svg_map_range
{
    template <typename TransformStrategy>
    static inline void apply(std::ostream& stream,
                std::string const& style, double size,
                Range1 const& range, TransformStrategy const& strategy)
    {
        Range2 irange;
        geometry::transform(range, irange, strategy);
        stream << geometry::svg(irange, style, size) << std::endl;
    }
};

template <typename Ring, typename SvgPoint>
struct svg_map<ring_tag, Ring, SvgPoint>
    : svg_map_range<Ring, model::ring<SvgPoint>, SvgPoint>
{};


template <typename Linestring, typename SvgPoint>
struct svg_map<linestring_tag, Linestring, SvgPoint>
    : svg_map_range<Linestring, model::linestring<SvgPoint>, SvgPoint>
{};


template <typename Polygon, typename SvgPoint>
struct svg_map<polygon_tag, Polygon, SvgPoint>
{
    template <typename TransformStrategy>
    static inline void apply(std::ostream& stream,
                    std::string const& style, double size,
                    Polygon const& polygon, TransformStrategy const& strategy)
    {
        model::polygon<SvgPoint> ipoly;
        geometry::transform(polygon, ipoly, strategy);
        stream << geometry::svg(ipoly, style, size) << std::endl;
    }
};


template <typename Multi, typename SvgPoint>
struct svg_map<multi_tag, Multi, SvgPoint>
{
    typedef typename single_tag_of
      <
          typename geometry::tag<Multi>::type
      >::type stag;

    template <typename TransformStrategy>
    static inline void apply(std::ostream& stream,
                    std::string const& style, double size,
                    Multi const& multi, TransformStrategy const& strategy)
    {
        for (typename boost::range_iterator<Multi const>::type it
            = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            svg_map
                <
                    stag,
                    typename boost::range_value<Multi>::type,
                    SvgPoint
                >::apply(stream, style, size, *it, strategy);
        }
    }
};


template <typename SvgPoint, typename Geometry>
struct devarianted_svg_map
{
    template <typename TransformStrategy>
    static inline void apply(std::ostream& stream,
                             std::string const& style,
                             double size,
                             Geometry const& geometry,
                             TransformStrategy const& strategy)
    {
        svg_map
            <
                typename tag_cast
                    <
                        typename tag<Geometry>::type,
                        multi_tag
                    >::type,
                typename std::remove_const<Geometry>::type,
                SvgPoint
            >::apply(stream, style, size, geometry, strategy);
    }
};

template <typename SvgPoint, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct devarianted_svg_map<SvgPoint, variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename TransformStrategy>
    struct visitor: static_visitor<void>
    {
        std::ostream& m_os;
        std::string const& m_style;
        double m_size;
        TransformStrategy const& m_strategy;

        visitor(std::ostream& os,
                std::string const& style,
                double size,
                TransformStrategy const& strategy)
            : m_os(os)
            , m_style(style)
            , m_size(size)
            , m_strategy(strategy)
        {}

        template <typename Geometry>
        inline void operator()(Geometry const& geometry) const
        {
            devarianted_svg_map<SvgPoint, Geometry>::apply(m_os, m_style, m_size, geometry, m_strategy);
        }
    };

    template <typename TransformStrategy>
    static inline void apply(std::ostream& stream,
                             std::string const& style,
                             double size,
                             variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
                             TransformStrategy const& strategy)
    {
        boost::apply_visitor(visitor<TransformStrategy>(stream, style, size, strategy), geometry);
    }
};


} // namespace dispatch
#endif


template <typename SvgPoint, typename Geometry, typename TransformStrategy>
inline void svg_map(std::ostream& stream,
            std::string const& style, double size,
            Geometry const& geometry, TransformStrategy const& strategy)
{
    dispatch::devarianted_svg_map<SvgPoint, Geometry>::apply(stream,
            style, size, geometry, strategy);
}


/*!
\brief Helper class to create SVG maps
\tparam Point Point type, for input geometries.
\tparam SameScale Boolean flag indicating if horizontal and vertical scale should
    be the same. The default value is true
\tparam SvgCoordinateType Coordinate type of SVG points. SVG is capable to
    use floating point coordinates. Therefore the default value is double
\ingroup svg

\qbk{[include reference/io/svg.qbk]}
*/
template
<
    typename Point,
    bool SameScale = true,
    typename SvgCoordinateType = double
>
class svg_mapper : boost::noncopyable
{
    typedef model::point<SvgCoordinateType, 2, cs::cartesian> svg_point_type;

    typedef typename geometry::select_most_precise
        <
            typename coordinate_type<Point>::type,
            double
        >::type calculation_type;

    typedef strategy::transform::map_transformer
        <
            calculation_type,
            geometry::dimension<Point>::type::value,
            geometry::dimension<Point>::type::value,
            true,
            SameScale
        > transformer_type;

    model::box<Point> m_bounding_box;
    boost::scoped_ptr<transformer_type> m_matrix;
    std::ostream& m_stream;

    SvgCoordinateType const m_width;
    SvgCoordinateType const m_height;
    calculation_type const m_scale{1.0};

    void scale_bounding_box()
    {
        if (m_scale != 1.0 && m_scale > 0)
        {
            // Zoom out (scale < 1) or zoom in (scale > 1).
            // The default is 0.95, giving a small margin around geometries.
            auto& b = m_bounding_box;
            auto const w = geometry::get<1, 0>(b) - geometry::get<0, 0>(b);
            auto const h = geometry::get<1, 1>(b) - geometry::get<0, 1>(b);

            auto const& m = (std::max)(w, h) * (1.0 - m_scale);
            geometry::set<0, 0>(b, geometry::get<0, 0>(b) - m);
            geometry::set<0, 1>(b, geometry::get<0, 1>(b) - m);
            geometry::set<1, 0>(b, geometry::get<1, 0>(b) + m);
            geometry::set<1, 1>(b, geometry::get<1, 1>(b) + m);
        }
    }

    void init_matrix()
    {
        if (! m_matrix)
        {
            scale_bounding_box();
            m_matrix.reset(new transformer_type(m_bounding_box,
                            m_width, m_height));
        }
    }

    void write_header(std::string const& width_height)
    {
        m_stream << "<?xml version=\"1.0\" standalone=\"no\"?>"
            << std::endl
            << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\""
            << std::endl
            << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">"
            << std::endl
            << "<svg " << width_height << " version=\"1.1\""
            << std::endl
            << "xmlns=\"http://www.w3.org/2000/svg\""
            << std::endl
            << "xmlns:xlink=\"http://www.w3.org/1999/xlink\""
            << ">"
            << std::endl;
    }

public :
    
    /*!
    \brief Constructor, initializing the SVG map. Opens and initializes the SVG.
         Should be called explicitly.
    \param stream Output stream, should be a stream already open
    \param width Width of the SVG map (in SVG pixels)
    \param height Height of the SVG map (in SVG pixels)
    \param scale Scale factor of the automatically determined bounding box.
            If the factor is less than 1.0, there will be a margin around the
            geometries. A factor of 0.95 is often a convenient margin. If the
            factor is more than 1.0, the SVG map is zoomed and not all
            geometries will be visible.
    \param width_height Optional information to increase width and/or height
    */
    svg_mapper(std::ostream& stream
        , SvgCoordinateType width
        , SvgCoordinateType height
        , calculation_type scale
        , std::string const& width_height = "width=\"100%\" height=\"100%\"")
        : m_stream(stream)
        , m_width(width)
        , m_height(height)
        , m_scale(scale)
    {
        assign_inverse(m_bounding_box);
        write_header(width_height);
    }

    /*!
    \brief Constructor, initializing the SVG map. Opens and initializes the SVG.
         Should be called explicitly.
    \param stream Output stream, should be a stream already open
    \param width Width of the SVG map (in SVG pixels)
    \param height Height of the SVG map (in SVG pixels)
    \param width_height Optional information to increase width and/or height
    */
    svg_mapper(std::ostream& stream
        , SvgCoordinateType width
        , SvgCoordinateType height
        , std::string const& width_height = "width=\"100%\" height=\"100%\"")
        : m_stream(stream)
        , m_width(width)
        , m_height(height)
    {
        assign_inverse(m_bounding_box);
        write_header(width_height);
    }

    /*!
    \brief Destructor, called automatically. Closes the SVG by streaming <\/svg>
    */
    virtual ~svg_mapper()
    {
        m_stream << "</svg>" << std::endl;
    }

    /*!
    \brief Adds a geometry to the transformation matrix. After doing this,
        the specified geometry can be mapped fully into the SVG map
    \tparam Geometry \tparam_geometry
    \param geometry \param_geometry
    */
    template <typename Geometry>
    void add(Geometry const& geometry)
    {
        if (! geometry::is_empty(geometry))
        {
            expand(m_bounding_box,
                return_envelope
                    <
                        model::box<Point>
                    >(geometry));
        }
    }

    /*!
    \brief Maps a geometry into the SVG map using the specified style
    \tparam Geometry \tparam_geometry
    \param geometry \param_geometry
    \param style String containing verbatim SVG style information
    \param size Optional size (used for SVG points) in SVG pixels. For linestrings,
        specify linewidth in the SVG style information
    */
    template <typename Geometry>
    void map(Geometry const& geometry, std::string const& style,
                double size = -1.0)
    {
        init_matrix();
        svg_map<svg_point_type>(m_stream, style, size, geometry, *m_matrix);
    }

    /*!
    \brief Adds a text to the SVG map
    \tparam TextPoint \tparam_point
    \param point Location of the text (in map units)
    \param s The text itself
    \param style String containing verbatim SVG style information, of the text
    \param offset_x Offset in SVG pixels, defaults to 0
    \param offset_y Offset in SVG pixels, defaults to 0
    \param lineheight Line height in SVG pixels, in case the text contains \n
    */
    template <typename TextPoint>
    void text(TextPoint const& point, std::string const& s,
                std::string const& style,
                double offset_x = 0.0, double offset_y = 0.0,
                double lineheight = 10.0)
    {
        init_matrix();
        svg_point_type map_point;
        transform(point, map_point, *m_matrix);
        m_stream
            << "<text style=\"" << style << "\""
            << " x=\"" << get<0>(map_point) + offset_x << "\""
            << " y=\"" << get<1>(map_point) + offset_y << "\""
            << ">";
        if (s.find("\n") == std::string::npos)
        {
             m_stream  << s;
        }
        else
        {
            // Multi-line modus

            std::vector<std::string> splitted;
            boost::split(splitted, s, boost::is_any_of("\n"));
            for (std::vector<std::string>::const_iterator it
                = splitted.begin();
                it != splitted.end();
                ++it, offset_y += lineheight)
            {
                 m_stream
                    << "<tspan x=\"" << get<0>(map_point) + offset_x
                    << "\""
                    << " y=\"" << get<1>(map_point) + offset_y
                    << "\""
                    << ">" << *it << "</tspan>";
            }
        }
        m_stream << "</text>" << std::endl;
    }
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_IO_SVG_MAPPER_HPP

/* svg_mapper.hpp
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
*/