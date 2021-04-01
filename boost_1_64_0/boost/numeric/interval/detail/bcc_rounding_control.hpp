/* Boost interval/detail/bcc_rounding_control.hpp file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_BCC_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_BCC_ROUNDING_CONTROL_HPP

#ifndef __BORLANDC__
#  error This header is only intended for Borland C++.
#endif

#ifndef _M_IX86
#  error This header only works on x86 CPUs.
#endif

#include <float.h>      // Borland C++ rounding control

namespace boost {
namespace numeric {
namespace interval_lib {
namespace detail {

#ifndef BOOST_NUMERIC_INTERVAL_KEEP_EXCEPTIONS_FOR_BCC
extern "C" { unsigned int _RTLENTRY _fm_init(void); }

struct borland_workaround {
  borland_workaround() { _fm_init(); }
};

static borland_workaround borland_workaround_exec;
#endif // BOOST_NUMERIC_INTERVAL_KEEP_EXCEPTIONS_FOR_BCC

__inline double rint(double)
{ __emit__(0xD9); __emit__(0xFC); /* asm FRNDINT */ }

struct x86_rounding
{
  typedef unsigned int rounding_mode;
  static void get_rounding_mode(rounding_mode& mode)
  { mode = _control87(0, 0); }
  static void set_rounding_mode(const rounding_mode mode)
  { _control87(mode, 0xffff); } 
  static double to_int(const double& x) { return rint(x); }
};

} // namespace detail
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif /* BOOST_NUMERIC_INTERVAL_DETAIL_BCC_ROUNDING_CONTROL_HPP */

/* bcc_rounding_control.hpp
M2MCvNnwKcCJXdUqKtU2iqTCoyJjqawH9lHI8OmxkfjCd5fOa0BiVYdKpXTFsnKpdeVpQ8QHaGHPInBU87QZUoc9ekxoM9KyEYDA8KpHgITz13Nk/WsNkKB7bEdkBZuUNdXpwnlR+slzQPdOzWtekSFAELRE3UwOE6rLVf0k9Z9Sk+E4JrboRCQTfmvHthP+N3OEpo2GBsonGZ+eonJA49JtjjtkG/V8iV7aLEBjtDgksbvSiLNk/s6MM6QgYC6HQpU1+gwqnJrjYRyS+DX4oaPJaWa9cfNxX/iXutDf8XLsslBtfKMHU1MWFV2U9FqJRejCDICjhaqf3mRcxyyVcTtX51DcPqW6X7hWz8LhYEibuyC/1cwr2tdgOznIJGuDDX/350GiF8foJezqCC8PQDftnTlnmLWzxIxrL50ARTwCUlSI7RDofzUUay2FccyWV24WGbRkqg0TPo3E+F0SFZa2HJ8jT9JoeYPZiShwSL5D/bIKAlmk7rRFY3eFYtNbIpjiANMhFobjDRxQEi4m2tJBbrNGJ7GT7ukUtRk62/doiUVT6Y1NaKnopw==
*/