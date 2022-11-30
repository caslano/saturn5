//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_NUMERIC_UTILS_FEB_23_2007_0841PM)
#define BOOST_SPIRIT_KARMA_NUMERIC_UTILS_FEB_23_2007_0841PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/limits.hpp>

#include <boost/type_traits/is_integral.hpp>
#include <boost/spirit/home/support/char_class.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/numeric_traits.hpp>
#include <boost/spirit/home/support/detail/pow10.hpp>
#include <boost/spirit/home/karma/detail/generate_to.hpp>
#include <boost/spirit/home/karma/detail/string_generate.hpp>

#include <boost/core/cmath.hpp>

///////////////////////////////////////////////////////////////////////////////
//
//  The value BOOST_KARMA_NUMERICS_LOOP_UNROLL specifies, how to unroll the
//  integer string generation loop (see below).
//
//      Set the value to some integer in between 0 (no unrolling) and the
//      largest expected generated integer string length (complete unrolling).
//      If not specified, this value defaults to 6.
//
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_KARMA_NUMERICS_LOOP_UNROLL)
#define BOOST_KARMA_NUMERICS_LOOP_UNROLL 6
#endif

#if BOOST_KARMA_NUMERICS_LOOP_UNROLL < 0
#error "Please set the BOOST_KARMA_NUMERICS_LOOP_UNROLL to a non-negative value!"
#endif

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////
    //
    //  return the absolute value from a given number, avoiding over- and
    //  underflow
    //
    ///////////////////////////////////////////////////////////////////////
    template <typename T, typename Enable/* = void*/>
    struct absolute_value
    {
        typedef T type;
        static T call (T n)
        {
            // allow for ADL to find the correct overloads for fabs
            using namespace std;
            return fabs(n);
        }
    };

#define BOOST_SPIRIT_ABSOLUTE_VALUE(signedtype, unsignedtype)                 \
        template <>                                                           \
        struct absolute_value<signedtype>                                     \
        {                                                                     \
            typedef unsignedtype type;                                        \
            static type call(signedtype n)                                    \
            {                                                                 \
                /* implementation is well-defined for one's complement, */    \
                /* two's complement, and signed magnitude architectures */    \
                /* by the C++ Standard. [conv.integral] [expr.unary.op] */    \
                return (n >= 0) ?  static_cast<type>(n)                       \
                                : -static_cast<type>(n);                      \
            }                                                                 \
        }                                                                     \
    /**/
#define BOOST_SPIRIT_ABSOLUTE_VALUE_UNSIGNED(unsignedtype)                    \
        template <>                                                           \
        struct absolute_value<unsignedtype>                                   \
        {                                                                     \
            typedef unsignedtype type;                                        \
            static type call(unsignedtype n)                                  \
            {                                                                 \
                return n;                                                     \
            }                                                                 \
        }                                                                     \
    /**/

#if defined(BOOST_MSVC)
# pragma warning(push)
// unary minus operator applied to unsigned type, result still unsigned
# pragma warning(disable: 4146)
#endif
    BOOST_SPIRIT_ABSOLUTE_VALUE(signed char, unsigned char);
    BOOST_SPIRIT_ABSOLUTE_VALUE(char, unsigned char);
    BOOST_SPIRIT_ABSOLUTE_VALUE(short, unsigned short);
    BOOST_SPIRIT_ABSOLUTE_VALUE(int, unsigned int);
    BOOST_SPIRIT_ABSOLUTE_VALUE(long, unsigned long);
    BOOST_SPIRIT_ABSOLUTE_VALUE_UNSIGNED(unsigned char);
    BOOST_SPIRIT_ABSOLUTE_VALUE_UNSIGNED(unsigned short);
    BOOST_SPIRIT_ABSOLUTE_VALUE_UNSIGNED(unsigned int);
    BOOST_SPIRIT_ABSOLUTE_VALUE_UNSIGNED(unsigned long);
#ifdef BOOST_HAS_LONG_LONG
    BOOST_SPIRIT_ABSOLUTE_VALUE(boost::long_long_type, boost::ulong_long_type);
    BOOST_SPIRIT_ABSOLUTE_VALUE_UNSIGNED(boost::ulong_long_type);
