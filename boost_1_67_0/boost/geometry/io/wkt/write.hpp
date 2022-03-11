// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2017 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2017 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2017 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015, 2018, 2019.
// Modifications copyright (c) 2015-2019, Oracle and/or its affiliates.

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
#include <boost/range.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_point.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/geometries/ring.hpp>

#include <boost/geometry/io/wkt/detail/prefix.hpp>

#include <boost/geometry/util/condition.hpp>


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
        typedef typename strategy::disjoint::services::default_strategy
            <
                point_type, point_type
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
struct devarianted_wkt
{
    template <typename OutputStream>
    static inline void apply(OutputStream& os, Geometry const& geometry,
                             bool force_closure)
    {
        wkt<Geometry>::apply(os, geometry, force_closure);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct devarianted_wkt<variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename OutputStream>
    struct visitor: static_visitor<void>
    {
        OutputStream& m_os;
        bool m_force_closure;

        visitor(OutputStream& os, bool force_closure)
            : m_os(os)
            , m_force_closure(force_closure)
        {}

        template <typename Geometry>
        inline void operator()(Geometry const& geometry) const
        {
            devarianted_wkt<Geometry>::apply(m_os, geometry, m_force_closure);
        }
    };

    template <typename OutputStream>
    static inline void apply(
        OutputStream& os,
        variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
        bool force_closure)
    {
        boost::apply_visitor(visitor<OutputStream>(os, force_closure), geometry);
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
    static const bool is_ring = boost::is_same<typename tag<Geometry>::type, ring_tag>::value;

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
        dispatch::devarianted_wkt<Geometry>::apply(os, m.m_geometry, m.m_force_closure);
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

#if defined(_MSC_VER)
#pragma warning(pop)  
#endif

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_IO_WKT_WRITE_HPP

/* write.hpp
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
*/