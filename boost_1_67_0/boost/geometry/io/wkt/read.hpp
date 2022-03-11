// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014, 2015, 2018.
// Modifications copyright (c) 2014-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_IO_WKT_READ_HPP
#define BOOST_GEOMETRY_IO_WKT_READ_HPP

#include <cstddef>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/mpl/if.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_point.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/exception.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/geometry_id.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/util/coordinate_cast.hpp>

#include <boost/geometry/io/wkt/detail/prefix.hpp>

namespace boost { namespace geometry
{

/*!
\brief Exception showing things wrong with WKT parsing
\ingroup wkt
*/
struct read_wkt_exception : public geometry::exception
{
    template <typename Iterator>
    read_wkt_exception(std::string const& msg,
                       Iterator const& it,
                       Iterator const& end,
                       std::string const& wkt)
        : message(msg)
        , wkt(wkt)
    {
        if (it != end)
        {
            source = " at '";
            source += it->c_str();
            source += "'";
        }
        complete = message + source + " in '" + wkt.substr(0, 100) + "'";
    }

    read_wkt_exception(std::string const& msg, std::string const& wkt)
        : message(msg)
        , wkt(wkt)
    {
        complete = message + "' in (" + wkt.substr(0, 100) + ")";
    }

    virtual ~read_wkt_exception() throw() {}

    virtual const char* what() const throw()
    {
        return complete.c_str();
    }
private :
    std::string source;
    std::string message;
    std::string wkt;
    std::string complete;
};


#ifndef DOXYGEN_NO_DETAIL
// (wkt: Well Known Text, defined by OGC for all geometries and implemented by e.g. databases (MySQL, PostGIS))
namespace detail { namespace wkt
{

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

template <typename Point,
          std::size_t Dimension = 0,
          std::size_t DimensionCount = geometry::dimension<Point>::value>
struct parsing_assigner
{
    static inline void apply(tokenizer::iterator& it,
                             tokenizer::iterator const& end,
                             Point& point,
                             std::string const& wkt)
    {
        typedef typename coordinate_type<Point>::type coordinate_type;

        // Stop at end of tokens, or at "," ot ")"
        bool finished = (it == end || *it == "," || *it == ")");

        try
        {
            // Initialize missing coordinates to default constructor (zero)
            // OR
            // Use lexical_cast for conversion to double/int
            // Note that it is much slower than atof. However, it is more standard
            // and in parsing the change in performance falls probably away against
            // the tokenizing
            set<Dimension>(point, finished
                    ? coordinate_type()
                    : coordinate_cast<coordinate_type>::apply(*it));
        }
        catch(boost::bad_lexical_cast const& blc)
        {
            BOOST_THROW_EXCEPTION(read_wkt_exception(blc.what(), it, end, wkt));
        }
        catch(std::exception const& e)
        {
            BOOST_THROW_EXCEPTION(read_wkt_exception(e.what(), it, end, wkt));
        }
        catch(...)
        {
            BOOST_THROW_EXCEPTION(read_wkt_exception("", it, end, wkt));
        }

        parsing_assigner<Point, Dimension + 1, DimensionCount>::apply(
                        (finished ? it : ++it), end, point, wkt);
    }
};

template <typename Point, std::size_t DimensionCount>
struct parsing_assigner<Point, DimensionCount, DimensionCount>
{
    static inline void apply(tokenizer::iterator&,
                             tokenizer::iterator const&,
                             Point&,
                             std::string const&)
    {
    }
};



template <typename Iterator>
inline void handle_open_parenthesis(Iterator& it,
                                    Iterator const& end,
                                    std::string const& wkt)
{
    if (it == end || *it != "(")
    {
        BOOST_THROW_EXCEPTION(read_wkt_exception("Expected '('", it, end, wkt));
    }
    ++it;
}


template <typename Iterator>
inline void handle_close_parenthesis(Iterator& it,
                                     Iterator const& end,
                                     std::string const& wkt)
{
    if (it != end && *it == ")")
    {
        ++it;
    }
    else
    {
        BOOST_THROW_EXCEPTION(read_wkt_exception("Expected ')'", it, end, wkt));
    }
}

template <typename Iterator>
inline void check_end(Iterator& it,
                      Iterator const& end,
                      std::string const& wkt)
{
    if (it != end)
    {
        BOOST_THROW_EXCEPTION(read_wkt_exception("Too many tokens", it, end, wkt));
    }
}

/*!
\brief Internal, parses coordinate sequences, strings are formated like "(1 2,3 4,...)"
\param it token-iterator, should be pre-positioned at "(", is post-positions after last ")"
\param end end-token-iterator
\param out Output itererator receiving coordinates
*/
template <typename Point>
struct container_inserter
{
    // Version with output iterator
    template <typename OutputIterator>
    static inline void apply(tokenizer::iterator& it,
                             tokenizer::iterator const& end,
                             std::string const& wkt,
                             OutputIterator out)
    {
        handle_open_parenthesis(it, end, wkt);

        Point point;

        // Parse points until closing parenthesis

        while (it != end && *it != ")")
        {
            parsing_assigner<Point>::apply(it, end, point, wkt);
            out = point;
            ++out;
            if (it != end && *it == ",")
            {
                ++it;
            }
        }

        handle_close_parenthesis(it, end, wkt);
    }
};


template <typename Geometry,
          closure_selector Closure = closure<Geometry>::value>
struct stateful_range_appender
{
    typedef typename geometry::point_type<Geometry>::type point_type;

