//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_REAL_POLICIES_MAR_02_2007_0936AM)
#define BOOST_SPIRIT_KARMA_REAL_POLICIES_MAR_02_2007_0936AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config/no_tr1/cmath.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/spirit/home/support/char_class.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/char.hpp>
#include <boost/spirit/home/karma/numeric/int.hpp>
#include <boost/spirit/home/karma/numeric/detail/real_utils.hpp>

#include <boost/mpl/bool.hpp>

namespace boost { namespace spirit { namespace karma 
{
    ///////////////////////////////////////////////////////////////////////////
    //
    //  real_policies, if you need special handling of your floating
    //  point numbers, just overload this policy class and use it as a template
    //  parameter to the karma::real_generator floating point specifier:
    //
    //      template <typename T>
    //      struct scientific_policy : karma::real_policies<T>
    //      {
    //          //  we want the numbers always to be in scientific format
    //          static int floatfield(T n) { return fmtflags::scientific; }
    //      };
    //
    //      typedef 
    //          karma::real_generator<double, scientific_policy<double> > 
    //      science_type;
    //
    //      karma::generate(sink, science_type(), 1.0); // will output: 1.0e00
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct real_policies
    {
        ///////////////////////////////////////////////////////////////////////
        // Expose the data type the generator is targeted at
        ///////////////////////////////////////////////////////////////////////
        typedef T value_type;

        ///////////////////////////////////////////////////////////////////////
        //  By default the policy doesn't require any special iterator 
        //  functionality. The floating point generator exposes its properties
        //  from here, so this needs to be updated in case other properties
        //  need to be implemented.
        ///////////////////////////////////////////////////////////////////////
        typedef mpl::int_<generator_properties::no_properties> properties;

        ///////////////////////////////////////////////////////////////////////
        //  Specifies, which representation type to use during output 
        //  generation.
        ///////////////////////////////////////////////////////////////////////
        struct fmtflags
        {
            enum {
                scientific = 0,   // Generate floating-point values in scientific 
                                  // format (with an exponent field).
                fixed = 1         // Generate floating-point values in fixed-point 
                                  // format (with no exponent field). 
            };
        };

        ///////////////////////////////////////////////////////////////////////
        //  This is the main function used to generate the output for a 
        //  floating point number. It is called by the real generator in order 
        //  to perform the conversion. In theory all of the work can be 
        //  implemented here, but it is the easiest to use existing 
        //  functionality provided by the type specified by the template 
        //  parameter `Inserter`. 
        //
        //      sink: the output iterator to use for generation
        //      n:    the floating point number to convert 
        //      p:    the instance of the policy type used to instantiate this 
        //            floating point generator.
        ///////////////////////////////////////////////////////////////////////
        template <typename Inserter, typename OutputIterator, typename Policies>
        static bool
        call (OutputIterator& sink, T n, Policies const& p)
        {
            return Inserter::call_n(sink, n, p);
        }

        ///////////////////////////////////////////////////////////////////////
        //  The default behavior is to not to require generating a sign. If 
        //  'force_sign()' returns true, then all generated numbers will 
        //  have a sign ('+' or '-', zeros will have a space instead of a sign)
        // 
        //      n     The floating point number to output. This can be used to 
        //            adjust the required behavior depending on the value of 
        //            this number.
        ///////////////////////////////////////////////////////////////////////
        static bool force_sign(T)
        {
            return false;
        }

        ///////////////////////////////////////////////////////////////////////
        //  Return whether trailing zero digits have to be emitted in the 
        //  fractional part of the output. If set, this flag instructs the 
        //  floating point generator to emit trailing zeros up to the required 
        //  precision digits (as returned by the precision() function).
        // 
        //      n     The floating point number to output. This can be used to 
        //            adjust the required behavior depending on the value of 
        //            this number.
        ///////////////////////////////////////////////////////////////////////
        static bool trailing_zeros(T)
        {
            // the default behavior is not to generate trailing zeros
            return false;
        }

        ///////////////////////////////////////////////////////////////////////
        //  Decide, which representation type to use in the generated output.
        //
        //  By default all numbers having an absolute value of zero or in 
        //  between 0.001 and 100000 will be generated using the fixed format, 
        //  all others will be generated using the scientific representation.
        //
        //  The function trailing_zeros() can be used to force the output of 
        //  trailing zeros in the fractional part up to the number of digits 
        //  returned by the precision() member function. The default is not to 
        //  generate the trailing zeros.
        //  
        //      n     The floating point number to output. This can be used to 
        //            adjust the formatting flags depending on the value of 
        //            this number.
        ///////////////////////////////////////////////////////////////////////
        static int floatfield(T n)
        {
            if (traits::test_zero(n))
                return fmtflags::fixed;

            T abs_n = traits::get_absolute_value(n);
            return (abs_n >= 1e5 || abs_n < 1e-3) 
              ? fmtflags::scientific : fmtflags::fixed;
        }

        ///////////////////////////////////////////////////////////////////////
        //  Return the maximum number of decimal digits to generate in the 
        //  fractional part of the output.
        //  
        //      n     The floating point number to output. This can be used to 
        //            adjust the required precision depending on the value of 
        //            this number. If the trailing zeros flag is specified the
        //            fractional part of the output will be 'filled' with 
        //            zeros, if appropriate
        //
        //  Note:     If the trailing_zeros flag is not in effect additional
        //            comments apply. See the comment for the fraction_part()
        //            function below.
        ///////////////////////////////////////////////////////////////////////
        static unsigned precision(T)
        {
            // by default, generate max. 3 fractional digits
            return 3;
        }

        ///////////////////////////////////////////////////////////////////////
        //  Generate the integer part of the number.
        //
        //      sink       The output iterator to use for generation
        //      n          The absolute value of the integer part of the floating
        //                 point number to convert (always non-negative).
        //      sign       The sign of the overall floating point number to
        //                 convert.
        //      force_sign Whether a sign has to be generated even for
        //                 non-negative numbers. Note, that force_sign will be
        //                 set to false for zero floating point values.
        ///////////////////////////////////////////////////////////////////////
        template <typename OutputIterator>
        static bool integer_part (OutputIterator& sink, T n, bool sign
          , bool force_sign)
        {
            return sign_inserter::call(
                      sink, traits::test_zero(n), sign, force_sign, force_sign) &&
                   int_inserter<10>::call(sink, n);
        }

        ///////////////////////////////////////////////////////////////////////
        //  Generate the decimal point.
        //
        //      sink  The output iterator to use for generation
        //      n     The fractional part of the floating point number to 
        //            convert. Note that this number is scaled such, that 
        //            it represents the number of units which correspond
        //            to the value returned from the precision() function 
        //            earlier. I.e. a fractional part of 0.01234 is
        //            represented as 1234 when the 'Precision' is 5.
        //      precision   The number of digits to emit as returned by the 
        //                  function 'precision()' above
        //
        //            This is given to allow to decide, whether a decimal point
        //            has to be generated at all.
        //
        //  Note:     If the trailing_zeros flag is not in effect additional
        //            comments apply. See the comment for the fraction_part()
        //            function below.
        ///////////////////////////////////////////////////////////////////////
        template <typename OutputIterator>
        static bool dot (OutputIterator& sink, T /*n*/, unsigned /*precision*/)
        {
            return char_inserter<>::call(sink, '.');  // generate the dot by default 
        }

        ///////////////////////////////////////////////////////////////////////
        //  Generate the fractional part of the number.
        //
        //      sink  The output iterator to use for generation
        //      n     The fractional part of the floating point number to 
        //            convert. This number is scaled such, that it represents 
        //            the number of units which correspond to the 'Precision'. 
        //            I.e. a fractional part of 0.01234 is represented as 1234 
        //            when the 'precision_' parameter is 5.
        //      precision_  The corrected number of digits to emit (see note 
        //                  below)
        //      precision   The number of digits to emit as returned by the 
        //                  function 'precision()' above
        //
        //  Note: If trailing_zeros() does not return true the 'precision_' 
        //        parameter will have been corrected from the value the 
        //        precision() function returned earlier (defining the maximal 
        //        number of fractional digits) in the sense, that it takes into 
        //        account trailing zeros. I.e. a floating point number 0.0123 
        //        and a value of 5 returned from precision() will result in:
        //
        //        trailing_zeros is not specified:
        //            n           123
        //            precision_  4
        //
        //        trailing_zeros is specified:
        //            n           1230
        //            precision_  5
        //
        ///////////////////////////////////////////////////////////////////////
        template <typename OutputIterator>
        static bool fraction_part (OutputIterator& sink, T n
          , unsigned precision_, unsigned precision)
        {
            // allow for ADL to find the correct overload for floor and log10
            using namespace std;

            // The following is equivalent to:
            //    generate(sink, right_align(precision, '0')[ulong], n);
            // but it's spelled out to avoid inter-modular dependencies.

            typename remove_const<T>::type digits = 
                (traits::test_zero(n) ? 0 : floor(log10(n))) + 1;
            bool r = true;
            for (/**/; r && digits < precision_; digits = digits + 1)
                r = char_inserter<>::call(sink, '0');
            if (precision && r)
                r = int_inserter<10>::call(sink, n);
            return r;
        }

        ///////////////////////////////////////////////////////////////////////
        //  Generate the exponential part of the number (this is called only 
        //  if the floatfield() function returned the 'scientific' flag).
        //
        //      sink  The output iterator to use for generation
        //      n     The (signed) exponential part of the floating point 
        //            number to convert. 
        //
        //  The Tag template parameter is either of the type unused_type or
        //  describes the character class and conversion to be applied to any 
        //  output possibly influenced by either the lower[...] or upper[...] 
        //  directives.
        ///////////////////////////////////////////////////////////////////////
        template <typename CharEncoding, typename Tag, typename OutputIterator>
        static bool exponent (OutputIterator& sink, long n)
        {
            long abs_n = traits::get_absolute_value(n);
            bool r = char_inserter<CharEncoding, Tag>::call(sink, 'e') &&
                     sign_inserter::call(sink, traits::test_zero(n)
                        , traits::test_negative(n), false);

            // the C99 Standard requires at least two digits in the exponent
            if (r && abs_n < 10)
                r = char_inserter<CharEncoding, Tag>::call(sink, '0');
            return r && int_inserter<10>::call(sink, abs_n);
        }

        ///////////////////////////////////////////////////////////////////////
        //  Print the textual representations for non-normal floats (NaN and 
        //  Inf)
        //
        //      sink       The output iterator to use for generation
        //      n          The (signed) floating point number to convert. 
        //      force_sign Whether a sign has to be generated even for 
        //                 non-negative numbers
        //
        //  The Tag template parameter is either of the type unused_type or
        //  describes the character class and conversion to be applied to any 
        //  output possibly influenced by either the lower[...] or upper[...] 
        //  directives.
        //
        //  Note: These functions get called only if fpclassify() returned 
        //        FP_INFINITY or FP_NAN.
        ///////////////////////////////////////////////////////////////////////
        template <typename CharEncoding, typename Tag, typename OutputIterator>
        static bool nan (OutputIterator& sink, T n, bool force_sign)
        {
            return sign_inserter::call(
                        sink, false, traits::test_negative(n), force_sign) &&
                   string_inserter<CharEncoding, Tag>::call(sink, "nan");
        }

        template <typename CharEncoding, typename Tag, typename OutputIterator>
        static bool inf (OutputIterator& sink, T n, bool force_sign)
        {
            return sign_inserter::call(
                        sink, false, traits::test_negative(n), force_sign) &&
                   string_inserter<CharEncoding, Tag>::call(sink, "inf");
        }
    };
}}}

#endif // defined(BOOST_SPIRIT_KARMA_REAL_POLICIES_MAR_02_2007_0936AM)

/* real_policies.hpp
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
*/