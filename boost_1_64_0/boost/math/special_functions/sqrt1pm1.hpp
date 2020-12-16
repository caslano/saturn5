//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SQRT1PM1
#define BOOST_MATH_SQRT1PM1

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/expm1.hpp>

//
// This algorithm computes sqrt(1+x)-1 for small x:
//

namespace boost{ namespace math{

template <class T, class Policy>
inline typename tools::promote_args<T>::type sqrt1pm1(const T& val, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;
   BOOST_MATH_STD_USING

   if(fabs(result_type(val)) > 0.75)
      return sqrt(1 + result_type(val)) - 1;
   return boost::math::expm1(boost::math::log1p(val, pol) / 2, pol);
}

template <class T>
inline typename tools::promote_args<T>::type sqrt1pm1(const T& val)
{
   return sqrt1pm1(val, policies::policy<>());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SQRT1PM1






/* sqrt1pm1.hpp
0pXrmstzzFVMHc/2835M+asZF2bmtiBtMWb16r4eXlm+YijYlG7ex/tm0jnHr6JNZiSu6p6N8Y5KN9ily85Z+kPibGMQVteC11BOhjxb5K7oPqtXsNbm9lr5j31gaBH5r30/aDDj8P/scUKbcGC+2WGPnbE9wxgR/9NZwTEyNBgRv/Ss4CgZGoxZvEw+MlQZEp/IxxYVBsT/7BpbVBgS+4trbFFlQOSv9iphmyoDYlPX2KDMmPTf9IsiXeJ/t7cMRc68IRz0pJF/2J+EDWpMSc+0R4vSJVfy+yzX/ikPdSYs/8s5VcYk/m2/EYr0WTTGp6naC2zv1+4P1Unb3lxzln5uTxmGF7vufPVHxvonxv0+PqdF8Yfq78rLse/LQ5nV51zRz6xX8j2A/l4Ysjet9wOdBz9QJ7PvmNvvnhWss3PvcJD9mja/rN9fPMtrv8+Vs06eOn3mJF7us+cc+7y8HzFXtAg+qk02qTEk+jFzwhYVBoRr8nGGMn1iH7f3Ejs0mbL8CeWoMSL+SXnI0iZUVw+bVBiR/JSxIkudIbFP6z9blOkT/Yy4yLDHjHRDHuqMSXxW/6j9ythIm0xIf07slDn8YWXeedD/Xz8r2LffV+H95qGsn0X33m5dv1XctN+i/Ousobzrr3GdfaKvVf+rzd+rxGLPq/wr+IX3RugyIfrLUJDmOBvkqZF5iViZcOoi5V9gDdJiSLCtDxzmNIXnX76+F4K6dOvdh/wPtXDQ8rrV3LHn4HP168HGjl06RE4YX85c7tKFoCztXnQg6EpjDzGm5Gjcxn4J0siFrpGlwZDEQ7VNgQ4zlk/qLzUGRB5m3bJFmR7Bw61N1tilQ/gR+sIWNUYsnlK/r7HHpBmazOg9/mCw/EhxU6JP9FHaYYcmE1KPlocSPSKn5SFDjTGpx2iDHC2m9C70xr2xO/5Y80WbGauP0zeqDCnf+EAQW7NuydMl8nj9YIM6A2JPEON/vFZLt6kxJvFEY0CeLuEzyrJJiR7hJ7n2o4XgsHSHJnMSDzSOD/Bs3Nv1G5kTxqRurG1qTFhKaoNd+izexLqnwB4zUjc1BhQZEL+ZNUeJIfElZcjSIXJz40ieLrFbuE+OJsEtvZayRZ0Z6ZTXImqMSd3KOXXmHD5XP2gTvbW1SokR6bS6aBG6jWebHF3itxUrBdrMWb2dMaTMkOSy/lFkSPL2ypCjxYTUHYwbcRvi1qUzDt/RfFFhzNKK9USNOUfuJMYHHgx2pNVH+92SdM6R86wx9ojcWTyDQ8EJaZ4+i6v6R4l9Fu8iHnZpEzpf22zQZPCeUHDyQQeD4c8P+XyE9UaWPUKHtcc2NVof8T60dO2Cg8GpcihI3s0xJx980PuH+nDiYNCTRu9uzsjRIXoP5/R/6TOVl6dEjuj3Qw56r1JsDEne07xRok/sXsb1Btbf9czfR+U9x9xf3dq9qteCQ2K0X1m+5XtL7+Es2Qfs8Mw+LFQYEP2nrzVk6f79Sv6XtPeOGLFpb6wqmUvxua65dOkyeTj5W3sQ0WTC0u9cI0eLGUu/t2cbeTqERvaBYZ0SPUJ/sKcTG9SYsfxHbdNgQuISZegRGouXLF0yv5IS/FpbF2uLIdGf6iuL91oINqUVBkR/Jr/3uI5IUz+yLxolhsR+bI8ZcrSYkv6Jtmn/1GfGpPvkvu+cpR/YB4YeR3+o3u+qZ08bXxMjWdqEvi4WtqgxIf0N8ZKnzZSltv1wKNBmSvqb9p6hzID4t4wzBQY3CQUdaeTb2idLl2jHOVmazFn5jvapMiYt1s0P+BrYUv6Kh7wHZA5okv6S+pva/Yy9eegTapg7NigxvedC0JGGPmvMKNAh+Jy+U6BP/PP6Sd8=
*/