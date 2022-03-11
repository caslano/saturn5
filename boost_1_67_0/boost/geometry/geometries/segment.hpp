// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_SEGMENT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_SEGMENT_HPP

#include <cstddef>

#include <boost/concept/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

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

#ifndef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
    /// \constructor_default_no_init
    segment() = default;
#else
    /// \constructor_default_no_init
    inline segment()
    {}
#endif

    /*!
        \brief Constructor taking the first and the second point
    */
    inline segment(Point const& p1, Point const& p2)
    {
        this->first = p1;
        this->second = p2;
    }
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
        typename boost::mpl::if_
            <
                boost::is_const<ConstOrNonConstPoint>,
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

    static inline coordinate_type get(segment_type const& s)
    {
        return geometry::get<Dimension>(s.first);
    }

    static inline void set(segment_type& s, coordinate_type const& value)
    {
        geometry::set<Dimension>(s.first, value);
    }
};


template <typename Point, std::size_t Dimension>
struct indexed_access<model::segment<Point>, 1, Dimension>
{
    typedef model::segment<Point> segment_type;
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