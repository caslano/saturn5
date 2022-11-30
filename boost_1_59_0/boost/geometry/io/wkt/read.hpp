// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2020 Baidyanath Kundu, Haldia, India

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021 Oracle and/or its affiliates.

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
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>
#include <boost/throw_exception.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_point.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/exception.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/geometry_id.hpp>
#include <boost/geometry/core/geometry_types.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For consistency with other functions
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/io/wkt/detail/prefix.hpp>

#include <boost/geometry/strategies/io/cartesian.hpp>
#include <boost/geometry/strategies/io/geographic.hpp>
#include <boost/geometry/strategies/io/spherical.hpp>

#include <boost/geometry/util/coordinate_cast.hpp>
#include <boost/geometry/util/range.hpp>
#include <boost/geometry/util/sequence.hpp>
#include <boost/geometry/util/type_traits.hpp>

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
            typename util::remove_cptrref<Geometry>::type
        >::type size_type;

    BOOST_STATIC_ASSERT(( util::is_ring<Geometry>::value ));

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
        typedef typename strategies::io::services::default_strategy
            <
                point_type
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
                range::push_back(geometry::interior_rings(poly), std::move(ring));
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


template <typename Geometry, typename Tag = typename geometry::tag<Geometry>::type>
struct dimension
    : geometry::dimension<Geometry>
{};

// TODO: For now assume the dimension of the first type defined for GC
//       This should probably be unified for all algorithms
template <typename Geometry>
struct dimension<Geometry, geometry_collection_tag>
    : geometry::dimension
        <
            typename util::sequence_front
                <
                    typename traits::geometry_types<Geometry>::type
                >::type
        >
{};


