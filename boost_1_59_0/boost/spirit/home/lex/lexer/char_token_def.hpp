//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_CHAR_TOKEN_DEF_MAR_28_2007_0626PM)
#define BOOST_SPIRIT_LEX_CHAR_TOKEN_DEF_MAR_28_2007_0626PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/string_traits.hpp>
#include <boost/spirit/home/lex/domain.hpp>
#include <boost/spirit/home/lex/lexer_type.hpp>
#include <boost/spirit/home/lex/meta_compiler.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////

    // enables 'x'
    template <>
    struct use_terminal<lex::domain, char>
      : mpl::true_ {};

    // enables "x"
    template <>
    struct use_terminal<lex::domain, char[2]>
      : mpl::true_ {};

    // enables wchar_t
    template <>
    struct use_terminal<lex::domain, wchar_t>
      : mpl::true_ {};

    // enables L"x"
    template <>
    struct use_terminal<lex::domain, wchar_t[2]>
      : mpl::true_ {};

    // enables char_('x'), char_("x")
    template <typename CharEncoding, typename A0>
    struct use_terminal<lex::domain
      , terminal_ex<
            tag::char_code<tag::char_, CharEncoding>
          , fusion::vector1<A0> > > 
      : mpl::true_ {};

    // enables char_('x', ID), char_("x", ID)
    template <typename CharEncoding, typename A0, typename A1>
    struct use_terminal<lex::domain
      , terminal_ex<
            tag::char_code<tag::char_, CharEncoding>
          , fusion::vector2<A0, A1> > > 
      : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace lex
{ 
    // use char_ from standard character set by default
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::standard::char_;
#endif
    using spirit::standard::char_type;

    ///////////////////////////////////////////////////////////////////////////
    //
    //  char_token_def 
    //      represents a single character token definition
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharEncoding = char_encoding::standard
      , typename IdType = std::size_t>
    struct char_token_def
      : primitive_lexer<char_token_def<CharEncoding, IdType> >
    {
        typedef typename CharEncoding::char_type char_type;

        char_token_def(char_type ch, IdType const& id) 
          : ch(ch), id_(id), unique_id_(std::size_t(~0))
          , token_state_(std::size_t(~0)) 
        {}

        template <typename LexerDef, typename String>
        void collect(LexerDef& lexdef, String const& state
          , String const& targetstate) const
        {
            std::size_t state_id = lexdef.add_state(state.c_str());

            // If the following assertion fires you are probably trying to use 
            // a single char_token_def instance in more than one lexer state. 
            // This is not possible. Please create a separate token_def instance 
            // from the same regular expression for each lexer state it needs 
            // to be associated with.
            BOOST_ASSERT(
                (std::size_t(~0) == token_state_ || state_id == token_state_) &&
                "Can't use single char_token_def with more than one lexer state");

            char_type const* target = targetstate.empty() ? 0 : targetstate.c_str();
            if (target)
                lexdef.add_state(target);

            token_state_ = state_id;
            unique_id_ = lexdef.add_token (state.c_str(), ch, id_, target);
        }

        template <typename LexerDef>
        void add_actions(LexerDef&) const {}

        IdType id() const { return id_; }
        std::size_t unique_id() const { return unique_id_; }
        std::size_t state() const { return token_state_; }

        char_type ch;
        mutable IdType id_;
        mutable std::size_t unique_id_;
        mutable std::size_t token_state_;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Lexer generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename CharEncoding>
        struct basic_literal
        {
            typedef char_token_def<CharEncoding> result_type;

            template <typename Char>
            result_type operator()(Char ch, unused_type) const
            {
                return result_type(ch, ch);
            }

            template <typename Char>
            result_type operator()(Char const* str, unused_type) const
            {
                return result_type(str[0], str[0]);
            }
        };
    }

    // literals: 'x', "x"
    template <typename Modifiers>
    struct make_primitive<char, Modifiers>
      : detail::basic_literal<char_encoding::standard> {};

    template <typename Modifiers>
    struct make_primitive<char const(&)[2], Modifiers>
      : detail::basic_literal<char_encoding::standard> {};

    // literals: L'x', L"x"
    template <typename Modifiers>
    struct make_primitive<wchar_t, Modifiers>
      : detail::basic_literal<char_encoding::standard_wide> {};

    template <typename Modifiers>
    struct make_primitive<wchar_t const(&)[2], Modifiers>
      : detail::basic_literal<char_encoding::standard_wide> {};

    // handle char_('x')
    template <typename CharEncoding, typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<
            tag::char_code<tag::char_, CharEncoding>
          , fusion::vector1<A0>
        >
      , Modifiers>
    {
        typedef char_token_def<CharEncoding> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args), fusion::at_c<0>(term.args));
        }
    };

    // handle char_("x")
    template <typename CharEncoding, typename Modifiers, typename Char>
    struct make_primitive<
        terminal_ex<
            tag::char_code<tag::char_, CharEncoding>
          , fusion::vector1<Char(&)[2]>   // single char strings
        >
      , Modifiers>
    {
        typedef char_token_def<CharEncoding> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            Char ch = fusion::at_c<0>(term.args)[0];
            return result_type(ch, ch);
        }
    };

    // handle char_('x', ID)
    template <typename CharEncoding, typename Modifiers, typename A0, typename A1>
    struct make_primitive<
        terminal_ex<
            tag::char_code<tag::char_, CharEncoding>
          , fusion::vector2<A0, A1>
        >
      , Modifiers>
    {
        typedef char_token_def<CharEncoding> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(
                fusion::at_c<0>(term.args), fusion::at_c<1>(term.args));
        }
    };

    // handle char_("x", ID)
    template <typename CharEncoding, typename Modifiers, typename Char, typename A1>
    struct make_primitive<
        terminal_ex<
            tag::char_code<tag::char_, CharEncoding>
          , fusion::vector2<Char(&)[2], A1>   // single char strings
        >
      , Modifiers>
    {
        typedef char_token_def<CharEncoding> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(
                fusion::at_c<0>(term.args)[0], fusion::at_c<1>(term.args));
        }
    };
}}}  // namespace boost::spirit::lex

#endif 

/* char_token_def.hpp
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
*/