// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2017 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2017 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2017 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2017 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2020 Baidyanath Kundu, Haldia, India.

// This file was modified by Oracle on 2015-2021.
// Modifications copyright (c) 2015-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_IO_WKT_WRITE_HPP
#define BOOST_GEOMETRY_IO_WKT_WRITE_HPP

#include <ostream>
#include <string>

#include <boost/array.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_point.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/geometries/ring.hpp>

#include <boost/geometry/io/wkt/detail/prefix.hpp>

#include <boost/geometry/strategies/io/cartesian.hpp>
#include <boost/geometry/strategies/io/geographic.hpp>
#include <boost/geometry/strategies/io/spherical.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/type_traits.hpp>


namespace boost { namespace geometry
{

// Silence warning C4512: 'boost::geometry::wkt_manipulator<Geometry>' : assignment operator could not be generated
#if defined(_MSC_VER)
#pragma warning(push)  
#pragma warning(disable : 4512)  
#endif

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace wkt
{

template <typename P, int I, int Count>
struct stream_coordinate
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os, P const& p)
    {
        os << (I > 0 ? " " : "") << get<I>(p);
        stream_coordinate<P, I + 1, Count>::apply(os, p);
    }
};

template <typename P, int Count>
struct stream_coordinate<P, Count, Count>
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>&, P const&)
    {}
};

struct prefix_linestring_par
{
    static inline const char* apply() { return "LINESTRING("; }
};

struct prefix_ring_par_par
{
    // Note, double parentheses are intentional, indicating WKT ring begin/end
    static inline const char* apply() { return "POLYGON(("; }
};

struct opening_parenthesis
{
    static inline const char* apply() { return "("; }
};

struct closing_parenthesis
{
    static inline const char* apply() { return ")"; }
};

struct double_closing_parenthesis
{
    static inline const char* apply() { return "))"; }
};

/*!
\brief Stream points as \ref WKT
*/
template <typename Point, typename Policy>
struct wkt_point
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os, Point const& p, bool)
    {
        os << Policy::apply() << "(";
        stream_coordinate<Point, 0, dimension<Point>::type::value>::apply(os, p);
        os << ")";
    }
};

/*!
\brief Stream ranges as WKT
\note policy is used to stream prefix/postfix, enabling derived classes to override this
*/
template
<
    typename Range,
    bool ForceClosurePossible,
    typename PrefixPolicy,
    typename SuffixPolicy
>
struct wkt_range
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Range const& range, bool force_closure = ForceClosurePossible)
    {
        typedef typename boost::range_iterator<Range const>::type iterator_type;

        typedef stream_coordinate
            <
                point_type, 0, dimension<point_type>::type::value
            > stream_type;

        bool first = true;

        os << PrefixPolicy::apply();

        // TODO: check EMPTY here

        iterator_type begin = boost::begin(range);
        iterator_type end = boost::end(range);
        for (iterator_type it = begin; it != end; ++it)
        {
            os << (first ? "" : ",");
            stream_type::apply(os, *it);
            first = false;
        }

        // optionally, close range to ring by repeating the first point
        if (BOOST_GEOMETRY_CONDITION(ForceClosurePossible)
            && force_closure
            && boost::size(range) > 1
            && wkt_range::disjoint(*begin, *(end - 1)))
        {
            os << ",";
            stream_type::apply(os, *begin);
        }

        os << SuffixPolicy::apply();
    }


private:
    typedef typename boost::range_value<Range>::type point_type;

    static inline bool disjoint(point_type const& p1, point_type const& p2)
    {
        // TODO: pass strategy
        typedef typename strategies::io::services::default_strategy
            <
                point_type
            >::type strategy_type;

        return detail::disjoint::disjoint_point_point(p1, p2, strategy_type());
    }
};

/*!
\brief Stream sequence of points as WKT-part, e.g. (1 2),(3 4)
\note Used in polygon, all multi-geometries
*/
template <typename Range, bool ForceClosurePossible = true>
struct wkt_sequence
    : wkt_range
        <
            Range,
            ForceClosurePossible,
            opening_parenthesis,
            closing_parenthesis
        >
{};

template <typename Polygon, typename PrefixPolicy>
struct wkt_poly
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Polygon const& poly, bool force_closure)
    {
        typedef typename ring_type<Polygon const>::type ring;

        os << PrefixPolicy::apply();
        // TODO: check EMPTY here
        os << "(";
        wkt_sequence<ring>::apply(os, exterior_ring(poly), force_closure);

        typename interior_return_type<Polygon const>::type
            rings = interior_rings(poly);
        for (typename detail::interior_iterator<Polygon const>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            os << ",";
            wkt_sequence<ring>::apply(os, *it, force_closure);
        }
        os << ")";
    }

};

