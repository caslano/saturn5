// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2009-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015, 2016.
// Modifications copyright (c) 2015-2016, Oracle and/or its affiliates.

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

#include <vector>

#include <boost/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>


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
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_OR_NOT_YET_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (Geometry)
        );
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
                typename boost::remove_const<Geometry>::type,
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
    SvgCoordinateType m_width, m_height;
    std::string m_width_height; // for <svg> tag only, defaults to 2x 100%

    void init_matrix()
    {
        if (! m_matrix)
        {
            m_matrix.reset(new transformer_type(m_bounding_box,
                            m_width, m_height));


            m_stream << "<?xml version=\"1.0\" standalone=\"no\"?>"
                << std::endl
                << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\""
                << std::endl
                << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">"
                << std::endl
                << "<svg " << m_width_height << " version=\"1.1\""
                << std::endl
                << "xmlns=\"http://www.w3.org/2000/svg\""
                << std::endl
                << "xmlns:xlink=\"http://www.w3.org/1999/xlink\""
                << ">"
                << std::endl;
        }
    }

public :
    
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
        , m_width_height(width_height)
    {
        assign_inverse(m_bounding_box);
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