/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010-2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_ENVIRONMENT_HPP
#define BOOST_PHOENIX_CORE_ENVIRONMENT_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/phoenix/support/vector.hpp>
#include <boost/proto/transform/impl.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/result_of.hpp>

#include <typeinfo>

namespace boost { namespace phoenix 
{
    struct unused {};

    namespace result_of
    {
        template <typename Env, typename Actions>
        struct context
        {
            typedef vector2<Env, Actions> type;
        };
        
        template <typename Env, typename Actions>
        struct make_context
            : context<Env, Actions>
        {};

        template <typename Context>
        struct env
        {
            typedef
                typename fusion::result_of::at_c<
                    typename boost::remove_reference<Context>::type
                  , 0
                >::type
                type;
        };
        
        template <typename Context>
        struct actions
        {
            typedef
                typename fusion::result_of::at_c<
                    typename boost::remove_reference<Context>::type
                  , 1
                >::type
                type;
        };
    }

    namespace functional
    {
        struct context
        {
            BOOST_PROTO_CALLABLE()

            template <typename Sig>
            struct result;

            template <typename This, typename Env, typename Actions>
            struct result<This(Env, Actions)>
                : result<This(Env const &, Actions const &)>
            {};

            template <typename This, typename Env, typename Actions>
            struct result<This(Env &, Actions)>
                : result<This(Env &, Actions const &)>
            {};

            template <typename This, typename Env, typename Actions>
            struct result<This(Env, Actions &)>
                : result<This(Env const &, Actions &)>
            {};

            template <typename This, typename Env, typename Actions>
            struct result<This(Env &, Actions &)>
                : result_of::context<Env &, Actions &>
            {};

            template <typename Env, typename Actions>
            typename result_of::context<Env &, Actions &>::type
            operator()(Env & env, Actions & actions) const
            {
                vector2<Env &, Actions &> e = {env, actions};
                return e;
            }

            template <typename Env, typename Actions>
            typename result_of::context<Env const &, Actions &>::type
            operator()(Env const & env, Actions & actions) const
            {
                vector2<Env const &, Actions &> e = {env, actions};
                return e;
            }

            template <typename Env, typename Actions>
            typename result_of::context<Env &, Actions const &>::type
            operator()(Env & env, Actions const & actions) const
            {
                vector2<Env &, Actions const &> e = {env, actions};
                return e;
            }

            template <typename Env, typename Actions>
            typename result_of::context<Env const &, Actions const &>::type
            operator()(Env const & env, Actions const & actions) const
            {
                vector2<Env const&, Actions const &> e = {env, actions};
                return e;
            }
        };

        struct make_context
            : context
        {};

        struct env
        {
            BOOST_PROTO_CALLABLE()

            template <typename Sig>
            struct result;

            template <typename This, typename Context>
            struct result<This(Context)>
                : result<This(Context const &)>
            {};

            template <typename This, typename Context>
            struct result<This(Context &)>
                : result_of::env<Context>
            {};

            template <typename Context>
            typename result_of::env<Context const>::type
            operator()(Context const & ctx) const
            {
                return fusion::at_c<0>(ctx);
            }

            template <typename Context>
            typename result_of::env<Context>::type
            operator()(Context & ctx) const
            {
                return fusion::at_c<0>(ctx);
            }
        };
        
        struct actions
        {
            BOOST_PROTO_CALLABLE()

            template <typename Sig>
            struct result;

            template <typename This, typename Context>
            struct result<This(Context)>
                : result<This(Context const &)>
            {};

            template <typename This, typename Context>
            struct result<This(Context &)>
                : result_of::actions<Context>
            {};

            template <typename Context>
            typename result_of::actions<Context const>::type
            operator()(Context const & ctx) const
            {
                return fusion::at_c<1>(ctx);
            }

            template <typename Context>
            typename result_of::actions<Context>::type
            operator()(Context & ctx) const
            {
                return fusion::at_c<1>(ctx);
            }
        };

    }

    struct _context
        : proto::transform<_context>
    {
        template <typename Expr, typename State, typename Data>
        struct impl
            : proto::transform_impl<Expr, State, Data>
        {
            typedef vector2<State, Data> result_type;

            result_type operator()(
                typename impl::expr_param
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                vector2<State, Data> e = {s, d};
                return e;
            }
        };
    };

    template <typename Env, typename Actions>
    inline
    typename result_of::context<Env const &, Actions const&>::type const
    context(Env const& env, Actions const& actions)
    {
        vector2<Env const&, Actions const &> e = {env, actions};
        return e;
    }

    template <typename Env, typename Actions>
    inline
    typename result_of::context<Env const &, Actions const&>::type const
    make_context(Env const& env, Actions const& actions)
    {
        return context(env, actions);
    }

    template <typename Env, typename Actions>
    inline
    typename result_of::context<Env &, Actions const&>::type const
    context(Env & env, Actions const& actions)
    {
        vector2<Env &, Actions const &> e = {env, actions};
        return e;
    }
    
    template <typename Env, typename Actions>
    inline
    typename result_of::context<Env &, Actions const&>::type const
    make_context(Env & env, Actions const& actions)
    {
        return context(env, actions);
    }

    template <typename Env, typename Actions>
    inline
    typename result_of::context<Env const &, Actions &>::type const
    context(Env const& env, Actions & actions)
    {
        vector2<Env const&, Actions &> e = {env, actions};
        return e;
    }
    
    template <typename Env, typename Actions>
    inline
    typename result_of::context<Env const &, Actions &>::type const
    make_context(Env const& env, Actions & actions)
    {
        return context(env, actions);
    }
    
