// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_IOSTREAM_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_IOSTREAM_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              
                 
#include <boost/iostreams/detail/config/wide_streams.hpp>
#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# include <istream>
# include <ostream>
#else
# include <iostream.h>
#endif

#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# define BOOST_IOSTREAMS_BASIC_ISTREAM(ch, tr) std::basic_istream< ch, tr >
# define BOOST_IOSTREAMS_BASIC_OSTREAM(ch, tr) std::basic_ostream< ch, tr >
# define BOOST_IOSTREAMS_BASIC_IOSTREAM(ch, tr) std::basic_iostream< ch, tr >
#else
# define BOOST_IOSTREAMS_BASIC_STREAMBUF(ch, tr) std::streambuf
# define BOOST_IOSTREAMS_BASIC_ISTREAM(ch, tr) std::istream
# define BOOST_IOSTREAMS_BASIC_OSTREAM(ch, tr) std::ostream
# define BOOST_IOSTREAMS_BASIC_IOSTREAM(ch, tr) std::iostream
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_IOSTREAM_HPP_INCLUDED

/* iostream.hpp
lKtGm0xCeNJuhGPfvClNJay8+tCcf/IZimE9Yv38mvwRFcJ/kj8yNTJ8jl3yzzzlaErbzi/hZbgeDB+CANvzyuaxvkqOQBs7QZtp0OZO0Odp0NZO0N8yoPXGDtDfs6DNHaAv86aIS/r8EvRmJBIy6sqsqC+Lex4NetIqADXDgAxoen/S/Uh+XbWMOZr6bZa76SC3IKO3JewHmN6K2MZR7pCMzMBdZuKghBMIGTczI8j2iO3UVUOWuglS13o9/sYL+bXa+LWAjvmOTgmVAbYKmS8B6YvKAcRuS0W/0Qai0gojiQx9jB46Yee44Ci/hEnP8rB+47MgivaJhcDSeJupbg7OmPnOUI44TvNLiMczFBXsgE3mriBHyYx77iHlcKqJGZ0zflgsYnw9sNsIGEyDckeoYYiGR9iCzCVEAUvzZLqvwi9pRcE7ibFvSUPH2Gj2kB2pbkfnkkSZzplqqkIw2Lo0oCVAOHeYc9flt+hSmRAsyS0V+ohl0qCRELvUTbuYakk2SQGqK7riSXKRbSBm/w9QSwMECgAAAAgALWdKUuEFulMABwAAkR4AACEACQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9jaGVja3NyYy5iYXRVVAUAAbZIJGCtWWtP20gU/Y7Ef7iy5AJVHoCq
*/