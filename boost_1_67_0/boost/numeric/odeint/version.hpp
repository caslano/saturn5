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
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
*/