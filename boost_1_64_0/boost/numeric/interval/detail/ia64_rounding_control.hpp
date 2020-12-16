/* Boost interval/detail/ia64_rounding_control.hpp file
 *
 * Copyright 2006-2007 Boris Gubenko
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_IA64_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_IA64_ROUNDING_CONTROL_HPP

#if !defined(ia64) && !defined(__ia64) && !defined(__ia64__)
#error This header only works on ia64 CPUs.
#endif

#if defined(__hpux)

#   include <fenv.h>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace detail {


    struct ia64_rounding_control
    {
    typedef unsigned int rounding_mode;

    static void set_rounding_mode(const rounding_mode& mode)  { 
fesetround(mode); }
    static void get_rounding_mode(rounding_mode& mode)  { mode = fegetround(); }

    static void downward()    { set_rounding_mode(FE_DOWNWARD); }
    static void upward()      { set_rounding_mode(FE_UPWARD); }
    static void to_nearest()  { set_rounding_mode(FE_TONEAREST); }
    static void toward_zero() { set_rounding_mode(FE_TOWARDZERO); }
    };

} // namespace detail

extern "C" {
  float rintf(float);
  double rint(double);
  long double rintl(long double);
}

template<>
struct rounding_control<float>:
  detail::ia64_rounding_control
{
  static float force_rounding(const float r)
  { volatile float _r = r; return _r; }
  static float to_int(const float& x) { return rintf(x); }
};

template<>
struct rounding_control<double>:
  detail::ia64_rounding_control
{
  static const double & force_rounding(const double& r) { return r; }
  static double to_int(const double& r) { return rint(r); }
};

template<>
struct rounding_control<long double>:
  detail::ia64_rounding_control
{
  static const long double & force_rounding(const long double& r) { return r; }
  static long double to_int(const long double& r) { return rintl(r); }
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#undef BOOST_NUMERIC_INTERVAL_NO_HARDWARE

#endif /* __hpux */

#endif /* BOOST_NUMERIC_INTERVAL_DETAIL_IA64_ROUNDING_CONTROL_HPP */


/* ia64_rounding_control.hpp
YZX9UEGH68JuFeKoVg7wg/zVzMeGid9h8gpoqGeBc+IzGhqORL64IuReiXLGyTN0eoTlRgm74Bd5OEAlS1uWdyWsIa7Lq9IPZM5gYePBsN5gdsDG+H8lUAy2Eo4K6DwSx3D8DsevpcNISFYqvbdC8BwFuUuFjKshjbASMIbjr1ocNfirXJbScrGhdCzDjuWENkNw14jYaI2jUuCNFOcldK0S1COknWAf5SglW/Krg0kGaCU8ZozlFdKLUM7i/2H4LYUmtbDDSriyChJsa3uTtHE1yTE2VoZjtCx9XMPvSqIm4FwgoETk/TinGruq+EXtFLZHiQjJ1H9DoeUgYcNl2TEIx4q4VirSipK2EvfDS0QpLoM08N9spLuQfkHaFGAnIr2ENA59zF6k25D+QpqJfvERy+JvpL+WzT7vdSHS10gbL48xDNL9SP1INei3NiPdg7TCYHwPBumCwYIn6MV18MjSfjFY4IGXwCY5wE/wmIZB78kloCtBvrzPluXPkiz2hCG4d0hW3iVDcvK/MIRkEXINWjEnfzPykM/lBa3IJ9mmrEhygaeQG3xzMk6QmLCFkDeF+89GemZFko1kxTXwEdfxt8BGPscnucEDskjef+McPIAFeuRDLuADT+oNvnQ/eENG0MnyAgYvM+KP8obMomyhH/IGZWWZWCr04jKRzb+WOiZLBQ6wbSyyB+nK7Q8cLiMwCY/kWlIqZPLCBQ9/XMgGTNWOOV1V3Be9cYFF2NzGKj4wVd3dMZdbyV/XCUPCxdwwJMysT+lhpjUwdXwJeJBLv0yv0MAFptTX35fOltjA9NT3dQNcd0xzfVcqU3EFDs5zMUaN6c3IgxyECQzQZ3FmlFn40fvHgjJ/e/WVgZ+0F8NmmPp1wPa1LyXuhCHFrQ/jVi5+rNlrZX8bRxFXT9bAnaBh05wt/HV9SAMzinjzw1LCXWto8f3pgKH+ukbhT2cVAfepoc7Yfw3AduuHqTYm23r1wYQMaj9s8jD/fljY8al5mL+Nde1r4scXu+Aq5Qo59LC9cbNYrwyz8Ytr45JV/G1cqB874W6ylHA7i4wLLMK+dhWOS20+eAt68Od11mXc61KHESscx79vK5j35PfFQOffH1si+yXDh+fGkpAdtOHJ7yT79sMV2YtksyOWEu5tA3CLY+fPVVzDvpHoK2j0h2rKhT6oO+ochyue9LfCcPcwwNXtF+n0/44v9481HK+vrHDMO8uBV+7fP3DSc/wI5i8S8y9Z/93maSAzydA4Qu0j5M11gR/FFFffPX0EeEn5II+bvZAXrIzgT5A361Pcbo+M8C8r4EnswvzxBwULOjF/VPvLZn3kupFUZxyx90c+sIHl3083wXXCOtUAK4yxwMMj9cYfheL8aKBXoVhrjSoe1mwNLPi+xJN+FtI47oxRatkJPsDOzWvzeWzORx3X9DO+j43KYY+X9Y7VaSHDb6OAKevfPW72JX39dR0/wl/f9SrI1h46m+nKY7SqY1OFno7PhDg2P7uiOPXxqQp/v00v799eeONAzgrej6B+tEfsLkyvCaNJL4kXrR0To6m8yFcG1v/gMdurXTp/dPi+4oX3LNmWY+qvh9lzvv+MttfComvXJlfq2SYMrLmVXn1HNRaazy2p80pLKoWMzOeKE39fqPSPGQquJ2ZfmT/mMmMEJuQ307eQ8pyyFDCTHphq+7YkxDbu3DECi9q38SPy8b4YLDCBRbgM0xUPsrhiCoynFVzQ4z51bJPzsT/GEH/6te6ftKqgdaVrQf5ty7rnN0tftvmdvWpOVsgG3ezypH0AVD7gKXg8DpoLBgsbgZ9tH8IjeXulPcqqsli3Md6gc5uTAA3ZmeYjaC5C2m0=
*/