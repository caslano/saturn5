// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_FSTREAM_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_FSTREAM_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              
                 
#include <boost/iostreams/detail/config/wide_streams.hpp>
#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# include <fstream>
#else
# include <fstream.h>
#endif 

#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# define BOOST_IOSTREAMS_BASIC_IFSTREAM(Ch, Tr) std::basic_ifstream<Ch, Tr>
# define BOOST_IOSTREAMS_BASIC_OFSTREAM(Ch, Tr) std::basic_ofstream<Ch, Tr>
# define BOOST_IOSTREAMS_BASIC_FSTREAM(Ch, Tr) std::basic_fstream<Ch, Tr>
# define BOOST_IOSTREAMS_BASIC_FILEBUF(Ch) std::basic_filebuf<Ch>
#else 
# define BOOST_IOSTREAMS_BASIC_IFSTREAM(Ch, Tr) std::ifstream
# define BOOST_IOSTREAMS_BASIC_OFSTREAM(Ch, Tr) std::ofstream
# define BOOST_IOSTREAMS_BASIC_FILEBUF(Ch) std::filebuf
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_FSTREAM_HPP_INCLUDED

/* fstream.hpp
MwSunA6tu1/bzwKq8qkX5f/A5oS0X+3/dzaZvu1xhWFD8ysnEWVuxMj9zBL89POwqUHOlC4FjjIx8IRbezqv5nHpYWWeFSnmrWmgw0Bvb8AaomAjxV7RRwphBBBsIEp6QsB63Xsy3FuuXnBFAespb0rezwCElqJeOkr3U+b+uMyzfwnbNraEnF8hpM8ieMBmLe8jxxoXrUaPgnyJer7gsMoZXb0kNeeKJOYa5DhvTB/0JggQ
*/