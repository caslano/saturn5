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
Sh8Nz9trouVl++9Re9gDhxBqCohgy6tgt5kJLQIhhZnbg2uH8THNpLl2qtWq80iQd9xtniw9tMra4Lwdr7ltqBlPchYuNV/7tvLMJye9c69wAe+tTz/4f9Ee+h1MbvEm3bbvw3v3YMEFUIZEGf5x0SfwN8QCwySnCPkgm0zmME0F4haxceA28MjkxUMzo4yyAGDKpj7MSxXbiORmD+VMEoUllINjTENT6HpRmF8x0P8i1BjsBBtX5cewb4eUnyU44taYeln8P7iN/wy8iVQBlTshdSeZxtbKn8bTdsc6WPzyZ/06XPq1gapiRE1TNDjA5vA104gY26lgjNCaYVfH7oTM+27j4LccY5292EqA/UbjF9BZygupRVaXOMMOLxaA1DTmcIuT6DEy3f9DccMiFCQkOm/bJCz6dsUpF20djrRhQrnR59JyR8HejIMXt4PKTAlWhXtbp4kZo1EiDOGRLlvGOPm0tfITrggGRyQ0PsE3B0iiCN5uNJCNs5f03adrdncVPlVyP9WZl9zFlLCSfZKPkcGwc9EctVez7s39dlHfqqXvFG900yda6O9rCxd0lzjz+5c++m91kGa3u9Kc2wpluwZwzJzGxHLbhd33OdyDVN3wZCXuGRdWQbcGVxYWxLhb0Amv4BbSs4Fx
*/