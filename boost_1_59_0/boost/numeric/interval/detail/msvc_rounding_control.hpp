/* Boost interval/detail/msvc_rounding_control.hpp file
 *
 * Copyright 2000 Maarten Keijzer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_MSVC_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_MSVC_ROUNDING_CONTROL_HPP

#ifndef _MSC_VER
#  error This header is only intended for MSVC, but might work for Borland as well
#endif

#include <float.h>      // MSVC rounding control

// Although the function is called _control87, it seems to work for
// other FPUs too, so it does not have to be changed to _controlfp.

namespace boost {
namespace numeric {
namespace interval_lib {
namespace detail {

#if BOOST_MSVC < 1400 || defined(_WIN64)
extern "C" { double rint(double); }
#else
inline double rint(double x)
{
_asm FLD [x] ;
_asm FRNDINT ;
//_asm RET ;
}
#endif

struct x86_rounding
{
  static unsigned int hard2msvc(unsigned short m) {
    unsigned int n = 0;
    if (m & 0x01) n |= _EM_INVALID;
    if (m & 0x02) n |= _EM_DENORMAL;
    if (m & 0x04) n |= _EM_ZERODIVIDE;
    if (m & 0x08) n |= _EM_OVERFLOW;
    if (m & 0x10) n |= _EM_UNDERFLOW;
    if (m & 0x20) n |= _EM_INEXACT;
    switch (m & 0x300) {
    case 0x000: n |= _PC_24; break;
    case 0x200: n |= _PC_53; break;
    case 0x300: n |= _PC_64; break;
    }
    switch (m & 0xC00) {
    case 0x000: n |= _RC_NEAR; break;
    case 0x400: n |= _RC_DOWN; break;
    case 0x800: n |= _RC_UP;   break;
    case 0xC00: n |= _RC_CHOP; break;
    }
    if (m & 0x1000) n |= _IC_AFFINE; // only useful on 287
    return n;
  }

  static unsigned short msvc2hard(unsigned int n) {
    unsigned short m = 0;
    if (n & _EM_INVALID)    m |= 0x01;
    if (n & _EM_DENORMAL)   m |= 0x02;
    if (n & _EM_ZERODIVIDE) m |= 0x04;
    if (n & _EM_OVERFLOW)   m |= 0x08;
    if (n & _EM_UNDERFLOW)  m |= 0x10;
    if (n & _EM_INEXACT)    m |= 0x20;
    switch (n & _MCW_RC) {
    case _RC_NEAR: m |= 0x000; break;
    case _RC_DOWN: m |= 0x400; break;
    case _RC_UP:   m |= 0x800; break;
    case _RC_CHOP: m |= 0xC00; break;
    }
    switch (n & _MCW_PC) {
    case _PC_24: m |= 0x000; break;
    case _PC_53: m |= 0x200; break;
    case _PC_64: m |= 0x300; break;
    }
    if ((n & _MCW_IC) == _IC_AFFINE) m |= 0x1000;
    return m;
  }

  typedef unsigned short rounding_mode;
  static void get_rounding_mode(rounding_mode& mode)
  { mode = msvc2hard(_control87(0, 0)); }
  static void set_rounding_mode(const rounding_mode mode)
  {
    _control87(hard2msvc(mode),
      _MCW_EM | _MCW_RC
#if !defined(_M_AMD64) && !defined(_M_ARM) && !defined(_M_ARM64)
      // x64 ignores _MCW_PC and _MCW_IC, and the Debug CRT library actually
      // asserts when these are passed to _control87.
      // MSDN says on '_control87' that changing precision (_MCW_PC) or
      // infinity (_MCW_IC) handling is not supported on the ARM and x64
      // architectures and that _control87 raises an assertion
      // and the invalid parameter handler is invoked.
      | _MCW_PC | _MCW_IC
#endif
    );
  }
  static double to_int(const double& x) { return rint(x); }
};

} // namespace detail
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif /* BOOST_NUMERIC_INTERVAL_DETAIL_MSVC_ROUNDING_CONTROL_HPP */

/* msvc_rounding_control.hpp
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
*/