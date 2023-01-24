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
5e6e7vunLwsbZ5QA+LaUL3UbvNh+/AYbxPw+PYLuDTQvsWn6pefi9z5ir20Aw9SQid6vd/vVUjs7hsMdHNUGZT0f2xCeLhk+mVMWxn1Fe4dlMveWVEPI5vfyNZJ/P7CsAJg3bcnO7JccfU8lQMayHmimewNK4Balp+qek9OXrTZtR/5f5hV79b5l7z67K9NYXpXkqd3uwhhfWKzCAtX2mbNQNa8kzttzAVbwqx8BZnT8yrEe4MgCY+u8rQZy+d7QMmNj1MeFy1l7swc73k5WGqEK74RGMnHjcj+mFT72DGx06i87pqurgxSy5WTKe58VjQwXkhV7yKWIHB4Bc9L8mPVOwo2ZFa9JymsDAp8bCuaEWBjCU75unBfvlnYq8+v8uyuqWeCATPibuTkKuGOWw2Opusf3InG4RZvDWz36m0Gm7cb+D5siBuW7gdWTuw/mO85DIkJNMGH1u3WJlcznIIei2jDvPa8ki7Ml5LNdDWI8gEL8eItwNr5JjWnte3ztwRn8DJ882VEYxVK65f8klGJVsCgOSUIaFntYtbOG1e9i4bjSXVN8fS56wmwpvSYrMI6+iQ8e4BXy+UIdS0ilgb+v7E8ANKt9R90AllU879pFNzUmWBQDylJB6gUzxqHtwlcSJtFt0WvYZGoMgLfCRA5p9TIPrj7Gwkrg6IlAC+EF+J50pEygD05w1HgFwxeh+YXI5kjaDkF9aUat
*/