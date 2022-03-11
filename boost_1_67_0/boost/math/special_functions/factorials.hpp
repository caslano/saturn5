//  Copyright John Maddock 2006, 2010.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SP_FACTORIALS_HPP
#define BOOST_MATH_SP_FACTORIALS_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/detail/unchecked_factorial.hpp>
#include <boost/array.hpp>
#ifdef BOOST_MSVC
#pragma warning(push) // Temporary until lexical cast fixed.
#pragma warning(disable: 4127 4701)
#endif
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
#include <boost/config/no_tr1/cmath.hpp>

namespace boost { namespace math
{

template <class T, class Policy>
inline T factorial(unsigned i, const Policy& pol)
{
   BOOST_STATIC_ASSERT(!boost::is_integral<T>::value);
   // factorial<unsigned int>(n) is not implemented
   // because it would overflow integral type T for too small n
   // to be useful. Use instead a floating-point type,
   // and convert to an unsigned type if essential, for example:
   // unsigned int nfac = static_cast<unsigned int>(factorial<double>(n));
   // See factorial documentation for more detail.

   BOOST_MATH_STD_USING // Aid ADL for floor.

   if(i <= max_factorial<T>::value)
      return unchecked_factorial<T>(i);
   T result = boost::math::tgamma(static_cast<T>(i+1), pol);
   if(result > tools::max_value<T>())
      return result; // Overflowed value! (But tgamma will have signalled the error already).
   return floor(result + 0.5f);
}

template <class T>
inline T factorial(unsigned i)
{
   return factorial<T>(i, policies::policy<>());
}
/*
// Can't have these in a policy enabled world?
template<>
inline float factorial<float>(unsigned i)
{
   if(i <= max_factorial<float>::value)
      return unchecked_factorial<float>(i);
   return tools::overflow_error<float>(BOOST_CURRENT_FUNCTION);
}

template<>
inline double factorial<double>(unsigned i)
{
   if(i <= max_factorial<double>::value)
      return unchecked_factorial<double>(i);
   return tools::overflow_error<double>(BOOST_CURRENT_FUNCTION);
}
*/
template <class T, class Policy>
T double_factorial(unsigned i, const Policy& pol)
{
   BOOST_STATIC_ASSERT(!boost::is_integral<T>::value);
   BOOST_MATH_STD_USING  // ADL lookup of std names
   if(i & 1)
   {
      // odd i:
      if(i < max_factorial<T>::value)
      {
         unsigned n = (i - 1) / 2;
         return ceil(unchecked_factorial<T>(i) / (ldexp(T(1), (int)n) * unchecked_factorial<T>(n)) - 0.5f);
      }
      //
      // Fallthrough: i is too large to use table lookup, try the
      // gamma function instead.
      //
      T result = boost::math::tgamma(static_cast<T>(i) / 2 + 1, pol) / sqrt(constants::pi<T>());
      if(ldexp(tools::max_value<T>(), -static_cast<int>(i+1) / 2) > result)
         return ceil(result * ldexp(T(1), static_cast<int>(i+1) / 2) - 0.5f);
   }
   else
   {
      // even i:
      unsigned n = i / 2;
      T result = factorial<T>(n, pol);
      if(ldexp(tools::max_value<T>(), -(int)n) > result)
         return result * ldexp(T(1), (int)n);
   }
   //
   // If we fall through to here then the result is infinite:
   //
   return policies::raise_overflow_error<T>("boost::math::double_factorial<%1%>(unsigned)", 0, pol);
}

template <class T>
inline T double_factorial(unsigned i)
{
   return double_factorial<T>(i, policies::policy<>());
}

namespace detail{

template <class T, class Policy>
T rising_factorial_imp(T x, int n, const Policy& pol)
{
   BOOST_STATIC_ASSERT(!boost::is_integral<T>::value);
   if(x < 0)
   {
      //
      // For x less than zero, we really have a falling
      // factorial, modulo a possible change of sign.
      //
      // Note that the falling factorial isn't defined
      // for negative n, so we'll get rid of that case
      // first:
      //
      bool inv = false;
      if(n < 0)
      {
         x += n;
         n = -n;
         inv = true;
      }
      T result = ((n&1) ? -1 : 1) * falling_factorial(-x, n, pol);
      if(inv)
         result = 1 / result;
      return result;
   }
   if(n == 0)
      return 1;
   if(x == 0)
   {
      if(n < 0)
         return -boost::math::tgamma_delta_ratio(x + 1, static_cast<T>(-n), pol);
      else
         return 0;
   }
   if((x < 1) && (x + n < 0))
   {
      T val = boost::math::tgamma_delta_ratio(1 - x, static_cast<T>(-n), pol);
      return (n & 1) ? T(-val) : val;
   }
   //
   // We don't optimise this for small n, because
   // tgamma_delta_ratio is already optimised for that
   // use case:
   //
   return 1 / boost::math::tgamma_delta_ratio(x, static_cast<T>(n), pol);
}

template <class T, class Policy>
inline T falling_factorial_imp(T x, unsigned n, const Policy& pol)
{
   BOOST_STATIC_ASSERT(!boost::is_integral<T>::value);
   BOOST_MATH_STD_USING // ADL of std names
   if(x == 0)
      return 0;
   if(x < 0)
   {
      //
      // For x < 0 we really have a rising factorial
      // modulo a possible change of sign:
      //
      return (n&1 ? -1 : 1) * rising_factorial(-x, n, pol);
   }
   if(n == 0)
      return 1;
   if(x < 0.5f)
   {
      //
      // 1 + x below will throw away digits, so split up calculation:
      //
      if(n > max_factorial<T>::value - 2)
      {
         // If the two end of the range are far apart we have a ratio of two very large
         // numbers, split the calculation up into two blocks:
         T t1 = x * boost::math::falling_factorial(x - 1, max_factorial<T>::value - 2);
         T t2 = boost::math::falling_factorial(x - max_factorial<T>::value + 1, n - max_factorial<T>::value + 1);
         if(tools::max_value<T>() / fabs(t1) < fabs(t2))
            return boost::math::sign(t1) * boost::math::sign(t2) * policies::raise_overflow_error<T>("boost::math::falling_factorial<%1%>", 0, pol);
         return t1 * t2;
      }
      return x * boost::math::falling_factorial(x - 1, n - 1);
   }
   if(x <= n - 1)
   {
      //
      // x+1-n will be negative and tgamma_delta_ratio won't
      // handle it, split the product up into three parts:
      //
      T xp1 = x + 1;
      unsigned n2 = itrunc((T)floor(xp1), pol);
      if(n2 == xp1)
         return 0;
      T result = boost::math::tgamma_delta_ratio(xp1, -static_cast<T>(n2), pol);
      x -= n2;
      result *= x;
      ++n2;
      if(n2 < n)
         result *= falling_factorial(x - 1, n - n2, pol);
      return result;
   }
   //
   // Simple case: just the ratio of two
   // (positive argument) gamma functions.
   // Note that we don't optimise this for small n,
   // because tgamma_delta_ratio is already optimised
   // for that use case:
   //
   return boost::math::tgamma_delta_ratio(x + 1, -static_cast<T>(n), pol);
}

} // namespace detail

template <class RT>
inline typename tools::promote_args<RT>::type
   falling_factorial(RT x, unsigned n)
{
   typedef typename tools::promote_args<RT>::type result_type;
   return detail::falling_factorial_imp(
      static_cast<result_type>(x), n, policies::policy<>());
}

template <class RT, class Policy>
inline typename tools::promote_args<RT>::type
   falling_factorial(RT x, unsigned n, const Policy& pol)
{
   typedef typename tools::promote_args<RT>::type result_type;
   return detail::falling_factorial_imp(
      static_cast<result_type>(x), n, pol);
}

template <class RT>
inline typename tools::promote_args<RT>::type
   rising_factorial(RT x, int n)
{
   typedef typename tools::promote_args<RT>::type result_type;
   return detail::rising_factorial_imp(
      static_cast<result_type>(x), n, policies::policy<>());
}

template <class RT, class Policy>
inline typename tools::promote_args<RT>::type
   rising_factorial(RT x, int n, const Policy& pol)
{
   typedef typename tools::promote_args<RT>::type result_type;
   return detail::rising_factorial_imp(
      static_cast<result_type>(x), n, pol);
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SP_FACTORIALS_HPP


/* factorials.hpp
jCpdVtWDMi9KYuUNJ1rvUKbydpSnZTCP5LRotecW/ELmgM+q2mYvr6a1fGBIsC+YDGTrXvSxaBGoFB7h8+aDUXq+FIWGLzpzFn+TLYlEs7wtaRiNhNCVXhj4CqUpaRHG5Kar/ahuwLqyL5alGzQy2EZNIbZZtyiSpVGTi6EgQ9OasFROCI8dQUAEwMvw/c8evEdyaKdYLLB1Bm2AKU2scUcgXbXh+xLCSOhLh5R2CH2FRKLyxqQ1SHM/PZLGlhDe3F/gfEMJO/YRRQgYwvxAJr3iBqcpCf6M/2AoDbNBkx+SUkDFvwxBRvnP1tSPp5YfGb1vuESQUTH9/cJL8GNrKLRy8ojqwryZ8PHt1vdnr9O2ukpVsyho4CxSwCyn2KrGKa7SMXjfV+dD8NFJwMNrXVfZqyfwTTceM9sZsv1kX0+gd5iZPFNB/ZFhK5X/CXQYEzg1gtvz2/kW9VElxGUE4oKivWbzOwTa8ER1NVzXRjR5SegfCU+Nt9SJbNxAApQVWAeAOH4WTQtgf2VO0uULTPaVAQRn4B8RR3zAQepJlC8BOQpyok5h0EOpyeVtxwl5nyWa/E8bFtTO1Z5TxEJr16+7Ia94xBeR+Y92YAfv5UkVRX5bOP9x+uvSdyo4mNhjFA1/rXpmDHlo15+EnMi5H6HZSowFJuuYbw6+po89qdW87eKr558Z2yCJyZ9NUcrrZcoeqCwPFrP1sx5vBhhapUuAecBLVpzpvaWog8kKPX9bJ9p5HdXKJuX9QtWETZIwHIhNidtSB1mVTSEC9PBNXm69yKV5T3VQrOjIGMSeUHh7GLRX04Xe6+lICvo7JOz0dWf8leQUwxJVo4JWGpvj+xqomE/ealmVVWAsUUv4clYl5uRDdalrlsunk4x9D8J0IXXq06MKNkmnSp7G4h4PUoMh3hxbiubth8rOdP/EMeX91rA2Or1A9GgHsyC1VhV7UGk4H6ei0x/1NksEekQ4G0uevsqbIQjJp+ubQbh0uT+UwBqSGlxiqYYsHNw+h3rVE4xGU1/llXYTMvuDREpQPCOO9TU0jPU9ljVdcaFqW6wokl6VN1kCwNUTf39eBTCkG3DAZypii/YhKh6AxAeOKEQ0zZtCvesjEippZXhiGvKui+yGzjSCO254XRnkGhwEe/+sJGw9vaneEi71DeUcBcaGCpg6/Lo3f9qg04zZCJSGbEDpFEiTl5+C6PJrPqzEzf65IT8P8j5SAWGledOQAR3iC5kwWo3v5cknnMMDgeYd/Z6VWnrt8ijJGWOii8gvUu5LQmJscmpixUeF34BjunmsXGa1L3upOGgfsWGM9CStqi6m88O6oJ92YQbz4927o1j67kqoBUsO9NGIJ2wJRlQ5+uOVerAYNg211SDuCBTpVBN1q0sfxbmknpDUihJc+TiC5/MhSDRWmiCN2TRghL48AJCPZ+GucOJDqHHwIcVKs9vSOavwG6UvFPpnZjsfy0ADlDE2oRjhBMEIhAwXwwvowEJvc5RVJ/q4nBKKSBcCL9ouNL5EIdyaO1cSxkvXBZep3U/u6UZaduNGMoje2+tFSx4yiZ+QhwmuH8iSnMEQ6tPQgjdkFyoacaM3i0SgzRqAFIavfXLMMnB6lHrTkKmCPx0phcsp6M5uEu+10+0RQxdE1snXARcizl37x3TUdg+WUqaEWVZMdrr6p71EZr1rjU//LHbntfTmkZxTQAmIimN/3iBlWj+WGwbZcP2yQx7fTzESsQYMHVIIzbpBHZIf13CHQyAiurvNb06c7sfz2nx37x9arxlO3BYIR3QgpKCeYHpcfurDCfxVPRZ+a4pznGmnchgbo/RQ2rkCosX03aWqahqRWS9qHz08l+VHJQ2Sgb9eVr1gzU7bltt1y0Cl/fbOEpnqST16lVO/5zU8esxfrxLM8zNEpQ69sHR8HydV2RTuCWM9U1vpehOwQyu1JTnINDDMy4Jal25mvjPlEbC4To38Nhoe53qLkZmtJINGmhfmuhmn9GsjTszXc4Wjo6/XthlDVKrxpvVKPfODslNU1w72iXqPnpcxXIMXI+Hf2vZ1maef7Er2lHZmb071x5HdVH7BRB88kwFEwHirOsgq/8XExXRAsnAdKvmA8dTZt+oxebnzmF5dmAxWrrslNM4ybUtATTU+Qkv4gqrqpPn7cd6PD28t86OFhUjauV7gOIMZp5JizQD93oI1tSbp+d19JNRqUEyvKrdwLQoJRLIkU6zP4xIYjNFq/uUxycxXytm8gUg9SsnXmO0cCIQBxb/qFX6IVJC0t34uet4ukUibdswNJGtiXR8uY9n4L2lJtvL982v5HgFlWou3mUXA/qoPBKOAXrLPU6NxHZJ6p8KT+AE8du/ct22gTC3nAGHjIjHJYpYQMzwEw8Qv9EnIon01fT+7BZP8kbFnNLn4OHhpsLtUU8UcUL9Kvl1DWhfN16MJdXxAAjAT7YdKq6XFXEjyJlb5yeZy/CLeg5a+PftExeF9wD9EinRUoYqGgPFCDD6iAwZdWZE9h6zUR9w3gdW+mN9CQ1upjCzwFMAqMAkW2pyNwb7lPnDQPrRDdL9EwwGEX/ChVNRh48ldHmeJRyQNzXHRcepynXFIhfqSajyVmdU9NATzQ7EPhKZfP63xFRlZ1JuEBmepDIUo4B+HKqwHhHaTZCLxWmK4xB9ny9qpAIpmYUIQ8ROcmDIcCfeAOAJ6X70cRvEVR5wQngCe3KWAdo0FZ7xMl0xNIhMlq+4OmVgmWeJ3RUdEDpIeOonCygdaG6rdis99yCpwMJIiZfDHlBn/cMx0+7k4eXRrE6xT0r2A+4x8GgMfS7RggCRgTHNFkuJVRIC4UhZw9XZS7e7RN6PMjI8rzkYpCy+Qv0lQHAU+gAEkL8vPsE6qWofOBsbDKLlYoHoCnqp61yWKXz9C5GAxQzsyoDyWb8k/dvANzwsOhM4/Fl7f+4v4o/LcuSnCLOd36yGOMRaqToAp4WIClAEPQR4xNERXHcCdO9Tcx9/nHjkPVc2M7KkiVJmMLKyzT51ekWsmd+OhhUP5Oa+L16cE6gsWRTgbOix5DDn7+l4Eriwfw2UxLCjirBYYpLMFvXENtIgzsXCnhnThkixsAgnVfl82nakkUjobuQg0LyrqtgwSyZJywmAKowfkIIgSjAPUynRNfzjgZcALEjoYukC1U8fh2MhDSOQUOVDKOjnqDbx+jAJbB2/DoZujm/hL9W6Z+Ul18lZzxVfWDyngSOx9l58dYwHF5TGEG+CKb3Ye4ecIgcL6T6uBfPMGwGDIwgBMQ6xflSCDjuiaOxL8HOyyT1tG7u/JLlZLPjHq2+ZjAgFvRF7m6mjayL9nn48t2uD1qslP7OtMqYSm54GSjmuCCp11zToX9jFaVfwrbWBJWc8645jKsY8DHMgvf5ZYx8RX5R+IfiD1hIShCZFbBxRDmnuHrE3ucvLbiMlYKPmKc6N7HlXTpkkhsgky/udrL9CFcNTk9N1H/plS4thzAC/uyPcwIlVt5ZsC09hWjUlZefc2wZGl75FTqQIxc7vpy6r6FSzyjZL/Vqgw2LCjtLsrd0NBOdPI868U2nWhOZoCY4Ol1QAHJEAe14RimXeyQkAiK1QFrld1WFhgpRh9h3eNDKYRtixhx66Y3YI4D4SGov1iIvlnzw2jKYIFcpCZ+8bmyk7SxD/bjdVnBcaNuReU85XQXg348W5DZ8QieTfG6JkG+l6LxRqIHjExF7/0t2MPworH9fEgfyZ+nL9KbRXhX/GGGuDXLfREzIzasWj6DUQIerMr8HW6peSdeQBf2W07YUtr/xdPL7krGs7kJGjCe2AUGw2Fmw07lnxTmxaM5N0s5B+u9w/encEHDJbbXqnQL1pobe4GHI3L5SVf10LV7DyoTcBrPHGXealKemyrjnS7dCCNqttOVfye5SdN0JpJCPOngUgJwM4jGMIyc6d6A0DBcQzVcYt5uWZcgpo5fr086yqkSq88t4+yLsk7BGgbISrDIcgtYKQIwY6p07UFJzM8BP9eXieq8qUV4rgFWeHjlJLPqDrTzGPhjh6c60y7QeEtiQnSZanTy/VJPwBJukc2keEXPz/Jh+c3mROdWIWMiER8Ag5iK+vaFRZcompnfuHW73OvklccGI8G1sJaADZmzOka3eTfIYkGE8v6querdWbXo731yVfzuSUDfIebd74bz3nvhCLyAOhWfL7DWODAbBX9BySYjrmipYomm8UYPsUKq/tVL+JVV9a5zLHMzFpzQ0ljNNPhLDXC/puQOBSNC2GOuqkD7+xznE5JRDnwR8r2hpHI1cHzqwKtq0QTincPQGnNEAzyYAj24uP/jG/o18uJTs/ieRUnSmI/vTQo2oUuDkp2X9cMkHXExO4bfCCVAHNB76XxNhyck3uedl8GQYShR9pPOUMDblFN1lBH0BbU62rAQfjKcoUdwpGrPZeHKN8HWSyoJls07x4uswo+jY5FTDOuDS8daPKHdeECebJVfPaDRNN7TCjfK9jqggEvGGmOqu+z+TqxwYBtgYFNNNqNCgvu2VmCb6cQs9fv4opBpds1haH4jBwqYPvzHANsKioNaonvwGSdvteqeGynNrBfcNlsovhs20pXAGBD8GlwF6zvHLNFmCCdGqp6jPfI+oHR6/67VKZ3UjcZ70nGVVOrc3FJCb/vUc0+LEtRRmqoV5GfQ/S+oNqzeTto4TZOHMPrC+lAcNLu1zu5DMChfeWdrC5AwvsfZ0gH6SfUL4sfQP7h1AeCkA4UDy7g/hpS8hHvX/9dAtz/gUC5Q6P7KUbetLTAExwKnRHer2ACRzv7OyEpO8K8FmLfykjxGezfG1dg0vPZmitYFwdfzVTys4gWAiLIE9QVhHBWuoQA56BR2gQeohSl2MTbHIFLxJIKIUrhMYwbueXLAkL4+8XymLPOvWb+Hv6NfuP6DkfJLju5Bk9OmuKV/BuHDRL8e67VW9ZKlvP9DNlK9bmdDzwAZ0VxZJguaFvvgysggKYnGZuNKtEM3Iz4mpwMjcp+XvbNJfuMTCzX7pbe/ncHyneOhpD/v2NLp6s0nlPWjUIZUrvWGK/n3l3Lmn+/1gSROdZIkRFTUTQrtZeSpOAe89qNMAQIvwuhea3fB8g0ZiwP9aveLgQdPD496576/37eSQ31/Harj7Th32jioh/Aoe9gqsr5AFRI79MYKjAkTlv7+TSxQRt8PJ5wC5bkb4Bvro8E+dqAzwKAPBzW3ZpdUcVuYzacj5717Fi+AhEZPGcTPR7E2YbPmQyvw6tVowT/infLmjJNOVGQFJX9zbCuKQ+zy+qKW1foN3aO1pSEXTumiKtPGp/ij3RcFc33LOgSKPtj0chHpYMCI0hDQ8Z0c0BHnS6fdvh7DmD6v2xEOOPP5fF3bc++FkaGF8+1tJeszeJ70XPXnqW8v0z4UYzue84C+e7sTHWdcLyXjQcWLOU+HRxCYxv6ispOwDmN20BFuR+sFp8Hozcag0aQfmuABvteQ69x5mWxjjk+nXOUUPVy16+4NMyRsLBlOZTApGxgRd/xSOqQF4//hEDM/nEt2gGzW4oW9QD1AGMxfU129trqwKlK6mumX5ahHGzHobH/utHG3eDmUASXQQklJiPMMoR3UR3IbO8c9exOUp5Nvive1Uup/JHNfIIEjiDTqse/GFcNZHqbCsuGZvYnxvOLo6rI5+CD+QhZQClAeqAohiSyLHi02IOTgzkrfg1x4uFkg6ycYW5p32UYMrgMGNUPhxVnr+dPZ0yivcHnSSY9tCpKF5RVLntzv1aDYDzhCMxwxIGdL+MBSvalRjgebRhtuw82zX9Tf3OXengO9XkkNckP95q7pdwQXJYtqZEng4tQjeJukDgvhAoxC0EIMRNAvsAjfZbfD7mygMI9SLvicZs7RwMEJWKod3lAaPSBx3CCZxcW53TR6BtbizGXrwDc8SoIbehNZbROJ/n6QBQAAqIkH290jG7RlMnFxM2VrtF84hIzloD5gJPyrxyDI/4OvkzxN1yO/JSBcB1im6xMuXTblS4E1AoM97YgX6gdMXh0ywY4RVxPcu8pJfWhlxvBMXp4OVQHo4/Xw6BUOpH+f1PImWSaJn/jvtW5bRVsD3Re/gaBLlug+Pqyosr5RQe+rD3EQyaiXz/0xBBlhKLUVSvA/0tljPRYq06uyDHxxYoDCPQLLWBB8ntglrCG7ZXlT1gas8SpdSaUANao506ko5eDGwGDGHKAYx4C3x67GSHCsX1crLpIUcLhJ/k74Z54Qrg4NNukmEsBq03tph4ySwQNH2QWZ1RNn3Kjnfgq7Valyjd6PcH2dlOY6EYNQFrDBPSAT3NQSXTefiH2wrKKIILIrRQLN4TnLX/KNmRlgxT+5HgTMavX9u2k30wznD22HEn5xV7GvVCviMevrEy2PG1JWnzmbIEYxA8WnURXigThXJoPq1gwabjXvc4jYbSaEQipCiplIjok+JftntSUYiPvaQGQ7iwKA7pyStVsS4kqAELlanEgBeyTTi/totKSX+yTo5r9eNcIu63Zuwpv8IYfG1f9rBXBeFGnUfzBMh2WwaUQ+63z+ccodJPQQ7dQkR68iNmmRxKhV5Udy69RFs3YJJ5u3sa8GfIXhdGEeILCc4n5uAa8XPq8y9EnGt4azMSO1THN70xG9p4bOTI1kxSXRCuG/qtKB156Ojaji0aXRWpuywj3Sf1cCzaTHuZn713S16XVHLZocABbY0zwlC8PUo+8mFtq22cKCH2Erv8ghRMEtRV/vVUno6v4TrFCPQPqfXm7JWDMat4PxDGPsge0nMinn/IMtnsV/iOQruXEmhDLHS+1cfNVICah01/syJdwst1+3hRJEKQ2vnWqKEAJnsqSsSo5sCjOuOUjcbAUA/3tGDK5/WaAqTzFGIYosZWvpj5bhhDgq0OCcwpPFkrLW5SxbJd80B/xPh0yB4E5jzcxQFSF/4oHHfFO2z9tGM+voPqZskbf+QG5PL7gfTmwKyqwkHoFMJeKrAGL71qOkQ6szub+sR3AGHBHABQs69Nobt5clRV6Exn/ZUcPlNEmmASfh5iqgyetsW4Lj7DK45iwmPpuny2fFx1TadvnNRrIyFvIUy3EvUkOqWNzidvtDlpOnjrbrM+Rx/7nGWb+lbP73YF5gTN+Dpx28voSTZqZFj0HPVT3lV/i01UYh6c+PVddDeowcFbwSmxBb9aUs81yB+wCDKfIOgn7FT1rRbmWBHFTG44XLybFxP7ng8OTsVC23DyLGTifIuiyXf/8/ZqRNs9HlhS5UiCeAnzLp93JwNec0VJ1mGUXu7Jq46oYrQA+qwP60Xt2FcVyORrW2Q0N1Yv53NH1+xrcPyz/1ZnlKxqjNSxx9irnNpWoav5dWuaaOEh/TWPkL/b/QQlZRLJR55LEF4sQznEpQ3TQJXw81FjYYjXklXWC6EwMj6GJIQJxtuCIc3FqYTas+Ei5WWKnL091vcEwf3OfrXpybJO7XBevXOhiuO8C7iWjek4Rw2IA56CSnqMezch8jOdIJmGj39tZDhNA6EXkCil/wWIWG4UYbF5zkcx/DfRRJg/zgdHRYTd9xPlSJY5q8J51QymI22t7N0FGO7IZ+7wh7FzD5KgsAxJr8jMgW8uy3CQJaGVmeAcEiiAiLgIcMbI+CCqz+PD5nYt2vnje2mTpcWvR1KJzP5aQl/UprT1AVAznuuoFChNsWB19lJWMql6xlXA1KuqJl9zBInEu+BstoE3k1D/u+Sd4tUVPR0KQDcPSlkU7AOntHCHwC8c/z+PAcpqMUG/4lcgQfeNSYqK3bJXwcnZ2mNoS4b71jw/kH8VSEAlpwIahw169RPOQki8pLYMYjaXNWuZ8ykUhYkBeD2xOib3K1wJVFzUfexOqoqFFyfRh5okZGiekxt1kdO+mtXUpw1/RsPAlvZie8+fHNCQmmJtSQe0IOyquhEdquQFHxZjmVjygqinruNfPNAwkkjbAxkfnzzzKyweAAIBDSwEAgP9/mQs8ux1Y3tnrAfIZnyZISyBmkuho2XqM6RKc1j84Gg/eQizPAP+DVkXdn8cO6ZjhFl7g6dh0zjWVYG51l13eERpoyti6wKDRRmFUFuum+V8ta4vf2znBWSLBmkX8atJzw48SW5Cxz91kkPk28Cq5DVoPxaaBXi5PGIV0hTuW1HYYExcR//CAIS0cLMGOp7nWeNWVaYNfd1r9VvGHq/ceQnYWrah1+BsN/W7uc17fg19g1qLo4HLGIvyqTcNGcYrIXM84ralaVQNh3DU3WewSBV7o5Z94a5PvTh7s/0QuPi8Xk0/CUsUCWSw4b9xq5+Ld4+AFip8mGAJOkYaljo8UCFJ4gozWBRbIgLjwit7Cjb+VCvJ2PinHTDLENBKhMl9m8vn5sA5eXuQ+iGAkILLzUw/+n3zNpicIDHaz4GeOp1qeOe5Lrb80nP/o9HozYM+9XNs5JYyAGvEr2Kk40M+YHkf2QXA2WLvKMBNnFqrp/thce/EpLWOj+CqiyVRoCjiIV4vt5HKDKHvYcv0o+nY434dW/EHngvDWjDZZegT0FueX8LUkogjGAq88DtE4J3+QcyVYGD6/H34z1tzz71gzNHX6pEAtQAWMKEihsdN2GufRWviEPw5v1kQ/CFsNH/NI3UAN3RdJW8BHlU+FSzzgu6L30oslxdsjOxwMW+Foa5yux0cP4no4abjAPIgrgCAv38XkdKbR4hBvl8jD5xOvh5QW0qqpZKIEkW0QQ03DkCi8rZd/3frfH4Pm3ThnG3xY3/tmj3OJsfRLD3FRiQkXi1sNuSg8+nOiFeX/E4IfV9zCYVAc20+3TyhPSJtjVyZ/E4N1rQCygz6uJTwMiiQdNXnN8+XCgRML0YzZt+h1/Tp71TNXZMXq0arJ3At6bxSI9VWBnUt1dH/WAX7/WgHIzvd70P8oywE/8WGEZFAZteOQ2Wj6gjwahKPaR5J7WOoxt3wFs4Ej2aLLhKE5bK3oHUMmK5EaWjD8qwSL+Ri1liHqECxAeEvRGsIs6QeHNQwO8Zgh5COQcWgAQ8nu24aNV4eoU7wv0Nx7OBVVQVp5yFRb9kXoZyjfVou6vxXVz/+Gu5r55wPeUcVCwBcY3J/dpj04ilt62uvhEdXRqNCpi6LDD8tcYAlQjgUzimTyBG6Hbpq3vqXNo44DwAuoe3z5jHS//QE=
*/