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
ygY+6hxh/nzm8lOJXpkv57FH1r+pti4kB+kDuTkPVT+yM7BofnLeVMKQ5Ub131EXzl/l2yt5W3zPmUp2h5zhzWE/MjW6+fFvVd4yWXlV0/Lev4V8J0x13wrZQ76fy3+P7U7TbNrw9DpqmqKXxl7f25kc+PXaG0V6fjrNn2/lBjZf/3t3Mrj3KIN7bzO49xODe0dP5/dS2aFM1LpCPKgN4Hx4fN1xuufaL3xEXRfxbl9onWe6xV+/bK+dbt1X+Hos98NXp5ONBu5ZclkP+Xd6ePsOpmxovubZvGGwNc8lG/rzfj4g73+IN5UH9HS246SNOAbZELR6dlT3mSc20nv/RyF9gQs2kuVULjEM1vGeAy1w2FyN+15D8Oexl/o6F0odbHn/Bk/oova/QOM1J8T3kNN7FtGn04vhVn9vvY2ZDVgs3wfXT0Z6YGPQINVuYtcnc/u7PUew+yb+8wysrwo5C+/HH7OJ//yirl5O/O+U/PvKotl31L+JWla0NsbjAPmvilWxKcehcSYbK5MdyObAgF9xe7g+64Vyc3/ny/abmu/76y/Xsz/HOXxTMwxT/jdb/Mv9fTcMf/1wU/+5mTDxRm7mj6e7Ru20Ps3XpbclrOjnwhds5jkXDj8u/Fll1JG8eH8d6ae3dxf34N5g2LT2upneWkYYWCWb62GZrplM39y97s3fPHw8N6xLNvefD+0v958L9bPjy5v71zmPuV7IoKebjRfbQh/PNKZQ2SmYEzQw3fXT123OFv7tO/N7WYY81vhjQXfCO3sLvTpgakcn3Z7UsGFYawK/OmBBB+AJHrjuOT6jdRvQ8HgLOfk4luYVIUeu78vj+/gt/fXrLw+m4wFbBrNnULzFGniFjD11/FAnNkI/Nyy0k/kx8sEt/TGnb+6P6afbd9J2g9bzt58DFmTQx1pthoWl18drHqJnUz/MWQLTbCxqz0ufOMPCIRrgynpWbtbnhR6wE/XjoRuXFfQznH0NmHxtEPS0xsGf8eN+A/ny7aPq9jWLE/w50C9mWLLrlbmu7au2svT2bzcKwdh5K2efInoqU8oDLZsvU+Lj0Vshrzz62AF5KObR/I8yn3frVsSHywOawu32xVbRlsuYralcXOsY15WXwcytw5Xl0K39406hGH0RYKDuDMB5OwIcFaNsm3AxwMcRZ1OJM33zcHCcMA7bRi8+9Jfrx4gbtglXxg+87c3lojZr5hpc9izusG2Jpydtf7nyPDfR2c8gkuzUx1DXEkGH+xXe5VnM07e157+iaS9tWR/aVo1hlA9s91gD3qDPrYF+u6091tMrV9lXcizfCS6yrr6dUxlHiznLBZM904J8p3bObNx2wnY2Bq2Dg6+eXjr9x7tU/qSDPo4fxmfbRcu/cnuVf7jP5e+4vVoXaAwIDNmPZX3JGdWxWN3I/DW8I8Djo9X5Ppus3928Pc1rSd7B1qPU+aAPtndejxq6g8iHHMQP2FSnoYfeHD/0HzBfufUO6jPWkD1izIVLAfPGpYD58VLAHDOz+Ji7LAXME5YC5j0RYvaVueN+64IrMDXXLxQ8yJffn1Ax63YUeinrGJ7f3lPfiad+g0/Ic8COtgzh2M3NZufu6GQzmrdQ34sGLNc9IWgjaN4RbQXNPQLX+Xn95wjb1itaXZfbKTq/dMPcaClgtkeIiXJ1xb2acPXej2jvq+X9d8hAzw+/uRPwI/b/oTtHZyvXvoQLJvLZeIN9h4C+nenwzUhps0N3Dkdmr/K9c2e9+Ao5JC5/viaYrb7YWX1vBjAjnEu35anZRe0X8z4q0bH5U8XHqa9LMtMYgLc7u+9iyREN7+MU3irfmS68JV9guPO+I0K5PxW8wxk/2bKM3tU=
*/