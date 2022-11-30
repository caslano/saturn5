//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_CHAR_CLASS_AUG_10_2009_0720AM)
#define BOOST_SPIRIT_KARMA_CHAR_CLASS_AUG_10_2009_0720AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/string_traits.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/char_class.hpp>
#include <boost/spirit/home/support/detail/get_encoding.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/char/char_generator.hpp>
#include <boost/spirit/home/karma/auxiliary/lazy.hpp>
#include <boost/spirit/home/karma/detail/get_casetag.hpp>
#include <boost/spirit/home/karma/detail/generate_to.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit 
{ 
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    // enables alnum, alpha, graph, etc.
    template <typename CharClass, typename CharEncoding>
    struct use_terminal<karma::domain
        , tag::char_code<CharClass, CharEncoding> >
      : mpl::true_ {};

}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
    // hoist the char classification namespaces into karma sub-namespaces of 
    // the same name
    namespace ascii { using namespace boost::spirit::ascii; }
    namespace iso8859_1 { using namespace boost::spirit::iso8859_1; }
    namespace standard { using namespace boost::spirit::standard; }
    namespace standard_wide { using namespace boost::spirit::standard_wide; }
#if defined(BOOST_SPIRIT_UNICODE)
    namespace unicode { using namespace boost::spirit::unicode; }
#endif

    // Import the standard namespace into the karma namespace. This allows 
    // for default handling of all character/string related operations if not 
    // prefixed with a character set namespace.
    using namespace boost::spirit::standard;

    // Import encoding
    using spirit::encoding;

    ///////////////////////////////////////////////////////////////////////////
    //
    //  char_class
    //      generates a single character if it matches the given character 
    //      class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename Tag, typename CharEncoding, typename CharClass>
    struct char_class
      : char_generator<
            char_class<Tag, CharEncoding, CharClass>
          , CharEncoding, CharClass>
    {
        typedef typename Tag::char_encoding char_encoding;
        typedef typename char_encoding::char_type char_type;
        typedef typename Tag::char_class classification;

        template <typename Context, typename Unused>
        struct attribute
        {
            typedef char_type type;
        };

        // char_class needs an attached attribute
        template <typename Attribute, typename CharParam, typename Context>
        bool test(Attribute const& attr, CharParam& ch, Context&) const
        {
            ch = attr;

            using spirit::char_class::classify;
            return classify<char_encoding>::is(classification(), attr);
        }

        // char_class shouldn't be used without any associated attribute
        template <typename CharParam, typename Context>
        bool test(unused_type, CharParam&, Context&) const
        {
            // It is not possible (doesn't make sense) to use char_ generators
            // without providing any attribute, as the generator doesn't 'know'
            // what to output. The following assertion fires if this situation
            // is detected in your code.
            BOOST_SPIRIT_ASSERT_FAIL(CharParam
              , char_class_not_usable_without_attribute, ());
            return false;
        }

        template <typename Context>
        static info what(Context const& /*context*/)
        {
            typedef spirit::char_class::what<char_encoding> what_;
            return info(what_::is(classification()));
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  space
    //      generates a single character from the associated parameter
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharEncoding>
    struct any_space
      : char_generator<any_space<CharEncoding>, CharEncoding, tag::space>
    {
        typedef typename CharEncoding::char_type char_type;
        typedef CharEncoding char_encoding;

        template <typename Context, typename Unused>
        struct attribute
        {
            typedef char_type type;
        };

        // any_space has an attached parameter
        template <typename Attribute, typename CharParam, typename Context>
        bool test(Attribute const& attr, CharParam& ch, Context&) const
        {
            ch = CharParam(attr);

            using spirit::char_class::classify;
            return classify<char_encoding>::is(tag::space(), attr);
        }

        // any_space has no attribute attached, use single space character
        template <typename CharParam, typename Context>
        bool test(unused_type, CharParam& ch, Context&) const
        {
            ch = ' ';
            return true;
        }

        template <typename Context>
        static info what(Context const& /*context*/)
        {
            return info("space");
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////

    namespace detail
    {
        template <typename Tag, bool lower = false, bool upper = false>
        struct make_char_class : mpl::identity<Tag> {};

        template <>
        struct make_char_class<tag::alpha, true, false> 
          : mpl::identity<tag::lower> {};

        template <>
        struct make_char_class<tag::alpha, false, true> 
          : mpl::identity<tag::upper> {};

        template <>
        struct make_char_class<tag::alnum, true, false> 
          : mpl::identity<tag::lowernum> {};

        template <>
        struct make_char_class<tag::alnum, false, true> 
          : mpl::identity<tag::uppernum> {};
    }

    // enables alnum, alpha, graph, etc.
    template <typename CharClass, typename CharEncoding, typename Modifiers>
    struct make_primitive<tag::char_code<CharClass, CharEncoding>, Modifiers>
    {
        static bool const lower = 
            has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
        static bool const upper = 
            has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

        typedef tag::char_code<
            typename detail::make_char_class<CharClass, lower, upper>::type
          , CharEncoding>
        tag_type;

        typedef char_class<
            tag_type
          , typename spirit::detail::get_encoding_with_case<
                Modifiers, CharEncoding, lower || upper>::type
          , typename detail::get_casetag<Modifiers, lower || upper>::type
        > result_type;

        result_type operator()(unused_type, unused_type) const
        {
            return result_type();
        }
    };

    // space is special
    template <typename CharEncoding, typename Modifiers>
    struct make_primitive<tag::char_code<tag::space, CharEncoding>, Modifiers>
    {
        typedef any_space<CharEncoding> result_type;

        result_type operator()(unused_type, unused_type) const
        {
            return result_type();
        }
    };

}}}  // namespace boost::spirit::karma

#endif // !defined(BOOST_SPIRIT_KARMA_CHAR_FEB_21_2007_0543PM)

/* char_class.hpp
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
*/