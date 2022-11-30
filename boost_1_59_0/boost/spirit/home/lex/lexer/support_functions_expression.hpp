//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c)      2011 Thomas Heller
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_LEX_LEXER_SUPPORT_FUNCTIONS_EXPRESSION_HPP
#define BOOST_SPIRIT_LEX_LEXER_SUPPORT_FUNCTIONS_EXPRESSION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/v2_eval.hpp>
#include <boost/proto/proto_fwd.hpp> // for transform placeholders

namespace boost { namespace spirit { namespace lex
{
    template <typename> struct less_type;
    struct more_type;
    template <typename, typename> struct lookahead_type;
}}}

///////////////////////////////////////////////////////////////////////////////

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(spirit)(lex)(less)
  , (boost::phoenix::meta_grammar)
)

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(spirit)(lex)(lookahead)
  , (boost::phoenix::meta_grammar)
    (boost::phoenix::meta_grammar)
)

namespace boost { namespace phoenix
{

    namespace result_of
    {
        template <>
        struct is_nullary<custom_terminal<boost::spirit::lex::more_type> >
          : mpl::false_
        {};
    }
    
    template <typename Dummy>
    struct is_custom_terminal<boost::spirit::lex::more_type, Dummy> : mpl::true_ {};
    
    template <typename Dummy>
    struct custom_terminal<boost::spirit::lex::more_type, Dummy>
        : proto::call<
            v2_eval(
                proto::make<boost::spirit::lex::more_type()>
              , proto::call<functional::env(proto::_state)>
            )
        >
    {};


    template <typename Dummy>
    struct is_nullary::when<spirit::lex::rule::less, Dummy>
      : proto::make<mpl::false_()>
    {};

    template <typename Dummy>
    struct default_actions::when<spirit::lex::rule::less, Dummy>
      : proto::call<
            v2_eval(
                proto::make<
                    spirit::lex::less_type<proto::_child0>(proto::_child0)
                >
              , _env
            )
        >
    {};

    template <typename Dummy>
    struct is_nullary::when<spirit::lex::rule::lookahead, Dummy>
      : proto::make<mpl::false_()>
    {};

    template <typename Dummy>
    struct default_actions::when<spirit::lex::rule::lookahead, Dummy>
      : proto::call<
            v2_eval(
                proto::make<
                    spirit::lex::lookahead_type<
                        proto::_child0
                      , proto::_child1
                    >(
                        proto::_child0
                      , proto::_child1
                    )
                >
              , _env
            )
        >
    {};
}}

#endif

/* support_functions_expression.hpp
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
*/