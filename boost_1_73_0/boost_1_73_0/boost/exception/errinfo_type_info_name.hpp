//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_0E11109E6C1311DEB7EA649255D89593
#define BOOST_EXCEPTION_0E11109E6C1311DEB7EA649255D89593

#include <string>

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Usage hint:
    //BOOST_THROW_EXCEPTION(
    //    bad_type() <<
    //    errinfo_type_info_name(typeid(x).name()) );
    typedef error_info<struct errinfo_type_info_name_,std::string> errinfo_type_info_name;
    }

#endif

/* errinfo_type_info_name.hpp
d/5zxur85/qyse8kL7B17oC5voRWcXvnK7YVrxU7f/JG7K3tA8WkD8KnwIHmtqw23XCIT7FH+IvtOXItKcDDnnpLfKkfsajjS1tq84hl8NWU/+huU2o3CN10k2K60XSDqV7ZRQ0dqa9tHTsSEBi8boM19LellN621J/o3hd97akbmD31Hm/J/dQ2DIMcU82l2xvgIt/yCkyZ2r/ijVyAleVb9lNbe+qkLXVjb8fUJuOCsvxh01kTLP52xic094Y=
*/