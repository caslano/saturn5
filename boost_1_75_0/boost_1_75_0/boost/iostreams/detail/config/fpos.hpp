/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 *
 * See http://www.boost.org/libs/iostreams for documentation.

 * File:        boost/iostreams/detail/execute.hpp
 * Date:        Thu Dec 06 13:21:54 MST 2007
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the preprocessor symbol BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS for
 * platforms that use the implementation of std::fpos from the Dinkumware
 * Standard Library.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_FPOS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_FPOS_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>

# if (defined(_YVALS) || defined(_CPPLIB_VER)) && !defined(__SGI_STL_PORT) && \
     !defined(_STLPORT_VERSION) && !defined(__QNX__) && !defined(_VX_CPU) && !defined(__VXWORKS__) \
     && !((defined(BOOST_MSVC) || defined(BOOST_CLANG)) && _MSVC_STL_VERSION >= 141)
     /**/

#include <boost/iostreams/detail/ios.hpp>

#  define BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS

#if !defined(_FPOSOFF)
#define BOOST_IOSTREAMS_FPOSOFF(fp) ((long long)(fp))
#else
#define BOOST_IOSTREAMS_FPOSOFF(fp) _FPOSOFF(fp)
#endif

# endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_FPOS_HPP_INCLUDED

/* fpos.hpp
2ONlqgU6iBHIx89dBR3WaIHgTwwQGfGmHKdTVm/QL+Fif6WLSCrGh/rgaRfALTfR7XqLX+3zyY7WQ/sz3lKphIt9Vp3+7xwRg0+no9q9fp0r5ZlTf446fnBnCtMB1ELyrUdbGS8X5Hqa3icJ0htnMMI5yJzYZ0iP6DN8Oy78MUpgdxLh4GdnPJ/2JiCiPD8AYJwDdjppsFsv21PlkJ0+vGh32l4Xdu85HJcaFRIjc0jKKoMhTnzfX5Lnm3DPX8+qfLEAlqHHsWs9dFR/y4xrfdLeo4B8Ma6AXd4AEC8MY222MEz10ZKK0S7TttdweBVq5Ssbw9RRJ+8Ihdd7P4+xbLe+iH+13bm/CNObq9LuEPjW8XbIQRrIPdOBtC19+8XpbdDErIt9ymnG2HAti0Z+GNKrlGVCs7BFtqWyCG+ZdFX5wZRILZfw58QcLMoF7BKQ0HJBGm8UT9sytzLbQZGQFciQ/uXRlMvAnjnImoRPKYCkDidzU4Fa7ULvJoDGqPveLKzjfYobpkxb0fiNQbFr/VSjulpIXJPz+mIigsZ/WnnlSfv5iq3Jrh8wFHpK62vTXyP4CqvN4DeTCnWRLimSB1OWAVt27lWR0juBH3ktX4Deq9FBck1vjMj5EjWT0m3GBJbSx5VaKP780VO6G28qd7NkNCIxNknyEw846p4JJ0T04AhO6XxfIYnb+uvaRyDrYZdJz1bUcgl9/RT/
*/