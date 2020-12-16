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
ANJMH63zleccqjXqm4i2TMS9tsXivXW/8O5NmkVEhkRExsSg3jitcpBpRYIEd5nYbseJQm9/Fa5CRd7t0tJKU2CX4Ri53lXyF8l3AnnW1pSSP9q+noJ4qPDYX9/xqC957Mq7KGY4gJnakncV7rwrLC/DJXfe2eWqlPStVbxZr0J6Dr/1RVp5xdf9OskPOSfdVS80lnYhIxCaIByJ0Bt5t7qVfzK+CWhmlz3Ptsd4TNINVVFiHeEwlZ20HFr+SbYu5Cm5dhhaYz/ICUGm8Yb8vvcI+FiuN7N1HGGLrHhwvXsvRLrwKk/iYXZ8kvDtQ/JteLqS+M9aXN+HI5/782XwBt3Jx+RFHnzMKckrtTplQWmZ0nlq25+kSJ40lWLuC6DpwU/Jaw2FVLmWqpKQ08BL5PWvH/nDm+GLzLwYQEZvZ596GeEY5Mt150VxyakaM7S5u7xYxhL7yHTJ94Q6ErWfhrASd9tg5g3v4dDG2ZTS4pl1+5sUyPXn1bHWCERYjXAHgievSItz9bQmiIdyro6M8pir45nmjNDavfmCOzYJimgS6XJtufPaHP2avW+IhJva+LdviKVru3ORu66NzwLyL0ZvM/LBarelbLfD2ac/cIv/xvgRbnsqVTS1fT/L9VMRTgDtksWu7TqltED2TGlmt+dc0KX+V9KWqxiZr5kXFJPUeJv3PO+pS2eeS+TaRGmXTFRwD8JylCOi+Vi7XdKi+QxlmlSU/b42VruEp4d3bNIkIiwUjRAazvTWM0fSO59FMWin5ijMKj/2F4l04f1cxp3P4ELh6Q1SZsyvNk9b1D57uXdiT/L0YPI06lIPnuLZW27kaZykTTeNB9JxKL2evt4rjPVB+VMuZfnd+sTnzVz7ZyjCmm4YK27ln1pQnmF4/pnKjLz1zlFH+vNsXhtex1tF3o5A+UsMZcvJGu757sj5uFzSZ6iOoG0qb4kLj+vdQ8vru5u+t9W0iNrEXZmpC8LxSXgWGss+ehAuG8tvEXtU8nRU+3sp/9a/oPyp3MMQ7+v2c3Ecyq8qDOUfOiQHv72WP0TypKkO5vKDZuOX/2OWP5WZOiHkovyZpvIf65v/WZKng2rtpfyZf0H5k1vUvdMrvtOPTAdtU/mnzcyb7OPddL5v/gtNPnP5rbN8gGp8puppD5GSFpcp7V2uSq6Hy9z+OdpgWySeM20wtwd3k/nZTx55exfmM5HfyrKc+pyRSorDOB8P5ZxR7cm3g4xzBufk7ZI+Q6UZ34lJj3xIT9LfaSmvXib7XonclIK2fB9hC/gQ7sBjq00MHmDBB+i80Hlzf5v6n1n19Z+e3FtvIPkwgPNPxmUmPnjr/9xbT/J0Uh2MvCBN8kLFefJivMaLNNSqBiG/lZMXTX3y4oFG4EVmDA2FyYvBnMvmGXjBucwrL86XPN1UZyMvSJO8yDD0izs0XvQB/V8QMuLIi7YRFi/ae+PFg43Ai6Na1ibuR1705by4y8SLY333iw8kT4pK9rY3nMaL4wz9oumSOl5koY3CULYpzn6RKP0iyRsvtu4FL4aRF2ti+Wxgpo4Ix6SjPZYYeFFeVGZtXFycX5BfUlw4q9yTL7b+qKfkb2XiCWnr30eUlJhtV+y0Rt8H0cCRcj3UlpvHSDxYWfJKNmgPR/0esuYc1cRS0wj//J1zDTop2slLeeWdcsQS7nXfyZWv1XGefB2OSK4nX7HX+5S82UXAwqkFZeU5s6Ce8voely/5O4CzRh0g6eu2PiWgZ+Yt0wqv1oJP5XGNyyux4+H9LV6drvFK199Mi+d7dy3gCvVPbrwqzPfv3btiSb3v3j71YoOdz4+E2sRtmKk1y7XarVwzC8vKoADW1QAsp2f7rZE=
*/