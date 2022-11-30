/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser
    Copyright (c)      2010 Bryce Lelbach

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_CHAR_APRIL_16_2006_1051AM)
#define BOOST_SPIRIT_CHAR_APRIL_16_2006_1051AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/string_traits.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/detail/get_encoding.hpp>
#include <boost/spirit/home/support/char_set/basic_chset.hpp>
#include <boost/spirit/home/qi/char/char_parser.hpp>
#include <boost/spirit/home/qi/char/char_class.hpp>
#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/qi/auxiliary/lazy.hpp>
#include <boost/spirit/home/qi/detail/enable_lit.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <string>

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharEncoding>
    struct use_terminal<qi::domain
      , terminal<
            tag::char_code<tag::char_, CharEncoding>    // enables char_
        >
    > : mpl::true_ {};

    template <typename CharEncoding, typename A0>
    struct use_terminal<qi::domain
      , terminal_ex<
            tag::char_code<tag::char_, CharEncoding>    // enables char_('x'), char_("x")
          , fusion::vector1<A0>                         // and char_("a-z0-9")
        >
    > : mpl::true_ {};

    template <typename CharEncoding, typename A0, typename A1>
    struct use_terminal<qi::domain
      , terminal_ex<
            tag::char_code<tag::char_, CharEncoding>    // enables char_('a','z')
          , fusion::vector2<A0, A1>
        >
    > : mpl::true_ {};

    template <typename CharEncoding>                    // enables *lazy* char_('x'), char_("x")
    struct use_lazy_terminal<                           // and char_("a-z0-9")
        qi::domain
      , tag::char_code<tag::char_, CharEncoding>
      , 1 // arity
    > : mpl::true_ {};

    template <typename CharEncoding>                    // enables *lazy* char_('a','z')
    struct use_lazy_terminal<
        qi::domain
      , tag::char_code<tag::char_, CharEncoding>
      , 2 // arity
    > : mpl::true_ {};

    template <>
    struct use_terminal<qi::domain, char>               // enables 'x'
      : mpl::true_ {};

    template <>
    struct use_terminal<qi::domain, char[2]>            // enables "x"
      : mpl::true_ {};

    template <>
    struct use_terminal<qi::domain, wchar_t>            // enables wchar_t
      : mpl::true_ {};

    template <>
    struct use_terminal<qi::domain, wchar_t[2]>         // enables L"x"
      : mpl::true_ {};

    // enables lit(...)
    template <typename A0>
    struct use_terminal<qi::domain
          , terminal_ex<tag::lit, fusion::vector1<A0> >
          , typename enable_if<traits::is_char<A0> >::type>
      : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace qi
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::lit; // lit('x') is equivalent to 'x'
#endif
    using spirit::lit_type;

    ///////////////////////////////////////////////////////////////////////////
    // Parser for a single character
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharEncoding, bool no_attribute, bool no_case = false>
    struct literal_char
      : char_parser<
            literal_char<CharEncoding, no_attribute, false>
          , typename CharEncoding::char_type
          , typename mpl::if_c<no_attribute, unused_type
              , typename CharEncoding::char_type>::type>
    {
        typedef typename CharEncoding::char_type char_type;
        typedef CharEncoding char_encoding;

        template <typename Char>
        literal_char(Char ch_)
          : ch(static_cast<char_type>(ch_)) {}

        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef typename mpl::if_c<
                no_attribute, unused_type, char_type>::type
            type;
        };

        template <typename CharParam, typename Context>
        bool test(CharParam ch_, Context&) const
        {
            return traits::ischar<CharParam, char_encoding>::call(ch_) &&
                   ch == char_type(ch_);
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("literal-char", char_encoding::toucs4(ch));
        }

        char_type ch;
    };

    template <typename CharEncoding, bool no_attribute>
    struct literal_char<CharEncoding, no_attribute, true> // case insensitive
      : char_parser<
            literal_char<CharEncoding, no_attribute, true>
          , typename mpl::if_c<no_attribute, unused_type
              , typename CharEncoding::char_type>::type>
    {
        typedef typename CharEncoding::char_type char_type;
        typedef CharEncoding char_encoding;

        literal_char(char_type ch)
          : lo(static_cast<char_type>(char_encoding::tolower(ch)))
          , hi(static_cast<char_type>(char_encoding::toupper(ch))) {}

        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef typename mpl::if_c<
                no_attribute, unused_type, char_type>::type
            type;
        };

        template <typename CharParam, typename Context>
        bool test(CharParam ch_, Context&) const
        {
            if (!traits::ischar<CharParam, char_encoding>::call(ch_))
                return false;

            char_type ch = char_type(ch_);  // optimize for token based parsing
            return this->lo == ch || this->hi == ch;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("no-case-literal-char", char_encoding::toucs4(lo));
        }

        char_type lo, hi;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser for a character range
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharEncoding, bool no_case = false>
    struct char_range
      : char_parser<char_range<CharEncoding, false>, typename CharEncoding::char_type>
    {
        typedef typename CharEncoding::char_type char_type;
        typedef CharEncoding char_encoding;

        char_range(char_type from_, char_type to_)
          : from(from_), to(to_) {}

        template <typename CharParam, typename Context>
        bool test(CharParam ch_, Context&) const
        {
            if (!traits::ischar<CharParam, char_encoding>::call(ch_))
                return false;

            char_type ch = char_type(ch_);  // optimize for token based parsing
            return !(ch < from) && !(to < ch);
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            info result("char-range", char_encoding::toucs4(from));
            boost::get<std::string>(result.value) += '-';
            boost::get<std::string>(result.value) += to_utf8(char_encoding::toucs4(to));
            return result;
        }

        char_type from, to;
    };

    template <typename CharEncoding>
    struct char_range<CharEncoding, true> // case insensitive
      : char_parser<char_range<CharEncoding, true>, typename CharEncoding::char_type>
    {
        typedef typename CharEncoding::char_type char_type;
        typedef CharEncoding char_encoding;

        char_range(char_type from, char_type to)
          : from_lo(static_cast<char_type>(char_encoding::tolower(from)))
          , to_lo(static_cast<char_type>(char_encoding::tolower(to)))
          , from_hi(static_cast<char_type>(char_encoding::toupper(from)))
          , to_hi(static_cast<char_type>(char_encoding::toupper(to)))
        {}

        template <typename CharParam, typename Context>
        bool test(CharParam ch_, Context&) const
        {
            if (!traits::ischar<CharParam, char_encoding>::call(ch_))
                return false;

            char_type ch = char_type(ch_);  // optimize for token based parsing
            return (!(ch < from_lo) && !(to_lo < ch))
                || (!(ch < from_hi) && !(to_hi < ch))
            ;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            info result("no-case-char-range", char_encoding::toucs4(from_lo));
            boost::get<std::string>(result.value) += '-';
            boost::get<std::string>(result.value) += to_utf8(char_encoding::toucs4(to_lo));
            return result;
        }

        char_type from_lo, to_lo, from_hi, to_hi;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser for a character set
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharEncoding, bool no_attribute, bool no_case = false>
    struct char_set
      : char_parser<char_set<CharEncoding, no_attribute, false>
          , typename mpl::if_c<no_attribute, unused_type
              , typename CharEncoding::char_type>::type>
    {
        typedef typename CharEncoding::char_type char_type;
        typedef CharEncoding char_encoding;

        template <typename String>
        char_set(String const& str)
        {
            using spirit::detail::cast_char;

            typedef typename
                remove_const<
                    typename traits::char_type_of<String>::type
                >::type
            in_type;

            BOOST_SPIRIT_ASSERT_MSG((
                (sizeof(char_type) >= sizeof(in_type))
            ), cannot_convert_string, (String));

            in_type const* definition =
                (in_type const*)traits::get_c_string(str);
            in_type ch = *definition++;
            while (ch)
            {
                in_type next = *definition++;
                if (next == '-')
                {
                    next = *definition++;
                    if (next == 0)
                    {
                        chset.set(cast_char<char_type>(ch));
                        chset.set('-');
                        break;
                    }
                    chset.set(
                        cast_char<char_type>(ch),
                        cast_char<char_type>(next)
                    );
                }
                else
                {
                    chset.set(cast_char<char_type>(ch));
                }
                ch = next;
            }
        }

        template <typename CharParam, typename Context>
        bool test(CharParam ch, Context&) const
        {
            return traits::ischar<CharParam, char_encoding>::call(ch) &&
                   chset.test(char_type(ch));
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("char-set");
        }

        support::detail::basic_chset<char_type> chset;
    };

    template <typename CharEncoding, bool no_attribute>
    struct char_set<CharEncoding, no_attribute, true> // case insensitive
      : char_parser<char_set<CharEncoding, no_attribute, true>
          , typename mpl::if_c<no_attribute, unused_type
              , typename CharEncoding::char_type>::type>
    {
        typedef typename CharEncoding::char_type char_type;
        typedef CharEncoding char_encoding;

        template <typename String>
        char_set(String const& str)
        {
            typedef typename traits::char_type_of<String>::type in_type;

            BOOST_SPIRIT_ASSERT_MSG((
                (sizeof(char_type) == sizeof(in_type))
            ), cannot_convert_string, (String));

            char_type const* definition =
                (char_type const*)traits::get_c_string(str);
            char_type ch = *definition++;
            while (ch)
            {
                char_type next = *definition++;
                if (next == '-')
                {
                    next = *definition++;
                    if (next == 0)
                    {
                        chset.set(static_cast<char_type>(CharEncoding::tolower(ch)));
                        chset.set(static_cast<char_type>(CharEncoding::toupper(ch)));
                        chset.set('-');
                        break;
                    }
                    chset.set(static_cast<char_type>(CharEncoding::tolower(ch))
                      , static_cast<char_type>(CharEncoding::tolower(next)));
                    chset.set(static_cast<char_type>(CharEncoding::toupper(ch))
                      , static_cast<char_type>(CharEncoding::toupper(next)));
                }
                else
                {
                    chset.set(static_cast<char_type>(CharEncoding::tolower(ch)));
                    chset.set(static_cast<char_type>(CharEncoding::toupper(ch)));
                }
                ch = next;
            }
        }

        template <typename CharParam, typename Context>
        bool test(CharParam ch, Context&) const
        {
            return traits::ischar<CharParam, char_encoding>::call(ch) &&
                   chset.test(char_type(ch));
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("no-case-char-set");
        }

        support::detail::basic_chset<char_type> chset;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename Modifiers, typename Encoding>
        struct basic_literal
        {
            static bool const no_case =
                has_modifier<
                    Modifiers
                  , tag::char_code_base<tag::no_case>
                >::value;

            static bool const no_attr =
                !has_modifier<
                    Modifiers
                  , tag::lazy_eval
                >::value;

            typedef literal_char<
                typename spirit::detail::get_encoding_with_case<
                    Modifiers, Encoding, no_case>::type
              , no_attr
              , no_case>
            result_type;

            template <typename Char>
            result_type operator()(Char ch, unused_type) const
            {
                return result_type(ch);
            }

            template <typename Char>
            result_type operator()(Char const* str, unused_type) const
            {
                return result_type(str[0]);
            }
        };
    }

    template <typename Modifiers>
    struct make_primitive<char, Modifiers>
      : detail::basic_literal<Modifiers, char_encoding::standard> {};

    template <typename Modifiers>
    struct make_primitive<char const(&)[2], Modifiers>
      : detail::basic_literal<Modifiers, char_encoding::standard> {};

    template <typename Modifiers>
    struct make_primitive<wchar_t, Modifiers>
      : detail::basic_literal<Modifiers, char_encoding::standard_wide> {};

    template <typename Modifiers>
    struct make_primitive<wchar_t const(&)[2], Modifiers>
      : detail::basic_literal<Modifiers, char_encoding::standard_wide> {};

    template <typename CharEncoding, typename Modifiers>
    struct make_primitive<
        terminal<tag::char_code<tag::char_, CharEncoding> >, Modifiers>
    {
        typedef typename
            spirit::detail::get_encoding<Modifiers, CharEncoding>::type
        char_encoding;

        typedef tag::char_code<tag::char_, char_encoding> tag;
        typedef char_class<tag> result_type;
        result_type operator()(unused_type, unused_type) const
        {
            return result_type();
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // char_('x')
    template <typename CharEncoding, typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<
            tag::char_code<tag::char_, CharEncoding>
          , fusion::vector1<A0> >
      , Modifiers>
    {
        static bool const no_case =
            has_modifier<Modifiers, tag::char_code_base<tag::no_case> >::value;

        typedef typename
            spirit::detail::get_encoding<Modifiers, CharEncoding>::type
        char_encoding;

        typedef typename
            mpl::if_<
                traits::is_string<A0>
              , char_set<char_encoding, false, no_case>
              , literal_char<char_encoding, false, no_case>
            >::type
        result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args));
        }
    };

    // lit('x')
    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::lit, fusion::vector1<A0> >
      , Modifiers
      , typename enable_if<traits::is_char<A0> >::type>
    {
        static bool const no_case =
            has_modifier<
                Modifiers
              , tag::char_code_base<tag::no_case>
            >::value;

        typedef typename traits::char_encoding_from_char<
                typename traits::char_type_of<A0>::type>::type encoding;

        typedef literal_char<
            typename spirit::detail::get_encoding_with_case<
                Modifiers, encoding, no_case>::type
          , true, no_case>
        result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args));
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename CharEncoding, typename Modifiers, typename Char>
    struct make_primitive<
        terminal_ex<
            tag::char_code<tag::char_, CharEncoding>
          , fusion::vector1<Char(&)[2]> // For single char strings
        >
      , Modifiers>
    {
        static bool const no_case =
            has_modifier<Modifiers, tag::char_code_base<tag::no_case> >::value;

        typedef typename
            spirit::detail::get_encoding<Modifiers, CharEncoding>::type
        char_encoding;

        typedef literal_char<char_encoding, false, no_case> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args)[0]);
        }
    };

    template <typename CharEncoding, typename Modifiers, typename A0, typename A1>
    struct make_primitive<
        terminal_ex<
            tag::char_code<tag::char_, CharEncoding>
          , fusion::vector2<A0, A1>
        >
      , Modifiers>
    {
        static bool const no_case =
            has_modifier<Modifiers, tag::char_code_base<tag::no_case> >::value;

        typedef typename
            spirit::detail::get_encoding<Modifiers, CharEncoding>::type
        char_encoding;

        typedef char_range<char_encoding, no_case> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(
                fusion::at_c<0>(term.args)
              , fusion::at_c<1>(term.args)
            );
        }
    };

    template <typename CharEncoding, typename Modifiers, typename Char>
    struct make_primitive<
        terminal_ex<
            tag::char_code<tag::char_, CharEncoding>
          , fusion::vector2<Char(&)[2], Char(&)[2]> // For single char strings
        >
      , Modifiers>
    {
        static bool const no_case =
            has_modifier<Modifiers, tag::char_code_base<tag::no_case> >::value;

        typedef typename
            spirit::detail::get_encoding<Modifiers, CharEncoding>::type
        char_encoding;

        typedef char_range<char_encoding, no_case> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(
                fusion::at_c<0>(term.args)[0]
              , fusion::at_c<1>(term.args)[0]
            );
        }
    };
}}}

#endif

/* char.hpp
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
*/