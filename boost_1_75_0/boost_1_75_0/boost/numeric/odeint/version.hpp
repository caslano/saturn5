/*
 [auto_generated]
 boost/numeric/odeint/version.hpp

 [begin_description]
 Defines the current version of odeint.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_VERSION_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_VERSION_HPP_INCLUDED

#include <string>
#include <sstream>


#define ODEINT_MAJOR_VERSION 2
#define ODEINT_MINOR_VERSION 2
#define ODEINT_PATCH_LEVEL 0
#define ODEINT_VERSION ( ODEINT_MAJOR_VERSION * 100000 + ODEINT_MINOR_VERSION * 100 + ODEINT_PATCH_LEVEL )


namespace boost {
namespace numeric {
namespace odeint {

namespace version {

const int major = ODEINT_MAJOR_VERSION ;
const int minor = ODEINT_MINOR_VERSION ;
const int patch_level = ODEINT_PATCH_LEVEL ;

}

inline std::string get_version_string( void )
{
    std::ostringstream str;
    str << "v" << version::major << "." << version::minor;
    if( version::patch_level != 0 ) str << "_" << version::patch_level;
    return str.str();
}


}
}
}

#endif // BOOST_NUMERIC_ODEINT_VERSION_HPP_INCLUDED

/* version.hpp
0SVJu0qaPR/e5QmARWKs4kQ+Uq1/Fn5nPlKIkcjvXiQczIsPr+es4aducWKTglBVWUjPj7JSLbyldEvnUnT8NpSiQ2pm833aqBTduQ3XANNXr3Ey38c+o+wHKAJTDQnY/5k4CVjjIjuVx21QcwO3dRCCvf5MyCEe3KPM9364z4DHMMdET5VwK/BUV0P+zODpMh0t8Op6ZVSaXxm+XlloZns0e3GuEY+c62an3KzFyxKz3M4ZrTYFU9tKG/DAj4eHfVAKtoHTaAsklYdx1OYKKs5Tk67hLEOW1pP0IDaGdck1+/VXCe8E+Tun5V9lK0NSKif9z501jlKfafZ3rwTODj/JSuNMTjxZiU8wHxPcm7TRrMdP3Iu3fVmTctqUAvNKx+aczZRJ31KDQQYgku5fMjyhQk1saXCV1gR6Ukog+m7jQDMRXAZlvKFbydCUFKpO0Cup20qPngLLwT5hoJnWfHbTwVPoVZ9swoN/0HZupBvZv25GtaXpxFs3bIQbfZS17JYnufbCxf6tQDOz5DjTndfhXJRu6JfREoJoI19vNeYQhpJ2Ceq4KUzTodmlgXxg85Dlydu4bwhzjPBAL/vtAlGXGDMSboMG0mC6nPOzchdhN9tu5eIoA+xFFOegr8mpbtsHid2wDvnvZhGbErgHKZM2iitYYSvuNJjzxPRnqF1A9QUb8y2ug/BSpsev0H0FQjmRcVTcy/RdBZG/
*/