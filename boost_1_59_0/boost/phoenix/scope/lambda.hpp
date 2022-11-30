/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2004 Daniel Wallin
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_SCOPE_LAMBDA_HPP
#define BOOST_PHOENIX_SCOPE_LAMBDA_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/mpl/int.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/scope/local_variable.hpp>
#include <boost/phoenix/scope/scoped_environment.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(lambda_actor)
  , (proto::terminal<proto::_>) // Locals
    (proto::terminal<proto::_>) // Map
    (meta_grammar)              // Lambda
)

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(lambda)
  , (proto::terminal<proto::_>) // OuterEnv 
    (proto::terminal<proto::_>) // Locals
    (proto::terminal<proto::_>) // Map
    (meta_grammar)              // Lambda
)

namespace boost { namespace phoenix
{
    struct lambda_eval
    {
        BOOST_PROTO_CALLABLE()

        template <typename Sig>
        struct result;

        template <
            typename This
          , typename OuterEnv
          , typename Locals
          , typename Map
          , typename Lambda
          , typename Context
        >
        struct result<This(OuterEnv, Locals, Map, Lambda, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<
                        OuterEnv
                    >::type
                >::type
                outer_env_type;

            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<
                        Locals
                    >::type
                >::type
                locals_type;

            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<
                        Map
                    >::type
                >::type
                map_type;
            
            typedef
                typename proto::detail::uncvref<
                    typename result_of::env<Context>::type
                >::type
                env_type;

                    typedef
                            typename result_of::eval<
                                Lambda
                                     , typename result_of::context<
                                       scoped_environment<
                                              env_type
                                            , outer_env_type
                                            , locals_type
                                            , map_type
                                            >
                          , typename result_of::actions<
                                Context
                                            >::type
                                       >::type
                                    >::type
                             type;
        };

        template <typename OuterEnv, typename Locals, typename Map, typename Lambda, typename Context>
        typename result<lambda_eval(OuterEnv const &, Locals const &, Map const &, Lambda const &, Context const &)>::type
        operator()(OuterEnv const & outer_env, Locals const & locals, Map const &, Lambda const & lambda, Context const & ctx) const
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<
                        OuterEnv
                    >::type
                >::type
                outer_env_type;

            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<
                        Locals
                    >::type
                >::type
                locals_type;

            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<
                        Map
                    >::type
                >::type
                map_type;
            
            typedef
                typename proto::detail::uncvref<
                    typename result_of::env<Context>::type
                >::type
                env_type;
            
                scoped_environment<
                env_type
              , outer_env_type
              , locals_type
              , map_type
            >
            env(phoenix::env(ctx), proto::value(outer_env), proto::value(locals));

            return eval(lambda, phoenix::context(env, phoenix::actions(ctx)));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::lambda, Dummy>
        : call<lambda_eval, Dummy>
    {};

    template <typename Dummy>
    struct is_nullary::when<rule::lambda, Dummy>
        : proto::call<
            evaluator(
                proto::_child_c<3>
              , proto::call<
                    functional::context(
                        proto::make<
                            mpl::true_()
                        >
                      , proto::make<
                            detail::scope_is_nullary_actions()
                        >
                    )
                >
              , proto::make<
                    proto::empty_env()
                >
            )
        >
    {};

    template <typename Dummy>
    struct is_nullary::when<rule::lambda_actor, Dummy>
        : proto::or_<
            proto::when<
                expression::lambda_actor<
                    proto::terminal<vector0<> >
                  , proto::terminal<proto::_>
                  , meta_grammar
                >
              , mpl::true_()
            >
          , proto::when<
                expression::lambda_actor<
                    proto::terminal<proto::_>
                  , proto::terminal<proto::_>
                  , meta_grammar
                >
              , proto::fold<
                    proto::call<proto::_value(proto::_child_c<0>)>
                  , proto::make<mpl::true_()>
                  , proto::make<
                        mpl::and_<
                            proto::_state
                          , proto::call<
                                evaluator(
                                    proto::_
                                  , _context
                                  , proto::make<proto::empty_env()>
                                )
                            >
                        >()
                    >
                >
            >
        >
    {};