#endif
#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#undef BOOST_SPIRIT_ABSOLUTE_VALUE
#undef BOOST_SPIRIT_ABSOLUTE_VALUE_UNSIGNED

    template <>
    struct absolute_value<float>
    {
        typedef float type;
        static type call(float n)
        {
            return (std::fabs)(n);
        }
    };

    template <>
    struct absolute_value<double>
    {
        typedef double type;
        static type call(double n)
        {
            return (std::fabs)(n);
        }
    };

    template <>
    struct absolute_value<long double>
    {
        typedef long double type;
        static type call(long double n)
        {
            return (std::fabs)(n);
        }
    };

    // specialization for pointers
    template <typename T>
    struct absolute_value<T*>
    {
        typedef std::size_t type;
        static type call (T* p)
        {
            return std::size_t(p);
        }
    };

    template <typename T>
    inline typename absolute_value<T>::type
    get_absolute_value(T n)
    {
        return absolute_value<T>::call(n);
    }

    ///////////////////////////////////////////////////////////////////////
    template <typename T, typename Enable/* = void*/>
    struct is_negative
    {
        static bool call(T n)
        {
            return (n < 0) ? true : false;
        }
    };

    template <>
    struct is_negative<float>
    {
        static bool call(float n)
        {
            return (core::signbit)(n) ? true : false;
        }
    };

    template <>
    struct is_negative<double>
    {
        static bool call(double n)
        {
            return (core::signbit)(n) ? true : false;
        }
    };

    template <>
    struct is_negative<long double>
    {
        static bool call(long double n)
        {
            return (core::signbit)(n) ? true : false;
        }
    };

    template <typename T>
    inline bool test_negative(T n)
    {
        return is_negative<T>::call(n);
    }

    ///////////////////////////////////////////////////////////////////////
    template <typename T, typename Enable/* = void*/>
    struct is_zero
    {
        static bool call(T n)
        {
            return (n == 0) ? true : false;
        }
    };

    template <>
    struct is_zero<float>
    {
        static bool call(float n)
        {
            return (core::fpclassify)(n) == core::fp_zero;
        }
    };

    template <>
    struct is_zero<double>
    {
        static bool call(double n)
        {
            return (core::fpclassify)(n) == core::fp_zero;
        }
    };

    template <>
    struct is_zero<long double>
    {
        static bool call(long double n)
        {
            return (core::fpclassify)(n) == core::fp_zero;
        }
    };

    template <typename T>
    inline bool test_zero(T n)
    {
        return is_zero<T>::call(n);
    }

    ///////////////////////////////////////////////////////////////////////
    template <typename T, typename Enable/* = void*/>
    struct is_nan
    {
        static bool call(T n)
        {
            // NaN numbers are not equal to anything
            return (n != n) ? true : false;
        }
    };

    template <>
    struct is_nan<float>
    {
        static bool call(float n)
        {
            return (core::fpclassify)(n) == core::fp_nan;
        }
    };

    template <>
    struct is_nan<double>
    {
        static bool call(double n)
        {
            return (core::fpclassify)(n) == core::fp_nan;
        }
    };

    template <>
    struct is_nan<long double>
    {
        static bool call(long double n)
        {
            return (core::fpclassify)(n) == core::fp_nan;
        }
    };

    template <typename T>
    inline bool test_nan(T n)
    {
        return is_nan<T>::call(n);
    }

    ///////////////////////////////////////////////////////////////////////
    template <typename T, typename Enable/* = void*/>
    struct is_infinite
    {
        static bool call(T n)
        {
            return std::numeric_limits<T>::has_infinity
                && n == std::numeric_limits<T>::infinity();
        }
    };

    template <>
    struct is_infinite<float>
    {
        static bool call(float n)
        {
            return (core::fpclassify)(n) == core::fp_infinite;
        }
    };

    template <>
    struct is_infinite<double>
    {
        static bool call(double n)
        {
            return (core::fpclassify)(n) == core::fp_infinite;
        }
    };

    template <>
    struct is_infinite<long double>
    {
        static bool call(long double n)
        {
            return (core::fpclassify)(n) == core::fp_infinite;
        }
    };

    template <typename T>
    inline bool test_infinite(T n)
    {
        return is_infinite<T>::call(n);
    }

    ///////////////////////////////////////////////////////////////////////
    struct cast_to_long
    {
        static long call(float n, mpl::false_)
        {
            return static_cast<long>(std::floor(n));
        }

        static long call(double n, mpl::false_)
        {
            return static_cast<long>(std::floor(n));
        }

        static long call(long double n, mpl::false_)
        {
            return static_cast<long>(std::floor(n));
        }

        template <typename T>
        static long call(T n, mpl::false_)
        {
            // allow for ADL to find the correct overload for floor and
            // lround
            using namespace std;
            return lround(floor(n));
        }

        template <typename T>
        static long call(T n, mpl::true_)
        {
            return static_cast<long>(n);
        }

        template <typename T>
        static long call(T n)
        {
            return call(n, mpl::bool_<is_integral<T>::value>());
        }
    };

    ///////////////////////////////////////////////////////////////////////
    struct truncate_to_long
    {
        static long call(float n, mpl::false_)
        {
            return test_negative(n) ? static_cast<long>(std::ceil(n)) :
                static_cast<long>(std::floor(n));
        }

        static long call(double n, mpl::false_)
        {
            return test_negative(n) ? static_cast<long>(std::ceil(n)) :
                static_cast<long>(std::floor(n));
        }

        static long call(long double n, mpl::false_)
        {
            return test_negative(n) ? static_cast<long>(std::ceil(n)) :
                static_cast<long>(std::floor(n));
        }

        template <typename T>
        static long call(T n, mpl::false_)
        {
            // allow for ADL to find the correct overloads for ltrunc
            using namespace std;
            return ltrunc(n);
        }

        template <typename T>
        static long call(T n, mpl::true_)
        {
            return static_cast<long>(n);
        }

        template <typename T>
        static long call(T n)
        {
            return call(n, mpl::bool_<is_integral<T>::value>());
        }
    };

    ///////////////////////////////////////////////////////////////////////
    //
    //  Traits class for radix specific number conversion
    //
    //      Convert a digit from binary representation to character
    //      representation:
    //
    //          static int call(unsigned n);
    //
    ///////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename CharEncoding, typename Tag, bool radix_less_than_10>
        struct convert_digit
        {
            static int call(unsigned n)
            {
                if (n <= 9)
                    return n + '0';

                using spirit::char_class::convert;
                return convert<CharEncoding>::to(Tag(), n - 10 + 'a');
            }
        };

        template <>
        struct convert_digit<unused_type, unused_type, false>
        {
            static int call(unsigned n)
            {
                if (n <= 9)
                    return n + '0';
                return n - 10 + 'a';
            }
        };

        template <typename CharEncoding, typename Tag>
        struct convert_digit<CharEncoding, Tag, true>
        {
            static int call(unsigned n)
            {
                return n + '0';
            }
        };
    }

    template <unsigned Radix, typename CharEncoding, typename Tag>
    struct convert_digit
      : detail::convert_digit<CharEncoding, Tag, (Radix <= 10) ? true : false>
    {};

    ///////////////////////////////////////////////////////////////////////
    template <unsigned Radix>
    struct divide
    {
        template <typename T>
        static T call(T& n, mpl::true_)
        {
            return n / Radix;
        }

        template <typename T>
        static T call(T& n, mpl::false_)
        {
            // Allow ADL to find the correct overload for floor
            using namespace std;
            return floor(n / Radix);
        }

        template <typename T>
        static T call(T& n, T const&, int)
        {
            return call(n, mpl::bool_<is_integral<T>::value>());
        }

        template <typename T>
        static T call(T& n)
        {
            return call(n, mpl::bool_<is_integral<T>::value>());
        }
    };

    // specialization for division by 10
    template <>
    struct divide<10>
    {
        template <typename T>
        static T call(T& n, T, int, mpl::true_)
        {
            return n / 10;
        }

        template <typename T>
        static T call(T, T& num, int exp, mpl::false_)
        {
            // Allow ADL to find the correct overload for floor
            using namespace std;
            return floor(num / spirit::traits::pow10<T>(exp));
        }

        template <typename T>
        static T call(T& n, T& num, int exp)
        {
            return call(n, num, exp, mpl::bool_<is_integral<T>::value>());
        }

        template <typename T>
        static T call(T& n)
        {
            return call(n, n, 1, mpl::bool_<is_integral<T>::value>());
        }
    };

    ///////////////////////////////////////////////////////////////////////
    template <unsigned Radix>
    struct remainder
    {
        template <typename T>
        static long call(T n, mpl::true_)
        {
            // this cast is safe since we know the result is not larger
            // than Radix
            return static_cast<long>(n % Radix);
        }

        template <typename T>
        static long call(T n, mpl::false_)
        {
            // Allow ADL to find the correct overload for fmod
            using namespace std;
            return cast_to_long::call(fmod(n, T(Radix)));
        }

        template <typename T>
        static long call(T n)
        {
            return call(n, mpl::bool_<is_integral<T>::value>());
        }
    };
}}}

