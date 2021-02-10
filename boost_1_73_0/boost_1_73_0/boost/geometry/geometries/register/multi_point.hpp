// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_REGISTER_MULTI_POINT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_REGISTER_MULTI_POINT_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

/*!
\brief \brief_macro{multi_point}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_MULTI_POINT, multi_point} The
    multi_point may contain template parameters, which must be specified then.
\param MultiPoint \param_macro_type{multi_point}

\qbk{
[heading Example]
[register_multi_point]
[register_multi_point_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_MULTI_POINT(MultiPoint) \
namespace boost { namespace geometry { namespace traits {  \
    template<> struct tag<MultiPoint> { typedef multi_point_tag type; }; \
}}}


/*!
\brief \brief_macro{templated multi_point}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_MULTI_POINT_TEMPLATED, templated multi_point}
    \details_macro_templated{multi_point, point}
\param MultiPoint \param_macro_type{multi_point (without template parameters)}

\qbk{
[heading Example]
[register_multi_point_templated]
[register_multi_point_templated_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_MULTI_POINT_TEMPLATED(MultiPoint) \
namespace boost { namespace geometry { namespace traits {  \
    template<typename Point> struct tag< MultiPoint<Point> > { typedef multi_point_tag type; }; \
}}}


#endif // BOOST_GEOMETRY_GEOMETRIES_REGISTER_MULTI_POINT_HPP

/* multi_point.hpp
kOCWTYFsFKVCPx+U6a+cTviXFwI7PBXcmwCjtEE68Czw9FfqbXRyuns6HB3ApfwIff03Tejw/cHBIJwUnj6gHz6erhYWLWlL2hSahbwdmJbLuzNobHXDtXu0aG956xgdLm/d1pIWL5zpCOGcFr93tLwnQqurmhC6XdkIUaw2ssho4KcteGxpT4K2Vw0XjeVQyUBaODRvO0oaHQn650ZfmGomzEhNev7uEN+kj4lj2ts/Id7v5+Hxq6MT4AFPj2EnT/rIZ+F97cut8kQFZnre83fpBd/T/obMhHHYWUniqEP9RXYjaB+QCD6ogEijEgF/h8482cFu5iBQzoudDYflr/Xiyo1dtrwH664PlhH0/pKZSL3fwc189IjRTvDB91F7Oam+oATihQSSAWWOAPm9SIC9f/aMVmYmgI36gtfiD3wL/q97p50U5yX3Y5mzhzSn58k3VfLiJf5XpIxvZjt0oMk3QNN9d8k/fTOd9P9SPLR9eGZKT/vjwDy0W/HRfkdwkzzpM0Jn8BmE6yKC9CUEKQdPSzcV2QqkO0hggOT463GdpUXF8tJjFMxA7ERFCNEWWfzjdJp/yh4rlBHc7J6cDI9PFRAQ6W++BBFwRE2Tl8kzmqo7+KjB5iYvhGl9LrowXsklQHda0LXeVLI5
*/