// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// what:  lexical_cast custom keyword cast
// who:   contributed by Kevlin Henney,
//        enhanced with contributions from Terje Slettebo,
//        with additional fixes and suggestions from Gennaro Prota,
//        Beman Dawes, Dave Abrahams, Daryle Walker, Peter Dimov,
//        Alexander Nasonov, Antony Polukhin, Justin Viiret, Michael Hofmann,
//        Cheng Yang, Matthew Bradbury, David W. Birdsall, Pavel Korzh and other Boosters
// when:  November 2000, March 2003, June 2005, June 2006, March 2011 - 2014

#ifndef BOOST_LEXICAL_CAST_DETAIL_CONVERTER_LEXICAL_HPP
#define BOOST_LEXICAL_CAST_DETAIL_CONVERTER_LEXICAL_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#if defined(BOOST_NO_STRINGSTREAM) || defined(BOOST_NO_STD_WSTRING)
#define BOOST_LCAST_NO_WCHAR_T
#endif

#include <cstddef>
#include <string>
#include <boost/limits.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/type_identity.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/has_left_shift.hpp>
#include <boost/type_traits/has_right_shift.hpp>
#include <boost/static_assert.hpp>
#include <boost/detail/lcast_precision.hpp>

#include <boost/lexical_cast/detail/widest_char.hpp>
#include <boost/lexical_cast/detail/is_character.hpp>

#ifndef BOOST_NO_CXX11_HDR_ARRAY
#include <array>
#endif

#include <boost/array.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/container/container_fwd.hpp>

#include <boost/lexical_cast/detail/converter_lexical_streams.hpp>

namespace boost {

    namespace detail // normalize_single_byte_char<Char>
    {
        // Converts signed/unsigned char to char
        template < class Char >
        struct normalize_single_byte_char
        {
            typedef Char type;
        };

        template <>
        struct normalize_single_byte_char< signed char >
        {
            typedef char type;
        };

        template <>
        struct normalize_single_byte_char< unsigned char >
        {
            typedef char type;
        };
    }

    namespace detail // deduce_character_type_later<T>
    {
        // Helper type, meaning that stram character for T must be deduced
        // at Stage 2 (See deduce_source_char<T> and deduce_target_char<T>)
        template < class T > struct deduce_character_type_later {};
    }

    namespace detail // stream_char_common<T>
    {
        // Selectors to choose stream character type (common for Source and Target)
        // Returns one of char, wchar_t, char16_t, char32_t or deduce_character_type_later<T> types
        // Executed on Stage 1 (See deduce_source_char<T> and deduce_target_char<T>)
        template < typename Type >
        struct stream_char_common: public boost::conditional<
            boost::detail::is_character< Type >::value,
            Type,
            boost::detail::deduce_character_type_later< Type >
        > {};

        template < typename Char >
        struct stream_char_common< Char* >: public boost::conditional<
            boost::detail::is_character< Char >::value,
            Char,
            boost::detail::deduce_character_type_later< Char* >
        > {};

        template < typename Char >
        struct stream_char_common< const Char* >: public boost::conditional<
            boost::detail::is_character< Char >::value,
            Char,
            boost::detail::deduce_character_type_later< const Char* >
        > {};

        template < typename Char >
        struct stream_char_common< boost::iterator_range< Char* > >: public boost::conditional<
            boost::detail::is_character< Char >::value,
            Char,
            boost::detail::deduce_character_type_later< boost::iterator_range< Char* > >
        > {};

        template < typename Char >
        struct stream_char_common< boost::iterator_range< const Char* > >: public boost::conditional<
            boost::detail::is_character< Char >::value,
            Char,
            boost::detail::deduce_character_type_later< boost::iterator_range< const Char* > >
        > {};

        template < class Char, class Traits, class Alloc >
        struct stream_char_common< std::basic_string< Char, Traits, Alloc > >
        {
            typedef Char type;
        };

        template < class Char, class Traits, class Alloc >
        struct stream_char_common< boost::container::basic_string< Char, Traits, Alloc > >
        {
            typedef Char type;
        };

        template < typename Char, std::size_t N >
        struct stream_char_common< boost::array< Char, N > >: public boost::conditional<
            boost::detail::is_character< Char >::value,
            Char,
            boost::detail::deduce_character_type_later< boost::array< Char, N > >
        > {};