namespace boost { namespace spirit { namespace karma
{
    ///////////////////////////////////////////////////////////////////////////
    //
    //  The int_inserter template takes care of the integer to string
    //  conversion. If specified, the loop is unrolled for better performance.
    //
    //      Set the value BOOST_KARMA_NUMERICS_LOOP_UNROLL to some integer in
    //      between 0 (no unrolling) and the largest expected generated integer
    //      string length (complete unrolling).
    //      If not specified, this value defaults to 6.
    //
    ///////////////////////////////////////////////////////////////////////////
#define BOOST_KARMA_NUMERICS_INNER_LOOP_PREFIX(z, x, data)                    \
        if (!traits::test_zero(n)) {                                          \
            int ch_##x = radix_type::call(remainder_type::call(n));           \
            n = divide_type::call(n, num, ++exp);                             \
    /**/

#define BOOST_KARMA_NUMERICS_INNER_LOOP_SUFFIX(z, x, n_rolls_sub1)            \
            *sink = char(BOOST_PP_CAT(ch_, BOOST_PP_SUB(n_rolls_sub1, x)));   \
            ++sink;                                                           \
        }                                                                     \
    /**/

    template <
        unsigned Radix, typename CharEncoding = unused_type
      , typename Tag = unused_type>
    struct int_inserter
    {
        typedef traits::convert_digit<Radix, CharEncoding, Tag> radix_type;
        typedef traits::divide<Radix> divide_type;
        typedef traits::remainder<Radix> remainder_type;

