//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_STRING_TOKEN_DEF_MAR_28_2007_0722PM)
#define BOOST_SPIRIT_LEX_STRING_TOKEN_DEF_MAR_28_2007_0722PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/string_traits.hpp>
#include <boost/spirit/home/lex/domain.hpp>
#include <boost/spirit/home/lex/lexer_type.hpp>
#include <boost/spirit/home/lex/meta_compiler.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////

    // enables strings
    template <typename T>
    struct use_terminal<lex::domain, T
      , typename enable_if<traits::is_string<T> >::type>
      : mpl::true_ {};

    // enables string(str)
    template <typename CharEncoding, typename A0>
    struct use_terminal<lex::domain
      , terminal_ex<
            tag::char_code<tag::string, CharEncoding>
          , fusion::vector1<A0> > > 
      : traits::is_string<A0> {};

    // enables string(str, ID)
    template <typename CharEncoding, typename A0, typename A1>
    struct use_terminal<lex::domain
      , terminal_ex<
            tag::char_code<tag::string, CharEncoding>
          , fusion::vector2<A0, A1> > > 
      : traits::is_string<A0> {};
}}

namespace boost { namespace spirit { namespace lex
{ 
    // use string from standard character set by default
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::standard::string;
#endif
    using spirit::standard::string_type;

    ///////////////////////////////////////////////////////////////////////////
    //
    //  string_token_def 
    //      represents a string based token definition
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename String, typename IdType = std::size_t
      , typename CharEncoding = char_encoding::standard>
    struct string_token_def
      : primitive_lexer<string_token_def<String, IdType, CharEncoding> >
    {
        typedef typename
            remove_const<typename traits::char_type_of<String>::type>::type
        char_type;
        typedef std::basic_string<char_type> string_type;

        string_token_def(typename add_reference<String>::type str, IdType const& id)
          : str_(str), id_(id), unique_id_(std::size_t(~0))
          , token_state_(std::size_t(~0)) 
        {}

        template <typename LexerDef, typename String_>
        void collect(LexerDef& lexdef, String_ const& state
          , String_ const& targetstate) const
        {
            std::size_t state_id = lexdef.add_state(state.c_str());

            // If the following assertion fires you are probably trying to use 
            // a single string_token_def instance in more than one lexer state. 
            // This is not possible. Please create a separate token_def instance 
            // from the same regular expression for each lexer state it needs 
            // to be associated with.
            BOOST_ASSERT(
                (std::size_t(~0) == token_state_ || state_id == token_state_) &&
                "Can't use single string_token_def with more than one lexer state");

            char_type const* target = targetstate.empty() ? 0 : targetstate.c_str();
            if (target)
                lexdef.add_state(target);

            token_state_ = state_id;

            if (IdType(~0) == id_)
                id_ = IdType(lexdef.get_next_id());

            unique_id_ = lexdef.add_token (state.c_str(), str_, id_, target);
        }

        template <typename LexerDef>
        void add_actions(LexerDef&) const {}

        std::size_t id() const { return id_; }
        std::size_t unique_id() const { return unique_id_; }
        std::size_t state() const { return token_state_; }

        string_type str_;
        mutable IdType id_;
        mutable std::size_t unique_id_;
        mutable std::size_t token_state_;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Lex generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename Modifiers>
    struct make_primitive<T, Modifiers
      , typename enable_if<traits::is_string<T> >::type>
    {
        typedef typename add_const<T>::type const_string;
        typedef string_token_def<const_string> result_type;

        result_type operator()(
            typename add_reference<const_string>::type str, unused_type) const
        {
            return result_type(str, std::size_t(~0));
        }
    };

    template <typename Modifiers, typename CharEncoding, typename A0>
    struct make_primitive<
        terminal_ex<
            tag::char_code<tag::string, CharEncoding>
          , fusion::vector1<A0> >
      , Modifiers>
    {
        typedef typename add_const<A0>::type const_string;
        typedef string_token_def<const_string, std::size_t, CharEncoding> 
            result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args), std::size_t(~0));
        }
    };

    template <typename Modifiers, typename CharEncoding, typename A0, typename A1>
    struct make_primitive<
        terminal_ex<
            tag::char_code<tag::string, CharEncoding>
          , fusion::vector2<A0, A1> >
      , Modifiers>
    {
        typedef typename add_const<A0>::type const_string;
        typedef string_token_def<const_string, A1, CharEncoding> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(
                fusion::at_c<0>(term.args), fusion::at_c<1>(term.args));
        }
    };
}}}  // namespace boost::spirit::lex

#endif 

/* string_token_def.hpp
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
*/