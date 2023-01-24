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
dZwCz1+h2YiW5On3ANcFlOVCHzJ/TmrAmvaKHXw7jb7FVbgJVmGkF9way2/piZdWa/ad95tNkZc+JEfVs/DGVfQGH7RyVt/0COAuakukHdedToPSDKfT5XhJOeqE5wIVM/Xvx01Cyiz2Rcu/pppEYIqHtfIsLBhr2MSpY+4UFGS5cvjKkgUw/SN8yhXXoNTgR2Z3qGuOifcGOFr87HfQa5AYKOMb1t7FLAFkLXtD1amhUz1n7v+QS8jPNPunQoFaykGAUdvWSKOGsPJRo9x2sgUaDXxjxSGrNDq+Uu/43RKQS48GVxunV12URW+HB+1OH7vOAy8/JlbPvKujb8H0+sLX8XfV2+GFpmkYAOmoU8cZa20cbRf3OZPCfOxhrmLsLbkeFk0mfNCEKQ/bxdbwyoe00fTCcp4g7NSNut/IRee7/GCkqT72Pdh339EubNifDVZjBvyXS978a2ivVlTOGTyMW/md7za9SrtNx2J2m+rVhXfpu00jbHInZv6yVhM38wN8tylq5qeRwYtm/vUz+eIawS182h9TZqSiF9chld9AqWjwH77bROlcpLhd2bQHuKHf4s1siVhkdoz2RW818yK4w4pJLg1+kEdPhz2YsDvYHx+5EujRJfGPUtSPCpEfN/1MtqwH5PQX5OIxP8gVTNy8UJ+Fd5o+JJm4m55W3YettEIrlPD9W/3+h/fR8f+gSRlhxrwhn5CXgYx5
*/