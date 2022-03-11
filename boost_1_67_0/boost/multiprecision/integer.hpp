///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_INTEGER_HPP
#define BOOST_MP_INTEGER_HPP

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/detail/bitscan.hpp>

namespace boost {
namespace multiprecision {

template <class Integer, class I2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value && is_integral<I2>::value, Integer&>::type
multiply(Integer& result, const I2& a, const I2& b)
{
   return result = static_cast<Integer>(a) * static_cast<Integer>(b);
}
template <class Integer, class I2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value && is_integral<I2>::value, Integer&>::type
add(Integer& result, const I2& a, const I2& b)
{
   return result = static_cast<Integer>(a) + static_cast<Integer>(b);
}
template <class Integer, class I2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value && is_integral<I2>::value, Integer&>::type
subtract(Integer& result, const I2& a, const I2& b)
{
   return result = static_cast<Integer>(a) - static_cast<Integer>(b);
}

template <class Integer>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value>::type divide_qr(const Integer& x, const Integer& y, Integer& q, Integer& r)
{
   q = x / y;
   r = x % y;
}

template <class I1, class I2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<I1>::value && is_integral<I2>::value, I2>::type integer_modulus(const I1& x, I2 val)
{
   return static_cast<I2>(x % val);
}

namespace detail {
//
// Figure out the kind of integer that has twice as many bits as some builtin
// integer type I.  Use a native type if we can (including types which may not
// be recognised by boost::int_t because they're larger than boost::long_long_type),
// otherwise synthesize a cpp_int to do the job.
//
template <class I>
struct double_integer
{
   static const unsigned int_t_digits =
       2 * sizeof(I) <= sizeof(boost::long_long_type) ? std::numeric_limits<I>::digits * 2 : 1;

   typedef typename mpl::if_c<
       2 * sizeof(I) <= sizeof(boost::long_long_type),
       typename mpl::if_c<
           is_signed<I>::value,
           typename boost::int_t<int_t_digits>::least,
           typename boost::uint_t<int_t_digits>::least>::type,
       typename mpl::if_c<
           2 * sizeof(I) <= sizeof(double_limb_type),
           typename mpl::if_c<
               is_signed<I>::value,
               signed_double_limb_type,
               double_limb_type>::type,
           number<cpp_int_backend<sizeof(I) * CHAR_BIT * 2, sizeof(I) * CHAR_BIT * 2, (is_signed<I>::value ? signed_magnitude : unsigned_magnitude), unchecked, void> > >::type>::type type;
};

} // namespace detail

template <class I1, class I2, class I3>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<I1>::value && is_unsigned<I2>::value && is_integral<I3>::value, I1>::type
powm(const I1& a, I2 b, I3 c)
{
   typedef typename detail::double_integer<I1>::type double_type;

   I1          x(1), y(a);
   double_type result(0);

   while (b > 0)
   {
      if (b & 1)
      {
         multiply(result, x, y);
         x = integer_modulus(result, c);
      }
      multiply(result, y, y);
      y = integer_modulus(result, c);
      b >>= 1;
   }
   return x % c;
}

template <class I1, class I2, class I3>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<I1>::value && is_signed<I2>::value && is_integral<I3>::value, I1>::type
powm(const I1& a, I2 b, I3 c)
{
   if (b < 0)
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("powm requires a positive exponent."));
   }
   return powm(a, static_cast<typename make_unsigned<I2>::type>(b), c);
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value, unsigned>::type lsb(const Integer& val)
{
   if (val <= 0)
   {
      if (val == 0)
      {
         BOOST_THROW_EXCEPTION(std::range_error("No bits were set in the operand."));
      }
      else
      {
         BOOST_THROW_EXCEPTION(std::range_error("Testing individual bits in negative values is not supported - results are undefined."));
      }
   }
   return detail::find_lsb(val);
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value, unsigned>::type msb(Integer val)
{
   if (val <= 0)
   {
      if (val == 0)
      {
         BOOST_THROW_EXCEPTION(std::range_error("No bits were set in the operand."));
      }
      else
      {
         BOOST_THROW_EXCEPTION(std::range_error("Testing individual bits in negative values is not supported - results are undefined."));
      }
   }
   return detail::find_msb(val);
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value, bool>::type bit_test(const Integer& val, unsigned index)
{
   Integer mask = 1;
   if (index >= sizeof(Integer) * CHAR_BIT)
      return 0;
   if (index)
      mask <<= index;
   return val & mask ? true : false;
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value, Integer&>::type bit_set(Integer& val, unsigned index)
{
   Integer mask = 1;
   if (index >= sizeof(Integer) * CHAR_BIT)
      return val;
   if (index)
      mask <<= index;
   val |= mask;
   return val;
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value, Integer&>::type bit_unset(Integer& val, unsigned index)
{
   Integer mask = 1;
   if (index >= sizeof(Integer) * CHAR_BIT)
      return val;
   if (index)
      mask <<= index;
   val &= ~mask;
   return val;
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value, Integer&>::type bit_flip(Integer& val, unsigned index)
{
   Integer mask = 1;
   if (index >= sizeof(Integer) * CHAR_BIT)
      return val;
   if (index)
      mask <<= index;
   val ^= mask;
   return val;
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value, Integer>::type sqrt(const Integer& x, Integer& r)
{
   //
   // This is slow bit-by-bit integer square root, see for example
   // http://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Binary_numeral_system_.28base_2.29
   // There are better methods such as http://hal.inria.fr/docs/00/07/28/54/PDF/RR-3805.pdf
   // and http://hal.inria.fr/docs/00/07/21/13/PDF/RR-4475.pdf which should be implemented
   // at some point.
   //
   Integer s = 0;
   if (x == 0)
   {
      r = 0;
      return s;
   }
   int g = msb(x);
   if (g == 0)
   {
      r = 1;
      return s;
   }

   Integer t = 0;
   r         = x;
   g /= 2;
   bit_set(s, g);
   bit_set(t, 2 * g);
   r = x - t;
   --g;
   do
   {
      t = s;
      t <<= g + 1;
      bit_set(t, 2 * g);
      if (t <= r)
      {
         bit_set(s, g);
         r -= t;
      }
      --g;
   } while (g >= 0);
   return s;
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value, Integer>::type sqrt(const Integer& x)
{
   Integer r(0);
   return sqrt(x, r);
}

}} // namespace boost::multiprecision

#endif

/* integer.hpp
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
*/