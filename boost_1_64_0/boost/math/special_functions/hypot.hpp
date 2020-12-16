//  (C) Copyright John Maddock 2005-2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_HYPOT_INCLUDED
#define BOOST_MATH_HYPOT_INCLUDED

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/config.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/config/no_tr1/cmath.hpp>
#include <algorithm> // for swap

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std{ using ::sqrt; using ::fabs; }
#endif

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
T hypot_imp(T x, T y, const Policy& pol)
{
   //
   // Normalize x and y, so that both are positive and x >= y:
   //
   using std::fabs; using std::sqrt; // ADL of std names

   x = fabs(x);
   y = fabs(y);

#ifdef BOOST_MSVC
#pragma warning(push) 
#pragma warning(disable: 4127)
#endif
   // special case, see C99 Annex F:
   if(std::numeric_limits<T>::has_infinity
      && ((x == std::numeric_limits<T>::infinity())
      || (y == std::numeric_limits<T>::infinity())))
      return policies::raise_overflow_error<T>("boost::math::hypot<%1%>(%1%,%1%)", 0, pol);
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

   if(y > x)
      (std::swap)(x, y);

   if(x * tools::epsilon<T>() >= y)
      return x;

   T rat = y / x;
   return x * sqrt(1 + rat*rat);
} // template <class T> T hypot(T x, T y)

}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type 
   hypot(T1 x, T2 y)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   return detail::hypot_imp(
      static_cast<result_type>(x), static_cast<result_type>(y), policies::policy<>());
}

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type 
   hypot(T1 x, T2 y, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   return detail::hypot_imp(
      static_cast<result_type>(x), static_cast<result_type>(y), pol);
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_HYPOT_INCLUDED




/* hypot.hpp
t6cH19mwil/RK5rH84Mp4tVd5lX/e468PfcExyPhq9PxvTi6IN5XYj380DL4iY5Xk4qvLoKzn9FXHmt8e7LTu+lSx7ai19KfrxFvv6IrRPdZsP50hN7afKvn2i4+nK/P8YZgvmp/YS9X4oO34Y076bTz7Wc5lT31DY5zt8fZp1m/6pPi9190x3bwU3Ir+2a4fqx+mhfkpY7i6qf0o61w90HylHHPTYZzf2a3d4l/7+GFeGoIn1gxwXXVcVs6sqN++nPH0AP7w9Fnmofh5v87/jXZOvzwR93B+q8G6f+/i25bY/2Ny32ndhw/TRBvd/HTAepRR8KlH9E54LBFP7XFv7zXTrhjmP7Hg/hTCnsYY12wLfI43av6Y+MfEXcS2B8dq/gYz9ma31/oPm+L04vgD3FoeT4e+o3x6Q5nwJupD+gjroS/ysT3FnWHC+i66miZX7Obo+keB+MdufLLQXjXxhD9UL4/WV13oPh7Gh3yALxwcCv7e+gr+MDPP1UPOFy/yVo84SZ5+0t+oD8/84TgfoWnxdlfGR8xr2n1xmtoBL6n/+6DH2+Ng+fomHTVxh30y14J9ufixxX0tl7w+t/qlX/RVUJ0MXp7tfy28DtxfXCIn+q7bqdPZ4T5vou+cYx4MZB+J06sqGAn+GSPgXDahXD+2XhlJ/P8mXwcls/gkUbvW/1cnP3grZtVGlw3Y7dx3WE/8efwumO853D46CXjfKV4N4qdvUxn22P/oLfpgvJvSS889ijxN7pvNL1qws3qrteo62+BC+D4tDb2S38C/tDfV/Sl+d4rr6vH5cAHeb393R/sb4x+xgF4KV1v9mB6TAZclE6nP816XX3tS4MPJc6Ab+0THDnbOrSFEft5wTvDXW8ivapvjP0XxMF3rNN/RAydmR1k6YePl8d7yher6NG/q0uqJ5ZkwEWD9EtH91sQ7xcni69/sGf7BmweIc+/b72H7eqq7DxlrLxxQ5z11uWZV6wvc654+R29sTu9cA17/JC9puCHG6P9B3CD9XLjH9EXhsfNfjMkHtPvFuINg/SD7MEfX1S3+BXPGiu+xtEhp8j7a9rC1b73elHchAeXe5+FCeLSLPWzN8Rd4xY6U/6hi7Qs0T/1MT/dQa/+hz/JG4nP4DGnmRc8qrxQfPjFz5fTVZ+h105Tr1mvDnu2fiG4ryLBeHRTBzuYPX2qb5aeUjeevjTQutD6MPN+hf9uZheDo/NsPY8/44LxLVAHWsv+jfvU7+kqN8HXN4gro+GlCvU0+k32FHjjOP0sfePVEewXsBqufxZ+XGF8Wsmv3fF1/di1p/GrbfpTPsBD9JMvvIp/D6P/PwAP2Rex/DrX5Se1/CSlHD69D7/fHt1fix/BvfNHsX/8cIU6fv4ZxvE6OvpCemmyfttC49ittf1E2K/7pbe3j9kR6gQd8cSZ5mMJvesR9md+pr4asR+b/DaEbjGVbkQ/qU2MNV7qU/w43/krMvDx3fLsUvX7Hew4ut5Ia9/b96CX3YRvdMSPasVv+npuIn31R3W5O/FI7z9THb7qyJC6Pzzwm3gPB6bdDN8V0q/oR3mvifv0x/h3XGcU3Jxo//8iOObYWH1/cOBl8ia+lPSV70MS5H15rqU7vbqdPE73qL4oxn4h+MEH9LCH6Yqt6B7ZvsvfBi9M11envrPc84dedB6/Tu3v/vL9unjXv02ctX7Cfvvgh2bhFy/qU/gubD0f+nJz8PNU9Y3suXSeQ9h5f/peR3h5KRw8zLhG8P304Hma5psPde+s7/DnufKwv0tKTgiu7/zQHHFyeoz908ThTZ4Hns+HD+rg0/h9noMdzHxEnmyEG+fpo1+qjj5S3pqsfvuUfjnrQEw=
*/