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
SV3Q9i7seM4KfccS4WLTbismS/eQFgas8zEXIGlVdXDoyqi0W6AQd9VytSU0mD1T+iZ5LXW0u5LvjgyxrB1Q0Yoaw2FZ0C7nWHgX2jqnwtibQvRRuiqbkn+nZYfcc+A1ZgUDP4YgHsCWSCZduAqSy3CVwJW/XPqLZA3hO/AX6w7vfbC4QG4wjCqA3jeCSsxCANs1FaP5UfAfqnTHSy5hulrOwyhJo2X4ae2vcOU5DE5fwp9trYn96wAGFdvqzsOZ9/zMm+CCfkspkftUUqV7jD+kk0TE+BIW/oeZ8xh28wxbquAySSJoBL/fA2lxy7ViGdHeSAlV8ty0UIm9gYrXizCKg9j5idVZ1eYU3ujYlojlW8eEyTiuf53SUH+BkxIpUiFTHqXjQsXra9gytSPyZvTahLuYxdNlECVBuHAigl0g1spqiGCCVHSy033X28FkSY/imtSRttBXzCrUbPmbmx3KkVHuHakVsF4rUGD3cVnYOjnHrh5AUKCOkHsKt4eMozqBLiH3EJthIgUTUsHfLRV7zWpHMhQYRpGUYnIo7f/pAeLJtmm4UNKoTBtBw7Ibo40tRVCM6+jcSVXxu0PyHrzT4uU72oO5dvCYfFidt5mWOBJdCQI1VXdc3DiCowyfoYoaD2JdVoxCMtWS
*/