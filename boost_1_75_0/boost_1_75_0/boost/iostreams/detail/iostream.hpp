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
48FbvgKFVccQ6b5ZrI2lfJ796nf25zeHm1mSvfuz+vmn8Lr3M5VC9bLozt1XySUXgRKA0oR8MQjHt10ghbnLpBdWy23sxgg6O6MGMLpjQLpX6RW4GXNXmPe1SKXmsa3oOoPq2jHVAmvqQnLKRtBsOjtfsvLBUIs4puovK1OZ0SC0jYUIw+u7Scan47vJ6/nuG7Ll4fksruMZptPuGe7x2h6ZxhlivcWZakepwYsEdy73skl/HU0uKZRm/IurDJHOZdOIdBX0+TWgE1gttBcwDMctd/4KlME80nmh7nahCrgeTgSlWNwOw+/sfYqrLeX7K6jZTrkBr1crk1ukUuzyPTZE0H+1sU5pCrFjx1GmksRuhTaSUjFV8vS1P9ZuM28ShgwWeQLfnk134HyQPF7cxlIq8x24D2nAbRmrRANZoZVeyy0HngM2jcNPdyX7v/v1qgmtjqToMgsEBzFiyH2X5Qlyekcjp/czMjKGzpaDFkfFd8IUzL+X4pdSY9E7rbM6JOacpZHlRKe7EKd7Io9EpE6+8M9ML3skAgninoCasyK/IJ6JMi5e5WGokHCHYo7k1X1zsplJvb3YJly5jYdVIxw6J/EHu4pfssXIu7xtfuPqYK0wVgEoD3rbzxRKuxwW7dWUNlimVq8g26k4Cp5Ipy45VCtnuqIVNdTyHRV8PjBcF9/lBaw3QU701q5M+Rgyf2K2eo5Pe8KaO9hO
*/