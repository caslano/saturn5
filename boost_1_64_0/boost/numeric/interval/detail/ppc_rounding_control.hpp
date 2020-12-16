/* Boost interval/detail/ppc_rounding_control.hpp file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 * Copyright 2005 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_PPC_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_PPC_ROUNDING_CONTROL_HPP

#if !defined(powerpc) && !defined(__powerpc__) && !defined(__ppc__)
#error This header only works on PPC CPUs.
#endif

#if defined(__GNUC__ ) || (__IBMCPP__ >= 700)

namespace boost {
namespace numeric {
namespace interval_lib {
namespace detail {

typedef union {
   ::boost::long_long_type imode;
  double dmode;
} rounding_mode_struct;

static const rounding_mode_struct mode_upward      = { 0xFFF8000000000002LL };
static const rounding_mode_struct mode_downward    = { 0xFFF8000000000003LL };
static const rounding_mode_struct mode_to_nearest  = { 0xFFF8000000000000LL };
static const rounding_mode_struct mode_toward_zero = { 0xFFF8000000000001LL };

struct ppc_rounding_control
{
  typedef double rounding_mode;

  static void set_rounding_mode(const rounding_mode mode)
  { __asm__ __volatile__ ("mtfsf 255,%0" : : "f"(mode)); }

  static void get_rounding_mode(rounding_mode& mode)
  { __asm__ __volatile__ ("mffs %0" : "=f"(mode)); }

  static void downward()    { set_rounding_mode(mode_downward.dmode);    }
  static void upward()      { set_rounding_mode(mode_upward.dmode);      }
  static void to_nearest()  { set_rounding_mode(mode_to_nearest.dmode);  }
  static void toward_zero() { set_rounding_mode(mode_toward_zero.dmode); }
};

} // namespace detail

// Do not declare the following C99 symbols if <math.h> provides them.
// Otherwise, conflicts may occur, due to differences between prototypes.
#if !defined(_ISOC99_SOURCE) && !defined(__USE_ISOC99)
extern "C" {
  float rintf(float);
  double rint(double);
}
#endif

template<>
struct rounding_control<float>:
  detail::ppc_rounding_control
{
  static float force_rounding(const float r)
  {
    float tmp;
    __asm__ __volatile__ ("frsp %0, %1" : "=f" (tmp) : "f" (r));
    return tmp;
  }
  static float to_int(const float& x) { return rintf(x); }
};

template<>
struct rounding_control<double>:
  detail::ppc_rounding_control
{
  static const double & force_rounding(const double& r) { return r; }
  static double to_int(const double& r) { return rint(r); }
};

template<>
struct rounding_control<long double>:
  detail::ppc_rounding_control
{
  static const long double & force_rounding(const long double& r) { return r; }
  static long double to_int(const long double& r) { return rint(r); }
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#undef BOOST_NUMERIC_INTERVAL_NO_HARDWARE
#endif

#endif /* BOOST_NUMERIC_INTERVAL_DETAIL_PPC_ROUNDING_CONTROL_HPP */

/* ppc_rounding_control.hpp
/buPNIbyeJad7fNU984Lnjvsytv7cHkfTrypzki+ZF/wd/dV/vxVr8veVEveW3a1ePvvi9J5T+7Hu7q8j8nwPUwVu4lzbkeVlpcneHvbc4fdBF+vZ1gRI/TePeY5f7ib6m/Iozri3B5+LcvY9nXwITm4znw/7Y27kZ74zed7m7TNX4PIPvS83l/MhxT+1E97ZzcbKxrZV95dyEx+odia+tzkL7JMVX9Uv3UAbHr3BN/budnuTmOB8Nqqjt3N3w1tr+dctruFE008fVnamcUNpQ5SWYFWjSE0n819HbIgcw/bNv5xjvFl9dP5WaTJe/B45yk36m0w2ZMku2Nfgr9/i/crEBtc+xaQRe89XOfuwWMDr5tUho7l3LyCd3t+IfK4zZ/aAzpF1Eb/voclSzRyr7Mn8CPw18Y9w5s3PXNP/3XQoLz/b3wf39N8r4TAAd3MEOeyo9Lvrlg0e8fHz7LHU9E867a/E/+Q10kXz/K3e9h9q4c1MAvR6ccB/ImWx2vkEw3onZ9vqtvLc6829GXfptDYnwQbEuZ+e5GcrIzDfY/oqXup7xEN19YP7qUfO9Q26Nu9eJ/Jfua78HeVjts7b54S/hteLJm1t4Wv980s2e9gfRGzPY99Zc4ynLR3tPXn/oj5f6vBX/edREuG6O05qdlHxaRf4ObKk+/3UPXZfR+bX2Hff1O/U9LMYsKx+0T/Pu/bBtqC6k4/xTf1PW/ez5XDx+kbKHzf4of7ZGWukXENWJA1vPo4fF/bXnoxSB23zdg33D5M57565ReU/5Wa/JOlwTFe1cDIxjj9sZXERExzxRU+tMJ+Wf8BPnzI/X2r3Ben7+f9rQhON9/g3ov3c8DcL0e3zP7uMjV45DV75F3okfe8R96/yMPfPJ/yJs92/9YEf8YxNZu+VaHguNej82a7y/T0bH9b/zk7R1vfSHXDK9bQ+xoOauTjY3c5zmqkPD5/xf2Q72shuicaZRz00NHt+m+N4Y0D1j1AnZfi3zqiOQ4qO9Q7x5h9hNzPs/8B4E3lzO5HvkJDc4Hq+5+AT3vkFx9A+ODlHHeRj/v5HkLCVPEI48EDyD8J64jtuX50L+NBMYns8b3U9+wVzd/PAzzSbdyBqizEk8nkLcvuB/JnnlR83t66zqkT5kwm3/EHkv9SGdwj21zwpO/6A49omM9xGXg9gyzUFgi8Ow4M9k1TiSlk+fhAek8T+StkYTY398ERTVROrN7x98E418EvBuvXw62bzOeHLZxME/Ux2PqsLANbv0Fm36Xg+zH4fpTLpYwUdwiTbO3y/Ij5syOWDq82CRxlrZsw1W9hAt/snSTQaYCeQw5SdSQZQUdzomr/h9YfgM/9nOrFZgfZ+Pr9SNAKjM6D7DKmeoi84HskryFZ1H466Ub8ekkH/r5G9zr95kGcJ62xUF2mfoLSP1s5btbHFv3rOM0vE4byng/mDyQn9wvBX/WNnrjbnJ7zt4j6yvzbYBmHaN/YdfHcd4nUWPCmgi/7vy5yeOKDP8nA30dH+Cr2ynPUtlXgS12LI8PmnjIIXPCk+g4+jt+t4O04xe/OObzt89LJXB/YwFGfq+ZYMvrr9MIQf11Ax+d8BM/XFJ3kOi7uc9QLGP7+yvXi3yRXdStJOOgV4F2LkJXa8I0S1IZ7lQ3qRDjl05rwL5+7Yua2dJHDUYZLEsHwTbHd6tzLRcIHttf3eiCfU92gPj746tUTXj+WSfL6YfMLxmtKHq/w37M0N+k/LxLmN1zOS/L5OvyWu84Jov7o6eaE86yCo86H/JPUG5ezMTmN56elgtPOK4D2ogJony+A9m/QTpwL2ZEuR3oDaZXmWGyH5nybHtMc3tzgvc36azE8Hnw=
*/