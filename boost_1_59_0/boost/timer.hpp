//  boost timer.hpp header file  ---------------------------------------------//

//  Copyright Beman Dawes 1994-99.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/timer for documentation.

//  Revision History
//  01 Apr 01  Modified to use new <boost/limits.hpp> header. (JMaddock)
//  12 Jan 01  Change to inline implementation to allow use without library
//             builds. See docs for more rationale. (Beman Dawes) 
//  25 Sep 99  elapsed_max() and elapsed_min() added (John Maddock)
//  16 Jul 99  Second beta
//   6 Jul 99  Initial boost version

#ifndef BOOST_TIMER_HPP
#define BOOST_TIMER_HPP

#include <boost/config/header_deprecated.hpp>
BOOST_HEADER_DEPRECATED( "the facilities in <boost/timer/timer.hpp>" )

#include <boost/config.hpp>
#include <ctime>
#include <boost/limits.hpp>

# ifdef BOOST_NO_STDC_NAMESPACE
    namespace std { using ::clock_t; using ::clock; }
# endif


namespace boost {

//  timer  -------------------------------------------------------------------//

//  A timer object measures elapsed time.

//  It is recommended that implementations measure wall clock rather than CPU
//  time since the intended use is performance measurement on systems where
//  total elapsed time is more important than just process or CPU time.

//  Warnings: The maximum measurable elapsed time may well be only 596.5+ hours
//  due to implementation limitations.  The accuracy of timings depends on the
//  accuracy of timing information provided by the underlying platform, and
//  this varies a great deal from platform to platform.

class timer
{
 public:
         timer() { _start_time = std::clock(); } // postcondition: elapsed()==0
//         timer( const timer& src );      // post: elapsed()==src.elapsed()
//        ~timer(){}
//  timer& operator=( const timer& src );  // post: elapsed()==src.elapsed()
  void   restart() { _start_time = std::clock(); } // post: elapsed()==0
  double elapsed() const                  // return elapsed time in seconds
    { return  double(std::clock() - _start_time) / CLOCKS_PER_SEC; }

  double elapsed_max() const   // return estimated maximum value for elapsed()
  // Portability warning: elapsed_max() may return too high a value on systems
  // where std::clock_t overflows or resets at surprising values.
  {
    return (double((std::numeric_limits<std::clock_t>::max)())
       - double(_start_time)) / double(CLOCKS_PER_SEC); 
  }

  double elapsed_min() const            // return minimum value for elapsed()
   { return double(1)/double(CLOCKS_PER_SEC); }

 private:
  std::clock_t _start_time;
}; // timer

} // namespace boost

#endif  // BOOST_TIMER_HPP

/* timer.hpp
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
*/