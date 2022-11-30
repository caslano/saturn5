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

#ifndef BOOST_LEXICAL_CAST_TRY_LEXICAL_CONVERT_HPP
#define BOOST_LEXICAL_CAST_TRY_LEXICAL_CONVERT_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#if defined(__clang__) || (defined(__GNUC__) && \
    !(defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)) && \
    (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif


#include <string>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/type_identity.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_arithmetic.hpp>

#include <boost/lexical_cast/detail/is_character.hpp>
#include <boost/lexical_cast/detail/converter_numeric.hpp>
#include <boost/lexical_cast/detail/converter_lexical.hpp>

#include <boost/range/iterator_range_core.hpp>
#include <boost/container/container_fwd.hpp>

namespace boost {
    namespace detail
    {
        template<typename T>
        struct is_stdstring
            : boost::false_type
        {};

        template<typename CharT, typename Traits, typename Alloc>
        struct is_stdstring< std::basic_string<CharT, Traits, Alloc> >
            : boost::true_type
        {};

        // Sun Studio has problem with partial specialization of templates differing only in namespace.
        // We workaround that by making `is_booststring` trait, instead of specializing `is_stdstring` for `boost::container::basic_string`.
        template<typename T>
        struct is_booststring
            : boost::false_type
        {};

        template<typename CharT, typename Traits, typename Alloc>
        struct is_booststring< boost::container::basic_string<CharT, Traits, Alloc> >
            : boost::true_type
        {};

        template<typename Target, typename Source>
        struct is_arithmetic_and_not_xchars
        {
            typedef boost::integral_constant<
                bool,
                !(boost::detail::is_character<Target>::value) &&
                    !(boost::detail::is_character<Source>::value) &&
                    boost::is_arithmetic<Source>::value &&
                    boost::is_arithmetic<Target>::value
                > type;

            BOOST_STATIC_CONSTANT(bool, value = (
                type::value
            ));
        };

        /*
         * is_xchar_to_xchar<Target, Source>::value is true,
         * Target and Souce are char types of the same size 1 (char, signed char, unsigned char).
         */
        template<typename Target, typename Source>
        struct is_xchar_to_xchar
        {
            typedef boost::integral_constant<
                bool,
                sizeof(Source) == sizeof(Target) &&
                     sizeof(Source) == sizeof(char) &&
                     boost::detail::is_character<Target>::value &&
                     boost::detail::is_character<Source>::value
                > type;

            BOOST_STATIC_CONSTANT(bool, value = (
                type::value
            ));
        };

        template<typename Target, typename Source>
        struct is_char_array_to_stdstring
            : boost::false_type
        {};

        template<typename CharT, typename Traits, typename Alloc>
        struct is_char_array_to_stdstring< std::basic_string<CharT, Traits, Alloc>, CharT* >
            : boost::true_type
        {};

        template<typename CharT, typename Traits, typename Alloc>
        struct is_char_array_to_stdstring< std::basic_string<CharT, Traits, Alloc>, const CharT* >
            : boost::true_type
        {};

        // Sun Studio has problem with partial specialization of templates differing only in namespace.
        // We workaround that by making `is_char_array_to_booststring` trait, instead of specializing `is_char_array_to_stdstring` for `boost::container::basic_string`.
        template<typename Target, typename Source>
        struct is_char_array_to_booststring
            : boost::false_type
        {};

        template<typename CharT, typename Traits, typename Alloc>
        struct is_char_array_to_booststring< boost::container::basic_string<CharT, Traits, Alloc>, CharT* >
            : boost::true_type
        {};

        template<typename CharT, typename Traits, typename Alloc>
        struct is_char_array_to_booststring< boost::container::basic_string<CharT, Traits, Alloc>, const CharT* >
            : boost::true_type
        {};

        template <typename Target, typename Source>
        struct copy_converter_impl
        {
// MSVC fail to forward an array (DevDiv#555157 "SILENT BAD CODEGEN triggered by perfect forwarding",
// fixed in 2013 RTM).
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && (!defined(BOOST_MSVC) || BOOST_MSVC >= 1800)
            template <class T>
            static inline bool try_convert(T&& arg, Target& result) {
                result = static_cast<T&&>(arg); // eqaul to `result = std::forward<T>(arg);`
                return true;
            }
#else
            static inline bool try_convert(const Source& arg, Target& result) {
                result = arg;
                return true;
            }
#endif
        };
    }

    namespace conversion { namespace detail {

        template <typename Target, typename Source>
        inline bool try_lexical_convert(const Source& arg, Target& result)
        {
            typedef BOOST_DEDUCED_TYPENAME boost::detail::array_to_pointer_decay<Source>::type src;

            typedef boost::integral_constant<
                bool,
                boost::detail::is_xchar_to_xchar<Target, src >::value ||
                boost::detail::is_char_array_to_stdstring<Target, src >::value ||
                boost::detail::is_char_array_to_booststring<Target, src >::value ||
                (
                     boost::is_same<Target, src >::value &&
                     (boost::detail::is_stdstring<Target >::value || boost::detail::is_booststring<Target >::value)
                ) ||
                (
                     boost::is_same<Target, src >::value &&
                     boost::detail::is_character<Target >::value
                )
            > shall_we_copy_t;

            typedef boost::detail::is_arithmetic_and_not_xchars<Target, src >
                shall_we_copy_with_dynamic_check_t;

            // We do evaluate second `if_` lazily to avoid unnecessary instantiations
            // of `shall_we_copy_with_dynamic_check_t` and improve compilation times.
            typedef BOOST_DEDUCED_TYPENAME boost::conditional<
                shall_we_copy_t::value,
                boost::type_identity<boost::detail::copy_converter_impl<Target, src > >,
                boost::conditional<
                     shall_we_copy_with_dynamic_check_t::value,
                     boost::detail::dynamic_num_converter_impl<Target, src >,
                     boost::detail::lexical_converter_impl<Target, src >
                >
            >::type caster_type_lazy;

            typedef BOOST_DEDUCED_TYPENAME caster_type_lazy::type caster_type;

            return caster_type::try_convert(arg, result);
        }

        template <typename Target, typename CharacterT>
        inline bool try_lexical_convert(const CharacterT* chars, std::size_t count, Target& result)
        {
            BOOST_STATIC_ASSERT_MSG(
                boost::detail::is_character<CharacterT>::value,
                "This overload of try_lexical_convert is meant to be used only with arrays of characters."
            );
            return ::boost::conversion::detail::try_lexical_convert(
                ::boost::iterator_range<const CharacterT*>(chars, chars + count), result
            );
        }

    }} // namespace conversion::detail

    namespace conversion {
        // ADL barrier
        using ::boost::conversion::detail::try_lexical_convert;
    }

} // namespace boost

#if defined(__clang__) || (defined(__GNUC__) && \
    !(defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)) && \
    (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)))
#pragma GCC diagnostic pop
#endif

#endif // BOOST_LEXICAL_CAST_TRY_LEXICAL_CONVERT_HPP


/* try_lexical_convert.hpp
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
*/