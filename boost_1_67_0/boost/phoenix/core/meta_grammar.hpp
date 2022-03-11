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