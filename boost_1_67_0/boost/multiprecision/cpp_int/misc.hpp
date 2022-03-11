///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//
// Comparison operators for cpp_int_backend:
//
#ifndef BOOST_MP_CPP_INT_MISC_HPP
#define BOOST_MP_CPP_INT_MISC_HPP

#include <boost/multiprecision/detail/constexpr.hpp>
#include <boost/multiprecision/detail/bitscan.hpp> // lsb etc
#include <boost/integer/common_factor_rt.hpp>      // gcd/lcm
#include <boost/functional/hash_fwd.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4702)
#pragma warning(disable : 4127) // conditional expression is constant
#pragma warning(disable : 4146) // unary minus operator applied to unsigned type, result still unsigned
#endif

namespace boost { namespace multiprecision { namespace backends {

template <class R, class CppInt>
BOOST_MP_CXX14_CONSTEXPR void check_in_range(const CppInt& val, const mpl::int_<checked>&)
{
   typedef typename boost::multiprecision::detail::canonical<R, CppInt>::type cast_type;
   if (val.sign())
   {
      if (boost::is_signed<R>::value == false)
         BOOST_THROW_EXCEPTION(std::range_error("Attempt to assign a negative value to an unsigned type."));
      if (val.compare(static_cast<cast_type>((std::numeric_limits<R>::min)())) < 0)
         BOOST_THROW_EXCEPTION(std::overflow_error("Could not convert to the target type - -value is out of range."));
   }
   else
   {
      if (val.compare(static_cast<cast_type>((std::numeric_limits<R>::max)())) > 0)
         BOOST_THROW_EXCEPTION(std::overflow_error("Could not convert to the target type - -value is out of range."));
   }
}
template <class R, class CppInt>
inline BOOST_MP_CXX14_CONSTEXPR void check_in_range(const CppInt& /*val*/, const mpl::int_<unchecked>&) BOOST_NOEXCEPT {}

inline BOOST_MP_CXX14_CONSTEXPR void check_is_negative(const mpl::true_&) BOOST_NOEXCEPT {}
inline void check_is_negative(const mpl::false_&)
{
   BOOST_THROW_EXCEPTION(std::range_error("Attempt to assign a negative value to an unsigned type."));
}

template <class Integer>
inline BOOST_MP_CXX14_CONSTEXPR Integer negate_integer(Integer i, const mpl::true_&) BOOST_NOEXCEPT
{
   return -i;
}
template <class Integer>
inline BOOST_MP_CXX14_CONSTEXPR Integer negate_integer(Integer i, const mpl::false_&) BOOST_NOEXCEPT
{
   return ~(i - 1);
}

template <class R, unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<R>::value && !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value, void>::type
eval_convert_to(R* result, const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& backend)
{
   typedef mpl::int_<Checked1> checked_type;
   check_in_range<R>(backend, checked_type());

   if (std::numeric_limits<R>::digits < cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits)
   {
      if ((backend.sign() && boost::is_signed<R>::value) && (1 + static_cast<boost::multiprecision::limb_type>((std::numeric_limits<R>::max)()) <= backend.limbs()[0]))
      {
         *result = (std::numeric_limits<R>::min)();
         return;
      }
      else if (boost::is_signed<R>::value && !backend.sign() && static_cast<boost::multiprecision::limb_type>((std::numeric_limits<R>::max)()) <= backend.limbs()[0])
      {
         *result = (std::numeric_limits<R>::max)();
         return;
      }
      else
         *result = static_cast<R>(backend.limbs()[0]);
   }
   else
      *result = static_cast<R>(backend.limbs()[0]);
   unsigned shift = cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits;
   unsigned i     = 1;
   if (std::numeric_limits<R>::digits > cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits)
   {
      while ((i < backend.size()) && (shift < static_cast<unsigned>(std::numeric_limits<R>::digits - cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits)))
      {
         *result += static_cast<R>(backend.limbs()[i]) << shift;
         shift += cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits;
         ++i;
      }
      //
      // We have one more limb to extract, but may not need all the bits, so treat this as a special case:
      //
      if (i < backend.size())
      {
         const limb_type mask = std::numeric_limits<R>::digits - shift == cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits ? ~static_cast<limb_type>(0) : (static_cast<limb_type>(1u) << (std::numeric_limits<R>::digits - shift)) - 1;
         *result += (static_cast<R>(backend.limbs()[i]) & mask) << shift;
         if ((static_cast<R>(backend.limbs()[i]) & static_cast<limb_type>(~mask)) || (i + 1 < backend.size()))
         {
            // Overflow:
            if (backend.sign())
            {
               check_is_negative(boost::is_signed<R>());
               *result = (std::numeric_limits<R>::min)();
            }
            else if (boost::is_signed<R>::value)
               *result = (std::numeric_limits<R>::max)();
            return;
         }
      }
   }
   else if (backend.size() > 1)
   {
      // Overflow:
      if (backend.sign())
      {
         check_is_negative(boost::is_signed<R>());
         *result = (std::numeric_limits<R>::min)();
      }
      else if (boost::is_signed<R>::value)
         *result = (std::numeric_limits<R>::max)();
      return;
   }
   if (backend.sign())
   {
      check_is_negative(mpl::bool_<boost::is_signed<R>::value>());
      *result = negate_integer(*result, mpl::bool_<boost::is_signed<R>::value>());
   }
}

template <class R, unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_floating_point<R>::value && !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value, void>::type
eval_convert_to(R* result, const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& backend) BOOST_MP_NOEXCEPT_IF(is_arithmetic<R>::value)
{
   typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::const_limb_pointer p     = backend.limbs();
   unsigned                                                                                          shift = cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits;
   *result                                                                                                 = static_cast<R>(*p);
   for (unsigned i = 1; i < backend.size(); ++i)
   {
      *result += static_cast<R>(std::ldexp(static_cast<long double>(p[i]), shift));
      shift += cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits;
   }
   if (backend.sign())
      *result = -*result;
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value, bool>::type
eval_is_zero(const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& val) BOOST_NOEXCEPT
{
   return (val.size() == 1) && (val.limbs()[0] == 0);
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value, int>::type
eval_get_sign(const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& val) BOOST_NOEXCEPT
{
   return eval_is_zero(val) ? 0 : val.sign() ? -1 : 1;
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_abs(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& val) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   result = val;
   result.sign(false);
}

//
// Get the location of the least-significant-bit:
//
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value, unsigned>::type
eval_lsb(const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a)
{
   using default_ops::eval_get_sign;
   if (eval_get_sign(a) == 0)
   {
      BOOST_THROW_EXCEPTION(std::range_error("No bits were set in the operand."));
   }
   if (a.sign())
   {
      BOOST_THROW_EXCEPTION(std::range_error("Testing individual bits in negative values is not supported - results are undefined."));
   }

   //
   // Find the index of the least significant limb that is non-zero:
   //
   unsigned index = 0;
   while (!a.limbs()[index] && (index < a.size()))
      ++index;
   //
   // Find the index of the least significant bit within that limb:
   //
   unsigned result = boost::multiprecision::detail::find_lsb(a.limbs()[index]);

   return result + index * cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits;
}

//
// Get the location of the most-significant-bit:
//
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value, unsigned>::type
eval_msb_imp(const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a)
{
   //
   // Find the index of the most significant bit that is non-zero:
   //
   return (a.size() - 1) * cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits + boost::multiprecision::detail::find_msb(a.limbs()[a.size() - 1]);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value, unsigned>::type
eval_msb(const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a)
{
   using default_ops::eval_get_sign;
   if (eval_get_sign(a) == 0)
   {
      BOOST_THROW_EXCEPTION(std::range_error("No bits were set in the operand."));
   }
   if (a.sign())
   {
      BOOST_THROW_EXCEPTION(std::range_error("Testing individual bits in negative values is not supported - results are undefined."));
   }
   return eval_msb_imp(a);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value, bool>::type
eval_bit_test(const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& val, unsigned index) BOOST_NOEXCEPT
{
   unsigned  offset = index / cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits;
   unsigned  shift  = index % cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits;
   limb_type mask   = shift ? limb_type(1u) << shift : limb_type(1u);
   if (offset >= val.size())
      return false;
   return val.limbs()[offset] & mask ? true : false;
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_bit_set(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& val, unsigned index)
{
   unsigned  offset = index / cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits;
   unsigned  shift  = index % cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits;
   limb_type mask   = shift ? limb_type(1u) << shift : limb_type(1u);
   if (offset >= val.size())
   {
      unsigned os = val.size();
      val.resize(offset + 1, offset + 1);
      if (offset >= val.size())
         return; // fixed precision overflow
      for (unsigned i = os; i <= offset; ++i)
         val.limbs()[i] = 0;
   }
   val.limbs()[offset] |= mask;
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_bit_unset(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& val, unsigned index) BOOST_NOEXCEPT
{
   unsigned  offset = index / cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits;
   unsigned  shift  = index % cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits;
   limb_type mask   = shift ? limb_type(1u) << shift : limb_type(1u);
   if (offset >= val.size())
      return;
   val.limbs()[offset] &= ~mask;
   val.normalize();
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_bit_flip(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& val, unsigned index)
{
   unsigned  offset = index / cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits;
   unsigned  shift  = index % cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::limb_bits;
   limb_type mask   = shift ? limb_type(1u) << shift : limb_type(1u);
   if (offset >= val.size())
   {
      unsigned os = val.size();
      val.resize(offset + 1, offset + 1);
      if (offset >= val.size())
         return; // fixed precision overflow
      for (unsigned i = os; i <= offset; ++i)
         val.limbs()[i] = 0;
   }
   val.limbs()[offset] ^= mask;
   val.normalize();
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_qr(
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& x,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& y,
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       q,
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       r) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   divide_unsigned_helper(&q, x, y, r);
   q.sign(x.sign() != y.sign());
   r.sign(x.sign());
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_qr(
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& x,
    limb_type                                                                   y,
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       q,
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       r) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   divide_unsigned_helper(&q, x, y, r);
   q.sign(x.sign());
   r.sign(x.sign());
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, class U>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<U>::value>::type eval_qr(
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& x,
    U                                                                           y,
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       q,
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       r) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   using default_ops::eval_qr;
   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> t;
   t = y;
   eval_qr(x, t, q, r);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, class Integer>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_unsigned<Integer>::value && !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value, Integer>::type
eval_integer_modulus(const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& x, Integer val)
{
   if ((sizeof(Integer) <= sizeof(limb_type)) || (val <= (std::numeric_limits<limb_type>::max)()))
   {
      cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> d;
      divide_unsigned_helper(static_cast<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>*>(0), x, static_cast<limb_type>(val), d);
      return d.limbs()[0];
   }
   else
   {
      return default_ops::eval_integer_modulus(x, val);
   }
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, class Integer>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_signed<Integer>::value && !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value, Integer>::type
eval_integer_modulus(const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& x, Integer val)
{
   return eval_integer_modulus(x, boost::multiprecision::detail::unsigned_abs(val));
}

inline BOOST_MP_CXX14_CONSTEXPR limb_type integer_gcd_reduce(limb_type u, limb_type v)
{
   do
   {
      if (u > v)
         std_constexpr::swap(u, v);
      if (u == v)
         break;
      v -= u;
      v >>= boost::multiprecision::detail::find_lsb(v);
   } while (true);
   return u;
}

inline BOOST_MP_CXX14_CONSTEXPR double_limb_type integer_gcd_reduce(double_limb_type u, double_limb_type v)
{
   do
   {
      if (u > v)
         std_constexpr::swap(u, v);
      if (u == v)
         break;
      if (v <= ~static_cast<limb_type>(0))
      {
         u = integer_gcd_reduce(static_cast<limb_type>(v), static_cast<limb_type>(u));
         break;
      }
      v -= u;
#ifdef __MSVC_RUNTIME_CHECKS
      while ((v & 1u) == 0)
#else
      while ((static_cast<unsigned>(v) & 1u) == 0)
#endif
         v >>= 1;
   } while (true);
   return u;
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_gcd(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a,
    limb_type                                                                   v)
{
   using default_ops::eval_get_sign;
   using default_ops::eval_is_zero;
   using default_ops::eval_lsb;

   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> u(a);

   int s = eval_get_sign(u);

   /* GCD(0,x) := x */
   if (s < 0)
   {
      u.negate();
   }
   else if (s == 0)
   {
      result = v;
      return;
   }
   if (v == 0)
   {
      result = u;
      return;
   }

   /* Let shift := lg K, where K is the greatest power of 2
   dividing both u and v. */

   unsigned us = eval_lsb(u);
   unsigned vs = boost::multiprecision::detail::find_lsb(v);
   int shift   = (std::min)(us, vs);
   eval_right_shift(u, us);
   if (vs)
      v >>= vs;

   do
   {
      /* Now u and v are both odd, so diff(u, v) is even.
      Let u = min(u, v), v = diff(u, v)/2. */
      if (u.size() <= 2)
      {
         if (u.size() == 1)
            v = integer_gcd_reduce(*u.limbs(), v);
         else
         {
            double_limb_type i = u.limbs()[0] | (static_cast<double_limb_type>(u.limbs()[1]) << sizeof(limb_type) * CHAR_BIT);
            v = static_cast<limb_type>(integer_gcd_reduce(i, static_cast<double_limb_type>(v)));
         }
         break;
      }
      eval_subtract(u, v);
      us = eval_lsb(u);
      eval_right_shift(u, us);
   } while (true);

   result = v;
   eval_left_shift(result, shift);
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, class Integer>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_unsigned<Integer>::value && (sizeof(Integer) <= sizeof(limb_type)) && !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_gcd(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a,
    const Integer&                                                              v)
{
   eval_gcd(result, a, static_cast<limb_type>(v));
}
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1, class Integer>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_signed<Integer>::value && (sizeof(Integer) <= sizeof(limb_type)) && !is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_gcd(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a,
    const Integer&                                                              v)
{
   eval_gcd(result, a, static_cast<limb_type>(v < 0 ? -v : v));
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<!is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_gcd(
    cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>&       result,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a,
    const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& b)
{
   using default_ops::eval_get_sign;
   using default_ops::eval_is_zero;
   using default_ops::eval_lsb;

   if (a.size() == 1)
   {
      eval_gcd(result, b, *a.limbs());
      return;
   }
   if (b.size() == 1)
   {
      eval_gcd(result, a, *b.limbs());
      return;
   }

   cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> u(a), v(b);

   int s = eval_get_sign(u);

   /* GCD(0,x) := x */
   if (s < 0)
   {
      u.negate();
   }
   else if (s == 0)
   {
      result = v;
      return;
   }
   s = eval_get_sign(v);
   if (s < 0)
   {
      v.negate();
   }
   else if (s == 0)
   {
      result = u;
      return;
   }

   /* Let shift := lg K, where K is the greatest power of 2
   dividing both u and v. */

   unsigned us = eval_lsb(u);
   unsigned vs = eval_lsb(v);
   int shift   = (std::min)(us, vs);
   eval_right_shift(u, us);
   eval_right_shift(v, vs);

   do
   {
      /* Now u and v are both odd, so diff(u, v) is even.
      Let u = min(u, v), v = diff(u, v)/2. */
      s = u.compare(v);
      if (s > 0)
         u.swap(v);
      if (s == 0)
         break;
      if (v.size() <= 2)
      {
         if (v.size() == 1)
            u = integer_gcd_reduce(*v.limbs(), *u.limbs());
         else
         {
            double_limb_type i = v.limbs()[0] | (static_cast<double_limb_type>(v.limbs()[1]) << sizeof(limb_type) * CHAR_BIT);
            double_limb_type j = (u.size() == 1) ? *u.limbs() : u.limbs()[0] | (static_cast<double_limb_type>(u.limbs()[1]) << sizeof(limb_type) * CHAR_BIT);
            u = integer_gcd_reduce(i, j);
         }
         break;
      }
      eval_subtract(v, u);
      vs = eval_lsb(v);
      eval_right_shift(v, vs);
   } while (true);

   result = u;
   eval_left_shift(result, shift);
}
//
// Now again for trivial backends:
//
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value>::type
eval_gcd(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a, const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& b) BOOST_NOEXCEPT
{
   *result.limbs() = boost::integer::gcd(*a.limbs(), *b.limbs());
}
// This one is only enabled for unchecked cpp_int's, for checked int's we need the checking in the default version:
template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && (Checked1 == unchecked)>::type
eval_lcm(cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& result, const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a, const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& b) BOOST_MP_NOEXCEPT_IF((is_non_throwing_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value))
{
   *result.limbs() = boost::integer::lcm(*a.limbs(), *b.limbs());
   result.normalize(); // result may overflow the specified number of bits
}

inline void conversion_overflow(const mpl::int_<checked>&)
{
   BOOST_THROW_EXCEPTION(std::overflow_error("Overflow in conversion to narrower type"));
}
inline BOOST_MP_CXX14_CONSTEXPR void conversion_overflow(const mpl::int_<unchecked>&) {}

template <class R, unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_signed_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && boost::is_convertible<typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::local_limb_type, R>::value>::type
eval_convert_to(R* result, const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& val)
{
   typedef typename common_type<R, typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::local_limb_type>::type common_type;
   if (std::numeric_limits<R>::is_specialized && (static_cast<common_type>(*val.limbs()) > static_cast<common_type>((std::numeric_limits<R>::max)())))
   {
      if (val.isneg())
      {
         check_is_negative(mpl::bool_ < boost::is_signed<R>::value || (number_category<R>::value == number_kind_floating_point) > ());
         if (static_cast<common_type>(*val.limbs()) > -static_cast<common_type>((std::numeric_limits<R>::min)()))
            conversion_overflow(typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
         *result = (std::numeric_limits<R>::min)();
      }
      else
      {
         conversion_overflow(typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
         *result = boost::is_signed<R>::value ? (std::numeric_limits<R>::max)() : static_cast<R>(*val.limbs());
      }
   }
   else
   {
      *result = static_cast<R>(*val.limbs());
      if (val.isneg())
      {
         check_is_negative(mpl::bool_ < boost::is_signed<R>::value || (number_category<R>::value == number_kind_floating_point) > ());
         *result = negate_integer(*result, mpl::bool_ < is_signed_number<R>::value || (number_category<R>::value == number_kind_floating_point) > ());
      }
   }
}

template <class R, unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<
    is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && is_unsigned_number<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value && boost::is_convertible<typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::local_limb_type, R>::value>::type
eval_convert_to(R* result, const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& val)
{
   typedef typename common_type<R, typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::local_limb_type>::type common_type;
   if (std::numeric_limits<R>::is_specialized && (static_cast<common_type>(*val.limbs()) > static_cast<common_type>((std::numeric_limits<R>::max)())))
   {
      conversion_overflow(typename cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>::checked_type());
      *result = boost::is_signed<R>::value ? (std::numeric_limits<R>::max)() : static_cast<R>(*val.limbs());
   }
   else
      *result = static_cast<R>(*val.limbs());
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value, unsigned>::type
eval_lsb(const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a)
{
   using default_ops::eval_get_sign;
   if (eval_get_sign(a) == 0)
   {
      BOOST_THROW_EXCEPTION(std::range_error("No bits were set in the operand."));
   }
   if (a.sign())
   {
      BOOST_THROW_EXCEPTION(std::range_error("Testing individual bits in negative values is not supported - results are undefined."));
   }
   //
   // Find the index of the least significant bit within that limb:
   //
   return boost::multiprecision::detail::find_lsb(*a.limbs());
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value, unsigned>::type
eval_msb_imp(const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a)
{
   //
   // Find the index of the least significant bit within that limb:
   //
   return boost::multiprecision::detail::find_msb(*a.limbs());
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_trivial_cpp_int<cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1> >::value, unsigned>::type
eval_msb(const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& a)
{
   using default_ops::eval_get_sign;
   if (eval_get_sign(a) == 0)
   {
      BOOST_THROW_EXCEPTION(std::range_error("No bits were set in the operand."));
   }
   if (a.sign())
   {
      BOOST_THROW_EXCEPTION(std::range_error("Testing individual bits in negative values is not supported - results are undefined."));
   }
   return eval_msb_imp(a);
}

template <unsigned MinBits1, unsigned MaxBits1, cpp_integer_type SignType1, cpp_int_check_type Checked1, class Allocator1>
inline BOOST_MP_CXX14_CONSTEXPR std::size_t hash_value(const cpp_int_backend<MinBits1, MaxBits1, SignType1, Checked1, Allocator1>& val) BOOST_NOEXCEPT
{
   std::size_t result = 0;
   for (unsigned i = 0; i < val.size(); ++i)
   {
      boost::hash_combine(result, val.limbs()[i]);
   }
   boost::hash_combine(result, val.sign());
   return result;
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

}}} // namespace boost::multiprecision::backends

#endif

/* misc.hpp
rxCQvgExzJNVqQLGSkQMX1WJeRAZfpWcV+LZqfAB7HYMBKgCbDUB7Yb/N1bJLEteNnUW58kcVAHtOs9sVXDPqAdwxTGwqUQE/upB7jcggTmyc/WXz/8d9opRj1dY58E9qx7AfsfAunmyl1K4tjqg3egZ+vYGEOlm8AwlvwGFzZORqQB81Z+zZvQD4bDkh/+LUfcOaCrYFr0FBKRLUTqoSJEqvRMRAQHpvXdp0kU6QRBQepEiHWnSQXqN1NBDB2mhh95DC0m+eM599917v+s754/f3jNrrzWzZq2ZPbMD65hQq/8AjGqim2/vTTHn6ABvW2+slZAnz+DgZsyjf8zNK8xClYKDYVNohxkvzH2a2VwDGKCJdO+4WVfZjePDzMjvKAM9YIAu0v3jDaAbM66r9Jt1TLyJppmhmC1DGxigjTzhgYMbMXVNtB3jpSkcjIncUQlAb4oZitlRMK8xzB5CAQeTTTMDtIC3BkiYA9Mr4C1mcmjDwZApZoA+8PYl8kQFDi7cjROGg21344am0eKjLNPMC9PM+pgdXgtoUoEywLSVj2rSQ7pn3az7mYNxlw4x4YzB7EolAJEpZhBmiSsgT4zhYMwsw7wrb2WRJzm7aKmjiMz+sLEIzXdddz90CblMFPBVbraRns3RGrsJcuczlzWJi1QT4ZmttKkhWPjsRxWAiy8RLHOmCJamwgvF57lI8v08DCVI8kVljKxeTch8449qU8WFopvkQZyFBqbcfqFYnYqp42Pqru96GWtCJDHHKwV0wOjeFDPiB+BCF7hfjJozR7pTw8Gm08ze2kDiMsAhZnlH3IB6EKCb9ezdOP8SAKkGcNEYaT5xm4BqirtZfwEHY/Yj/BL0UBsao445lIJurDHz8A4c3InZDzSBUhrIk0dwcOg0M5kmWt8HrQ+U0kG6f75Zx2wXmGWE0sOczeFgaAmgD7OsSgGk2miBIzRmyZUCmApRPnU36/y7cQT/Zwv556IDDf5x58tuHGZhsGH2ET2gFGZK6sDB5LtxmIRgVmt2EYroT1eYvUMME/D3cPPc5ur8UF1vzFT6thtnVwIowixFjF4FCr2CxIy57Wb9LhyMaRL2A/B2ihmiC8wsQPlg3vU2cGDMpS8cjJlKfJilYIB0L71ZZ92NSy0FmBWhfpBkEJphlpEq0hwWaPZnm1hnxiwzzMRXRvJjfK2/WRfejcMcAEcxy7AEReSbg0l60o117c06fDcOcxpc/oESU0GeQDCVEsByOcrVnlcdiNkTTvTg4AXMvpUD516u/I/9IA6zk7ZiFp0eWmQZswiOdIFt6kj3hpt182nm/9wKrnJv1uV248jK0BltmHc4ZiuY+/7fVhrwNuNmPQmz4PXRjT4Yd/65EaxjdkAIZucoQ4mpI0/E4UCVWcEx5j+PZZHQLczQ/nP5AAP0ke4JN+v+u3EP4ODLaWbqMvQCYImPWCLOeXT9hBRE1n0l0+dGwHZCObxil9Yt8XBsp2v9402TBr2IJYnoZN9qazk7TQ+VgptQnztxkRv2W/cnIuthBgH6syzHPitwg0766lgnYXWTHj/yrZNffGRbJwbnkzJxYmXXcIJTkrQ+NVNGEuCi6vO4DCsilzDb/TDdRXL6ucayjrm0S3LidRea7udsJ3eGV8jT/NVnFbeJzAzVqz+t15CwW5CwO+LUd11j4Z0QRq8k04DLnoeJD6/Vz0XPWpPbWXKhaP/x1fjwHATZI5bzkVQ4kX2zIpfW959vrZMkpnMwX00kybuVWRqD4ROC8BP86FW6kdST+YrtOFcL0rixgAc4rePM/hb0Fz10LoUkM2Riar8euYSSt0XlWDOI/sZs7ceYNugAs29NwuXfSXxC3XgZdKrWxGaNgz7BMrZYt2fb7opi8GdSBi4anmETO5gFRziaBcsJ8f3qxkApzPcLYG92nCfKTrC+lE5tEbWFe9W0hSumeIZ9q3OGvah3psvw3ReLqcIXK3YKb1+xzdy+I5LaqSMyFXOvUJxkNu/h7vg40nQ36upxw5qiQWdcTazuOXDYLzkXIBOrGYD5bsWf9DmpiQ1POWRNA6vU4PJ1C6h1c8pEkwRQ4ejGQtQKAIef+TNzCgAdmVPU1JItIgsDq8YGv+QNui4Tb0KMZujLVyPm55CfQNh4NZHk+wECSHfBN5bUw2t6c9EL1uQRsQUAprAHbdh7PvVbQzk/ZezNQhqdzEK8LbCP+oRGFajRkb7csVPU9meoYNuA+2VX90WOLYkD+vZwu684+o4J3qwlpXWCrEnl8rfjiq0IFC3oY3voYicU4LBMfYv7ZNIxqLQ+sdhuKpkow3e9bxeF5IGLDMY1fHrPQ73a7iDNj1GRj8utqPhm2+7lYKDOjfKPyQOQ0uTzBW1dPRwSexfdkZu1zvPOghDH/DSAQQV4brsTp5rWo5bWeZiGOC3eOyKQGUkiNPc7K5hIXZYqOVBxzdZBTGSwi6u0+2q5lYiKRnLDtxROCpcXOerPwb7jE8wweZX2aw33ElFmR9PdkQjOP7XAElHq09m2a/UfWyPA78KuqKQfvmc570cy0E1/KlW+Z1kp6aLQZxgVtfqtES86YddKSgNMoWuorVnt3TfRWSXesy2Jb7bLJuyNwxl7VCm+nlkTAq6Vkw2Y2lSK7xmDXbMohID3cks0YXP5lq1jMQNakOJ/9m3fw1Vmsm0xA0KViqnNbC4zFP1czABNpfp7PkATulZSGK2OaH/navNVtgoTVVeqOt56dkjoGpRovjqibqTnc5Z0SujqomW6OqJKx9XWrJSLBPsqtYpefq7394yzwRT66zAFE0yB409Bq1X0yN7pcou+/oNr5Wr5+RZtZ/IyA8vPiQzrHn0/z+gpZdfYBNOdEf70P7U1TG28BfNMRw9Tu8HUVs03R/hflrWJK7xPFgW9Lj/dot7RXb7tMt0c4Tsta7uWH+J0DdI02xzhKi1r85W3Thatuld+sfVgdXq57UnDfIb+U33/s8hhR1ezBOODES7CsnZfeYd60Sp7TI3dsay9+ZP25RZFZ4to6uepdt9XbYcjLFperqQJFf6en7daRCM4ZtrFXzktZUjq7C4v5pldbpGihJcXH9f1LUTEVZ5crFI6tSEvz+lc0Uum66aNCeaYy/jPvlaX/La+VtT3lr6FWZfyk4sqHKf2wO1jI1eoeMPMgrlaJfwiVdCpHbm5aORq3lw9s6DOWwG/SFqY8UMM1NcvB/2sHV1QJ608u0hi2WtDblxJuALE6zGiUYwoIWMW2WTedghGrnkBDqmrzi6+7O21BVqh/VzNxeqWF6hjKy8vwij32gNXzzGiOdOjAyLYrD+ii+eP6BQjamrBaLmUY7Rw6NsCV4/xXAFiDZ0LaFWX4wugIH0bErqI5wpqrO5cOOJxPq6Uc1hYMY3Q+nNZe3c+Cguhbz9r7lc4CuDtGJfMUXHGiH5iRA1bMcu+hu753h3TLeOS0FKMauMuRs6D1l++1tvmOgrgukn27ki+GpSEKgM3sxSbm8opke7iDSuE3OuOf/5OMPfrRSiMLLyGjCiQuDutZ4k/1N+CFBiGu0ip0kTdsHqnfHXZL/8q3etBqNh9lia+PtCMF+Z7ytz64eXk5edVlEEPR8OanYFsYJwBI+gFWpQBYnUv1YrKKe2XbVrf5k2HgMlHX5M4niasoSbysisekWNJ4oC9Jqg1DVADuP/zGbKG6201/ZabCrfFHZU5nIVq6hk3fNPgE8Y9bryT99ErtDTgmrQuQf6o9WpaSN8TFJax+xO9Y4ZyazwktJbU+h67JRWk+65an1B2HK9ap5RZME9ar4BZ9PSRV5Yk8oRiaWAVf8aOeF0oevXBbhzm6xf9A+VTeGON+X51hIOdppirdNHA0za9P8cEH8zhMWcKcwQHBBWhrppv1gXg4M3dOK4pzFkTetKMOcjrlwBcMOewH6ir5P/zkXUjMcmcIbEnQyPTSCniRkl8FXBYRNM3StM98vxL0PDKVlo3r8GvSoMul7lwYyuS0JbjogGYS5zsfhj5Itb6HL12E8tbd/Z3fVk1n/NGb8wkcxbwueao9+bIkFkBLkDiVV6aXlP+j62WdOqy1Oq9UrG/Hv7zM/2fJydoD0wNcwoz/8dH8Bu4orn3jTUZt4U696rIXDjCggQyHSaXcbMoTNNTTyMLTTkHs72xZB9eK5qLlq7+LF3zoLGL0CXGa5EJmeUrxf9J0oLK3xrbu0foMIYXBVmfUZW4kD3dsDQFRjd6Bun2OfNunFz9rgKMGuYisU+B9iALwRxE+gVR9XckdoA5ArfJAIF79fGCyO3LBdGx3AG1hSpGZoLhJX5/UA4i5oJoDILlcVcULPahk+pwECoYBfNgWor2tiZnyVRsXEMZdO5kKs5qwkZQI74yuwG0jWPXAh9mrwVcvjgQ50ZJP4+TrsFtnLwWWC4/sx3eC6BFl55t8spcYmXxee9cvWul7Lbm/9LNHwq2JI0DY2cHs0qRLxzblK8+k8g9GDyjDBXDZhGjWBcj1Pahe8sfNiJGFyWGZ3zyvnyF1gBcs3205QnpuZ8dNu7CmNPpTSFGOimGZZr52Vcq+2z7oRTW0Nz3M1tkEGkmfRMB/uhHnoDDfBoFZkgqjYglRWMvsUuEOLEVViOY4qJLZBHLac6Y+o4X7DpSdpGApUmwj//Ts/1Qw/2okTmyqCXgjRSyfN13SXnZEOHQRA3JkSB9gU6RubxDvCpL0yvH/1Hfiq7qJbVnGvjbXIgv9zqPQe9Czce47Q8ALCYyYmuivmP+N2vraZ3szyM8sW8ceXL82dmDWbkt6B2ZS8Oh2z3VEVXWAM7PUMu7ILCYI5AzDN3DPToBozyG3ARgL5dD2FeW/hTyMYX2efX9Hc+jSczDoEAZLOYpTOFxoAwO8wxM8Jj/T2EWUyDAFHKmYILVBRC7Fe2bgD49Ge9KmZyP6ntntFfRF5Dq7xh5xE0AXtCfQvGfQiWmQI0p8E4TnMyUU2JKLmOYBuir0GIuX54tGu1hmUWONJFVoZ8o1DOtYBmRuT2fOXlk6toWU7UusXY/u3LP+UTY1DXKddfPeFEdoUgzjSJnykWyMJQjWW5jzMh8ci/ijh8dMDvveZL1PWcK4Y+2pCDrJSbtZGAKx5ViULkyftfNUh0OmsQNW/BajMJqxbqDjQEHw10MuBjwMOBjuIeBAAMhBiIMxBhIMJBiIMNwHwM5BgoMlBioMDzA8BADNQYaDLQY6DDQY2DAwIiBCQMzhkcYHmN4goEFw1MMrBjYMLBj4MDwDAMnBi4M3Bh4MPBi4MPwHAM/BgEMghiEMAhjEMEgikEMgzgGCQySGKQwSGOQwQDA8AKDLIaXGOQwvMIgj0EBgyKG1xiUMChjUMHwBoMqBjUM6hg0MGhi0MKgjUEHgy4GPQz6GAwwGGIwwmCMwQSDKQYzDOYYLDBYYrDCYI3BBoMthrcY7DDYY3DA4IjBCcM7DM4YXDC4YnDD4I7BA4MnhvcYvDB8wOCNwQeDLwY/DP4YAjAEYgjCAMTwEUMXwZoGZjZ1v2/nQZnNLqwltCw/jJuAN/jUVTb2WmOkbBiYyvac3ZsqG0l+8lreiwNzZAcTSJFP+iTeWGshT2zgYO0pZnVdIAPm2zj9xvXIE6IHvA29WfeBgwl24yinmSGawOEfgGzMd5wS8kQKftSLqLpZv96Nw5jxaaDNGC+33H7+xw9HqWUAszyUmCnyJG4XhFPlCQeXTTF77sbpY+T5/+2nITSjxCHBmtCxH/zowNNVA9imiXRPwexR//h5KOAl0j32Zh3Gsh2nUhPO9X4VFivTyBjaRMjShLfeRKrdxFTbRJ5RY/sUeSJ/wLwWgEFlHtCTWg9sSoIEyiMiDGZQjztKkXImuUi524gLshNhjMoeRiUMg2gd8DNiD3lngb9acI86/IQ+erUxrefoeSjU2gUW608mhntuSZBRTSJpSWK3FzJz/6iWpueJwnFQ9DpOWhc+fxSZpaBMtHzAXWP3x3rHJOXrn/nPj9b35i6JVpmfR/JFFwI6QndkGHNMZyO4FmXSwB1zIcjqaGRNZKsFjnfvC/NYUcyajl49TOuRfh4K6mI4/IK7SKQidmfBzbXc8hX19oW1dPcj0p57h1Hui2TaTYC3CK+AvmWHPpzqz3I1DyIscYFx8KAO89tlJyA6Z8s0q8YvKN68EoavNnmGU7x3/VF/F8PO9UdxaYDbIAcTc9udMh9ckeO3xPtriN6jWVI096VkOrqnXxim9H2LlXbqliUiXZRKwzOcwnF0LPxMPKgCuQ/Z29g+ezpa2RELibqrmWP3eX8XYwuPPdpF/L708w4o/ppQHCPltCHOAqH3He9XUTATOY1MmI1us9xALQWJk9H5zvXnKzCJnhb8Xa/65Ir+31BbigFD+7sVmIRPmxLYY6ScNwxZILS+y/1RCmYCpz8T9KPb3m6QsFweWUqhFJhETn8kgGOkHDYcWCB0vqP9ZwpmQqeJCakxbVYbwiyuNM1o/b511w1Lljg638X+JIVskdPyBFi0lOuGPAsfre/vfi4FM8HT8ATEpRATkIWM3neqf10hW+i0LsEuRspuw5eFj853oH9IwYz/ND1BNHoRlPrvDQLr3+xV5N/qlZn/31IDxf17zn38N50T/rd6BfT73MZIvdvQZImj953on1TIFj7NTIDFtNlvsLLw0fv29jsABCz70yksP/dAV/2bebX7t/IKBK6fiJ5WJyjGSLlsKLGo0/vO9HsqZIuefk9IjW57t/GApYrWt7sfqfnvqeHTxIESImKkHDfcWdTpfOf7axWyBU/bEqhj2mw2bFmqaHxH+ukVDpnf/VvOoUX/vQiT/XuTDhj/7+U19N+LMLPVvzUIwNt/Sw2t8e9FWC7633Pu3+zV7T96BSai+WbfZags3vvzD8peC7/JX0jKBq/OfrUgePaY5J677Jh/FR7VfdG18MG3U0Sf6WXvvzKxwn/2mLXg09d4itP+qzVK6J6o3dYb1ECmjYA4GspstvJgeYVRZoWyY4U+aIUatbJKPc7MtEqQvYprtkqyvIojs0rUsYoftErGJPMRdXxP/ZiY75jQ9ZiU+ZjA/JgEcEwEPD5WOo9Q9Amx8/mo7xPqfRWsfhXievXR/Co0Ivr/WNx43qJR+Q7/3UwFAAVi/e99BdEiV8mzV2j//+7pj/3FvaAHfzPR3iaLO74LOcauOsY7OsbKOcaFHuOAjvHJQOF/G5HDPuA/G5OJQf1Xo5zO27+M1lwR6POJ3Sec2idM1CeC7OoT31U481UYwOeK5G8BIvvfR3OEk4kO+Ayn/v89g8mdR2Dau3eGZjmP+F+7Uh3+mxM8f3Mi5P9Ewaga1SUZ8Is9oFP09hffbWe33QkSzX3TTSnVTbRs/D+nQ8Tfgrfw13iH/s3E92++8eUCpLr+9N/WRd/WjR/QRR3QTXbbxSwVQP63dHv/bQJ3fPpb9/5/9Tjubyb4fzMBfv6bieLfTMwV/pKzH3/t5D9X1v/shP2vJpF/M7H7q0ns30we/O/5QhAe5tziHub8YpHqFGz7xdXW+d+mk/n3vyTz9sFN9/9uov/XZP517Xr9bS65/nUuUf5tLlX9rXu6vzkM/Vsntzx/Ncn7m1//9/3JPwpY/W+eGYsBw/8yzPy/NYf/t2Ee/TXKUajjK9Ny0H+NM83Rf7xQ8P8WaOCrv72D2P9q8rclcEX9N5Ojf4YNSIZgljL/H35L/C3Wl38bKeqv28dfVzrgr8MU/ZvPzH9L9S3N37qH/s3joP98b//PFcD8V4/l/+ax+t88Rr/8m4nrX01k/2JC8ze/0FH/dShoWsmZ/R+BTH/OOO8XgAEmni34x4oCSmpsSdAkG7ZvT5O+KQncU3aKaXhn1LnvzCs7/aOJfopOXzneVtmkXb/UU5+858M2mfy8ZMVMQ7KAfZmKu5luj7MzmDBkN8vUsntG2NjS+3APlQA5A8MAEMRwJsy/A+Y/ej2s1PsZ/IX9c0ZPUo92z2RPDHjglvKSkuw+GQUZORll3P04ijjyOEr1+6Jf2L8Ufy7+Ql/W/68U/lULTv+qBad/1YJ6/DX7ITvTI6anTE+Y2JgeM7EysTCxZz9yoVCnUCdXpxSdSfgXCtlPz9QX1aVeSL2WeiX1RuqllLKUgpSalOzi0+yn2U+y2Vyk5LdymnJ8gn3ifT77pPl88vnqE+2T6RPSpCSlJCUvpbrokz4McAec3Dl5dHL/5PnJvROOE5oTsZO77kk+iT6RPulN/K/+ny1Iv0Kh9+AbaBDbXxytZD9Tx/Qz92Lm/93PibkN6gviC/5n/C8RnyO+KH5W/AL+7zkV+wZcC1rDWpNde7xmuUa+prnGv+a+RrDGdvL0hOpEyN2a5V8pUP4LhXVaAXQPsgenJ7RHrqe7h6Unv8e6Z72Hskd1TWnt2ZrDWt/bf6XwUABt/Br1H6EI/F9Vav/VQKH/Ku0Nif9K4V+2kPQPhTm1bNDfRuK5gWT/f8+MN/9ibs3J/kPBAr8ZTfmXJQBJQvyLaYH9L3LG8s9O/njBIXuI/jMS2iMxLi5Bi4RuNEhWgneEwu5aZ4lxNLEwTBt+VVX7tNGiVKZFSKUj1C9APsXEMaN0gWkoUTJvuVZGJaUTFQKxHWA9Rk631haU+5Qu33xIMcFZOGC2GfA9Ro6yGAoQNYA7BhKdNRrRaayNsuj2698/HzbwlfanXFoi3qk3tOEgnYtto5BXJfOB8g2ZWFAyJKdxiEZVq7hxpsbR/tBDwFREqp2K9FSK4s9CmjhX54ZMMi9Y37vAgO7fWthet8nvBiL8fMzfSg5DluV+r0n6lqptGhSUYW2Bfj9x7bpUKTLewLsKMi+TjzUs3u2XivI5DuCp7uc24BvY45kwE9RFpBhuiM3loFeHYZ4WKP23Dd0BEaIGU7evGg17TPHAiHT5yr4zz19P3u7oBD4/YxZcQfR9kj+MOKPPqOsXmDsU8djApnGNE1U8DNmzfCI4R7o9K8Gn+KHrYsDJY+M1ayZU0mNDbQ442y6+9hFyWTWS8JimCugUm4mNIGv/vrct+e2GWtvrO6f+Ycg1sdDWoKKGZBFMmWEUnH3mYavCyACtb9bSw13fGUqmjlq5OhxKJrO4rUxutoo4ebMQz0XdfYFybj5liIUlmyjp/fLzA+gH4eWQxdr24Z9Jn8hVmkTNaptlt2HX50upx5aFn2R+ZQdGnO2kf2M=
*/