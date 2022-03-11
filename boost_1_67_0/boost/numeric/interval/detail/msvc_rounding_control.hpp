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