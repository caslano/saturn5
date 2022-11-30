//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_LEX_LEXER_SEQUENCE_HPP
#define BOOST_SPIRIT_LEX_LEXER_SEQUENCE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/lex/domain.hpp>
#include <boost/spirit/home/lex/lexer_type.hpp>
#include <boost/spirit/home/lex/meta_compiler.hpp>
#include <boost/spirit/home/lex/detail/sequence_function.hpp>
#include <boost/fusion/include/any.hpp>
#include <boost/proto/operators.hpp>
#include <boost/proto/tags.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_operator<lex::domain, proto::tag::bitwise_or>  // enables |
      : mpl::true_ {};

    template <>
    struct flatten_tree<lex::domain, proto::tag::bitwise_or>  // flattens |
      : mpl::true_ {};

}}

namespace boost { namespace spirit { namespace lex
{
    template <typename Elements>
    struct sequence : nary_lexer<sequence<Elements> >
    {
        sequence(Elements const& elements)
          : elements(elements) {}

        template <typename LexerDef, typename String>
        void collect(LexerDef& lexdef, String const& state
          , String const& targetstate) const
        {
            typedef detail::sequence_collect_function<LexerDef, String>
                collect_function_type;
            collect_function_type f (lexdef, state, targetstate);
            fusion::any(elements, f);
        }

        template <typename LexerDef>
        void add_actions(LexerDef& lexdef) const 
        {
            detail::sequence_add_actions_function<LexerDef> f (lexdef);
            fusion::any(elements, f);
        }

        Elements elements;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Lexer generator: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Elements, typename Modifiers>
    struct make_composite<proto::tag::bitwise_or, Elements, Modifiers>
      : make_nary_composite<Elements, sequence>
    {};

}}} // namespace boost::spirit::lex

#endif

/* sequence.hpp
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
*/