// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_BOX_HPP
#define BOOST_GEOMETRY_GEOMETRIES_BOX_HPP

#include <cstddef>

#include <boost/concept/assert.hpp>
#include <boost/config.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>

#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
#include <boost/geometry/core/assert.hpp>
#endif


namespace boost { namespace geometry
{

namespace model
{

/*!
\brief Class box: defines a box made of two describing points
\ingroup geometries
\details Box is always described by a min_corner() and a max_corner() point. If another
    rectangle is used, use linear_ring or polygon.
\note Boxes are for selections and for calculating the envelope of geometries. Not all algorithms
are implemented for box. Boxes are also used in Spatial Indexes.
\tparam Point point type. The box takes a point type as template parameter.
The point type can be any point type.
It can be 2D but can also be 3D or more dimensional.
The box can also take a latlong point type as template parameter.

\qbk{[include reference/geometries/box.qbk]}
\qbk{before.synopsis, [heading Model of]}
\qbk{before.synopsis, [link geometry.reference.concepts.concept_box Box Concept]}
 */

template<typename Point>
class box
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

public:

#if !defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
#if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
    /// \constructor_default_no_init
    box() = default;
#else
    /// \constructor_default_no_init
    inline box()
    {}
#endif
#else // defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
    inline box()
    {
        m_created = 1;
    }
    ~box()
    {
        m_created = 0;
    }
#endif

    /*!
        \brief Constructor taking the minimum corner point and the maximum corner point
    */
    inline box(Point const& min_corner, Point const& max_corner)
    {
        geometry::convert(min_corner, m_min_corner);
        geometry::convert(max_corner, m_max_corner);

#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        m_created = 1;
#endif
    }

    inline Point const& min_corner() const
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        BOOST_GEOMETRY_ASSERT(m_created == 1);
#endif
        return m_min_corner;
    }
    inline Point const& max_corner() const
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        BOOST_GEOMETRY_ASSERT(m_created == 1);
#endif
        return m_max_corner;
    }

    inline Point& min_corner()
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        BOOST_GEOMETRY_ASSERT(m_created == 1);
#endif
        return m_min_corner;
    }
    inline Point& max_corner()
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        BOOST_GEOMETRY_ASSERT(m_created == 1);
#endif
        return m_max_corner;
    }

private:

    Point m_min_corner;
    Point m_max_corner;

#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
    int m_created;
#endif
};


} // namespace model


// Traits specializations for box above
#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename Point>
struct tag<model::box<Point> >
{
    typedef box_tag type;
};

template <typename Point>
struct point_type<model::box<Point> >
{
    typedef Point type;
};

template <typename Point, std::size_t Dimension>
struct indexed_access<model::box<Point>, min_corner, Dimension>
{
    typedef typename geometry::coordinate_type<Point>::type coordinate_type;

    static inline coordinate_type get(model::box<Point> const& b)
    {
        return geometry::get<Dimension>(b.min_corner());
    }

    static inline void set(model::box<Point>& b, coordinate_type const& value)
    {
        geometry::set<Dimension>(b.min_corner(), value);
    }
};

template <typename Point, std::size_t Dimension>
struct indexed_access<model::box<Point>, max_corner, Dimension>
{
    typedef typename geometry::coordinate_type<Point>::type coordinate_type;

    static inline coordinate_type get(model::box<Point> const& b)
    {
        return geometry::get<Dimension>(b.max_corner());
    }

