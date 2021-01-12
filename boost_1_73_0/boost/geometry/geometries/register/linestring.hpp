// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_REGISTER_LINESTRING_HPP
#define BOOST_GEOMETRY_GEOMETRIES_REGISTER_LINESTRING_HPP


#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

/*!
\brief \brief_macro{linestring}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_LINESTRING, linestring} The
    linestring may contain template parameters, which must be specified then.
\param Linestring \param_macro_type{linestring}

\qbk{
[heading Example]
[register_linestring]
[register_linestring_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_LINESTRING(Linestring) \
namespace boost { namespace geometry { namespace traits {  \
    template<> struct tag<Linestring> { typedef linestring_tag type; }; \
}}}


/*!
\brief \brief_macro{templated linestring}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_LINESTRING_TEMPLATED, templated linestring}
    \details_macro_templated{linestring, point}
\param Linestring \param_macro_type{linestring (without template parameters)}

\qbk{
[heading Example]
[register_linestring_templated]
[register_linestring_templated_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_LINESTRING_TEMPLATED(Linestring) \
namespace boost { namespace geometry { namespace traits {  \
    template<typename P> struct tag< Linestring<P> > { typedef linestring_tag type; }; \
}}}


#endif // BOOST_GEOMETRY_GEOMETRIES_REGISTER_LINESTRING_HPP

/* linestring.hpp
lAuT2UfCwoQdzvDiM+VFmLWwsKQbD7lGMLkO/9qN4rqbVjO8z+9+66yYn7CCwhb+9lL/O2iYjOfSVyV9OXeYv7DH4y5yfqNgNsImf/H8xBoJc5ZW99117ndYMWHNN9tYcu4wc2GX1u+6zLWFFRJW2rkQ66BRdcN4Vr50jTELg8l7qVR1723OHWYnY5b8azX3LcxBWIx9AWPuTcXO+lVsxT5Z+byotKJ3GDOYq7CDyUMYz7kw
*/