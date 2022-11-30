// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2021.
// Modifications copyright (c) 2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_SEGMENT_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_SEGMENT_CONCEPT_HPP


#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/geometries/concepts/concept_type.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>


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


template <typename Geometry>
struct concept_type<Geometry, segment_tag>
{
    using type = Segment<Geometry>;
};

template <typename Geometry>
struct concept_type<Geometry const, segment_tag>
{
    using type = ConstSegment<Geometry>;
};


}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_SEGMENT_CONCEPT_HPP

/* segment_concept.hpp
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
*/