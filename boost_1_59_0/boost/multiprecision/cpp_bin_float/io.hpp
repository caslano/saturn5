///////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CPP_BIN_FLOAT_IO_HPP
#define BOOST_MP_CPP_BIN_FLOAT_IO_HPP

#include <boost/multiprecision/detail/no_exceptions_support.hpp>
#include <boost/multiprecision/detail/assert.hpp>

namespace boost { namespace multiprecision {
namespace cpp_bf_io_detail {

//
// Multiplies a by b and shifts the result so it fits inside max_bits bits,
// returns by how much the result was shifted.
//
template <class I>
inline I restricted_multiply(cpp_int& result, const cpp_int& a, const cpp_int& b, I max_bits, std::int64_t& error)
{
   result   = a * b;
   I gb     = msb(result);
   I rshift = 0;
   if (gb > max_bits)
   {
      rshift      = gb - max_bits;
      I   lb      = lsb(result);
      int roundup = 0;
      // The error rate increases by the error of both a and b,
      // this may be overly pessimistic in many case as we're assuming
      // that a and b have the same level of uncertainty...
      if (lb < rshift)
         error = error ? error * 2 : 1;
      if (rshift)
      {
         BOOST_MP_ASSERT(rshift < INT_MAX);
         if (bit_test(result, static_cast<unsigned>(rshift - 1)))
         {
            if (lb == rshift - 1)
               roundup = 1;
            else
               roundup = 2;
         }
         result >>= rshift;
      }
      if ((roundup == 2) || ((roundup == 1) && (result.backend().limbs()[0] & 1)))
         ++result;
   }
   return rshift;
}
//
// Computes a^e shifted to the right so it fits in max_bits, returns how far
// to the right we are shifted.
//
template <class I>
inline I restricted_pow(cpp_int& result, const cpp_int& a, I e, I max_bits, std::int64_t& error)
{
   BOOST_MP_ASSERT(&result != &a);
   I exp = 0;
   if (e == 1)
   {
      result = a;
      return exp;
   }
   else if (e == 2)
   {
      return restricted_multiply(result, a, a, max_bits, error);
   }
   else if (e == 3)
   {
      exp = restricted_multiply(result, a, a, max_bits, error);
      exp += restricted_multiply(result, result, a, max_bits, error);
      return exp;
   }
   I p = e / 2;
   exp = restricted_pow(result, a, p, max_bits, error);
   exp *= 2;
   exp += restricted_multiply(result, result, result, max_bits, error);
   if (e & 1)
      exp += restricted_multiply(result, result, a, max_bits, error);
   return exp;
}

inline int get_round_mode(const cpp_int& what, std::int64_t location, std::int64_t error)
{
   //
   // Can we round what at /location/, if the error in what is /error/ in
   // units of 0.5ulp.  Return:
   //
   // -1: Can't round.
   //  0: leave as is.
   //  1: tie.
   //  2: round up.
   //
   BOOST_MP_ASSERT(location >= 0);
   BOOST_MP_ASSERT(location < INT_MAX);
   std::int64_t error_radius = error & 1 ? (1 + error) / 2 : error / 2;
   if (error_radius && (static_cast<int>(msb(error_radius)) >= location))
      return -1;
   if (bit_test(what, static_cast<unsigned>(location)))
   {
      if (static_cast<int>(lsb(what)) == location)
         return error ? -1 : 1; // Either a tie or can't round depending on whether we have any error
      if (!error)
         return 2; // no error, round up.
      cpp_int t = what - error_radius;
      if (static_cast<int>(lsb(t)) >= location)
         return -1;
      return 2;
   }
   else if (error)
   {
      cpp_int t = what + error_radius;
      return bit_test(t, static_cast<unsigned>(location)) ? -1 : 0;
   }
   return 0;
}

inline int get_round_mode(cpp_int& r, cpp_int& d, std::int64_t error, const cpp_int& q)
{
   //
   // Lets suppose we have an inexact division by d+delta, where the true
   // value for the divisor is d, and with |delta| <= error/2, then
   // we have calculated q and r such that:
   //
   // n                  r
   // ---       = q + -----------
   // d + error        d + error
   //
   // Rearranging for n / d we get:
   //
   //    n         delta*q + r
   //   --- = q + -------------
   //    d              d
   //
   // So rounding depends on whether 2r + error * q > d.
   //
   // We return:
   //  0 = down down.
   //  1 = tie.
   //  2 = round up.
   // -1 = couldn't decide.
   //
   r <<= 1;
   int c = r.compare(d);
   if (c == 0)
      return error ? -1 : 1;
   if (c > 0)
   {
      if (error)
      {
         r -= error * q;
         return r.compare(d) > 0 ? 2 : -1;
      }
      return 2;
   }
   if (error)
   {
      r += error * q;
      return r.compare(d) < 0 ? 0 : -1;
   }
   return 0;
}

} // namespace cpp_bf_io_detail

namespace backends {

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::operator=(const char* s)
{
   cpp_int                      n;
   std::intmax_t              decimal_exp     = 0;
   std::intmax_t              digits_seen     = 0;
   constexpr const std::intmax_t max_digits_seen = 4 + (cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count * 301L) / 1000;
   bool                         ss              = false;
   //
   // Extract the sign:
   //
   if (*s == '-')
   {
      ss = true;
      ++s;
   }
   else if (*s == '+')
      ++s;
   //
   // Special cases first:
   //
   if ((std::strcmp(s, "nan") == 0) || (std::strcmp(s, "NaN") == 0) || (std::strcmp(s, "NAN") == 0))
   {
      return *this = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::quiet_NaN().backend();
   }
   if ((std::strcmp(s, "inf") == 0) || (std::strcmp(s, "Inf") == 0) || (std::strcmp(s, "INF") == 0) || (std::strcmp(s, "infinity") == 0) || (std::strcmp(s, "Infinity") == 0) || (std::strcmp(s, "INFINITY") == 0))
   {
      *this = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::infinity().backend();
      if (ss)
         negate();
      return *this;
   }
   //
   // Digits before the point:
   //
   while (*s && (*s >= '0') && (*s <= '9'))
   {
      n *= 10u;
      n += *s - '0';
      if (digits_seen || (*s != '0'))
         ++digits_seen;
      ++s;
   }
   // The decimal point (we really should localise this!!)
   if (*s && (*s == '.'))
      ++s;
   //
   // Digits after the point:
   //
   while (*s && (*s >= '0') && (*s <= '9'))
   {
      n *= 10u;
      n += *s - '0';
      --decimal_exp;
      if (digits_seen || (*s != '0'))
         ++digits_seen;
      ++s;
      if (digits_seen > max_digits_seen)
         break;
   }
   //
   // Digits we're skipping:
   //
   while (*s && (*s >= '0') && (*s <= '9'))
      ++s;
   //
   // See if there's an exponent:
   //
   if (*s && ((*s == 'e') || (*s == 'E')))
   {
      ++s;
      std::intmax_t e  = 0;
      bool            es = false;
      if (*s && (*s == '-'))
      {
         es = true;
         ++s;
      }
      else if (*s && (*s == '+'))
         ++s;
      while (*s && (*s >= '0') && (*s <= '9'))
      {
         e *= 10u;
         e += *s - '0';
         ++s;
      }
      if (es)
         e = -e;
      decimal_exp += e;
   }
   if (*s)
   {
      //
      // Oops unexpected input at the end of the number:
      //
      BOOST_MP_THROW_EXCEPTION(std::runtime_error("Unable to parse string as a valid floating point number."));
   }
   if (n == 0)
   {
      // Result is necessarily zero:
      *this = static_cast<limb_type>(0u);
      return *this;
   }

   constexpr const std::size_t limb_bits = sizeof(limb_type) * CHAR_BIT;
   //
   // Set our working precision - this is heuristic based, we want
   // a value as small as possible > cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count to avoid large computations
   // and excessive memory usage, but we also want to avoid having to
   // up the computation and start again at a higher precision.
   // So we round cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count up to the nearest whole number of limbs, and add
   // one limb for good measure.  This works very well for small exponents,
   // but for larger exponents we may may need to restart, we could add some
   // extra precision right from the start for larger exponents, but this
   // seems to be slightly slower in the *average* case:
   //
#ifdef BOOST_MP_STRESS_IO
   std::intmax_t max_bits = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + 32;
#else
   std::intmax_t max_bits = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + ((cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count % limb_bits) ? (limb_bits - cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count % limb_bits) : 0) + limb_bits;
#endif
   std::int64_t  error          = 0;
   std::intmax_t calc_exp       = 0;
   std::intmax_t final_exponent = 0;

   if (decimal_exp >= 0)
   {
      // Nice and simple, the result is an integer...
      do
      {
         cpp_int t;
         if (decimal_exp)
         {
            calc_exp = boost::multiprecision::cpp_bf_io_detail::restricted_pow(t, cpp_int(5), decimal_exp, max_bits, error);
            calc_exp += boost::multiprecision::cpp_bf_io_detail::restricted_multiply(t, t, n, max_bits, error);
         }
         else
            t = n;
         final_exponent = (std::int64_t)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1 + decimal_exp + calc_exp;
         std::ptrdiff_t rshift     = msb(t) - cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + 1;
         if (rshift > 0)
         {
            final_exponent += rshift;
            int roundup = boost::multiprecision::cpp_bf_io_detail::get_round_mode(t, rshift - 1, error);
            t >>= rshift;
            if ((roundup == 2) || ((roundup == 1) && t.backend().limbs()[0] & 1))
               ++t;
            else if (roundup < 0)
            {
#ifdef BOOST_MP_STRESS_IO
               max_bits += 32;
#else
               max_bits *= 2;
#endif
               error = 0;
               continue;
            }
         }
         else
         {
            BOOST_MP_ASSERT(!error);
         }
         if (final_exponent > cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent)
         {
            exponent() = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent;
            final_exponent -= cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent;
         }
         else if (final_exponent < cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::min_exponent)
         {
            // Underflow:
            exponent() = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::min_exponent;
            final_exponent -= cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::min_exponent;
         }
         else
         {
            exponent()     = static_cast<Exponent>(final_exponent);
            final_exponent = 0;
         }
         copy_and_round(*this, t.backend());
         break;
      } while (true);

      if (ss != sign())
         negate();
   }
   else
   {
      // Result is the ratio of two integers: we need to organise the
      // division so as to produce at least an N-bit result which we can
      // round according to the remainder.
      //cpp_int d = pow(cpp_int(5), -decimal_exp);
      do
      {
         cpp_int d;
         calc_exp       = boost::multiprecision::cpp_bf_io_detail::restricted_pow(d, cpp_int(5), -decimal_exp, max_bits, error);
         std::ptrdiff_t shift      = static_cast<int>(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count) - msb(n) + msb(d);
         final_exponent = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1 + decimal_exp - calc_exp;
         if (shift > 0)
         {
            n <<= shift;
            final_exponent -= static_cast<Exponent>(shift);
         }
         cpp_int q, r;
         divide_qr(n, d, q, r);
         std::ptrdiff_t gb = msb(q);
         BOOST_MP_ASSERT((gb >= static_cast<int>(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count) - 1));
         //
         // Check for rounding conditions we have to
         // handle ourselves:
         //
         int roundup = 0;
         if (gb == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1)
         {
            // Exactly the right number of bits, use the remainder to round:
            roundup = boost::multiprecision::cpp_bf_io_detail::get_round_mode(r, d, error, q);
         }
         else if (bit_test(q, gb - static_cast<int>(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count)) && (static_cast<int>(lsb(q)) == (gb - static_cast<int>(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count))))
         {
            // Too many bits in q and the bits in q indicate a tie, but we can break that using r,
            // note that the radius of error in r is error/2 * q:
            std::ptrdiff_t lshift = gb - static_cast<int>(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count) + 1;
            q >>= lshift;
            final_exponent += static_cast<Exponent>(lshift);
            BOOST_MP_ASSERT((msb(q) >= cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1));
            if (error && (r < (error / 2) * q))
               roundup = -1;
            else if (error && (r + (error / 2) * q >= d))
               roundup = -1;
            else
               roundup = r ? 2 : 1;
         }
         else if (error && (((error / 2) * q + r >= d) || (r < (error / 2) * q)))
         {
            // We might have been rounding up, or got the wrong quotient: can't tell!
            roundup = -1;
         }
         if (roundup < 0)
         {
#ifdef BOOST_MP_STRESS_IO
            max_bits += 32;
#else
            max_bits *= 2;
#endif
            error = 0;
            if (shift > 0)
            {
               n >>= shift;
               final_exponent += static_cast<Exponent>(shift);
            }
            continue;
         }
         else if ((roundup == 2) || ((roundup == 1) && q.backend().limbs()[0] & 1))
            ++q;
         if (final_exponent > cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent)
         {
            // Overflow:
            exponent() = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent;
            final_exponent -= cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent;
         }
         else if (final_exponent < cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::min_exponent)
         {
            // Underflow:
            exponent() = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::min_exponent;
            final_exponent -= cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::min_exponent;
         }
         else
         {
            exponent()     = static_cast<Exponent>(final_exponent);
            final_exponent = 0;
         }
         copy_and_round(*this, q.backend());
         if (ss != sign())
            negate();
         break;
      } while (true);
   }
   //
   // Check for scaling and/or over/under-flow:
   //
   final_exponent += exponent();
   if (final_exponent > cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent)
   {
      // Overflow:
      exponent() = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity;
      bits()     = limb_type(0);
   }
   else if (final_exponent < cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::min_exponent)
   {
      // Underflow:
      exponent() = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero;
      bits()     = limb_type(0);
      sign()     = 0;
   }
   else
   {
      exponent() = static_cast<Exponent>(final_exponent);
   }
   return *this;
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
std::string cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::str(std::streamsize dig, std::ios_base::fmtflags f) const
{
   bool scientific = (f & std::ios_base::scientific) == std::ios_base::scientific;
   bool fixed      = !scientific && (f & std::ios_base::fixed);

   if (dig == 0 && !fixed)
      dig = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::max_digits10;

   std::string s;

   if (exponent() <= cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent)
   {
      // How far to left-shift in order to demormalise the mantissa:
      std::intmax_t shift         = (std::intmax_t)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - (std::intmax_t)exponent() - 1;
      std::intmax_t digits_wanted = static_cast<int>(dig);
      std::intmax_t base10_exp    = exponent() >= 0 ? static_cast<std::intmax_t>(std::floor(0.30103 * exponent())) : static_cast<std::intmax_t>(std::ceil(0.30103 * exponent()));
      //
      // For fixed formatting we want /dig/ digits after the decimal point,
      // so if the exponent is zero, allowing for the one digit before the
      // decimal point, we want 1 + dig digits etc.
      //
      if (fixed)
         digits_wanted += 1 + base10_exp;
      if (scientific)
         digits_wanted += 1;
      if (digits_wanted < -1)
      {
         // Fixed precision, no significant digits, and nothing to round!
         s = "0";
         if (sign())
            s.insert(static_cast<std::string::size_type>(0), 1, '-');
         boost::multiprecision::detail::format_float_string(s, base10_exp, dig, f, true);
         return s;
      }
      //
      // power10 is the base10 exponent we need to multiply/divide by in order
      // to convert our denormalised number to an integer with the right number of digits:
      //
      std::intmax_t power10 = digits_wanted - base10_exp - 1;
      //
      // If we calculate 5^power10 rather than 10^power10 we need to move
      // 2^power10 into /shift/
      //
      shift -= power10;
      cpp_int               i;
      int                   roundup   = 0; // 0=no rounding, 1=tie, 2=up
      constexpr const std::size_t limb_bits = sizeof(limb_type) * CHAR_BIT;
      //
      // Set our working precision - this is heuristic based, we want
      // a value as small as possible > cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count to avoid large computations
      // and excessive memory usage, but we also want to avoid having to
      // up the computation and start again at a higher precision.
      // So we round cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count up to the nearest whole number of limbs, and add
      // one limb for good measure.  This works very well for small exponents,
      // but for larger exponents we add a few extra limbs to max_bits:
      //
#ifdef BOOST_MP_STRESS_IO
      std::intmax_t max_bits = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + 32;
#else
      std::intmax_t max_bits = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + ((cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count % limb_bits) ? (limb_bits - cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count % limb_bits) : 0) + limb_bits;
      if (power10)
         max_bits += (msb(boost::multiprecision::detail::abs(power10)) / 8) * limb_bits;
#endif
      do
      {
         std::int64_t  error    = 0;
         std::intmax_t calc_exp = 0;
         //
         // Our integer result is: bits() * 2^-shift * 5^power10
         //
         i = bits();
         if (shift < 0)
         {
            if (power10 >= 0)
            {
               // We go straight to the answer with all integer arithmetic,
               // the result is always exact and never needs rounding:
               BOOST_MP_ASSERT(power10 <= (std::intmax_t)INT_MAX);
               i <<= -shift;
               if (power10)
                  i *= pow(cpp_int(5), static_cast<unsigned>(power10));
            }
            else if (power10 < 0)
            {
               cpp_int d;
               calc_exp = boost::multiprecision::cpp_bf_io_detail::restricted_pow(d, cpp_int(5), -power10, max_bits, error);
               shift += calc_exp;
               BOOST_MP_ASSERT(shift < 0); // Must still be true!
               i <<= -shift;
               cpp_int r;
               divide_qr(i, d, i, r);
               roundup = boost::multiprecision::cpp_bf_io_detail::get_round_mode(r, d, error, i);
               if (roundup < 0)
               {
#ifdef BOOST_MP_STRESS_IO
                  max_bits += 32;
#else
                  max_bits *= 2;
#endif
                  shift = (std::intmax_t)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - exponent() - 1 - power10;
                  continue;
               }
            }
         }
         else
         {
            //
            // Our integer is bits() * 2^-shift * 10^power10
            //
            if (power10 > 0)
            {
               if (power10)
               {
                  cpp_int t;
                  calc_exp = boost::multiprecision::cpp_bf_io_detail::restricted_pow(t, cpp_int(5), power10, max_bits, error);
                  calc_exp += boost::multiprecision::cpp_bf_io_detail::restricted_multiply(i, i, t, max_bits, error);
                  shift -= calc_exp;
               }
               if ((shift < 0) || ((shift == 0) && error))
               {
                  // We only get here if we were asked for a crazy number of decimal digits -
                  // more than are present in a 2^max_bits number.
#ifdef BOOST_MP_STRESS_IO
                  max_bits += 32;
#else
                  max_bits *= 2;
#endif
                  shift = (std::intmax_t)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - exponent() - 1 - power10;
                  continue;
               }
               if (shift)
               {
                  roundup = boost::multiprecision::cpp_bf_io_detail::get_round_mode(i, shift - 1, error);
                  if (roundup < 0)
                  {
#ifdef BOOST_MP_STRESS_IO
                     max_bits += 32;
#else
                     max_bits *= 2;
#endif
                     shift = (std::intmax_t)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - exponent() - 1 - power10;
                     continue;
                  }
                  i >>= shift;
               }
            }
            else
            {
               // We're right shifting, *and* dividing by 5^-power10,
               // so 5^-power10 can never be that large or we'd simply
               // get zero as a result, and that case is already handled above:
               cpp_int r;
               BOOST_MP_ASSERT(-power10 < INT_MAX);
               cpp_int d = pow(cpp_int(5), static_cast<unsigned>(-power10));
               d <<= shift;
               divide_qr(i, d, i, r);
               r <<= 1;
               int c   = r.compare(d);
               roundup = c < 0 ? 0 : c == 0 ? 1 : 2;
            }
         }
         s = i.str(0, std::ios_base::fmtflags(0));
         //
         // Check if we got the right number of digits, this
         // is really a test of whether we calculated the
         // decimal exponent correctly:
         //
         std::intmax_t digits_got = i ? static_cast<std::intmax_t>(s.size()) : 0;
         if (digits_got != digits_wanted)
         {
            base10_exp += digits_got - digits_wanted;
            if (fixed)
               digits_wanted = digits_got; // strange but true.
            power10 = digits_wanted - base10_exp - 1;
            shift   = (std::intmax_t)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - exponent() - 1 - power10;
            if (fixed)
               break;
            roundup = 0;
         }
         else
            break;
      } while (true);
      //
      // Check whether we need to round up: note that we could equally round up
      // the integer /i/ above, but since we need to perform the rounding *after*
      // the conversion to a string and the digit count check, we might as well
      // do it here:
      //
      if ((roundup == 2) || ((roundup == 1) && ((s[s.size() - 1] - '0') & 1)))
      {
         boost::multiprecision::detail::round_string_up_at(s, static_cast<int>(s.size() - 1), base10_exp);
      }

      if (sign())
         s.insert(static_cast<std::string::size_type>(0), 1, '-');

      boost::multiprecision::detail::format_float_string(s, base10_exp, dig, f, false);
   }
   else
   {
      switch (exponent())
      {
      case exponent_zero:
         s = sign() ? "-0" : f & std::ios_base::showpos ? "+0" : "0";
         boost::multiprecision::detail::format_float_string(s, 0, dig, f, true);
         break;
      case exponent_nan:
         s = "nan";
         break;
      case exponent_infinity:
         s = sign() ? "-inf" : f & std::ios_base::showpos ? "+inf" : "inf";
         break;
      }
   }
   return s;
}

} // namespace backends
}} // namespace boost::multiprecision

#endif

/* io.hpp
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
*/