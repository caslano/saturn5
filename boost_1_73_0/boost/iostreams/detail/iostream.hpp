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
LAnedstt8+cFFxgLFi64w+B6fLqD9nzbZTle1vvV3wY3X9CRv3Cc3giu5Miclw7l+sGvB+jb/ZBgQ50XUAGr7HmqeZ7fF8o5eCOAGkrX4jR3pKHWkBbXsvI3/j5tGEAp+fDdjwaBKTOPTxzkZ5epczOLAe1cLVOWNpCkm+4LAaiBPv4SgcwcxJkvQONoQOual8lgA33n4AXUEafm6o102VZQXNWTq6fBFVf25eZCEObjbxCS
*/