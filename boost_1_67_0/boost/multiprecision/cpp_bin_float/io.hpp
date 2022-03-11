///////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CPP_BIN_FLOAT_IO_HPP
#define BOOST_MP_CPP_BIN_FLOAT_IO_HPP

namespace boost { namespace multiprecision {
namespace cpp_bf_io_detail {

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4127) // conditional expression is constant
#endif

//
// Multiplies a by b and shifts the result so it fits inside max_bits bits,
// returns by how much the result was shifted.
//
template <class I>
inline I restricted_multiply(cpp_int& result, const cpp_int& a, const cpp_int& b, I max_bits, boost::int64_t& error)
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
         BOOST_ASSERT(rshift < INT_MAX);
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
inline I restricted_pow(cpp_int& result, const cpp_int& a, I e, I max_bits, boost::int64_t& error)
{
   BOOST_ASSERT(&result != &a);
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

inline int get_round_mode(const cpp_int& what, boost::int64_t location, boost::int64_t error)
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
   BOOST_ASSERT(location >= 0);
   BOOST_ASSERT(location < INT_MAX);
   boost::int64_t error_radius = error & 1 ? (1 + error) / 2 : error / 2;
   if (error_radius && ((int)msb(error_radius) >= location))
      return -1;
   if (bit_test(what, static_cast<unsigned>(location)))
   {
      if ((int)lsb(what) == location)
         return error ? -1 : 1; // Either a tie or can't round depending on whether we have any error
      if (!error)
         return 2; // no error, round up.
      cpp_int t = what - error_radius;
      if ((int)lsb(t) >= location)
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

inline int get_round_mode(cpp_int& r, cpp_int& d, boost::int64_t error, const cpp_int& q)
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
   boost::intmax_t              decimal_exp     = 0;
   boost::intmax_t              digits_seen     = 0;
   static const boost::intmax_t max_digits_seen = 4 + (cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count * 301L) / 1000;
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
      boost::intmax_t e  = 0;
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
      BOOST_THROW_EXCEPTION(std::runtime_error("Unable to parse string as a valid floating point number."));
   }
   if (n == 0)
   {
      // Result is necessarily zero:
      *this = static_cast<limb_type>(0u);
      return *this;
   }

   static const unsigned limb_bits = sizeof(limb_type) * CHAR_BIT;
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
   boost::intmax_t max_bits = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + 32;
#else
   boost::intmax_t max_bits = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + ((cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count % limb_bits) ? (limb_bits - cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count % limb_bits) : 0) + limb_bits;
#endif
   boost::int64_t  error          = 0;
   boost::intmax_t calc_exp       = 0;
   boost::intmax_t final_exponent = 0;

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
         final_exponent = (boost::int64_t)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1 + decimal_exp + calc_exp;
         int rshift     = msb(t) - cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + 1;
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
            BOOST_ASSERT(!error);
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
         int shift      = (int)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - msb(n) + msb(d);
         final_exponent = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1 + decimal_exp - calc_exp;
         if (shift > 0)
         {
            n <<= shift;
            final_exponent -= static_cast<Exponent>(shift);
         }
         cpp_int q, r;
         divide_qr(n, d, q, r);
         int gb = msb(q);
         BOOST_ASSERT((gb >= static_cast<int>(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count) - 1));
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
         else if (bit_test(q, gb - (int)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count) && ((int)lsb(q) == (gb - (int)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count)))
         {
            // Too many bits in q and the bits in q indicate a tie, but we can break that using r,
            // note that the radius of error in r is error/2 * q:
            int lshift = gb - (int)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + 1;
            q >>= lshift;
            final_exponent += static_cast<Exponent>(lshift);
            BOOST_ASSERT((msb(q) >= cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1));
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
   if (dig == 0)
      dig = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::max_digits10;

   bool scientific = (f & std::ios_base::scientific) == std::ios_base::scientific;
   bool fixed      = !scientific && (f & std::ios_base::fixed);

   std::string s;

   if (exponent() <= cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent)
   {
      // How far to left-shift in order to demormalise the mantissa:
      boost::intmax_t shift         = (boost::intmax_t)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - (boost::intmax_t)exponent() - 1;
      boost::intmax_t digits_wanted = static_cast<int>(dig);
      boost::intmax_t base10_exp    = exponent() >= 0 ? static_cast<boost::intmax_t>(std::floor(0.30103 * exponent())) : static_cast<boost::intmax_t>(std::ceil(0.30103 * exponent()));
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
      boost::intmax_t power10 = digits_wanted - base10_exp - 1;
      //
      // If we calculate 5^power10 rather than 10^power10 we need to move
      // 2^power10 into /shift/
      //
      shift -= power10;
      cpp_int               i;
      int                   roundup   = 0; // 0=no rounding, 1=tie, 2=up
      static const unsigned limb_bits = sizeof(limb_type) * CHAR_BIT;
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
      boost::intmax_t max_bits = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + 32;
#else
      boost::intmax_t max_bits = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + ((cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count % limb_bits) ? (limb_bits - cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count % limb_bits) : 0) + limb_bits;
      if (power10)
         max_bits += (msb(boost::multiprecision::detail::abs(power10)) / 8) * limb_bits;
#endif
      do
      {
         boost::int64_t  error    = 0;
         boost::intmax_t calc_exp = 0;
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
               BOOST_ASSERT(power10 <= (boost::intmax_t)INT_MAX);
               i <<= -shift;
               if (power10)
                  i *= pow(cpp_int(5), static_cast<unsigned>(power10));
            }
            else if (power10 < 0)
            {
               cpp_int d;
               calc_exp = boost::multiprecision::cpp_bf_io_detail::restricted_pow(d, cpp_int(5), -power10, max_bits, error);
               shift += calc_exp;
               BOOST_ASSERT(shift < 0); // Must still be true!
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
                  shift = (boost::intmax_t)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - exponent() - 1 - power10;
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
                  shift = (boost::intmax_t)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - exponent() - 1 - power10;
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
                     shift = (boost::intmax_t)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - exponent() - 1 - power10;
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
               BOOST_ASSERT(-power10 < INT_MAX);
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
         boost::intmax_t digits_got = i ? static_cast<boost::intmax_t>(s.size()) : 0;
         if (digits_got != digits_wanted)
         {
            base10_exp += digits_got - digits_wanted;
            if (fixed)
               digits_wanted = digits_got; // strange but true.
            power10 = digits_wanted - base10_exp - 1;
            shift   = (boost::intmax_t)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - exponent() - 1 - power10;
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

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

} // namespace backends
}} // namespace boost::multiprecision

#endif

/* io.hpp
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
*/