    // NOTE: Geometry is a reference
    inline void append(Geometry geom, point_type const& point, bool)
    {
        geometry::append(geom, point);
    }
};

template <typename Geometry>
struct stateful_range_appender<Geometry, open>
{
    typedef typename geometry::point_type<Geometry>::type point_type;
    typedef typename boost::range_size
        <
            typename util::bare_type<Geometry>::type
        >::type size_type;

    BOOST_STATIC_ASSERT(( boost::is_same
                            <
                                typename tag<Geometry>::type,
                                ring_tag
                            >::value ));

    inline stateful_range_appender()
        : pt_index(0)
    {}

    // NOTE: Geometry is a reference
    inline void append(Geometry geom, point_type const& point, bool is_next_expected)
    {
        bool should_append = true;

        if (pt_index == 0)
        {
            first_point = point;
            //should_append = true;
        }
        else
        {
            // NOTE: if there is not enough Points, they're always appended
            should_append
                = is_next_expected
                || pt_index < core_detail::closure::minimum_ring_size<open>::value
                || disjoint(point, first_point);
        }
        ++pt_index;

        if (should_append)
        {
            geometry::append(geom, point);
        }
    }

private:
    static inline bool disjoint(point_type const& p1, point_type const& p2)
    {
        // TODO: pass strategy
        typedef typename strategy::disjoint::services::default_strategy
            <
                point_type, point_type
            >::type strategy_type;

        return detail::disjoint::disjoint_point_point(p1, p2, strategy_type());
    }

    size_type pt_index;
    point_type first_point;
};

// Geometry is a value-type or reference-type
template <typename Geometry>
struct container_appender
{
    typedef typename geometry::point_type<Geometry>::type point_type;

    static inline void apply(tokenizer::iterator& it,
                             tokenizer::iterator const& end,
                             std::string const& wkt,
                             Geometry out)
    {
        handle_open_parenthesis(it, end, wkt);

        stateful_range_appender<Geometry> appender;

        // Parse points until closing parenthesis
        while (it != end && *it != ")")
        {
            point_type point;

            parsing_assigner<point_type>::apply(it, end, point, wkt);

            bool const is_next_expected = it != end && *it == ",";

            appender.append(out, point, is_next_expected);

            if (is_next_expected)
            {
                ++it;
            }
        }

        handle_close_parenthesis(it, end, wkt);
    }
};

/*!
\brief Internal, parses a point from a string like this "(x y)"
\note used for parsing points and multi-points
*/
template <typename P>
struct point_parser
{
    static inline void apply(tokenizer::iterator& it,
                             tokenizer::iterator const& end,
                             std::string const& wkt,
                             P& point)
    {
        handle_open_parenthesis(it, end, wkt);
        parsing_assigner<P>::apply(it, end, point, wkt);
        handle_close_parenthesis(it, end, wkt);
    }
};


template <typename Geometry>
struct linestring_parser
{
    static inline void apply(tokenizer::iterator& it,
                             tokenizer::iterator const& end,
                             std::string const& wkt,
                             Geometry& geometry)
    {
        container_appender<Geometry&>::apply(it, end, wkt, geometry);
    }
};


template <typename Ring>
struct ring_parser
{
    static inline void apply(tokenizer::iterator& it,
                             tokenizer::iterator const& end,
                             std::string const& wkt,
                             Ring& ring)
    {
        // A ring should look like polygon((x y,x y,x y...))
        // So handle the extra opening/closing parentheses
        // and in between parse using the container-inserter
        handle_open_parenthesis(it, end, wkt);
        container_appender<Ring&>::apply(it, end, wkt, ring);
        handle_close_parenthesis(it, end, wkt);
    }
};


/*!
\brief Internal, parses a polygon from a string like this "((x y,x y),(x y,x y))"
\note used for parsing polygons and multi-polygons
*/
template <typename Polygon>
struct polygon_parser
{
    typedef typename ring_return_type<Polygon>::type ring_return_type;
    typedef container_appender<ring_return_type> appender;