    static inline void set(model::box<Point>& b, coordinate_type const& value)
    {
        geometry::set<Dimension>(b.max_corner(), value);
    }
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_BOX_HPP

/* box.hpp
mST3xAJhfWRIN5okjw/0wjWWcx6ZcmDopx0w8FB4iq+R4qOw1B6Z2xe4hu5YRcd7xkiXPCeUqsak1MFLnibQD1nibXpbxusNJNJkmscAzHea4uWwkEEYk1JqjX05jjO4FmMR3mNbWSSEVZ+ToO0j3a+V4/lAGdYQ5OEkOZ6OGiPxXQJrWzFbbyvIX5Vhb7LrGrGI2gqpazLi2LpWpQk6jA0MoYLjMY3iOQF4jsb0K6+VCQoGHclSE0nfBtpxwA5KB8pjPEIgctR+Nadr+Dp9nSKYuPIc+OXzIvoZeISRuY7tZ1WiOW5j2tB1vD4hxVDg0Xm5AvQv6ffkjgYvX/kqzVng1wh4hnSTFNwYW/kq/uyUEK1XcAPuYtA7KqvfChR43MHEsfpdasj7QNtP+xci0EvOR/u3PvZ/fIR+tiAUUYcexAr4QOdU56hW18U+T7IZEXsJO9nPui5m7QvNvYRIf/XNkJAsJ6Rj73q1p5Qps94v/cvgtwXwFPn3MvI9lWm716v53JpMlWcqPNcGtSfkRngJidJ/H/hPGuGlykUJCk/RBGR2sYy1HKPLs1iFvXak1JXCTobfKADba9LaqbqNKdo8CptlLGFncZhHQX+a6En6pUUe3XeXaQVthxm2a21XuoEY8Fvqt+I7Atirh4MxvjuBWqCAjwb6xhif4/TdzXYZWvtlqecxyLrg9wzJf1m2oWSL5rjeHMdv4XH9dfBcZv4dg1N4XP+PFBrTA87/3oMc1786Ov64viVqXL8jzrh+b8z7DtZxfR0xZnBY2YL8IvqukPntIAtNH1dnDI8ch9dcx+NsdmsjdferUffrTt7LbxECugIeADyIDrZpnDnuDpc21FbULyuSt8lF3DP0zM/j4elwP0Pu26jedk6RvKX1jeZ4m/mvNM617yL37TFvPUwDbQfR7uKxN8ua90+k3IJlHHaFQb/WQq+oKwqHrd8IYh7zG0GpsCMn8EMhHR5uw3dD7O7AI71wc3q5jK3fFZto3LsgvaPu95GuEd8Vy9ysR5oB3bsxXosyKrw+fhnZf4dNyfQTqVxOd5L7T+KnogN/Xy3yfdwphkyucUdvObnPiFPRb3Pw3bvgeElPMvrYpcT/V/EQ/N6ABJcjh3uFXTkyvSe5q+GuJ/dN7NbEZIqnU9w3QocTzS/UGf9TJLsKp887ilnwX2je68Sv9nbrm4PfIt7PCzfdeFvGfZSKr4v1GxX1Jchu+ZJviOPdQrJVKD8H4vG2Gn932U+j/p27D+cn5DsinhkBDLicnbDaTwOvLPWOmWmT1E6yXPYm9JtSLjFfxLyNxjyF4Pms5PE1PRZ0TsSLJvHfRlO6bNik6yIXQ5sOBOQgMM2Prt09Kr4uIZbbq3RJaHom6OwUo09b3pOId2fpBt1ttLOFUXVpblRdst6zPNNs3v/qwe/TjJL3LMfb1Bt6KSNuvWGZ3kab9BNy32LXvjF/vrE3/Qa5b4ysL1w/fkW0aVwvlOyA6HvHRA8B/4zo07meKP4+Frs0L+mq+vAm8VynvrGIX+S7IH8geqLx5uJ74/W6l2H5js9X0/R7sk5A149wr5nL1Gwfz1umSHdUmc59UI/gZ1ymX+cyLZ5gU6Z1FQttypRlehvlsI7cX7ArU+a/1ijTz5D70bh91qeI9giXqZIdYlumW4i+hctU8Q9utUw/Szzror6ZU1VRZhlXP0c8HY03vs5ymjOFwyK3uIzFRIjj/wHxTYNFXC7Ggtc6J65J0WWsb3j/doLVfiLjUe9tPZeKfJFrqIDsjujLADekRNrTqPPYU2GUPc2NY0/FUfZUHmVPPI5iPzPt1j7Xt0WP+AW+O/ocoAr61ky02Fk9X+Oze3uA1yI=
*/