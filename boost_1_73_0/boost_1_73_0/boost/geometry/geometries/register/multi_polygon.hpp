// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_REGISTER_MULTI_POLYGON_HPP
#define BOOST_GEOMETRY_GEOMETRIES_REGISTER_MULTI_POLYGON_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

/*!
\brief \brief_macro{multi_polygon}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_MULTI_POLYGON, multi_polygon} The
    multi_polygon may contain template parameters, which must be specified then.
\param MultiPolygon \param_macro_type{multi_polygon}

\qbk{
[heading Example]
[register_multi_polygon]
[register_multi_polygon_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_MULTI_POLYGON(MultiPolygon) \
namespace boost { namespace geometry { namespace traits {  \
    template<> struct tag<MultiPolygon> { typedef multi_polygon_tag type; }; \
}}}


/*!
\brief \brief_macro{templated multi_polygon}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_MULTI_POLYGON_TEMPLATED, templated multi_polygon}
    \details_macro_templated{multi_polygon, polygon}
\param MultiPolygon \param_macro_type{multi_polygon (without template parameters)}

\qbk{
[heading Example]
[register_multi_polygon_templated]
[register_multi_polygon_templated_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_MULTI_POLYGON_TEMPLATED(MultiPolygon) \
namespace boost { namespace geometry { namespace traits {  \
    template<typename Polygon> struct tag< MultiPolygon<Polygon> > { typedef multi_polygon_tag type; }; \
}}}


#endif // BOOST_GEOMETRY_GEOMETRIES_REGISTER_MULTI_POLYGON_HPP

/* multi_polygon.hpp
SOaLAuVJmgIsmskK7yFDgH2ixPuLF8UMHVRByZOq3ufBbV8pLP4OOzytsjVaDpLR6GD/cDga9Q33iOqlDyTG0IayRqvKRKYgDRndZZCnYLWXCaBJ2PDxZcIS1gaxQZbSV5ejrKjnt3SY9gV9rtxTRTwJPcIh9SlwIXTqrDzDAXgbFwXKwqTKrJOU9nmHzuOGeabrM0QH8iY5Hu7uPf1wvH86DHq6SfO6Wibd4NqawwFjJNNlvUHnhOlTvhiiNmHGK6tr0oie3XJfCXDjl8nYCUKjtMLhev2WwedZOtHhaZBr4AjN8Dcp85HYruXzm3ler/M5tSOWcAdZwjPYKNqNx7yjj1EzjOssSn6nN9FvLvyGKgtgPhEDQFMYCPdajgS1FwKhJz+O8ICSZNs+4uP6jjjSaVleJQvgVpMLuICFG6JwoAh/IewArrrKZ/DiE1zVibypDDvaCphP4LcLIMD4R68BofB2HZlbflg5SuOOQDZlhhQxXfLgRaCDebVr8VtZTG95mbjLIDLPSEpw0/cU0s9sNMvHVz1cdI8F4v6jCjYg/68MiEMwj77gXtcHMhSMYmTDT4+99mb7D263oC9YRT3H4QTFX2W3A30Bv4+mWXFRX7pH1bSsqxFcDF65bwgnApStxw/6T1qEgSd9
*/