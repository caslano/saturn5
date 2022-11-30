//  (C) Copyright John Maddock 2005-2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_FRACTION_INCLUDED
#define BOOST_MATH_TOOLS_FRACTION_INCLUDED

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/complex.hpp>
#include <type_traits>
#include <cstdint>
#include <cmath>

namespace boost{ namespace math{ namespace tools{

namespace detail
{

   template <typename T>
   struct is_pair : public std::false_type{};

   template <typename T, typename U>
   struct is_pair<std::pair<T,U>> : public std::true_type{};

   template <typename Gen>
   struct fraction_traits_simple
   {
      using result_type = typename Gen::result_type;
      using  value_type = typename Gen::result_type;

      static result_type a(const value_type&) BOOST_MATH_NOEXCEPT(value_type)
      {
         return 1;
      }
      static result_type b(const value_type& v) BOOST_MATH_NOEXCEPT(value_type)
      {
         return v;
      }
   };

   template <typename Gen>
   struct fraction_traits_pair
   {
      using  value_type = typename Gen::result_type;
      using result_type = typename value_type::first_type;

      static result_type a(const value_type& v) BOOST_MATH_NOEXCEPT(value_type)
      {
         return v.first;
      }
      static result_type b(const value_type& v) BOOST_MATH_NOEXCEPT(value_type)
      {
         return v.second;
      }
   };

   template <typename Gen>
   struct fraction_traits
       : public std::conditional<
         is_pair<typename Gen::result_type>::value,
         fraction_traits_pair<Gen>,
         fraction_traits_simple<Gen>>::type
   {
   };