    template <typename Env, typename Actions>
    inline
    typename result_of::context<Env &, Actions &>::type const
    context(Env & env, Actions & actions)
    {
        vector2<Env &, Actions &> e = {env, actions};
        return e;
    }
    
    template <typename Env, typename Actions>
    inline
    typename result_of::context<Env &, Actions &>::type const
    make_context(Env & env, Actions & actions)
    {
        return context(env, actions);
    }

    struct _env
        : proto::transform<_env>
    {
        template <typename Expr, typename State, typename Data>
        struct impl
            : proto::transform_impl<Expr, State, Data>
        {
            typedef State result_type;

            result_type operator()(
                typename impl::expr_param
              , typename impl::state_param s
              , typename impl::data_param
            ) const
            {
                return s;
            }
        };
    };

    template <typename Expr, typename State>
    struct _env::impl<Expr, State, proto::empty_env>
        : proto::transform_impl<Expr, State, proto::empty_env>
    {
            typedef
                typename fusion::result_of::at_c<
                    typename boost::remove_reference<State>::type
                  , 0
                >::type
                result_type;

            result_type operator()(
                typename impl::expr_param
              , typename impl::state_param s
              , typename impl::data_param
            ) const
            {
                return fusion::at_c<0>(s);
            }
    };

    template <typename Expr, typename State>
    struct _env::impl<Expr, State, unused>
        : _env::impl<Expr, State, proto::empty_env>
    {};

    template <typename Context>
    inline
    typename fusion::result_of::at_c<Context, 0>::type
    env(Context & ctx)
    {
        return fusion::at_c<0>(ctx);
    }

    template <typename Context>
    inline
    typename fusion::result_of::at_c<Context const, 0>::type
    env(Context const & ctx)
    {
        return fusion::at_c<0>(ctx);
    }

    struct _actions
        : proto::transform<_actions>
    {
        template <typename Expr, typename State, typename Data>
        struct impl
            : proto::transform_impl<Expr, State, Data>
        {
            typedef Data result_type;

            result_type operator()(
                typename impl::expr_param
              , typename impl::state_param
              , typename impl::data_param d
            ) const
            {
                return d;
            }
        };
    };

    template <typename Expr, typename State>
    struct _actions::impl<Expr, State, proto::empty_env>
        : proto::transform_impl<Expr, State, proto::empty_env>
    {
            typedef
                typename fusion::result_of::at_c<
                    typename boost::remove_reference<State>::type
                  , 1
                >::type
                result_type;

            result_type operator()(
                typename impl::expr_param
              , typename impl::state_param s
              , typename impl::data_param
            ) const
            {
                return fusion::at_c<1>(s);
            }
    };

    template <typename Expr, typename State>
    struct _actions::impl<Expr, State, unused>
        : _actions::impl<Expr, State, proto::empty_env>
    {};

    template <typename Context>
    inline
    typename fusion::result_of::at_c<Context, 1>::type
    actions(Context & ctx)
    {
        return fusion::at_c<1>(ctx);
    }

    template <typename Context>
    inline
    typename fusion::result_of::at_c<Context const, 1>::type
    actions(Context const & ctx)
    {
        return fusion::at_c<1>(ctx);
    }

    namespace result_of
    {
        template <
            BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
                BOOST_PHOENIX_LIMIT
              , typename A
              , mpl::void_
            )
          , typename Dummy = void
        >
        struct make_env;
        
    #define M0(Z, N, D)                                                         \
        template <BOOST_PHOENIX_typename_A(N)>                                  \
        struct make_env<BOOST_PHOENIX_A(N)>                                     \
        {                                                                       \
            typedef BOOST_PP_CAT(vector, N)<BOOST_PHOENIX_A(N)> type;           \
        };                                                                      \
    /**/
        BOOST_PP_REPEAT_FROM_TO(1, BOOST_PHOENIX_LIMIT, M0, _)
    #undef M0
    }

    inline
    result_of::make_env<>::type
    make_env()
    {
        return result_of::make_env<>::type();
    }
#define M0(Z, N, D)                                                             \
    template <BOOST_PHOENIX_typename_A(N)>                                      \
    inline                                                                      \
    typename result_of::make_env<BOOST_PHOENIX_A_ref(N)>::type                  \
    make_env(BOOST_PHOENIX_A_ref_a(N))                                          \
    {                                                                           \
        typename result_of::make_env<BOOST_PHOENIX_A_ref(N)>::type              \
            env =                                                               \
            {                                                                   \
                BOOST_PHOENIX_a(N)                                              \
            };                                                                  \
        return env;                                                             \
    }                                                                           \
    template <BOOST_PHOENIX_typename_A(N)>                                      \
    inline                                                                      \
    typename result_of::make_env<BOOST_PHOENIX_A_const_ref(N)>::type            \
    make_env(BOOST_PHOENIX_A_const_ref_a(N))                                    \
    {                                                                           \
        typename result_of::make_env<BOOST_PHOENIX_A_const_ref(N)>::type        \
            env =                                                               \
            {                                                                   \
                BOOST_PHOENIX_a(N)                                              \
            };                                                                  \
        return env;                                                             \
    }                                                                           \
    /**/
        BOOST_PP_REPEAT_FROM_TO(1, BOOST_PHOENIX_LIMIT, M0, _)
    #undef M0

    template <typename T, typename Enable = void>
    struct is_environment : fusion::traits::is_sequence<T> {};
}}

#endif


/* environment.hpp
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
*/