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
hv2qczz4HIEQYXBv+Or9D6/e7x/saY+AvgCvjAGrE13HP/BNVqTX2a8fX/w3zPXh/uH+6UOc9UMBztG74eFe8IT/+LC7f3o8PDk6+HnoHzRavDs++vMvwdMT6A6enh4FT5tP9o70X2AG9NfR26Pjoftj7+hQ/ng3PH5zdPyW/zg9Onqze+K60Tavj96+OxieDmUxb09+gKlgqy877sI9RU6lGCNPlsxKQKKAXsfpdEpcxjgD9iYrkuomrxFzXSSnR4DNaAsRCde3sww3ng6u9yQv8prPhlqMsON+r/Mu4NgyFI2CrJAsS4aA/87rKsGhLIjQOMCCAdK77up+A88Wf9t8Oc/+c2t8uSiuAN++2T04Ge4gXiWqcTGvTgEQe9hwkJzuvx0ej94dD0+BgTp5MzyGSX7ZaA49LoFvyoARWzo4rI4QMvwvTdwniTIyuChutX89K+c1IOnnwDsDo0QbgYTXHQgwxvUlMMQ3GXCSxeOaXyCdYSLAV46ajJVYnc8z5MGLW8IiMJiseZLVQIVG2D9Sdjj3npyHNAD+MJ9no/E0S+fyCmdZ1eUMePRpgv3NK+zxCx1hOr1JbytkuXm9DpxgenDziouMT3NA8wUSlhDxvUBwQurJW2E3+Zrad2zugDGSA5A6a7n+LWhn
*/