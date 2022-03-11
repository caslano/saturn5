
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CPP_INT_CHECKED_HPP
#define BOOST_MP_CPP_INT_CHECKED_HPP

namespace boost { namespace multiprecision { namespace backends { namespace detail {

//
// Simple routines for performing checked arithmetic with a builtin arithmetic type.
// Note that this is not a complete header, it must be included as part of boost/multiprecision/cpp_int.hpp.
//

inline void raise_overflow(std::string op)
{
   BOOST_THROW_EXCEPTION(std::overflow_error("overflow in " + op));
}
inline void raise_add_overflow()
{
   raise_overflow("addition");
}
inline void raise_subtract_overflow()
{
   BOOST_THROW_EXCEPTION(std::range_error("Subtraction resulted in a negative value, but the type is unsigned"));
}
inline void raise_mul_overflow()
{
   raise_overflow("multiplication");
}
inline void raise_div_overflow()
{
   raise_overflow("division");
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_add_imp(A a, A b, const mpl::true_&)
{
   if (a > 0)
   {
      if ((b > 0) && ((integer_traits<A>::const_max - b) < a))
         raise_add_overflow();
   }
   else
   {
      if ((b < 0) && ((integer_traits<A>::const_min - b) > a))
         raise_add_overflow();
   }
   return a + b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_add_imp(A a, A b, const mpl::false_&)
{
   if ((integer_traits<A>::const_max - b) < a)
      raise_add_overflow();
   return a + b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_add(A a, A b, const mpl::int_<checked>&)
{
   return checked_add_imp(a, b, mpl::bool_<boost::is_signed<A>::value>());
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_add(A a, A b, const mpl::int_<unchecked>&)
{
   return a + b;
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_subtract_imp(A a, A b, const mpl::true_&)
{
   if (a > 0)
   {
      if ((b < 0) && ((integer_traits<A>::const_max + b) < a))
         raise_subtract_overflow();
   }
   else
   {
      if ((b > 0) && ((integer_traits<A>::const_min + b) > a))
         raise_subtract_overflow();
   }
   return a - b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_subtract_imp(A a, A b, const mpl::false_&)
{
   if (a < b)
      raise_subtract_overflow();
   return a - b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_subtract(A a, A b, const mpl::int_<checked>&)
{
   return checked_subtract_imp(a, b, mpl::bool_<boost::is_signed<A>::value>());
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_subtract(A a, A b, const mpl::int_<unchecked>&)
{
   return a - b;
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_multiply(A a, A b, const mpl::int_<checked>&)
{
   BOOST_MP_USING_ABS
   if (a && (integer_traits<A>::const_max / abs(a) < abs(b)))
      raise_mul_overflow();
   return a * b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_multiply(A a, A b, const mpl::int_<unchecked>&)
{
   return a * b;
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_divide(A a, A b, const mpl::int_<checked>&)
{
   if (b == 0)
      raise_div_overflow();
   return a / b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_divide(A a, A b, const mpl::int_<unchecked>&)
{
   return a / b;
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_left_shift(A a, boost::ulong_long_type shift, const mpl::int_<checked>&)
{
   if (a && shift)
   {
      if ((shift > sizeof(A) * CHAR_BIT) || (a >> (sizeof(A) * CHAR_BIT - shift)))
         BOOST_THROW_EXCEPTION(std::overflow_error("Shift out of range"));
   }
   return a << shift;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_left_shift(A a, boost::ulong_long_type shift, const mpl::int_<unchecked>&)
{
   return (shift >= sizeof(A) * CHAR_BIT) ? 0 : a << shift;
}

}}}} // namespace boost::multiprecision::backends::detail

#endif

/* checked.hpp
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
*/