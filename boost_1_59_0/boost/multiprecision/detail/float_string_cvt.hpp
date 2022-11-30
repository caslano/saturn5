///////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//
// Generic routines for converting floating point values to and from decimal strings.
// Note that these use "naive" algorithms which result in rounding error - so they
// do not round trip to and from the string representation (but should only be out
// in the last bit).
//

#ifndef BOOST_MP_FLOAT_STRING_CVT_HPP
#define BOOST_MP_FLOAT_STRING_CVT_HPP

#include <string>
#include <cctype>
#include <boost/multiprecision/detail/no_exceptions_support.hpp>
#include <boost/multiprecision/detail/assert.hpp>

namespace boost { namespace multiprecision { namespace detail {

template <class I>
inline void round_string_up_at(std::string& s, std::ptrdiff_t pos, I& expon)
{
   //
   // Rounds up a string representation of a number at pos:
   //
   if (pos < 0)
   {
      s.insert(static_cast<std::string::size_type>(0), 1, '1');
      s.erase(s.size() - 1);
      ++expon;
   }
   else if (s[pos] == '9')
   {
      s[pos] = '0';
      round_string_up_at(s, pos - 1, expon);
   }
   else
   {
      if ((pos == 0) && (s[pos] == '0') && (s.size() == 1))
         ++expon;
      ++s[pos];
   }
}

template <class Backend>
std::string convert_to_string(Backend b, std::streamsize digits, std::ios_base::fmtflags f)
{
   using default_ops::eval_convert_to;
   using default_ops::eval_divide;
   using default_ops::eval_floor;
   using default_ops::eval_fpclassify;
   using default_ops::eval_log10;
   using default_ops::eval_multiply;
   using default_ops::eval_pow;
   using default_ops::eval_subtract;

   using ui_type = typename std::tuple_element<0, typename Backend::unsigned_types>::type;
   using exponent_type = typename Backend::exponent_type                            ;

   std::string     result;
   bool            iszero     = false;
   bool            isneg      = false;
   exponent_type   expon      = 0;
   std::streamsize org_digits = digits;
   BOOST_MP_ASSERT(digits > 0);

   int fpt = eval_fpclassify(b);

   if (fpt == static_cast<int>(FP_ZERO))
   {
      result = "0";
      iszero = true;
   }
   else if (fpt == static_cast<int>(FP_INFINITE))
   {
      if (b.compare(ui_type(0)) < 0)
         return "-inf";
      else
         return ((f & std::ios_base::showpos) == std::ios_base::showpos) ? "+inf" : "inf";
   }
   else if (fpt == static_cast<int>(FP_NAN))
   {
      return "nan";
   }
   else
   {
      //
      // Start by figuring out the exponent:
      //
      isneg = b.compare(ui_type(0)) < 0;
      if (isneg)
         b.negate();
      Backend t;
      Backend ten;
      ten = ui_type(10);

      eval_log10(t, b);
      eval_floor(t, t);
      eval_convert_to(&expon, t);
      if (-expon > std::numeric_limits<number<Backend> >::max_exponent10 - 3)
      {
         int     e = -expon / 2;
         Backend t2;
         eval_pow(t2, ten, e);
         eval_multiply(t, t2, b);
         eval_multiply(t, t2);
         if (expon & 1)
            eval_multiply(t, ten);
      }
      else
      {
         eval_pow(t, ten, -expon);
         eval_multiply(t, b);
      }
      //
      // Make sure we're between [1,10) and adjust if not:
      //
      if (t.compare(ui_type(1)) < 0)
      {
         eval_multiply(t, ui_type(10));
         --expon;
      }
      else if (t.compare(ui_type(10)) >= 0)
      {
         eval_divide(t, ui_type(10));
         ++expon;
      }
      Backend digit;
      ui_type cdigit;
      //
      // Adjust the number of digits required based on formatting options:
      //
      if (((f & std::ios_base::fixed) == std::ios_base::fixed) && (expon != -1))
         digits += expon + 1;
      if ((f & std::ios_base::scientific) == std::ios_base::scientific)
         ++digits;
      //
      // Extract the digits one at a time:
      //
      for (unsigned i = 0; i < digits; ++i)
      {
         eval_floor(digit, t);
         eval_convert_to(&cdigit, digit);
         result += static_cast<char>('0' + cdigit);
         eval_subtract(t, digit);
         eval_multiply(t, ten);
      }
      //
      // Possibly round result:
      //
      if (digits >= 0)
      {
         eval_floor(digit, t);
         eval_convert_to(&cdigit, digit);
         eval_subtract(t, digit);
         if ((cdigit == 5) && (t.compare(ui_type(0)) == 0))
         {
            // Bankers rounding:
            if ((*result.rbegin() - '0') & 1)
            {
               round_string_up_at(result, result.size() - 1, expon);
            }
         }
         else if (cdigit >= 5)
         {
            round_string_up_at(result, result.size() - 1, expon);
         }
      }
      eval_floor(t, b);
      if ((t.compare(b) == 0) && (static_cast<std::size_t>(expon + 1) < result.size()))
      {
         // Input is an integer, sometimes we get a result which is not an integer here as a result of printing too
         // many digits, so lets round if required:
         round_string_up_at(result, expon + 1, expon);
         result.erase(expon + 1);
      }
   }
   while ((static_cast<std::streamsize>(result.size()) > digits) && (result.size() != 0U))
   {
      // We may get here as a result of rounding...
      if (result.size() > 1)
         result.erase(result.size() - 1);
      else
      {
         if (expon > 0)
            --expon; // so we put less padding in the result.
         else
            ++expon;
         ++digits;
      }
   }
   BOOST_MP_ASSERT(org_digits >= 0);
   if (isneg)
      result.insert(static_cast<std::string::size_type>(0), 1, '-');
   format_float_string(result, expon, org_digits, f, iszero);

   return result;
}

template <class Backend>
void convert_from_string(Backend& b, const char* p)
{
   using default_ops::eval_add;
   using default_ops::eval_divide;
   using default_ops::eval_multiply;
   using default_ops::eval_pow;

   using ui_type = typename std::tuple_element<0, typename Backend::unsigned_types>::type;
   b = ui_type(0);
   if (!p || (*p == 0))
      return;

   bool                                                  is_neg       = false;
   bool                                                  is_neg_expon = false;
   constexpr const ui_type                               ten          = ui_type(10);
   typename Backend::exponent_type                       expon        = 0;
   int                                                   digits_seen  = 0;
   using limits = std::numeric_limits<number<Backend, et_off> >;
   constexpr const int                                   max_digits = limits::is_specialized ? limits::max_digits10 + 1 : INT_MAX;

   if (*p == '+')
      ++p;
   else if (*p == '-')
   {
      is_neg = true;
      ++p;
   }
   if ((std::strcmp(p, "nan") == 0) || (std::strcmp(p, "NaN") == 0) || (std::strcmp(p, "NAN") == 0))
   {
      eval_divide(b, ui_type(0));
      if (is_neg)
         b.negate();
      return;
   }
   if ((std::strcmp(p, "inf") == 0) || (std::strcmp(p, "Inf") == 0) || (std::strcmp(p, "INF") == 0))
   {
      b = ui_type(1);
      eval_divide(b, ui_type(0));
      if (is_neg)
         b.negate();
      return;
   }
   //
   // Grab all the leading digits before the decimal point:
   //
   while (std::isdigit(*p))
   {
      eval_multiply(b, ten);
      eval_add(b, ui_type(*p - '0'));
      ++p;
      ++digits_seen;
   }
   if (*p == '.')
   {
      //
      // Grab everything after the point, stop when we've seen
      // enough digits, even if there are actually more available:
      //
      ++p;
      while (std::isdigit(*p))
      {
         eval_multiply(b, ten);
         eval_add(b, ui_type(*p - '0'));
         ++p;
         --expon;
         if (++digits_seen > max_digits)
            break;
      }
      while (std::isdigit(*p))
         ++p;
   }
   //
   // Parse the exponent:
   //
   if ((*p == 'e') || (*p == 'E'))
   {
      ++p;
      if (*p == '+')
         ++p;
      else if (*p == '-')
      {
         is_neg_expon = true;
         ++p;
      }
      typename Backend::exponent_type e2 = 0;
      while (std::isdigit(*p))
      {
         e2 *= 10;
         e2 += (*p - '0');
         ++p;
      }
      if (is_neg_expon)
         e2 = -e2;
      expon += e2;
   }
   if (expon)
   {
      // Scale by 10^expon, note that 10^expon can be
      // outside the range of our number type, even though the
      // result is within range, if that looks likely, then split
      // the calculation in two:
      Backend t;
      t = ten;
      if (expon > limits::min_exponent10 + 2)
      {
         eval_pow(t, t, expon);
         eval_multiply(b, t);
      }
      else
      {
         eval_pow(t, t, expon + digits_seen + 1);
         eval_multiply(b, t);
         t = ten;
         eval_pow(t, t, -digits_seen - 1);
         eval_multiply(b, t);
      }
   }
   if (is_neg)
      b.negate();
   if (*p)
   {
      // Unexpected input in string:
      BOOST_MP_THROW_EXCEPTION(std::runtime_error("Unexpected characters in string being interpreted as a float128."));
   }
}

}}} // namespace boost::multiprecision::detail

#endif

/* float_string_cvt.hpp
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
*/