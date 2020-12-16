//  Copyright (c) 2007 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SIN_PI_HPP
#define BOOST_MATH_SIN_PI_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/config/no_tr1/cmath.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/trunc.hpp>
#include <boost/math/tools/promotion.hpp>
#include <boost/math/constants/constants.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
inline T sin_pi_imp(T x, const Policy& pol)
{
   BOOST_MATH_STD_USING // ADL of std names
   if(x < 0)
      return -sin_pi_imp(T(-x), pol);
   // sin of pi*x:
   bool invert;
   if(x < 0.5)
      return sin(constants::pi<T>() * x);
   if(x < 1)
   {
      invert = true;
      x = -x;
   }
   else
      invert = false;

   T rem = floor(x);
   if(iconvert(rem, pol) & 1)
      invert = !invert;
   rem = x - rem;
   if(rem > 0.5f)
      rem = 1 - rem;
   if(rem == 0.5f)
      return static_cast<T>(invert ? -1 : 1);
   
   rem = sin(constants::pi<T>() * rem);
   return invert ? T(-rem) : rem;
}

} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type sin_pi(T x, const Policy&)
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
   return policies::checked_narrowing_cast<result_type, forwarding_policy>(boost::math::detail::sin_pi_imp<value_type>(x, forwarding_policy()), "sin_pi");
}

template <class T>
inline typename tools::promote_args<T>::type sin_pi(T x)
{
   return boost::math::sin_pi(x, policies::policy<>());
}

} // namespace math
} // namespace boost
#endif


/* sin_pi.hpp
0aN9TX+HzYbPd9vUGBD1Oe/GdJmSuZ54VK7v/Sc3voF4NOvmznvVgy3f03bIXdLPjK4rhvGsvd9z9JgRaagbu2qdpECDgflSatqS+7Bxo2oMzjY3Dri+WMGY+tG4lLrKJc5YLqGW6+d0zLxmHHCNljZj+kLTMSN65tA1iDPj2NiOCZgjN/+0+UmZUMe8iRkPVtdTF/GX63uT3Jg9clToMGb7N3I15tHzqbtxzESNpRzHl5ejMaiob/Xa6itWv6smzDj8ghiETucnZ5yzS8Jxh+yo11kcEP61nGlpa3L6vXluPnv/MSH6l9PfR2iDCXtqPyQq/9YNjJcxmazvzXPyC9vTeU/ylHhnzdRXnHtRM6/bS8fREWsuzuHTz2XtyLkCkSedK3CNJ54rEObsP7lWKNNjwe7CNUONE6rOqzs2zS59Zhyx6fgtxxQuqB9sh11fbHBAgQELttf3yK6z8Q9zghQlWpwQXOkHcTJUSJ/fnKXFCfUtc5sFsSvp15bfNdLlGue29vNy6n8j4xVSj4DryNf3urHx5Jjk5f1+0qU2Ye9c3gvZlmmv/4f39cmy67g8QzkE/ikvdklzTJspiXP4zEaNSdB1fBnXIxM25RK5ks+sW+LaZuRXtO+MPELy2nu7eUiNATd/hzlPjQXR9X2n2pwQfLc8aDMm9B6P2SF4unbnwOsk21XXY9Q591AT+4/W9/TOeK7JkI2He41c3ztr8BntnFvuF1Bjr2crQuZNU64jNQ5fUx25sXkU87m84O+GN1leUJ6P9rtA+1Yv/u//J0tSo8fggtq4kHl+HmPGnIA2kptiXl5Mbi5+/IbaOo/vXZwQNM7bp5+HQ/K60en7bmNBj+3zmkfkqdFjur43/I3J0WXOvnMPaZE9n/bE3aVzQe1dUR7aKLC6inkkh64xOctYnbX+n/FxVle0te/G55C7Gh2cvl4b25urzdKYxYxTggE3NkZ7ZDmqGQMm7zKu5zN3Io61TTC4sHFiy740y0cYQ7JUGRJ7pNp5HYqfUvscyYcbW444yxgG2KVpvCbXkJ/zWg9XQ7Z8HaiJwdm05RH6nPPYJc0xHaZEu/IkQYGNqceMucavxPyNvH4n5u+dT5oj9rxuHXL9pVhqGLqxPJ+vzby2SHBIhQ4TAs+XH2eTYxn1OndxtT/jeyTl58uX5Pq+aoF3iUWcDGV2zf8Mx1zji8Z6fU+YMm22fi3H9T1bqh80xtwrYOzo/Yeiu49TPJ8DAP5j29nchRByBiEMcsJgnHEWi8VinXUWi8VgMRgMBoOOQQghDEIIIYQQQhiEEEJHCIO43IUQ8vC+P96v7+/h+/D5PvyamWb6zietBbGW2Hc8Mu9x6dzPyJMNa5Ua0Wdwf+/b+DzMIsPL+xaKBCsHI8FJZo536dMg7tqIYwuRYImO4zoFtsjIMzwQCbbZ47jzRULyLksDUoec03AtfKVIUHQcCSvDluMRe6TDUvYpceIQ0pPK7J6lPkKs0XetzMmz1c/QtURcPPq3TPM68l5bXReEgprrfSJXth9FVB52qdFhRPhq+nc5eY5KT7NFgRptNkqHguI3fcZyPxSc1sZQ/VnXThKkjRFHbh0JWixx8iZival+MSd1M+Mh3aVNzf28fAnpDn0m54rFtaS/+diWf5dQJOIz+44TEXvT68d54mOFLANGd1LXVYzDVbVFi+J1I/bVN87klW/fwPzIs0FmMRJU2D5ijNk5PxKM72GMHSelK3fTlmvhu0eCnvSk8yXHybtEgqbjIpm7mgP5Q/K3HVcYup51foajrMsfce2Ee7vKjw/Ly1HHe+6PXM87j6hn07VFbQ2VaRE43ndtWZ4YU+dlZQrulR237i5O6VI=
*/