//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_DEFINITIONS_HPP_INCLUDED
#define BOOST_LOCALE_DEFINITIONS_HPP_INCLUDED

#include <boost/config.hpp>

// Support older ICU versions
#ifndef BOOST_SYMBOL_VISIBLE
# define BOOST_SYMBOL_VISIBLE
#endif

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_LOCALE_DYN_LINK)
#   ifdef BOOST_LOCALE_SOURCE
#       define BOOST_LOCALE_DECL BOOST_SYMBOL_EXPORT
#   else
#       define BOOST_LOCALE_DECL BOOST_SYMBOL_IMPORT
#   endif  // BOOST_LOCALE_SOURCE
#endif  // DYN_LINK

#ifndef BOOST_LOCALE_DECL
#   define BOOST_LOCALE_DECL
#endif

#endif // boost/locale/config.hpp
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* definitions.hpp
cyWGGoU3HPd0i1EvG5t2u//o6fbK4JkJoJXJskpVkIm8knAB7VoaQxBFCZMAG1yflailbHCQ3DdwHDZoTnLOZ2p4msgil/qM8yRZiBB9k0k+9T2RiuGv6q4V9LQDiUDe+XOBQjDOrUdjeaBT3ejyfIxafjwdn4wvBigjbDrX0ocB1iUNAmae5UjUUV3ZwvyNYryQU8rTfe0QOlOjiYmTW6/j7hA1d2DXhYZ7zem6hIA3MU+aHZ2QJp/Xn3u1y68V1VzB6Lrk6b51H9hqmuemlmRb6Dqej7rc9uIHTNnZlycyrnWjWpKSvP5RT/e9XCvUhW8dmoDWOzxshR/NhzvuDLep82unNhEAHHPkKDhoZJGW2qPR5Pji9atj7LViQtFEDw7GELIJWc8akBl85WONH1DISuGy8ApEyvrSEPmzXjt8QD5ZbkL0ANcG0kzcqkY0bZc2PK9xyzdAdusedtcCWNEOdtAQLK6qpeGcuKAnR/Ss5pijCvuvbXzZyGcizVek7mDkgYQzd8NZ1yQSxTMIBI2GJtcocIPnEPacq0b2sCqzD4yCWxOw4nyuRcciqW8KWekCzFZGsOkh62iordXdorb9I9po8yBw09HVmnBbbcFjmSv/zXxZy8LWiiyGPGaPRlO8HBC8lwPYo41Q
*/