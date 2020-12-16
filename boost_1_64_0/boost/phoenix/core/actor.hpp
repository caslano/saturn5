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
x74J0/Axo/Jn1HPEBXu94Zr1W5p79K5ik8e/XbPO3TMrZw24VUgk7MQ1OK7fSJN9M7J4U3U4b43IHjkb58Wb2sFyY2SgOSdDkDtzQGD9eo3rBZgjx47MyeDwmLjYmBH1gv7D++4usL9V3v9xasbUsuvoJsvubU3ZdROtjf+27OieWfZs/tc1Cg3Hse/Nfzw+RohFTJk5I0P2cppAyqmtppzegb3Q/m05sft6/W/1G2xukFO/cDwcL/7Te7tIsZ/J8/87swbhZxhByrcd/G+Zmz7/Q/na6895+eXLtrdI+c/L1rkZVe+f4kjZdhCKt8xNL5Fo+G/L1rFnmjMzzZdvz/+m7To9swZY084g5dtJ9Bssc9NDLHL/b8sXhh8ntwq+fLv/N+Xr9MzmrCPCf8K9c567RXfWjL19xaQ2/zqfV+xvspraD42FC58JlkTq7At4/C+P9R8887ebDW5ClhF794lHQ7Sq9reFpXnU2WjFtRuwky7SbnkVU9AgXz1Jui3Z++vmmgkeqo4n9tFvw1JyLQ2sIbHlMa2O4/NLWCpxk5azDoHHBGtPrOfh3ZdzLQGsH7Gtnzwbnmv2ByAzaD59x07DGMD6E9ves1OnXDPDuyMdiH2z5XgAlnUAyadcG87znZNcywYrQqxcRr8NGDuU3hkPaSdTml7H2EPke0tgOe8t5ZoVzEys8ax2nTCfYO7ScvY+wHyC+RLr1j32Gv5GDqyKtJx9YnLN/oOiasQMd/fPxjIDo7GHhT5MxzoCCyd2KjLz7VzLBAsmdsKn1jE8JrzY35pYJ+MwG8YHFkqsRKG0T/CYYBVpPfRtdhDLupnWnp6zeeWaBcyPmFe3019gXwELIObSMOAQtiWwZsRGPPHfnWv2TNag5VL2vhHPB+ZB7Mnh4S+wbsFmEsuqePsOHrO5EPeJbTr4KfYjswUeTRIr+NvZjXhMsDBiO8X4mxiDzvY0OPETllkL+28NpF34fqkR66GlvT9ICzz6vC62M7AQYr+eO+eC/QHsHWKz/87CerC1gnIh55vePbkkjiHQIPbSfnT5njvG8Jb2fB323jqCZdZGm8/xMWHtMb422npfG5V1A+sI7CdiH43KWJ5r0W/Dr2tIPtf/uC0E+xEUpitJt/3zI37YPsFuEbt05tFJzGc4XB1o/aWe+xX7EdgsYrvL+q7Hem8H+7UT+zZ2TXvuHUA8JvxbHxK7FtSrMffOJMYO5itNM4YkglWRphlD0sCCpWn6u3dH6NPSNH06GqyiNE2fTgQLkKbpm+lgNaRp+p93J2hn0jT9zwRWitiAOvsxnxawgsQCF3bFNmHtpD3fkWPx1zGfumO2SE7ajG0XbACxFVfm/oD1YIW6laatWzBXaZp2Fs2YjbEExhIZS2IsGewRsRczK9bE/tAZvqdDrI7ouAKP2QX6rUFa/z77zuIYAovGPxB7/+GN1Vhm8PHQWGJ9upzozL0DjW2CMRNjZsYsjFkZi2bMxlgCY4mMJTGWzFgaY+mMZTKWzRjc/uVdf4yZGDMzZmHMylg0YzbGEhhLZCyJsWTG0hhLZyyTsWzGYKkh7/pjzMSYmTHLv7S8fweCdQTWkFjl339pj2UG1pFYvT8vNcO89NEec8/6i+F4PrC1xA6f/BnPZ4qEObs0zZzdDFaMWBf3V93xmGCliE0vUTwSY2COmQDmTczthNt1bEtgZYh1DW42jPstEZY1TOpiiaWM9URLB2tnkPau/4xz3O+1sJ1F2+/upT211J6OscPN33xiP1zOaptr9hu8CsRehm2YguXZX5tuRPCTKng+sLL0fM9/xvtN+0U6wSjtzoaECOzvMDv6lsTQKaLEfey3Q+Gb7uSYDW8U2os=
*/