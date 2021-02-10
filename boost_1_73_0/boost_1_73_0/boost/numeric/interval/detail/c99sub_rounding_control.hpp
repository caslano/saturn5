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
2IdHL+L/CV549xoXWv3FYvt1aULuoPpDrRu8P+akDVuVO9KEx1XuIPQqpPZy7NaEPOboxnFzP22neUPcEhFUc5onqlhpPs8shCdNeP3mzW/wExx0DjoRnFLJmYBLy+SM6XkEx4lH/sjo7W3LsLcRMAtUtGpTk4wbMCq1S6oZ4FrwmEnDEqAGEmZizWf4wCXYjEHKBYOT0cV1f3gWwTLjceaMrFQJJlOlSCCjCwaaxYwvKhsF1RZUiupoPOHGosHSciVb6JuBZTo3zoZzT4VRQBeUCzpDR9RCZm1hDtvtuNQC2bcTFZt2vA6/ldl8E8k1ksjpClRhwSooDYvASUaQq4Sn7o4JQbAoZ4KbLNqyQVcyaSsNhgnhbKEeZ6aizeCyTk/kxKBAxty6m1HSOFfLTOU7gphHZyUttURHmAcUShSmOYJSJkx7YR/52kWdU5/gb5ZmyzcBJZEMNLqX0L9swIwabiKY9icfRlcTmHbH4+5wcg2j99AdXjtjH/vDUyw9R2ca2G2hmUHnGnheCM6S2uf3u9rBHpexKBMGDcsMlqoRPIBwFwgHb1EMVAoktovmLE/YrJxXJhKWcslg0ruckA/d4RmZ9M97LuhfOxjm606ns5GZdj/2ri7I8Ooc8SDgEjcG+g3jjGrYvxoP
*/