    static inline void apply(tokenizer::iterator& it,
                             tokenizer::iterator const& end,
                             std::string const& wkt,
                             Polygon& poly)
    {

        handle_open_parenthesis(it, end, wkt);

        int n = -1;

        // Stop at ")"
        while (it != end && *it != ")")
        {
            // Parse ring
            if (++n == 0)
            {
                appender::apply(it, end, wkt, exterior_ring(poly));
            }
            else
            {
                typename ring_type<Polygon>::type ring;
                appender::apply(it, end, wkt, ring);
                traits::push_back
                    <
                        typename boost::remove_reference
                        <
                            typename traits::interior_mutable_type<Polygon>::type
                        >::type
                    >::apply(interior_rings(poly), ring);
            }

            if (it != end && *it == ",")
            {
                // Skip "," after ring is parsed
                ++it;
            }
        }

        handle_close_parenthesis(it, end, wkt);
    }
};


inline bool one_of(tokenizer::iterator const& it,
                   std::string const& value,
                   bool& is_present)
{
    if (boost::iequals(*it, value))
    {
        is_present = true;
        return true;
    }
    return false;
}

inline bool one_of(tokenizer::iterator const& it,
                   std::string const& value,
                   bool& present1,
                   bool& present2)
{
    if (boost::iequals(*it, value))
    {
        present1 = true;
        present2 = true;
        return true;
    }
    return false;
}


inline void handle_empty_z_m(tokenizer::iterator& it,
                             tokenizer::iterator const& end,
                             bool& has_empty,
                             bool& has_z,
                             bool& has_m)
{
    has_empty = false;
    has_z = false;
    has_m = false;

    // WKT can optionally have Z and M (measured) values as in
    // POINT ZM (1 1 5 60), POINT M (1 1 80), POINT Z (1 1 5)
    // GGL supports any of them as coordinate values, but is not aware
    // of any Measured value.
    while (it != end
           && (one_of(it, "M", has_m)
               || one_of(it, "Z", has_z)
               || one_of(it, "EMPTY", has_empty)
               || one_of(it, "MZ", has_m, has_z)
               || one_of(it, "ZM", has_z, has_m)
               )
           )
    {
        ++it;
    }
}

/*!
\brief Internal, starts parsing
\param tokens boost tokens, parsed with separator " " and keeping separator "()"
\param geometry string to compare with first token
*/
template <typename Geometry>
inline bool initialize(tokenizer const& tokens,
                       std::string const& geometry_name,
                       std::string const& wkt,
                       tokenizer::iterator& it,
                       tokenizer::iterator& end)
{
    it = tokens.begin();
    end = tokens.end();

    if (it == end || ! boost::iequals(*it++, geometry_name))
    {
        BOOST_THROW_EXCEPTION(read_wkt_exception(std::string("Should start with '") + geometry_name + "'", wkt));
    }

    bool has_empty, has_z, has_m;

    handle_empty_z_m(it, end, has_empty, has_z, has_m);

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)  
#pragma warning(disable : 4127)  
#endif

    if (has_z && dimension<Geometry>::type::value < 3)
    {
        BOOST_THROW_EXCEPTION(read_wkt_exception("Z only allowed for 3 or more dimensions", wkt));
    }

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

    if (has_empty)
    {
        check_end(it, end, wkt);
        return false;
    }
    // M is ignored at all.
    