template <typename Multi, typename StreamPolicy, typename PrefixPolicy>
struct wkt_multi
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Multi const& geometry, bool force_closure)
    {
        os << PrefixPolicy::apply();
        // TODO: check EMPTY here
        os << "(";

        for (typename boost::range_iterator<Multi const>::type
                    it = boost::begin(geometry);
            it != boost::end(geometry);
            ++it)
        {
            if (it != boost::begin(geometry))
            {
                os << ",";
            }
            StreamPolicy::apply(os, *it, force_closure);
        }

        os << ")";
    }
};

template <typename Box>
struct wkt_box
{
    typedef typename point_type<Box>::type point_type;

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Box const& box, bool force_closure)
    {
        // Convert to a clockwire ring, then stream.
        // Never close it based on last point (box might be empty and
        // that should result in POLYGON((0 0,0 0,0 0,0 0, ...)) )
        if (force_closure)
        {
            do_apply<model::ring<point_type, true, true> >(os, box);
        }
        else
        {
            do_apply<model::ring<point_type, true, false> >(os, box);
        }
    }

    private:

        inline wkt_box()
        {
            // Only streaming of boxes with two dimensions is support, otherwise it is a polyhedron!
            //assert_dimension<B, 2>();
        }

        template <typename RingType, typename Char, typename Traits>
        static inline void do_apply(std::basic_ostream<Char, Traits>& os,
                    Box const& box)
        {
            RingType ring;
            geometry::convert(box, ring);
            os << "POLYGON(";
            wkt_sequence<RingType, false>::apply(os, ring);
            os << ")";
        }

};


template <typename Segment>
struct wkt_segment
{
    typedef typename point_type<Segment>::type point_type;

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Segment const& segment, bool)
    {
        // Convert to two points, then stream
        typedef boost::array<point_type, 2> sequence;

        sequence points;
        geometry::detail::assign_point_from_index<0>(segment, points[0]);
        geometry::detail::assign_point_from_index<1>(segment, points[1]);

        // In Boost.Geometry a segment is represented
        // in WKT-format like (for 2D): LINESTRING(x y,x y)
        os << "LINESTRING";
        wkt_sequence<sequence, false>::apply(os, points);
    }

    private:

        inline wkt_segment()
        {}
};

}} // namespace detail::wkt
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct wkt: not_implemented<Tag>
{};

template <typename Point>
struct wkt<Point, point_tag>
    : detail::wkt::wkt_point
        <
            Point,
            detail::wkt::prefix_point
        >
{};

template <typename Linestring>
struct wkt<Linestring, linestring_tag>
    : detail::wkt::wkt_range
        <
            Linestring,
            false,
            detail::wkt::prefix_linestring_par,
            detail::wkt::closing_parenthesis
        >
{};

/*!
\brief Specialization to stream a box as WKT
\details A "box" does not exist in WKT.
It is therefore streamed as a polygon
*/
template <typename Box>
struct wkt<Box, box_tag>
    : detail::wkt::wkt_box<Box>
{};

template <typename Segment>
struct wkt<Segment, segment_tag>
    : detail::wkt::wkt_segment<Segment>
{};

/*!
\brief Specialization to stream a ring as WKT
\details A ring or "linear_ring" does not exist in WKT.
A ring is equivalent to a polygon without inner rings
It is therefore streamed as a polygon
*/
template <typename Ring>
struct wkt<Ring, ring_tag>
    : detail::wkt::wkt_range
        <
            Ring,
            true,
            detail::wkt::prefix_ring_par_par,
            detail::wkt::double_closing_parenthesis
        >
{};

/*!
\brief Specialization to stream polygon as WKT
*/
template <typename Polygon>
struct wkt<Polygon, polygon_tag>
    : detail::wkt::wkt_poly
        <
            Polygon,
            detail::wkt::prefix_polygon
        >
{};

template <typename Multi>
struct wkt<Multi, multi_point_tag>
    : detail::wkt::wkt_multi
        <
            Multi,
            detail::wkt::wkt_point
                <
                    typename boost::range_value<Multi>::type,
                    detail::wkt::prefix_null
                >,
            detail::wkt::prefix_multipoint
        >
{};

