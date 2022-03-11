// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_IO_DSV_WRITE_HPP
#define BOOST_GEOMETRY_IO_DSV_WRITE_HPP

#include <cstddef>
#include <ostream>
#include <string>

#include <boost/concept_check.hpp>
#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>

#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace dsv
{

struct dsv_settings
{
    std::string coordinate_separator;
    std::string point_open;
    std::string point_close;
    std::string point_separator;
    std::string list_open;
    std::string list_close;
    std::string list_separator;

    dsv_settings(std::string const& sep
            , std::string const& open
            , std::string const& close
            , std::string const& psep
            , std::string const& lopen
            , std::string const& lclose
            , std::string const& lsep
            )
        : coordinate_separator(sep)
        , point_open(open)
        , point_close(close)
        , point_separator(psep)
        , list_open(lopen)
        , list_close(lclose)
        , list_separator(lsep)
    {}
};

/*!
\brief Stream coordinate of a point as \ref DSV
*/
template <typename Point, std::size_t Dimension, std::size_t Count>
struct stream_coordinate
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Point const& point,
            dsv_settings const& settings)
    {
        os << (Dimension > 0 ? settings.coordinate_separator : "")
            << get<Dimension>(point);

        stream_coordinate
            <
                Point, Dimension + 1, Count
            >::apply(os, point, settings);
    }
};

template <typename Point, std::size_t Count>
struct stream_coordinate<Point, Count, Count>
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>&,
            Point const&,
            dsv_settings const& )
    {
    }
};

/*!
\brief Stream indexed coordinate of a box/segment as \ref DSV
*/
template
<
    typename Geometry,
    std::size_t Index,
    std::size_t Dimension,
    std::size_t Count
>
struct stream_indexed
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Geometry const& geometry,
            dsv_settings const& settings)
    {
        os << (Dimension > 0 ? settings.coordinate_separator : "")
            << get<Index, Dimension>(geometry);
        stream_indexed
            <
                Geometry, Index, Dimension + 1, Count
            >::apply(os, geometry, settings);
    }
};

template <typename Geometry, std::size_t Index, std::size_t Count>
struct stream_indexed<Geometry, Index, Count, Count>
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>&, Geometry const&,
            dsv_settings const& )
    {
    }
};

/*!
\brief Stream points as \ref DSV
*/
template <typename Point>
struct dsv_point
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Point const& p,
            dsv_settings const& settings)
    {
        os << settings.point_open;
        stream_coordinate<Point, 0, dimension<Point>::type::value>::apply(os, p, settings);
        os << settings.point_close;
    }
};

/*!
\brief Stream ranges as DSV
\note policy is used to stream prefix/postfix, enabling derived classes to override this
*/
template <typename Range>
struct dsv_range
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Range const& range,
            dsv_settings const& settings)
    {
        typedef typename boost::range_iterator<Range const>::type iterator_type;

        bool first = true;

        os << settings.list_open;

        for (iterator_type it = boost::begin(range);
            it != boost::end(range);
            ++it)
        {
            os << (first ? "" : settings.point_separator)
                << settings.point_open;

            stream_coordinate
                <
                    point_type, 0, dimension<point_type>::type::value
                >::apply(os, *it, settings);
            os << settings.point_close;

            first = false;
        }

        os << settings.list_close;
    }

private:
    typedef typename boost::range_value<Range>::type point_type;
};

/*!
\brief Stream sequence of points as DSV-part, e.g. (1 2),(3 4)
\note Used in polygon, all multi-geometries
*/

template <typename Polygon>
struct dsv_poly
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Polygon const& poly,
                dsv_settings const& settings)
    {
        typedef typename ring_type<Polygon>::type ring;

        os << settings.list_open;

        dsv_range<ring>::apply(os, exterior_ring(poly), settings);

        typename interior_return_type<Polygon const>::type
            rings = interior_rings(poly);
        for (typename detail::interior_iterator<Polygon const>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            os << settings.list_separator;
            dsv_range<ring>::apply(os, *it, settings);
        }
        os << settings.list_close;
    }
};

template <typename Geometry, std::size_t Index>
struct dsv_per_index
{
    typedef typename point_type<Geometry>::type point_type;

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Geometry const& geometry,
            dsv_settings const& settings)
    {
        os << settings.point_open;
        stream_indexed
            <
                Geometry, Index, 0, dimension<Geometry>::type::value
            >::apply(os, geometry, settings);
        os << settings.point_close;
    }
};

