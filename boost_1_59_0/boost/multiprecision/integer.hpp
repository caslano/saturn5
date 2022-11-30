///////////////////////////////////////////////////////////////
//  Copyright 2012-21 John Maddock.
//  Copyright 2021 Iskandarov Lev. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_INTEGER_HPP
#define BOOST_MP_INTEGER_HPP

#include <type_traits>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/detail/bitscan.hpp>
#include <boost/multiprecision/detail/no_exceptions_support.hpp>
#include <boost/multiprecision/detail/standalone_config.hpp>

namespace boost {
namespace multiprecision {

template <class Integer, class I2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<Integer>::value && boost::multiprecision::detail::is_integral<I2>::value, Integer&>::type
multiply(Integer& result, const I2& a, const I2& b)
{
   return result = static_cast<Integer>(a) * static_cast<Integer>(b);
}
template <class Integer, class I2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<Integer>::value && boost::multiprecision::detail::is_integral<I2>::value, Integer&>::type
add(Integer& result, const I2& a, const I2& b)
{
   return result = static_cast<Integer>(a) + static_cast<Integer>(b);
}
template <class Integer, class I2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<Integer>::value && boost::multiprecision::detail::is_integral<I2>::value, Integer&>::type
subtract(Integer& result, const I2& a, const I2& b)
{
   return result = static_cast<Integer>(a) - static_cast<Integer>(b);
}

template <class Integer>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<Integer>::value>::type divide_qr(const Integer& x, const Integer& y, Integer& q, Integer& r)
{
   q = x / y;
   r = x % y;
}

template <class I1, class I2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<I1>::value && boost::multiprecision::detail::is_integral<I2>::value, I2>::type integer_modulus(const I1& x, I2 val)
{
   return static_cast<I2>(x % val);
}

namespace detail {
//
// Figure out the kind of integer that has twice as many bits as some builtin
// integer type I.  Use a native type if we can (including types which may not
// be recognised by boost::int_t because they're larger than long long),
// otherwise synthesize a cpp_int to do the job.
//
template <class I>
struct double_integer
{
   static constexpr const unsigned int_t_digits =
       2 * sizeof(I) <= sizeof(long long) ? std::numeric_limits<I>::digits * 2 : 1;

