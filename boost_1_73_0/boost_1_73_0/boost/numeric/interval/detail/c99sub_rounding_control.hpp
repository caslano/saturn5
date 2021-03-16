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
wxyNjovvm5DlOs2zHo/unTCEZqyOshfODT3sCFz9rqKdYlMTozPO3TvlkSs3zV93rFGjv58XsBq/OxCeiVz87a03fyDznviUjDOGaFcg83kBnwf+fmZBuPcriPnBcWHejxo4/mVw3FeBK88CyBnm6c37rF/ws91ZPusbuHbeN3+f34btK3z170Le8WyZf38XuPb5CJ7OvHV6uLpmp++D5/zhujV7a706zmh/cNyB4LgA47zfcXj6KF8w87yeTq4=
*/