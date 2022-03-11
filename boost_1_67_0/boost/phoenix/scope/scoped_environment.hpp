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