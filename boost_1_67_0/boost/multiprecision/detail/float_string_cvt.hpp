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

#include <cctype>

namespace boost { namespace multiprecision { namespace detail {

template <class I>
inline void round_string_up_at(std::string& s, int pos, I& expon)
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

   typedef typename mpl::front<typename Backend::unsigned_types>::type ui_type;
   typedef typename Backend::exponent_type                             exponent_type;

   std::string     result;
   bool            iszero     = false;
   bool            isneg      = false;
   exponent_type   expon      = 0;
   std::streamsize org_digits = digits;
   BOOST_ASSERT(digits > 0);

   int fpt = eval_fpclassify(b);

   if (fpt == (int)FP_ZERO)
   {
      result = "0";
      iszero = true;
   }
   else if (fpt == (int)FP_INFINITE)
   {
      if (b.compare(ui_type(0)) < 0)
         return "-inf";
      else
         return ((f & std::ios_base::showpos) == std::ios_base::showpos) ? "+inf" : "inf";
   }
   else if (fpt == (int)FP_NAN)
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
   }
   while ((result.size() > digits) && result.size())
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
   BOOST_ASSERT(org_digits >= 0);
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

   typedef typename mpl::front<typename Backend::unsigned_types>::type ui_type;
   b = ui_type(0);
   if (!p || (*p == 0))
      return;

   bool                                                  is_neg       = false;
   bool                                                  is_neg_expon = false;
   static const ui_type                                  ten          = ui_type(10);
   typename Backend::exponent_type                       expon        = 0;
   int                                                   digits_seen  = 0;
   typedef std::numeric_limits<number<Backend, et_off> > limits;
   static const int                                      max_digits = limits::is_specialized ? limits::max_digits10 + 1 : INT_MAX;

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
      BOOST_THROW_EXCEPTION(std::runtime_error("Unexpected characters in string being interpreted as a float128."));
   }
}

}}} // namespace boost::multiprecision::detail

#endif

