/*=============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_META_GRAMMAR_HPP
#define BOOST_PHOENIX_CORE_META_GRAMMAR_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/proto/matches.hpp>
#include <boost/proto/transform/call.hpp>
#include <boost/proto/transform/default.hpp>

namespace boost { namespace phoenix
{
    /////////////////////////////////////////////////////////////////////////////
    // The grammar defining valid phoenix expressions
    struct meta_grammar
        : proto::switch_<meta_grammar>
    {
        template <typename Tag, typename Dummy = void>
        struct case_
            : proto::not_<proto::_>
        {};
    };

    struct evaluator
    {
        BOOST_PROTO_TRANSFORM(evaluator)

        template <typename Expr, typename State, typename Data>
        struct impl
            : proto::transform_impl<Expr, State, Data>
        {
            typedef meta_grammar::impl<Expr, State, Data> what;

            typedef typename what::result_type result_type;

            result_type operator()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return what()(e, s, d);
            }
        };

        template <typename Expr, typename State>
        struct impl<Expr, State, proto::empty_env>
            : proto::transform_impl<Expr, State, proto::empty_env>
        {
            typedef
                meta_grammar::impl<
                    Expr
                  , typename result_of::env<State>::type
                  , typename result_of::actions<State>::type
                >
                what;

            typedef typename what::result_type result_type;

            result_type operator()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param
            ) const
            {
                return what()(e, phoenix::env(s), actions(s));
            }
        };
        
        template <typename Expr, typename State>
        struct impl<Expr, State, unused>
            : proto::transform_impl<Expr, State, unused>
        {
            typedef
                meta_grammar::impl<
                    Expr
                  , typename result_of::env<State>::type
                  , typename result_of::actions<State>::type
                >
                what;

            typedef typename what::result_type result_type;

            result_type operator()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param
            ) const
            {
                return what()(e, phoenix::env(s), actions(s));
            }
        };
    };

    /////////////////////////////////////////////////////////////////////////////
    // Set of default actions. Extend this whenever you add a new phoenix
    // construct
    struct default_actions
    {
        template <typename Rule, typename Dummy = void>
        struct when
            : proto::_default<meta_grammar>
        {};
    };

    template <typename Rule, typename Dummy = void>
    struct enable_rule
        : proto::when<Rule, proto::external_transform>
    {};

    namespace result_of
    {
        template <typename Expr, typename Context>
        struct eval
            : boost::result_of< ::boost::phoenix::evaluator(Expr, Context)>
        {};
    }

    /////////////////////////////////////////////////////////////////////////////
    // A function we can call to evaluate our expression
    template <typename Expr, typename Context>
    inline
    typename meta_grammar::template impl<
        Expr const&
      , typename result_of::env<Context const&>::type
      , typename result_of::actions<Context const&>::type
    >::result_type
    eval(Expr const& expr, Context const & ctx)
    {
        static evaluator const e = {};
        return e(expr, ctx);
    }
    
    template <typename Expr, typename Context>
    inline
    typename meta_grammar::template impl<
        Expr &
      , typename result_of::env<Context const&>::type
      , typename result_of::actions<Context const&>::type
    >::result_type
    eval(Expr & expr, Context const & ctx)
    {
        static evaluator const e = {};
        return e(expr, ctx);
    }
}}

#endif

/* meta_grammar.hpp
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
*/