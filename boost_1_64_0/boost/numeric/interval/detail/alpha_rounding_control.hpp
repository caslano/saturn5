/* Boost interval/detail/alpha_rounding_control.hpp file
 *
 * Copyright 2005 Felix Höfling, Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_ALPHA_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_ALPHA_ROUNDING_CONTROL_HPP

#if !defined(alpha) && !defined(__alpha__)
#error This header only works on Alpha CPUs.
#endif

#if defined(__GNUC__) || defined(__digital__) || defined(__DECCXX)

#include <float.h> // write_rnd() and read_rnd()

namespace boost {
namespace numeric {
namespace interval_lib {

namespace detail {
#if defined(__GNUC__ )
    typedef union {
    ::boost::long_long_type imode;
    double dmode;
    } rounding_mode_struct;

    // set bits 59-58 (DYN),
    // clear all exception bits and disable overflow (51) and inexact exceptions (62)
    static const rounding_mode_struct mode_upward      = { 0x4C08000000000000LL };
    static const rounding_mode_struct mode_downward    = { 0x4408000000000000LL };
    static const rounding_mode_struct mode_to_nearest  = { 0x4808000000000000LL };
    static const rounding_mode_struct mode_toward_zero = { 0x4008000000000000LL };

    struct alpha_rounding_control
    {
    typedef double rounding_mode;

    static void set_rounding_mode(const rounding_mode mode)
    { __asm__ __volatile__ ("mt_fpcr %0" : : "f"(mode)); }

    static void get_rounding_mode(rounding_mode& mode)
    { __asm__ __volatile__ ("mf_fpcr %0" : "=f"(mode)); }

    static void downward()    { set_rounding_mode(mode_downward.dmode);    }
    static void upward()      { set_rounding_mode(mode_upward.dmode);      }
    static void to_nearest()  { set_rounding_mode(mode_to_nearest.dmode);  }
    static void toward_zero() { set_rounding_mode(mode_toward_zero.dmode); }
    };
#elif defined(__digital__) || defined(__DECCXX)

#if defined(__DECCXX) && !(defined(__FLT_ROUNDS) && __FLT_ROUNDS == -1)
#error Dynamic rounding mode not enabled. See cxx man page for details.
#endif

    struct alpha_rounding_control
    {
    typedef unsigned int rounding_mode;

    static void set_rounding_mode(const rounding_mode& mode)  { write_rnd(mode); }
    static void get_rounding_mode(rounding_mode& mode)  { mode = read_rnd(); }

    static void downward()    { set_rounding_mode(FP_RND_RM); }
    static void upward()      { set_rounding_mode(FP_RND_RP); }
    static void to_nearest()  { set_rounding_mode(FP_RND_RN); }
    static void toward_zero() { set_rounding_mode(FP_RND_RZ); }
    };
#endif
} // namespace detail

extern "C" {
  float rintf(float);
  double rint(double);
  long double rintl(long double);
}

template<>
struct rounding_control<float>:
  detail::alpha_rounding_control
{
  static float force_rounding(const float r)
  { volatile float _r = r; return _r; }
  static float to_int(const float& x) { return rintf(x); }
};

template<>
struct rounding_control<double>:
  detail::alpha_rounding_control
{
  static const double & force_rounding(const double& r) { return r; }
  static double to_int(const double& r) { return rint(r); }
};

template<>
struct rounding_control<long double>:
  detail::alpha_rounding_control
{
  static const long double & force_rounding(const long double& r) { return r; }
  static long double to_int(const long double& r) { return rintl(r); }
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#undef BOOST_NUMERIC_INTERVAL_NO_HARDWARE
#endif

#endif /* BOOST_NUMERIC_INTERVAL_DETAIL_ALPHA_ROUNDING_CONTROL_HPP */

