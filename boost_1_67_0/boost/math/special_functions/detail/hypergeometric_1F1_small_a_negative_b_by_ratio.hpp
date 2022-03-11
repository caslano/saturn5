
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
     inline T hypergeometric_1F1_imp(const T& a, const T& b, const T& z, const Policy& pol, int& log_scaling);

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
      T hypergeometric_1F1_small_a_negative_b_by_ratio(const T& a, const T& b, const T& z, const Policy& pol, int& log_scaling)
      {
         BOOST_MATH_STD_USING
         //
         // We grab the ratio for M[a, b, z] / M[a, b+1, z] and use it to seed 2 initial values,
         // then recurse until b > 0, compute a reference value and normalize (Millers method).
         //
         int iterations = itrunc(-b, pol);
         boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
         T ratio = boost::math::tools::function_ratio_from_forwards_recurrence(boost::math::detail::hypergeometric_1F1_recurrence_b_coefficients<T>(a, b, z), boost::math::tools::epsilon<T>(), max_iter);
         boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1F1_small_a_negative_b_by_ratio<%1%>(%1%,%1%,%1%)", max_iter, pol);
         T first = 1;
         T second = 1 / ratio;
         int scaling1 = 0;
         BOOST_ASSERT(b + iterations != a);
         second = boost::math::tools::apply_recurrence_relation_forward(boost::math::detail::hypergeometric_1F1_recurrence_b_coefficients<T>(a, b + 1, z), iterations, first, second, &scaling1);
         int scaling2 = 0;
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