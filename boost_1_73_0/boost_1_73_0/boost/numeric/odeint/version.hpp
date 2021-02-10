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
m8aTTzBiE+/Jbj15S6VTPeKdPdrYVK/4EwHB4rZc5tplvYM1UGXSgS3IqTxnWTinlQtmK5pX4enxNtrCYu35w1njWNUus5sbGxFHlrIqCwNFiAM2pRZh7lFpUlXIZvG8VlHFVAJ8LzQHe1OyBsZQezin8bxNy9hp16OP48W7yw8L+jiczYbTxSe6/JWG008s7Lfx9A2g11BWkPqyLZSD8oL0ZptrlVY6/7/XoDUQJ+ZKNSCuob1c9hO7ETzDm3auVG7w/fc/PDv22yvnKYmdoiRTyZVDkJXYzoeiTZl7HRVqY69VlAGVXHW62G4SlQc2ub1JssIaWzp6M52Dks7m18CMdrDClp6WuU2utFmzZMR3a53TYF2f6HJ5rXEuB2W0Z2nW5HuxyAXOKwhqJFLyYTZheOLEl3GOnctS5170cFgHLYSCPqonULLTec4qmTQxSBQTBOxprYwq2FK/A0tUYk3qaGUDT8RLJCyFwDC1iBMrtzv+2Cn2m9ZMQ85O56GDFAgBS1y53drCs8r5+O1wMrsgrzf8s5LOsow1T31WqDgFr5qo1O5B79iDvcqZJx4J5r3wF7m5KZOMliqJkWocRMPCArOB3TZ2ToGTsM9IvMRhqQK5Nes+B+abVK20UbQYzRfRu+H0bbQYX4yY
*/