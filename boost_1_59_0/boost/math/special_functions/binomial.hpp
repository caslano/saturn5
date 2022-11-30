//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SF_BINOMIAL_HPP
#define BOOST_MATH_SF_BINOMIAL_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <boost/math/special_functions/beta.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <type_traits>

namespace boost{ namespace math{

template <class T, class Policy>
T binomial_coefficient(unsigned n, unsigned k, const Policy& pol)
{
   static_assert(!std::is_integral<T>::value, "Type T must not be an integral type");
   BOOST_MATH_STD_USING
   static const char* function = "boost::math::binomial_coefficient<%1%>(unsigned, unsigned)";
   if(k > n)
      return policies::raise_domain_error<T>(
         function, 
         "The binomial coefficient is undefined for k > n, but got k = %1%.",
         static_cast<T>(k), pol);
   T result;
   if((k == 0) || (k == n))
      return static_cast<T>(1);
   if((k == 1) || (k == n-1))
      return static_cast<T>(n);

   if(n <= max_factorial<T>::value)
   {
      // Use fast table lookup:
      result = unchecked_factorial<T>(n);
      result /= unchecked_factorial<T>(n-k);
      result /= unchecked_factorial<T>(k);
   }
   else
   {
      // Use the beta function:
      if(k < n - k)
         result = k * beta(static_cast<T>(k), static_cast<T>(n-k+1), pol);
      else
         result = (n - k) * beta(static_cast<T>(k+1), static_cast<T>(n-k), pol);
      if(result == 0)
         return policies::raise_overflow_error<T>(function, 0, pol);
      result = 1 / result;
   }
   // convert to nearest integer:
   return ceil(result - 0.5f);
}
//
// Type float can only store the first 35 factorials, in order to
// increase the chance that we can use a table driven implementation
// we'll promote to double:
//
template <>
inline float binomial_coefficient<float, policies::policy<> >(unsigned n, unsigned k, const policies::policy<>&)
{
   typedef policies::normalise<
       policies::policy<>,
       policies::promote_float<true>,
       policies::promote_double<false>,
       policies::discrete_quantile<>,
       policies::assert_undefined<> >::type forwarding_policy;
   return policies::checked_narrowing_cast<float, forwarding_policy>(binomial_coefficient<double>(n, k, forwarding_policy()), "boost::math::binomial_coefficient<%1%>(unsigned,unsigned)");
}

template <class T>
inline T binomial_coefficient(unsigned n, unsigned k)
{
   return binomial_coefficient<T>(n, k, policies::policy<>());
}

} // namespace math
} // namespace boost


#endif // BOOST_MATH_SF_BINOMIAL_HPP




