//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c)      2011 Thomas Heller
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_ARGUMENT_PHEONIX_MARCH_25_2011_1841PM)
#define BOOST_SPIRIT_LEX_ARGUMENT_PHEONIX_MARCH_25_2011_1841PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/as_actor.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/v2_eval.hpp>
#include <boost/phoenix/core/value.hpp> // includes as_actor specialization
#include <boost/proto/traits.hpp>
#include <boost/proto/proto_fwd.hpp> // for transform placeholders

namespace boost { namespace spirit { namespace lex
{
    ///////////////////////////////////////////////////////////////////////////
    //  The value_context is used as a noop Phoenix actor to create the 
    //  placeholder '_val' (see below). It is a noop actor because it is used
    //  as a placeholder only, while it is being converted either to a 
    //  value_getter (if used as a rvalue) or to a value_setter (if used as a 
    //  lvalue). The conversion is achieved by specializing and overloading a 
    //  couple of the Phoenix templates from the Phoenix expression composition
    //  engine (see the end of this file).
    struct value_context 
    {
        typedef mpl::true_ no_nullary;

        typedef unused_type result_type;

        template <typename Env>
        struct result
        {
            typedef unused_type type;
        };

        template <typename Env>
        unused_type
        eval(Env const&) const
        {
            return unused;
        }
    };

    // forward declarations
    struct value_getter;
    template <typename> struct value_setter;

    ///////////////////////////////////////////////////////////////////////////
    //  The state_context is used as a noop Phoenix actor to create the 
    //  placeholder '_state' (see below). It is a noop actor because it is used
    //  as a placeholder only, while it is being converted either to a 
    //  state_getter (if used as a rvalue) or to a state_setter (if used as a 
    //  lvalue). The conversion is achieved by specializing and overloading a 
    //  couple of the Phoenix templates from the Phoenix expression composition
    //  engine (see the end of this file).
    struct state_context 
    {
        typedef mpl::true_ no_nullary;

        typedef unused_type result_type;

        template <typename Env>
        struct result
        {
            typedef unused_type type;
        };

        template <typename Env>
        unused_type
        eval(Env const&) const
        {
            return unused;
        }
    };

    // forward declarations
    struct state_getter;
    template <typename> struct state_setter;
    struct eoi_getter;
}}}

///////////////////////////////////////////////////////////////////////////////

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(spirit)(lex)(value_setter)
  , (boost::phoenix::meta_grammar)
)

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(spirit)(lex)(state_setter)
  , (boost::phoenix::meta_grammar)
)

namespace boost { namespace phoenix
{
    namespace result_of
    {
        template <>
        struct is_nullary<custom_terminal<boost::spirit::lex::value_context> >
          : mpl::false_
        {};
    }
    
    template <typename Dummy>
    struct is_custom_terminal<boost::spirit::lex::value_context, Dummy>: mpl::true_ {};
    
    template <typename Dummy>
    struct custom_terminal<boost::spirit::lex::value_context, Dummy>
      : proto::call<
            v2_eval(
                proto::make<boost::spirit::lex::value_getter()>
              , proto::call<functional::env(proto::_state)>
            )
        >
    {};

    template <typename Dummy>
    struct is_nullary::when<spirit::lex::rule::value_setter, Dummy>
      : proto::make<mpl::false_()>
    {};

    template <typename Dummy>
    struct default_actions::when<spirit::lex::rule::value_setter, Dummy>
      : proto::call<
            v2_eval(
                proto::make<
                    spirit::lex::value_setter<proto::_child0>(
                        proto::_child0
                    )
                >
              , _env
            )
        >
    {};

    template <>
    struct actor<spirit::lex::value_context>
      : boost::phoenix::actor<proto::terminal<spirit::lex::value_context>::type>
    {
        typedef boost::phoenix::actor<
            proto::terminal<spirit::lex::value_context>::type
        > base_type;

        actor(base_type const & base = base_type())
            : base_type(base)
        {}

        template <typename Expr>
        typename spirit::lex::expression::value_setter<
            typename phoenix::as_actor<Expr>::type>::type const
        operator=(Expr const & expr) const
        {
            return
                spirit::lex::expression::value_setter<
                    typename phoenix::as_actor<Expr>::type
                >::make(phoenix::as_actor<Expr>::convert(expr));
        }
    };
    
    namespace result_of
    {
        template <>
        struct is_nullary<custom_terminal<boost::spirit::lex::state_context> >
          : mpl::false_
        {};
    }
    
    template <typename Dummy>
    struct is_custom_terminal<boost::spirit::lex::state_context, Dummy>: mpl::true_ {};
    
    template <typename Dummy>
    struct custom_terminal<boost::spirit::lex::state_context, Dummy>
      : proto::call<
            v2_eval(
                proto::make<boost::spirit::lex::state_getter()>
              , proto::call<functional::env(proto::_state)>
            )
        >
    {};

    template <typename Dummy>
    struct is_nullary::when<spirit::lex::rule::state_setter, Dummy>
      : proto::make<mpl::false_()>
    {};

    template <typename Dummy>
    struct default_actions::when<spirit::lex::rule::state_setter, Dummy>
      : proto::call<
            v2_eval(
                proto::make<
                    spirit::lex::state_setter<proto::_child0>(
                        proto::_child0
                    )
                >
              , _env
            )
        >
    {};

    template <>
    struct actor<spirit::lex::state_context>
      : boost::phoenix::actor<proto::terminal<spirit::lex::state_context>::type>
    {
        typedef boost::phoenix::actor<
            proto::terminal<spirit::lex::state_context>::type
        > base_type;

        actor(base_type const & base = base_type())
          : base_type(base)
        {}

        template <typename Expr>
        typename spirit::lex::expression::state_setter<
            typename phoenix::as_actor<Expr>::type>::type const
        operator=(Expr const & expr) const
        {
            return
                spirit::lex::expression::state_setter<
                    typename phoenix::as_actor<Expr>::type
                >::make(phoenix::as_actor<Expr>::convert(expr));
        }
    };
    
    namespace result_of
    {
        template <>
        struct is_nullary<custom_terminal<boost::spirit::lex::eoi_getter> >
          : mpl::false_
        {};
    }
    
    template <typename Dummy>
    struct is_custom_terminal<boost::spirit::lex::eoi_getter, Dummy>: mpl::true_ {};
    
    template <typename Dummy>
    struct custom_terminal<boost::spirit::lex::eoi_getter, Dummy>
      : proto::call<
            v2_eval(
                proto::make<boost::spirit::lex::eoi_getter()>
              , proto::call<functional::env(proto::_state)>
            )
        >
    {};
}}

#endif

/* argument_phoenix.hpp
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
*/