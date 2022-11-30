/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_CHAR_CLASS_APRIL_16_2006_1051AM)
#define BOOST_SPIRIT_CHAR_CLASS_APRIL_16_2006_1051AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/qi/char/char_parser.hpp>
#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/support/char_class.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/modify.hpp>
#include <boost/spirit/home/support/detail/get_encoding.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    // enables alnum, alpha, graph, etc.
    template <typename CharClass, typename CharEncoding>
    struct use_terminal<qi::domain, tag::char_code<CharClass, CharEncoding> >
      : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace qi
{
    // hoist the char classification namespaces into qi sub-namespaces of the
    // same name
    namespace ascii { using namespace boost::spirit::ascii; }
    namespace iso8859_1 { using namespace boost::spirit::iso8859_1; }
    namespace standard { using namespace boost::spirit::standard; }
    namespace standard_wide { using namespace boost::spirit::standard_wide; }
#if defined(BOOST_SPIRIT_UNICODE)
    namespace unicode { using namespace boost::spirit::unicode; }
#endif

    // Import the standard namespace into the qi namespace. This allows
    // for default handling of all character/string related operations if not
    // prefixed with a character set namespace.
    using namespace boost::spirit::standard;

    // Import encoding
    using spirit::encoding;

    ///////////////////////////////////////////////////////////////////////////
    // Generic char classification parser (for alnum, alpha, graph, etc.)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Tag>
    struct char_class
      : char_parser<char_class<Tag>, typename Tag::char_encoding::char_type>
    {
        typedef typename Tag::char_encoding char_encoding;
        typedef typename Tag::char_class classification;

        template <typename CharParam, typename Context>
        bool test(CharParam ch, Context&) const
        {
            using spirit::char_class::classify;
            return traits::ischar<CharParam, char_encoding>::call(ch) &&
                   classify<char_encoding>::is(classification(), ch);
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            typedef spirit::char_class::what<char_encoding> what_;
            return info(what_::is(classification()));
        }
    };

    namespace detail
    {
        template <typename Tag, bool no_case = false>
        struct make_char_class : mpl::identity<Tag> {};

        template <>
        struct make_char_class<tag::lower, true> : mpl::identity<tag::alpha> {};

        template <>
        struct make_char_class<tag::upper, true> : mpl::identity<tag::alpha> {};
    }

    ///////////////////////////////////////////////////////////////////////////
    // Parser generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharClass, typename CharEncoding, typename Modifiers>
    struct make_primitive<tag::char_code<CharClass, CharEncoding>, Modifiers>
    {
        static bool const no_case =
            has_modifier<Modifiers, tag::char_code_base<tag::no_case> >::value;

        typedef typename
            spirit::detail::get_encoding<Modifiers, CharEncoding>::type
        char_encoding;

        typedef tag::char_code<
            typename detail::make_char_class<CharClass, no_case>::type
          , char_encoding>
        tag;

        typedef char_class<tag> result_type;
        result_type operator()(unused_type, unused_type) const
        {
            return result_type();
        }
    };
}}}

#endif

/* char_class.hpp
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
*/