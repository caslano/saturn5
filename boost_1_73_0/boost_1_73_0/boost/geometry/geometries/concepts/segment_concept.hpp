// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_SEGMENT_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_SEGMENT_CONCEPT_HPP

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/point_type.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
\brief Segment concept.
\ingroup concepts
\details Formal definition:
The segment concept is defined as following:
- there must be a specialization of traits::tag defining segment_tag as type
- there must be a specialization of traits::point_type to define the
  underlying point type (even if it does not consist of points, it should define
  this type, to indicate the points it can work with)
- there must be a specialization of traits::indexed_access, per index
  and per dimension, with two functions:
  - get to get a coordinate value
  - set to set a coordinate value (this one is not checked for ConstSegment)

\note The segment concept is similar to the box concept, defining another tag.
However, the box concept assumes the index as min_corner, max_corner, while
for the segment concept there is no assumption.
*/
template <typename Geometry>
class Segment
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename point_type<Geometry>::type point_type;

    BOOST_CONCEPT_ASSERT( (concepts::Point<point_type>) );


    template <size_t Index, size_t Dimension, size_t DimensionCount>
    struct dimension_checker
    {
        static void apply()
        {
            Geometry* s = 0;
            geometry::set<Index, Dimension>(*s, geometry::get<Index, Dimension>(*s));
            dimension_checker<Index, Dimension + 1, DimensionCount>::apply();
        }
    };

    template <size_t Index, size_t DimensionCount>
    struct dimension_checker<Index, DimensionCount, DimensionCount>
    {
        static void apply() {}
    };

public :

    BOOST_CONCEPT_USAGE(Segment)
    {
        static const size_t n = dimension<point_type>::type::value;
        dimension_checker<0, 0, n>::apply();
        dimension_checker<1, 0, n>::apply();
    }
#endif
};


/*!
\brief Segment concept (const version).
\ingroup const_concepts
\details The ConstSegment concept verifies the same as the Segment concept,
but does not verify write access.
*/
template <typename Geometry>
class ConstSegment
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename point_type<Geometry>::type point_type;
    typedef typename coordinate_type<Geometry>::type coordinate_type;

    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<point_type>) );


    template <size_t Index, size_t Dimension, size_t DimensionCount>
    struct dimension_checker
    {
        static void apply()
        {
            const Geometry* s = 0;
            coordinate_type coord(geometry::get<Index, Dimension>(*s));
            boost::ignore_unused(coord);
            dimension_checker<Index, Dimension + 1, DimensionCount>::apply();
        }
    };

    template <size_t Index, size_t DimensionCount>
    struct dimension_checker<Index, DimensionCount, DimensionCount>
    {
        static void apply() {}
    };

public :

    BOOST_CONCEPT_USAGE(ConstSegment)
    {
        static const size_t n = dimension<point_type>::type::value;
        dimension_checker<0, 0, n>::apply();
        dimension_checker<1, 0, n>::apply();
    }
#endif
};


}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_SEGMENT_CONCEPT_HPP

/* segment_concept.hpp
qEr9kd1G9wl1afy6CXee1i76I7bBsSJJJrM0TkfO/jeyl3hL8NY3Px2vzLa8gk5mMvrrMAj6Wjn5GVVPevm/q4h/Hj5el1T1bs/5M0ths9I1hr8YeEEnoo9ZyAVUKBe29H30/yNXEjtZWmnEQvq7irqTZ1/QivzQh03+Gq2sylS1ZxrMRCEysJpLU6De01hx11I5t9xR9Uk6hXx+WcmpTgbdaSysIo2MS8+IP5BZkG6jS4kWnNhbyF5u2l6WKPub0WXoY15xdOF6lvk9aZWpVtrV6fiWmA+kENpYB9qI4ZturNOty7rrGMf5+B/ZMf8LUEsDBAoAAAAIAC1nSlK2iKyDVWkAAHabAQAXAAkAY3VybC1tYXN0ZXIvbGliL211bHRpLmNVVAUAAbZIJGDtvftb21iWKPo7f4WS+SqxU4aE6nl1qKQPCU4VXxHIAKl0nepcf8IWoMZIHksOYabyv9/13HvtLck2pHq6z72H6amAtLWfa6/34+mT3+9nI3mSrPwZ0f+P4Af+pS/ezcu/ZuO6vfVo9FvC/wdf/QX+XTXI08R/8tuon6z+5LekR5+MZJTv8ffRaNVAf8G54X+e4pd/GeGv8AQ+wy9fl7PbeX5xWSe91/1k+49//PdkM/nu2Xfbg2QvLfJsmpzU
*/