   template <typename T, bool = is_complex_type<T>::value>
   struct tiny_value
   {
      // For float, double, and long double, 1/min_value<T>() is finite.
      // But for mpfr_float and cpp_bin_float, 1/min_value<T>() is inf.
      // Multiply the min by 16 so that the reciprocal doesn't overflow.
      static T get() {
         return 16*tools::min_value<T>();
      }
   };
   template <typename T>
   struct tiny_value<T, true>
   {
      using value_type = typename T::value_type;
      static T get() {
         return 16*tools::min_value<value_type>();
      }
   };

} // namespace detail

//
// continued_fraction_b
// Evaluates:
//
// b0 +       a1
//      ---------------
//      b1 +     a2
//           ----------
//           b2 +   a3
//                -----
//                b3 + ...
//
// Note that the first a0 returned by generator Gen is discarded.
//
template <typename Gen, typename U>
inline typename detail::fraction_traits<Gen>::result_type continued_fraction_b(Gen& g, const U& factor, std::uintmax_t& max_terms)
      noexcept(BOOST_MATH_IS_FLOAT(typename detail::fraction_traits<Gen>::result_type) && noexcept(std::declval<Gen>()()))
{
   BOOST_MATH_STD_USING // ADL of std names

   using traits = detail::fraction_traits<Gen>;
   using result_type = typename traits::result_type;
   using value_type = typename traits::value_type;
   using integer_type = typename integer_scalar_type<result_type>::type;
   using scalar_type = typename scalar_type<result_type>::type;

   integer_type const zero(0), one(1);

   result_type tiny = detail::tiny_value<result_type>::get();
   scalar_type terminator = abs(factor);

   value_type v = g();

   result_type f, C, D, delta;
   f = traits::b(v);
   if(f == zero)
      f = tiny;
   C = f;
   D = 0;

   std::uintmax_t counter(max_terms);
   do{
      v = g();
      D = traits::b(v) + traits::a(v) * D;
      if(D == result_type(0))
         D = tiny;
      C = traits::b(v) + traits::a(v) / C;
      if(C == zero)
         C = tiny;
      D = one/D;
      delta = C*D;
      f = f * delta;
   }while((abs(delta - one) > terminator) && --counter);

   max_terms = max_terms - counter;

   return f;
}

template <typename Gen, typename U>
inline typename detail::fraction_traits<Gen>::result_type continued_fraction_b(Gen& g, const U& factor)
   noexcept(BOOST_MATH_IS_FLOAT(typename detail::fraction_traits<Gen>::result_type) && noexcept(std::declval<Gen>()()))
{
   std::uintmax_t max_terms = (std::numeric_limits<std::uintmax_t>::max)();
   return continued_fraction_b(g, factor, max_terms);
}

template <typename Gen>
inline typename detail::fraction_traits<Gen>::result_type continued_fraction_b(Gen& g, int bits)
   noexcept(BOOST_MATH_IS_FLOAT(typename detail::fraction_traits<Gen>::result_type) && noexcept(std::declval<Gen>()()))
{
   BOOST_MATH_STD_USING // ADL of std names

   using traits = detail::fraction_traits<Gen>;
   using result_type = typename traits::result_type;

   result_type factor = ldexp(1.0f, 1 - bits); // 1 / pow(result_type(2), bits);
   std::uintmax_t max_terms = (std::numeric_limits<std::uintmax_t>::max)();
   return continued_fraction_b(g, factor, max_terms);
}

template <typename Gen>
inline typename detail::fraction_traits<Gen>::result_type continued_fraction_b(Gen& g, int bits, std::uintmax_t& max_terms)
   noexcept(BOOST_MATH_IS_FLOAT(typename detail::fraction_traits<Gen>::result_type) && noexcept(std::declval<Gen>()()))
{
   BOOST_MATH_STD_USING // ADL of std names

   using traits = detail::fraction_traits<Gen>;
   using result_type = typename traits::result_type;

   result_type factor = ldexp(1.0f, 1 - bits); // 1 / pow(result_type(2), bits);
   return continued_fraction_b(g, factor, max_terms);
}

//
// continued_fraction_a
// Evaluates:
//
//            a1
//      ---------------
//      b1 +     a2
//           ----------
//           b2 +   a3
//                -----
//                b3 + ...
//
// Note that the first a1 and b1 returned by generator Gen are both used.
//
template <typename Gen, typename U>
inline typename detail::fraction_traits<Gen>::result_type continued_fraction_a(Gen& g, const U& factor, std::uintmax_t& max_terms)
   noexcept(BOOST_MATH_IS_FLOAT(typename detail::fraction_traits<Gen>::result_type) && noexcept(std::declval<Gen>()()))
{
   BOOST_MATH_STD_USING // ADL of std names

   using traits = detail::fraction_traits<Gen>;
   using result_type = typename traits::result_type;
   using value_type = typename traits::value_type;
   using integer_type = typename integer_scalar_type<result_type>::type;
   using scalar_type = typename scalar_type<result_type>::type;

   integer_type const zero(0), one(1);

   result_type tiny = detail::tiny_value<result_type>::get();
   scalar_type terminator = abs(factor);

   value_type v = g();

   result_type f, C, D, delta, a0;
   f = traits::b(v);
   a0 = traits::a(v);
   if(f == zero)
      f = tiny;
   C = f;
   D = 0;

   std::uintmax_t counter(max_terms);

   do{
      v = g();
      D = traits::b(v) + traits::a(v) * D;
      if(D == zero)
         D = tiny;
      C = traits::b(v) + traits::a(v) / C;
      if(C == zero)
         C = tiny;
      D = one/D;
      delta = C*D;
      f = f * delta;
   }while((abs(delta - one) > terminator) && --counter);

   max_terms = max_terms - counter;

   return a0/f;
}

template <typename Gen, typename U>
inline typename detail::fraction_traits<Gen>::result_type continued_fraction_a(Gen& g, const U& factor)
   noexcept(BOOST_MATH_IS_FLOAT(typename detail::fraction_traits<Gen>::result_type) && noexcept(std::declval<Gen>()()))
{
   std::uintmax_t max_iter = (std::numeric_limits<std::uintmax_t>::max)();
   return continued_fraction_a(g, factor, max_iter);
}

template <typename Gen>
inline typename detail::fraction_traits<Gen>::result_type continued_fraction_a(Gen& g, int bits)
   noexcept(BOOST_MATH_IS_FLOAT(typename detail::fraction_traits<Gen>::result_type) && noexcept(std::declval<Gen>()()))
{
   BOOST_MATH_STD_USING // ADL of std names

   typedef detail::fraction_traits<Gen> traits;
   typedef typename traits::result_type result_type;

   result_type factor = ldexp(1.0f, 1-bits); // 1 / pow(result_type(2), bits);
   std::uintmax_t max_iter = (std::numeric_limits<std::uintmax_t>::max)();

   return continued_fraction_a(g, factor, max_iter);
}

template <typename Gen>
inline typename detail::fraction_traits<Gen>::result_type continued_fraction_a(Gen& g, int bits, std::uintmax_t& max_terms)
   noexcept(BOOST_MATH_IS_FLOAT(typename detail::fraction_traits<Gen>::result_type) && noexcept(std::declval<Gen>()()))
{
   BOOST_MATH_STD_USING // ADL of std names

   using traits = detail::fraction_traits<Gen>;
   using result_type = typename traits::result_type;

   result_type factor = ldexp(1.0f, 1-bits); // 1 / pow(result_type(2), bits);
   return continued_fraction_a(g, factor, max_terms);
}

} // namespace tools
} // namespace math
} // namespace boost

#endif // BOOST_MATH_TOOLS_FRACTION_INCLUDED

/* fraction.hpp
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
*/