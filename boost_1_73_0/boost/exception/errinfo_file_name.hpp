//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_FEE5120A6C1211DE94E8BC9155D89593
#define BOOST_EXCEPTION_FEE5120A6C1211DE94E8BC9155D89593

#include <string>

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Usage hint:
    //FILE * f=fopen(name,mode);
    //if( !f )
    //    BOOST_THROW_EXCEPTION(
    //        file_open_error() <<
    //        errinfo_file_name(name) <<
    //        errinfo_file_open_mode(mode) );
    typedef error_info<struct errinfo_file_name_,std::string> errinfo_file_name;
    }

#endif

/* errinfo_file_name.hpp
MVrPgxqp4fnHYPtw49VA4qXvKDSd6cmqEyxAO4OvwNtx+7k3ne6AuASF+vk9JI03mfFwqA9J7St6vXyxTl9fsM8+KmH8IfAiKc3yne+3pF/v44vMO3MGdERv93px4Bwn0TnF18b+LZNeEWNhuob80mVOso7Nb5Qwejgn8QRLc+0wPS52R/0BfJ3mvIOuibW+Op5nNztazfiqTNwuYn2tF/HCzvh/11+bnJziLPHzTJA+5Fyx
*/