    struct lambda_actor_eval
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Vars, typename Map, typename Lambda, typename Context>
        struct result<This(Vars, Map, Lambda, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename result_of::env<Context>::type
                >::type
                env_type;
            typedef
                typename proto::detail::uncvref<
                    typename result_of::actions<Context>::type
                >::type
                actions_type;
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<Vars>::type
                     >::type
                     vars_type;
            
            typedef typename
                detail::result_of::initialize_locals<
                    vars_type
                  , Context
                >::type
            locals_type;

            typedef
                typename expression::lambda<
                    env_type
                  , locals_type
                  , Map
                  , Lambda
                >::type const
                type;
        };

        template <
            typename Vars
          , typename Map
          , typename Lambda
          , typename Context
        >
        typename result<
            lambda_actor_eval(Vars const&, Map const &, Lambda const&, Context const &)
        >::type const
        operator()(Vars const& vars, Map const& map, Lambda const& lambda, Context const & ctx) const
        {
            typedef
                typename proto::detail::uncvref<
                    typename result_of::env<Context>::type
                >::type
                env_type;
            /*typedef
                typename proto::detail::uncvref<
                    typename result_of::actions<Context>::type
                >::type
                actions_type;*/
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<Vars>::type
                     >::type
                     vars_type;
            /*typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<Map>::type
                     >::type
                     map_type;*/

            typedef typename
                detail::result_of::initialize_locals<
                    vars_type
                  , Context
                >::type
            locals_type;

            locals_type locals = initialize_locals(proto::value(vars), ctx);

            return
                expression::
                    lambda<env_type, locals_type, Map, Lambda>::
                        make(phoenix::env(ctx), locals, map, lambda);
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::lambda_actor, Dummy>
        : call<lambda_actor_eval, Dummy>
    {};
    
    template <typename Locals = vector0<>,
              typename Map = detail::map_local_index_to_tuple<>,
              typename Dummy = void>
    struct lambda_actor_gen;

    template <>
    struct lambda_actor_gen<vector0<>, detail::map_local_index_to_tuple<>, void>
    {
        template <typename Expr>
        typename expression::lambda_actor<vector0<>, detail::map_local_index_to_tuple<>, Expr>::type const
        operator[](Expr const & expr) const
        {
            typedef vector0<> locals_type;
            typedef detail::map_local_index_to_tuple<> map_type;
            return expression::lambda_actor<locals_type, map_type, Expr>::make(locals_type(), map_type(), expr);
        }
    };

    template <typename Locals, typename Map>
    struct lambda_actor_gen<Locals, Map>
    {
        lambda_actor_gen(Locals const & locals_)
            : locals(locals_)
        {}

        lambda_actor_gen(lambda_actor_gen const & o)
            : locals(o.locals)
        {};

        template <typename Expr>
        typename expression::lambda_actor<
            Locals
          , Map
          , Expr
        >::type const
        operator[](Expr const & expr) const
        {
            return expression::lambda_actor<Locals, Map, Expr>::make(locals, Map(), expr);
        }

        Locals locals;
    };

    struct lambda_local_gen
        : lambda_actor_gen<>
    {
#if defined(BOOST_PHOENIX_NO_VARIADIC_SCOPE)
        lambda_actor_gen<> const
        operator()() const
        {
            return lambda_actor_gen<>();
        }

        #include <boost/phoenix/scope/detail/cpp03/lambda.hpp>
#else
#define BOOST_PHOENIX_SCOPE_ACTOR_GEN_NAME lambda_actor_gen
#define BOOST_PHOENIX_SCOPE_ACTOR_GEN_FUNCTION operator()
#define BOOST_PHOENIX_SCOPE_ACTOR_GEN_CONST const
        #include <boost/phoenix/scope/detail/local_gen.hpp>
#undef BOOST_PHOENIX_SCOPE_ACTOR_GEN_NAME
#undef BOOST_PHOENIX_SCOPE_ACTOR_GEN_FUNCTION
#undef BOOST_PHOENIX_SCOPE_ACTOR_GEN_CONST
#endif
    };

    typedef lambda_local_gen lambda_type;
    lambda_local_gen const lambda = lambda_local_gen();

}}

#endif

/* lambda.hpp
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
*/