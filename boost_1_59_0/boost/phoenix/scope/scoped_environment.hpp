/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_SCOPE_SCOPED_ENVIRONMENT_HPP
#define BOOST_PHOENIX_SCOPE_SCOPED_ENVIRONMENT_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/mpl/int.hpp>
#include <boost/fusion/sequence/sequence_facade.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace phoenix
{
    template<typename Env, typename OuterEnv, typename Locals, typename Map>
    struct scoped_environment
        : fusion::sequence_facade<
            scoped_environment<Env, OuterEnv, Locals, Map>
          , fusion::random_access_traversal_tag
        >
    {
        typedef Env env_type;
        typedef OuterEnv outer_env_type;
        typedef Locals locals_type;
        typedef Map map_type;

        scoped_environment(
            Env const & env_
          , OuterEnv const &outer_env_
          , Locals const &locals_
        )
            : env(env_)
            , outer_env(outer_env_)
            , locals(locals_)
        {}

        scoped_environment(scoped_environment const & o)
            : env(o.env)
            , outer_env(o.outer_env)
            , locals(o.locals)
        {}

        Env      const & env;
        OuterEnv const & outer_env;
        Locals   const & locals;

        typedef typename
            fusion::result_of::pop_front<
                typename add_const<
                    typename proto::detail::uncvref<Env>::type
                >::type
            >::type
            args_type;

        args_type args() const
        {
            return fusion::pop_front(env);
        }
    
        #define BOOST_PHOENIX_ADAPT_SCOPED_ENVIRONMENT(INTRINSIC)               \
        template <typename Seq>                                                 \
        struct INTRINSIC                                                        \
        {                                                                       \
            typedef                                                             \
                typename fusion::result_of::INTRINSIC<                          \
                    typename mpl::eval_if_c<                                    \
                        is_const<                                               \
                            typename remove_reference<                          \
                                typename Seq::env_type                          \
                            >::type                                             \
                        >::value                                                \
                      , add_const<                                              \
                            typename proto::detail::uncvref<                    \
                                typename Seq::env_type                          \
                            >::type                                             \
                        >                                                       \
                      , proto::detail::uncvref<                                 \
                            typename Seq::env_type                              \
                        >                                                       \
                    >::type                                                     \
                >::type                                                         \
                type;                                                           \
                                                                                \
            static type call(Seq & seq)                                         \
            {                                                                   \
                return fusion::INTRINSIC(seq.env);                              \
            }                                                                   \
        }                                                                       \
        /**/
        BOOST_PHOENIX_ADAPT_SCOPED_ENVIRONMENT(begin);
        BOOST_PHOENIX_ADAPT_SCOPED_ENVIRONMENT(end);
        BOOST_PHOENIX_ADAPT_SCOPED_ENVIRONMENT(size);
        #undef BOOST_PHOENIX_ADAPT_SCOPED_ENVIRONMENT
    
        template <typename Seq, typename N>
        struct value_at
        {
            typedef
                typename fusion::result_of::value_at<
                    typename mpl::eval_if_c<
                        is_const<
                            typename remove_reference<
                                typename Seq::env_type
                            >::type
                        >::value
                      , add_const<
                            typename proto::detail::uncvref<
                                typename Seq::env_type
                            >::type
                        >
                      , proto::detail::uncvref<
                            typename Seq::env_type
                        >
                    >::type
                  , N
                >::type
                type;
        };
        
        template <typename Seq, typename N>
        struct at
        {
            typedef
                typename fusion::result_of::at<
                    typename mpl::eval_if_c<
                        is_const<
                            typename remove_reference<
                                typename Seq::env_type
                            >::type
                        >::value
                      , add_const<
                            typename proto::detail::uncvref<
                                typename Seq::env_type
                            >::type
                        >
                      , proto::detail::uncvref<
                            typename Seq::env_type
                        >
                    >::type
                  , N
                >::type
                type;

            static type call(Seq & seq)
            {
                return fusion::at<N>(seq.env);
            }
        };
    };

    template <typename Env, typename Dummy = void>
    struct is_scoped_environment : mpl::false_ {};
    
    template <typename Env>
    struct is_scoped_environment<Env&> : is_scoped_environment<Env> {};
    
    template <typename Env, typename OuterEnv, typename Locals, typename Map>
    struct is_scoped_environment<scoped_environment<Env, OuterEnv, Locals, Map> >
        : mpl::true_
    {};

    template <typename Env, typename OuterEnv, typename Locals, typename Map>
    struct is_scoped_environment<scoped_environment<Env, OuterEnv, Locals, Map> const>
        : mpl::true_
    {};
}}

#endif

/* scoped_environment.hpp
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
*/