template <typename Geometry>
struct dsv_indexed
{
    typedef typename point_type<Geometry>::type point_type;

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Geometry const& geometry,
            dsv_settings const& settings)
    {
        os << settings.list_open;
        dsv_per_index<Geometry, 0>::apply(os, geometry, settings);
        os << settings.point_separator;
        dsv_per_index<Geometry, 1>::apply(os, geometry, settings);
        os << settings.list_close;
    }
};

}} // namespace detail::dsv
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Tag, typename Geometry>
struct dsv {};

template <typename Point>
struct dsv<point_tag, Point>
    : detail::dsv::dsv_point<Point>
{};

template <typename Linestring>
struct dsv<linestring_tag, Linestring>
    : detail::dsv::dsv_range<Linestring>
{};

template <typename Box>
struct dsv<box_tag, Box>
    : detail::dsv::dsv_indexed<Box>
{};

template <typename Segment>
struct dsv<segment_tag, Segment>
    : detail::dsv::dsv_indexed<Segment>
{};

template <typename Ring>
struct dsv<ring_tag, Ring>
    : detail::dsv::dsv_range<Ring>
{};

template <typename Polygon>
struct dsv<polygon_tag, Polygon>
    : detail::dsv::dsv_poly<Polygon>
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace dsv
{

// FIXME: This class is not copyable/assignable but it is used as such --mloskot
template <typename Geometry>
class dsv_manipulator
{
public:

    inline dsv_manipulator(Geometry const& g,
            dsv_settings const& settings)
        : m_geometry(g)
        , m_settings(settings)
    {}

    template <typename Char, typename Traits>
    inline friend std::basic_ostream<Char, Traits>& operator<<(
            std::basic_ostream<Char, Traits>& os,
            dsv_manipulator const& m)
    {
        dispatch::dsv
            <
                typename tag_cast
                    <
                        typename tag<Geometry>::type,
                        multi_tag
                    >::type,
                Geometry
            >::apply(os, m.m_geometry, m.m_settings);
        os.flush();
        return os;
    }

private:
    Geometry const& m_geometry;
    dsv_settings m_settings;
};


template <typename MultiGeometry>
struct dsv_multi
{
    typedef dispatch::dsv
                <
                    typename single_tag_of
                        <
                            typename tag<MultiGeometry>::type
                        >::type,
                    typename boost::range_value<MultiGeometry>::type
                > dispatch_one;

    typedef typename boost::range_iterator
        <
            MultiGeometry const
        >::type iterator;


    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                MultiGeometry const& multi,
                dsv_settings const& settings)
    {
        os << settings.list_open;

        bool first = true;
        for(iterator it = boost::begin(multi);
            it != boost::end(multi);
            ++it, first = false)
        {
            os << (first ? "" : settings.list_separator);
            dispatch_one::apply(os, *it, settings);
        }
        os << settings.list_close;
    }
};

}} // namespace detail::dsv
#endif // DOXYGEN_NO_DETAIL

// TODO: The alternative to this could be a forward declaration of dispatch::dsv<>
//       or braking the code into the interface and implementation part
#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Geometry>
struct dsv<multi_tag, Geometry>
    : detail::dsv::dsv_multi<Geometry>
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

/*!
\brief Main DSV-streaming function
\details DSV stands for Delimiter Separated Values. Geometries can be streamed
    as DSV. There are defaults for all separators.
\note Useful for examples and testing purposes
\note With this function GeoJSON objects can be created, using the right
    delimiters
\ingroup dsv
*/
template <typename Geometry>
inline detail::dsv::dsv_manipulator<Geometry> dsv(Geometry const& geometry
    , std::string const& coordinate_separator = ", "
    , std::string const& point_open = "("
    , std::string const& point_close = ")"
    , std::string const& point_separator = ", "
    , std::string const& list_open = "("
    , std::string const& list_close = ")"
    , std::string const& list_separator = ", "
    )
{
    concepts::check<Geometry const>();

    return detail::dsv::dsv_manipulator<Geometry>(geometry,
        detail::dsv::dsv_settings(coordinate_separator,
            point_open, point_close, point_separator,
            list_open, list_close, list_separator));
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_IO_DSV_WRITE_HPP

/* write.hpp
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
*/