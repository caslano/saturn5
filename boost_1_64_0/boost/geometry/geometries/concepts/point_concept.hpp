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
OeQtql7o80x6u7i5NejzbonZFsTNDYHnmfS+db24eUD6Jxnra53t1MZ6t7Dc7xkgm7o1QkXn7hrtp8b6vFOoCfDdP/UEXdqN35zG1nZ1zwLtYXe42XwWGBawv2jsGUD9dLKfrb8QPSkk0JyOC3rdD/O518/XvYN031CxL9A8tNz3VnvD8c1wU48L2vY2iv1s1W33QdvcRdnY0y6DtbmsRtpcR69fnk6bO06mzbklLu/4tbk4MXvOr80lq5lvm+spZi9JG1jThrDa+bSBtwO1AVfQNvBC9onbwJPi5o5G28DL4ubmRtvAg+LmYannPv0p/WeDPlXq/LLAdX6CfW/2qfNr6tX59X7ze3oftr/Bl3qm+3DVvw/7Pyvv1AmdDbo+/2fQ3HNh44h67aPEs8Rj303tIXOgdqJ+29nPvI+J/hPjN47A494Jtp8EHS+Sl6KvMg46nA3Hs9p+vhE3g4yrHM3sNrNfzLo3rMfaZt8T+1xji7w/xcz2k1j/m3F7fu/XI+UdT6Dxtz2Xd7e4uUj2PtpOfR2b6h2XOStdXVzjzHcnzkTzHQ/hNTrfaY/vtPP7DWavIia/0LEeOt+pn9weKQGfm+yxmn9fWaXf/p+tgcxFHiSO20f51AV2XzuZdxxeP30kT4mj334bTui1Pztguy02bPug70hKgrshIG9/li7tYnTMFNzyt7qnpCmjXUTqSAdvv+LMok9pFxG0j4iBR8SvS8rn++6lFKtz71zS3h8j1u89ClG234MHfueSHvidi/3MO08/+M3UiPRDtpjvI0Y3WnZ5JYHbsPrLDFp+ah+0/NQ+aJ7m17kJUMYBy0/dG0HLO8N2j1s/94H77Gm4Gyhuep30/PAPLVPtqzUPtEyDlHXGCco6t7M3Yos1guXIBsq6xresZSHEiffKoazV32L/d89636/VPNR+Wt2WN3ofvFTcnPO989TUo+13ceV+z31VXbweP9U98Y/q3mjRp3vTfMLN0QKnXf3H23HvJPqWBu/yp5p1UOw2OeT9OGWQ0UXHJU5nzTq6kAges9wt3I32I5skjHTpR6w9dz+WZ6wfd2ZAaDevw9/qdyJPwlHUiewxmj9+mycF3gesStxea2jeqN/MwHsm2fan2PfWMtELmSGKUDPe8YlZHnMaY4xA+2Hl2OF0Fv0MdI/o9xjazrWO1fmRe+hYmdfRdR7WdWZxnRFGoH2UXhH7DCNwvPS+r2MSa93ORnGTRu2IUDNyR8w6UgfjffYCqmIeSqKn8aGcxd0SxrgRMsfAMj31e6ERsO3oWKlA3NxvWHXjm4STO2vF3IdGwqcK5y9gYyJr/2L/Pkv3L/bvs8rr7dmVKP6sPS81bTpP03ysvT5C9Htt3b+PWt1T37s6aSfKX1If14zzr49107BFja4HfEb83e08bMRp27XCGoBOOTTcZ03t+9ljyqdE3+asNaKCzaVKef5G3D1tDGEPTWsvp+snmGah/nsPaT1pOV7qXoiT3UdOCYm058FjxTzPOcAxM+ShkCH2Oq+9E2W8qe9VrLAXGjxZSl38vVSqpSUVHrmvydg/WB19V+L6gOF23GjovEnAvY9awa/kOs2N5dy17nJ0wx3men3rveMcea7znd8bKX5DkUskPbGmmazFcmO2Vcya2++Xo5HdYhYmcc9BD7J3mdiPgmZ/Gkn/NacHc50xhBtac7Nrgqsr4+WalWH+Y+K/JMi+ZcKvkC+QLxHfPeu2n2AuYaM+V5lt5u2Jfns3idmhcV4zHnTKHNqOauu1o2Om27o2I2ZrIGWHmZQdZtZ+x/5zozmQfPabR03GfFQj+6W5x/vPj86f4N8Ou0+07Zv2X/oH7L/0y0TT/PDgs42PH7w=
*/