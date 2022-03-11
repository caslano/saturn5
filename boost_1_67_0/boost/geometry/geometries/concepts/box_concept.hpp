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

}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_BOX_CONCEPT_HPP

/* box_concept.hpp
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
*/