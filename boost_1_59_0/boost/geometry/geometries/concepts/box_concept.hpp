// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_BOX_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_BOX_CONCEPT_HPP

#include <cstddef>

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/geometries/concepts/concept_type.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
\brief Box concept
\ingroup concepts
\par Formal definition:
The box concept is defined as following:
- there must be a specialization of traits::tag defining box_tag as type
- there must be a specialization of traits::point_type to define the
  underlying point type (even if it does not consist of points, it should define
  this type, to indicate the points it can work with)
- there must be a specialization of traits::indexed_access, per index
  (min_corner, max_corner) and per dimension, with two functions:
  - get to get a coordinate value
  - set to set a coordinate value (this one is not checked for ConstBox)
*/
template <typename Geometry>
class Box
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename point_type<Geometry>::type point_type;


    template
    <
        std::size_t Index,
        std::size_t Dimension,
        std::size_t DimensionCount
    >
    struct dimension_checker
    {
        static void apply()
        {
            Geometry* b = 0;
            geometry::set<Index, Dimension>(*b, geometry::get<Index, Dimension>(*b));
            dimension_checker<Index, Dimension + 1, DimensionCount>::apply();
        }
    };

    template <std::size_t Index, std::size_t DimensionCount>
    struct dimension_checker<Index, DimensionCount, DimensionCount>
    {
        static void apply() {}
    };

public :
    BOOST_CONCEPT_USAGE(Box)
    {
        static const std::size_t n = dimension<Geometry>::type::value;
        dimension_checker<min_corner, 0, n>::apply();
        dimension_checker<max_corner, 0, n>::apply();
    }
#endif
};


/*!
\brief Box concept (const version)
\ingroup const_concepts
\details The ConstBox concept apply the same as the Box concept,
but does not apply write access.
*/
template <typename Geometry>
class ConstBox
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename point_type<Geometry>::type point_type;
    typedef typename coordinate_type<Geometry>::type coordinate_type;

    template
    <
        std::size_t Index,
        std::size_t Dimension,
        std::size_t DimensionCount
    >
    struct dimension_checker
    {
        static void apply()
        {
            const Geometry* b = 0;
            coordinate_type coord(geometry::get<Index, Dimension>(*b));
            boost::ignore_unused(coord);
            dimension_checker<Index, Dimension + 1, DimensionCount>::apply();
        }
    };

    template <std::size_t Index, std::size_t DimensionCount>
    struct dimension_checker<Index, DimensionCount, DimensionCount>
    {
        static void apply() {}
    };

public :
    BOOST_CONCEPT_USAGE(ConstBox)
    {
        static const std::size_t n = dimension<Geometry>::type::value;
        dimension_checker<min_corner, 0, n>::apply();
        dimension_checker<max_corner, 0, n>::apply();
    }
#endif
};


template <typename Geometry>
struct concept_type<Geometry, box_tag>
{
    using type = Box<Geometry>;
};

template <typename Geometry>
struct concept_type<Geometry const, box_tag>
{
    using type = ConstBox<Geometry>;
};


}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_BOX_CONCEPT_HPP

/* box_concept.hpp
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
*/