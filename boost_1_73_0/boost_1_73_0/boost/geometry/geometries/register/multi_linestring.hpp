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
8v4uPc88ijlXxTNXxzOfYuQHwqe+kC7W8yygmCIVz3wdj51i5MeUO8sfukjPs5BiylQ8dh3PIorB1hxt7LZbnj+o51lMMXiMeCXnWUR4F0O1g5cNuFlLV8ElM4RkKZcUCMlaLikUkg1cUiQkPVxiFZI4l+QJyV4uKRWSO7mkTEgeIfJlpxZNd7OkSV7USX6jk7ynk5zSSfA3XFpJlU6yTCdZp5Ns0Ek26SQ7dZJdOsleneRWneSATvKwTvJvOsk=
*/