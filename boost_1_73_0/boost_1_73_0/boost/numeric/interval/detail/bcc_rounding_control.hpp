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
GdXMhc26yVYshuHOR4pffAfHE/2v4uKkAzF8UJTt5QLrx9pccnvf/RpJQIbpu8klfFOcRbZzilLHPKQU3DIAUhTpaymP0jQ/IC9V4VK4IOY6KBsiHXUqeMm3hs51EQyNKLEdHRyK4RHAXG2ApCAUo2Shq/S2I+NE4X6VvaGAW11ysinqU4t51KxJROk/o0aJe9AUdipvmeYlY52+gJ9kNVb3lIkxGfWVKjyP4i0nhcPBiKucPHo0WNhPFnSEScRpDiVOmRMkpvm4pYZkXOZE5bkKjdTHH6EhhMRYjauRjHVSQ6llR22ilXLG7Nt1YhtF5wnHqxrJo43WorFNYrzGXc4PPmIzRmfRgCZJmxzLYW9abg54u94coFQj2qeWnAP84ZGrSvM5uxkQAOR9ZqrZNjWDIwIxptI/n8XbSo0/WYpH2tMCtyR14Pa2VHquNm4S/14KU3QU39KUnwQ/wtttFXyq5vAfFsXHjOPPhh+5T/3LNbyK+DKPdCmeNz/COw+HbTwhGQo7TEpiVKG43ZF/prIUgWRkxbaelGK3gWxVubK4hHrSBfUTRgoNMhnGgCvv+aezfvqIvKOGz2MuWTv7eZbs/T7e25edL+Qx8h88WSTUKEiomiaULim+Hs4Eyv/ButRlbAzD78UpGdbg
*/