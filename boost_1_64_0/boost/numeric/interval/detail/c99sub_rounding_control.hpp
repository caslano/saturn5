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
/BFAhFH4fG5vCJa2UnfmUEcA94t4DK/EbcpxBonJsKl0nLUYE76P9VViLMj9cBhT6Yrd3hw/WL4VApz3SvXbzRv670XpF6RghaFk0tjLmEhVu4MvF3xiQbKfBIvMx8lZjr70WFUCfKLBU/4zUyO+kC7bXGwvU0QB0wEV6U2XUhlFuGOPL3+9cMI64/sSFhx65GUJLwEywwEmCAUsemtUC1+qt4s0Bg/BRwWVu/D4tRcXW6nNp/xfX7SdqIPkqWzZ7Stv4QmTxd/PgHcvN1Rf7JSGQt/t7K3FUS/CKftbMoqyHYPTAtYOv/a4gfNPOLGBEUOCjlRUfoCalqFUtHgEyxJ5cCFaXZ/oKTvxb1FWN8orEQJqNpWKFQUGibbq1PQP9kVuRpO/SeJAF3NCdFx4Vk82tuC1cnv6T2jyCxUIdkvCGvZc4/opIH8EyBFGCDsOZcc1H3sXU3wTvAEp5fK+G1UsvxlU82Rp6++pmTxpa244Zom+nClFa8ZJxupMb91zfius0Wmgz/W0Xy0XB0KZ3emjBh9EKqDqG/8eEGXUmWcM/rBhDPUooT86DA==
*/