/* float_string_cvt.hpp
wWvKX+vxhQdBa/9W+gWJlVhLHBCzP3hcPw79dlOOfrsywHxr/Ngk05hAj1B+cVtHjluFtmvgfvgOzSTHlHqjrB5XhyYmF+Xn1Ykadi21exGa3QZ/Rr7x2oST13BsPDarRfzLCtKJNToQFD1oZO35WfhMJlyTPn++ftX1SnvB1JwrmFrs8ZU6kzhMkqON+mSnDN63BQc+kOUTDqrP1/dJsOgiEo2UABAuISGT1ijJ94YrMtZNK5Xppw+nynpKwi35Z3LpHTzVRUmiStmbpFL3HRp8xaoT9WN/V00fbTCpP0BnBf4hD/3H6BEknqTZ5V+IcdZGPbIX5AYgabMKJnsWfRH3mRVdRGQlbGvYMOKZokGZfsZvcRi9GDFKUl3YirRBlxiB5gEtqbNFAXKRji0a3J7OD+6onwTumI+X6rj3mepY95piupu/v97J863KHipy99ZknK9P7qhPiPVK42aLDwlmg3WsfvQrhHAs6Jwf3tn3m1c0tTRc2byAvPCMf/eZNhM55vOztkEPinHzsBkX/Ucke0lCMO5W/hHsYnS9UejRQ1RaA9yFRV5pcBjioJHOfd2a8nwBu+lNre//aunBdsMPszDLZhd4FeXluZS9o7of5wACveSjGYWHfXcHdAujvGzsl3XUmqeCLiuL0vXO96NfvajTrBM9syhTQzP8L/esbs50zUesUu66/uUlaNG/td1qMW+TGQl1t759GD8bvtMBplIowZDB8bu2XWXrGudW3Wnf1MEDJg4vLwnQSxtuQNZZZgewKsQR8Psqp8uWCt99GITuGyUL5u/ljIZlohO4PtUlpMfsQabE33Op2OH+lh3f1sKWxsSMvR1fJRDq6A4WjU3l1RKzK/NYVM2fGnQ0db/BpdTxSU7nVjj5xxY87tJemI1b4dQezOhfcQ7lH1vIGcHYOX/GDygFeTBy8RJ3M3Rkxg8tmmBe5nKST9Mzv2qlc8RE9wTtC9WxKUarrPVAY+noZh7HpbERjAXk6OkVlcvfgwZU/mMDjwYiFWeJxnxCprvZ9B9bOrofz+3UL9wSSNApE7qM9a/9HMby3xfIb1V5D7al/8e6+VPi2uv/X+cnr4P99973umFCFZYlifwin+bRwtslAwcYbOlCSCjqX+EkgTBSRmX0Rbw//5KlVtKlxGq9XFT5WyaMwX9dAzEt2D8BLHV8WOIEWvE68BvQlJRkVH7clGWo789rR0f3wqVZ4cHHH+mWrWZ5z+BH8XXr9P1Y69l2kIyQkfPDIaDYtpk2XUlGXOZ2B5zGibmdoVm1H/h8YmBqW9pS+fS10dzsmYzt7LZmWpbOpYAjVgfRA4qV7q+Pll84sepc7eVTSbh4L9baddV7LeMRV0DZteTNWLJUfpkCs3FrIzxKG7Rhtxn9ueKtJeHzElB7Uc+rYwf6eqmtNHKcUvUCuIQFwkNeHYF8MJUObGEg7DhEX14RA+IJO1ngR1G99yvHtE9Png5kp9hRAwreLs82EqC3u7scAgOS1u/L0MeigmAPx58x4+2Okbx8B9Wp6s18/3CWUYMCmaM0vrrPHAZ7oCxUjJC/x0630JS9bN58FuIRbsWf7s+diZhyrwagYVBmqTZwl3pJgqiril+dsQldzsqxSW7jeH66WZZ1lJZLkp8O5WBhXnMU4XyqE97Is4AXcwvhhK7Z61voslOHc3wR0jwIXge2c/VHcT1ceiZCPNxfEykdMFTnqZT/maZfb2VG/fCZgIYTuhcWnGmfDVV7bdm7uC0Es/nyfbOcc9dxfNd4BbR1c4nlOhh9k4b2e1JT64maWWHpTN+wkA7dQkgVj6RhfVDCgF5VPnZ0arluFMtkoam63qC4DMkfZCsaC7QPnOtHB0xNTfJWKdNnfZaV24f5LVMzknQtFJkb0YxGVpHZocHUdxV5B+EAMjDNRr7DfSQE57BIR1QmuFwZxk3eSIbRGMA+v51AxYQ/SfZREaPhQLiIW274O+7V06SVTU+e2m3ued7609GQ07+8qHFUHWcAAiz909fxwq1F2m/BSVrgp7HYoC0xffOEY/4b8UyCGvScw8bTLgMtRKcBi1NKW83j6+rMYW34D/bBk7RFtQUFjsPBT5Bb2XAdbcmCtXJ+MT6sb+3xCT38lvLGi4d6ZB/BRupRwXxZHcalXmJR3FENruxj/GcrGNRfMTQ51RafnZQiM9CMWBQXZghLCDekWYmG0kosNt/ksK4vdn3JygvmZJX7ZgMmE12WqBVLChF7n1uyfKufK2j766E8wsykn//NCVWiP1H8lyAAbGvqEAxZGv3fjIlBmsAq6X4QCS8ADc/g/KRloVvznWPmzctWyZjNgCSgFAvt6vPABX7a/SnH+TZPe0Knbtj27Sw8ourcQwTpgZPGQUucNrRaOUv9fdvDsKEYPrFwStmlNkAiAnYcOtguzx6dPrboPx9ZBTTLdPyphIgpMDkqnfHl9l+IP1bjqgSCEUwV3gcpWzQEqcMeAldBTQcrMfJ2IjWSf3T9OESAXmnzxSUtyVnsy27J3gQIXQg5AtAKLiMVDMCXH0RKpS/ZBNe2b931Oodtj4wDk7XECm2nGFq16t4GKtyghgVn5J5tKUf2IvBVYkVEjB4lu0RB/Ozdth2vYDk9iDfWmwq/DihMAUYCugmLkgz61t1f7LsVeOy+vkwS3xj+qwIa3/THTz53BdTJRfbBr2IMth0l86M4vB7SEjCsG22/SauqccYnRtFymijyixN8vF6b4LTaeYYQ1LVnPp6RVIIGY1s6eGH16Samnj68tPmuJYCOOf2RYqp4uffgSwNOHp34OJOvUpr8hHIiYs+FETSCwIM+H/WJyv736eBg2KmkyWWBoepjbvNChtmbF2o7yaid2fUm7QctuRZlmTBXOp6yHu+dQ44a9bxOcrFy47mywo44njAghxxIGODks7ukAlDWqOmQopCz3Nn6Nyn86ddoXmjDxKLMIOU+by+SOxurUTk/VipXK9b0g7FoGG1Ges5JrAcmNwl3rIoU6y4klQPhX7RpxglhytyW59lASBMwQB5oogpNI+tkRhakxxKiWO+e472MZaGNmtHdVqbFy1DQA+rXo19PAXjUxR1W1ij84qf4s3WSEJ5GrBeT7WsTXOVKrS4UCZO8MI6IuVlDxIVRlB8RI85/AdX9LGdVAAB9Xnf+csawhZugayZvYkGErMSNxyiq0z4kQKKqsVKCZR3rJh66EHxb2C6FhTxILPMWnKUalZ35zK/veGIqZIvCNLQ4436Z0VBPp9qbPTGwUKjgI/wuHjFOKRk6h78s/oPPVyEBTgP6KNj8OUUdr5a65OQCBE/2MqFUu5EtlGx5glj2NdE3HlkDDvzq8rvds0Sa9l+98s8BGiNYOQPixMUGtaw9e4QqMXNB+pOfY1ljFMUyULPcdq4MDzAjTLfYFqfgqSqRGOEUK7WiiSS3RHxLryMYlSwgxgkoDH6Hu0Ttb7uXqo0flx1SBWnOyHP3jysa9jIMi1ltg8kDlMae/gPhyNcj1wPrtjtHN4dF+ynycuxpcMcf+6bXtz94z02Jx3P5AYehov3oiZd2uwW5mPH3Y+xF6b6XE92we1XBqih3uPehkTEFSaIBXInqCtZBCTMcUvJjRAI+cSorbjIjq6N3cfLkrlj2OrSU82mJwhgk7SDEzGNAunagR5bSKnpUbir2R5QoQKRFcIwJyDJmkuozYNtNFGlHpEzB4xM22G5oYycKY9dnS4vEzYroigD6ruzSatIePyUHl+QSLlqdLCKaEmOlYL3Zs7RFpB08XSTA6Ev0LQtnD29HTTlEQ4xgTQR0LQECgoAKZJL2UlUQdxzabtqqvbMTfjuHp1ssP4dvZ1tfAEjut0emCyrIA45OIPRv8/p1VWcXtY4rc31VIVi+9nE2tLH1PS2FsThcdY2+Ix17hd4NlpPnFPFr/7j/vj27mFsZX7+FXxl6C8tKTzc/4jy/N19O33ma0BtH9ySOVDmAYNnJ+gZlTYJbQhaGVuifJ+bYql/LzYivtgA9C4GyAZ8kVmVwByfgA1c+axeqn3oBTol8/NgPi7LWc5ZE7nuqtrHdRSwNVTIqKj3lEryKa/c3bXELL3rnPgzzTrdmZ0+fgPV3opbVMsohwCyfn3aBNdsGw17cmfAkWteWgK49VKdY16eBd4049f3sx3hvk2RX5uTq4e5l8qS+eKdrts8X7ncj4m4SfeBDx9yS/ZQEzD+q91z0puiYFEdmGGrDq3PT/YC719NVNET6iq7jOS9R6dNAtMwhpjMIuy3K9zvfeLtTfwDSP4JOG3Pabij5FPjjI78zdfRB/XazPhzjMW7CnzANnKvvr9b4Y66ibImnP3LyNmEjRVP1kkETn2PKouOWAPFPQWQjKQQWzieZERGWwrZJz8hh/BmoS+XcLSuBreR7XfKBY9zBIRWdKlDxV9hMkdcQeR4Gw0Oi4txMYVyg5LA3Q7pn4GjIbGP00/TGbHeKCnosPyGthioCNpylrFQWOos9d3ggbYbpSnxXauybVAdrwZ+uWj3pMfPorhPydfXQQ7wh0NaIGU9c16ZiXWG6svRhqy7YhF9Y0vHRafTi8+Eq+yu7IDszWJpVZuiJHLsVBXDRKvOxWtwliq4NsdYuqloU1XbSsxDkkL1v0CQUAWzRd20hL2WA1VvzHznwdnlVAlTn34DEwja+STmkTQGvbnVEA480yu2suT70A/UjqKnE88uemAeqpzOnpfRSEaLq7Ckuagh3gFZpdWEir0B9T3UFxoFOZbvdpplOwxkvaA9xKkNVQIqWEbBTU+3OsPGgdsAMdMSwFJGTypAz3Wxh2jIsa9AF72rTBDrpRt/XQOJS1/MSzrBqG5MDXdXdY027+2DRuEo+qVZfOsqEppijhY8RQpw881o4c5+MgFKa1tl9ovGJtrG7dqtiYKv6L0P6P/Tjvcehgxu6D7uI2en62yk7k1l1p0wrNHKc/FR5cj/ki3yTd+5gNhBFHUeK3oSM/gnzpC5HufqOsgTpF+RADZC3FcCjI+zbIdJpDM5wI2vfg5V12e/SxQZ18MqIkboIWJcM5TbKpRZQ77big+dEOymTrLitlaaRNi2IftFOwBTXIP5xmqx86m0MA7S4GVf1jMN6Gd03u6HqDHJzXh8IEZiKDzCTrxCelijszA+mG54QFJwsPgvY4dyR1cpCfC8GhJmwhmnwYH5AZ80oKEyhdOOOpquUWRjboKVw0gy1IZSjW0CU7FdysX3l1E4Fmpnt9sAfoTswaKDHXhtwpXsBx+SjVPBuRgSPU7uAMIHZLwu02bLm6Kr85K7BBZ1+9dru7XkhM//r2vStXY8lRKMP2esPgqVytlZvAsPZFaIU6Xv9MN7yEvVoS1WnunrG4+fthBSjucOPeV+2xMY5wuDf+ZZba7PoRHis0fF2gt2UXm6dm2mc0fnt/TxHYSFA1FeM6AA5kYI+uTSnODOHGNb83DM1aNz8o2LOq91s8/8724rckImiYnHo3RWfXDjSSWZ7gDElf4bJMWC7ees6csc1nf5PXqsV1ztOorv9Bq4eHP8gnzSHCb2BTSFi+neAo7c5nc2nzoDOYAroqfsEefG9sZuKLW2bF3/2OLhL0o8o1l1ESAnLbe9XtGQ9cljHfVn5hpRk5eEMaVHm/wWBLuwqLh+aYFfpVaeIq0cFb1SRVg6q07cUTdLgC8boEq79feMEtu576tHcz14evFEb4GtdIUgNUnnDezWTnhkY+5GQL5beKsNdeLBSDGOs+cVtro+8lziQpdxlDq2aHfv39cMD8Sftn5CUXfY3j8/3HA7/cyDs//7/Nf8E3yC8f/q2iW0omWggu3AoC4MiKQXzkup+juZlXMIxk2ysk0O1OWOIpB/RJDpo4mr7GREygZeER0z0zBvTOnI6fW4ldaxyk7hq7wGEFFSNITm9sK03ffTus9ZKNFQuneAvSYjpW73KD6018NYh6udkKO4qxsiBjeYT0s09OpYryrcmbVxaa7vzcoqUJTzp8pgsb2U3sbGdcZrgaZM20rO00+nKRxy9TfPjUxReQAKAIK4It6FVlqu4KrucF8ctEu5a3wXHgT9TXMiI9IiH3UUS8oiLhPYc4YKdIicUHK7bOc7PExnvYGQNEycMhP8BVXmwEEQB42RVkXhH+scQgBUaEohqVhJw+zgDTWXa/CjDxOkSK8G9cYb5aqXNi4jApprQgUSnismGY3nDPHEQcPpeIbDBAI3y8D5XctDDdOTzpSg52ZRvkXUGTt99H/jvYOMghHDSYvZjQuQQise82VtTh5UNy0GQhlZuCpbuX7zpq+sGA2+HmdBs5w9OIcKv3RyF75LjcySoYD200jVIHm112OBvkouQPMzSfNj0jOaHi5AjH00c1VElYdS08QTD2tq1pjubBjWdLnqzqdhCerHE8mFgJ3x+S9rW5BMsrurDrh6E0T7ldy/Kxm2P7T1/yMnMLCszYFdGfIJ+Ss5SapGbJMG2nI21KYiikQW4js96APwF4VPLg+isA30E5C6qdA5x2dzDbJyVLOKpSbm1u6Unvt9+gWb+Y/nRB3eCY017B+zLq9p79fwgevUIJaNPL42Cn1QP1hXqJczWi8LjXukMIybx/1t2Oqi3s7gvLxSYTus6+hlbWp8Z4bA/6aJqbrcNnjVRXVWZSRwrebO/yoQ78ZTMmaHsjJwe056mCG4UB3Mh3vqYQ3/uOSUzQwWjw3DZLDs0zhLnj3Pl35hn58WCYnpJ4To3Ua5iq4wt9nOcT6T/BmRXErE76h+6VY8239u3fFUDQ03HdPLhS4upb7t1fviiezEgXrkoVS5Pw6j75Pzerogub7ohO3y40M4peAwy6RQ99HX5XUAUsduSXHlFWSQtXg4ZjOzHcfTwR9/vghcHGb99XcP0cZWn281/GnKks4i7R4zPAkbKCM5qzZ5CYcOVMhLk3Ge1w5VCJ8x5WYQbgPfkR4oQLJ/Ps/zdJpxKzih1Pe8dt9ANVeYOkY/x+0+hx+ss3w/XDhPJK4Gtjal7q99hy99lK9mfqyny0dCNc79WVFupnDm5sdI2Cwm4P2RvDyvj17ZUfZV5fTdlm/JN8eTdtjid1mk3eXV9OdhWXiXnlt1EoojulkVNfpRu6yZrqvKJIbnppuyWQx4KFxKt5QaVbhku8ubWl9W6Zyh3IffnsXGrqlZ9QOSh22zamdYj6zqIg8ETuwgtbmXM3IWIBWocQpbr6ERBjiuCrUUp7xTjg3Zgo/WtXbGd6lW4e3UIkQH3zPpKcGZnElUBYdFo3SJ+RFdK91rxskuPM6PTgAjvF36LdXth92lJeNzQkir3OAhnVhVLOZf6T/V1Lyf7Bz6U7zdd/gm/Rd7//gKe72egnP/9GTz/d38J3+cz+P8l+Sny7/b73psLjRoK2fIOJi4HyOPFYKVVs7zWRY6dNM67i4EWU1WmjcNwURVfNPyJzkgUrWghl/kgVxIw8cSV+KirPTYwpx1knKR99VnXPz8xk5k/YAXpd0nrrrNl8ifioCvDmtDEy1jbnibEdeuautaW1lzxjSpvhoPl6o6k/XBKaSHuMvqDLqInm1j3vibpFwZ5e4XmMi8Xa6c1Z+pcB3PnShgmksnNE8Fudik4q9Ca7F+B5hKfbRcVN7xNwUlyd+fQkK0lDPReg3phsVkNSgfZOXanSQ6qFLEdDF7BfPBCASQySeuS05jma3tZuEzg4I8JiuB6Q83V68tXi+IbhizDxxYe5I7Q2R0aPBDXKY0Y0BMx+btx6mT7nL9FfMZFisrvqbSnQCIQZqT/9PMPJATmE0DXC/XiDesU3f1EIDy44rEfETQur75bGRmtc9ei14kQKgAcSriG+xxkkr8DtQp5EI036wE6C083Eg5DIkXC6CyDkZKFxljKGlkRnBH1HxZ0TSTuUC3tq67MHB4ICDG7TjtVXwmASsI/ZyZoG7WChbt+Fdomr5jFfA6AfTaqtO0azxuvM6UHJoDjojRuIga0v8BgOkefZC5WWhSEdbp7hGHRYjGufjS2FTpQQ9+v4vfLmZdBez4UakTfKlCDtqBH7RsoNUDr9Q8sirSQ+7XZqWBxCAQHge3QDZ9P/pkTJTBZFPyjHGNiaeTry+O0Anpd1Vnx3idCqc7UqD/bkZM0xVQHcMlips44keUBfR2P2I2cBcGK40OxSVF/9oDulxQ93R9m4IzTxOtSgtv+K5KkBJCiPmQf+jWJSKx4rxe7RnHfTdpRPCYnwolpHHTgwieZN6oytv6oW6LMEt3GxJQ+shyr4tp8KgdGNZZ0fahtBOPJHcBNlPThGJYJsQ8Gtoh57hUrKyFaqiavUS7uAcmc2MQdXeZYbjj2o04f4/MRL8t2Iq96KrmuugbzqpKdfRqrtjz01wP1M72Qw2vj+mHkumvBbe6gSHRTEVcqBxC7Laym79o6MUrdFhM7OxtiiD71V7vemfVRmLjb/0MylYrOGX5PXXxVch/ye3oaVoJpkWc0m+PtO8eMMiQnofKs1BjLfaUMTMqfIzTZ04BCV/oGMDpiAqcjLOoxjRmWgSHELmj3IlySLrI2THnuFY9XP0j5ebVKXhrzE6W7hNCcRWcfyMaepR8bSWYp6FfSmcQvBcPhITelqdKnCJRYPDbX5XGqsLDqJ9+R60eIXBV5Ei0nZvGCU5AmXEARyZyzqK86fD+SgNEB+oq+hm/nykDc+S7/tCd60WAgFD2I6tYA6eJXLjU6njf8KtbEChNZfP2NuevltlI+DK0tVhMKnSTpdrjW94WloSjAwyVfF+VF/WKjpgSjfbTmRkCmEz1VditDH8fZtKnqzZne8/kb1asujf0OT4lqwSIb+iW1MxM/qDI+f7AurdVdk3ghNz7DsfPE2Q8tH09vd+jT0Qy2E4fSQJuUwIRXQaz0Tcbs5MGa+B28LeTjllkkym9XEm+w9a8wl1mNq8tDw8bjJ2ZImgUhlJF0NHRNCrK+NGOTqeWXvBjARxFYFY4Cz7JYF2ANOpmpBlWU+gQe3oFTggaEBsVpKGdDAZjMs1tKl2jCsBjHdFCFs248Oc2BpfCHBxPjhbRYN5jCfMaRdEJV85giEMFzBfM2jY/FSTAQAmEjwfRIvJBcpCXqnE4jBepGiZZLUkF6Vxo7mMam8QrKO2eplSzAo0y2IXbRl6pYhHWjqHlcqCqAGHRwb+vXCuZIvRJWWyTvA2VHxxRWLjEksDo=
*/