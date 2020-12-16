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
rMbeNIFvap90kIfLLG2dY/H+s9WMjartY4/tzA7qPT9aLFbcsfeJtI5862sJp/N4U2o8a7n3bOqvgK7QHdbI0jz8VQK5iRFO9n1H6lNEzpLepSYMCalllc2OiDnBHBGs0FRQ1OIRkr47IOi7h3sbjkSs+ttQ5ON2UlM+ZlOiXCIRc2P9ucesSbMsp7B/utws6wt9FMoKLzRzNBQ5Opg5HPrllOMxM0eSyBFn5rBVjo7ILgDr7+jVxEL9m82L9pw4Oij6aFm8FZEOfcfP1WbGkl7EGJxLGYJJ1JGPkCgI6y6R/9Ov9ftJ/RdIC1m/Y9oC6Hfkb4jqd4xZwBodL+LcHW9XvMNvj287OSEYKw+VR71dvjOkgBt6t7IY12IB8em7P6H9IOEDigaGSI/kgzEGqPALHf8Bt3eN5Hflc1ZxxHri+ngD+uBbU/RKR1K4AFMfVm6KXMlNUVVvIRaZY5E3+BBTnKQ/trbaMF6nRUCi8oT21DZurCIae4ZsbFfZ2K78QvIE0sKjxrJ49Vswu1qZWdapSlYh7+axO/CNMXZP96Kx2yza8s7H3JZ7e9U1cGgItS6dBgxS7/r4l5MzVShqy/wcyDjIR9v7pRLsRWRskK+33C50Qmk+9H5vG10czG592dGvmCW0JT/8HVr9bU9j+OJEkz/uGW0y0LUqLGE2cBTkZMY0eeflmv1xLHAqkfwsRD4UlZ/GpDaP5Gdz7lDDOY4F14Dqnm4NtVY5VXzoW1s58PSihlh4u5IWCZ+fy2MJFR0P9zA63mA9d/yzHlG4oa/JWJyB8Zae0miL1YLHQPoPsf9o3b66FjBu5O/1e1ZVR04VsGLPJ7jRT2+tNvUv9kt1gx46HTpSq0egXet6yKuPWHZ4m1gkt+rjPpLtkhNurpTD3Y0eN1/HPda7mz2mqeZO01RzJzoAeKKFnEJPjnPesmJLrfOWVZeI85b3/sJQZZjBHO4u+pXFi/8m0a84/clVJz45Kd9oqjLa90rRyi8/O6mlD5NstD/hjaxW1GxBNIsBXbaGB/SJrLqWO5pIBREKiuR3ZlQJYoWUUgqLQcMzcio5Vf2UWuN769c1xxdiahqJ0hpD+1yWGFoPD+3NBl7tvfLEQztmgzm0f939q4dWtr/RLb9tZREnisfq/31lDPXlyIJxNtHq9at5nLtw9EpeqFOd9TosFfyuW5RMa6nTYro33rhlGl4XMTzTf0tawxv0C1aYlgzQ+6D/amRY15PPh5yKr7+stb/NKK6xvzVDRVT1xbx0bzXm4Z3lVG/MsNJ1Am3raOgGrBwcsOmz8EEY7uNtwvIDmxvB5Ro9CXz9r5wfoMnmgghxGt2xRvLTmLI4cf4tX0TzC/36k/gvf118wHfMboYEgofowMViiM7iIcoOqV9hiJrqD0PeUNNBObOXd7xujq/zWF/i5YmohOAF40SbEe9U5+EFUWJz0hrzlnRmEDGh+PxgYkxO3wYujwH1V7ghl/4/Pzfhj7TgHbKPh3g5XoQO/obA77VyE/zIK8c55JrV3IHw2aaL2OgmEur3gj4zJi/JYxKWVddrG62FP877vOZ+o2cdEFvNrahxJGoUWwxBZHvaZ4ydR7eU133sbTS6KWX6HM1COVehHFZtg40CNoD+eGXfsfpVB2oWcspQK8Z3xGc1xvf1TDG+n/D4djfG94pldSxvtT7lJ9Qs/0pZ/i4u/xKj/N1L6yi/8ynOx9Obj0UicD+gZ71XA5+v7iYasJUbMMHAI7ctrWs0aerS6f6wbjGtHni7OKi/Rc/CR+EmgHyaG4lOOgt0UqRX/1pVBAn/m2SnSmgIE/QHsJpJMSafPHxy437+jWjce9yjsaJHij7nQ3NIT6w=
*/