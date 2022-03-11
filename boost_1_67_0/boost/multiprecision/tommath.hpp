///////////////////////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_MP_TOMMATH_BACKEND_HPP
#define BOOST_MATH_MP_TOMMATH_BACKEND_HPP

#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/rational_adaptor.hpp>
#include <boost/multiprecision/detail/integer_ops.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/cstdint.hpp>
#include <boost/scoped_array.hpp>
#include <boost/functional/hash_fwd.hpp>
#include <tommath.h>
#include <cctype>
#include <cmath>
#include <limits>
#include <climits>

namespace boost {
namespace multiprecision {
namespace backends {

namespace detail {

template <class ErrType>
inline void check_tommath_result(ErrType v)
{
   if (v != MP_OKAY)
   {
      BOOST_THROW_EXCEPTION(std::runtime_error(mp_error_to_string(v)));
   }
}

} // namespace detail

struct tommath_int;

void eval_multiply(tommath_int& t, const tommath_int& o);
void eval_add(tommath_int& t, const tommath_int& o);

struct tommath_int
{
   typedef mpl::list<boost::int32_t, boost::long_long_type>   signed_types;
   typedef mpl::list<boost::uint32_t, boost::ulong_long_type> unsigned_types;
   typedef mpl::list<long double>                             float_types;