/* alpha_rounding_control.hpp
0+L6ZujyEPrdSxeqL5X2+6j70fSNE2bL7LP7ta/Sd2iYK7N/l9X1ou8MMA2z8TUmR9B3BpgHsz2bthXQt4Quhm+H9riuDG12l76VdKX1XmmtzVr40u9zYM7Mpm2NHE1zDXNi5r7T+gHNGcyN2b1q7r7UF5grs/L65U9pbcIimP0d5ptP3zi7GsZgh2vIhJk09qxutKYrbWEdu/30PJgtsz3v6nSh7ygwDbPS6Z1/p29dsK3K82xxHbx96HGqS91p7JV26ueWB6n2wHTMLm3O/5buCbNndrB3h2dUe2BaZuWLdwdQ7YFFMPOtUeRM32J7GPJTg2vfvQ5t6HdEgg03sVtD+QkLY1bcYNpEqiEwB2ZFnmPv0e/0YU7M6nrbRdG8wGwU+3jddNQykOIAs2b27NsDVF8KhHYB3p8NoZwQ2o2e+j6R6hJMx6z06/5/07dmmIZZzoteT+h7MsyeWb0nbkvpe3LPqs+LeKCjuqSBOTIrvjlnI801zJbZzn/OUV9iYLwvPtumx9P3SJiaWV9tDR3VAqHd2qwP3ShGMDM+n7siGlOdF9qp3p3rQPGD8bm2srR2o3UEc2Lm0HtVb4ofzI7Z44hONJ9be9LeUWljbFNb0bqFhbN2O/Z98Kc6n2xoZ41rz7K5lEvDk6ldpd0oMs2iNQYrVNpZ4frdP+Vk83tRnYdhXgaVzqXv3oKNHfu9J40PpmY2rPWdnyk/YWZkuD69bUtjh1kwC7SIobPGLpgbs383HlOH1jvMmdlnD1v1o/yERTCr2yBsKOVZb3NVqjJ2Na5ue3o46S2/N8W90s4eS6LfheyA2TO73ymznNYRzJHZmH4bH9E6goUzM/17Mu2puj6GGmKJa+LStxo6v8DMmTXxvPAV5TXMhFn1uxOH0dlGsMNH3r2ncyTMjFlOtSM018kwC2YP/1XnM1oPwj3n9XszkvYxmCkz1bM/bSkHhTH021BqQusI5qCYBa4NrTOozs+GeTFb1KWdM+WLYM5Hm4RQTsB8mNVrMOgonTFhNsy+dNnVWm/qFMSdWXj/H+ic5Qbj7WatHZtH60+woTGBKfT7VJgtswnDG6sotjBnZpPeRa+muYbpmLUsXVWNzigwJ2atajg2pLUJ4/MZ86/9PWj9wTyYDcJXQfrdNcyeWY1Qd4rtNZgVs2ufXuhJ51ah3fO9q6nuVsAcmR3vHP4H5XzfqnPde2ghtQuAqXlsffN/o3MWjI9dOzF2NM0nzIHPmevmZMprmAuzi2tD29C5VeiL5flNYygHYTwO60xrPqM6ITzvi7D126lmwXhsp2896U75KYyhu633SJpP4Z7TzurMaD6Fdj49Ct7SfParOtdfvZ73A51RYHwMT7wromnfhPGcGD3kyjvKQaFd89flAykHYXw+3a67V9A7JYznS+CGPlQjN8Bcma3wfk+/+ywUxnD0192095cIfWlUP20H7Y0wni+DZ++6S3MGc+A5eHqymt6d+lfNXU3pr96UgzAev5vjo4vovQPGx9DlqvkUyjMY76en6eSDVOtgWmb3r5Ybap1gfVY/c6E9VehL6dLXP9K5TmiX7/U8Um+nYXzsLTqqKO63hLH/OHj8WXrfFJ7X7pvysTRnA6q261n9WT+aMxh/XsbT4iyqgzCeuy93PQumfQzG476h24O1tK/AeJ55neq6mM5ZQrsu/gVRNGdCX6Z0alBGe7hg9rtDmtAeLoxv45J1fSgHYTbMmv7sTWO4D+NxaJm2tCHlIMyd2ahrhbTneA3EeZCZa6PSLrRuYXzsXZd/c4hqHYyP/VCjnXvpTCu0u9XlWjtatzDel+TXmXdozmA8RosmnzhN9Qzmxuz8N4XdqZ7B+HzOX3M=
*/