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
6n4LfAM+Bd+Ez6m5rl/TvfsZI3qsX1vfOlAud8HBcCM8D94Lc+F92t9ugsvhg9r/PARvgw/Du+Ej2v4ehf2s8TM8EW6Fk+BTMBs+DgvhFrgQPgNXw21wDXwW3gufgw/C7XAn3AHfgC/BX8GXYaC8dO9zsNSjvNa2CdyXb4YZ8BYdnzXAGfBWfc9yG6yD6+FGeDvcDe+E78G74G/g3dqP3QeTuNb9sCPcpP3jAzAdPgZHwMfhifBBeDZ8CJ4LN8Pz4aOwAG6B2k7ZzzpyO71K1/teDYfDazT+a+BceB2cD6+Hy+ANGm6S2Sda9pmWcLvLeCC4LjwZToRd4ekwHV4MB8Mz4Ag4CZ4OJ+vz5FTtJ6bB+eq+AmZru10MV6r5dXAmrIdztD3m6zilEH6g7j6F8+A46/ukdT1YArPhAjgXLoR3wDJ4D6yE96o76ov4b4KLYauoQLjt4CLYF1Zoe280e9pyj9X6M0z2udB17QmBcc4NsDOsh13gWtgd3gj7q7uB6m6Umk+HN8FZ8Ba4EN4Oq+EdcDE8AK+DG+D34Ub4DPw+3A43wUPwYRjvD5inwR/AXvBp2BdugwPhD+Ew+AIcCV+Eo+GP4GnwVTgJvgbPhLvhFPgGnK56juoXqF4GfwGXwQ/h5fB9uBo2wevgB/AGuAfeDN+Csu4D3g73wrvhJ/BR+Cl8Am6Ez8P9cAe8C74Ov4JvwwPwY/gg/BQ+BPX7p+69Sd3x+P7ZUvfLSICdYKLW6w56P2oNB8G2MBO2hzlq/x3YBuaqbl1vv723pOyvqXsCBe4j8muVSL5b/uBImAIlPJgHU2ER7AhrYCd4KewMV8A0eCU8Dl4Du8KbYXfYCHvArbAXfA72hS/DfvAN2B++CQfCA3AYtJ7HT4Ez4anwQjgB1sIseAk8G26GU+EWOA2+DLPhz+A58F14HvwczoT/gLOgtcdbDpwEvwPnwAthMcyFl8I8eBWcC2+ABXAdnA8fhiXwVbgAvglL4XtwMfwULoF/hUthvPW+EraDl8IOsAx2hYtgb3gZ7A+vgBnwfDgazoZT4AVwGhwEZ8Ar4Ry4ChbCq+AiuBoGnhN0rz54ssdzwhJd318LO8Ol8Dh4CZT+E45WfV0L2geTpNPHWR4gMg4Zi54Ha5EGZCtSiNk6ZCdyEBk4nrxGfPy9G/v9SNJSyh8Zh8xB6rHfjCSehnskC8lDarFbBnci+5CYCdwvMGtEevP3WKQW2YBsQ/Zgvh/Zzd97kYNI+4nIxTxHI/34OwupQNYgG5EczOuQHfz9EXIA6Xc6fpCxyEbstiN7kXXochO5hDQgjfzdG+6BWfAQTDoDM2Qcko2UYl4BG5BNyBr0V+F+pNMkwkDfiexFEpeRfiQLGYvdHKQOqUeKMdsAG5Hdlhn6AbgFJlLYGcgMpBRZhqxDdi/DHjYhvjOJH3r6pcSPvyciM5DRl0JkGX+vQTYi25DdSDHmB+Fq2P4s8gXJQnKQTZjVwfXIVmTnePIB7kV8Z5MPyHbcDITFyBpkM7ID2Yu5bznX4O90OBrJRg6iV8CMyYyTCS8L5iF1yAZkHXaNcCeyhb+TphAXZDd/F8Na5BB/t7+M6/H3ZmQb0hv9IEycStjIRPQZsBBZjWxGdiL7kDzsfNNIKzIOqUNvuAzydz2yCWlE3wr3IDutsGGXbNwjecg+zCpgfB3xgJuRdP7eASfC/TDmHPwgA5GxyBykFLtquBJpQDYhdZhthTuRfUjMuaQPGY70RiYjG3CzHWlCDiJJl5M2zOuQdcho9C1wF5LH3/uhbzrX4u90uBJOhOthMVyDbEJeRfYiSTPINyQbyUOqkZXIemQrsg1/u2ATEn8eeYeMRbKRamQ=
*/