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
kTeVx7pPjTfDoe7edtmr5GVswt6EvD4xq0tv6BWX+Bp+fiFT97OG/UBlYxbK0zz0bvRzMb9KaGtFipw9uI6SJ9Pn6Emwhca3Ij3TW8FAooCveF5iYNZNdSpa4P/DQ9hiY/SSbyvogtyej8aBhADE04N9szfgNZCjqzH34KV3gfLafEkQwEEPZXXR3/njAdGSdBkz1d3h7UmuZR8zaI9T94LXoWt1lSDWtpBEFd0yqFVKd46G02Awj14JU0WB/NEc+KaFqIP87PecCd2UpVLneMkU+ntljJLofuDNNoHtMxIweOMyGfSV4HX9DHGq+LK5UcAvFsNwTr7ebmGWf1Wovz93+HFOQFqE3OToNv1mUft5I8OglNjvpgh81FLBz9ozl0aA9rVXyOM/4tKXZ/6gwsnpA7GSLhvcB2gXK1D6BZ6D/KoRAE8/XhbZQolI6CPxzSebgfDLbiP5Gvn5VildB8ZF8lRAZ3unwsmOQatSKrSQXP6jYI2v1EuW/hxDBYU1NczyyokKC+u949l5xEiF4FoivaB6vTe51eRsMQ6RtQpuH8/OJ0/MwgyagA==
*/