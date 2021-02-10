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
Pkm4oAEj8+xn9yIKGj/ZhL0FSWv3WFG2aWSEeQS92LApYvf5WPG5hPclPlZ2MlvNe3ys+X/iYy+/28e2KTzSx17+AB/L0/g+H3v5UB+DxJxxsK1iJsr+JcgnrZ3IJrEXIzt0Fi4K0HuDy7Pzdx21vANdUJeCq5YTMAA7SBz+K8bO1FvlCMsHI1DXvwfnID4AWMVG9dVo3B2Op6fnw6wPxK87wKPYVRSX0Pvi8Vsvvf/6+MslA7/5xdRSSbGFpVe2sjI1J1/5UGAK7DKspHwFTGuFMSRVgEei6xhVXMKe0rkVuoEKLhBaoDmMC1ckwz1sZ7xfAyJ9arM59B4FDBLbZE1Sr0/g7y1351K6qbI5ailUFW7dUzinGV2dRe2DPy+jl60c4oCZopYOJ1VzhqtxY7K2tykX2UbRkAVEY+0TiikDtG3uzdkCupC4nM6e0WpUWxcc32qqSK/GlXYJhe04ctO76Q4L2oj4nJTRSYUUBaW9yaxijV0ppL9NrZRCo4yCtXJOWqVozcehtR6L1ngcWvMeNN1kKe/CjzgTrMcNb/emf6ozTLV3mt7xAuHMFkG/7G679qQb3jGXWWIzeRsy15msbWi0JUBWSHVLsuq2UxQo9BNY7SJ5LwltmNh0tkOOHFJNrFfdapWTcBWB
*/