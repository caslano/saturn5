// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_BOX_HPP
#define BOOST_GEOMETRY_GEOMETRIES_BOX_HPP

#include <cstddef>
#include <type_traits>

#include <boost/concept/assert.hpp>

#include <boost/geometry/algorithms/convert.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/make.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

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

    // TODO: constexpr requires LiteralType and until C++20
    // it has to have trivial destructor which makes access
    // debugging impossible with constexpr.

#if !defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
    /// \constructor_default_no_init
    constexpr box() = default;
#else // defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
    box()
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
    template
    <
        typename P = Point,
        std::enable_if_t
            <
                ! std::is_copy_constructible<P>::value,
                int
            > = 0
    >
    box(Point const& min_corner, Point const& max_corner)
    {
        geometry::convert(min_corner, m_min_corner);
        geometry::convert(max_corner, m_max_corner);

#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        m_created = 1;
#endif
    }

    /*!
        \brief Constructor taking the minimum corner point and the maximum corner point
    */
    template
    <
        typename P = Point,
        std::enable_if_t
            <
                std::is_copy_constructible<P>::value,
                int
            > = 0
    >
#if ! defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
    constexpr
#endif
    box(Point const& min_corner, Point const& max_corner)
        : m_min_corner(min_corner)
        , m_max_corner(max_corner)
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        m_created = 1;
#endif
    }

#if ! defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
    constexpr
#endif
    Point const& min_corner() const
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        BOOST_GEOMETRY_ASSERT(m_created == 1);
#endif
        return m_min_corner;
    }

#if ! defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
    constexpr
#endif
    Point const& max_corner() const
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        BOOST_GEOMETRY_ASSERT(m_created == 1);
#endif
        return m_max_corner;
    }

    Point& min_corner()
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        BOOST_GEOMETRY_ASSERT(m_created == 1);
#endif
        return m_min_corner;
    }

    Point& max_corner()
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

    static constexpr coordinate_type get(model::box<Point> const& b)
    {
        return geometry::get<Dimension>(b.min_corner());
    }

    static void set(model::box<Point>& b, coordinate_type const& value)
    {
        geometry::set<Dimension>(b.min_corner(), value);
    }
};

template <typename Point, std::size_t Dimension>
struct indexed_access<model::box<Point>, max_corner, Dimension>
{
    typedef typename geometry::coordinate_type<Point>::type coordinate_type;

    static constexpr coordinate_type get(model::box<Point> const& b)
    {
        return geometry::get<Dimension>(b.max_corner());
    }

    static void set(model::box<Point>& b, coordinate_type const& value)
    {
        geometry::set<Dimension>(b.max_corner(), value);
    }
};

template <typename Point>
struct make<model::box<Point> >
{
    typedef model::box<Point> box_type;

    static const bool is_specialized = true;

    static constexpr box_type apply(Point const& min_corner, Point const& max_corner)
    {
        return box_type(min_corner, max_corner);
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_BOX_HPP

/* box.hpp
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
*/