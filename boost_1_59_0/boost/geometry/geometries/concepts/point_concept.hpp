// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_POINT_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_POINT_CONCEPT_HPP

#include <cstddef>

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>

#include <boost/geometry/geometries/concepts/concept_type.hpp>


namespace boost { namespace geometry { namespace concepts
{

/*!
\brief Point concept.
\ingroup concepts

\par Formal definition:
The point concept is defined as following:
- there must be a specialization of traits::tag defining point_tag as type
- there must be a specialization of traits::coordinate_type defining the type
  of its coordinates
- there must be a specialization of traits::coordinate_system defining its
  coordinate system (cartesian, spherical, etc)
- there must be a specialization of traits::dimension defining its number
  of dimensions (2, 3, ...) (derive it conveniently
  from std::integral_constant&lt;std::size_t, X&gt; for X-D)
- there must be a specialization of traits::access, per dimension,
  with two functions:
  - \b get to get a coordinate value
  - \b set to set a coordinate value (this one is not checked for ConstPoint)
- for non-Cartesian coordinate systems, the coordinate system's units
  must either be boost::geometry::degree or boost::geometry::radian


\par Example:

A legacy point, defining the necessary specializations to fulfil to the concept.

Suppose that the following point is defined:
\dontinclude doxygen_5.cpp
\skip legacy_point1
\until };

It can then be adapted to the concept as following:
\dontinclude doxygen_5.cpp
\skip adapt legacy_point1
\until }}

Note that it is done like above to show the system. Users will normally use the registration macro.

\par Example:

A read-only legacy point, using a macro to fulfil to the ConstPoint concept.
It cannot be modified by the library but can be used in all algorithms where
points are not modified.

The point looks like the following:

\dontinclude doxygen_5.cpp
\skip legacy_point2
\until };

It uses the macro as following:
\dontinclude doxygen_5.cpp
\skip adapt legacy_point2
\until end adaptation

*/

template <typename Geometry>
class Point
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    typedef typename coordinate_type<Geometry>::type ctype;
    typedef typename coordinate_system<Geometry>::type csystem;

    // The following enum is used to fully instantiate the coordinate
    // system class; this is needed in order to check the units passed
    // to it for non-Cartesian coordinate systems.
    enum { cs_check = sizeof(csystem) };

    enum { ccount = dimension<Geometry>::value };

    template <typename P, std::size_t Dimension, std::size_t DimensionCount>
    struct dimension_checker
    {
        static void apply()
        {
            P* p = 0;
            geometry::set<Dimension>(*p, geometry::get<Dimension>(*p));
            dimension_checker<P, Dimension+1, DimensionCount>::apply();
        }
    };


    template <typename P, std::size_t DimensionCount>
    struct dimension_checker<P, DimensionCount, DimensionCount>
    {
        static void apply() {}
    };

public:

    /// BCCL macro to apply the Point concept
    BOOST_CONCEPT_USAGE(Point)
    {
        dimension_checker<Geometry, 0, ccount>::apply();
    }
#endif
};


/*!
\brief point concept (const version).

\ingroup const_concepts

\details The ConstPoint concept apply the same as the Point concept,
but does not apply write access.

*/
template <typename Geometry>
class ConstPoint
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    typedef typename coordinate_type<Geometry>::type ctype;
    typedef typename coordinate_system<Geometry>::type csystem;

    // The following enum is used to fully instantiate the coordinate
    // system class; this is needed in order to check the units passed
    // to it for non-Cartesian coordinate systems.
    enum { cs_check = sizeof(csystem) };

    enum { ccount = dimension<Geometry>::value };

    template <typename P, std::size_t Dimension, std::size_t DimensionCount>
    struct dimension_checker
    {
        static void apply()
        {
            const P* p = 0;
            ctype coord(geometry::get<Dimension>(*p));
            boost::ignore_unused(p, coord);
            dimension_checker<P, Dimension+1, DimensionCount>::apply();
        }
    };


    template <typename P, std::size_t DimensionCount>
    struct dimension_checker<P, DimensionCount, DimensionCount>
    {
        static void apply() {}
    };

public:

    /// BCCL macro to apply the ConstPoint concept
    BOOST_CONCEPT_USAGE(ConstPoint)
    {
        dimension_checker<Geometry, 0, ccount>::apply();
    }
#endif
};


template <typename Geometry>
struct concept_type<Geometry, point_tag>
{
    using type = Point<Geometry>;
};

template <typename Geometry>
struct concept_type<Geometry const, point_tag>
{
    using type = ConstPoint<Geometry>;
};


}}} // namespace boost::geometry::concepts

#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_POINT_CONCEPT_HPP

/* point_concept.hpp
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
*/