//  Copyright (c) 2007 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COS_PI_HPP
#define BOOST_MATH_COS_PI_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/special_functions/trunc.hpp>
#include <boost/math/tools/promotion.hpp>
#include <boost/math/constants/constants.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
T cos_pi_imp(T x, const Policy& pol)
{
   BOOST_MATH_STD_USING // ADL of std names
   // cos of pi*x:
   bool invert = false;
   if(fabs(x) < 0.25)
      return cos(constants::pi<T>() * x);

   if(x < 0)
   {
      x = -x;
   }
   T rem = floor(x);
   if(iconvert(rem, pol) & 1)
      invert = !invert;
   rem = x - rem;
   if(rem > 0.5f)
   {
      rem = 1 - rem;
      invert = !invert;
   }
   if(rem == 0.5f)
      return 0;
   
   if(rem > 0.25f)
   {
      rem = 0.5f - rem;
      rem = sin(constants::pi<T>() * rem);
   }
   else
      rem = cos(constants::pi<T>() * rem);
   return invert ? T(-rem) : rem;
}

} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type cos_pi(T x, const Policy&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<>,
      // We want to ignore overflows since the result is in [-1,1] and the 
      // check slows the code down considerably.
      policies::overflow_error<policies::ignore_error> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, forwarding_policy>(boost::math::detail::cos_pi_imp<value_type>(x, forwarding_policy()), "cos_pi");
}

template <class T>
inline typename tools::promote_args<T>::type cos_pi(T x)
{
   return boost::math::cos_pi(x, policies::policy<>());
}

} // namespace math
} // namespace boost
#endif


/* cos_pi.hpp
n+TZgZMvRI73fJ+fe03Q4bsKnb72K8f1kn6CY48a5RI456+Mo04GeEXB4fehdP2f+iNfP6+HmMeQ81udV/P8mv1V67QOtLtdb7HT5w+cj8In+w74vlX64Zl5C/2Odb3a372+ox6D8RWcxyXfBx/UMUFvkNYp2KOp62ReEhz/Js8EXs6l8f/l3mdzjot+6zs+uZdC/2edLz+d9Z/8qq7e88z5GXy5LiVjrs/VqRuDT9bj6GOq9/fwgb5Z78A/+w/88ELRhY7mbf7j0AL3I16JS+4D4Mes04m3UdYT+sKvmnsfukn46A997PWQ4MgBHeRaJjj+Qh4EvX3neeJI77+wB3HDuQZx4X15ozo+byD+8Z8ZXpciB3pI59deFBy8xAvPZ3t9QP4IO5D/pv8XrvOlLg8/4/wP+1WyP3B/kTjELvDLv7uDf9zsfMkR6gce77d3ss9jHP+eHfYs73VhA9vjN/XHvuk8dbGe0dsYz5s3qEXObtZ7M9ah4od75tBbaP69T1iLP+Of1MVB907HHfW+8MW8TYu9kINzTuzC+QdyputSjrL/kP/Dvl3ox31bnrl35jw08yTjcm3Hcc7PDBcd8H7IOPbjahnHPQLsOpqWegTXl42kpV5LLXJyXgP/rOPQy5nW40P23/mOY/JC+HGp7ICfUqcI3i1qsc8c65lzAvgb7vmN7y3yc88e/WWpRW+t7K+f8Uydoc8Nb3J+hXke/jk/BO9rXu+Q/4bPzfDFvl8tft5bLfpEPuR0vnA1fgbfzLPwwbyCvad7vcC9e/RGPRX8eD9zvdYDo5GDfQJxgB9AB3vgt3xn0cMT3v+eDH7qerxPe5GWOqX0eslwzp2Q/wngfEcFRy/kV9A39+jhp6vXEaM8X5OPIu47Jm0z1n2MT/+7XacIDv/l1aKnQ32uwHoUv4EOz9zXQ5/0o/926JI/t/8Np8Xe4g8+qIcnjlSHVhF71Dc/b9iOzJ/4EXVG0MmyHVo7X8l6CTswL6LXtY6Pg9QPO3PuA1/UA+EHxr/nSvsV+V30S90Rci0QnP63yS7Afa6cw/cdfTEOu+Z7f0adPX5VGzzsX30OiX8Sr6x/0Qd5Q+S+TnD447yPfugPP+ffYwZeQ3iA8+9NQNf+uBR9Qo/6Vuj0Eh3sDf/olX0n9vvU8yj1w/hHS/VHX3WdT8Ru8Hux4NBVPOSi5zbJOiJjqd5jf+Yh6Gd63nnH+ZgLNR+in92eP8gLYLcuXrd0oOXfSybPw/fU8+FA8JB38/qrGe8lj/NmGfgr9Fo7nlW3/hL7ixfEN/Baqi9Bbp+TN+ZcAb0y/6A3zn3wM74HjG+gln59BUc/1E3zzL0y7HeSWuDv2t7Ds1M52PdPmn+IZ/JK4G+s98jd3Ovjafbn17S+wH+oQ0IP1LegT851wdsQvvneSR7iGn8CP/iIQ/YD9B/v/EChWuQk/wI+1k3Y+w7NE9iT7yTj+ffwkY95lLjGvvgzfoXeWbfSv6nPhy71/ow8O/gH+Ryff08Je1GnTfywDke/7E+xD/l64pD+0KEOHHn+6XWi5d1Juy+evc5X3VIm8HQ9wNWSBzxNvd6t53h60XL3g2/q6dSib+Zr7EQdMf2IV+iyf0P+LYJjL/SEHqmDoV9TwRmXvg88KIHPHUo/9gvO06b/nZuN1NHw7yHTj3v1gqO/mtCnblot+Ed6/U5dAHReUYvdJ3hfsl4t8ZPtfF+6btP1uNdfgF6Q0/6fka4r9H6P/B9xyX1P+DW9haXWL/k04DPEJ3wfaTzUocI/56L4Z4n3vfwuA8/PJvDunFtCh/sL8M25NPYkv4o+2Q8AZ77Eb9iPYifWYfhfU8HRN+sg7LPK8jLfwk+Rz5M=
*/