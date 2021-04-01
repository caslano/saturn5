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
ugQyuvhyFPTB/V7ppjieYiYZF8uMLElTO54bsHMUAmN03Y7ijUDhHhnqDTHgya1s5O3AvbXHbel6ZzxllbwBFcbxzriH9oMUiCkzjMGxMNHJxS7csfDU6nSF/rdnNMoQ2sPvM96ODehGNAyRnoH4fEAU/b8tpQ+Bdp3zCSo5qYxPm0USTiqjbi/tm6RTQH/4KKF8wLWoagvgNq347jtvG2gb+nbi8mttWxLAC13kiuCQhA8QzW4ndueziWrtGbDxzYUZpDiy4BTA9lXAPe81/SL4YqMTiDrDil0KdVrfkXORk++8/JW69U/qnEFDbDnb5t70mtPJZSJu7JqJpBEJTO5dDpXdUxyGOCHj65iyVYWi9Icvy9lf/kjV+uVQl4QBukamWuuI7UB5R2Jm3HqpdUqL/Xt0C9YX1VLXmat3e4SzTGbSzU5kci846cqArftZndMm03VRIpO0IVc4NZ8q9fR48goVRll3/AtjFy+Gtog4UYXTWa8yyamgGe2pMPYeW3vPhO8MuI5+rE5QLyqRL3n8TTbtM2ztaQDFj6OtE/CNjsVzuIQEwvACZw==
*/