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
DqKRTwu5+c0ujZB4HsOtbL+o37+gUHIc9HwaEOt3c5t/hhkXqJV2n6dfMZqzUY2+8mtefli6gg/EUwvbLbDTy0hLybUbCInISrHKhueIrqVqi6AK1B+th8NJE99HnEtNt0T++ILRpvJtowNTvZVqjg0glDfVd+L1mjValkB62pnZ8Bk3kLIyudfdDf1QtfV2DFnB6P3yup+7OjwevXNjvZm/qjLqBEaDaBJGLAz2DDCKeTizg2h2GaoeewQ1Hw69rJkF3JxjsORhtk3on+Ar7l/eSI4iy9A7/UQGKbpqVSjcE2/H0nrXDu1KFJTN/O5OFoHG5FOvIwDJxv/fShtVl5SPNCg7RfSB8j1oLLEnh5+MOWqHOVn9Bfd/h4XK2FNh0J+IYVwLwNZopx4znxWt64G/zwixxxz9TVBTnJB9xuVHxIjM1JikRsO4/s1oEsQu9yMSfbcspGx5nP+5hDrrC4JMf6+nzponEI4SNkH2f59J/l8VwzVpkipkaRxMcamrZ7R+j7rpLnrZh0SQweKGT1sdXP0AwaDLbtMT5RQ2FqCLGdVHNRlhvs2MyQ==
*/