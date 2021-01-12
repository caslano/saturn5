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
kT71VdEvpPwF4SOJfVwSvjfh0Tst+8nZP6+sX+FH2jxS7fnC34K1f1N9f+Ft4c+6eHa9MPtpfxD+uIsfd1G5f+97l8wfLr7Z4vZvJeHHs/c7fC2Mu63vhsrL5e0RfpWLf+5iOLffrBF+iYuvEm7Yv60TfoGLvyTc0T9fD6Olin2yo/23I4TXq9we/2H7+ccIX+RwZ/w7z58v/DiHV47/gvA6tr4S/om1Ph726fztYfPA3WH8
*/