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
66ytQcmaUbKmlaB26Izj56KB7iW2jI5P90sMgnoJxNuajMNrOjChTO5R1JCkTW3YX632hRCXYlZXLx4xgXPHKP3jui0Kvl21yfMfV1zh5SHVpVysCOU6pyqYiOdUdU90hrMNOpOL89SpxONy6C4clpAs5JHOytE98nTE6awcLaOyTp2Z+4VT1TZxE+fuRrd2UJc1rFUEAF0nBq7DbazPDb2/ezp664/2T0bD03dOub+Cpgx0udKjeW63I10REpQD027kMmF6j54aIo82+lY57whmkn54oS1YLRsU1oCTPw72WtIObQwauR3b6q5ynNgg0Rlxew5CnKsplTldBUms+/aHHFkaDCqLGaxPbE0rGxOr/1Htai7CeByLb7CgoV+nAY09Kj9qEA4bKcu6FOakVaTo/c0BSZ/0NQD4ECp0y9/c8xpbh2mAZWuu65UnAK/0Vetvtfrsfc2ia5+xy3VqzLuMv+f0RHXJ1YC1YwM5+2CQTxr5esrxaqg2Vr7XKkFee202WNzFsokWlJxboRy0nE4qHdPWPojnk+O914fHy+A8D3SbbHcunRKz32JSn/zGcg54NuNmaxJoSiF6T2YpWZbKclHY4Gn2LgoHQhuZw5ImR2gi0m2mfvS0Wh65+rfbbcvZ4y866QoOIJBn
*/