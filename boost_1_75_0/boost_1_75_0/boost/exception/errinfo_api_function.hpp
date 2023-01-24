//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_DDFBB4546C1211DEA4659E9055D89593
#define BOOST_EXCEPTION_DDFBB4546C1211DEA4659E9055D89593

#include <boost/exception/error_info.hpp>

namespace
boost
    {
    //Usage hint:
    //if( api_function(....)!=0 )
    //    BOOST_THROW_EXCEPTION(
    //        failure() <<
    //        errinfo_api_function("api_function") );
    typedef error_info<struct errinfo_api_function_,char const *> errinfo_api_function;
    }

#endif

/* errinfo_api_function.hpp
8h1xafY8ipTwZW6yAO51oHtP8r2ZcK8J3XvodlkbIAFjTMkOXb3GZofO9n+WlXI8w/9Vhn8bJcms2FE00ecP02Sgqr/jKSrOIlev6ohwVQi5mq3ZoqGAJ5Gr5gJXkqEyIFCHWFz+bLH16w5LE2xvaYLtIPoLunsPtptgpXOjqCGRJ6kRw3UvS95Z/yow59W+xvj6K69Kvj79HuLrWwcwX38cX/14gMbXvxlk8fV36js4zLahfN0rvmF+1lbx9dRBDfN1SatKJug8vekgu3OjqHFb9KwYqr5QgoZoCM0UuDD5NkSn2xhNxotL89tfEE1G3xYSi0x4UlCj48nRbP8mGYX8jmFI+oJVz5PJykxrv5AfJmUsa4o630ieoZAXvaDBZ7iWfqpm1k4sUc8it7dsdZjWXtA/0XQ55SNosTwIv11W56/+0Zkfsz5f83fBLj6aKQO2dSDMbEpAyFNAoO32cR4B4Jb8hvZG0aoQHw1NeLtDTVhXDe49GW/z0bx3tj2x4J/uidTMBvdEE+jM3SXzf7AnUs69J959GRD7zUGN7YnZL8s9MfFu2hPL+/OeKMFXX+uv7YmtA6098VH9PQHanX1P9HoZ4r/i1J5IHHiOPTFJ3xPHB/zjPfGAM3RPEDr89yb2/0/A7eHNp8tMcWmu/Qm3R+oEkjsBV+Ix242uXg74yFIvvZTuGQYrFczTYaSIpKpwdsp7+KqmVB7i
*/