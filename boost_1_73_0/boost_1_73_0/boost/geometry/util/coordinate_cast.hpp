// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_COORDINATE_CAST_HPP
#define BOOST_GEOMETRY_UTIL_COORDINATE_CAST_HPP

#include <cstdlib>
#include <string>
#include <boost/lexical_cast.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

/*!
\brief cast coordinates from a string to a coordinate type
\detail By default it uses lexical_cast. However, lexical_cast seems not to support
    ttmath / partial specializations. Therefore this small utility is added.
    See also "define_pi" where the same issue is solved
*/
template <typename CoordinateType>
struct coordinate_cast
{
    static inline CoordinateType apply(std::string const& source)
    {
#if defined(BOOST_GEOMETRY_NO_LEXICAL_CAST)
        return atof(source.c_str());
#else
        return boost::lexical_cast<CoordinateType>(source);
#endif
    }
};


} // namespace detail
#endif



}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_COORDINATE_CAST_HPP

/* coordinate_cast.hpp
kWxyzixmsvj0m+ypoxkXV6Pmhg/M/cnubMLhSE4mwg+jvTw42Hv55z8HDSTCyCRIOlDbl8RB8WDGQIshCGJEQJvvBD+gXF0TTMVNknHSkCOFZT396DbjTJs/tZ8ftL97Zewc8yy1S8XINIdTtKgXpmTawXTGeBHyXhpk7NhrFo19GeAr0CgGYw4gCt6h3cSaOlhmdX08yhOdy4nr2As6NC3M+OHDh72OnYdDgajDIpoX089adX+auu178I10Ff9DpNG/wY+mLMXOqehZEwSzJAblxpQtoaX8yV3KBW378Yux7/3+JQH+wJLOMGIETf9HN2k8sYY5euA7eKCf5hz3636BmxlFC7iO4eouGHgaFyiPIQz6ih6lDCrQ+Dh+uKGtGtYJJcqiHTZrOiMPkTPherlxN0a6x5MYsXSBgEopYJCYVY8D2yOyoUqumnaCEOGX1NuFWHPPf8BfLs6HI/jXJhIQ2dUqkoSoLw+ev+IIf2wMcBGtFmHCN8cus/H3NdoM6DrA3H968fK5zZP7rv1t+4XwGeNU4Bp/J+iQjVG7oj5UzIIx+IcsiwHb1c46H91yNHKKOpCYwWlq2Q2Gd5kIWC9yii0Wgcp2OsZVdBN+xkBxoCLrBIANpzflRDg82kb5ZJua5mxbZ+1qOoJb
*/