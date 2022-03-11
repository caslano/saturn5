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
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
*/