   tommath_int()
   {
      detail::check_tommath_result(mp_init(&m_data));
   }
   tommath_int(const tommath_int& o)
   {
      detail::check_tommath_result(mp_init_copy(&m_data, const_cast< ::mp_int*>(&o.m_data)));
   }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   tommath_int(tommath_int&& o) BOOST_NOEXCEPT
   {
      m_data      = o.m_data;
      o.m_data.dp = 0;
   }
   tommath_int& operator=(tommath_int&& o)
   {
      mp_exch(&m_data, &o.m_data);
      return *this;
   }
#endif
   tommath_int& operator=(const tommath_int& o)
   {
      if (m_data.dp == 0)
         detail::check_tommath_result(mp_init(&m_data));
      if (o.m_data.dp)
         detail::check_tommath_result(mp_copy(const_cast< ::mp_int*>(&o.m_data), &m_data));
      return *this;
   }
#if defined(DIGIT_BIT)
   // Pick off 32 bit chunks for mp_set_int:
   tommath_int& operator=(boost::ulong_long_type i)
   {
      if (m_data.dp == 0)
         detail::check_tommath_result(mp_init(&m_data));
      boost::ulong_long_type mask = ((1uLL << 32) - 1);
      unsigned shift = 0;
      ::mp_int t;
      detail::check_tommath_result(mp_init(&t));
      mp_zero(&m_data);
      while (i)
      {
         detail::check_tommath_result(mp_set_int(&t, static_cast<unsigned>(i & mask)));
         if (shift)
            detail::check_tommath_result(mp_mul_2d(&t, shift, &t));
         detail::check_tommath_result((mp_add(&m_data, &t, &m_data)));
         shift += 32;
         i >>= 32;
      }
      mp_clear(&t);
      return *this;
   }
#elif !defined(ULLONG_MAX) || (ULLONG_MAX != 18446744073709551615uLL)
   // Pick off 64 bit chunks for mp_set_i64:
   tommath_int& operator=(boost::ulong_long_type i)
   {
      if (m_data.dp == 0)
         detail::check_tommath_result(mp_init(&m_data));
      if(sizeof(boost::ulong_long_type) * CHAR_BIT == 64)
      {
         mp_set_u64(&m_data, i);
         return *this;
      }
      boost::ulong_long_type mask = ((1uLL << 64) - 1);
      unsigned shift = 0;
      ::mp_int t;
      detail::check_tommath_result(mp_init(&t));
      mp_zero(&m_data);
      while (i)
      {
         detail::check_tommath_result(mp_set_i64(&t, static_cast<boost::uint64_t>(i & mask)));
         if (shift)
            detail::check_tommath_result(mp_mul_2d(&t, shift, &t));
         detail::check_tommath_result((mp_add(&m_data, &t, &m_data)));
         shift += 64;
         i >>= 64;
      }
      mp_clear(&t);
      return *this;
   }
#else
   tommath_int& operator=(boost::ulong_long_type i)
   {
      if (m_data.dp == 0)
         detail::check_tommath_result(mp_init(&m_data));
      mp_set_u64(&m_data, i);
      return *this;
   }
#endif
   tommath_int& operator=(boost::long_long_type i)
   {
      if (m_data.dp == 0)
         detail::check_tommath_result(mp_init(&m_data));
      bool neg = i < 0;
      *this    = boost::multiprecision::detail::unsigned_abs(i);
      if (neg)
         detail::check_tommath_result(mp_neg(&m_data, &m_data));
      return *this;
   }
   //
   // Note that although mp_set_int takes an unsigned long as an argument
   // it only sets the first 32-bits to the result, and ignores the rest.
   // So use uint32_t as the largest type to pass to this function.
   //
   tommath_int& operator=(boost::uint32_t i)
   {
      if (m_data.dp == 0)
         detail::check_tommath_result(mp_init(&m_data));
#ifdef DIGIT_BIT
      detail::check_tommath_result((mp_set_int(&m_data, i)));
#else
      mp_set_u32(&m_data, i);
#endif
      return *this;
   }
   tommath_int& operator=(boost::int32_t i)
   {
      if (m_data.dp == 0)
         detail::check_tommath_result(mp_init(&m_data));
      bool neg = i < 0;
      *this    = boost::multiprecision::detail::unsigned_abs(i);
      if (neg)
         detail::check_tommath_result(mp_neg(&m_data, &m_data));
      return *this;
   }
   tommath_int& operator=(long double a)
   {
      using std::floor;
      using std::frexp;
      using std::ldexp;

      if (m_data.dp == 0)
         detail::check_tommath_result(mp_init(&m_data));

      if (a == 0)
      {
#ifdef DIGIT_BIT
         detail::check_tommath_result(mp_set_int(&m_data, 0));
#else
         mp_set_i32(&m_data, 0);
#endif
         return *this;
      }

      if (a == 1)
      {
#ifdef DIGIT_BIT
         detail::check_tommath_result(mp_set_int(&m_data, 1));
#else
         mp_set_i32(&m_data, 1);
#endif
         return *this;
      }

      BOOST_ASSERT(!(boost::math::isinf)(a));
      BOOST_ASSERT(!(boost::math::isnan)(a));

      int         e;
      long double f, term;
#ifdef DIGIT_BIT
      detail::check_tommath_result(mp_set_int(&m_data, 0u));
#else
      mp_set_i32(&m_data, 0);
#endif
      ::mp_int t;
      detail::check_tommath_result(mp_init(&t));

      f = frexp(a, &e);

#ifdef DIGIT_BIT
      static const int shift = std::numeric_limits<int>::digits - 1;
      typedef int      part_type;
#else
      static const int       shift = std::numeric_limits<boost::int64_t>::digits - 1;
      typedef boost::int64_t part_type;
#endif

      while (f)
      {
         // extract int sized bits from f:
         f    = ldexp(f, shift);
         term = floor(f);
         e -= shift;
         detail::check_tommath_result(mp_mul_2d(&m_data, shift, &m_data));
         if (term > 0)
         {
#ifdef DIGIT_BIT
            detail::check_tommath_result(mp_set_int(&t, static_cast<part_type>(term)));
#else
            mp_set_i64(&t, static_cast<part_type>(term));
#endif
            detail::check_tommath_result(mp_add(&m_data, &t, &m_data));
         }
         else
         {
#ifdef DIGIT_BIT
            detail::check_tommath_result(mp_set_int(&t, static_cast<part_type>(-term)));
#else
            mp_set_i64(&t, static_cast<part_type>(-term));
#endif
            detail::check_tommath_result(mp_sub(&m_data, &t, &m_data));
         }
         f -= term;
      }
      if (e > 0)
         detail::check_tommath_result(mp_mul_2d(&m_data, e, &m_data));
      else if (e < 0)
      {
         tommath_int t2;
         detail::check_tommath_result(mp_div_2d(&m_data, -e, &m_data, &t2.data()));
      }
      mp_clear(&t);
      return *this;
   }
   tommath_int& operator=(const char* s)
   {
      //
      // We don't use libtommath's own routine because it doesn't error check the input :-(
      //
      if (m_data.dp == 0)
         detail::check_tommath_result(mp_init(&m_data));
      std::size_t n  = s ? std::strlen(s) : 0;
      *this          = static_cast<boost::uint32_t>(0u);
      unsigned radix = 10;
      bool     isneg = false;
      if (n && (*s == '-'))
      {
         --n;
         ++s;
         isneg = true;
      }
      if (n && (*s == '0'))
      {
         if ((n > 1) && ((s[1] == 'x') || (s[1] == 'X')))
         {
            radix = 16;
            s += 2;
            n -= 2;
         }
         else
         {
            radix = 8;
            n -= 1;
         }
      }
      if (n)
      {
         if (radix == 8 || radix == 16)
         {
            unsigned shift = radix == 8 ? 3 : 4;
#ifdef DIGIT_BIT
            unsigned block_count = DIGIT_BIT / shift;
#else
            unsigned block_count = MP_DIGIT_BIT / shift;
#endif
            unsigned               block_shift = shift * block_count;
            boost::ulong_long_type val, block;
            while (*s)
            {
               block = 0;
               for (unsigned i = 0; (i < block_count); ++i)
               {
                  if (*s >= '0' && *s <= '9')
                     val = *s - '0';
                  else if (*s >= 'a' && *s <= 'f')
                     val = 10 + *s - 'a';
                  else if (*s >= 'A' && *s <= 'F')
                     val = 10 + *s - 'A';
                  else
                     val = 400;
                  if (val > radix)
                  {
                     BOOST_THROW_EXCEPTION(std::runtime_error("Unexpected content found while parsing character string."));
                  }
                  block <<= shift;
                  block |= val;
                  if (!*++s)
                  {
                     // final shift is different:
                     block_shift = (i + 1) * shift;
                     break;
                  }
               }
               detail::check_tommath_result(mp_mul_2d(&data(), block_shift, &data()));
               if (data().used)
                  data().dp[0] |= block;
               else
                  *this = block;
            }
         }
         else
         {
            // Base 10, we extract blocks of size 10^9 at a time, that way
            // the number of multiplications is kept to a minimum:
            boost::uint32_t block_mult = 1000000000;
            while (*s)
            {
               boost::uint32_t block = 0;
               for (unsigned i = 0; i < 9; ++i)
               {
                  boost::uint32_t val;
                  if (*s >= '0' && *s <= '9')
                     val = *s - '0';
                  else
                     BOOST_THROW_EXCEPTION(std::runtime_error("Unexpected character encountered in input."));
                  block *= 10;
                  block += val;
                  if (!*++s)
                  {
                     static const boost::uint32_t block_multiplier[9] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
                     block_mult                                       = block_multiplier[i];
                     break;
                  }
               }
               tommath_int t;
               t = block_mult;
               eval_multiply(*this, t);
               t = block;
               eval_add(*this, t);
            }
         }
      }
      if (isneg)
         this->negate();
      return *this;
   }
   std::string str(std::streamsize /*digits*/, std::ios_base::fmtflags f) const
   {
      BOOST_ASSERT(m_data.dp);
      int base = 10;
      if ((f & std::ios_base::oct) == std::ios_base::oct)
         base = 8;
      else if ((f & std::ios_base::hex) == std::ios_base::hex)
         base = 16;
      //
      // sanity check, bases 8 and 16 are only available for positive numbers:
      //
      if ((base != 10) && m_data.sign)
         BOOST_THROW_EXCEPTION(std::runtime_error("Formatted output in bases 8 or 16 is only available for positive numbers"));
#ifdef DIGIT_BIT
      int s;
      detail::check_tommath_result(mp_radix_size(const_cast< ::mp_int*>(&m_data), base, &s));
#else
      std::size_t s;
      detail::check_tommath_result(mp_radix_size(const_cast< ::mp_int*>(&m_data), base, &s));
#endif
      boost::scoped_array<char> a(new char[s + 1]);
#ifdef DIGIT_BIT
      detail::check_tommath_result(mp_toradix_n(const_cast< ::mp_int*>(&m_data), a.get(), base, s + 1));
#else
      std::size_t written;
      detail::check_tommath_result(mp_to_radix(&m_data, a.get(), s + 1, &written, base));
#endif
      std::string result = a.get();
      if (f & std::ios_base::uppercase)
         for (size_t i = 0; i < result.length(); ++i)
            result[i] = std::toupper(result[i]);
      if ((base != 10) && (f & std::ios_base::showbase))
      {
         int         pos = result[0] == '-' ? 1 : 0;
         const char* pp  = base == 8 ? "0" : (f & std::ios_base::uppercase) ? "0X" : "0x";
         result.insert(static_cast<std::string::size_type>(pos), pp);
      }
      if ((f & std::ios_base::showpos) && (result[0] != '-'))
         result.insert(static_cast<std::string::size_type>(0), 1, '+');
      if (((f & std::ios_base::uppercase) == 0) && (base == 16))
      {
         for (std::size_t i = 0; i < result.size(); ++i)
            result[i] = std::tolower(result[i]);
      }
      return result;
   }
   ~tommath_int()
   {
      if (m_data.dp)
         mp_clear(&m_data);
   }
   void negate()
   {
      BOOST_ASSERT(m_data.dp);
      detail::check_tommath_result(mp_neg(&m_data, &m_data));
   }
   int compare(const tommath_int& o) const
   {
      BOOST_ASSERT(m_data.dp && o.m_data.dp);
      return mp_cmp(const_cast< ::mp_int*>(&m_data), const_cast< ::mp_int*>(&o.m_data));
   }
   template <class V>
   int compare(V v) const
   {
      tommath_int d;
      tommath_int t(*this);
      detail::check_tommath_result(mp_shrink(&t.data()));
      d = v;
      return t.compare(d);
   }
   ::mp_int& data()
   {
      BOOST_ASSERT(m_data.dp);
      return m_data;
   }
   const ::mp_int& data() const
   {
      BOOST_ASSERT(m_data.dp);
      return m_data;
   }
   void swap(tommath_int& o) BOOST_NOEXCEPT
   {
      mp_exch(&m_data, &o.data());
   }

