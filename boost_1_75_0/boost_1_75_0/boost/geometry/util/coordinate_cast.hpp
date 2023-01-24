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
5f4r+NtRhg9Oxi7dUdAQcQtmPpoWzJsfeYQ95vBXASyccgtjyiwFeWYGyGmHYuXPX7XyOntz0boSF8QTB/YMRzuCM9Scu2hak6XmrEhI/ZHiMOw7GM7tLe4tacGRsoj8ifr1VmhpwWFBqTOOqRdMevDL6vPi50Nawa8Fl50cFD9r2EkuQmgCMeqFJS+UP/4wr/OsUZEKKkUpTHVcW8D2ZZ0MdmWpkpIfqNUtKqVwWeHktIUUXHwL2vKWzXs74mLqsULW+kPKNrm+3G/ubSiDG2SAyE2n9kxjbuF8j4KqO3W5reWryJ+qP6gDtHP8xnGsSfWMkbRYPnj8zvJwI1oy0ml2ucIG1Q/OWqaMzrJTEkVatdfBtwPGcpf+fD5JwIblbvPkxU2nLya5b4JNVYZm9GhSVqRMZ1UWtVKeRmIi4tcknLG3apfbo3fnH/ozLH76SMIoy6sBBm2QQWNnsSmDtu6iFgIwBuXnrT9EwHsFsYTqIp+dqWuc6f9C2FkFxQEkYZhAgASX4BYgSNDgDpfgTiC4BRYJwV0XDe7uLhvc3d0ti7vD4rLYwrKnVfdwV3c1U9U1L13z+nf//bWwxY4Zhqfky5fXPHCMywwr4XydS+cgUQ1MTnNZdhdj/Rbsemf6ioO4V7unNEMfqfbkl6cszlq7fLMH54rTBJKeQjLTVKXd4GGZvAPK5DuF3OlMZJLm9goYJYMq3nbdLGTB
*/