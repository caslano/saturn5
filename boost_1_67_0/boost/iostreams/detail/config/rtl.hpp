/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 *
 * Defines preprocessor symbols expanding to the names of functions in the 
 * C runtime library used to access file descriptors and to the type used
 * to store file offsets for seeking.
 * 
 * File:        boost/iostreams/detail/config/rtl.hpp
 * Date:        Wed Dec 26 11:58:11 MST 2007
 * 
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 */

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_RTL_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_RTL_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/iostreams/detail/config/windows_posix.hpp>

// Handle open, close, read, and write
#ifdef __BORLANDC__
# define BOOST_IOSTREAMS_RTL(x) BOOST_JOIN(_rtl_, x)
#elif defined BOOST_IOSTREAMS_WINDOWS
# define BOOST_IOSTREAMS_RTL(x) BOOST_JOIN(_, x)
#else
# define BOOST_IOSTREAMS_RTL(x) ::x  // Distinguish from member function named x
#endif
#define BOOST_IOSTREAMS_FD_OPEN   BOOST_IOSTREAMS_RTL(open)
#define BOOST_IOSTREAMS_FD_CLOSE  BOOST_IOSTREAMS_RTL(close)
#define BOOST_IOSTREAMS_FD_READ   BOOST_IOSTREAMS_RTL(read)
#define BOOST_IOSTREAMS_FD_WRITE  BOOST_IOSTREAMS_RTL(write)

// Handle lseek, off_t, ftruncate, and stat
#ifdef BOOST_IOSTREAMS_WINDOWS
# if defined(BOOST_MSVC) || defined(__MSVCRT__) // MSVC, MinGW
#  define BOOST_IOSTREAMS_FD_SEEK    _lseeki64
#  define BOOST_IOSTREAMS_FD_OFFSET  __int64
# else                                          // Borland, Metrowerks, ...
#  define BOOST_IOSTREAMS_FD_SEEK    lseek  
#  define BOOST_IOSTREAMS_FD_OFFSET  long
# endif
#else // Non-windows
# if defined(_LARGEFILE64_SOURCE) && !defined(__APPLE__) && \
         (!defined(_FILE_OFFSET_BITS) || _FILE_OFFSET_BITS != 64) || \
     defined(_AIX) && !defined(_LARGE_FILES) || \
     defined(BOOST_IOSTREAMS_HAS_LARGE_FILE_EXTENSIONS)
     /**/

    /* Systems with transitional extensions for large file support */

#  define BOOST_IOSTREAMS_FD_SEEK      lseek64
#  define BOOST_IOSTREAMS_FD_TRUNCATE  ftruncate64
#  define BOOST_IOSTREAMS_FD_MMAP      mmap64
#  define BOOST_IOSTREAMS_FD_STAT      stat64
#  define BOOST_IOSTREAMS_FD_FSTAT     fstat64
#  define BOOST_IOSTREAMS_FD_OFFSET    off64_t
# else
#  define BOOST_IOSTREAMS_FD_SEEK      lseek
#  define BOOST_IOSTREAMS_FD_TRUNCATE  ftruncate
#  define BOOST_IOSTREAMS_FD_MMAP      mmap
#  define BOOST_IOSTREAMS_FD_STAT      stat
#  define BOOST_IOSTREAMS_FD_FSTAT     fstat
#  define BOOST_IOSTREAMS_FD_OFFSET    off_t
# endif
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_RTL_HPP_INCLUDED

/* rtl.hpp
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
*/