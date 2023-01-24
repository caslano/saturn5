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
5hNUFGabIdibIIwY0iRkEF85xZDeMcgDdNZgOKDmuejH8q8h4pBP/0iDnZKHkNj0QSHRhSUMWR01qwrng3oaM6OJ2FFDtfr93cN8pKGatujsYEEI/ZRG0jaWvTeUHvoXfHErkSSqVB2exy+P+eKchCq4a9omrEXMoHrYhNIGXTeRLghqziRH4QnJjkZN0uVRvX1KSoQKO3MKfLMxFozKbdKq9MYFY5ARL3XIo4eghX2SGqQS/Qget4FxEoGUCcIvrq/A4YIlA7+VRoYQND4nm7LipEO0I1O00kX70PKCr5wJ/MptjVzW8SPFBJFTuaN6UraivkjZY7ir98JaprYJw4Ciow+0K+IPK7K56NVb87agzFCQIUMLWtbw1HcWNeTaok0EyJtjZ6KQG2UkK02v4gVhObEHpKXnjGNlN/MAejQdrCeObzo9C39kFDIt4tnbYyAYB/ZM49vTbGrmOob4qzSwoGDaQidT03NrHWNja987Epgf3g9xklBfM9vL0Yz1+30wldmpGSe+Zod4rcPyxaa/5UxO3Su8LuWlv11SuvXBZ+bRPRi7mjJArsZS3fc5h+NES5xNrGqlbf2w+w1pSC9qKwW1GyOCDBWgRNEB4LTUhVrAKHHlQznQ2SRcx7Li5Pizq3kf1/kPe9sdvKjDHBORbmS+Jtb+hS0CQGFYZmWuTsrm6gGLNlaix9EoJokDTlsZYNBCfS/z2Y6A
*/