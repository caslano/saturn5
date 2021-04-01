//  boost/cstdlib.hpp header  ------------------------------------------------//

//  Copyright Beman Dawes 2001.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/utility/cstdlib.html for documentation.

//  Revision History
//   26 Feb 01  Initial version (Beman Dawes)

#ifndef BOOST_CSTDLIB_HPP
#define BOOST_CSTDLIB_HPP

#include <cstdlib>

namespace boost
{
   //  The intent is to propose the following for addition to namespace std
   //  in the C++ Standard Library, and to then deprecate EXIT_SUCCESS and
   //  EXIT_FAILURE.  As an implementation detail, this header defines the
   //  new constants in terms of EXIT_SUCCESS and EXIT_FAILURE.  In a new
   //  standard, the constants would be implementation-defined, although it
   //  might be worthwhile to "suggest" (which a standard is allowed to do)
   //  values of 0 and 1 respectively.

   //  Rationale for having multiple failure values: some environments may
   //  wish to distinguish between different classes of errors.
   //  Rationale for choice of values: programs often use values < 100 for
   //  their own error reporting.  Values > 255 are sometimes reserved for
   //  system detected errors.  200/201 were suggested to minimize conflict.

   const int exit_success = EXIT_SUCCESS;  // implementation-defined value
   const int exit_failure = EXIT_FAILURE;  // implementation-defined value
   const int exit_exception_failure = 200; // otherwise uncaught exception
   const int exit_test_failure = 201;      // report_error or
                                           //  report_critical_error called.
}

#endif


/* cstdlib.hpp
fYKdSi76+7gaWW+0+ADgzqg3rHuV2zEQ0xz0rVaC54CgQ5L2zJY/fllnqv97yqcU9L0zYIOLOyzH3UqtURB/VHvI2mMQP07Wd9l1MNS81nHh8KjMXKnxHISAIfNnFPQ1aNP0h22Wg5mU8bWVTa+2IVXRR0qVEGG8cSTFYtZ8SCSTLPtC5MVuOM+n5i/3UX6mFg7NEyWHdPrZ0y/yaNcGIUa93aItmvcMgiy8NOKf1MX7EJr08ETYfrr0iGLPGLrpQonmpk6NogsLIwPYwsHzDRKnx1oVYBMSujarZ3heKJ3Sq11uZnuN0dXgpaaingI3N5zWMC73NrhdHG59ESIWF6YsV68SCJD1o3IrFg8nK2fsqWoYQ82O/ISLWk+q1S7yc2s90d5j7gnxFnc71K4ALnIcqR60TBNo5X1mIOIP0yvB+xziZwhzlUh+8akbXNQT7IindnbczDjVzRX5z2/rsfswQiMD5xBvOYH1/eRYng3Yz22quecjqAfq4O+8q5g6IOy3ISHp+xGrTsz9GPc971PuAgy1JJCY1o7yjurQf9fg0lLvx/X+CaFzEw==
*/