/*!
\brief Internal, starts parsing
\param geometry_name string to compare with first token
*/
template <typename Geometry>
inline bool initialize(tokenizer::iterator& it,
                       tokenizer::iterator const& end,
                       std::string const& wkt,
                       std::string const& geometry_name)
{
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

    if (has_z && dimension<Geometry>::value < 3)
    {
        BOOST_THROW_EXCEPTION(read_wkt_exception("Z only allowed for 3 or more dimensions", wkt));
    }

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

    if (has_empty)
    {
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
        tokenizer::iterator it = tokens.begin();
        tokenizer::iterator const end = tokens.end();

        apply(it, end, wkt, geometry);

        check_end(it, end, wkt);
    }

    static inline void apply(tokenizer::iterator& it,
                             tokenizer::iterator const& end,
                             std::string const& wkt,
                             Geometry& geometry)
    {
        if (initialize<Geometry>(it, end, wkt, PrefixPolicy::apply()))
        {
            Parser<Geometry>::apply(it, end, wkt, geometry);
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
        tokenizer::iterator it = tokens.begin();
        tokenizer::iterator const end = tokens.end();

        apply(it, end, wkt, geometry);

        check_end(it, end, wkt);
    }

    static inline void apply(tokenizer::iterator& it,
                             tokenizer::iterator const& end,
                             std::string const& wkt,
                             MultiGeometry& geometry)
    {
        if (initialize<MultiGeometry>(it, end, wkt, PrefixPolicy::apply()))
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
        tokenizer::iterator it = tokens.begin();
        tokenizer::iterator const end = tokens.end();

        apply(it, end, wkt, geometry);

        check_end(it, end, wkt);
    }

    static inline void apply(tokenizer::iterator& it,
                             tokenizer::iterator const& end,
                             std::string const& wkt,
                             MultiGeometry& geometry)
    {
        if (initialize<MultiGeometry>(it, end, wkt, PrefixPolicy::apply()))
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
        tokenizer tokens(wkt, boost::char_separator<char>(" ", ",()"));
        tokenizer::iterator it = tokens.begin();
        tokenizer::iterator end = tokens.end();

        apply(it, end, wkt, box);

        check_end(it, end, wkt);
    }

    static inline void apply(tokenizer::iterator& it,
                             tokenizer::iterator const& end,
                             std::string const& wkt,
                             Box& box)
    {
        bool should_close = false;
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

        apply(it, end, wkt, segment);

        check_end(it, end, wkt);
    }

    static inline void apply(tokenizer::iterator& it,
                             tokenizer::iterator const& end,
                             std::string const& wkt,
                             Segment& segment)
    {
        if (it != end && (boost::iequals(*it, "SEGMENT") || boost::iequals(*it, "LINESTRING")))
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


struct dynamic_move_assign
{
    template <typename DynamicGeometry, typename Geometry>
    static void apply(DynamicGeometry& dynamic_geometry, Geometry & geometry)
    {
        dynamic_geometry = std::move(geometry);
    }
};

struct dynamic_move_emplace_back
{
    template <typename GeometryCollection, typename Geometry>
    static void apply(GeometryCollection& geometry_collection, Geometry & geometry)
    {
        traits::emplace_back<GeometryCollection>::apply(geometry_collection, std::move(geometry));
    }
};

template
<
    typename Geometry,
    template <typename, typename> class ReadWkt,
    typename AppendPolicy
>
struct dynamic_readwkt_caller
{
    static inline void apply(tokenizer::iterator& it,
                             tokenizer::iterator const& end,
                             std::string const& wkt,
                             Geometry& geometry)
    {
        if (boost::iequals(*it, "POINT"))
        {
            parse_geometry<util::is_point>("POINT", it, end, wkt, geometry);
        }
        else if (boost::iequals(*it, "MULTIPOINT"))
        {
            parse_geometry<util::is_multi_point>("MULTIPOINT", it, end, wkt, geometry);
        }
        else if (boost::iequals(*it, "SEGMENT"))
        {
            parse_geometry<util::is_segment>("SEGMENT", it, end, wkt, geometry);
        }
        else if (boost::iequals(*it, "LINESTRING"))
        {
            parse_geometry<util::is_linestring>("LINESTRING", it, end, wkt, geometry, false)
            || parse_geometry<util::is_segment>("LINESTRING", it, end, wkt, geometry);
        }
        else if (boost::iequals(*it, "MULTILINESTRING"))
        {
            parse_geometry<util::is_multi_linestring>("MULTILINESTRING", it, end, wkt, geometry);
        }
        else if (boost::iequals(*it, "BOX"))
        {
            parse_geometry<util::is_box>("BOX", it, end, wkt, geometry);
        }
        else if (boost::iequals(*it, "POLYGON"))
        {
            parse_geometry<util::is_polygon>("POLYGON", it, end, wkt, geometry, false)
            || parse_geometry<util::is_ring>("POLYGON", it, end, wkt, geometry, false)
            || parse_geometry<util::is_box>("POLYGON", it, end, wkt, geometry);
        }
        else if (boost::iequals(*it, "MULTIPOLYGON"))
        {
            parse_geometry<util::is_multi_polygon>("MULTIPOLYGON", it, end, wkt, geometry);
        }
        else if (boost::iequals(*it, "GEOMETRYCOLLECTION"))
        {
            parse_geometry<util::is_geometry_collection>("GEOMETRYCOLLECTION", it, end, wkt, geometry);
        }
        else
        {
            BOOST_THROW_EXCEPTION(read_wkt_exception(
                "Should start with geometry's name, e.g. 'POINT', 'LINESTRING', 'POLYGON', etc.",
                wkt));
        }
    }

private:
    template
    <
        template <typename> class UnaryPred,
        typename Geom = typename util::sequence_find_if
            <
                typename traits::geometry_types<Geometry>::type, UnaryPred
            >::type,
        std::enable_if_t<! std::is_void<Geom>::value, int> = 0
    >
    static bool parse_geometry(const char * ,
                               tokenizer::iterator& it,
                               tokenizer::iterator const& end,
                               std::string const& wkt,
                               Geometry& geometry,
                               bool = true)
    {
        Geom g;
        ReadWkt<Geom, typename tag<Geom>::type>::apply(it, end, wkt, g);
        AppendPolicy::apply(geometry, g);
        return true;
    }

    template
    <
        template <typename> class UnaryPred,
        typename Geom = typename util::sequence_find_if
            <
                typename traits::geometry_types<Geometry>::type, UnaryPred
            >::type,
        std::enable_if_t<std::is_void<Geom>::value, int> = 0
    >
    static bool parse_geometry(const char * name,
                               tokenizer::iterator& ,
                               tokenizer::iterator const& ,
                               std::string const& wkt,
                               Geometry& ,
                               bool throw_on_misfit = true)
    {
        if (throw_on_misfit)
        {
            std::string msg = std::string("Unable to store '") + name + "' in this geometry";
            BOOST_THROW_EXCEPTION(read_wkt_exception(msg, wkt));
        }

        return false;
    }
};


}} // namespace detail::wkt
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct read_wkt {};


template <typename Point>
struct read_wkt<Point, point_tag>
    : detail::wkt::geometry_parser
        <
            Point,
            detail::wkt::point_parser,
            detail::wkt::prefix_point
        >
{};


template <typename L>
struct read_wkt<L, linestring_tag>
    : detail::wkt::geometry_parser
        <
            L,
            detail::wkt::linestring_parser,
            detail::wkt::prefix_linestring
        >
{};

template <typename Ring>
struct read_wkt<Ring, ring_tag>
    : detail::wkt::geometry_parser
        <
            Ring,
            detail::wkt::ring_parser,
            detail::wkt::prefix_polygon
        >
{};

template <typename Geometry>
struct read_wkt<Geometry, polygon_tag>
    : detail::wkt::geometry_parser
        <
            Geometry,
            detail::wkt::polygon_parser,
            detail::wkt::prefix_polygon
        >
{};


template <typename MultiGeometry>
struct read_wkt<MultiGeometry, multi_point_tag>
    : detail::wkt::multi_point_parser
            <
                MultiGeometry,
                detail::wkt::prefix_multipoint
            >
{};

template <typename MultiGeometry>
struct read_wkt<MultiGeometry, multi_linestring_tag>
    : detail::wkt::multi_parser
            <
                MultiGeometry,
                detail::wkt::linestring_parser,
                detail::wkt::prefix_multilinestring
            >
{};

template <typename MultiGeometry>
struct read_wkt<MultiGeometry, multi_polygon_tag>
    : detail::wkt::multi_parser
            <
                MultiGeometry,
                detail::wkt::polygon_parser,
                detail::wkt::prefix_multipolygon
            >
{};


// Box (Non-OGC)
template <typename Box>
struct read_wkt<Box, box_tag>
    : detail::wkt::box_parser<Box>
{};

// Segment (Non-OGC)
template <typename Segment>
struct read_wkt<Segment, segment_tag>
    : detail::wkt::segment_parser<Segment>
{};


template <typename DynamicGeometry>
struct read_wkt<DynamicGeometry, dynamic_geometry_tag>
{
    static inline void apply(std::string const& wkt, DynamicGeometry& dynamic_geometry)
    {
        detail::wkt::tokenizer tokens(wkt, boost::char_separator<char>(" ", ",()"));
        detail::wkt::tokenizer::iterator it = tokens.begin();
        detail::wkt::tokenizer::iterator end = tokens.end();
        if (it == end)
        {
            BOOST_THROW_EXCEPTION(read_wkt_exception(
                "Should start with geometry's name, e.g. 'POINT', 'LINESTRING', 'POLYGON', etc.",
                wkt));
        }

        detail::wkt::dynamic_readwkt_caller
            <
                DynamicGeometry, dispatch::read_wkt, detail::wkt::dynamic_move_assign
            >::apply(it, end, wkt, dynamic_geometry);

        detail::wkt::check_end(it, end, wkt);
    }
};


template <typename Geometry>
struct read_wkt<Geometry, geometry_collection_tag>
{
    static inline void apply(std::string const& wkt, Geometry& geometry)
    {
        range::clear(geometry);

        detail::wkt::tokenizer tokens(wkt, boost::char_separator<char>(" ", ",()"));
        detail::wkt::tokenizer::iterator it = tokens.begin();
        detail::wkt::tokenizer::iterator const end = tokens.end();

        apply(it, end, wkt, geometry);

        detail::wkt::check_end(it, end, wkt);
    }

    static inline void apply(detail::wkt::tokenizer::iterator& it,
                             detail::wkt::tokenizer::iterator const& end,
                             std::string const& wkt,
                             Geometry& geometry)
    {
        if (detail::wkt::initialize<Geometry>(it, end, wkt, "GEOMETRYCOLLECTION"))
        {
            detail::wkt::handle_open_parenthesis(it, end, wkt);

            // Stop at ")"
            while (it != end && *it != ")")
            {
                detail::wkt::dynamic_readwkt_caller
                    <
                        Geometry, dispatch::read_wkt, detail::wkt::dynamic_move_emplace_back
                    >::apply(it, end, wkt, geometry);

                if (it != end && *it == ",")
                {
                    // Skip "," after geometry is parsed
                    ++it;
                }
            }

            detail::wkt::handle_close_parenthesis(it, end, wkt);
        }
    }
};


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
    dispatch::read_wkt<Geometry>::apply(wkt, geometry);
}

/*!
\brief Parses OGC Well-Known Text (\ref WKT) into a geometry (any geometry) and returns it
\ingroup wkt
\tparam Geometry \tparam_geometry
\param wkt string containing \ref WKT
\ingroup wkt
\qbk{[include reference/io/from_wkt.qbk]}
*/
template <typename Geometry>
inline Geometry from_wkt(std::string const& wkt)
{
    Geometry geometry;
    geometry::concepts::check<Geometry>();
    dispatch::read_wkt<Geometry>::apply(wkt, geometry);
    return geometry;
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_IO_WKT_READ_HPP

/* read.hpp
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
*/