        template < typename Char, std::size_t N >
        struct stream_char_common< boost::array< const Char, N > >: public boost::conditional<
            boost::detail::is_character< Char >::value,
            Char,
            boost::detail::deduce_character_type_later< boost::array< const Char, N > >
        > {};

#ifndef BOOST_NO_CXX11_HDR_ARRAY
        template < typename Char, std::size_t N >
        struct stream_char_common< std::array<Char, N > >: public boost::conditional<
            boost::detail::is_character< Char >::value,
            Char,
            boost::detail::deduce_character_type_later< std::array< Char, N > >
        > {};

        template < typename Char, std::size_t N >
        struct stream_char_common< std::array< const Char, N > >: public boost::conditional<
            boost::detail::is_character< Char >::value,
            Char,
            boost::detail::deduce_character_type_later< std::array< const Char, N > >
        > {};
#endif

#ifdef BOOST_HAS_INT128
        template <> struct stream_char_common< boost::int128_type >: public boost::type_identity< char > {};
        template <> struct stream_char_common< boost::uint128_type >: public boost::type_identity< char > {};
#endif

#if !defined(BOOST_LCAST_NO_WCHAR_T) && defined(BOOST_NO_INTRINSIC_WCHAR_T)
        template <>
        struct stream_char_common< wchar_t >
        {
            typedef char type;
        };
#endif
    }

    namespace detail // deduce_source_char_impl<T>
    {
        // If type T is `deduce_character_type_later` type, then tries to deduce
        // character type using boost::has_left_shift<T> metafunction.
        // Otherwise supplied type T is a character type, that must be normalized
        // using normalize_single_byte_char<Char>.
        // Executed at Stage 2  (See deduce_source_char<T> and deduce_target_char<T>)
        template < class Char >
        struct deduce_source_char_impl
        {
            typedef BOOST_DEDUCED_TYPENAME boost::detail::normalize_single_byte_char< Char >::type type;
        };

        template < class T >
        struct deduce_source_char_impl< deduce_character_type_later< T > >
        {
            typedef boost::has_left_shift< std::basic_ostream< char >, T > result_t;

#if defined(BOOST_LCAST_NO_WCHAR_T)
            BOOST_STATIC_ASSERT_MSG((result_t::value),
                "Source type is not std::ostream`able and std::wostream`s are not supported by your STL implementation");
            typedef char type;
#else
            typedef BOOST_DEDUCED_TYPENAME boost::conditional<
                result_t::value, char, wchar_t
            >::type type;

            BOOST_STATIC_ASSERT_MSG((result_t::value || boost::has_left_shift< std::basic_ostream< type >, T >::value),
                "Source type is neither std::ostream`able nor std::wostream`able");
#endif
        };
    }

    namespace detail  // deduce_target_char_impl<T>
    {
        // If type T is `deduce_character_type_later` type, then tries to deduce
        // character type using boost::has_right_shift<T> metafunction.
        // Otherwise supplied type T is a character type, that must be normalized
        // using normalize_single_byte_char<Char>.
        // Executed at Stage 2  (See deduce_source_char<T> and deduce_target_char<T>)
        template < class Char >
        struct deduce_target_char_impl
        {
            typedef BOOST_DEDUCED_TYPENAME normalize_single_byte_char< Char >::type type;
        };

        template < class T >
        struct deduce_target_char_impl< deduce_character_type_later<T> >
        {
            typedef boost::has_right_shift<std::basic_istream<char>, T > result_t;

#if defined(BOOST_LCAST_NO_WCHAR_T)
            BOOST_STATIC_ASSERT_MSG((result_t::value),
                "Target type is not std::istream`able and std::wistream`s are not supported by your STL implementation");
            typedef char type;
#else
            typedef BOOST_DEDUCED_TYPENAME boost::conditional<
                result_t::value, char, wchar_t
            >::type type;

            BOOST_STATIC_ASSERT_MSG((result_t::value || boost::has_right_shift<std::basic_istream<wchar_t>, T >::value),
                "Target type is neither std::istream`able nor std::wistream`able");
#endif
        };
    }

    namespace detail  // deduce_target_char<T> and deduce_source_char<T>
    {
        // We deduce stream character types in two stages.
        //
        // Stage 1 is common for Target and Source. At Stage 1 we get
        // non normalized character type (may contain unsigned/signed char)
        // or deduce_character_type_later<T> where T is the original type.
        // Stage 1 is executed by stream_char_common<T>
        //
        // At Stage 2 we normalize character types or try to deduce character
        // type using metafunctions.
        // Stage 2 is executed by deduce_target_char_impl<T> and
        // deduce_source_char_impl<T>
        //
        // deduce_target_char<T> and deduce_source_char<T> functions combine
        // both stages

