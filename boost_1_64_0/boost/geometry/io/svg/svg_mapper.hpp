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
z3pcyLnfv2JCPO9frLmFON+tsrHr+UKR7AEICbwuNyMk4B4D9bzhOYS79zlE3KqPz1bu9HuPX9xuUG7SzsTvaEgbE/kwInvsDb3e55iTXNPOLuAPxNVcWDGee/2Wd07CUyfoHqI3lL/HXe+Z8TJX8YTtGWzPENflO7/sGTqs7Ltdn9HjSu0bEhniB5Wfp11anpCyTws+T9B+uoi8XoYKZd/jOmMy/nvXQooLszInyzd2PTY8r/w+7zJdpu+eIt3OKx2T55E8G2OVfaZruxnm3WfjK09J1jNGKX9NXJmM+6X3GTn2ChFH6b1Cn6h81eIeVtbrJu8rt+pGhHybnBVg/89oZ5xkzLse/oIK/5zrZ9Olwt8XU3rsKoC96K9ccvS9ezFPltrz45S1+HvMHsxeH5mLy8+zzlHi8x37UOlvLlR36b08J6D/Xp5TMFA/Sw+yl2c0nBVgz04BpF4cfc0rWymYTKF/veyjwDKXgslEunAZRxcqyyiwbJ8Ll3F0obKMFlS33N/vEdNqftcPLmlb/OmnE9873eU/J+MosKytYDKOgsng+tfLPgosyyuYjKlgMsGCydoqLVvpkEvLVuJvLVuJv7VsJf4W2Ury9638vVb9Dfl7g/x9L3/fJX8/xt/r5e8bRLZSH885XPm7xE82Rn2cLDaCMbAxrAqbwk6wGewN03z04Y+W+Mar+Jz68C+V+FrDNNgG9oRtYSZs7yML44TEE6HiccrC6CTxdIbhsItPuNMSjttJWcsuKypme/BwayTcWgl3pw6HkXBVVbiyy4pKd4Qru6yoAgkXo8KVXVbUckd6ZZcVtV3CRahwZZcVtU/CRatwZZcVdegc4R6VcI9JuB2ecPr8jTrPo9pLXSsc5MeXDWTkwBdgA/gq7AoPw6vhMVgM34a3wXfhnfB9eD/8DO6Hn8Mv4Gl4Bn4Nf4LfwXjSOgsbwB9hG/gz7AJ/gf1geBhiG2AlOB4mwWkwGa6AKXAtbA6fgGlwD+wMX4J94GtwMPwrHAYjXMzbiL8CHIc9BV4Dm8BrYXM4CraCVrl7wyPQqrfl+vwHdSr11txqN1JvoVJfCVY4WBdeAS+C6l0WZsPGcBJsCpfClnAFbA1XwzZwPXwQboK94CuwH/wQ9ocmaQ6FLeE18Co4DubDLFgIx8NimAuvg5PhDbAAroOFcDcsgvthMTwCZ8DjsAR+BOfAL+E8+He4AP4Ch8MQ6mEEjIEjYRy8CdaBi2A9eDNMg4thC3gr7ACXw75wGRwk9nHwflgMH4Qz4Cp4HbwH3gq3wJXwIbkvpw3Zvw+bue37UoO/T0o/GONGTz6cBLvDyXAIzIPD4BQ4DhbDGXAqnAWnwflwOrwJzoD3wuvhe3ApPAOXwYqkuQLGwvVwIdwAb4Gb4Eq4Ga6H98FN8HH4totnJvwz3AM/g0/Db+Az8G/wCWhSrl0wGu6DVrlPGbLHWfZ2l2CS+Pu4If04hPYMX4Qt4CE4GB6FBfANeCs8DrfBd+GT8H14EH4AP4R/gafhh/BreBKeFXsF07YnwI9hDbEnw09gGvwUdoWfwfHwKzgNfgNnwDNwEfwWLhH7MrHfB11yn7frPZm0XXnOxcMtUt4++Ld4OYyD6TABjoBV4BBYB14Bm8ChsIXYu4u9l9j7i32Q2K+GV8JRcDjMFPs4sU8Ue57Yp0i6IjNK9toRF6bET2ZUfZf9/GkEL4VNYRvYDLaDrWAXmAa7wxawH2wJL5frX8MZmBJJZ6mkEw1zMYbIloqH8TAFJsAOsCrsAavBXrAuHAyTYB6sCQthbTgVpsDZMBXOFf9fw2p67xZ9XNqjlU40VB9GXPb96CXpD4T14SDYEM6DbeHlsBNMl3w=
*/