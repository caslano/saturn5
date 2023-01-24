// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from http://www.boost.org/more/separate_compilation.html, by
// John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_WIDE_STREAMS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_WIDE_STREAMS_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <cstddef>

#if defined(_MSC_VER)
# pragma once
#endif       

//------------------Templated stream support----------------------------------//

// From boost/dynamic_bitset.hpp; thanks to Matthias Troyer for cray patch.
#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# if defined(__STL_CONFIG_H) && \
    !defined (__STL_USE_NEW_IOSTREAMS) && !defined(__crayx1) \
    /**/
#  define BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# endif
#endif // #ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES

//------------------Wide stream support---------------------------------------//

#ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS
# if defined(BOOST_IOSTREAMS_NO_STREAM_TEMPLATES) || \
     defined (BOOST_NO_STD_WSTREAMBUF) && \
     ( !defined(__MSL_CPP__) || defined(_MSL_NO_WCHART_CPP_SUPPORT) ) \
     /**/
#  define BOOST_IOSTREAMS_NO_WIDE_STREAMS
# endif
#endif // #ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS   

//------------------Locale support--------------------------------------------//

#ifndef BOOST_IOSTREAMS_NO_LOCALE
# if defined(BOOST_NO_STD_LOCALE) && \
     ( !defined(__MSL_CPP__) || defined(_MSL_NO_WCHART_CPP_SUPPORT) ) \
     /**/
#  define BOOST_IOSTREAMS_NO_LOCALE
# endif
#endif // #ifndef BOOST_IOSTREAMS_NO_LOCALE

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_WIDE_STREAMS_HPP_INCLUDED

/* wide_streams.hpp
uDeccvk8gZw+nbrJ07p8GoGjghy28E2wTF6aYHQRtpG3xe8/1GFoMbSl7Bt9xu5iaKP9jGuiEORCVo25id5F1sb4mdgZzRVNBEO6j0PYjiCPLjQnpLpPZNu0rzP0tG+yT/M9QHpdqDJYctMP7QwdrufSed5F1Ubnn/8DNuglcB6MPYSy1eyMt/Sq9WBzhsdH7FrOudHsjGxv/iGZo8IbjnLppYElGbEmUtR3IgLgccvMcVS+yqysdvM03ajQZ/0RGvzsxe1vcwdi2rAP64LWgEkyzVYHsYuKFT+3dzZKfIAZpxUlb+98kkTr653kaJdVTXMD7zcy8WGvxj65ER/EAnkcbyWTj75sSR8euf6mCXuh+Y40vei2srXH1IL63W/WY2lO+xZTaczhNyUjNqgC4vfMGz0mDrUHEZPOva48tF4NAkCvvugor1qZ33DRg2+SCckk3pM0f4XmzbG0TMcPvdJMsiQeSpBrHI4V3xzBc7jx4H7o2ajNC/dly5aV7l4s4BvasI6oihaFi5GsuQ0q/RqqyPywXLBEQ5izodQ7yhNYnRrEwqqtDWvO/UzseJI6/MZL2/rN+AZjHc6edniO2kUMU4x4OhlEGMAy3Mn6x1LhCyEO8Lfgd4YBPXhcZMlra0KXyZygUNfe1tqVxvrSWvaZXZiTE9QVdvUolZfgUp3XNxQyPDczIpet6dhXrpkeWAWcS8STJurrl78A
*/