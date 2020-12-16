// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_SLICED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_SLICED_HPP


#include <boost/range/adaptor/sliced.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Geometry>
struct tag<boost::adaptors::sliced_range<Geometry> >
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_SLICED_HPP


/* sliced.hpp
eBAeUvkE3AbPqL0f4B74C9wLo0mLfbAAdBPfBJWLw/dhFdVPhJHwYXgY/V7wY/gi/ByugF/BLfA0fB+ehf+C38MT8Dy8AC/Dm/AKTKCB+w2WgEY4pVWuqHJVGAlbwRvoPwr/hD3hTTgC3oIvwb/gEnW3TOVVKq9VfzbBr9H/HJ6BX6v5tyr/qPJFtX8F3kH/GrQh/wXtsITLZ68CjISVYRisDsNhc0j+W+uq+2b6ymF3aV+D11Uf0HlECRgLS8HqsIyODyvBxrAabA6rw2RYGXZR/a6qf037k4bP+cL7VsPzwsEaXk2vL5yGsARspOW9KXwCNoepsCWcCVvDV2BbuAMmwz2wC/wQdoKfqWzOo3vN8oU/wJFzHr0xwlfvtsHqcCesC3fBxvA92Azuhq3gPtgX7odj4UE4CR6C8+ERuAwehZvgJ3Av/AyegP+Cp+Hn8Bw8AY3IfQE98EsYrXKsyvHwKyjjQNgRnoHT4LdwBvwOzoIn4POq/4Lqz1f9VfAcfAP+BP+GP8MiDso5LA2vwvLwJKwFT8E68BJsCK/A7vDfUNIXJd/hh30lf4PXR2s6aV9gLZ1/1oatYB3YEdaFnWF9+DisB3uKrOMLI07q/5Ywn/+PGOMLbTdneXzz8ZdhNbgYNobLYVf4GhwLV8FJcDWcDtfAVXAt3ADXwXfgengQZsHv4TZ4A26Hd+B70MiX3bAU/AAmwv2wATwEm8LjcAT8Es6BX8Ol8AzcAc/C9+H38CA8Bxs5yBf4KPwZ9oAXYD94Ec6GNSjXa+AlI97wCnwX/gp3wt/gXvhveBReg2fhHzDcaK9gIvwbNoEuL88JI+B5GAUvwlwwmnYjN8wHo2EdGAPrwVjYHeaHvWABOAUWhIthYbgSFoHrYHGYBUvBk7AM/AWWhX/BcrAi+VsBNoSVYDO4h3i2hXthe7gBDoeVMZ8Bq8C5sCpcAKvB5bA6XANfxf5bcAU02yP5DjgcEaI9GoO9GDgeFoATYGE4EdaHk+AjcDJsAZ+F7WAGfBJOgX3hNNgfzoCD1Z65H5Sl4T8v4QfvB1UI99WXirASrATbwAdhZ1gZPgprw+6wGhwMq8MJsAacCmvBZ8Werq/a9fvasqYi4cp5BMqw/H0c5msHT8Dy8CuYCE/BpvA0bAXPwv7wd/g8vAFfhDfhUngLroR/wf3wb/gRvA0/hmWJz9fwP8jfwjvQiJQT/aLQBYvDKFgLeuDDMBdsCKNhe5gXDocxcDyMhRNhWfgcLABXwXi4ExaEH8BC8DAsBs/B4vASLAmvwjLwuvij+RVmfpNavnUt6bbByC/0jb+HsVcb1oONYCPYDDaGLWET2BY+AjvAdvBxmAx7wg4wA3aEz8BOcBZ8FL4In4Cvwifhfthb068P/Av2gy7iNBDmhYNgPEyHReBwWA6OgFXhSFgXToCt4ETYFk7SdB0Fu8IxsC8cDQeqnAHHwWfgZE3np+FymAFlXgu3wqlwF5wO98MZ8CCcCY/ATHgZvgR/gy/Df+B8aMxjZ8MIOAfmh3NhAlwIK8BFsB1cAjvBZXAAfBVOgivgcrgSroKr4Vr4OnwHroOH4Hr4BbwOr8IbMNIYz8Fi8BYsCzfCanAzrAvfho3hFtgcboed4Q7YA+6EveEumA53w9FwL5wF34fL4H64Dh6AG+ERuAsehXvhR/AjeAwehyfgefgt/AV+D6/CH2ExF/0ELAV/geXgJVgJXoYPwfOwCfwZtoBXYVv4b9gLOiJIR+iEw2E4HAON9JkOo5BXQi/cCnPBHTA33AOj4SEYA0/BWPgNzA+/g3Hwe1gAXoTx8BIsBD3UqcLwQVgEVocPwDawBOwCS8HBsDR8DpaBL8GKcCs=
*/