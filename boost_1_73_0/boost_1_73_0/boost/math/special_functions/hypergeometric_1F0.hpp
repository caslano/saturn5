
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_HYPERGEOMETRIC_1F0_HPP
#define BOOST_MATH_HYPERGEOMETRIC_1F0_HPP

#include <boost/math/policies/policy.hpp>
#include <boost/math/policies/error_handling.hpp>


namespace boost { namespace math { namespace detail {

template <class T, class Policy>
inline T hypergeometric_1F0_imp(const T& a, const T& z, const Policy& pol)
{
   static const char* function = "boost::math::hypergeometric_1F0<%1%,%1%>(%1%, %1%)";
   BOOST_MATH_STD_USING // pow

   if (z == 1)
      return policies::raise_pole_error<T>(
         function,
         "Evaluation of 1F0 with z = %1%.",
         z,
         pol);
   if (1 - z < 0)
   {
      if (floor(a) != a)
         return policies::raise_domain_error<T>(function,
            "Result is complex when a is non-integral and z > 1, but got z = %1%", z, pol);
   }
   // more naive and convergent method than series
   return pow(T(1 - z), T(-a));
}

} // namespace detail

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type hypergeometric_1F0(T1 a, T2 z, const Policy&)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, Policy>(
      detail::hypergeometric_1F0_imp<value_type>(
         static_cast<value_type>(a),
         static_cast<value_type>(z),
         forwarding_policy()),
      "boost::math::hypergeometric_1F0<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type hypergeometric_1F0(T1 a, T2 z)
{
   return hypergeometric_1F0(a, z, policies::policy<>());
}


  } } // namespace boost::math

#endif // BOOST_MATH_HYPERGEOMETRIC_1F0_HPP

/* hypergeometric_1F0.hpp
bC1+x81OimbSm/qVS6TpCvuf55+nHRaS2qny64tjfVmYbW+Ropbn+RAnznYxphkbVh49dvlTwtrdieKLXpkaytzfrf5v7s/v/7OKBBa7lFpvtSuT/p6wzPCUfxJfXe7MOX0Gif/Nnx2cmMqzcHEi4/vSO/1Bc6ItXU2TT/0+dbfMi6niyAadN49O3FOff23na8t7C5VnXk2dXvGohiN0+sSWgi8dByLnfPrwL6awYn9bn9CkVnnRt5eb/6gGfGljOVtezTPr9eqXp51nHJHLu3dJbW7fwhP3/Zel7de0zqvaeWlfidixLYfdZnNKOs1mLV23dU704qsPy1IjLffMjGWY0M7EzMjAuLix06CxzUAcGICygiwCBnxNqIHIDZLgZ2FhZmJeAQ5mWVUWHgMuNg5tNkZWVnZmRgNZkCAfixiLyK0/b/c3nRa9UbfQe4ZyX7OWYJ7nSQN5kLQyi4SBWIOI0Kld3m4sy0u7dF7whUzZI5S6rPocOO5lhVmYDBjQ0igzKJJmqFe1brPkn3+KP+OU17duQf37QU/c4w045+jc0EmyVuGyNY/g21fdfUzXZt9aT/lkq75GE75ZDR++HKr+m5O2L+Om+rLEBI7UVT/TOv/MdGa3Cb95RUpz8uMdS0LCnWpE87dMWj/f
*/