/*=============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2014 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_ACTOR_HPP
#define BOOST_PHOENIX_CORE_ACTOR_HPP

#include <boost/phoenix/core/limits.hpp>

#include <boost/is_placeholder.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/phoenix/core/domain.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/phoenix/support/vector.hpp>
#include <boost/proto/extends.hpp>
#include <boost/proto/make_expr.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/mpl/void.hpp>
#include <cstring>
#ifndef BOOST_PHOENIX_NO_VARIADIC_ACTOR
#   include <boost/mpl/if.hpp>
#   include <boost/type_traits/is_reference.hpp>
#   include <boost/phoenix/core/detail/index_sequence.hpp>
#endif

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4522) // 'this' used in base member initializer list
#pragma warning(disable: 4510) // default constructor could not be generated
#pragma warning(disable: 4610) // can never be instantiated - user defined cons
#endif

namespace boost { namespace phoenix
{
    template <typename Expr>
    struct actor;

    namespace detail
    {
        struct error_expecting_arguments
        {
            template <typename T>
            error_expecting_arguments(T const&) {}
        };

        struct error_invalid_lambda_expr
        {
            template <typename T>
            error_invalid_lambda_expr(T const&) {}
        };

        template <typename T>
        struct result_type_deduction_helper
        {
            typedef T const & type;
        };

        template <typename T>
        struct result_type_deduction_helper<T &>
        {
            typedef T & type;
        };

        template <typename T>
        struct result_type_deduction_helper<T const &>
        {
            typedef T const & type;
        };
    }

    namespace result_of
    {
#ifdef BOOST_PHOENIX_NO_VARIADIC_ACTOR
        // Bring in the result_of::actor<>
        #include <boost/phoenix/core/detail/cpp03/actor_result_of.hpp>
#else
        template <typename Expr, typename... A>
        struct actor_impl
        {
            typedef
                typename boost::phoenix::evaluator::impl<
                    Expr const&
                  , vector2<
                        typename vector_chooser<sizeof...(A) + 1>::
                          template apply<const ::boost::phoenix::actor<Expr> *, A...>::type&
                      , default_actions
                    > const &
                  , proto::empty_env
                >::result_type
                type;
        };

        template <typename Expr, typename... A>
        struct actor : actor_impl<Expr, A...> {};

        template <typename Expr>
        struct nullary_actor_result : actor_impl<Expr> {};
#endif

        template <typename Expr>
        struct actor<Expr>
        {
            typedef
                // avoid calling result_of::actor when this is false
                typename mpl::eval_if_c<
                    result_of::is_nullary<Expr>::value
                  , nullary_actor_result<Expr>
                  , mpl::identity<detail::error_expecting_arguments>
                >::type
            type;
        };
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  actor
    //
    //      The actor class. The main thing! In phoenix, everything is an actor
    //      This class is responsible for full function evaluation. Partial
    //      function evaluation involves creating a hierarchy of actor objects.
    //
    ////////////////////////////////////////////////////////////////////////////
    template <typename Expr>
    struct actor
    {
        typedef typename
            mpl::eval_if_c<
                mpl::or_<
                    is_custom_terminal<Expr>
                  , mpl::bool_<is_placeholder<Expr>::value>
                >::value
              , proto::terminal<Expr>
              , mpl::identity<Expr>
            >::type
            expr_type;

        BOOST_PROTO_BASIC_EXTENDS(expr_type, actor<Expr>, phoenix_domain)
        BOOST_PROTO_EXTENDS_SUBSCRIPT()
        BOOST_PROTO_EXTENDS_ASSIGN()

        template <typename Sig>
        struct result;

        typename result_of::actor<proto_base_expr>::type
        operator()()
        {
            typedef vector1<const actor<Expr> *> env_type;
            env_type env = {this};

            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }

        typename result_of::actor<proto_base_expr>::type
        operator()() const
        {
            typedef vector1<const actor<Expr> *> env_type;
            env_type env = {this};

            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }

        template <typename Env>
        typename evaluator::impl<
            proto_base_expr const &
          , typename result_of::context<
                Env const &
              , default_actions const &
            >::type
          , proto::empty_env
        >::result_type
        eval(Env const & env) const
        {
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }

#ifdef BOOST_PHOENIX_NO_VARIADIC_ACTOR
        // Bring in the rest
        #include <boost/phoenix/core/detail/cpp03/actor_operator.hpp>
#else
        template <typename This, typename... A>
        struct result<This(A...)>
            : result_of::actor<
                proto_base_expr
              , typename mpl::if_<is_reference<A>, A, A const &>::type...
            >
        {};

        template <typename... A>
        typename result<actor(A...)>::type
        operator()(A &&... a)
        {
            typedef
                typename vector_chooser<sizeof...(A) + 1>::template apply<
                    const actor<Expr> *
                  , typename mpl::if_<is_reference<A>, A, A const &>::type...
                >::type
            env_type;

            env_type env = {this, a...};
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }

        template <typename... A>
        typename result<actor(A...)>::type
        operator()(A &&... a) const
        {
            typedef
                typename vector_chooser<sizeof...(A) + 1>::template apply<
                    const actor<Expr> *
                  , typename mpl::if_<is_reference<A>, A, A const &>::type...
                >::type
            env_type;

            env_type env = {this, a...};
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
#endif
    };
}}

namespace boost
{
    // specialize boost::result_of to return the proper result type
    template <typename Expr>
    struct result_of<phoenix::actor<Expr>()>
        : phoenix::result_of::actor<typename phoenix::actor<Expr>::proto_base_expr>
    {};

    template <typename Expr>
    struct result_of<phoenix::actor<Expr> const()>
        : phoenix::result_of::actor<typename phoenix::actor<Expr>::proto_base_expr>
    {};
}


#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif


/* actor.hpp
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
*/