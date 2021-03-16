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
JCDs73pZFnKcB5J6VRlKajxDioecXooHnIUU9xdSjBO5DfEfL8OIfyaJdwgSvwKfuK6d8DlIfMc2+B4JTmK8yqOX3HPYLAlrk7CkhP1Rwj6QMB0rsnAB5x/HtFy4j+ERYTN0XEDs+ol/mBfyv2X6+nVrsgWmvqYgWEzMmJ/BjUGS3DcZT0fukmsLWL4gNw4F5J4viEvULdG0Rbx2MF7PGShgwwQVy5lKRbzKo1fPc9iNErZZwrZI2I+h2HimpRg=
*/