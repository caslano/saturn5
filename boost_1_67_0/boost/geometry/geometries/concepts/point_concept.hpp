// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

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
  from boost::mpl::int_&lt;X&gt; for X-D)
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

}}} // namespace boost::geometry::concepts

#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_POINT_CONCEPT_HPP

/* point_concept.hpp
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
*/