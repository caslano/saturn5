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