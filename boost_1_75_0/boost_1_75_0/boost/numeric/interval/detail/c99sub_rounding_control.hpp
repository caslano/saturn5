/* Boost interval/detail/c99sub_rounding_control.hpp file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_C99SUB_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_C99SUB_ROUNDING_CONTROL_HPP

#include <boost/detail/fenv.hpp>      // ISO C 99 rounding mode control

namespace boost {
namespace numeric {
namespace interval_lib {
namespace detail {

extern "C" { double rint(double); }

struct c99_rounding_control
{
  typedef int rounding_mode;

  static void set_rounding_mode(rounding_mode mode)  { fesetround(mode); }
  static void get_rounding_mode(rounding_mode &mode) { mode = fegetround(); }
  static void downward()    { set_rounding_mode(FE_DOWNWARD);   }
  static void upward()      { set_rounding_mode(FE_UPWARD);     }
  static void to_nearest()  { set_rounding_mode(FE_TONEAREST);  }
  static void toward_zero() { set_rounding_mode(FE_TOWARDZERO); }

  template<class T>
  static T to_int(const T& r) { return rint(r); }
};

} // namespace detail
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_DETAIL_C99SUB_ROUBDING_CONTROL_HPP

/* c99sub_rounding_control.hpp
cSD+aKr+iH3XdNQSvT9Svx/5byzdXZuo0123+8VO1bv4VTjdpxTDytoLqgKWcH0Rb+78RRllQdLzkG5O2WYcjdOk8KAs0Kvu5oQXsBiTJFFdV1IEUT0Ge46CcGioQBh2JSEIwpDk4EudRF3Mvu3MURePH4mRg3GBSfdYdLyuvo/LwWG+cDYKQJmzZweFWzgaKeAClxGJQZB+nvKBsJB8PA9qj2lcBmrezFMYcvGHtAnDgSWA7avJBFuaiDImGCTWJXK+CDPeeK8hf3Nj+r2Oh3koSXcMwjDiaLwHwgB9+4yV/Oe7RHCxP7Mey+1+hhzRiUfQrqWAI6BSsF/0qGv1WlCyqOrlCaSTepldq9nHEwwtwV+aNpExEfPIaTxa/n+amn2Tzjw1kV9ONzX1RszYinv+P0zNzDtPOzVDJ515ai6+58xTU3P1/5ialqmdTM01ODW5MVPjptRdL/7ecV4+mS4GP/KnuPtv6PclUmfwwQ6ZDQX9nB5oIq5U2421rqsjw/TF/eB0nR+QXoDv7IN3WFU0MnWk/go9/Rieto9Mbas+Y2TqDZ8ZkalzEtF4ocv7o5e342XT6mNGXrCSeSl4OvvlX1DrNgd6MK+Vu2OPTaVkONlxZznE27P42+QKj/lky1TjMFMqcdNt6spqHi0RF4vpAfEYHpPuC49Bq7Ynb0xioKiMyXWXjwFFb0yGOywBuaUA1XlTPSLJxDky
*/