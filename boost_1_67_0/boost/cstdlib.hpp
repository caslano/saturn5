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
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
*/