//  (C) Copyright John Maddock 2005-2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_FRACTION_INCLUDED
#define BOOST_MATH_TOOLS_FRACTION_INCLUDED

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/config/no_tr1/cmath.hpp>
#include <boost/cstdint.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/mpl/if.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/complex.hpp>

namespace boost{ namespace math{ namespace tools{

namespace detail
{

   template <class T>
   struct is_pair : public boost::false_type{};

   template <class T, class U>
   struct is_pair<std::pair<T,U> > : public boost::true_type{};

   template <class Gen>
   struct fraction_traits_simple
   {
       typedef typename Gen::result_type result_type;
       typedef typename Gen::result_type value_type;

       static result_type a(const value_type&) BOOST_MATH_NOEXCEPT(value_type)
       {
          return 1;
       }
       static result_type b(const value_type& v) BOOST_MATH_NOEXCEPT(value_type)
       {
          return v;
       }
   };

   template <class Gen>
   struct fraction_traits_pair
   {
       typedef typename Gen::result_type value_type;
       typedef typename value_type::first_type result_type;

       static result_type a(const value_type& v) BOOST_MATH_NOEXCEPT(value_type)
       {
          return v.first;
       }
       static result_type b(const value_type& v) BOOST_MATH_NOEXCEPT(value_type)
       {
          return v.second;
       }
   };

   template <class Gen>
   struct fraction_traits
       : public boost::mpl::if_c<
         is_pair<typename Gen::result_type>::value,
         fraction_traits_pair<Gen>,
         fraction_traits_simple<Gen> >::type
   {
   };

   template <class T, bool = is_complex_type<T>::value>
   struct tiny_value
   {
      static T get() {
         return tools::min_value<T>(); 
      }
   };
   template <class T>
   struct tiny_value<T, true>
   {
      typedef typename T::value_type value_type;
      static T get() {
         return tools::min_value<value_type>();
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
template <class Gen, class U>
inline typename detail::fraction_traits<Gen>::result_type continued_fraction_b(Gen& g, const U& factor, boost::uintmax_t& max_terms) 
      BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename detail::fraction_traits<Gen>::result_type) && noexcept(std::declval<Gen>()()))
{
   BOOST_MATH_STD_USING // ADL of std names

   typedef detail::fraction_traits<Gen> traits;
   typedef typename traits::result_type result_type;
   typedef typename traits::value_type value_type;
   typedef typename integer_scalar_type<result_type>::type integer_type;
   typedef typename scalar_type<result_type>::type scalar_type;

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

   boost::uintmax_t counter(max_terms);

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

template <class Gen, class U>
inline typename detail::fraction_traits<Gen>::result_type continued_fraction_b(Gen& g, const U& factor)
   BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename detail::fraction_traits<Gen>::result_type) && noexcept(std::declval<Gen>()()))
{
   boost::uintmax_t max_terms = (std::numeric_limits<boost::uintmax_t>::max)();
   return continued_fraction_b(g, factor, max_terms);
}

template <class Gen>
inline typename detail::fraction_traits<Gen>::result_type continued_fraction_b(Gen& g, int bits)
   BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename detail::fraction_traits<Gen>::result_type) && noexcept(std::declval<Gen>()()))
{
   BOOST_MATH_STD_USING // ADL of std names

   typedef detail::fraction_traits<Gen> traits;
   typedef typename traits::result_type result_type;

   result_type factor = ldexp(1.0f, 1 - bits); // 1 / pow(result_type(2), bits);
   boost::uintmax_t max_terms = (std::numeric_limits<boost::uintmax_t>::max)();
   return continued_fraction_b(g, factor, max_terms);
}

template <class Gen>
inline typename detail::fraction_traits<Gen>::result_type continued_fraction_b(Gen& g, int bits, boost::uintmax_t& max_terms)
   BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename detail::fraction_traits<Gen>::result_type) && noexcept(std::declval<Gen>()()))
{
   BOOST_MATH_STD_USING // ADL of std names

   typedef detail::fraction_traits<Gen> traits;
   typedef typename traits::result_type result_type;

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
template <class Gen, class U>
inline typename detail::fraction_traits<Gen>::result_type continued_fraction_a(Gen& g, const U& factor, boost::uintmax_t& max_terms)
   BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename detail::fraction_traits<Gen>::result_type) && noexcept(std::declval<Gen>()()))
{
   BOOST_MATH_STD_USING // ADL of std names

   typedef detail::fraction_traits<Gen> traits;
   typedef typename traits::result_type result_type;
   typedef typename traits::value_type value_type;
   typedef typename integer_scalar_type<result_type>::type integer_type;
   typedef typename scalar_type<result_type>::type scalar_type;

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

   boost::uintmax_t counter(max_terms);

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

template <class Gen, class U>
inline typename detail::fraction_traits<Gen>::result_type continued_fraction_a(Gen& g, const U& factor)
   BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename detail::fraction_traits<Gen>::result_type) && noexcept(std::declval<Gen>()()))
{
   boost::uintmax_t max_iter = (std::numeric_limits<boost::uintmax_t>::max)();
   return continued_fraction_a(g, factor, max_iter);
}

template <class Gen>
inline typename detail::fraction_traits<Gen>::result_type continued_fraction_a(Gen& g, int bits)
   BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename detail::fraction_traits<Gen>::result_type) && noexcept(std::declval<Gen>()()))
{
   BOOST_MATH_STD_USING // ADL of std names

   typedef detail::fraction_traits<Gen> traits;
   typedef typename traits::result_type result_type;

   result_type factor = ldexp(1.0f, 1-bits); // 1 / pow(result_type(2), bits);
   boost::uintmax_t max_iter = (std::numeric_limits<boost::uintmax_t>::max)();

   return continued_fraction_a(g, factor, max_iter);
}

template <class Gen>
inline typename detail::fraction_traits<Gen>::result_type continued_fraction_a(Gen& g, int bits, boost::uintmax_t& max_terms)
   BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename detail::fraction_traits<Gen>::result_type) && noexcept(std::declval<Gen>()()))
{
   BOOST_MATH_STD_USING // ADL of std names

   typedef detail::fraction_traits<Gen> traits;
   typedef typename traits::result_type result_type;

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