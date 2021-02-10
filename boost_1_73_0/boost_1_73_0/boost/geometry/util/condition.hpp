// Boost.Geometry

// Copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_CONDITION_HPP
#define BOOST_GEOMETRY_UTIL_CONDITION_HPP


#include <boost/config.hpp>


// The macro defined in this file allows to suppress the MSVC
// compiler warning C4127: conditional expression is constant

#ifdef BOOST_MSVC

// NOTE: The code commented out below contains an alternative implementation
// of a macro using a free function. It was left here in case if in the future
// version of MSVC for the code currently used in the macro implementation
// the warning was generated.

//#ifndef DOXYGEN_NO_DETAIL
//namespace boost { namespace geometry { namespace detail {
//BOOST_FORCEINLINE bool condition(bool const b) { return b; }
//}}} // boost::geometry::detail
//#endif // DOXYGEN_NO_DETAIL
//#define BOOST_GEOMETRY_CONDITION(CONDITION) boost::geometry::detail::condition(CONDITION)

#define BOOST_GEOMETRY_CONDITION(CONDITION) ((void)0, (CONDITION))

#else

#define BOOST_GEOMETRY_CONDITION(CONDITION) (CONDITION)

#endif


#endif // BOOST_GEOMETRY_UTIL_CONDITION_HPP

/* condition.hpp
W6UV+eZt/tlgqVa4HDqP1w+7sY5T1Wuo8uSr6XpZZx+XnWxXLupRkuU96yZEwzO/izKx6JN4Ng+91PdyVGqRbgy6o8FHe+0dfys1UkPiAw9/e/C86dhnyl//yQ7B6h5ci6ssxW4eaJxvKM/oX56etoKzzt/Gw6Pvu2fd8Wm331TN2e2hgvhiqOh0TSQhxHUgbsF8Np5NVTWZTuEHoH2ldkS6nWEwWQNRWbBpQqLUVLfyibO5xi7Bda/zmnvG+g6IzDog5KFW0dkgYKgkX0WqjbQRI15oCKTv4+HlxcU5DMWgC15VD1ND/XUgRDnsF4FRNAfNQA3V1reh/GPbX0lBBKZNT8ZAi3D/iAg4hFWvVTJiO73cfulXQxlPGHKJTmtqUG4UFz1+nFK3xyFoFIAFV29O/e65ICKF64fZXmx0OQawvacS6mclfPnggQK94Rv0fK2/qe64nyja+06kB4LSXtpKzHAcmk+1ms8svl6TAEbNZEV4RIBwSABxUozGLLE40/8Rj4K7AZkSb1xuD/VJ6QldMK6VzdtY5UVEMt22FQhqfGhn4Zd4sV4EjW/m06bjVNalenqcFTkqvW1VgpolhyUh3wLapQNlw7tnP7QRaPVe2Vo912McW5VONyvT1jpdDZnye9NlGWVUUDaO
*/