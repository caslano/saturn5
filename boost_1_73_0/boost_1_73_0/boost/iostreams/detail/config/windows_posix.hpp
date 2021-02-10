// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2004-2007 Jonathan Turkanis
// (C) Copyright 2002, 2003 Beman Dawes   Boost.Filesystem
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_WINDOWS_POSIX_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_WINDOWS_POSIX_HPP_INCLUDED

//------------------From boost/libs/filesystem/src/path_posix_windows.cpp-----//

// BOOST_IOSTREAMS_POSIX or BOOST_IOSTREAMS_WINDOWS specify which API to use.
#if !defined( BOOST_IOSTREAMS_WINDOWS ) && !defined( BOOST_IOSTREAMS_POSIX )
# if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && \
     !defined(__CYGWIN__) \
     /**/
#  define BOOST_IOSTREAMS_WINDOWS
# else
#  define BOOST_IOSTREAMS_POSIX
# endif
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_WINDOWS_POSIX_HPP_INCLUDED

/* windows_posix.hpp
heTI6YtWcPV1n+fKULbgGifLSKuS/hK4d23sTsLNUA4lAA0c1twEg5zyzeFd2FdTw26n3KgytZ6fe/78eP1phUW0W7A2R11jaFa525DrSrDvCOCGAXT3V4tadp+rhfo3Vp2q1imrukWrLsbzauWEsbe3XvUiSdjM6Pxp/bBde26eGc78/wFQSwMECgAAAAgALWdKUrh2SMsMCAAA0xUAACQACQBjdXJsLW1hc3Rlci9zY3JpcHRzL3JlbGVhc2Utbm90ZXMucGxVVAUAAbZIJGCtWGtT20gW/e5fcTEma2eMBGQftTCewCZMJrVZmAKyUylwHFlq2VpktbZb4lHB+9v33G49jUnYrREVbLrv4/R9nL7K5oaba+VOo8RNhYo7my9/v6ezSd99JubfBA8+WeFXJf8l/Gy98GTyQPYHSlf4/I4Ll2qNh8mAvqvxQH2jMSl8/MjfJ5PvuLliYPzLZcWrCX/FSmcTem9keq+i2Tyj/psB7e3s7QzprZdEIqbzTCRToWZD+jEwK4dz7+7O0eKnIYmMvNgxFi7mkSYtw+zWU4LwPY58kWgRkKcpENpX0RR/RAllc0FhFAt6c/rrp/cn74Z0O4/8OWzcy5z0XOZxQHPvRpASvohurInUUxnJENqwHUQ6g708i2Ti
*/