 protected:
   ::mp_int m_data;
};

#ifdef SIGN
#define BOOST_MP_TOMMATH_BIT_OP_CHECK(x) \
   if (SIGN(&x.data()))                  \
   BOOST_THROW_EXCEPTION(std::runtime_error("Bitwise operations on libtommath negative valued integers are disabled as they produce unpredictable results"))
#else
#define BOOST_MP_TOMMATH_BIT_OP_CHECK(x) \
   if (mp_isneg(&x.data()))              \
   BOOST_THROW_EXCEPTION(std::runtime_error("Bitwise operations on libtommath negative valued integers are disabled as they produce unpredictable results"))
#endif

int eval_get_sign(const tommath_int& val);

inline void eval_add(tommath_int& t, const tommath_int& o)
{
   detail::check_tommath_result(mp_add(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
}
inline void eval_subtract(tommath_int& t, const tommath_int& o)
{
   detail::check_tommath_result(mp_sub(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
}
inline void eval_multiply(tommath_int& t, const tommath_int& o)
{
   detail::check_tommath_result(mp_mul(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
}
inline void eval_divide(tommath_int& t, const tommath_int& o)
{
   using default_ops::eval_is_zero;
   tommath_int temp;
   if (eval_is_zero(o))
      BOOST_THROW_EXCEPTION(std::overflow_error("Integer division by zero"));
   detail::check_tommath_result(mp_div(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data(), &temp.data()));
}
inline void eval_modulus(tommath_int& t, const tommath_int& o)
{
   using default_ops::eval_is_zero;
   if (eval_is_zero(o))
      BOOST_THROW_EXCEPTION(std::overflow_error("Integer division by zero"));
   bool neg  = eval_get_sign(t) < 0;
   bool neg2 = eval_get_sign(o) < 0;
   detail::check_tommath_result(mp_mod(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
   if ((neg != neg2) && (eval_get_sign(t) != 0))
   {
      t.negate();
      detail::check_tommath_result(mp_add(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
      t.negate();
   }
   else if (neg && (t.compare(o) == 0))
   {
      mp_zero(&t.data());
   }
}
template <class UI>
inline void eval_left_shift(tommath_int& t, UI i)
{
   detail::check_tommath_result(mp_mul_2d(&t.data(), static_cast<unsigned>(i), &t.data()));
}
template <class UI>
inline void eval_right_shift(tommath_int& t, UI i)
{
   using default_ops::eval_decrement;
   using default_ops::eval_increment;
   bool        neg = eval_get_sign(t) < 0;
   tommath_int d;
   if (neg)
      eval_increment(t);
   detail::check_tommath_result(mp_div_2d(&t.data(), static_cast<unsigned>(i), &t.data(), &d.data()));
   if (neg)
      eval_decrement(t);
}
template <class UI>
inline void eval_left_shift(tommath_int& t, const tommath_int& v, UI i)
{
   detail::check_tommath_result(mp_mul_2d(const_cast< ::mp_int*>(&v.data()), static_cast<unsigned>(i), &t.data()));
}
/*
template <class UI>
inline void eval_right_shift(tommath_int& t, const tommath_int& v, UI i)
{
   tommath_int d;
   detail::check_tommath_result(mp_div_2d(const_cast< ::mp_int*>(&v.data()), static_cast<unsigned long>(i), &t.data(), &d.data()));
}
*/
inline void eval_bitwise_and(tommath_int& result, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(result);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_and(&result.data(), const_cast< ::mp_int*>(&v.data()), &result.data()));
}

inline void eval_bitwise_or(tommath_int& result, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(result);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_or(&result.data(), const_cast< ::mp_int*>(&v.data()), &result.data()));
}

inline void eval_bitwise_xor(tommath_int& result, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(result);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_xor(&result.data(), const_cast< ::mp_int*>(&v.data()), &result.data()));
}

inline void eval_add(tommath_int& t, const tommath_int& p, const tommath_int& o)
{
   detail::check_tommath_result(mp_add(const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&o.data()), &t.data()));
}
inline void eval_subtract(tommath_int& t, const tommath_int& p, const tommath_int& o)
{
   detail::check_tommath_result(mp_sub(const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&o.data()), &t.data()));
}
inline void eval_multiply(tommath_int& t, const tommath_int& p, const tommath_int& o)
{
   detail::check_tommath_result(mp_mul(const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&o.data()), &t.data()));
}
inline void eval_divide(tommath_int& t, const tommath_int& p, const tommath_int& o)
{
   using default_ops::eval_is_zero;
   tommath_int d;
   if (eval_is_zero(o))
      BOOST_THROW_EXCEPTION(std::overflow_error("Integer division by zero"));
   detail::check_tommath_result(mp_div(const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&o.data()), &t.data(), &d.data()));
}
inline void eval_modulus(tommath_int& t, const tommath_int& p, const tommath_int& o)
{
   using default_ops::eval_is_zero;
   if (eval_is_zero(o))
      BOOST_THROW_EXCEPTION(std::overflow_error("Integer division by zero"));
   bool neg  = eval_get_sign(p) < 0;
   bool neg2 = eval_get_sign(o) < 0;
   detail::check_tommath_result(mp_mod(const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&o.data()), &t.data()));
   if ((neg != neg2) && (eval_get_sign(t) != 0))
   {
      t.negate();
      detail::check_tommath_result(mp_add(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
      t.negate();
   }
   else if (neg && (t.compare(o) == 0))
   {
      mp_zero(&t.data());
   }
}

inline void eval_bitwise_and(tommath_int& result, const tommath_int& u, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(u);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_and(const_cast< ::mp_int*>(&u.data()), const_cast< ::mp_int*>(&v.data()), &result.data()));
}

inline void eval_bitwise_or(tommath_int& result, const tommath_int& u, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(u);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_or(const_cast< ::mp_int*>(&u.data()), const_cast< ::mp_int*>(&v.data()), &result.data()));
}

inline void eval_bitwise_xor(tommath_int& result, const tommath_int& u, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(u);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_xor(const_cast< ::mp_int*>(&u.data()), const_cast< ::mp_int*>(&v.data()), &result.data()));
}
/*
inline void eval_complement(tommath_int& result, const tommath_int& u)
{
   //
   // Although this code works, it doesn't really do what the user might expect....
   // and it's hard to see how it ever could.  Disabled for now:
   //
   result = u;
   for(int i = 0; i < result.data().used; ++i)
   {
      result.data().dp[i] = MP_MASK & ~(result.data().dp[i]);
   }
   //
   // We now need to pad out the left of the value with 1's to round up to a whole number of
   // CHAR_BIT * sizeof(mp_digit) units.  Otherwise we'll end up with a very strange number of
   // bits set!
   //
   unsigned shift = result.data().used * DIGIT_BIT;    // How many bits we're actually using
   // How many bits we actually need, reduced by one to account for a mythical sign bit:
   int padding = result.data().used * std::numeric_limits<mp_digit>::digits - shift - 1; 
   while(padding >= std::numeric_limits<mp_digit>::digits) 
      padding -= std::numeric_limits<mp_digit>::digits;

   // Create a mask providing the extra bits we need and add to result:
   tommath_int mask;
   mask = static_cast<boost::long_long_type>((1u << padding) - 1);
   eval_left_shift(mask, shift);
   add(result, mask);
}
*/
inline bool eval_is_zero(const tommath_int& val)
{
   return mp_iszero(&val.data());
}
inline int eval_get_sign(const tommath_int& val)
{
#ifdef SIGN
   return mp_iszero(&val.data()) ? 0 : SIGN(&val.data()) ? -1 : 1;
#else
   return mp_iszero(&val.data()) ? 0 : mp_isneg(&val.data()) ? -1 : 1;
#endif
}
/*
template <class A>
inline void eval_convert_to(A* result, const tommath_int& val)
{
   *result = boost::lexical_cast<A>(val.str(0, std::ios_base::fmtflags(0)));
}
inline void eval_convert_to(char* result, const tommath_int& val)
{
   *result = static_cast<char>(boost::lexical_cast<int>(val.str(0, std::ios_base::fmtflags(0))));
}
inline void eval_convert_to(unsigned char* result, const tommath_int& val)
{
   *result = static_cast<unsigned char>(boost::lexical_cast<unsigned>(val.str(0, std::ios_base::fmtflags(0))));
}
inline void eval_convert_to(signed char* result, const tommath_int& val)
{
   *result = static_cast<signed char>(boost::lexical_cast<int>(val.str(0, std::ios_base::fmtflags(0))));
}
*/
inline void eval_abs(tommath_int& result, const tommath_int& val)
{
   detail::check_tommath_result(mp_abs(const_cast< ::mp_int*>(&val.data()), &result.data()));
}
inline void eval_gcd(tommath_int& result, const tommath_int& a, const tommath_int& b)
{
   detail::check_tommath_result(mp_gcd(const_cast< ::mp_int*>(&a.data()), const_cast< ::mp_int*>(&b.data()), const_cast< ::mp_int*>(&result.data())));
}
inline void eval_lcm(tommath_int& result, const tommath_int& a, const tommath_int& b)
{
   detail::check_tommath_result(mp_lcm(const_cast< ::mp_int*>(&a.data()), const_cast< ::mp_int*>(&b.data()), const_cast< ::mp_int*>(&result.data())));
}
inline void eval_powm(tommath_int& result, const tommath_int& base, const tommath_int& p, const tommath_int& m)
{
   if (eval_get_sign(p) < 0)
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("powm requires a positive exponent."));
   }
   detail::check_tommath_result(mp_exptmod(const_cast< ::mp_int*>(&base.data()), const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&m.data()), &result.data()));
}

inline void eval_qr(const tommath_int& x, const tommath_int& y,
                    tommath_int& q, tommath_int& r)
{
   detail::check_tommath_result(mp_div(const_cast< ::mp_int*>(&x.data()), const_cast< ::mp_int*>(&y.data()), &q.data(), &r.data()));
}

inline unsigned eval_lsb(const tommath_int& val)
{
   int c = eval_get_sign(val);
   if (c == 0)
   {
      BOOST_THROW_EXCEPTION(std::range_error("No bits were set in the operand."));
   }
   if (c < 0)
   {
      BOOST_THROW_EXCEPTION(std::range_error("Testing individual bits in negative values is not supported - results are undefined."));
   }
   return mp_cnt_lsb(const_cast< ::mp_int*>(&val.data()));
}

inline unsigned eval_msb(const tommath_int& val)
{
   int c = eval_get_sign(val);
   if (c == 0)
   {
      BOOST_THROW_EXCEPTION(std::range_error("No bits were set in the operand."));
   }
   if (c < 0)
   {
      BOOST_THROW_EXCEPTION(std::range_error("Testing individual bits in negative values is not supported - results are undefined."));
   }
   return mp_count_bits(const_cast< ::mp_int*>(&val.data())) - 1;
}

template <class Integer>
inline typename enable_if<is_unsigned<Integer>, Integer>::type eval_integer_modulus(const tommath_int& x, Integer val)
{
#ifdef DIGIT_BIT
   static const mp_digit m = (static_cast<mp_digit>(1) << DIGIT_BIT) - 1;
#else
   static const mp_digit m = (static_cast<mp_digit>(1) << MP_DIGIT_BIT) - 1;
#endif
   if (val <= m)
   {
      mp_digit d;
      detail::check_tommath_result(mp_mod_d(const_cast< ::mp_int*>(&x.data()), static_cast<mp_digit>(val), &d));
      return d;
   }
   else
   {
      return default_ops::eval_integer_modulus(x, val);
   }
}
template <class Integer>
inline typename enable_if<is_signed<Integer>, Integer>::type eval_integer_modulus(const tommath_int& x, Integer val)
{
   return eval_integer_modulus(x, boost::multiprecision::detail::unsigned_abs(val));
}

inline std::size_t hash_value(const tommath_int& val)
{
   std::size_t result = 0;
   std::size_t len    = val.data().used;
   for (std::size_t i = 0; i < len; ++i)
      boost::hash_combine(result, val.data().dp[i]);
   boost::hash_combine(result, val.data().sign);
   return result;
}

} // namespace backends

