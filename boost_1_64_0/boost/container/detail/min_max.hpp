//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_MIN_MAX_HPP
#define BOOST_CONTAINER_DETAIL_MIN_MAX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace container {
namespace dtl {

template<class T>
const T &max_value(const T &a, const T &b)
{  return a > b ? a : b;   }

template<class T>
const T &min_value(const T &a, const T &b)
{  return a < b ? a : b;   }

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_MIN_MAX_HPP

/* min_max.hpp
03Zi4d6T6MNTilyXLgVGHG9WEpiWb/Ssy3dlPphw2sufWPoXZF4+H+gnQXgVfKo8LI8GZr6IOCh0h4UMeqIgyoBVbzNvG8rhK6VFD94wRm84EYQhiXAAy6UHNEdryVsdZ2pUCMcE99htVcxuG8KfFqQj7RvaxNOBT8qsiJ7bbvLay7iBcL6WL3o1SRS8C7mS2k13ak9wac2vQGOtcwyok3BrwbbP8aSLw3/NzV3CDqBdZ8892bdikeql0OcRFBQtWBhLE8J79DAJDXWoafBNGu3IN2DwQ97AAlqP8R66Pu8ZJiY4k/PaYQlx/3dVbCm7xnRcJPVj4ULajCUy8xpTZUV8Qgng09hyaIF6jLqHQqOjErROezjQTKj3dOjiMMXysklcbl/M9AxllXFdXQw1Mokrm1KAnrjQrE154cVQFq7hiAPZJHTcuT68sVbwawL/z1FgvbzwlBRluKuvjXEQChcJIVjfn9ik/Q4hm2YQsH2WICUnSgfpXJEQ3Nr+GuxzhNuZjj7BKesz1bwUUvon2TXEBjv97skphOKPJvmgKPk7EwSwnEZddgAU+g==
*/