        template <typename OutputIterator, typename T>
        static bool
        call(OutputIterator& sink, T n, T& num, int exp)
        {
            // remainder_type::call returns n % Radix
            int ch = radix_type::call(remainder_type::call(n));
            n = divide_type::call(n, num, ++exp);

            BOOST_PP_REPEAT(
                BOOST_KARMA_NUMERICS_LOOP_UNROLL,
                BOOST_KARMA_NUMERICS_INNER_LOOP_PREFIX, _);

            if (!traits::test_zero(n))
                call(sink, n, num, exp);

            BOOST_PP_REPEAT(
                BOOST_KARMA_NUMERICS_LOOP_UNROLL,
                BOOST_KARMA_NUMERICS_INNER_LOOP_SUFFIX,
                BOOST_PP_DEC(BOOST_KARMA_NUMERICS_LOOP_UNROLL));

            *sink = char(ch);
            ++sink;
            return true;
        }

        //  Common code for integer string representations
        template <typename OutputIterator, typename T>
        static bool
        call(OutputIterator& sink, T n)
        {
            return call(sink, n, n, 0);
        }

    private:
        // helper function returning the biggest number representable either in
        // a boost::long_long_type (if this does exist) or in a plain long
        // otherwise
#if defined(BOOST_HAS_LONG_LONG)
        typedef boost::long_long_type biggest_long_type;
#else
        typedef long biggest_long_type;
#endif

