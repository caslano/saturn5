
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_1F1_SMALL_A_NEG_B_HPP
#define BOOST_MATH_HYPERGEOMETRIC_1F1_SMALL_A_NEG_B_HPP

#include <algorithm>
#include <boost/math/tools/recurrence.hpp>

  namespace boost { namespace math { namespace detail {

     // forward declaration for initial values
     template <class T, class Policy>
     inline T hypergeometric_1F1_imp(const T& a, const T& b, const T& z, const Policy& pol);

     template <class T, class Policy>
     inline T hypergeometric_1F1_imp(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scaling);

      template <class T>
      T max_b_for_1F1_small_a_negative_b_by_ratio(const T& z)
      {
         if (z < -998)
            return (z * 2) / 3;
         float max_b[][2] = 
         {
            { 0.0f, -47.3046f }, {-6.7275f, -52.0351f }, { -8.9543f, -57.2386f }, {-11.9182f, -62.9625f }, {-14.421f, -69.2587f }, {-19.1943f, -76.1846f }, {-23.2252f, -83.803f }, {-28.1024f, -92.1833f }, {-34.0039f, -101.402f }, {-37.4043f, -111.542f }, {-45.2593f, -122.696f }, {-54.7637f, -134.966f }, {-60.2401f, -148.462f }, {-72.8905f, -163.308f }, {-88.1975f, -179.639f }, {-88.1975f, -197.603f }, {-106.719f, -217.363f }, {-129.13f, -239.1f }, {-142.043f, -263.01f }, {-156.247f, -289.311f }, {-189.059f, -318.242f }, {-207.965f, -350.066f }, {-228.762f, -385.073f }, {-276.801f, -423.58f }, {-304.482f, -465.938f }, {-334.93f, -512.532f }, {-368.423f, -563.785f }, {-405.265f, -620.163f }, {-445.792f, -682.18f }, {-539.408f, -750.398f }, {-593.349f, -825.437f }, {-652.683f, -907.981f }, {-717.952f, -998.779f }
         };
         auto p = std::lower_bound(max_b, max_b + sizeof(max_b) / sizeof(max_b[0]), z, [](const float (&a)[2], const T& z) { return a[1] > z; });
         T b = p - max_b ? (*--p)[0] : 0;
         //
         // We need approximately an extra 10 recurrences per 50 binary digits precision above that of double:
         //
         b += (std::max)(0, boost::math::tools::digits<T>() - 53) / 5;
         return b;
      }

      template <class T, class Policy>
      T hypergeometric_1F1_small_a_negative_b_by_ratio(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scaling)
      {
         BOOST_MATH_STD_USING
         //
         // We grab the ratio for M[a, b, z] / M[a, b+1, z] and use it to seed 2 initial values,
         // then recurse until b > 0, compute a reference value and normalize (Millers method).
         //
         int iterations = itrunc(-b, pol);
         std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
         T ratio = boost::math::tools::function_ratio_from_forwards_recurrence(boost::math::detail::hypergeometric_1F1_recurrence_b_coefficients<T>(a, b, z), boost::math::tools::epsilon<T>(), max_iter);
         boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1F1_small_a_negative_b_by_ratio<%1%>(%1%,%1%,%1%)", max_iter, pol);
         T first = 1;
         T second = 1 / ratio;
         long long scaling1 = 0;
         BOOST_MATH_ASSERT(b + iterations != a);
         second = boost::math::tools::apply_recurrence_relation_forward(boost::math::detail::hypergeometric_1F1_recurrence_b_coefficients<T>(a, b + 1, z), iterations, first, second, &scaling1);
         long long scaling2 = 0;
         first = hypergeometric_1F1_imp(a, T(b + iterations + 1), z, pol, scaling2);
         //
         // Result is now first/second * e^(scaling2 - scaling1)
         //
         log_scaling += scaling2 - scaling1;
         return first / second;
      }


  } } } // namespaces

#endif // BOOST_MATH_HYPERGEOMETRIC_1F1_SMALL_A_NEG_B_HPP

/* hypergeometric_1F1_small_a_negative_b_by_ratio.hpp
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
*/