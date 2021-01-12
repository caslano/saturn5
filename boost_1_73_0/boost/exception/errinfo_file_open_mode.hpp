//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_056F1F266C1311DE8E74299255D89593
#define BOOST_EXCEPTION_056F1F266C1311DE8E74299255D89593

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
    typedef error_info<struct errinfo_file_open_mode_,std::string> errinfo_file_open_mode;
    }

#endif

/* errinfo_file_open_mode.hpp
zwx4ytPE41993GufOrODdpg+FLtXyDPuH9E/p2o9+E7S93jgKZ75DwViKCeTTqN7erHk/25nKjUiTe93TPw9GbjFWczo5GHfmkBPfdb5nNX93GvdcF1Zfsx3dvmSfaF7lZjxRyeJc6rRB5cj9w6YsW2emPv6kpwU0oUbY3eqbzZ3fNk51cw5ouS+TwcwS5/aUMLe4pkLlBfRunJK8vNCcy/xk+Ckqp+/iHm/P8N5w0mmHC3j
*/