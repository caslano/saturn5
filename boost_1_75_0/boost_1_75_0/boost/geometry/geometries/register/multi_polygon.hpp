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
qEAvy37uGVOz/IXlxnN+oTtCAkJ8eQ9YDLUHdSV0/sDmr6gTXlLBRePYSnwFPlrd20NsfeE+nvPpsX4NMKvu0nylzyVZ9MNDJ32pKDuxC5Gwm6ZvJzfpN4NlT5w/UCRUYiR5wi8vPjct3/VrluRpadCoSNza9RssS3QGhtqpPr/+J82WLhxqfPktK12esM6cD3OVrkmob8Moi1+NrkvonFiXuQJSonb5HRsW8llD3JaHw7P/7lKJbOX0yh87Hg7fquxZMW2u3TXpy0hJUE2fkbbyLfhJWs3Bcu3dTI8Pu9tDJ1HFgokKi0PzoiaLSdc2g+Op/9ZBJJhoYqk3b08YfCoir0x4dzoxKXTGNEDGqgenB6yaHAFrdu3/uXim/N2HfQAkL24KzDuEAa5Yv0MITDPljL93yfaFKtrNz0OPinKsDM5fOXNRDYt+ZfBY2dyLNcsRojVocv1+ODGgT7+rZkDnumGHLWOLcxi95kW3T9lfbC+HmiplgXhl96vXfCs7Iumm7iy+i6VnrtQcHWqaJbVuVj+VP6nxtJmoZ6HaoibFXvbboigeUQpVxK0sgkXSN/bR3k0WW6D52byBqgKb2ZyOcidLj3Mq3h59Xgi6yjlzFbugvg844Se1xmTHWdPG/s5OvmJ4gPLzePtw4qPeYHwmG/FoZ46wyMW7rSJ+qJrS+abM51sgin6Z1RGeWxlw7ho23nSWw6uIz49N
*/