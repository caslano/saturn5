//  (C) Copyright John Maddock 2005-2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_SERIES_INCLUDED
#define BOOST_MATH_TOOLS_SERIES_INCLUDED

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/config/no_tr1/cmath.hpp>
#include <boost/cstdint.hpp>
#include <boost/limits.hpp>
#include <boost/math/tools/config.hpp>

namespace boost{ namespace math{ namespace tools{

//
// Simple series summation come first:
//
template <class Functor, class U, class V>
inline typename Functor::result_type sum_series(Functor& func, const U& factor, boost::uintmax_t& max_terms, const V& init_value) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING

   typedef typename Functor::result_type result_type;

   boost::uintmax_t counter = max_terms;

   result_type result = init_value;
   result_type next_term;
   do{
      next_term = func();
      result += next_term;
   }
   while((abs(factor * result) < abs(next_term)) && --counter);

   // set max_terms to the actual number of terms of the series evaluated:
   max_terms = max_terms - counter;

   return result;
}

template <class Functor, class U>
inline typename Functor::result_type sum_series(Functor& func, const U& factor, boost::uintmax_t& max_terms) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   typename Functor::result_type init_value = 0;
   return sum_series(func, factor, max_terms, init_value);
}

template <class Functor, class U>
inline typename Functor::result_type sum_series(Functor& func, int bits, boost::uintmax_t& max_terms, const U& init_value) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING
   typedef typename Functor::result_type result_type;
   result_type factor = ldexp(result_type(1), 1 - bits);
   return sum_series(func, factor, max_terms, init_value);
}

template <class Functor>
inline typename Functor::result_type sum_series(Functor& func, int bits) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING
   typedef typename Functor::result_type result_type;
   boost::uintmax_t iters = (std::numeric_limits<boost::uintmax_t>::max)();
   result_type init_val = 0;
   return sum_series(func, bits, iters, init_val);
}

template <class Functor>
inline typename Functor::result_type sum_series(Functor& func, int bits, boost::uintmax_t& max_terms) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING
   typedef typename Functor::result_type result_type;
   result_type init_val = 0;
   return sum_series(func, bits, max_terms, init_val);
}

template <class Functor, class U>
inline typename Functor::result_type sum_series(Functor& func, int bits, const U& init_value) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING
   boost::uintmax_t iters = (std::numeric_limits<boost::uintmax_t>::max)();
   return sum_series(func, bits, iters, init_value);
}
//
// Checked summation:
//
template <class Functor, class U, class V>
inline typename Functor::result_type checked_sum_series(Functor& func, const U& factor, boost::uintmax_t& max_terms, const V& init_value, V& norm) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING

   typedef typename Functor::result_type result_type;

   boost::uintmax_t counter = max_terms;

   result_type result = init_value;
   result_type next_term;
   do {
      next_term = func();
      result += next_term;
      norm += fabs(next_term);
   } while ((abs(factor * result) < abs(next_term)) && --counter);

   // set max_terms to the actual number of terms of the series evaluated:
   max_terms = max_terms - counter;

   return result;
}


//
// Algorithm kahan_sum_series invokes Functor func until the N'th
// term is too small to have any effect on the total, the terms
// are added using the Kahan summation method.
//
// CAUTION: Optimizing compilers combined with extended-precision
// machine registers conspire to render this algorithm partly broken:
// double rounding of intermediate terms (first to a long double machine
// register, and then to a double result) cause the rounding error computed
// by the algorithm to be off by up to 1ulp.  However this occurs rarely, and
// in any case the result is still much better than a naive summation.
//
template <class Functor>
inline typename Functor::result_type kahan_sum_series(Functor& func, int bits) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING

   typedef typename Functor::result_type result_type;

   result_type factor = pow(result_type(2), bits);
   result_type result = func();
   result_type next_term, y, t;
   result_type carry = 0;
   do{
      next_term = func();
      y = next_term - carry;
      t = result + y;
      carry = t - result;
      carry -= y;
      result = t;
   }
   while(fabs(result) < fabs(factor * next_term));
   return result;
}

template <class Functor>
inline typename Functor::result_type kahan_sum_series(Functor& func, int bits, boost::uintmax_t& max_terms) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING

   typedef typename Functor::result_type result_type;

   boost::uintmax_t counter = max_terms;

   result_type factor = ldexp(result_type(1), bits);
   result_type result = func();
   result_type next_term, y, t;
   result_type carry = 0;
   do{
      next_term = func();
      y = next_term - carry;
      t = result + y;
      carry = t - result;
      carry -= y;
      result = t;
   }
   while((fabs(result) < fabs(factor * next_term)) && --counter);

   // set max_terms to the actual number of terms of the series evaluated:
   max_terms = max_terms - counter;

   return result;
}

} // namespace tools
} // namespace math
} // namespace boost

