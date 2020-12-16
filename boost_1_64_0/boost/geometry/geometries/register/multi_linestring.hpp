// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_REGISTER_MULTI_LINESTRING_HPP
#define BOOST_GEOMETRY_GEOMETRIES_REGISTER_MULTI_LINESTRING_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

/*!
\brief \brief_macro{multi_linestring}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_MULTI_LINESTRING, multi_linestring} The
    multi_linestring may contain template parameters, which must be specified then.
\param MultiLineString \param_macro_type{multi_linestring}

\qbk{
[heading Example]
[register_multi_linestring]
[register_multi_linestring_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_MULTI_LINESTRING(MultiLineString) \
namespace boost { namespace geometry { namespace traits {  \
    template<> struct tag<MultiLineString> { typedef multi_linestring_tag type; }; \
}}}


/*!
\brief \brief_macro{templated multi_linestring}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_MULTI_LINESTRING_TEMPLATED, templated multi_linestring}
    \details_macro_templated{multi_linestring, linestring}
\param MultiLineString \param_macro_type{multi_linestring (without template parameters)}

\qbk{
[heading Example]
[register_multi_linestring_templated]
[register_multi_linestring_templated_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_MULTI_LINESTRING_TEMPLATED(MultiLineString) \
namespace boost { namespace geometry { namespace traits {  \
    template<typename LineString> struct tag< MultiLineString<LineString> > { typedef multi_linestring_tag type; }; \
}}}


#endif // BOOST_GEOMETRY_GEOMETRIES_REGISTER_MULTI_LINESTRING_HPP

/* multi_linestring.hpp
kMSNfbRzZHRjwldF3PamBsWLvQ5ij8hPmDaJ6bcZk5yVdOrkGU/5TtXybc+BWmr71ymBtKScb4frURlJrG2iXkqRMYSoDajHUV1xswf9LHVr8zM1s+vF0j+5a3uiVXrX9odHA+vIbiuwjhywAutIiVW+jhy2yteRLvBW8SegPJj1DcoCZloWVD/TvEMw5cDUy6TAb+bMPI+kl79vGaw1gfvhdLud/jxEPctjSSGP95Nc9RTivbK67Vl6D5jI97sD6pve1z1ZzB53a31Tt7mmvnQ+ZsuNtW2ntRU51lfmpX4RIK7eIbq2n5I2Y8SPreYO8LHiJkHLv/OMAnaThpm56F1iJ6ZsW2/K318+1zrgtP0idwp6p28avFL8c6us/jPmKK0jhFvrSInerZQXrnUnN4dBaW4B3YNpV2bK8+5xp2pdj3Q5lgL3Dl4h9n7gTo4pqsft2KJ3sXsKNzrYexWTtUAP/0LOX5C0nFEdDeNnYLuT4YRLglx6D/GV4u8ad6IJExaccqdtx2y1M9G1SZ6dqs9+A33JE9GTCqfhbOSWfe/2maS9+OaAshXrLkqVW6Si4vjHGxNqX3MniU9flZ14h4Xc55wl9oep7NhPl3mn3/hL1Du0Jb87d7yq3kfIKNqO0nH48T9pO0r82g7KREDbkekObDuykJ22Q+7cR6bMI5eWeZnfugPbD2lnpM6rXb87+8ln9Ew+y/zpVYk39hMC++CSy3yBn4r/yXAMHFkd/S9DtA1z8tl5G3yvzQ/ippe7O//+DaV5pn7VDDaOU7NG4sdA5F9Ebu9uSygXl58TmDv+z4i9Du4syvYSlPbV6l/9oHV8sDGvI/6MRP5J5ESrPWXoJhT25H74c1/Ldzfa7+qYzCn3ekdgva9kn7I7LsS6SZj48XNZP0OuIXYU/8JdidoedBP5uHUJ/Xqofvl+sbPUwtzp26VfT9U27YTEr5u7Mysct6K6UeYr+/Wt1VJM3yrcDulvpZ/do0r7UCn/WRWag4QlENeAcj+xzLhyWplxZV6QcWVhkDnJRNP/OfkRWJ5H9dM9uLoeEAulPB8PUZ7z5+SFWgP4Vtycce1xmTUA9adasLKsZg3NeP+syKe5a8gqW47NPOcHsfOrax9x0DKs/tQMNSdR898Z7T4lbfgoc0+1mTNK+/W75OkF86tvkPU0kfuUyZ/sIPkzKiB/Atf4q+sB9jfqPr4bdG25yz/L50OQ5eWg+TFa3E53TTRti+NfVbN/8R8p/vu+K1JWiXuo7zCyfRbn2fcsKe04nLhAHOR7jOBjJnXX3JSPi7615cs8Q0rXjvnLMXU7+TvbfITbWaPt/62uV5vxCHsAC66mipXeMdlM7Awn3g1Vz3E3ltatv5Spzr45CPsGXabtril2CqxmuBtgpau+49ZyJ7tirHZW9YD1wXR9Zm8J5zsuN6Z10R3pmmfu56z2vcyVqDEx5l3IY6IXyzP8wzfa4ssHeUa62HP0a3qqusLRj7HGumMD1sUT9d3JXPHvNM93q57jtp1V02VJ25hnB0beuZe2t+ttd0iJIrMLUuRmzJiqB94prGk0QMwfM/Ma6wfpu2RW47QBp8ROtKnfMZI23ayJxMqp389I2Noi+6dxsropE3ZxQ+y+DfF+SdcG6ol5T09pP6Fnqmlf1EjMu3p6S1+pfZq+/3PS45DYyVDZeaZX9hFmUJ+XDMJukv2txqLrS/eFhN6jkeukhY7VrhG5MymWJOMv9VfOOY+3/a206LGy7wbaI8ch79d6XQQPoP6C6kCedqUP28bvO7D/CnxV9i5W7H2Z3U8N/jb0+odp91DaxslYqqPkOz199cC1aC6kkL9T9n188Bso33/8GKq9CFw=
*/