        template < class T >
        struct deduce_target_char
        {
            typedef BOOST_DEDUCED_TYPENAME stream_char_common< T >::type stage1_type;
            typedef BOOST_DEDUCED_TYPENAME deduce_target_char_impl< stage1_type >::type stage2_type;

            typedef stage2_type type;
        };

        template < class T >
        struct deduce_source_char
        {
            typedef BOOST_DEDUCED_TYPENAME stream_char_common< T >::type stage1_type;
            typedef BOOST_DEDUCED_TYPENAME deduce_source_char_impl< stage1_type >::type stage2_type;

            typedef stage2_type type;
        };
    }

    namespace detail // extract_char_traits template
    {
        // We are attempting to get char_traits<> from T
        // template parameter. Otherwise we'll be using std::char_traits<Char>
        template < class Char, class T >
        struct extract_char_traits
                : boost::false_type
        {
            typedef std::char_traits< Char > trait_t;
        };

        template < class Char, class Traits, class Alloc >
        struct extract_char_traits< Char, std::basic_string< Char, Traits, Alloc > >
            : boost::true_type
        {
            typedef Traits trait_t;
        };

        template < class Char, class Traits, class Alloc>
        struct extract_char_traits< Char, boost::container::basic_string< Char, Traits, Alloc > >
            : boost::true_type
        {
            typedef Traits trait_t;
        };
    }

    namespace detail // array_to_pointer_decay<T>
    {
        template<class T>
        struct array_to_pointer_decay
        {
            typedef T type;
        };

        template<class T, std::size_t N>
        struct array_to_pointer_decay<T[N]>
        {
            typedef const T * type;
        };
    }

    namespace detail // lcast_src_length
    {
        // Return max. length of string representation of Source;
        template< class Source,         // Source type of lexical_cast.
                  class Enable = void   // helper type
                >
        struct lcast_src_length
        {
            BOOST_STATIC_CONSTANT(std::size_t, value = 1);
        };

        // Helper for integral types.
        // Notes on length calculation:
        // Max length for 32bit int with grouping "\1" and thousands_sep ',':
        // "-2,1,4,7,4,8,3,6,4,7"
        //  ^                    - is_signed
        //   ^                   - 1 digit not counted by digits10
        //    ^^^^^^^^^^^^^^^^^^ - digits10 * 2
        //
        // Constant is_specialized is used instead of constant 1
        // to prevent buffer overflow in a rare case when
        // <boost/limits.hpp> doesn't add missing specialization for
        // numeric_limits<T> for some integral type T.
        // When is_specialized is false, the whole expression is 0.
        template <class Source>
        struct lcast_src_length<
                    Source, BOOST_DEDUCED_TYPENAME boost::enable_if<boost::is_integral<Source> >::type
                >
        {
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
            BOOST_STATIC_CONSTANT(std::size_t, value =
                  std::numeric_limits<Source>::is_signed +
                  std::numeric_limits<Source>::is_specialized + /* == 1 */
                  std::numeric_limits<Source>::digits10 * 2
              );
#else
            BOOST_STATIC_CONSTANT(std::size_t, value = 156);
            BOOST_STATIC_ASSERT(sizeof(Source) * CHAR_BIT <= 256);
#endif
        };

        // Helper for floating point types.
        // -1.23456789e-123456
        // ^                   sign
        //  ^                  leading digit
        //   ^                 decimal point
        //    ^^^^^^^^         lcast_precision<Source>::value
        //            ^        "e"
        //             ^       exponent sign
        //              ^^^^^^ exponent (assumed 6 or less digits)
        // sign + leading digit + decimal point + "e" + exponent sign == 5
        template<class Source>
        struct lcast_src_length<
                Source, BOOST_DEDUCED_TYPENAME boost::enable_if<boost::is_float<Source> >::type
            >
        {

#ifndef BOOST_LCAST_NO_COMPILE_TIME_PRECISION
            BOOST_STATIC_ASSERT(
                    std::numeric_limits<Source>::max_exponent10 <=  999999L &&
                    std::numeric_limits<Source>::min_exponent10 >= -999999L
                );

            BOOST_STATIC_CONSTANT(std::size_t, value =
                    5 + lcast_precision<Source>::value + 6
                );
#else // #ifndef BOOST_LCAST_NO_COMPILE_TIME_PRECISION
            BOOST_STATIC_CONSTANT(std::size_t, value = 156);
#endif // #ifndef BOOST_LCAST_NO_COMPILE_TIME_PRECISION
        };
    }

