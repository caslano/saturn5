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

#ifndef BOOST_GEOMETRY_GEOMETRIES_SEGMENT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_SEGMENT_HPP

#include <cstddef>
#include <utility>
#include <type_traits>

#include <boost/concept/assert.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/make.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>

namespace boost { namespace geometry
{

namespace model
{

/*!
\brief Class segment: small class containing two points
\ingroup geometries
\details From Wikipedia: In geometry, a line segment is a part of a line that is bounded
 by two distinct end points, and contains every point on the line between its end points.
\note There is also a point-referring-segment, class referring_segment,
   containing point references, where points are NOT copied

\qbk{[include reference/geometries/segment.qbk]}
\qbk{before.synopsis,
[heading Model of]
[link geometry.reference.concepts.concept_segment Segment Concept]
}
*/
template<typename Point>
class segment : public std::pair<Point, Point>
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

public :

    /// \constructor_default_no_init
    constexpr segment() = default;

    /*!
        \brief Constructor taking the first and the second point
    */
    constexpr segment(Point const& p1, Point const& p2)
        : std::pair<Point, Point>(p1, p2)
    {}
};


/*!
\brief Class segment: small class containing two (templatized) point references
\ingroup geometries
\details From Wikipedia: In geometry, a line segment is a part of a line that is bounded
 by two distinct end points, and contains every point on the line between its end points.
\note The structure is like std::pair, and can often be used interchangeable.
Difference is that it refers to points, does not have points.
\note Like std::pair, points are public available.
\note type is const or non const, so geometry::segment<P> or geometry::segment<P const>
\note We cannot derive from std::pair<P&, P&> because of
reference assignments.
\tparam ConstOrNonConstPoint point type of the segment, maybe a point or a const point
*/
template<typename ConstOrNonConstPoint>
class referring_segment
{
    BOOST_CONCEPT_ASSERT( (
        typename std::conditional
            <
                std::is_const<ConstOrNonConstPoint>::value,
                concepts::Point<ConstOrNonConstPoint>,
                concepts::ConstPoint<ConstOrNonConstPoint>
            >
    ) );

    typedef ConstOrNonConstPoint point_type;

public:

    point_type& first;
    point_type& second;

    /*!
        \brief Constructor taking the first and the second point
    */
    inline referring_segment(point_type& p1, point_type& p2)
        : first(p1)
        , second(p2)
    {}
};


} // namespace model


// Traits specializations for segment above
#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename Point>
struct tag<model::segment<Point> >
{
    typedef segment_tag type;
};

template <typename Point>
struct point_type<model::segment<Point> >
{
    typedef Point type;
};

template <typename Point, std::size_t Dimension>
struct indexed_access<model::segment<Point>, 0, Dimension>
{
    typedef model::segment<Point> segment_type;
    typedef typename geometry::coordinate_type<segment_type>::type coordinate_type;

    static constexpr coordinate_type get(segment_type const& s)
    {
        return geometry::get<Dimension>(s.first);
    }

    static void set(segment_type& s, coordinate_type const& value)
    {
        geometry::set<Dimension>(s.first, value);
    }
};


template <typename Point, std::size_t Dimension>
struct indexed_access<model::segment<Point>, 1, Dimension>
{
    typedef model::segment<Point> segment_type;
    typedef typename geometry::coordinate_type<segment_type>::type coordinate_type;

    static constexpr coordinate_type get(segment_type const& s)
    {
        return geometry::get<Dimension>(s.second);
    }

    static void set(segment_type& s, coordinate_type const& value)
    {
        geometry::set<Dimension>(s.second, value);
    }
};


template <typename Point>
struct make<model::segment<Point> >
{
    typedef model::segment<Point> segment_type;

    static const bool is_specialized = true;

    static constexpr segment_type apply(Point const& p1, Point const& p2)
    {
        return segment_type(p1, p2);
    }
};



template <typename ConstOrNonConstPoint>
struct tag<model::referring_segment<ConstOrNonConstPoint> >
{
    typedef segment_tag type;
};

template <typename ConstOrNonConstPoint>
struct point_type<model::referring_segment<ConstOrNonConstPoint> >
{
    typedef ConstOrNonConstPoint type;
};

template <typename ConstOrNonConstPoint, std::size_t Dimension>
struct indexed_access<model::referring_segment<ConstOrNonConstPoint>, 0, Dimension>
{
    typedef model::referring_segment<ConstOrNonConstPoint> segment_type;
    typedef typename geometry::coordinate_type<segment_type>::type coordinate_type;

    static inline coordinate_type get(segment_type const& s)
    {
        return geometry::get<Dimension>(s.first);
    }

    static inline void set(segment_type& s, coordinate_type const& value)
    {
        geometry::set<Dimension>(s.first, value);
    }
};


template <typename ConstOrNonConstPoint, std::size_t Dimension>
struct indexed_access<model::referring_segment<ConstOrNonConstPoint>, 1, Dimension>
{
    typedef model::referring_segment<ConstOrNonConstPoint> segment_type;
    typedef typename geometry::coordinate_type<segment_type>::type coordinate_type;

    static inline coordinate_type get(segment_type const& s)
    {
        return geometry::get<Dimension>(s.second);
    }

    static inline void set(segment_type& s, coordinate_type const& value)
    {
        geometry::set<Dimension>(s.second, value);
    }
};



} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_SEGMENT_HPP

/* segment.hpp
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
*/