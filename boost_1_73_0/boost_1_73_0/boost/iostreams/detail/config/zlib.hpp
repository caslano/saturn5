// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from <boost/config/auto_link.hpp> and from
// http://www.boost.org/more/separate_compilation.html, by John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_ZLIB_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_ZLIB_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp> // BOOST_STRINGIZE.

#if defined(BOOST_ZLIB_BINARY)
# if defined(BOOST_MSVC) || \
     defined(__BORLANDC__) || \
     (defined(__MWERKS__) && defined(_WIN32) && (__MWERKS__ >= 0x3000)) || \
     (defined(__ICL) && defined(_MSC_EXTENSIONS)) \
     /**/

// Specify the name of the .lib file.
#  pragma comment(lib, BOOST_STRINGIZE(BOOST_ZLIB_BINARY))
# endif
#else 
# if !defined(BOOST_IOSTREAMS_SOURCE) && \
     !defined(BOOST_ALL_NO_LIB) && \
     !defined(BOOST_IOSTREAMS_NO_LIB) \
     /**/

// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it.
#  define BOOST_LIB_NAME boost_zlib

// If we're importing code from a dll, then tell auto_link.hpp about it.
#  if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_IOSTREAMS_DYN_LINK)
#   define BOOST_DYN_LINK
#  endif

// And include the header that does the work.
#  include <boost/config/auto_link.hpp>
# endif
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_ZLIB_HPP_INCLUDED

/* zlib.hpp
wLWgTKiFhgl27sVaknfjRbE3hRsvo3mWpXrfdf1cxUDuBtLXrl+e2Zlni+IUn4Bg4d2TTDPKJOVaDInlhrSQQRTyJ0KBxTSfxpGeD2socJQErlSkRYwKZbVIaAtZ0HkRmSFLEYp4EWX8oWWi2dPtXC5aggghjIS5SuAGIYBMIBHgIeVJIJSRNYcuPRTRNKF9IiU11oBkAiTUPTqn9+ddmno60kP67f3FL6cfL+i3o7Ozo5OLT3T6Mx2dfIKtv78/eYt8R/CkSNylSmh4VhQt0jgSgXH4+z2d/9WYOe8ID/0ib4vM2VLhwkMyec8I7Tr0DmXLpZVkSNICidDkBYGN8dnxh+Oj8+Ptk9OL4/N9o9Ejx7VWtKtELDwtthOZCe2ksRHYc+g4QDpbuibPSizkDRdkTPCmuB6yOeoxkMkfMpqKWCYzh+hjArgBLCkRCiUSH3K8eUu3EVSngny4TYAwT8sOSsRdRjoTqUP/8K4F6Rw5xgHYISx1/bmXzITusgqWWaVYQoH6tnGOGrisp3u0aujlMYNDB8M+w7IVN81n22F0B1lPt2Lre3ya64TxojwMjDTP2OfCVuIrh85yi9ucBJgKXY5SjHwgfFoqo1NBakQwXxOhUKFl4ijBVyYOK2kYhsNC/b3Bav4epa9E
*/