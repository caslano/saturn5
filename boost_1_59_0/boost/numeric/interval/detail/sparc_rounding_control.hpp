/* Boost interval/detail/sparc_rounding_control.hpp file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * The basic code in this file was kindly provided by Jeremy Siek.
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_SPARC_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_SPARC_ROUNDING_CONTROL_HPP

#if !defined(sparc) && !defined(__sparc__)
#  error This header is only intended for SPARC CPUs.
#endif

#ifdef __SUNPRO_CC
#  include <ieeefp.h>
#endif


namespace boost {
namespace numeric {
namespace interval_lib {
namespace detail {

struct sparc_rounding_control
{
  typedef unsigned int rounding_mode;

  static void set_rounding_mode(const rounding_mode& mode)
  {
#   if defined(__GNUC__)
    __asm__ __volatile__("ld %0, %%fsr" : : "m"(mode));
#   elif defined (__SUNPRO_CC)
    fpsetround(fp_rnd(mode));
#   elif defined(__KCC)
    asm("sethi %hi(mode), %o1");
    asm("ld [%o1+%lo(mode)], %fsr");
#   else
#     error Unsupported compiler for Sparc rounding control.
#   endif
  }

  static void get_rounding_mode(rounding_mode& mode)
  {
#   if defined(__GNUC__)
    __asm__ __volatile__("st %%fsr, %0" : "=m"(mode));
#   elif defined (__SUNPRO_CC)
    mode = fpgetround();
#   elif defined(__KCC)
#     error KCC on Sun SPARC get_round_mode: please fix me
    asm("st %fsr, [mode]");
#   else
#     error Unsupported compiler for Sparc rounding control.
#   endif
  }

#if defined(__SUNPRO_CC)
  static void downward()    { set_rounding_mode(FP_RM); }
  static void upward()      { set_rounding_mode(FP_RP); }
  static void to_nearest()  { set_rounding_mode(FP_RN); }
  static void toward_zero() { set_rounding_mode(FP_RZ); }
#else
  static void downward()    { set_rounding_mode(0xc0000000); }
  static void upward()      { set_rounding_mode(0x80000000); }
  static void to_nearest()  { set_rounding_mode(0x00000000); }
  static void toward_zero() { set_rounding_mode(0x40000000); }
#endif
};

} // namespace detail

extern "C" {
  float rintf(float);
  double rint(double);
}

template<>
struct rounding_control<float>:
  detail::sparc_rounding_control
{
  static const float& force_rounding(const float& x) { return x; }
  static float to_int(const float& x) { return rintf(x); }
};

template<>
struct rounding_control<double>:
  detail::sparc_rounding_control
{
  static const double& force_rounding(const double& x) { return x; }
  static double to_int(const double& x) { return rint(x); }
};

template<>
struct rounding_control<long double>:
  detail::sparc_rounding_control
{
  static const long double& force_rounding(const long double& x) { return x; }
  static long double to_int(const long double& x) { return rint(x); }
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#undef BOOST_NUMERIC_INTERVAL_NO_HARDWARE

#endif /* BOOST_NUMERIC_INTERVAL_DETAIL_SPARC_ROUNDING_CONTROL_HPP */

