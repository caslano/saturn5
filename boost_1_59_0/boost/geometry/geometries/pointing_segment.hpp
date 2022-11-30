// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_GEOMETRIES_POINTING_SEGMENT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_POINTING_SEGMENT_HPP

#include <cstddef>
#include <type_traits>

#include <boost/concept/assert.hpp>
#include <boost/core/addressof.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>

namespace boost { namespace geometry
{

namespace model
{

// const or non-const segment type that is meant to be
// * default constructible
// * copy constructible
// * assignable
// referring_segment does not fit these requirements, hence the
// pointing_segment class
//
// this class is used by the segment_iterator as its value type
template <typename ConstOrNonConstPoint>
class pointing_segment
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
    point_type* first;
    point_type* second;

    inline pointing_segment()
        : first(NULL)
        , second(NULL)
    {}

    inline pointing_segment(point_type const& p1, point_type const& p2)
        : first(boost::addressof(p1))
        , second(boost::addressof(p2))
    {}
};


} // namespace model


// Traits specializations for segment above
#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename Point>
struct tag<model::pointing_segment<Point> >
{
    typedef segment_tag type;
};

template <typename Point>
struct point_type<model::pointing_segment<Point> >
{
    typedef Point type;
};

template <typename Point, std::size_t Dimension>
struct indexed_access<model::pointing_segment<Point>, 0, Dimension>
{
    typedef model::pointing_segment<Point> segment_type;
    typedef typename geometry::coordinate_type
        <
            segment_type
        >::type coordinate_type;

    static inline coordinate_type get(segment_type const& s)
    {
        BOOST_GEOMETRY_ASSERT( s.first != NULL );
        return geometry::get<Dimension>(*s.first);
    }

    static inline void set(segment_type& s, coordinate_type const& value)
    {
        BOOST_GEOMETRY_ASSERT( s.first != NULL );
        geometry::set<Dimension>(*s.first, value);
    }
};


template <typename Point, std::size_t Dimension>
struct indexed_access<model::pointing_segment<Point>, 1, Dimension>
{
    typedef model::pointing_segment<Point> segment_type;
    typedef typename geometry::coordinate_type
        <
            segment_type
        >::type coordinate_type;

    static inline coordinate_type get(segment_type const& s)
    {
        BOOST_GEOMETRY_ASSERT( s.second != NULL );
        return geometry::get<Dimension>(*s.second);
    }

    static inline void set(segment_type& s, coordinate_type const& value)
    {
        BOOST_GEOMETRY_ASSERT( s.second != NULL );
        geometry::set<Dimension>(*s.second, value);
    }
};



} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_POINTING_SEGMENT_HPP

/* pointing_segment.hpp
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
*/