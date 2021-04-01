//  Copyright (c) 2006-7 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_WORHAROUND_HPP
#define BOOST_MATH_TOOLS_WORHAROUND_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/config.hpp>

namespace boost{ namespace math{ namespace tools{
//
// We call this short forwarding function so that we can work around a bug
// on Darwin that causes std::fmod to return a NaN.  The test case is:
// std::fmod(1185.0L, 1.5L);
//
template <class T>
inline T fmod_workaround(T a, T b) BOOST_MATH_NOEXCEPT(T)
{
   BOOST_MATH_STD_USING
   return fmod(a, b);
}
#if (defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)) && ((LDBL_MANT_DIG == 106) || (__LDBL_MANT_DIG__ == 106))
template <>
inline long double fmod_workaround(long double a, long double b) BOOST_NOEXCEPT
{
   return ::fmodl(a, b);
}
#endif

}}} // namespaces

#endif // BOOST_MATH_TOOLS_WORHAROUND_HPP


/* workaround.hpp
M9HEIRhAQWAsz9iu1l920rpxWXNxixmGhQa0SRjTifqQ5bzXzcfpJ+sgS6NVUKtzDWaObtVFUwqGD3xQtbhUMif1c+JcfZbdn8v/0cfsQEmkPOLDZ5cwpVPDhS+ByzWuD0A4n4mCaTxPERleLm5yDKf9pau64ttkMSvpO7cCq2WrGvTgrtcLNjIkK0K+4Gq8lQDT62zF0Z+2pckLOrj5klgIrdUrOXNKkHUKqs3LsRyq7uBbEO268LQuZiY7xpnVrFrC0hueJ/wKOjUGTzG2arQJmbHsSW9KebvTclardpOfObaOkZeVwu0CujXgOiWsxLndayk/Uwd+Kr4uDc/7sX5EBybC8Rdoq1/gMSbg3JG6FEBmOeZi+4RCpK+kvt+XrtyfSX6wa/7IXM6v59FFmNf00GA9QJwigNTDf5XK5mvbKhfVjrqR2wAdETSgJMMI+nIWsi2Xqg4mo0i/0HvaaDcNZg6k5J7ABsjHC8wkoPA5qVpF4iOoeRrRV46K3oY1br3TyBRmBGxbIWY2p4WAr4d+Zpp37xG91+Q6GKfaX48EL6eUlQYsrZvkrQ==
*/