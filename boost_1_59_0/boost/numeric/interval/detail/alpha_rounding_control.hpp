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
Ztmhs5I0VuNQbfzw/LoixhtRHka6rMGrvo4Z5g1Z6Cv9gCpzAMqGAxvTFcEV4/bLCOQrEpKR28DB7xAAmNhAdOIwfvqMkEVRqhH/KfWhK27UYxZHmd+IC2rXXPSLX3oiiFXEYP8m8kK7daE2mgNVlIyZottmuHQb3ItZZlv8eLPiiXhFOlKSPdVDxYV9I8NW+iz2qRom9Uiyphrjk1uVVMMpELvXvTSBrnEPZbbptBax12x/IE/XZ68J+cuOO+c+3x7fpqamZofmZXukv6RjsTRn2EjMw0fjv5giStL8/FuJPbOSc8bZwPNe/mu11LpRJathJbSWM2iotdXLM1N8ef+baPmQwTwe+3VaUGLQSMKYSNvzgoHLvV1bEmosva2laP6EvS7aTqI+kbIlyXrxM7pI7kmeI7M9SdOY6p8/H399p9NphJN5AFc5MA1atcXTjFN+KSY2HBm2imeOe7OX1ObmkivpPDcRWHozrnKGo1csclaoTkUqUdYtuULjhh8mSYKYbqyGexiGH9fZVHIYLlyfsCA9QwAxSgAKC9A75iFRaH1O2CtcmdEL+6px+yAyuqrcvFuS/m8Av0yVYqdGcipvD8USitu1fYrv2nwFLXg9eVxG8jN6XbYt+d8BfMsbvWqx/LfYFr+of2tufK15yNorJuJo9Q/KsyXQ9+9yZ6s5yDdu5CjwhJmihlmEeTyz/MYcXLCDys4/ImE3M8/y+8MAKJeX61R7n/3/vnNSk0dpYOPjGH6AtTyTF/0s/q1s9OPvn233Nw7Ow/fb75fgsXqh4LDfm4kVQ5Dv0QGalN2hGGAZPAKHiO662Jybv6cyxiH/zCF4dw7bhXBSvz1ILdljFNS7a/szATgyJufi1sq4t4R2DAf0GOqTQ54NhQqeD85xOo8K0IltmIKgf3g1Y1rtrueiGtuH/dCTMYfHuB3OAdpY+xidSDBOUugYIX4uLPy+W041KJkSQrafgIaiihGedc98S2Bpcemw53ZAuJxDKgrcgJ49TpMciezJs+O4GyvBg9a54k1TjsrSCuCmC2LE4l9DbAz10ISCQ999j+SBvgWFS9cv4Iy+oYpCeHOk5cKqEIKI+jRzO0kXsPBjQ+3uD8clfUkuIMbWFvg0jbBZxP2LYNh6ngkvC3+A9LmWESvfydWBN2Zf2Lk1JGh6zMgXW5WEY8PrxVn42HOST6FkThUKiT1GuqHZNkQ1PlT+caHF5O/x2k297zLxzEml7mgK0EmvqM7bVu8MHCxlt9Qd3GUxpQZaaw2qdKye6citJ0+u1HMtO8IEkp4HlbZCHEIwLZDsHvP8SJHRjmX2la5yf8Prc5qcdAgAIUNxLlV7ZGN1FZpFwRI3I7hsdo5UAzStDX9gvt8Md8bxpFEpZdIxID71OpytPy3huodQdY/a48Txh4yivx00GuYT367fWz6QQf1ub9giAhFMFTFZf1hk118CSqe7iJv3ATsvWLhFX6dvcn8BqSbsdh2rZTZcgcRTQ7lx69VuotqCZ6PkQLiRq3cbGUo7WeWDR+TSPO1dIrVwLtJIYaaWe3ZD/hC/nl3PGvuVYSv/AVo5cVVOHk2+8uVji+N+F4xfoEjr9onvA/dOhoYb50fq4o5W3O/SblKlNV+U/NB5PqyxqkVYOgN7nYc5kaXlHIPahyjvp7qgywTLxjdymIefsr9ltlndzppDdje5Ja2r8tv/J+XPa8tb7f7VsIDYmV3L5Jl0ow3aWDYb8JmDhlKXFOGQWZ6cG51agDWibJAcHXyDE2q/n7uXurgfHmvHvfjkQh/VI4yxtA4TZjIREyaqNfeK4uwBR11RxbgyHDiSSYkfwntWTOOT2lGWFcJ2tbEgw8H5i9pxlRgjcvbQDZrYiWWgv4gLhBuUQhLidpbnZMtr1uV73E+WtRLx8TSng21++YLhWcOFJk189m6kCAHPCwdqS1X4BGbUH7RRnC6mn3X7flVKIQxSKZvWzgD8WP5O7lm1AnH4tqs2pGXCESAur10GJv4xZXpoHAXsXjjAClaLvcIZaYYiJE/rUr1DF5lcEtdJAVnTddLFXZ7zugurS3QT2l4KIUOuQs8Azm2sNY7tukJzDMcQnu26AoyHQjWubyxQgxYaFcU0GZQQwSEMPy8W9wUPEzJ2ay3gHFD2iwA4ngJ7YWxdUIXJkcsSZDM/yVFge4q9kiukV/0cGTaxEMmCcgXWUQQt8aPBwy9yVBus0s6MDczGpRzCA9MLnzzU5ieD231WPgbxFK9y9Tgfj1M+zrDirRfxCKsh9f0P1YzTNzCFN4Zxdf1xFN9Re67Hh6rFU7WHzDzQyomaWux3mnW3CngmOr0Hy2gx1YXF+9zvXHL+EScmkuxawoy3HBaxh31gF+1L2vWAteCMvGzeRhf4xaSQBwkwItwnJxVoe36LqSyMQNPNM4jlApLlHDJnFnfUbIVm3kp1A19QZvMTcgP63j+L5ehgxhdBS42O8UGMZlKUJUJ2h9YCFdI6KCb0RwPRdcNYoaBA2mP+cSSyibdF470JsiTSpdtIkR/2+2xeMicUrpLM1WByCDvBdFe6sSrVSH13SdLBHHsuUvsiWCcBkdyi9aZwHNuSzRZrCJyvPO7L7sCmXjKIo8ypjdj64OVORpPIFMroP3Y1nsznhJOuwRUc3aKi9BTZQp2nBBwPbdqN8tTrkutqBt+QHIEqWt2isvVDylQO4UNsC7Jbvp/EaSsia7jui2gk6xRaQkdRNYnysnsCD8WlH7KN7DuV2ttHFw0qMDCCyu015mg/xzG3W7KZKvRXHTKVPgRdq8kDvf4aCoJ6LWVBRLyV5PE9Aj74sDX/+jwfxssFwKwD8N7o0584ktRzkI9417VTUMbxSEJb2BTRv5OkRCInFFRUBymE5jGMbv3oflhFjgYVDZIKIiNYdXrr21yDgojVqVDIoV38p32xAuG4n3RZlHKpFSGJ5Mr+MSN2BRCIElXcNq9xyOLliZ2PyYMQiqRJLsNNEOtioiCVZX4hGT+l/hW6gNiWtKnbdgMfr5e64SCguYyUiW1LbYzpUnEs/WsgVT7Y75LPeqyo3hKPmAs1Cy07u6AtQg4yH0kv9SO5qiGuCc7w75LpDHYhUU2NCRubmcubKLO6wDETSqdBdQvS5bqRbDIw32Hg2FHSv1dlWWHhtpOL/hgrQLBOUL4IiWnOgXo1kRI8BDjHoVPIGxAqcv9JouOeZeM9z+INzKX5RE2Lv4rhuxf8n9uDhesU7WATjxH8z3A900tAhJvcC1DMrwuQiJDyz5m32gSnevPF4CfvoufhK6tkY6impXqDR3Tvtvj2eJV8Swg2G+r+Qb4MLu1XaM60yTbom9j6aTPWS20yo7n9kfYb9psqjOhUiXEFCYnhf7REv9bd8yJ9RRJ4JqJ4aof7m9YWWSPmt4//WAX6w/XUAOWmLyaIpmypL1Luqm7yji2CqiBEDWTHt2JwwNHST2GL3jAxe6NGlrVGSqHLC0fvLHgdvXnt4zRupZfBL7d9GAI5zPlErdndffLUZgVrGm7xsgkD2lGZ9tMZDyQO7UjV1mNGwqrjhV/D9P577UpvUFrGHPrHfHxitrEgecftpQDxtoN+fgS1zP7EabBJcfXNK5pfwYrodTPlujBJdS6fdt2Rl2ZwmlnkuoAVDT2T8+5vXjVyYlaY0sieIYheCZ3Qmh5PktYAbynCSkjoeJAzyh7Pbj97eDWW1XZ6H/YXEwzdjGS2HtkoGUZROseDEps/uIXQ59x3x+VGXK10UldGQJxcjL1eE3WNyRR5WKY323J3TerIdXkpex5XO43DoM2fU3UTSbqLi99DNXc0CKWtYsYCMaux1kPLXZsCXLEMNYeYzA/MgGyn5xCqyAQd1yIUElNSRjg/D9DJX9ARey5QYYAl59r00zUjR20d8TIUyKltB79xBoBJRyXpEFZPsUv3ZHloYpOWLiBxWHmQKNpBAXSUgWhijmu7XnxGcJtFEOPPC65+xMYl93hyCUxyxUTNz1NmEa73jv9lGjVDPHtwsdxYyppcifjtMxU/otAQYugdmJjv7X4+XUyHfMIZTsIHWIMJc2/CpXDXolrP5M4Yjbt/t/devUqwUK7UHpHPWWR2LuzYqrqg9YPTH0bmuIKi6RpB4PTNM1ethbAb8VvSCWKIT9SEN6QSrELjFjQqg3V/6fPYjhavGiL2lA2z3jN61d2R4HxaDL1UlIkSA7EbWD0VNI/YzvrhHm0EbEvaJxiLTFj0J3HLyJpeaCldP5pqtuNiYCaSsbYai8Xz6441a2GQb6phWE/aBowwuFUG/GCxI2nwjnTOl01JrqHatKhf0kNZzpcE7BQHCluupo+EFWfRFBE707O78rFodWur4GJQ9KNJoEKy9Gfwsy8Ez4A3ghPCz++TuF/BqBQQsV3qa7FhTYkORm/u0JPmp5Pyj5XTbloZg4W2liJ32eNmf8Sbo1za81M+NrgmoM4XG7RQmnC2NG9UW00nL1hEmUeAehYuW1RjhylBc/wbALl8Q8veqlbB8v3oblnjl7P8Arz0FK1Q1JsytGeW4fIxKAhfLMs0+0s0oMzikbeO+uXwDyp6idrRywCdei+K0QKBBr9x+lbpCpPNUAbSgsLenu+mYt1TWi0Gf7lnLUM7Zq3A3W8EognbCgNybEF2QOauw3Mq5/CE+iF9eJpwd27AWjdJ9gw7TSbtyw4ZD5DNWxXQ16C2zn530vvMEJ8FSNJ9RseErKB4Xgsvo+wRduPLjFsXsNzugiW2J45kDKw6JbeozVl0qc04aXPTnanShuDbpElbszoG6Zx2tqmRBnGSKfxQ2WyZXNqC6pUMizGInFUvaq5IksgE8QIrAH9DLzwJQYf5uZEF7RrWEh/toLaXa/dp4OvyPU7xxdoOwar+fc25lqesjhNiV2Sr2p9wrlJhZ5UheUKQU9tgKmI3cf3+l4rXYsPRjk6kItLRrCVHsLXUyaUA5KYdF8xWJpFCbVR558NhjBqbiYcwa3bTUwE0BJg2xexC1n25CwzbLGdYfFdHlKN/Z/PsMa1tAzf0J90gU0nFvSuQPLpHCPcceoR3fgpnr3lyMLueoSChCXvQwLIBI2Az1G4IQcJ3HOfnUpSMjXtydnJ8jDlp/0rXv5CjBGjDtKDT5ycg/b9UxKg8WEgfTag4ikv2FvfQgx+klznBF0aSY9MINOsNmD/HHU2OueqKILFmOFgNHWPEluvi5xlCKyk4CBJFZK3+Ch2wSccSG2/IjjWNrjTzvnSaMt9EhSuJ4CKztKFkmf2raT0f/cDWiOhz+VslD4Etc3VS79rUpxQCc+vYe+sN5ndZAS7da78O+KdTbnN0qyillLN7AJAobp0XfpFnakpk87Qpael4ElUn4/cinYXzQHfrdXj5fYDHAepDIZYkyhWfQn8NZMHXgZnFw4q79BPerlwDuqz6kSD9n4HhfoCjda5AP1QswJvbwUaG/yBt5k8VC+aObq3rb/u9JcgwpFVNzN6Ta/aA960fnNBCKEAZfT/wLrCq7XZ/VpDB02x77d3EJ2gyB4xcEphx3NasFtIcUyMs+3Ok3EMfY455xy0vEjoMJWmo1wJ2l1HDkbvirDIHJW/yGkeb2tI/KKhsBFIqI4z7K1iNVVgOIzm3yb/o2XnmEuKBrdA1uZXOGhYwyPEw0XS1ufwCjt2nkZ1BU3JgTItOiA/NamPgNe+Nf5KQ+TlfOuF3qhn2MCYNoEc3Mgs2MpF2JlgED/6tXz3owZCGlJnv13f1MAsqhuh+VHEqbOi6ebuHTg6PvkNezWiElVM8AXu/X7p1Mn/JGNf/srSBv1M55BCPREtpSo7R+CLTCZhJBBc09poZ3UWHmt5NcZ6txgGMTPRP1VAhymeWI9ckJKtwh1yB/w0Fx69+pzTt10tfVpaKWFamS6Igz0fVj5Vr0Rqy6bwCQWHAIDwd8P3x+ILUBAR62YhyuWDr61+4Fxf1DBXhSPFZ3zcM4I+AI8Flb9uBaErkXIDS9t85b1bzL+rY4fHOGt//HuYne0O7KQ0v/9q4JFLV1fEPuM7llaHVFeRLaJXxrRFF4GdSjVfA1SVbSNUvdFDOs2KCZUK3w7DiARjoRuE2f1c2oyRb8A0FySEGCUSR8QeISDovHHljVgeHjf3MsjO+3mwbKXq74+zddDuazmSlczqeeH3NNJI4JGuVlkr3WU0RJ8/LyGgfu7FY3+MblMT5cqG5QnpyNRO6us1niFte7/rMZ9xKSDAxvHtq8l+AmwXVFWs6U0Gc7a0nIsrqqFhp1izpB3KIAe+bAgu9vToLXyEfKZxJDSOlyTtm3wKZTJonddEYwkZbCNztK+Nt9Tc+xDyB/IsYnkp7SlSi32eBz5d5fQ8HXTA4cRQMMohTli1iJfPnaepvnzHtIidZW2arz8DG9In6BR1G0w1GjBpnxplpAh/rjopQ5klj9i76qVArVqpy6gkxPJ/9j6WjhyR3V3ZBblvRnpym8LeDjL8CM2GaofE03uoHJcnuJdl3Sut0cdDRH2b9JIRh7Z0BQJezwkVuw45fZ1g6M8sUGzOn7/01Iy8aDwHIulEXvMb/PfVIGX2a9/HyqOyVT8VDLYlmd1ZkPJ6nqEt8U0wuU3sik42Kbwkfx+e/aq2Zxh5ydOTyHskPY3Z1IpDty+WQrWXSneS5SK/h2kWpgRirl+ji0iWFFwlrdpEhP/kNLn7bcxWy4n+sE+R+ctx00DTBxOVXCKeh/uEG1AaNuLA90V+s71OOp5y8VLdaPVXhvs+VTT73gb8VdG+9eXIMZRG1YsVcIl5Tgg9c7gGgnlalCiVukUtwPPaVF9lqe9+ttGF1A6TebEy21UG+3+BX4wgIo64nkR57fGVALuT+HsR1qZl8UeYlUyJGxJ6QilD78JpbgpPQ2ZOQrihnI9nkFZalmo3M8jeEPU+pZwwBqWb2HFDewfFsQ42TYJZa1FZisIH/wfmVe/GBN5H5Dyr8N2bNB/Z6SqXQGfH58k+huzXu4rsuwZBU6vUH9CzfDQLt2OTRdG6OjzkYNAnuWMihOS+c6rVOwj9JR6jI1R54mwH43S4goCG4tDN0rAwkiekuycg++yWht9HERTJskAnLaEoNrQiOfa3Xeqq/q8zScN2FiYygzDvUtg3MTg51cwoPJBnC9VxwusYwKGXzU9cchFPMLibW4WMbNasxgkbljrfJ7LTVg7pTVMdOl0IiAln93BoY/tvxH0Uef0P8SvtWyAJbXD7s2ZYlfvkpXfqp2GJAgayod1a4aSSLBT1ErLVMTClEchz0LNybBfVwEsCtJXkV0pquZHzxXIRgJc9sBPCD1RvTrE7QrFJVH6LNoS5TIXBt4vRCIKIMZWsc/DEKQ8GWgWmsq95dI+gh4pJ3GYoFjPq+NZfGwPp3O3lQtJ8bOqZ4fpb2DA5q/EPfoUpLTwgUcHVaSr9ZNnYM5Q8KUoVdf62VyDtXlcHwz6rzsw7HTTipFPzzjq60/AU3i8IKvPzNtzIU+nteeGJLIcR02Fen60clF5byLp41kvBltFQe61HUvUY6IAl+pcigW/m5FaeMhJ4yDhY1BCekmUMBd+DvS/bt6b65kg4hZL2tkT1uRQdHZ+J7yeeClESeMjiWIsC1RB7gCd4TZImE9STdVKGRYgv2CGRrtnJi
*/