using boost::multiprecision::backends::tommath_int;

template <>
struct number_category<tommath_int> : public mpl::int_<number_kind_integer>
{};

typedef number<tommath_int>           tom_int;
typedef rational_adaptor<tommath_int> tommath_rational;
typedef number<tommath_rational>      tom_rational;
}
} // namespace boost::multiprecision

namespace std {

template <boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> number_type;

 public:
   BOOST_STATIC_CONSTEXPR bool is_specialized = true;
   //
   // Largest and smallest numbers are bounded only by available memory, set
   // to zero:
   //
   static number_type(min)()
   {
      return number_type();
   }
   static number_type(max)()
   {
      return number_type();
   }
   static number_type                        lowest() { return (min)(); }
   BOOST_STATIC_CONSTEXPR int                digits       = INT_MAX;
   BOOST_STATIC_CONSTEXPR int                digits10     = (INT_MAX / 1000) * 301L;
   BOOST_STATIC_CONSTEXPR int                max_digits10 = digits10 + 3;
   BOOST_STATIC_CONSTEXPR bool               is_signed    = true;
   BOOST_STATIC_CONSTEXPR bool               is_integer   = true;
   BOOST_STATIC_CONSTEXPR bool               is_exact     = true;
   BOOST_STATIC_CONSTEXPR int                radix        = 2;
   static number_type                        epsilon() { return number_type(); }
   static number_type                        round_error() { return number_type(); }
   BOOST_STATIC_CONSTEXPR int                min_exponent      = 0;
   BOOST_STATIC_CONSTEXPR int                min_exponent10    = 0;
   BOOST_STATIC_CONSTEXPR int                max_exponent      = 0;
   BOOST_STATIC_CONSTEXPR int                max_exponent10    = 0;
   BOOST_STATIC_CONSTEXPR bool               has_infinity      = false;
   BOOST_STATIC_CONSTEXPR bool               has_quiet_NaN     = false;
   BOOST_STATIC_CONSTEXPR bool               has_signaling_NaN = false;
   BOOST_STATIC_CONSTEXPR float_denorm_style has_denorm        = denorm_absent;
   BOOST_STATIC_CONSTEXPR bool               has_denorm_loss   = false;
   static number_type                        infinity() { return number_type(); }
   static number_type                        quiet_NaN() { return number_type(); }
   static number_type                        signaling_NaN() { return number_type(); }
   static number_type                        denorm_min() { return number_type(); }
   BOOST_STATIC_CONSTEXPR bool               is_iec559       = false;
   BOOST_STATIC_CONSTEXPR bool               is_bounded      = false;
   BOOST_STATIC_CONSTEXPR bool               is_modulo       = false;
   BOOST_STATIC_CONSTEXPR bool               traps           = false;
   BOOST_STATIC_CONSTEXPR bool               tinyness_before = false;
   BOOST_STATIC_CONSTEXPR float_round_style  round_style     = round_toward_zero;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION

template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::digits;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::digits10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::max_digits10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::is_signed;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::is_integer;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::is_exact;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::radix;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::min_exponent;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::min_exponent10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::max_exponent;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::max_exponent10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::has_infinity;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::has_quiet_NaN;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::has_signaling_NaN;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST float_denorm_style numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::has_denorm;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::has_denorm_loss;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::is_iec559;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::is_bounded;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::is_modulo;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::traps;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::tinyness_before;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST float_round_style numeric_limits<boost::multiprecision::number<boost::multiprecision::tommath_int, ExpressionTemplates> >::round_style;

#endif
} // namespace std

