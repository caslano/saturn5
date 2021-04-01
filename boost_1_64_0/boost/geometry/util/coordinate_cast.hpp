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
TKm7gGfQMle/VmLPCuNgPrUw0QSqInvkJhdWbZOQItsjG+zoMfqZM+dEmjCTObXfMV9V1sM+7KZnifYeeYQADrRxIsPLwheJ6kSpXRW4w1f0cMPrp4rydBGUsw72l6qtZUs7K50KzpxFRYubbovMcjbD1nP8SqIPZxExL76Mdz95DcACvmBUpEvb4pgBlNYFo74uKeEh6Hz/LfB2pAupAM3R4kPWOGA5OfEq+ODQCClaf53Bb3X4m5XMyfZhaoWZ+pwfFPZ760asb6NB30f65ZpoOvCeAl2ndL5zbW7IHya1FuUfLvLtH9rAX+ZRs71CHw8QVMjCPjfIRpbMLJAZt8E2P+ERP5WQHcex+AvXcZGy7EL43uEm8E3G+bKaJO9336y8inWvRkPBi7FMkd/fZyqdA3MHD04A8sRG+qPajwZ5rpM8o1M3fLP4vDZJXdcRHZuw1daiMmCE80iZh4c1qwcmY338rY3n5nPbXG7WBvx0cyWdPCtcqls7YThL6NkJYZugUwT5AqZiRkhU/MYhVpJbEUdVL2C+P8/Q9eFBz2BX9fiW4jw6AAdc3g==
*/