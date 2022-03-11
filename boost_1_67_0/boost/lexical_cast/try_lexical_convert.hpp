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