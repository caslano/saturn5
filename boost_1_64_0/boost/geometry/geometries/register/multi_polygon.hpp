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
hDV42iT+Sr2qn03EXxAZ29ksv7wu9IgZQYK2rlqYOWsOoS8hI6ytgtHxqlsaTphnZ4VnYL3X8q4EHa55++w92o6Rs9Fz8s8gAjdFDy2XyhoXO7DtHhQDBhksg5puZmLHsvrE00zjrkbPjhuXJn4DD7WmmtT4SyaW3HvXKz0PD+k9kiF6iKFj+90E9OAr7AXs/FSGuH/ycb8pXwyN5KjXG/afs+TuZe76Q2QjmfXWQtE3qT01dsa+yQpg/xizhhtDVEgad2bEEJcKbZD+i0DzaDhFYROusGJ6Pzq9T2hLEi1JdBeYoLMlmrCp7elFOa6sL/XNTWdmlGL8z2Syk2U6VTKd/CSh8emx1hOY/93XcY4pA0HYJu7DnwhMS8zEv99alASymbhiPgp3GkU19jZrwl5ALVD1QtFGyBe7mYP2z5sSrlDbDTrpo8b5Yg5YqdyTdxaLdMfxl12syx/MatvlfFqXp1n8+WRWtadHvx/0r1zMvs88hQrmQDsDBlTIC3JUbugKSTFRsEhGTGvof+p/OnTZb+YuDvIrfn6TdNmXfPP8I/PKfS32B13FNA==
*/