    namespace detail // lexical_cast_stream_traits<Source, Target>
    {
        template <class Source, class Target>
        struct lexical_cast_stream_traits {
            typedef BOOST_DEDUCED_TYPENAME boost::detail::array_to_pointer_decay<Source>::type src;
            typedef BOOST_DEDUCED_TYPENAME boost::remove_cv<src>::type            no_cv_src;

            typedef boost::detail::deduce_source_char<no_cv_src>                           deduce_src_char_metafunc;
            typedef BOOST_DEDUCED_TYPENAME deduce_src_char_metafunc::type           src_char_t;
            typedef BOOST_DEDUCED_TYPENAME boost::detail::deduce_target_char<Target>::type target_char_t;

            typedef BOOST_DEDUCED_TYPENAME boost::detail::widest_char<
                target_char_t, src_char_t
            >::type char_type;

#if !defined(BOOST_NO_CXX11_CHAR16_T) && defined(BOOST_NO_CXX11_UNICODE_LITERALS)
            BOOST_STATIC_ASSERT_MSG(( !boost::is_same<char16_t, src_char_t>::value
                                        && !boost::is_same<char16_t, target_char_t>::value),
                "Your compiler does not have full support for char16_t" );
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T) && defined(BOOST_NO_CXX11_UNICODE_LITERALS)
            BOOST_STATIC_ASSERT_MSG(( !boost::is_same<char32_t, src_char_t>::value
                                        && !boost::is_same<char32_t, target_char_t>::value),
                "Your compiler does not have full support for char32_t" );
#endif

            typedef BOOST_DEDUCED_TYPENAME boost::conditional<
                boost::detail::extract_char_traits<char_type, Target>::value,
                BOOST_DEDUCED_TYPENAME boost::detail::extract_char_traits<char_type, Target>,
                BOOST_DEDUCED_TYPENAME boost::detail::extract_char_traits<char_type, no_cv_src>
            >::type::trait_t traits;

            typedef boost::integral_constant<
              bool,
              boost::is_same<char, src_char_t>::value &&                                 // source is not a wide character based type
                (sizeof(char) != sizeof(target_char_t)) &&  // target type is based on wide character
                (!(boost::detail::is_character<no_cv_src>::value))
                > is_string_widening_required_t;

            typedef boost::integral_constant<
              bool,
                !(boost::is_integral<no_cv_src>::value ||
                  boost::detail::is_character<
                    BOOST_DEDUCED_TYPENAME deduce_src_char_metafunc::stage1_type          // if we did not get character type at stage1
                  >::value                                                           // then we have no optimization for that type
                 )
                > is_source_input_not_optimized_t;

            // If we have an optimized conversion for
            // Source, we do not need to construct stringbuf.
            BOOST_STATIC_CONSTANT(bool, requires_stringbuf =
                (is_string_widening_required_t::value || is_source_input_not_optimized_t::value)
            );

            typedef boost::detail::lcast_src_length<no_cv_src> len_t;
        };
    }

    namespace detail
    {
        template<typename Target, typename Source>
        struct lexical_converter_impl
        {
            typedef lexical_cast_stream_traits<Source, Target>  stream_trait;

            typedef detail::lexical_istream_limited_src<
                BOOST_DEDUCED_TYPENAME stream_trait::char_type,
                BOOST_DEDUCED_TYPENAME stream_trait::traits,
                stream_trait::requires_stringbuf,
                stream_trait::len_t::value + 1
            > i_interpreter_type;

            typedef detail::lexical_ostream_limited_src<
                BOOST_DEDUCED_TYPENAME stream_trait::char_type,
                BOOST_DEDUCED_TYPENAME stream_trait::traits
            > o_interpreter_type;

            static inline bool try_convert(const Source& arg, Target& result) {
                i_interpreter_type i_interpreter;

                // Disabling ADL, by directly specifying operators.
                if (!(i_interpreter.operator <<(arg)))
                    return false;

                o_interpreter_type out(i_interpreter.cbegin(), i_interpreter.cend());

                // Disabling ADL, by directly specifying operators.
                if(!(out.operator >>(result)))
                    return false;

                return true;
            }
        };
    }

} // namespace boost

#undef BOOST_LCAST_NO_WCHAR_T

#endif // BOOST_LEXICAL_CAST_DETAIL_CONVERTER_LEXICAL_HPP


/* converter_lexical.hpp
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
*/