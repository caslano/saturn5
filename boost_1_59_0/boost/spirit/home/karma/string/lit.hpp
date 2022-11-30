//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c)      2010 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_LIT_FEB_22_2007_0534PM)
#define BOOST_SPIRIT_KARMA_LIT_FEB_22_2007_0534PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/string_traits.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/char_class.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/support/detail/get_encoding.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/auxiliary/lazy.hpp>
#include <boost/spirit/home/karma/detail/get_casetag.hpp>
#include <boost/spirit/home/karma/detail/extract_from.hpp>
#include <boost/spirit/home/karma/detail/string_generate.hpp>
#include <boost/spirit/home/karma/detail/string_compare.hpp>
#include <boost/spirit/home/karma/detail/enable_lit.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/cons.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
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
        , tag::char_code<tag::string, CharEncoding> >     // enables string
      : mpl::true_ {};

    template <typename T>
    struct use_terminal<karma::domain, T
      , typename enable_if<traits::is_string<T> >::type>  // enables string literals
      : mpl::true_ {};

    template <typename CharEncoding, typename A0>
    struct use_terminal<karma::domain
      , terminal_ex<
            tag::char_code<tag::string, CharEncoding>     // enables string(str)
          , fusion::vector1<A0> >
    > : traits::is_string<A0> {};

    template <typename CharEncoding>                      // enables string(f)
    struct use_lazy_terminal<
        karma::domain
      , tag::char_code<tag::string, CharEncoding>
      , 1 /*arity*/
    > : mpl::true_ {};

    // enables lit(str)
    template <typename A0>
    struct use_terminal<karma::domain
          , terminal_ex<tag::lit, fusion::vector1<A0> >
          , typename enable_if<traits::is_string<A0> >::type>
      : mpl::true_ {};
}} 

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::lit;
#endif
    using spirit::lit_type;

    ///////////////////////////////////////////////////////////////////////////
    // generate literal strings from a given parameter
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharEncoding, typename Tag>
    struct any_string
      : primitive_generator<any_string<CharEncoding, Tag> >
    {
        typedef typename CharEncoding::char_type char_type;
        typedef CharEncoding char_encoding;

        template <typename Context, typename Unused = unused_type>
        struct attribute
        {
            typedef std::basic_string<char_type> type;
        };

        // lit has an attached attribute
        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        static bool
        generate(OutputIterator& sink, Context& context, Delimiter const& d, 
            Attribute const& attr)
        {
            if (!traits::has_optional_value(attr))
                return false;

            typedef typename attribute<Context>::type attribute_type;
            return 
                karma::detail::string_generate(sink
                  , traits::extract_from<attribute_type>(attr, context)
                  , char_encoding(), Tag()) &&
                karma::delimit_out(sink, d);      // always do post-delimiting
        }

        // this lit has no attribute attached, it needs to have been
        // initialized from a direct literal
        template <typename OutputIterator, typename Context, typename Delimiter>
        static bool generate(OutputIterator&, Context&, Delimiter const&, 
            unused_type const&)
        {
            // It is not possible (doesn't make sense) to use string without
            // providing any attribute, as the generator doesn't 'know' what
            // character to output. The following assertion fires if this
            // situation is detected in your code.
            BOOST_SPIRIT_ASSERT_FAIL(OutputIterator, string_not_usable_without_attribute, ());
            return false;
        }

        template <typename Context>
        static info what(Context const& /*context*/)
        {
            return info("any-string");
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // generate literal strings
    ///////////////////////////////////////////////////////////////////////////
    template <typename String, typename CharEncoding, typename Tag, bool no_attribute>
    struct literal_string
      : primitive_generator<literal_string<String, CharEncoding, Tag, no_attribute> >
    {
        typedef CharEncoding char_encoding;
        typedef typename
            remove_const<typename traits::char_type_of<String>::type>::type
        char_type;
        typedef std::basic_string<char_type> string_type;

        template <typename Context, typename Unused = unused_type>
        struct attribute
          : mpl::if_c<no_attribute, unused_type, string_type>
        {};

        literal_string(typename add_reference<String>::type str)
          : str_(str)
        {}

        // A string("...") which additionally has an associated attribute emits
        // its immediate literal only if it matches the attribute, otherwise
        // it fails.
        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& context
          , Delimiter const& d, Attribute const& attr) const
        {
            if (!traits::has_optional_value(attr))
                return false;

            // fail if attribute isn't matched by immediate literal
            typedef typename attribute<Context>::type attribute_type;

            using spirit::traits::get_c_string;
            if (!detail::string_compare(
                    get_c_string(
                        traits::extract_from<attribute_type>(attr, context))
                  , get_c_string(str_), char_encoding(), Tag()))
            {
                return false;
            }
            return detail::string_generate(sink, str_, char_encoding(), Tag()) && 
                   karma::delimit_out(sink, d);      // always do post-delimiting
        }

        // A string("...") without any associated attribute just emits its 
        // immediate literal
        template <typename OutputIterator, typename Context, typename Delimiter>
        bool generate(OutputIterator& sink, Context&, Delimiter const& d
          , unused_type) const
        {
            return detail::string_generate(sink, str_, char_encoding(), Tag()) && 
                   karma::delimit_out(sink, d);      // always do post-delimiting
        }

        template <typename Context>
        info what(Context const& /*context*/) const
        {
            return info("literal-string", str_);
        }

        string_type str_;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////

    // string
    template <typename CharEncoding, typename Modifiers>
    struct make_primitive<
        tag::char_code<tag::string, CharEncoding>
      , Modifiers>
    {
        static bool const lower = 
            has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
        static bool const upper = 
            has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

        typedef any_string<
            typename spirit::detail::get_encoding_with_case<
                Modifiers, CharEncoding, lower || upper>::type
          , typename detail::get_casetag<Modifiers, lower || upper>::type
        > result_type;

        result_type operator()(unused_type, unused_type) const
        {
            return result_type();
        }
    };

    // string literal 
    template <typename T, typename Modifiers>
    struct make_primitive<T, Modifiers
      , typename enable_if<traits::is_string<T> >::type>
    {
        static bool const lower =
            has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;

        static bool const upper =
            has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

        typedef typename add_const<T>::type const_string;
        typedef literal_string<
            const_string
          , typename spirit::detail::get_encoding_with_case<
                Modifiers, unused_type, lower || upper>::type
          , typename detail::get_casetag<Modifiers, lower || upper>::type
          , true
        > result_type;

        result_type operator()(
            typename add_reference<const_string>::type str, unused_type) const
        {
            return result_type(str);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename CharEncoding, typename Modifiers, typename A0
          , bool no_attribute>
        struct make_string_direct
        {
            static bool const lower = 
                has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
            static bool const upper = 
                has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

            typedef typename add_const<A0>::type const_string;
            typedef literal_string<
                const_string
              , typename spirit::detail::get_encoding_with_case<
                    Modifiers, unused_type, lower || upper>::type
              , typename detail::get_casetag<Modifiers, lower || upper>::type
              , no_attribute
            > result_type;

            template <typename Terminal>
            result_type operator()(Terminal const& term, unused_type) const
            {
                return result_type(fusion::at_c<0>(term.args));
            }
        };
    }

    // string("..."), lit("...")
    template <typename CharEncoding, typename Modifiers, typename A0>
    struct make_primitive<
            terminal_ex<
                tag::char_code<tag::string, CharEncoding>
              , fusion::vector1<A0> >
          , Modifiers>
      : detail::make_string_direct<CharEncoding, Modifiers, A0, false>
    {};

    template <typename Modifiers, typename A0>
    struct make_primitive<
            terminal_ex<tag::lit, fusion::vector1<A0> >
          , Modifiers
          , typename enable_if<traits::is_string<A0> >::type>
      : detail::make_string_direct<
            typename traits::char_encoding_from_char<
                typename traits::char_type_of<A0>::type>::type
          , Modifiers, A0, true>
    {};
}}}   // namespace boost::spirit::karma

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharEncoding, typename Tag, typename Attribute
            , typename Context, typename Iterator>
    struct handles_container<karma::any_string<CharEncoding, Tag>, Attribute
      , Context, Iterator>
      : mpl::false_ {};

    template <typename String, typename CharEncoding, typename Tag
            , bool no_attribute, typename Attribute, typename Context
            , typename Iterator>
    struct handles_container<karma::literal_string<String, CharEncoding, Tag
      , no_attribute>, Attribute, Context, Iterator>
      : mpl::false_ {};
}}}

#endif

/* lit.hpp
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
*/