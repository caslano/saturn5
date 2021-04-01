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
KvUQs2+6YYPq+ZVTZ8XmC0Z8F40Wp0c1VtWY4I2PrisSk6R3tBwS33/VJPdz6HdIif8wgmd+ybOW9kcBKr5dZJuF6spdno0ghxZk3dtezMMZzftMJI8gXEyeRAwa3gF5VZ0nHUnh7/ibh2/X4d14J9622666+C4cX/WquZaBEOgW+MxYlGSY6JkxKghZ4HM4wYps93rkfJYGQhV7wug4IPqhOdWtRSDcVQxF0e5ItRBRKAFCN0kJoCxuyQMOP2W5N7pA++bTTtMaVt1VULTSAN7obGh/CS7sojnA2yqdjqkaciUpYTOkbbnieiYZf9kc1ZdVvCbPWeSvsqS8ZDqFN0JUxi0rLP8xeoH0spyIukBltEd4Qr1e42TKoLrGcfCqrUeoLDkzir7zT4c5w81LfXN0qR7jIBE+Hu4WBYQzmxhgASK88FjyA+EJQxAmGDBPbcgSPUjbEKKi9ukPEx3odlx+H5J7T+q1gy4esjSzkUzUyn/3/zhizesNuEt38xmv1+/CeN70GN4YMqJHIcUCrej+8NHYKmSzS5E4eNG9iVSZKGQw5qQLdWPDug==
*/