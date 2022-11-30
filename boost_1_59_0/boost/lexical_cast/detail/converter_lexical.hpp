// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2022.
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