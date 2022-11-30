//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c)      2010 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_CHAR_FEB_21_2007_0543PM)
#define BOOST_SPIRIT_KARMA_CHAR_FEB_21_2007_0543PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/string_traits.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/char_class.hpp>
#include <boost/spirit/home/support/detail/get_encoding.hpp>
#include <boost/spirit/home/support/char_set/basic_chset.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/char/char_generator.hpp>
#include <boost/spirit/home/karma/auxiliary/lazy.hpp>
#include <boost/spirit/home/karma/detail/get_casetag.hpp>
#include <boost/spirit/home/karma/detail/generate_to.hpp>
#include <boost/spirit/home/karma/detail/enable_lit.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/cons.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>
#include <string>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharEncoding>
    struct use_terminal<karma::domain
      , tag::char_code<tag::char_, CharEncoding>        // enables char_
    > : mpl::true_ {};

    template <typename CharEncoding, typename A0>
    struct use_terminal<karma::domain
      , terminal_ex<
            tag::char_code<tag::char_, CharEncoding>    // enables char_('x'), char_("x")
          , fusion::vector1<A0>
        >
    > : mpl::true_ {};

    template <typename A0>
    struct use_terminal<karma::domain
          , terminal_ex<tag::lit, fusion::vector1<A0> > // enables lit('x')
          , typename enable_if<traits::is_char<A0> >::type>
      : mpl::true_ {};

    template <typename CharEncoding, typename A0, typename A1>
    struct use_terminal<karma::domain
      , terminal_ex<
            tag::char_code<tag::char_, CharEncoding>    // enables char_('a','z')
          , fusion::vector2<A0, A1>
        >
    > : mpl::true_ {};

    template <typename CharEncoding>                    // enables *lazy* char_('x'), char_("x")
    struct use_lazy_terminal<
        karma::domain
      , tag::char_code<tag::char_, CharEncoding>
      , 1 // arity
    > : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, char>            // enables 'x'
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, char[2]>         // enables "x"
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, wchar_t>         // enables L'x'
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, wchar_t[2]>      // enables L"x"
      : mpl::true_ {};
}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::lit;    // lit('x') is equivalent to 'x'
#endif
    using spirit::lit_type;

    ///////////////////////////////////////////////////////////////////////////
    //
    //  any_char
    //      generates a single character from the associated attribute
    //
    //      Note: this generator has to have an associated attribute
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharEncoding, typename Tag>
    struct any_char
      : char_generator<any_char<CharEncoding, Tag>, CharEncoding, Tag>
    {
        typedef typename CharEncoding::char_type char_type;
        typedef CharEncoding char_encoding;

        template <typename Context, typename Unused>
        struct attribute
        {
            typedef char_type type;
        };

        // any_char has an attached parameter
        template <typename Attribute, typename CharParam, typename Context>
        bool test(Attribute const& attr, CharParam& ch, Context&) const
        {
            ch = CharParam(attr);
            return true;
        }

        // any_char has no attribute attached, it needs to have been
        // initialized from a direct literal
        template <typename CharParam, typename Context>
        bool test(unused_type, CharParam&, Context&) const
        {
            // It is not possible (doesn't make sense) to use char_ without
            // providing any attribute, as the generator doesn't 'know' what
            // character to output. The following assertion fires if this
            // situation is detected in your code.
            BOOST_SPIRIT_ASSERT_FAIL(CharParam, char_not_usable_without_attribute, ());
            return false;
        }

        template <typename Context>
        static info what(Context const& /*context*/)
        {
            return info("any-char");
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  literal_char
    //      generates a single character given by a literal it was initialized
    //      from
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharEncoding, typename Tag, bool no_attribute>
    struct literal_char
      : char_generator<literal_char<CharEncoding, Tag, no_attribute>
          , CharEncoding, Tag>
    {
        typedef typename CharEncoding::char_type char_type;
        typedef CharEncoding char_encoding;

        literal_char(char_type ch)
          : ch (spirit::char_class::convert<char_encoding>::to(Tag(), ch)) 
        {}

        template <typename Context, typename Unused>
        struct attribute
          : mpl::if_c<no_attribute, unused_type, char_type>
        {};

        // A char_('x') which additionally has an associated attribute emits
        // its immediate literal only if it matches the attribute, otherwise
        // it fails.
        // any_char has an attached parameter
        template <typename Attribute, typename CharParam, typename Context>
        bool test(Attribute const& attr, CharParam& ch_, Context&) const
        {
            // fail if attribute isn't matched my immediate literal
            ch_ = static_cast<char_type>(attr);
            return attr == ch;
        }

        // A char_('x') without any associated attribute just emits its 
        // immediate literal
        template <typename CharParam, typename Context>
        bool test(unused_type, CharParam& ch_, Context&) const
        {
            ch_ = ch;
            return true;
        }

        template <typename Context>
        info what(Context const& /*context*/) const
        {
            return info("literal-char", char_encoding::toucs4(ch));
        }

        char_type ch;
    };

    ///////////////////////////////////////////////////////////////////////////
    // char range generator
    template <typename CharEncoding, typename Tag>
    struct char_range
      : char_generator<char_range<CharEncoding, Tag>, CharEncoding, Tag>
    {
        typedef typename CharEncoding::char_type char_type;
        typedef CharEncoding char_encoding;

        char_range(char_type from, char_type to)
          : from(spirit::char_class::convert<char_encoding>::to(Tag(), from))
          , to(spirit::char_class::convert<char_encoding>::to(Tag(), to)) 
        {}

        // A char_('a', 'z') which has an associated attribute emits it only if 
        // it matches the character range, otherwise it fails.
        template <typename Attribute, typename CharParam, typename Context>
        bool test(Attribute const& attr, CharParam& ch, Context&) const
        {
            // fail if attribute doesn't belong to character range
            ch = attr;
            return (from <= char_type(attr)) && (char_type(attr) <= to);
        }

        // A char_('a', 'z') without any associated attribute fails compiling
        template <typename CharParam, typename Context>
        bool test(unused_type, CharParam&, Context&) const
        {
            // It is not possible (doesn't make sense) to use char_ generators
            // without providing any attribute, as the generator doesn't 'know'
            // what to output. The following assertion fires if this situation
            // is detected in your code.
            BOOST_SPIRIT_ASSERT_FAIL(CharParam
              , char_range_not_usable_without_attribute, ());
            return false;
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

    ///////////////////////////////////////////////////////////////////////////
    // character set generator
    template <typename CharEncoding, typename Tag, bool no_attribute>
    struct char_set
      : char_generator<char_set<CharEncoding, Tag, no_attribute>
          , CharEncoding, Tag>
    {
        typedef typename CharEncoding::char_type char_type;
        typedef CharEncoding char_encoding;

        template <typename Context, typename Unused>
        struct attribute
          : mpl::if_c<no_attribute, unused_type, char_type>
        {};

        template <typename String>
        char_set(String const& str)
        {
            typedef typename traits::char_type_of<String>::type in_type;

            BOOST_SPIRIT_ASSERT_MSG((
                (sizeof(char_type) == sizeof(in_type))
            ), cannot_convert_string, (String));

            typedef spirit::char_class::convert<char_encoding> convert_type;

            char_type const* definition =
                (char_type const*)traits::get_c_string(str);
            char_type ch = convert_type::to(Tag(), *definition++);
            while (ch)
            {
                char_type next = convert_type::to(Tag(), *definition++);
                if (next == '-')
                {
                    next = convert_type::to(Tag(), *definition++);
                    if (next == 0)
                    {
                        chset.set(ch);
                        chset.set('-');
                        break;
                    }
                    chset.set(ch, next);
                }
                else
                {
                    chset.set(ch);
                }
                ch = next;
            }
        }

        // A char_("a-z") which has an associated attribute emits it only if 
        // it matches the character set, otherwise it fails.
        template <typename Attribute, typename CharParam, typename Context>
        bool test(Attribute const& attr, CharParam& ch, Context&) const
        {
            // fail if attribute doesn't belong to character set
            ch = attr;
            return chset.test(char_type(attr));
        }

        // A char_("a-z") without any associated attribute fails compiling
        template <typename CharParam, typename Context>
        bool test(unused_type, CharParam&, Context&) const
        {
            // It is not possible (doesn't make sense) to use char_ generators
            // without providing any attribute, as the generator doesn't 'know'
            // what to output. The following assertion fires if this situation
            // is detected in your code.
            BOOST_SPIRIT_ASSERT_FAIL(CharParam
               , char_set_not_usable_without_attribute, ());
            return false;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("char-set");
        }

        support::detail::basic_chset<char_type> chset;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename Modifiers, typename Encoding>
        struct basic_literal
        {
            static bool const lower =
                has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
            static bool const upper =
                has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

            typedef literal_char<
                typename spirit::detail::get_encoding_with_case<
                    Modifiers, Encoding, lower || upper>::type
              , typename get_casetag<Modifiers, lower || upper>::type
              , true>
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

    // literals: 'x', "x"
    template <typename Modifiers>
    struct make_primitive<char, Modifiers>
      : detail::basic_literal<Modifiers, char_encoding::standard> {};

    template <typename Modifiers>
    struct make_primitive<char const(&)[2], Modifiers>
      : detail::basic_literal<Modifiers, char_encoding::standard> {};

    // literals: L'x', L"x"
    template <typename Modifiers>
    struct make_primitive<wchar_t, Modifiers>
      : detail::basic_literal<Modifiers, char_encoding::standard_wide> {};

    template <typename Modifiers>
    struct make_primitive<wchar_t const(&)[2], Modifiers>
      : detail::basic_literal<Modifiers, char_encoding::standard_wide> {};

    // char_
    template <typename CharEncoding, typename Modifiers>
    struct make_primitive<tag::char_code<tag::char_, CharEncoding>, Modifiers>
    {
        static bool const lower =
            has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
        static bool const upper =
            has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

        typedef any_char<
            typename spirit::detail::get_encoding_with_case<
                Modifiers, CharEncoding, lower || upper>::type
          , typename detail::get_casetag<Modifiers, lower || upper>::type
        > result_type;

        result_type operator()(unused_type, unused_type) const
        {
            return result_type();
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename CharEncoding, typename Modifiers, typename A0
          , bool no_attribute>
        struct make_char_direct
        {
            static bool const lower =
                has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
            static bool const upper =
                has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

            typedef typename spirit::detail::get_encoding_with_case<
                Modifiers, CharEncoding, lower || upper>::type encoding;
            typedef typename detail::get_casetag<
                Modifiers, lower || upper>::type tag;

            typedef typename mpl::if_<
                traits::is_string<A0>
              , char_set<encoding, tag, no_attribute>
              , literal_char<encoding, tag, no_attribute>
            >::type result_type;

            template <typename Terminal>
            result_type operator()(Terminal const& term, unused_type) const
            {
                return result_type(fusion::at_c<0>(term.args));
            }
        };
    }

    // char_(...), lit(...)
    template <typename CharEncoding, typename Modifiers, typename A0>
    struct make_primitive<
            terminal_ex<
                tag::char_code<tag::char_, CharEncoding>
              , fusion::vector1<A0> >
          , Modifiers>
      : detail::make_char_direct<CharEncoding, Modifiers, A0, false>
    {};

    template <typename Modifiers, typename A0>
    struct make_primitive<
            terminal_ex<tag::lit, fusion::vector1<A0> >
          , Modifiers
          , typename enable_if<traits::is_char<A0> >::type>
      : detail::make_char_direct<
            typename traits::char_encoding_from_char<
                typename traits::char_type_of<A0>::type>::type
          , Modifiers, A0, true>
    {};

    ///////////////////////////////////////////////////////////////////////////
    // char_("x")
    template <typename CharEncoding, typename Modifiers, typename Char>
    struct make_primitive<
        terminal_ex<
            tag::char_code<tag::char_, CharEncoding>
          , fusion::vector1<Char(&)[2]> > // For single char strings
      , Modifiers>
    {
        static bool const lower =
            has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
        static bool const upper =
            has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

        typedef literal_char<
            typename spirit::detail::get_encoding_with_case<
                Modifiers, CharEncoding, lower || upper>::type
          , typename detail::get_casetag<Modifiers, lower || upper>::type
          , false
        > result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args)[0]);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // char_('a', 'z')
    template <typename CharEncoding, typename Modifiers, typename A0, typename A1>
    struct make_primitive<
        terminal_ex<
            tag::char_code<tag::char_, CharEncoding>
          , fusion::vector2<A0, A1>
        >
      , Modifiers>
    {
        static bool const lower =
            has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
        static bool const upper =
            has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

        typedef char_range<
            typename spirit::detail::get_encoding_with_case<
                Modifiers, CharEncoding, lower || upper>::type
          , typename detail::get_casetag<Modifiers, lower || upper>::type
        > result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args)
              , fusion::at_c<1>(term.args));
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
        static bool const lower =
            has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
        static bool const upper =
            has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

        typedef char_range<
            typename spirit::detail::get_encoding_with_case<
                Modifiers, CharEncoding, lower || upper>::type
          , typename detail::get_casetag<Modifiers, lower || upper>::type
        > result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args)[0]
              , fusion::at_c<1>(term.args)[0]);
        }
    };
}}}   // namespace boost::spirit::karma

#endif

/* char.hpp
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
*/