   using type = typename std::conditional<
       2 * sizeof(I) <= sizeof(long long),
       typename std::conditional<
           boost::multiprecision::detail::is_signed<I>::value && boost::multiprecision::detail::is_integral<I>::value,
           typename boost::multiprecision::detail::int_t<int_t_digits>::least,
           typename boost::multiprecision::detail::uint_t<int_t_digits>::least>::type,
       typename std::conditional<
           2 * sizeof(I) <= sizeof(double_limb_type),
           typename std::conditional<
               boost::multiprecision::detail::is_signed<I>::value && boost::multiprecision::detail::is_integral<I>::value,
               signed_double_limb_type,
               double_limb_type>::type,
           number<cpp_int_backend<sizeof(I) * CHAR_BIT * 2, sizeof(I) * CHAR_BIT * 2, (boost::multiprecision::detail::is_signed<I>::value ? signed_magnitude : unsigned_magnitude), unchecked, void> > >::type>::type;
};

} // namespace detail

template <class I1, class I2, class I3>
BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<I1>::value && boost::multiprecision::detail::is_unsigned<I2>::value && boost::multiprecision::detail::is_integral<I3>::value, I1>::type
powm(const I1& a, I2 b, I3 c)
{
   using double_type = typename detail::double_integer<I1>::type;

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
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<I1>::value && boost::multiprecision::detail::is_signed<I2>::value && boost::multiprecision::detail::is_integral<I2>::value && boost::multiprecision::detail::is_integral<I3>::value, I1>::type
powm(const I1& a, I2 b, I3 c)
{
   if (b < 0)
   {
      BOOST_MP_THROW_EXCEPTION(std::runtime_error("powm requires a positive exponent."));
   }
   return powm(a, static_cast<typename boost::multiprecision::detail::make_unsigned<I2>::type>(b), c);
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<Integer>::value, std::size_t>::type lsb(const Integer& val)
{
   if (val <= 0)
   {
      if (val == 0)
      {
         BOOST_MP_THROW_EXCEPTION(std::domain_error("No bits were set in the operand."));
      }
      else
      {
         BOOST_MP_THROW_EXCEPTION(std::domain_error("Testing individual bits in negative values is not supported - results are undefined."));
      }
   }
   return detail::find_lsb(val);
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<Integer>::value, std::size_t>::type msb(Integer val)
{
   if (val <= 0)
   {
      if (val == 0)
      {
         BOOST_MP_THROW_EXCEPTION(std::domain_error("No bits were set in the operand."));
      }
      else
      {
         BOOST_MP_THROW_EXCEPTION(std::domain_error("Testing individual bits in negative values is not supported - results are undefined."));
      }
   }
   return detail::find_msb(val);
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<Integer>::value, bool>::type bit_test(const Integer& val, std::size_t index)
{
   Integer mask = 1;
   if (index >= sizeof(Integer) * CHAR_BIT)
      return 0;
   if (index)
      mask <<= index;
   return val & mask ? true : false;
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<Integer>::value, Integer&>::type bit_set(Integer& val, std::size_t index)
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
BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<Integer>::value, Integer&>::type bit_unset(Integer& val, std::size_t index)
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
BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<Integer>::value, Integer&>::type bit_flip(Integer& val, std::size_t index)
{
   Integer mask = 1;
   if (index >= sizeof(Integer) * CHAR_BIT)
      return val;
   if (index)
      mask <<= index;
   val ^= mask;
   return val;
}

namespace detail {

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR Integer karatsuba_sqrt(const Integer& x, Integer& r, size_t bits)
{
   //
   // Define the floating point type used for std::sqrt, in our tests, sqrt(double) and sqrt(long double) take
   // about the same amount of time as long as long double is not an emulated 128-bit type (ie the same type
   // as __float128 from libquadmath).  So only use long double if it's an 80-bit type:
   //
#ifndef __clang__
   typedef typename std::conditional<(std::numeric_limits<long double>::digits == 64), long double, double>::type real_cast_type;
#else
   // clang has buggy __int128 -> long double conversion:
   typedef double real_cast_type;
#endif
   //
   // As per the Karatsuba sqrt algorithm, the low order bits/4 bits pay no part in the result, only in the remainder,
   // so define the number of bits our argument must have before passing to std::sqrt is safe, even if doing so
   // looses a few bits:
   //
   constexpr std::size_t cutoff = (std::numeric_limits<real_cast_type>::digits * 4) / 3;
   //
   // Type which can hold at least "cutoff" bits:
   // 
#ifdef BOOST_HAS_INT128
   using cutoff_t = typename std::conditional<(cutoff > 64), uint128_type, std::uint64_t>::type;
#else
   using cutoff_t = std::uint64_t;
#endif
   //
   // See if we can take the fast path:
   //
   if (bits <= cutoff)
   {
      constexpr cutoff_t half_bits = (cutoff_t(1u) << ((sizeof(cutoff_t) * CHAR_BIT) / 2)) - 1;
      cutoff_t       val = static_cast<cutoff_t>(x);
      real_cast_type real_val = static_cast<real_cast_type>(val);
      cutoff_t       s64 = static_cast<cutoff_t>(std::sqrt(real_val));
      // converting to long double can loose some precision, and `sqrt` can give eps error, so we'll fix this
      // this is needed
      while ((s64 > half_bits) || (s64 * s64 > val))
         s64--;
      // in my tests this never fired, but theoretically this might be needed
      while ((s64 < half_bits) && ((s64 + 1) * (s64 + 1) <= val))
         s64++;
      r = static_cast<Integer>(val - s64 * s64);
      return static_cast<Integer>(s64);
   }
   // https://hal.inria.fr/file/index/docid/72854/filename/RR-3805.pdf
   std::size_t b = bits / 4;
   Integer q = x;
   q >>= b * 2;
   Integer s = karatsuba_sqrt(q, r, bits - b * 2);
   Integer t = 0u;
   bit_set(t, static_cast<unsigned>(b * 2));
   r <<= b;
   t--;
   t &= x;
   t >>= b;
   t += r;
   s <<= 1;
   divide_qr(t, s, q, r);
   r <<= b;
   t = 0u;
   bit_set(t, static_cast<unsigned>(b));
   t--;
   t &= x;
   r += t;
   s <<= (b - 1); // we already <<1 it before
   s += q;
   q *= q;
   // we substract after, so it works for unsigned integers too
   if (r < q)
   {
      t = s;
      t <<= 1;
      t--;
      r += t;
      s--;
   }
   r -= q;
   return s;
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR Integer bitwise_sqrt(const Integer& x, Integer& r)
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
   std::ptrdiff_t g = msb(x);
   if (g == 0)
   {
      r = 1;
      return s;
   }

   Integer t = 0;
   r = x;
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

} // namespace detail

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<Integer>::value, Integer>::type sqrt(const Integer& x, Integer& r)
{
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   // recursive Karatsuba sqrt can cause issues in constexpr context:
   if (BOOST_MP_IS_CONST_EVALUATED(x))
      return detail::bitwise_sqrt(x, r);
#endif
   if (x == 0u) {
      r = 0u;
      return 0u;
   }

   return detail::karatsuba_sqrt(x, r, msb(x) + 1);
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<Integer>::value, Integer>::type sqrt(const Integer& x)
{
   Integer r(0);
   return sqrt(x, r);
}

}} // namespace boost::multiprecision

#endif

/* integer.hpp
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
*/