template <typename Multi>
struct wkt<Multi, multi_linestring_tag>
    : detail::wkt::wkt_multi
        <
            Multi,
            detail::wkt::wkt_sequence
                <
                    typename boost::range_value<Multi>::type,
                    false
                >,
            detail::wkt::prefix_multilinestring
        >
{};

template <typename Multi>
struct wkt<Multi, multi_polygon_tag>
    : detail::wkt::wkt_multi
        <
            Multi,
            detail::wkt::wkt_poly
                <
                    typename boost::range_value<Multi>::type,
                    detail::wkt::prefix_null
                >,
            detail::wkt::prefix_multipolygon
        >
{};


template <typename Geometry>
struct wkt<Geometry, dynamic_geometry_tag>
{
    template <typename OutputStream>
    static inline void apply(OutputStream& os, Geometry const& geometry,
                             bool force_closure)
    {
        traits::visit<Geometry>::apply([&](auto const& g)
        {
            wkt<util::remove_cref_t<decltype(g)>>::apply(os, g, force_closure);
        }, geometry);
    }
};

// TODO: Implement non-recursive version
template <typename Geometry>
struct wkt<Geometry, geometry_collection_tag>
{
    template <typename OutputStream>
    static inline void apply(OutputStream& os, Geometry const& geometry,
                             bool force_closure)
    {
        wkt::output_or_recursive_call(os, geometry, force_closure);
    }

private:
    template
    <
        typename OutputStream, typename Geom,
        std::enable_if_t<util::is_geometry_collection<Geom>::value, int> = 0
    >
    static void output_or_recursive_call(OutputStream& os, Geom const& geom, bool force_closure)
    {
        os << "GEOMETRYCOLLECTION(";

        bool first = true;
        auto const end = boost::end(geom);
        for (auto it = boost::begin(geom); it != end; ++it)
        {
            if (first)
                first = false;
            else
                os << ',';

            traits::iter_visit<Geom>::apply([&](auto const& g)
            {
                wkt::output_or_recursive_call(os, g, force_closure);
            }, it);
        }

        os << ')';
    }

    template
    <
        typename OutputStream, typename Geom,
        std::enable_if_t<! util::is_geometry_collection<Geom>::value, int> = 0
    >
    static void output_or_recursive_call(OutputStream& os, Geom const& geom, bool force_closure)
    {
        wkt<Geom>::apply(os, geom, force_closure);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

/*!
\brief Generic geometry template manipulator class, takes corresponding output class from traits class
\ingroup wkt
\details Stream manipulator, streams geometry classes as \ref WKT streams
\par Example:
Small example showing how to use the wkt class
\dontinclude doxygen_1.cpp
\skip example_as_wkt_point
\line {
\until }
*/
template <typename Geometry>
class wkt_manipulator
{
    static const bool is_ring = util::is_ring<Geometry>::value;

public:

    // Boost.Geometry, by default, closes polygons explictly, but not rings
    // NOTE: this might change in the future!
    inline wkt_manipulator(Geometry const& g,
                           bool force_closure = ! is_ring)
        : m_geometry(g)
        , m_force_closure(force_closure)
    {}

    template <typename Char, typename Traits>
    inline friend std::basic_ostream<Char, Traits>& operator<<(
            std::basic_ostream<Char, Traits>& os,
            wkt_manipulator const& m)
    {
        dispatch::wkt<Geometry>::apply(os, m.m_geometry, m.m_force_closure);
        os.flush();
        return os;
    }

private:
    Geometry const& m_geometry;
    bool m_force_closure;
};

/*!
\brief Main WKT-streaming function
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\ingroup wkt
\qbk{[include reference/io/wkt.qbk]}
*/
template <typename Geometry>
inline wkt_manipulator<Geometry> wkt(Geometry const& geometry)
{
    concepts::check<Geometry const>();

    return wkt_manipulator<Geometry>(geometry);
}

/*!
\brief WKT-string formulating function
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\param significant_digits Specifies the no of significant digits to use in the output wkt
\ingroup wkt
\qbk{[include reference/io/to_wkt.qbk]}
*/
template <typename Geometry>
inline std::string to_wkt(Geometry const& geometry)
{
    std::stringstream ss;
    ss << boost::geometry::wkt(geometry);
    return ss.str();
}

template <typename Geometry>
inline std::string to_wkt(Geometry const& geometry, int significant_digits)
{
    std::stringstream ss;
    ss.precision(significant_digits);
    ss << boost::geometry::wkt(geometry);
    return ss.str();
}

#if defined(_MSC_VER)
#pragma warning(pop)  
#endif

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_IO_WKT_WRITE_HPP

/* write.hpp
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
*/