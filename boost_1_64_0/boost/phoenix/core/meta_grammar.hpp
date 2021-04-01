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
6NFkl563dQqyW4n3sCut9ZXPAHWoW4pxx1+0vL1dCUkT72TegNRLB9Ygif0tAe+TKYbS55CLEvZ2cgqjuyli6J38cnq2qplPrZ+6Il0qrOB2yFPA7nZTRosZy4Oq26p8z5Qd0QdaLNDCr78SYGKW4f20M/Yoak8XCAFM7PzXklIRv00aG23h2xBLFwnNDuoEENDaLzJMcex6TQ6+v1cXZGMuVBtXqhKye4h81m3jCxghDvD27r/flAp1vCMiOu+Z55WemH/gW9+dkyI4hcWLNxktgflv4MZxE+0t/ZOxOHrZ2UyQlUN3AtZx/5bY98iuafKAvyjb0w+skj5e/OI0/cFKSfI5F1b6VlvIed7NvXWTQ7ozonsTpmesSQuJAMX2FMHULFDgTo2wamNUNfxd5sQR7hjDRlh1NM/uAQKrH6fc/K4J1DZhPp97BCMY2af/sz6fh8++LC02G/W/HHOknJlCManRUJqs6wMC8HAHdgUqX2xHF5f+lTDPQ9pAj1ouQWKK2sAchP5dzhS09DGhA0ZHqbwzO50fNQ/mcfH2QhWZfZESqDys3JqL5Q==
*/