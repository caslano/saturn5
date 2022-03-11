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