/* sparc_rounding_control.hpp
gIg+U21aKnymgDYm4isKK+wT3B9fVtoUgg1zjKeoxNCoAooEe/5QgOITE8v/dO+2s1JK+k148SjLeqfg/alXXknwjJpkyvQlGl+zI7pxTa8RnpbxbY05G9gTU2gGIeApHjHbsXylTvYkxLXfDW5R7phSyI2M+hSoAR5A3DuOh1wVXiU8zre508fx8rVg2vzgKGXd0o8s1tdRAb6it4vWlvZZBCqJkv03vAYjxfOsLxUdckOaHo9x2N5fo39J3Qn0kyEJu0kjnhf/Ka4wwPbKr9MKuS9wBCzDWDntpzulQxe3AYZgfSXtIyJvDaV4HHS441sQj8LZgeIQEJXL3okWPWycZ5VA1mGwS2GfAk2D4DJEUYEPv/nOvZ18VHUScuM3QYXup8kUwkQ+WavKg0xd97i5E8+MZ/kJanTYlRhnxcWAOLqgm0/MrWSXDU7yKI2wI0kgPubQ8I0FfjeNGtwoms/bVQKw0HK6s2fLhKx+Xylb288FsrWPek/h30nwuMu9dcVUhJSa+fUSZBDQb3NeczNsKKZz4vqic+IFJ25QqNVsgDhGwKhO7ocLES3sjGa//88XNIRIOUHensOtKlk3EBBRoVF09rEek1AnalBnLElX68/Vxik6tSGc3gzuwNHWxK1ooSmXlMJRWLPUJbIgFPKxrBmpQ+8OETy0SnDAvisP2fKEMRtZ9EkAgZvf/5d593x8Qj+ksLbfITtlGbrzZUjdk57I/zk7jH3k03WSQwxQ5tNV8hcBXcSdWodkmEVkVwfHaXkvBd7x5zWPZx+6G6iMDk2crvtp1Qt0WCMA6WWpfYZ+botgFJMo0/gtQczOSThLFrszXBNthx+dx4KNpbFYTnuG1bHZn6PPOMZ6qXnl2UFLdVedEt7kElRTdac4XGpnGh6oZ2UGHEmoxH+fK658FFSsHiLmCmqDoz0WgFVBXoFrWA8yMyYhZxA1vxwYeP7xOToYs2BIqTwnZHqL5xFI4F0RNbtXP+TvetNjQ6m8l1S6Fn7myTVGGSN2JVZHZ3HQaNKKnMr0jpXCrr/Y5ekDm3F227t8dsb4o8gzLFCIkP2vv2jxPR9x2o8O5beqcr0QOBR3uuwaNxTi/lTPj0i6UpnWi4u/95kYWa3jRNJuZXzq4QvqKoDEq5B8j7S2spYUKvObc4GAlVU8hvqxdrwkG3aCRHjcyLgz6hLOdMWd8IjbJnb4t7DiR7X9zczZ+pDrV7c/Yq6NyBq79sqyNRpkRrL2kVRJDvizN8R7b49Lr7slxFP6MQNIXOiX8H1/bm4AvVLctL9u337e2JdnSiZPKeK2Yxvo+WxUcVWwCeJBVKKsoyO6UCAgqbhhiN9F2a89C1XhVAE7X7OIouzGpKuTJyBeEXCPsXor53piVneLdwUIyZvlKTdQdxsLCnGDMQR4my5ymsDx1McTpXNFgZKirAMNMozs2BaAVLa1T2NGPDxgjzGg48w8frbkaoUTXmRdgSXUVymoefR33ASxS/qs3gFCKxywjN7OW2weH690GlbanM+OI1XY8sItLvuMhLqF49M2cEI9IUuKSu/63l3r7+Z7vnY3C+Kz99lpvEoRfbXHHRQBC6zgJzwXvySOyMC+7BpBJ6A9/rZHW6KOSATqQr8XG5wYHEFzocsZ6gLV0MHbEp5Lz2WwMrQZCzOGt/UpBcFOMq3S6E+FVd7sRdS9dFBT1i1jVfb2yYW4TfBGh+ahobiObLZEkB5plAXEFayqkehVQJwOj3C3IVUYf2EfMQaXnS4tFugSC0jNBoWoh1vHYfhwXeRfhvW/D3EgBc/Ct5aHj1nCIVpwoEeosahpi0xwwIZffoWIhTIXFom8wW0W/es28TWePua1K17v6R0s/unoK4ln8GpQ/e1efX/zDE1wW1JsexHx5FZGYywdAy2TjVbg2Wumz2JjoAnfi03UNJritffEd8hLWBOCK+V2zBgC9s4wyAR9mx8hWrfktpYjabNeRteWHDMDeXj3z2RXexPgr9+UC0/UDXiY+A061sXq8bjel0rNyr5kWpuqeU07tdpy0+0l67VsZxvosEQC3UYptkFD4wk72g/9ZdhrBt4IyHf125zV1tF1ulGodG26PJ8qPanNySh3hNg1hfEMrrL1hR8/KTYf/H+3d3CEJ9tgked0TFfYHdVBcqiWo/Hl6TRjCBdvM3JvNsiRNccGVRrHKWXFq1w3FhdauTwtII3h5HPk2SQdaUvyDWLj45cGxRLGRgUX5LcFgA1WO5vEXe4ZKDzUb/h9qJBOD8+yWA3Qo8Gc2TFSFPkgQFw+Eb6+1qWQVX0Jk2q1FB9e2UHjQ13UFx0yd4AWHiZ15IsLHho1LuXT73b6ovZn9Y1ijiw2V1v467xlhsmsIhNwrC3VcuiKIowOYf5DC+0eP69WIJP18sAl0LDgZ9KHCqWq1FYDhVk6vOE4r4WxP+K5FC4794CubvwXuCJViFF7D2soP8vUEwWQyxvvCY2zI4CbluhvX0JcpNdRUXNvRHs0dGFFhy1LvipYZdsIs5Fsl9aQOyl8FdwyHoF/5VA2vrMFyUgcDCE2fi33nriltuib/wKHWnNxva6z2g0cjiHGMVrkhaaFS5hj3pPUef7xhRoA29YDk9BjxiooeTuieI9MYD0t1OpN1KVz8kk1tXzDp9mDaPVFkxXRKaYkjaYEhxp1ioewhD8X51tperZbebLdATqyBg3ecJdJWte4oKEwr/RQz31arCYtFWIa2g72JltBOM98aUigm3avD1dzL0KhE0AWEy9uB2IZaFOkcNIJS1M+xRNaNJELxBJPBpCmRo0el/vOKDfpe6hGKLHWgxCG0gpLZA5sdEoq+61MCNUUOO2VKlFK6oDk9na75vpRk7mcv8R6jVVjAzPpmaxDf4HqGmyxE3k3TIJ5yclUu1ea5JmdqtNHIm43WD05KgwbNjX3rp1/MaPA9vfROO7wCE3R2pA8nCvVfHqDpmMPzf6vUwZXAVjujWKGCf8ygUQvQR3Ak1m2fqAr03Y6MXVb0MkAGgPT2R84pn/kf2FzcrvBTVc71hs53IHAHqWwBbjaxHSijk9AucTaYYcrQ8ZcQQK0GSEzlGtJjW8yTfXLQkrV3f79QyuvoW+KGMAlCDusP2yjQ4vJgkwoazctvdKI51Dtv2P6wIatY1Fx3iurKKbP4TAd/cipdvZFnasfDBIdy2FGwGHjIasBj8llsiDoE3cuA8fNCJXOVNCzi8ajeGXI3oWxG+Lx+mtCSe4h4oygKKrOjEBCMf3XGNUoCGyBqpTzt2I7CWk613/8ad4zF4OEB4UKXYJIwOjU0Ch2EfNhsGT+04KmcjDGyWjys6/WqnTdW5tee3T7fKQPxnMBUQFeMQBZxnm0grc9VLuyfxftz2gP7f3TPQYTZwXWTz1be50v7d3fvbuQ00nDfhMZIrPCObd8LqB58TcL7Ih5wEzfbluIKdhjJV/MW/kkXwdNQJaEI4HJxod3ri5uT/G31AvGaeW6oxg47wo0lJzO7puGFnJ5jUY4RLrNxDGksGcHRGpw/8PWV63wVljMvvPa+K7oOgQuXLfPbtf9El/1Ex1xIyebj0vTWis0lde76sSxnQEq+xPpvQAvS+5HRJdUAVoED/g1ixPUpe/vjadwCUEYHEiS9nalpdTKRQKabpNmlpr+kO1/rHfPFkXT9RVDaaPeZpRuzFp2wDHZDuXzjKtR+6e1ewgkcqNc5tsGzR1Sl0dA9Xjb1Br9PTyIEtHq4a856noYt8GYHiW3cTTqmkSMAhCvcYpwBvQH9etsUbaWjZcmS8s9bIULou3a/ljzaGHfgqGRRyHpBoksg35y9qPamkiDxeMmAWLA4coeGse00AvyYVy27oG9cDR1yxWobXcHI1YJQ67j4T5hY/D1Vhwb1rVOQEKNjzzuXv7NaVwdhzvJSmL9Z5a3XiSw7PiFin6U3lFOKcRbbT0qC/dobU12JwrQi8ZYNg0GjTEDX1vFqdEtIEXXNTdhFjCfe7L8XZRKeW/uTRMS5Mo+jRx+o7L6i6mrnxcn+b8VUzUFN+ZR2iTl+YiBesPERhFYeuowbtHHIPdvMuzm97g5UlTp/hbM0YytMDleS4YTIDUktMFA6STGg6mL3zBAAxq0EFyJKKm64FtFfXqiFyD4+g9Oi4l3MGGrLNFxMzwF0aWtwobMWPsQH1Egu8RpN02jHxrdlV8ac1AxWN6BgpZncDpuB+wmrzA40TJJ7aXWKDuuQH2Bni113ZYuaqivMW29UjJm38zdmAxd+gafOS8JQBuxEQMuKN592QlxSsT4tmMhc+nrE957cN/zcJnNLeVPiwnqMiLOfRdBxvXLOWV09qO1wxi+nZ95TCvfE4vIpmEF8catPnKr6Jwi8y78/S6BGzVNf1wzrZbIAP24hV0VUZUiDH5C4yWNGzQogVR75mFQwWiL0ggqwsaPSNYb9zKVeIhCKIOYUUKUOMnD+xecVAKTRUhz/HrY1HLQxXKrUNJ2lnorbsudDCKP8YQSCTiaP2jCVGPFSoijRxOt9wdmH4uiGnNWwFGTzL3gM1XgzwLBFlg/N4oCnBpwYNU91lOdZkeX/0Vots/0PhXM7V8w11hgooHqIY1N10fdYEKJv8iyUBQ4mnveYkHLKkTonH/lIo1WacsQXw4IgK9GQQ8wi8sUZ/tGCG7LsN8ya0b9pIugzp53MoiP4uxkryPdrcO7O/wgO/Cuu8r11oRoNMP1r6UeabDhyD0AiODk8595pzuut8zj9WtJ8q2AauKZIrgHYAgqn9N8tF+c2Aqs0+25+eIavx5cFcR7Pvjrpa9hbeXJR9xQbVJct2kC3DrU3HSf7HwANph0VsxWxezVxdSDE3zAD3W53lBNX3DpGfz47RZHib6Ku+X+gZiW7cXb8d7QRGPMyIM5KFV0QMhneTUP715rtxqpxmwhUqPv33z9TaJTulBVczCushL9AtGGlDx+lmrCcGj58rkGi440QSUUGgceEA/jRimCYwHxkvb08UGsos+FEsq3bLNn2OSXYOIH1OHNMr9H6p1/3s9xeNVk/+TbViF5odnEtw92CwNJRUkIuARaOJJyklJgkuG4/b6xKVWJivt+edfGMt6kerqSVfjWc/vMDPXUgxelEYe4ec63tUkSO4BnJI46rZVdnMghEsufXHglDXwQ40UgpAIkFVZ31u8JS5ebbbNbbUMJbczCAU/HmWFdBs9A1D6Of8q/1s278F5BKEbNhAz1u8NKa5h0uqEcqjpSv/Y6vbnx5NrJ8BEUj9F/VuodEsPUDI8cg50iaEgJejcoBJHmzl84qG3cEioxZbgJy+jdIaiK+HftOlbrA9wUDLd/fhvTeP4nUV8lhMd+bFqNgUiamfvsojb0rW44UjBiWSYFMHeOCpCFRMqZTUGRqWNjQh93v7aA/VIMBpLn7e7ay0EPMC7RfIfide+SFFU1tn93WCSzscnuiOY7I4nUL5QSmp0WdVD/ZWig2MDaV1t4dUxU8TT1faHkieErPoU8KeWMR6cYvpDzxhF1MGB+bUqyeUOt3jXP6C5e9wNRZ7qu4iMZbi2dQTybTXu6zqOYi0Y27TKNbSSBcYHRGLSnnrj381t0bOMz2YwL6boTvZhimqxt1k5JAFwIkN8mWODvyBVl4o/HN0r2T7Zasg/UhC6uLm/a5wnet0zQh6bdXGsANn0QtK+f8/kNv4sqh4BZKULBAsPUz36O92oO5UO8+vxnW+9lWVTqWru0AmtQEN0Kha2zAmyIfQ0N3fsSdx7XLV4q/PmOQBorjztDWU0wA6nPo6GCash9bHArcayEw/VUoD2RV6SRtXTL3AjPZNM/AK/I/ARMJ6CpclonewUf+HFC9Xze+ZvuqGG+5OhWAjaqzktYBW8bMCmexP2iww7tr7WxP2Jw0i3GSxP4YtbFGfXn/97N8jTrzRG9LnU1uUj9hz0v12Kkaf7Q/r7li2aY/X8YLvcjyQMzcrTp7zVCz7lMrg5ukfyotAeweoTdfD/AGAz5yEZ7ES1gK4+EEWmWVbP3/ZSuYYcDM9E/CB9CE4AWRr5kH3eHIQERO3foPMAxJEv1FJo8sNhWgtIl67a1Wq+P+53AUKvxPZmi+1xxyptWnELrD1fMM79ZZHwYS1ps37ft9Znhh9Kbk21q3HwyuWCHJT3y8xhYHlVB1+xX9PHwP4UGPfq1rvNyJr2/XL3uDO9DlH3SffotuX2y32Tdjlmy29JWVkqCXN9z7h5bbh+/3Nwx4qGxS4HeKyiD6PdqOXYjfSHT+Fa6eHMzRpTy3034zmLCVyDfg0IVfCJr4H4o6EdCAGhLJ3hf3LlfFwJqQNQtn7fhiJ/IvA7tO1N4FNpeEN8idEnE/MNfr7wbiMhijRPjK1BRvQ7HTx5gieSZl+ZFq1vLTwlVLTh/G3eX+cpWCSwp3LZ+pjnRapmandY95MQr9fdRpHqOJ2DtJyxF3Ep6SV64q+SXkYOivhObdT77YGj66Hnn0E/+L0xm1VuYeD4XDaKaM3ScBE1iBfYxdOYx5As1kb8b0jCkn2dHto0BJwYhLnpvWxuFWOe6/8blfu61Ala8Zv8gg5GaORoVvjCmN6K1J8Jwk3o4o5o8C1jV7NXMwwWSdyGM0p5k1QzgPi0f7Eb01P3Y1WiVkFz1A2+ZOAn7HNtxe1tmtxDPeu0jtkDc4Rj0u0e/AEAm+iOa3xSeN58o2i1ltWVQUJzRPG2jq1QhJ61eGKSWeYqT+7M6i9qvXiBI8tKnbNtzMmmR6r0VxYM9dZBWnTqdo0UzJdABOghDKyaOHa7BC/IYl3rIiARUYNLlao0wkmcwoSZXhPtGm6I3T1LIWXTBjTuEmAqLw01sU+Z0jdlafiN6DkWqHM/W/4Avv6IBUnaAdO+IT+DsqbVbZ/iseVBe1F1u5dVIppUXJnEr0HrQWzKvkmuDTtzrtyQpfCRzC1B1FDAvzip5IW0OzmoCOXi4VS+Jec2KQft1gDsF1+PomDKcjwDJq6KVfVAM1aruqybg+5WuoJVJS6z9MRyT/eoTi0oP9d6ON07CkjE0+UIbkYIEiVZfm9Tk1jhMNYXGelDPU85FmQusL8HYm4SiQdkDtbBFAYRpzMHdVESaxkKSYeh/MrWtwgdQtfMfUAdpbT+BaupoXaSQewFQRTXwxezdpYCzzgRFJWQpXgBoieyH/gsqOkTP7wmjf4hrrLaHQKOEjB5NjZ9OcjZdOG/Wgs4kDum584m2D/OIeJUhZnKxJ02iSJ/6apW8RjKGt55160UxZRlbsFijTWG1W6wTCN0Q6tlQcad7H9ymboOGBezk1s9lSptn/dh9xTBao21tUMbb+DuF9V1uB2GyBjLfZMfXWMJgNFtqfsptyuxplkgKEOfHWoj0wpl450L/+EzRvS2Hhn/vtAjg11qhaoZYbKxVU/Yb2I80a2FopAGflWGya8wZdRrfDqJ9KFV/1tIdctSLU86FiUThEx0mH6odvykp0ZLVhB4EVDqUTaoXScnbHhMxeGkloRPIitN9KiflXRfskdNHP1+oMThYSokp4HaCLPi2D6+LwK6Kxx3YKr6LLMDYKLvX7czyJnmUWBCocxwFz9CBGrQF9irXOIJFrRmw4m8Fx9i8Asp89weU0XkMsPWG8gzhuayOYwLFoUtisNXh
*/