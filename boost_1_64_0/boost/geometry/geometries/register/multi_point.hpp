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
pKWF3Ho6KTMlkx8AbjFoTqKFvkwaomac1vri35zXEEWCAVlK8LBuj2slGlZ42I4B9P8bQchtwnZp8jpYOPGNy+UalfJz6lX0/YFsvgDIxtRNmfaOWcaZvCpWbiSqNcQuhEODB2DVmJ6i12Z+TBoKW/0/dFpTehbWRIQzhmXGS3ZJMFwJKVYfANErDHRQrJvSfgrw5o+nsblMUOaRg2+cSJ2NaUZe4IslJ+kmHh9DBlCZmyLs38TStrElXru7V6okJrvRv05gNVUF+Jg2kp0feNl5wNWcgwoNwt5LUknwEILoriIlYYqp2V1Lhbk5ieRNOPHYeuArlKPhrqKgHr9aA2UAG8Gul5j1P15oMTk3RD5sm6KpdYcTOS3jB1AEYzDXBcx7Exmwb2MC68h4QD8SXypoA8etKL16FOQguW3nNuABkR8JSXi2fnqzUZe0xWrpxKHAJSEGc/Z15lSNhNAGxpR4f/agHGVmgDLsoLXdZI1bdMppirjzQ3VvrqO2MKL11OO/cc3uucsbAU65woF5FCN5SnJK3UZWUORr6/quz8KNFbIH0ss3OD2Heg==
*/