        static biggest_long_type max_long()
        {
            return (std::numeric_limits<biggest_long_type>::max)();
        }

    public:
        // Specialization for doubles and floats, falling back to long integers
        // for representable values. These specializations speed up formatting
        // of floating point numbers considerably as all the required
        // arithmetics will be executed using integral data types.
        template <typename OutputIterator>
        static bool
        call(OutputIterator& sink, long double n)
        {
            if (std::fabs(n) < max_long())
            {
                biggest_long_type l((biggest_long_type)n);
                return call(sink, l, l, 0);
            }
            return call(sink, n, n, 0);
        }
        template <typename OutputIterator>
        static bool
        call(OutputIterator& sink, double n)
        {
            if (std::fabs(n) < max_long())
            {
                biggest_long_type l((biggest_long_type)n);
                return call(sink, l, l, 0);
            }
            return call(sink, n, n, 0);
        }
        template <typename OutputIterator>
        static bool
        call(OutputIterator& sink, float n)
        {
            if (std::fabs(n) < max_long())
            {
                biggest_long_type l((biggest_long_type)n);
                return call(sink, l, l, 0);
            }
            return call(sink, n, n, 0);
        }
    };

#undef BOOST_KARMA_NUMERICS_INNER_LOOP_PREFIX
#undef BOOST_KARMA_NUMERICS_INNER_LOOP_SUFFIX

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The uint_inserter template takes care of the conversion of any integer
    //  to a string, while interpreting the number as an unsigned type.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
        unsigned Radix, typename CharEncoding = unused_type
      , typename Tag = unused_type>
    struct uint_inserter : int_inserter<Radix, CharEncoding, Tag>
    {
        typedef int_inserter<Radix, CharEncoding, Tag> base_type;

        //  Common code for integer string representations
        template <typename OutputIterator, typename T>
        static bool
        call(OutputIterator& sink, T const& n)
        {
            typedef typename traits::absolute_value<T>::type type;
            type un = type(n);
            return base_type::call(sink, un, un, 0);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The sign_inserter template generates a sign for a given numeric value.
    //
    //    The parameter forcesign allows to generate a sign even for positive
    //    numbers.
    //
    ///////////////////////////////////////////////////////////////////////////
    struct sign_inserter
    {
        template <typename OutputIterator>
        static bool
        call_noforce(OutputIterator& sink, bool is_zero, bool is_negative,
            bool sign_if_zero)
        {
            // generate a sign for negative numbers only
            if (is_negative || (is_zero && sign_if_zero)) {
                *sink = '-';
                ++sink;
            }
            return true;
        }

        template <typename OutputIterator>
        static bool
        call_force(OutputIterator& sink, bool is_zero, bool is_negative,
            bool sign_if_zero)
        {
            // generate a sign for all numbers except zero
            if (!is_zero || sign_if_zero)
                *sink = is_negative ? '-' : '+';
            else
                *sink = ' ';

            ++sink;
            return true;
        }

        template <typename OutputIterator>
        static bool
        call(OutputIterator& sink, bool is_zero, bool is_negative
          , bool forcesign, bool sign_if_zero = false)
        {
            return forcesign ?
                call_force(sink, is_zero, is_negative, sign_if_zero) :
                call_noforce(sink, is_zero, is_negative, sign_if_zero);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //  These are helper functions for the real policies allowing to generate
    //  a single character and a string
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharEncoding = unused_type, typename Tag = unused_type>
    struct char_inserter
    {
        template <typename OutputIterator, typename Char>
        static bool call(OutputIterator& sink, Char c)
        {
            return detail::generate_to(sink, c, CharEncoding(), Tag());
        }
    };

    template <typename CharEncoding = unused_type, typename Tag = unused_type>
    struct string_inserter
    {
        template <typename OutputIterator, typename String>
        static bool call(OutputIterator& sink, String str)
        {
            return detail::string_generate(sink, str, CharEncoding(), Tag());
        }
    };

}}}

#endif

/* numeric_utils.hpp
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
*/