#endif

/* tommath.hpp
cHbiesiuPbzRnPuwrVzo1e3QK/9MkLqUbEJ7IaytxoTWVoPP8CBdQIAPfBextjrEbjrLF0WHWHojtZWttJXF27oLXmG1tohWazAoTrWmb8MwVMdC80YcByHFuwwpvIsTVFms2vaUOKe272kd9v1uVN71fBH2JbxkmZTrgNXESkx8xLkItxE4dUPiB5DI7rnAqRoJfvwFqu51Xh0sGlKzTFJXXsPzaqIzAEs+jRRPVhj+7Q+7SYPSBwbagvtVbRXS78EGpgHzBoRrFrShcLMR9+DQtlts792Kk6MQAnJXrMOSVpM1xjmCuys2fapooHR3OQ2geAhSyVXWdp33KdANmgUPsSeIMSsirsNpc+ZsmtXz5E6Y2EycdkcuVz2tU3nX8j5FhX8Y74IEL/JXrqtmociCDm2XzUL+cjQ5nBDyEzAhADOhDrWo/UI+Oq4F9zvH8D535KukrQwn+twlyQOB/n+iuK074elbtEp4xj0ORFzC82d/TZYVZ482ay7/Ipj0Ci0lKyzerCHOmEJLabml9NYVlpJAVLml5FYUr3RimyUyRXYVzwyLruU/KqIL50+kOuJLICl/Px3qfCbnjThS4Nn3Ue+OdX2iJ2zUAsn7KYSBx/EiS+pHfF29UUcImYNI2HaWkKBgILABS8XjNdkYj8gahGVZ7B1QWQi/w4C9/JsJiBZ+Haywsiv6Fl6eKKz8HJ0CL98t3eq6fI9QQPfKAOjo+C2zdlFXONuvEPfQOPyPadXktZDcZDiN8TLwfNFtOFR+cddO2mrRn1EwUTNWo8E7gfbsovtLcGPD5+8SVGjLlHvV7BwNw+y5WadhNd+FTD6OrQr/bmVT/bwHkMu/iYQczQZ/h2nDf5gLPxHSA16OiMVsClQDFVuXDIK/E3P601zDDicqfUdho/GreBvM6oGOXYHxUlpwvxQD/x3w/2agqQfpckX20a+h6cnHKlm43DouN3PZK5E53onIsYznWMeeicyRzxRTK4k3YqVpIVZKwV5SwEeK7zfwmyvkzI+MAzIL5NW8yPCr7a/P0j5GerrEzbFC/ia6hcErpcMi1pnGpWccZkGDf1eA3qT3APb3guT0r+fgLH9PxxdsIiQGYOJ4QN1YrN8Jkmcc6nqLSEmaM0KjaZpgJBpIgZK57ykrtehv21mOF55VFhfXYRk8oNYRymRBmUA1qka0pk0MS/O5p0h7sdLdXCgImZUYYElri1t2hK8MG93cas/sWjm0HuSQhsuh4udUOTShjSV0D+egY6YVw7vAkNEwKhSc56WO7FCm/dNkEIUpuP4ag2i+n+asd3eQIcPsEX1kBu0Hss6zQzGDTjsLAF0Ob+xoA+b2+ZeRHtHKACo357bc71RsBe+8S+v0KTtUGT0KJUYf7EZLsrO3FfcppHiAXzTkGoI1S5cgwwWUgC1jhALOLY7l7HQLcm//HQr3zoXOjMAPCvOO/4rodgSLH8OZV7uDM68BehnIh548+S7huYn1/ZrwvBxe1Bm3jr31LeG5DtdNPGMFqhAV7DyjDxWBsfApmX+6mZ04E6pjh1LHDvYwr2MHZLxAItCxAevYwDbzOvANRGygH+hcq2GBspbbi6ethpw9WY8MEHWqQAZEJG6HAaSA1tjMbcbG7RE240T2y1eq4AHcfQOTIrcICyATyw0x2/V871t2TECeXNXAeVLzWzypnsWfE4c0Z3ebElS6aySq6vPyR9wDSm4R9ug/po4Hy5Ica5McRXa3ZTX8X47uDe4+T0FGvAS8aAeK7vz1HegyjvwX6cLnocLKvXQx9LBlj7iaM4SibXi5qrBnCgylT9/9l4F4VtWm1nVA2K1m3ZAhXUtXQzVDSIrHv/AWRw178HQIchsU+G9gX31N+v8GP14kyDu2PL9GyPdwGmpi60mmOXYUZ5Edp4HeNoSVyA3sdU4bG4jkVuKL7FiObj/x3H8ta7SzM34rTmRT+ep0efFoZvuOLstdgPSmL9eAat/nsQ/1GlN6mrMDLLqWB5xW2bkc7/N197HhkS2PYwKftF6JJqRD+jBIFwZZVtOApVtzFweHOQdSZ5ex4Q3tjLbxDB8tFQJW7qrQ42p2lH9Zzc2l/FhVa4spR7xV1dBA//uAz+cfHAc5ud/VPFbIP4MR2FbGEd5+J6ysp/B9jwgFV2mnsLNnzltW/VdQdOEHaO+cJBRp6QyHWfDMx6wtgF08OyM9AtC7m44I7COX/juW3eJqSYcViSaM+uQqjvrJ9R2oG0tAivpFnHGVDPqIDP5TuCOR8pV8lG60VLM0VF4mfKjZ2IhTZHwpEvwLr+LZhDFSqqvFtEzE4ycr0TPA1TLOmWaWy4GwHlyr42LmnX/yQjH+cbi9uEfPB/lKMV0K5nY1p0rdFc3L7o4mxWsNNxFO/jvMCZ+4WqYKRcvoUMQUwTMLW/FPFvL76rhD/kyMr13l3K12OoV3ejV2OgE7feMZ0rv7F6sq9mgVk6b0BUahaDCZhnA1Agva9V+EliIHjwHEkPnpUBl7HfDo19AIvC6WKqwoJDwaBFce3Y/tUyFlOgGNvnuaGn1/G53P0dv1X4HGvm4bMnKqelf7MOk2l/cg1O1q1i24Tu0U0hx7AsjT/wruAyFSoOhMKOrfeoVToUqWuB5fzUZypqtjXf/Jua94cIiidWHmW826NigCnV24JuOxMxEZ2Sn63pPtvTbj1siMe3nGs8B2T36nZB0UyloQmXUVZKVFPEjt1aS6PYFq6RZFfkAN84eTTNlAq+EdXMyPPRPBplzcQ6r1FBf+ilbtr8KjMW1093t/DdNxQnkbkujMIRHNJcbdl0LmkeUgK5aDQtJkKULPYee7KlYCq10t04QXpuKB1ZZ7hZVXifHuE1aOpZQHhJW1lALcnHolgso3b+Gy+4XrMV+zeVkXV/P4Zf1czROFougr4S46P+Pc2IDcaI/o+0OfhXkQP7IPTpBSMXUL6h9jnENo8rwUz+d0pNtbvqIMaVv4SjnJqi8HRSAZXgPxJOkXRYczX/mSOO3MeoVZp50mNXs5KfrdLof7cWQf7yDCz/9exIdPIj+sblG1JuXrm/vCoG8+Ct1/8SsMSyLkz28JzUR/o2Mms9d29K+5FBlHWtnfS5wWjksyKzkXLaNcBbv7fb3GXHgGJlAAhFAwEzWghdpkoeBBvPlQHnJ+Mxrnh1//Pv6MugF+XFVBPG1x2wm3HQPmet0O2leezrvsNgQ3oytx7M7NNKF4V7zppfTYOp6QaCo8Cm+HNxPoaekCizh9ud1TwDMa9sAn8ucspKIBo7mwnKEUB/oSthsqNutVbcQFA9MI5vIVhmJIzD8hFBQo+0mTmf0X1TRGs6r7mLJOijCNpbJxJ9UdblICb8dXGRcXMDlcF5paY/gqJJE1f6WuSEazH77CU1vfYDZDDA1GAzoQkcmVTTBn4rLE7h6ybRN6ag8/Tj+jTmzS8/Wm0Mapg+x/WnU+VO4BW2xF+59ya0F2+J4b9RzwtFY27qELVBW82S7HLoKWLIU+U+HPFmEPGvVCDgQ30r2ZsVbIYAuW2N2xd8ETexNktv8Hbn1bpxE/QVXKnJS9UczNGOOcjAHpgMk3kkNIbB8an0Y9l9mFD8qyLsvEzQt8+dz0HhpJcNF2sf6GmqbjwVL2xhFoZCbpTKPYX3UYAkvc2Y2rAYVd82skYWSc4gHvFYOV6AHfUdiuSal0drC5SroHRkK5dWq5mP9COaGA7vhwlcRSgAR37GPQKTbkHOrsf3pP0dmh1mkMvys6+8s1JNgYezSN6+yO94hy15HDIzJ8HIgPuvOXUj3xUdAndvk4FavHgPVT6rjluNXq++gxkri4+n76TRIVW8lIzQZ8yTcIaIG7FXIFzOitlixyAweaQwEVlSBGvYAxnLDWwVBW/wOE0Q1Q2cp/UPfqxa0m1q8ubKU25dP13rEP/4Nr6BgVeh2bWsut0bgI5Kp4M6riHb/gqniuph1VPHIP23StXxiuTGEWKNayB6+ozetR7weqPP+uXuOchMwxES2ZE2lJm9id1OaWN/jiOLSq7X0yZCtFGyq3266tD9ltU6DCde9ykRzDl9EvwWvgKay/axsDXmAKup6QJolHPfazGwGvgdHUgRk+ktgL23bg9RPtdODGVh0oC9nmssM+b+z4b/iXtvKtkA3BjajPtphlr1jCBLEJ1rINWilW2NUQMzeaBGhAl3bRKsfvwoyI+LyZlciKwp5OeAzJHb8ePuDJZFJa/VOl+cEq6Sn4/xD8vx7+x4IaNxd9BF4HtW86PFTiw304ILwF/o+kbMS/93p433jDkWv3jVPqwjs2XlgYeuKfeV1xNZj+uuJqMInX4WW6emVbUNm4Rj8PpFXa6aAcn14JsYOPHTrK66Y96V7WYDWqiu74yg1IxfHf/wVYqceR0H7ftQ4VByJ85V7ZoPgUjHEmAz3kpic7OwIZatDZrA8pJkAif4RMbNt59JDjVPrRpba+MibZ8DhVFf/Sq+RihNv7kU59z9WS5Ou/AZebJ8zpvaT7Uaxy+beBNFIpzdV8mxTvah7unNvaUSGwhGaeNvYvELgBG4z4hjU6xQbRB1n/DjK25gy1ZzyUnCj14sb9SdURJZ89iOZqeuXGHcshQurVUEVH6hWzqUqyiiFbWU+3ilIWXk27Hk82obnESgQ3aM5OYdDCjXb5eyBY9rIXw6QtBXnYKHUXmyz8UGHHCksOEW2Ua2aOZhSeIr7WALwQBPUoPL3qvInAwPt8+gBUiDcLhYzgO3ByuBMz49FXZxcRlqj0xX9HDF4I2yjmfYfnaoX87dHohh2UK81yQ95pTQJejL4LD2/mteAOptvxJ1FYVWHufybva1RALQVBEfftl1YIljJ39gKze+Z+kOSCXD5Ac4NGk1kq5D8erWaDLHiZrvJtlKYrNmiJxsdu+DgSV8a7vusiuJ6j65yH/F2vCTmbWkr8evIHxeMTiPG1VxSFPhE5zXA4qKihKqctZyUkjmcvl7MXkBnGFLiFF32c359v1Uu9chcatcu6C3tMRtBNrGklwnZvWiVenSk7/gS9NguWrzF2Yf6bWgJBArocvqTYl3HTpOtxxSSwGGA6GxuevZwNPqqoPtg6fn2CkofVqhYktPT2r6UV2OC3yYtOI42Av6IUL1v2qs62wPg7NG7L3sAttHETf/5Vkgo7YLl18W/Adzafshm6g+PdX41z7wX4hAhzWvm+yGDmJxqetgN7EgLO2zUcOFDvA69x5Zr38sIXkb1cShN2/G2vcfo3sSNfKMoee6cW7+7ssxzaE+UyjiYh//cYpU0uo8PO+H4fj9r2dYzwnN2gLqDYvYdCymFEn+JCfUJzC+9OwxGe09Qalt8exqzO5WZ59p/8C/HW3Oy9AK+zKNmb8E8d/tmgIRia5Zn7yYCV5PgpyQF/TyU5tvQ/xqnSnb1XsFgWoMXqOSVs8kwkUaLLDgDHWzkctWwACSz200C9utekReemVOzJWSbUc18nem0KdMcKkkMVwJAxCjuv4Ju6iKx1aupBSKXeCQOXJKeiS8vSDVCJkI/3CIcqQpkwD7qd5CiSDd3f0oeGt1zjapiuHuyzewxXnuSoSs2aLvWyo7ELF+ynu6M/l9L0jsAgO/IKrH1ZZXfceNqrl67D4BHaZYKwx5ycnlaGjFAPsJFj31kfwYbpJf4ozoa30nps/WEFPdRkWPu3+MJDjeC8uYfbcB5yHXJfBOeRLJTuxhWISSONbjIkrVco+jbFDpfwuYIIkHLhJmsORSw4TKwMXgOdVUlnTjblzSxCKFvSfrQnzV5uzpidIz2C5AhcfN9+onIrZ7DVKFB+ONDeouaPrdt45BByXN463j+pE7q3mfy0XgTaDIzmLtJd1yk+2Tu9yPKM67quRE25CVS96STS8ZTaj9g2DIlVVuMck8rlz8wFJIBSyOkKqCIQSRVIn4uh58tW8Z6z4dTtaWfboGP7QQUdikwgrKQyF2FvWlP4k/Lh+YPK6OlLKP+Uw5FYTQ0MRmLPbkXsk6A3Da8ovdmwX9VZ8XCsZxqneTZQrb14cERt7BdfK+DqcC7GnZ+8V1Thcx/1N36jkoAFgWWY6XCrglVEHtD8yaOKcB6IGD1T3R5G3/i8FWQGKX15qnVf5n+OsZmCUu9W/NiFS1XMMA0yyIbFf6Xlwmq6tgG4pQd7tE5ZKqN2kQqZAgOYo+6/MP0Yhv5VuVIC6ol3FPwoxRF1XRBBVGr8UZex21KyiQTgEh2fkUxIPdVAArDIXIL0ctE5VC4X+5eNwqs8nN04p8qH2B5YFvlHRvEsMUqWOTCkL+m2UAve/f8ZERp8ySxx3o9gBEbpV6tibjECzaRAK/NQeM5IjUTpaCLH+Asv0Y4ofSHb2koo4MdtWWz/EWpFzCxzTqMhQoEuReoWajR77JCCTksH2i9GSH63X/W78B4ka9K3b3BHk4KZuA1Cy5caSPLfqyd9xiyfg0byvsUJ3Cx/J+ZdQW0GVZmC8+gdrBFWlUBXRMFyaADqNWLeN8jRBVVuRwXwYAOxoAtdqqsogpyiwcRRwabjN3gLSmiX8P0XQYO/By9TfKB1zq5tc9ox50DMObR1zm6RObtDzp+LVPK/HzkiHkEWp6BsIepNz1+m+O3SDKjoqCiX553BmvIuqY3WY1XO69KqIKkbzs7loVRpKDRw94sKuzZXtC/MF1ZzYktFdqTPkHlSElqNUvH6P5NraQX0Yw7e7G9Y8LpyTQnO/ls5yL6iYy2gMgLr5F1G3uHwFiwlIAtBrMcbipQ+SL/Rh39WKX2gBqGsZOR3i0l9cOwT4QXEjxQHv0Am9DGKTxnxa1YqdSf8Rt2vtapbNnz4F+UmFhzCXyimmHw07wxazFyXTMIqLzQPVNGMEgFxORAaCExE+OZyUkrzIoURdXhDw8Sc5zyQMzGtqqCGcmHct4gc2NlPPUpnny5vv7OBytaA+AanyKtrwlNk/FNqFQN/o4qNraoAlTtu3hAol6SWa/ys/XJz1HLwPqL1NpOp1QV+ra8DDa/ZE9X9f9kweQ0tL2F5HjvvFmFXI1qRGtNq3IYR8IF1uhGXAkNugedYmMEbyZF2KIVlNFx6Ta8pHlNoHFktFHTWqdz+DaSmx8H0E/TCT38yReQHuf8XfAoozl+7XyNzovN8YCOsaHHRTKvaW9DXNEld1b4GmWi/l/tm85XtiQAZhH0a2VkvCQC0jvNgjZaortESNfLBEr/gOq1Fl2+3I2EZLtR9fL9KNlheU7bjt2mU7fiNqr/5H8kyuLRBw+Px5I4yvabnzpqSg7yePdMayg0pmIjL/kbmL6cqf15NLsuNUBu5vklTaNB9uWtOo2p4EeKM8OtoDGB/GqgGwPWxQp2GGatD7g+NqodfIyssJy2c3nwwWNmRIE9LpItUyAE6Wth1rqPbWS9SqFq6mb1zI7zTVyEfg518TMLzvFDQwo9cTVjNjbh90E51jTHpd9agYQDkKIjNhL/S4IIa50CxoBGQ6JrZoMmbyZRN8wYa3yuNIRtHSqAvd/Xbz5Y2orKQX+V8K3Re4vhufu5pYRsvjLZ737jvvTE9SOHEvYSLVkY4020XYZVuSn/GKBT0pD12w8I/K8iM1ivIvIouU6OWQ7pGis0dlYMPQv4MzI47d4/jGRA3cpeHQu0Ulap2obqQXaj7Z+HzBGheBM3Dg+Kz+EE2sDSkRNSp3GhiZ/ZxS4QJesh3mgynXiXLv1CQHuKLA6+Sc4fLnyzk/6hcuFZEN7BdL+STRPPrhPyltJFrlJ6CXplgnh9JCrEHxRl3v/x7CXeLxsn34+3qcy3L3se7Nr34ZoVmZiVPZykVEU6ikMCNfcP2cWOfv4wM2YZhr5K2NJ3z12LuUp9bnK2AJJd9wykxl3tg15HFjAXKACfb0Q/Z63+Wb7SwVViRVZub8YhzSu5C3Rinw+qOrVnFN0X4JlrMKdWLWAX5OraujEC+ToHe+lWKDnEz799L8O6/gbNTKhtxmSqYzOHxqpePe3KEMjmZTSrjyuRk8oUjl9RZyXNYb5LDjhfx0xxlIC+yfpR59ov+D7k/Uz/eXw3amrdT9fE/PU8SeQ572Ku6V9eFbN5nSsM+b1Y5tvYVboqeDSyhYVWfAj88Zg3GHngFa/W8yI/XA5y7nw2pwXVh0f5qKSemVDyv5IjjWdl3IdNYXdhx8A+lYQsYevtq/F/T4TfDo69wLr8OufwPbQ+IPYCcEDIZH2KBT9AYj42x1F00WsvzipEt3NYTnykHidRucH8a9l1J+IDRUJyJvNq2Dg+KRbMtr7exzr3IN3jeeRkPC9npwGt6grO/Z4qWNpj//DGa0o6SexfXRmdBy/5ZUcj3dywx5KZnLEvITX9E6q6a7N29cM/JPxFdKfak8hM3rqqgTb/Pde4O4McsaMl1dZDzpvQE6XrIQR9GwYf+9CFqyXWuq9EBQZSP+J8NosF3ocF1Vb9MJ5/PPO9U/RCs7r5k//tGj+rs7J+EOJ1Zvor6LZ5/cJ3VWd3ZZ83u2T+Rp5OQH8d9ab7JJ3LqyYQ9JFDrcI9ZoadoskMCKF5/iaaVaMxIdgroqMiqLhEBNnFr2+rdfH86bG2LZlO8RM7Rar1YNpqNgtS0E4E+eDTGtrOdVnvzVgcorSotCvljFLe1AvSWpbM42U3wH33GWl7Ew2LCS3gD0+PJia6G6XaPocP9fGxZ08mpXcgvAcAnWYJJFsEO/YZ2o9lJVDwHzqZhnTVdLI+Ctauh4kV+tZ+Yv0/I/4pPytFM9EeOd8On3OEgPN6ebMZeGm9PZURUaU/mUFJpHHL2Kdnw+8j6t6n1P+UNwaJnqMq4yML+jTQAAcZgR1DDMp3dgNPM0p/0Qv5ogIo5fWZfYeXtQdzCsPQV0z6D1aM5jSHe/TdyH+OeCPfD23lb/uFXFL+JGQwPc5yCeh6geqYbhZWTMOZC9ikyxqjWn1P+LKUetnMvLyL1wOzLurTOZ0n70ZFxqzQKx1Y8kC34pJ3R3bZHBZijJz/U0pPpSiJGzK0lX69UrCWFW4JqsN4484onjYqlxO4eGNDb5F/Qr8AqH2Wvf8xpkZ0rV1BGq/1/7roWZVt3X9uDXI6InuShUrSbTJofriSTJhAW2tBQy+/BbSqQZRbP8hJmKQkYCcZNtZb8k1J3Ze3iqMNJ0rwbb3Rhj1YoYOtJYOsqO05Fmrscp9CPqxtoZnV4TEeIc9w=
*/