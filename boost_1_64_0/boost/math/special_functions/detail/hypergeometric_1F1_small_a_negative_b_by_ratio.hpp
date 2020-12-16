
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
OiTOsr2u0TOrEyeXMZWfMcr7406F5jmbjnqZ++RcMWZzrObDupDfqgRdSnHbH19AuvQn8F73/S6pfMd3rRQdvFhEb/G5woWXa+nye0dQNrLRPmFg1o6yn+jzGo3eL1LtmPOfMDBQffh8lPZ8Xm/QVyLWCzYNu4jTv/ACGwMdwPb9C226qlfcN+p0nli4D9fnYVqKPL5Nx6AtnJC9ZtD5TnJnzHOIjkHltErj4axOhxHDe7AftWjcVuTbsDFqW6U2XdubOKX3B72ZQ33Z0OUNTDGiOU2dBmcpiTY28oUyEe2UQVP7bv1RVwCaCG+Q4WAY4TDV3jtceKMcW/3lTpGvhPVB+slLIM7yOyRk7zOm0Adw/kpMV/b4iT7+LNPZt6Xsgb3jyhn9OPmeQppzmGZM2Cxj7jsZo020gCG9nrdHt7g9yH57AOMKfUdMt31HSrvuWTjbd+QcvCRj5viOFhkz13fkMmau72idMfv6jvYsXLHv6DTj5vqOzjKmWG6YXug7Sq9yCaYX+I6cuzP/fr6jRcbN9R25FqbYd7TOuH19R3uMK/QdnWa67TsiXwvXv8h3dJbT0HxHtJZk+r5+IecejCvyCy1adNsv5DKmyC/EaZ3S6wTDVOivXmeb7Z/TNHbId9SmsyM8juf4jngMnr4dYS3fEcUAtAmzr1/o9C7h9vULueAXQtxcv9D5ZzFmP7/Q+BTjLL+QTuNmVO9/fR6X2fYdIeaKl0OM7Ts6z7RC39E69/lc39EeYwp9R+e5jIW+I+f5Ft3yHaUBl3Oe7+gMzKc2xvYdnbNx9tqP8yv0Hbkf4jSKfEcXOI+5vqOFF1kYa611isth+Y7OMK3Qd+SWLo/0Yt/RHtPn+o6WyiqGEdT3TC/0HS1xHef6jlILY/uOznB7F/qOxpzGXN/RqQKM2ufrryY5LPQdOX+6KtKLfUeLTN/Xd+Qybq7vKH0Fl2U/39Eel7nQd3Taotu+owvXJsxc39HCdSyM5TtasjC27yi1MLbvaJH1wb6+o70v0jwzx3fEemwckY6a6zs6ZWFs39FZniMKfUdL4FtA+lzfUcqYQt/R2KLbvqNTjCn0HZ1heqHv6BzTC31HF5he6Dta+BfT5/mOliyM7TtKGVPoOxpbdNt3dMrC2L6jM4yZ6zs6x5i5vqMLFsb2HZ3lMVfoO7rwDZLbQt/R4jmiW76jhW8yrch35IJvB+mW72idaYW+oz2LbvuOTlsY23d0+l+MKfIdnWV6oe9oEfweSLd8Ry7TCn1H60yf6zvaszDFvqPTFs72HZ1lzBzfEdvy500saPWKMoc5l2b6PN/SImMKfUuuRS/2La1buGLf0hmeMzXfEo2H++jpqFYq3UFlprE55nsYmWb4lYQ9ne17Uozyi/fDZnug1MdPYRmz/Vp8D9RZG6eaH5uU91Pn4uCQrl7OvX2xRjl/yOPZ9m1x/qe47gU4Pf8z+2Kz/GkeYGyhv+wC0y1/WfoV0nP7+svO85xZ6C9zLmb6PH/Z+Is55n/zl51ivO4vIx841cvyly28hGlF/rIlphf6y/Y+x31a5C9LmX+uv2xsYWx/2cLnOZ8if9m5z9DYnOsvO8X57OsvO2Pj7Hg7zq/QX3aO05jrL7tgYWx/2cJnOZ95/rIlxsz1l51iGSj0ly281KJba7glC2Ov4c6Cvwwx7C+juZLk1PKXnWWa5S9b5zVEob9sj+lz/WWnLUyxv+zsPJzp02Kc5S9z/sy0In/ZokXX03aZbvnL1plW6C/bY3qhv+w00+f6y84yptBfdt6i2/4y5y8WxvKXLbIuLPSXOZ9cQLruL3PvR2uXQn/ZOtML/WVLL+d05/nLFjlvy1/mfIFp8/xlC58=
*/