#endif // BOOST_MATH_TOOLS_SERIES_INCLUDED


/* series.hpp
dgQwflzkyZCud31If+d1hA40LQB9OS7dR9NPrW7o+H2G1ePdDTTz3WjVAc5Fvk/a1v0C+mmMtb14PdDcd0+ft72/pXu8dTf2iY5hLCYwGMu6vVYd6zPQB8A3HO186s/6QUINd2mIveMeFNvfjCF2a8e2WO3rSM5kDu/cFmv8N49Y3OUr4Ix4jPWG50L36vNYB1S4dkTcrl3jcVYJDnd5G5xVgMN97t7b4cw+zuG27rMdzrhHONwN9x2Pe4bRJuJ2794OB5r0fcO2wc3B593cmo664ZV5/XisxWGMAw/nnNI8+oX7d/TjSPbmlZVgXuGyiqIi+b9sfhpsXrywNd8sEOcwEzV9h/ChCbJbxblmp6bRXWkYu+rDlm4/yV39p4Ixq1KZV6m66lwvfv0bHLNVlMzxaDYyMSleoH+PhYnM1cWOnHFYOqd+ZIJ+0fqxH27Yoemw9kFP+HFsf7ZT/24ZtDF4tPa6gDZA2uH7+LQNqAr6Pr1sD9D6K5DvcwUr4ljMWJ+rXQ8ci7V+Uuh/drePe5ZzB3N1XnwQoUN1kHfXXp/mquF4/03o1Hf40oMJzVYL7fzS66mdCJFkcZxfswOXewv1huBNehsVqYykjk4VJS+ey5qZWaurbo8z5dvJRyfoiZY/pjd2EPrwsAW4c/5JpGvSnH2A65ex/56I0YMqlHHrLqTjx7W3/t/H0ulHqbOHu3drutaKbcPN6wMjxMUbxTg3BAcQv18uBP3S5KWSdX7N848/V3xswj+pwfF3clLTzI96JKFf6b3J7yT2z3uudzRYbfQQwzH2zgdq2pXH2I0PAsxVjrHjeymWjjGs08EHIy4cQz8jNCfG0S8+hNB7/qMff6ilb+PXvmefT4fiPd4v+TQUjXp+GNJDn/jh64P9rcjruEyKa7UDd8eh2zLRPw2d8DCzkxYTHHz6mFfu7mPsftXV/cbAhmtRpE2Zi2utu2/Dn5jwTq/994GBrDLKGl4316wn/+3AJye2OfS2OHsnj7jwcNv/LrgOcXjoifX/2etoPwuViaiIrvnxlD+XfsrKcw+UPPpPd1C6nZ4cffaelK63iuQ90a4x9IH3PXFvpNt9sbP3vz1Q0/R3oZ5WzNbLjZUzezVNt8aWCwicC4D3wUDf5gvS3E11Y+oh43E4chG776GAvcq5aO++sVgzakms9Yd5uGfRueYCobkqOfq+hyOdrvf4zhPpRjTq1tLGvUm84waPZqc4a38QY4+OnyznseLVNe8Xffu7MIGH9bov/flj7z2QTg7zgzH46W2/l/C75ZX3MDi0xWSmrSH2sJ3X8JtxB8WBVsGLcnHldWsW7GF/vvMKWDMZInbPPa+IhUkR211eR7AmJN/8im78It6F3sth8Ntljurm4i6KITJ9n6F7d7jj3TA/q1/BT3hxlc9v+X66MlWRyKOM4UF/kFNvy/dFf2Yc8STPRKNPAqkf+nv8co8lRVNmhTvRN1D0k77Txx7lVVkJHWpp0XN6jjr5+17p+3Y3RamqpDYZ7Kj8/QQXF6XkqijYMp4bo9/gh7fouWrZVkkpS8mCD5/QZ/lrPl/F2ijOmqpObZ7RqfXhmDhIP92id7mwUunA2h3PFoxO9A/3ZP1qKzinTmWS1y3hC2OJ/YHKakQqqzYVHc9gcbA8VtbE6+iZbd3GVcTdHRqMxJme//oen6dmvIlkwVPVyQLTc/e1zPmH+jwtSxVYE28cz+AMcpH6TdH61WmVyah0evft9kBn59znmRZxFtVxWXQsICU4t25p3YRI0pa3SXB9R21u8XXE5oVq2zxlJIhg3LV95XXU5qoki0uVCiIAFY05HQhfzGLVxirL0o4vesGs1Lwd48Otn+Wes5o=
*/