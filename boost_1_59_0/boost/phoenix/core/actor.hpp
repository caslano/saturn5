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
        BOOST_PROTO_EXTENDS_ASSIGN_()

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

        BOOST_DELETED_FUNCTION(actor& operator=(actor const&))
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