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
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
*/