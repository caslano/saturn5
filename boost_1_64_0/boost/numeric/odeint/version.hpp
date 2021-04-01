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
7u4jM1UCoSUUdXYGCf+iwT1mRovAuGZ7knH/sMxVJ2vq4zaYY5d+9OavaKdHHgk4qYHlQQCCA45RNWxFhnjT/bfHDSZOgJdMHh1aicZilHft71nOdNq4LGdW7l4xVbE8xlioBtg6bTmBQmqXatDKp4uIZ30YC2lT2W6asI+BykDpGU0ZCTNBlAVSnaVSUKwjyatfKIjzTbWxnEYsDwbbGfNGQW63yaQXzVuU6B1q55wD1WHR5fbSGaKZNFbe0u5VKrbUrECz0e01h7yzE5uhEFNwvsmwKJyqG0+oBVavZ9PeX7DMOZpdzVEbQO3qJE9XO1yV08JpgUkuhdukw5LyQvWZSO9Ljhnf24mDB71feLeW0cgbFSbVj26/QZqO+ayD7czFLAtvOj2msaI0O+w/A33hCGScERo0cJ9y4dNlXJxXnQjiqWgYQNcO9+vjCeUy4yMClcgxksegMEhRUOBp76e8325yAJ5o0Gg6mABuQtfunWg5gUgA9J71S8fFtw9saLcLYXJvEiyrqxSRMqm9DbQAipfclLnwMvoBGJsvUkqc+Etz5CFh1SYMeA==
*/