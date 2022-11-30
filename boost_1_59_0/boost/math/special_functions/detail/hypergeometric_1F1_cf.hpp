
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_1F1_CF_HPP
#define BOOST_MATH_HYPERGEOMETRIC_1F1_CF_HPP

#include <boost/math/tools/fraction.hpp>

//
// Evaluation of 1F1 by continued fraction
// see http://functions.wolfram.com/HypergeometricFunctions/Hypergeometric1F1/10/0002/
//
// This is not terribly useful, as like the series we're adding a something to 1,
// so only really useful when we know that the result will be > 1.
//


  namespace boost { namespace math { namespace detail {

     template <class T>
     struct hypergeometric_1F1_cf_func
     {
        typedef std::pair<T, T>  result_type;
        hypergeometric_1F1_cf_func(T a_, T b_, T z_) : a(a_), b(b_), z(z_), k(0) {}
        std::pair<T, T> operator()()
        {
           ++k;
           return std::make_pair(-(((a + k) * z) / ((k + 1) * (b + k))), 1 + ((a + k) * z) / ((k + 1) * (b + k)));
        }
        T a, b, z;
        unsigned k;
     };

     template <class T, class Policy>
     T hypergeometric_1F1_cf(const T& a, const T& b, const T& z, const Policy& pol, const char* function)
     {
        hypergeometric_1F1_cf_func<T> func(a, b, z);
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        T result = boost::math::tools::continued_fraction_a(func, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>(function, max_iter, pol);
        return 1 + a * z / (b * (1 + result));
     }

  } } } // namespaces

#endif // BOOST_MATH_HYPERGEOMETRIC_1F1_BESSEL_HPP

/* hypergeometric_1F1_cf.hpp
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
*/