/* binomial.hpp
htYTQeu0mOk/W2p4ViEm6pavCQgZZCYcG20AgrRYLbJBJZJ3laAzKO98BGshk9hHhvtTpUT3+LW4X351lTqLw1hjbnK+8zKR6xqt2bLBVvvvJ6tsTFe9p8ANsPYw/Gdn2F8rSZh3LtYgQM4ypJzKKRhI9SlG0Jrf24ppGTsb6wPQHZavnC62YCss959RvAeHujMEG3GsTOwAMRFFVxRusVJM0pNO/1zazcWx86o6C8fzj9LKMtbAhDqqok1GZnW/FNOoWbCNzGZyV668aKt4F8S6sCkcb3NPtJair3kK1yRMiAkKxDQbvjTuRzMApsKQ2kRdjxVjreKSpxVyIhOtVwYVszUQf2N56md0thGoRKO63aNzcTDQ5INCL/fmVS8jqp2PCFuLrzkwxIiKH0oNC9GUsYRWgQVNJ5eIbMwBA8903kSH/NH2NfBlxqSEKGMi4UcNxQZJrjq6kFSzNeflpX2OTbdo+xvhtvJS4iZQdMGZRfwM6ggVWJxw1MqTJtoET+LuobQm7khETLtCyTMvQykSqVF6p7dOvp5WiYI2n4hg2UDXkybQSnahSZZ+MO76UPbrrVOkLYj+mkq9T5zCyrKDKTGSEIudKGQ9QxDhwjd7caGvxLaWOQtJOiZk8kI7CobjL3WKT5IiK2dgOYjl+eiq2UabCpo+D58H8rtC+ojFfXa4MOm/QEEOHKAPNtJp5UCaQZGPTtHILfUqx8rpQKlwEzYz0ZyuJfZHSS0z4B70QbfSzKIY0YqGKcryFZltnPUfU61gw7VGHTQGXGBVs3G5iUFl440bbtsy1ZZafuHNDNjWUlP11piXLai9ZUWKhhIH2IW1WDLuaBjOobynSm+4tpeiGaomKEeTh13tmgqSRkmx+jLpZ7iG/DHkBHD7RMLLmnqjogs+B5twkuiOeQDHO3xVEWE6qXfDNO862tCtA6Xqg7fwZnJIzVTS9OlJ7jYRjTydbmotvmh3OUTdp/brgW+Y/677euYYA2EGZLKaGT1C96y+KVzdixyn30qarYLsuj4WEIqJ+4cCyDUXSL+LaVq+AoclIT5i2lqzTERkjvu1Qxh65eSjsi/Y0ovdcQ0VJ6S/VOw95hzuclguqfQKCKEzlx0zz7WyStzjbEcnVHcW19iUAx04L02U07qtlawXQNpJ7uWMPgDZZqZR/sPgdJftkUyvGXgYcSd4+I+jSVKJL9XjsHDB1OLj5MFda1KUC8QDM251MKnATL1zrPDkTUPIqvTm5np7yoSHsQPwwWLp6qVAHrO8OAVxSii7/fi5OuiocHmBAGb5+YWVN5oN69swN+X8y1t4yODROlsS5vreRRaP7zDFRRtjZtBxlBLrTgI6bnQO13YCkYpatGK5pcDc1l3LG0ObTOSsbYGbHemGT81IgWSfgu3ZTK7VYoHxJofK0CzjZA2Bdp4Jwu4qvEeY9d/SlbDQiyk5aaCLTHoGZpMUNmm8aBYJx1FSINCryslwUfXogaTBNz8DPySg9w0XW4fLdMhd5jtePNRkq1JRcI/iNL2vxsZFtndmRZY5772Ms0K1M9Qc50hg8f2HUmsNCpQh2DQKRpMDJ3bPoYd7R9tpWeDehuvYpxKTkEsI0MeIXWdeCeMEnzfyaUS1lBBi/zjid8T+zXj5lpYVHoRgpeJfWFiDsNIc4oipS1ybeGQeFuZW7OonmTTYD9fVTdGixNRYwuzakcBoVgbS5Dm9ZEm/GKrlwZ7c9hWrYAZgUMhBgIgFBU6pVFHz92gKHsfstEOzs0ua2hz3jOTGUGJWLAGu6hTWJ2G0pG6av4l2yfmSHGLJOZ7lir6gQeTTbAG9Gx/xNz2rwzPYDpCZr5GQdj99kxBQFoYJFUEnpfrZoPBZmtimmZpEqT35YIoNB8rLxy61CTRRS+Btd+LmdIUPrbAjaYt/lKiWQsbuxSn18l4sQoA5WYONIBsASe2XgiucyUO1mAgD8Iu+GcSKTcPSnExadynRohoQWLEudrD5AhoxS5e+JtP7ndtADK6ViaCpqRmVFgLHKRavAXXaXOH4CumAGnvri1DIuXxYK+7AxTjmBfaGhudhPUufRc21dc0P+hJIOWVf2nlnjfdsQfKrjtNn0hIXtuKfxQLB/IZhmdhqKk8iyy1FR6a0HspNuw+JtVeDzw8lnNAwXciCh0k54IThQC/8c5QV00oRTYq0cJcMt9dRj+4fYeKMFE7myIOKZgNW/fddwVcdKPNKuHZfiT/Zd+NCIxbptxowM3tpekg3iocp8dRePqsw60o76q1jAgQxZVtDQr319s0TG1jvdxuNb56XLyrfW5Ha1VcC6T68sL8Reu4mHUudEAtY9NPUihcWhvlo7xbUVxZYZ6H/zIkD3tGnP46iYqcERPyyBrcQNKw50xN/Y4s1EtjlFV04jAXSevAxC2ksR1babcIgGyu29B9D5o/rXtvU/fMrdO+sfJaN3FnJlWxs58DaYTDPb7E+SBey9L6XWuaOXOfN9LFP0P3+dHvfrKskTFhHu+szdntvBynUeLn9EiO6C2lMAMk3e29kPtzm66D5CJWRelXgQMvl00WB/3vvuaeY0L8lo7p15LNP9b6WtOe6bJeAFqlSifZRy9SAah+o1wfBhGYBp7JhXyl6+3uZmQikEUIgowGIhrHmCA5wxRSFFZl/DGkyY3kyFDX1/zHp82No5vc/eaTN6+xa2etkI3eg7+000c0+iTPAkVGWe/dO1woji2J5f9XL/5cMpaU/7cWy2apnpgq5GO2toSkYfvMNwkh8M9bRxSk3ZXVwN+Z4IBBHtJgABGjOYzk9cMMFj/F06prOeXoksl/INvXx78R4lM/nXtW83AcKnOqA+sybHQncLR7XWzmp6xldkl8M0dwQQfnz+Jys9RFm2b+NXsZeDCrT1ZOF+XMtptJMGQpc3R28XmHoOJVPA455YcKaizy9cSnpxXss9QGL+VVTq8Q93FIW6qKdd75S/KGpZKLYxkbFWI+yA1g1vnTflFAlAU/VIgaCwx4nBanTI5IyuY0E6d6My8HetZ3K5FX7VJ55bv4wwUK4tLH7AWnlQ/ODFqp4EsmSJaw8T33mYvX6bkaJ/EFiDvFqYB59neQ+EYzvljG6sdqRGJniqPYasRkDchxhTvCTcle58teRizfi8qwFvA95NCxkYYNxliCuV7qGKAIxRVhrs1Mp9Pop372MrNkeQurlMpHdSufR4JvgCI61vB0FAJrIAA5DafVc3b7wx6ZGCoTrSYwvfzyS6U25E5/uSjETbVxgQlhKxWDTJJMMcRGdQi1++iCald31myqKH/63nc27uj+AHIu+U1Z9dxGhsJqadLjQ3nLQ49izmY+K7h/WvAXURX9fyNXtqqQLs85SggyPYNFEe4pkQsyM9pm47aAhyMz1JhDSmW2TYzh/XeErIc+2K8xxkM7asEbIMXNMP1Lir4NtUx8ep9topzq6uE9Sjibi8BS/yo9bk28JghMtgIgRyzQcIxQcDrmVu7hVtqZLiiR+w5tHZchpfgPj+JDztqGmiTNmeCQxMwhg4ax6Trsc2M+Ua6uMwelZ/1V/CTGQoEhcGO4m4zc5X3AvhWz+e07zyUAuxQ91QX96+Uh8MHwwFNBsOMYnpWOIvARVPR5bsQky7XSZf0N176KmmONthhRcpFREFqE5j1Vivdw7ZBWYFC8eqv6xHwSzAtRBy/P03Ph/LWvsGdmHK3oJQbPFQ+BeOVzLbR0uww0YwoLBnR4InEjb88jb0hZlKzqdHhMpzpb6Vl54qxKCD2IVzogldbM3o7nrROMWIQk1O9O4F7AwdNZD83fkrFvl1wJgcxIe3AMhWPZr/5HY1x9iui4+gu8N6ztzS9UenAsIdskymlonAWANgM/MdD29AZrpFzHp3xynR+m/SjnJR2jk3b4c8voqJb1sWrrKugBw6V8a6Y+QYgUnLu/nPUvAYjjabeavPfVVb1SZlzReV5/M/O7H3mcF3zkV2wQxPNjhAp4KA/oASLgzhtZTaHb5mZs0RkYXjIzPb14ox0LIbRDt6GnGo+wc33hcDZ/qWyXVbAzu+SVWSTmvKyTIbQGhaiNdwuwPug/yJtkCdKTEJrvvici7ChWfv7eirb5/vIOa9G00I8dtIHvW8msm0H10vxUcXlSXhZW7kkQBuwMBAByjs+H6RQJuokbHvDWKhTvlFOihOLEMATDv1xmQJYyaFQqsXq6JVSep0sLjd21u+VTE1q6DQ2jurMYjKdvrSEKdDTVqEdj2H3tX8zsljLIz4Ho5rTJ+DhzT715X63LiG9YvPqL+jKyi60mOnSU1jDH+POm+XdL/jskn9I28vl+O27bB5wHP+lhaX8f0ZhcT/QKVR1S3fK7d8NlezQbVxvgK99Ks7d05zVZj5HjDn70wORFLNbx8Cco7muOjIoSM6X0ysez4eKWdUxjs+eu1XlN8s0IuXp7Po0msvpBH4xLw+psCzsKxO5Yaf0Cy1feyC/JF//LCsCtV9EbsaMFjYP1zd5JQsC/vwRB3XUhFTUML8ccvSyOT/0F3Njk6oMdPCuzD+dLero+KJTRnJ6KqTIiV8+aw8d2s7dGHkhfBpcJtyWMb9GWv4dV2K9d/0L5c/66ip7mPu4fvK2vUS3xV94dP1k80qYp93Dj772tn90f+BbuZ/od/rqHix2usT7IOS9VI2J/8B1pzbOmxBfnr66BXXHvK9Vk/a2pecA16TgaXHRc/F+RVviLgFSz2Gxb9Tu82x4vvh6HrUazAagwE472HKWp0kYfuufPilit8+jCVnyj3yP98fe9OQTjnFUz8arXjbUgQY0mXvQRMsHGsZPgl3We4r9+HYJtSfQYSeDGBwQ2BVdbBwCj2GVHJpJSNc95I0C/IxYuN8L1xSaCR2JaRKIQNiXuQQxsCU7CrPBqhnMC+4Jd7hHXrikUkmVnlY68DaBEnY4jFwvB+unzGDAacoJ9busHDqOLE3ghS+p06W1BBz88+XwXJlBMbp7J6lQUB0D2rGOFecEJCQmE/f7u2XKyaWaG5HKQsoz3xcel8awJuT9rCKjbFz6397D/4KnvKx1KmjRJ3OF++zi80LvcziKVu/OqQ2q649HJGPzumNQGRjBgOMmhdxu8QS3CFva/lkuC5IQoh8jbvri321GjdujS5O8Mle1b0Qz7QfDBOvzTcACFJY9qwud5uO+RHIbQurju4SLg74YVQlruLXlRILKRpqVUwHPQKtW4j6dryyIbhrQjHRjDnyVOpNg8kXuzSXJJNJmqJMCBknpPYxQHeClaS+cOqvLQR1l4iIBJBPlBJbEZk2mL6YmXnN0Yk4k5wG0L7GXR+X3b+RlcWJpUFvKJffmpqYAvv8aLQiV5O1KzfXURMVeFiSFNBQhXGNYQXoSXovqbDSq9RIruM8cFFpshuEpcDxniVk3GKfugPeoqgRShliSkVAnOhiX9vEpf0yOjFeLPr0w8FyBkB50L/FHxEBNjejeDsAD/61olYOtT2JZDiKRbxaJS2DOLjCZgsnI7TkCGoAWyfku1/Fppv5ps+r9aI7wANtJqV/FZ6UxsLAgGSQGZgruFBpaV1ltl4zQT/vW0P8PvAdyv46C9RpElKLJxBG3oYsOiJ/3q8zZ2w+n4gq2TlvYucpJq/uy/cKmuOUC0Yf827gv+G5/PSKCa1FwqE47sz4ohjeNkqyX9jsp/peUB94Sw3gBKpBv6CVQktkgdqChF4zWA2YsEBHDNYULFWhikPF8vni66YmwkUwc4b8rsMfFgR7Oxk7kpiOxAv8Er7+ovRzgA5s0UfXyhAHV/H0xQA3EFTUMTPxNxNg3seoik5llb6MrlR0CE847cHuO+MC2LDbmF0G/UT2MTjE0YYAfwbjpAUb8OACJ5cQ/MtH5JgdRI6Z2Qt06attFdW5XhOwkhbXt+rOiRWD0tpAyXs60Eo1aZ8gNCFhdpCaTY43gCBJgFoCoOpMBxg2xNBNLreZIQqzx+QRUc7CCgAxQCJAPyxBDmCVlxPQpSbCMSYTT47actuJKrTiDVxLjIzLK73DyRKRIIutjQsXhF8GEZKNVKVK+uoURq6CiQ2axWiTjkTNkHKeJFBGOE2flSIhmXXgmEdXEeATfc/6n5K2W0f6pzrKgSUbuInRetuSl9rLxirm3dm7e/3q0esfQWWQL3dIw9ruReNY3ezScw9hbhocC6UZ511B9o4XJQBwjwQotmHXcwKGe9g+2S7vVSR/B54VQt6HpS4Ll3xkuHnb1S+JVHfdFQT7fG/33fv6waTCXwEMHiJxJ/tDATMRwg3ATCxJSlsIijfmaK4Wm/Xi8PwkylC/9AEzRDf+V6OHUGp8QVfJ0icBQAwVtIKxlIY38MbRjc0LKUl5rvzrLuWFIfnxEAW/3Cqu0SX/rcwzfhNFpNX02q3/9QlgLl70pqMVZAW999qMnkKcGwRrzMXe0Ve2UAAuFpUFS45bYD1CG8XG+oi9lIdviWwexLwltzveHNFHybibEbBjTQ4pjhUxSySIbyyt4zipK5+JMJU18dMoe1YQANAvETSXjDJQDBEueIg1/HYgCCrvepUnY9xIR0Xijmi3UXKCYV89OoFzbDBFq/I5hVR8RyZmonzO7PwBhRChrnmfr3D28t90/ghKIzQRx1SVn1Ju4qyTK9HWGIIMq0rSJvsfCUm4F12L1h/SMpAYxgqgQkfXD6En0J6DU8eGZdv5lMlWdMn7hGY/bdvfErfJ7vdfX2WTj+/x/fkiiZsWXuiCiBK1iOFiw3XhtqjkGNz/2q1EJgvvcXIBQ5U5j8td6ivk5RqyoPdlB9ex69oA5ULXsX7M+Oh/4w0EEesknQtRQ8XTFDKNPhwhU6TkrnyKYtTmDmTWfIZFESzB+pwRVZnit0FkVGkFXNWRJKFBNbjQcb199bWOCqNV5uRnO0bC3VF8Xbg44oTQC2wDMIkQucCMCHeoumxei9iZvm/eQRe7vNjLzxZRZZqgcOF7319C+BrmqTZq7WDFtSfvy+b6vgOtjd1TKfCBEvu6H1BgvVXmpWuyv1rFjDH2mRigZLrXMKc8iRlgcAppJmwINg/0UUj0NFivUSaaqk3Gy6X3rAivyUDAEhd2lEIYAD05HPDLVfbskvgKNSik99m3j2CsfUoAjXAoDjWp7OBEYr1FDDoMlQY0oBHSeQewiHRLdRo4AkMueroP/oe296El7izyBkGTSDa8Z7ElzcLqNQGJAdqxbhgEQnPztvPAYNIh6Jb/4k4g232rgR2k5UC1mH9rJV80WBhtJ3+lyuCdIxReCtoDgZR5x50ixf0JCpyusE5Ooq/oVQGUJYUvXDFhqEpIjYk4om6QSSABORvwh8HBjFnME04FhwgArgp21get3falwADyI+OF28ZuPBxZgsTLxLcXhkoqCUhAabTY0m7CeM/7e8aJvRpzQaWLOscrI8jcBLKfwTpXu7pDcrGUOe0DqRt/mPJHhIsUMg5Tv9p2kI32mbuahIK5VEFcsGDiiBJ4jfCK/RAHsi+ZX7zJkUjWOwPtvU5fuaDdwSoySPVOg0fAohFhmG5gm4aCA1rO34GbRkKzBG+0RcA4QmodX5sB/8Va9/of+MFYB4Luu+BrD3w5JppWLH4Wf9QnTVQjsSdfxUnkARf1U/h9xPICYgq/+zBH8MP
*/