    return true;
}


template <typename Geometry, template<typename> class Parser, typename PrefixPolicy>
struct geometry_parser
{
    static inline void apply(std::string const& wkt, Geometry& geometry)
    {
        geometry::clear(geometry);

        tokenizer tokens(wkt, boost::char_separator<char>(" ", ",()"));
        tokenizer::iterator it, end;
        if (initialize<Geometry>(tokens, PrefixPolicy::apply(), wkt, it, end))
        {
            Parser<Geometry>::apply(it, end, wkt, geometry);
            check_end(it, end, wkt);
        }
    }
};


template <typename MultiGeometry, template<typename> class Parser, typename PrefixPolicy>
struct multi_parser
{
    static inline void apply(std::string const& wkt, MultiGeometry& geometry)
    {
        traits::clear<MultiGeometry>::apply(geometry);

        tokenizer tokens(wkt, boost::char_separator<char>(" ", ",()"));
        tokenizer::iterator it, end;
        if (initialize<MultiGeometry>(tokens, PrefixPolicy::apply(), wkt, it, end))
        {
            handle_open_parenthesis(it, end, wkt);

            // Parse sub-geometries
            while(it != end && *it != ")")
            {
                traits::resize<MultiGeometry>::apply(geometry, boost::size(geometry) + 1);
                Parser
                    <
                        typename boost::range_value<MultiGeometry>::type
                    >::apply(it, end, wkt, *(boost::end(geometry) - 1));
                if (it != end && *it == ",")
                {
                    // Skip "," after multi-element is parsed
                    ++it;
                }
            }

            handle_close_parenthesis(it, end, wkt);
        }

        check_end(it, end, wkt);
    }
};

template <typename P>
struct noparenthesis_point_parser
{
    static inline void apply(tokenizer::iterator& it,
                             tokenizer::iterator const& end,
                             std::string const& wkt,
                             P& point)
    {
        parsing_assigner<P>::apply(it, end, point, wkt);
    }
};

template <typename MultiGeometry, typename PrefixPolicy>
struct multi_point_parser
{
    static inline void apply(std::string const& wkt, MultiGeometry& geometry)
    {
        traits::clear<MultiGeometry>::apply(geometry);

        tokenizer tokens(wkt, boost::char_separator<char>(" ", ",()"));
        tokenizer::iterator it, end;

        if (initialize<MultiGeometry>(tokens, PrefixPolicy::apply(), wkt, it, end))
        {
            handle_open_parenthesis(it, end, wkt);

            // If first point definition starts with "(" then parse points as (x y)
            // otherwise as "x y"
            bool using_brackets = (it != end && *it == "(");

            while(it != end && *it != ")")
            {
                traits::resize<MultiGeometry>::apply(geometry, boost::size(geometry) + 1);

                if (using_brackets)
                {
                    point_parser
                        <
                            typename boost::range_value<MultiGeometry>::type
                        >::apply(it, end, wkt, *(boost::end(geometry) - 1));
                }
                else
                {
                    noparenthesis_point_parser
                        <
                            typename boost::range_value<MultiGeometry>::type
                        >::apply(it, end, wkt, *(boost::end(geometry) - 1));
                }

                if (it != end && *it == ",")
                {
                    // Skip "," after point is parsed
                    ++it;
                }
            }

            handle_close_parenthesis(it, end, wkt);
        }

        check_end(it, end, wkt);
    }
};


/*!
\brief Supports box parsing
\note OGC does not define the box geometry, and WKT does not support boxes.
    However, to be generic GGL supports reading and writing from and to boxes.
    Boxes are outputted as a standard POLYGON. GGL can read boxes from
    a standard POLYGON, from a POLYGON with 2 points of from a BOX
\tparam Box the box
*/
template <typename Box>
struct box_parser
{
    static inline void apply(std::string const& wkt, Box& box)
    {
        bool should_close = false;
        tokenizer tokens(wkt, boost::char_separator<char>(" ", ",()"));
        tokenizer::iterator it = tokens.begin();
        tokenizer::iterator end = tokens.end();
        if (it != end && boost::iequals(*it, "POLYGON"))
        {
            ++it;
            bool has_empty, has_z, has_m;
            handle_empty_z_m(it, end, has_empty, has_z, has_m);
            if (has_empty)
            {
                assign_zero(box);
                return;
            }
            handle_open_parenthesis(it, end, wkt);
            should_close = true;
        }
        else if (it != end && boost::iequals(*it, "BOX"))
        {
            ++it;
        }
        else
        {
            BOOST_THROW_EXCEPTION(read_wkt_exception("Should start with 'POLYGON' or 'BOX'", wkt));
        }

        typedef typename point_type<Box>::type point_type;
        std::vector<point_type> points;
        container_inserter<point_type>::apply(it, end, wkt, std::back_inserter(points));

        if (should_close)
        {
            handle_close_parenthesis(it, end, wkt);
        }
        check_end(it, end, wkt);

        unsigned int index = 0;
        std::size_t n = boost::size(points);
        if (n == 2)
        {
            index = 1;
        }
        else if (n == 4 || n == 5)
        {
            // In case of 4 or 5 points, we do not check the other ones, just
            // take the opposite corner which is always 2
            index = 2;
        }
        else
        {
            BOOST_THROW_EXCEPTION(read_wkt_exception("Box should have 2,4 or 5 points", wkt));
        }

        geometry::detail::assign_point_to_index<min_corner>(points.front(), box);
        geometry::detail::assign_point_to_index<max_corner>(points[index], box);
    }
};


/*!
\brief Supports segment parsing
\note OGC does not define the segment, and WKT does not support segmentes.
    However, it is useful to implement it, also for testing purposes
\tparam Segment the segment
*/
template <typename Segment>
struct segment_parser
{
    static inline void apply(std::string const& wkt, Segment& segment)
    {
        tokenizer tokens(wkt, boost::char_separator<char>(" ", ",()"));
        tokenizer::iterator it = tokens.begin();
        tokenizer::iterator end = tokens.end();
        if (it != end &&
            (boost::iequals(*it, "SEGMENT")
            || boost::iequals(*it, "LINESTRING") ))
        {
            ++it;
        }
        else
        {
            BOOST_THROW_EXCEPTION(read_wkt_exception("Should start with 'LINESTRING' or 'SEGMENT'", wkt));
        }

        typedef typename point_type<Segment>::type point_type;
        std::vector<point_type> points;
        container_inserter<point_type>::apply(it, end, wkt, std::back_inserter(points));

        check_end(it, end, wkt);

        if (boost::size(points) == 2)
        {
            geometry::detail::assign_point_to_index<0>(points.front(), segment);
            geometry::detail::assign_point_to_index<1>(points.back(), segment);
        }
        else
        {
            BOOST_THROW_EXCEPTION(read_wkt_exception("Segment should have 2 points", wkt));
        }

    }
};


}} // namespace detail::wkt
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Tag, typename Geometry>
struct read_wkt {};


template <typename Point>
struct read_wkt<point_tag, Point>
    : detail::wkt::geometry_parser
        <
            Point,
            detail::wkt::point_parser,
            detail::wkt::prefix_point
        >
{};


template <typename L>
struct read_wkt<linestring_tag, L>
    : detail::wkt::geometry_parser
        <
            L,
            detail::wkt::linestring_parser,
            detail::wkt::prefix_linestring
        >
{};

template <typename Ring>
struct read_wkt<ring_tag, Ring>
    : detail::wkt::geometry_parser
        <
            Ring,
            detail::wkt::ring_parser,
            detail::wkt::prefix_polygon
        >
{};

template <typename Geometry>
struct read_wkt<polygon_tag, Geometry>
    : detail::wkt::geometry_parser
        <
            Geometry,
            detail::wkt::polygon_parser,
            detail::wkt::prefix_polygon
        >
{};


template <typename MultiGeometry>
struct read_wkt<multi_point_tag, MultiGeometry>
    : detail::wkt::multi_point_parser
            <
                MultiGeometry,
                detail::wkt::prefix_multipoint
            >
{};

template <typename MultiGeometry>
struct read_wkt<multi_linestring_tag, MultiGeometry>
    : detail::wkt::multi_parser
            <
                MultiGeometry,
                detail::wkt::linestring_parser,
                detail::wkt::prefix_multilinestring
            >
{};

template <typename MultiGeometry>
struct read_wkt<multi_polygon_tag, MultiGeometry>
    : detail::wkt::multi_parser
            <
                MultiGeometry,
                detail::wkt::polygon_parser,
                detail::wkt::prefix_multipolygon
            >
{};


// Box (Non-OGC)
template <typename Box>
struct read_wkt<box_tag, Box>
    : detail::wkt::box_parser<Box>
{};

// Segment (Non-OGC)
template <typename Segment>
struct read_wkt<segment_tag, Segment>
    : detail::wkt::segment_parser<Segment>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

/*!
\brief Parses OGC Well-Known Text (\ref WKT) into a geometry (any geometry)
\ingroup wkt
\tparam Geometry \tparam_geometry
\param wkt string containing \ref WKT
\param geometry \param_geometry output geometry
\ingroup wkt
\qbk{[include reference/io/read_wkt.qbk]}
*/
template <typename Geometry>
inline void read_wkt(std::string const& wkt, Geometry& geometry)
{
    geometry::concepts::check<Geometry>();
    dispatch::read_wkt<typename tag<Geometry>::type, Geometry>::apply(wkt, geometry);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_IO_WKT_READ_HPP

/* read.hpp
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
*/