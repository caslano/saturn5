// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2018-2020.
// Modifications copyright (c) 2018-2020, Oracle and/or its affiliates.
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
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

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