//  Copyright (c) 2001-2020 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_REAL_UTILS_FEB_23_2007_0841PM)
#define BOOST_SPIRIT_KARMA_REAL_UTILS_FEB_23_2007_0841PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/limits.hpp>

#include <boost/spirit/home/support/char_class.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/detail/pow10.hpp>
#include <boost/spirit/home/karma/detail/generate_to.hpp>
#include <boost/spirit/home/karma/detail/string_generate.hpp>
#include <boost/spirit/home/karma/numeric/detail/numeric_utils.hpp>

namespace boost { namespace spirit { namespace karma 
{ 
    ///////////////////////////////////////////////////////////////////////////
    //
    //  The real_inserter template takes care of the floating point number to 
    //  string conversion. The Policies template parameter is used to allow
    //  customization of the formatting process
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct real_policies;

    template <typename T
      , typename Policies = real_policies<T>
      , typename CharEncoding = unused_type
      , typename Tag = unused_type>
    struct real_inserter
    {
        template <typename OutputIterator, typename U>
        static bool
        call (OutputIterator& sink, U n, Policies const& p = Policies())
        {
            if (traits::test_nan(n)) {
                return p.template nan<CharEncoding, Tag>(
                    sink, n, p.force_sign(n));
            }
            else if (traits::test_infinite(n)) {
                return p.template inf<CharEncoding, Tag>(
                    sink, n, p.force_sign(n));
            }
            return p.template call<real_inserter>(sink, n, p);
        }

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)  
# pragma warning(push)
# pragma warning(disable: 4100)   // 'p': unreferenced formal parameter  
# pragma warning(disable: 4127)   // conditional expression is constant
# pragma warning(disable: 4267)   // conversion from 'size_t' to 'unsigned int', possible loss of data
#endif 
        ///////////////////////////////////////////////////////////////////////
        //  This is the workhorse behind the real generator
        ///////////////////////////////////////////////////////////////////////
        template <typename OutputIterator, typename U>
        static bool
        call_n (OutputIterator& sink, U n, Policies const& p)
        {
        // prepare sign and get output format
            bool force_sign = p.force_sign(n);
            bool sign_val = false;
            int flags = p.floatfield(n);
            if (traits::test_negative(n)) 
            {
                n = -n;
                sign_val = true;
            }

        // The scientific representation requires the normalization of the 
        // value to convert.

            // get correct precision for generated number
            unsigned precision = p.precision(n);

            // allow for ADL to find the correct overloads for log10 et.al.
            using namespace std;

            bool precexp_offset = false;
            U dim = 0;
            if (0 == (Policies::fmtflags::fixed & flags) && !traits::test_zero(n))
            {
                dim = log10(n);
                if (dim > 0)
                    n /= spirit::traits::pow10<U>(traits::truncate_to_long::call(dim));
                else if (n < 1.) {
                    long exp = traits::truncate_to_long::call(-dim);

                    dim = static_cast<U>(-exp);

                    // detect and handle denormalized numbers to prevent overflow in pow10
                    if (exp > std::numeric_limits<U>::max_exponent10)
                    {
                        n *= spirit::traits::pow10<U>(std::numeric_limits<U>::max_exponent10);
                        n *= spirit::traits::pow10<U>(exp - std::numeric_limits<U>::max_exponent10);
                    }
                    else
                        n *= spirit::traits::pow10<U>(exp);

                    if (n < 1.)
                    {
                        n *= 10.;
                        --dim;
                        precexp_offset = true;
                    }
                }
            }

        // prepare numbers (sign, integer and fraction part)
            U integer_part;
            U precexp = spirit::traits::pow10<U>(precision);
            U fractional_part = modf(n, &integer_part);

            if (precexp_offset)
            {
                fractional_part =
                    floor((fractional_part * precexp + U(0.5)) * U(10.)) / U(10.);
            }
            else
            {
                fractional_part = floor(fractional_part * precexp + U(0.5));
            }

            if (fractional_part >= precexp)
            {
                fractional_part = floor(fractional_part - precexp);
                integer_part += 1;    // handle rounding overflow
                if (integer_part >= 10. && 0 == (Policies::fmtflags::fixed & flags))
                {
                    integer_part /= 10.;
                    ++dim;
                }
            }

        // if trailing zeros are to be omitted, normalize the precision and``
        // fractional part
            U long_int_part = floor(integer_part);
            U long_frac_part = fractional_part;
            unsigned prec = precision;
            if (!p.trailing_zeros(n))
            {
                U frac_part_floor = long_frac_part;
                if (0 != long_frac_part) {
                    // remove the trailing zeros
                    while (0 != prec && 
                           0 == traits::remainder<10>::call(long_frac_part)) 
                    {
                        long_frac_part = traits::divide<10>::call(long_frac_part);
                        --prec;
                    }
                }
                else {
                    // if the fractional part is zero, we don't need to output 
                    // any additional digits
                    prec = 0;
                }

                if (precision != prec)
                {
                    long_frac_part = frac_part_floor / 
                        spirit::traits::pow10<U>(precision-prec);
                }
            }

        // call the actual generating functions to output the different parts
            if ((force_sign || sign_val) &&
                traits::test_zero(long_int_part) &&
                traits::test_zero(long_frac_part))
            {
                sign_val = false;     // result is zero, no sign please
                force_sign = false;
            }

        // generate integer part
            bool r = p.integer_part(sink, long_int_part, sign_val, force_sign);

        // generate decimal point
            r = r && p.dot(sink, long_frac_part, precision);

        // generate fractional part with the desired precision
            r = r && p.fraction_part(sink, long_frac_part, prec, precision);

            if (r && 0 == (Policies::fmtflags::fixed & flags)) {
                return p.template exponent<CharEncoding, Tag>(sink, 
                    traits::truncate_to_long::call(dim));
            }
            return r;
        }

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
# pragma warning(pop)
#endif 

    };
}}}

#endif


/* real_utils.hpp
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
*/