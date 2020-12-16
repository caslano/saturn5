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
4TuvbQhNXdvwPzvf+3cZmeO89mmNPP14Xo2Cv2YbjS0zjcaBpzYa159vGC9fahjPvDd+86kZv9MB+09X4NwR3C+C/SjC10HTX7gYv52C8O8i7COwX3ofw2hD+BrsKrwNE/HHLsdaA8IvXAE7wnbAngKPTsAXsSDWBP/V8P/SReC5DHvH4NkPPl+D+xmAJuD8Bjz+0YI9CtivQNhi0N6+DPHBbz3CjsPvs4CnId4TgK/C/nqEPx283ww574TfWxHvOxHPb1uQpqWgB+9v430QePcJIX68lwJnO94fgn8W4Z8H7S3wuxh+H26GPHhfgjS9ohk6BO8toHvXBYZx0cXQH2i+Av4bIeMQ7JkWuJuhG8j3bLhvgH8r3mngvB/4d4D3LqTjpmbIDtxuhIcvgh7x/iTi+PlKxA/3NYBfw/5lwD8RVrMcaYIcdwFegLhNwIoLoVOE9yFsFP5/gr3DhF7A95eQ8zBwphHX689HHAhfBf9PQ/aHQJ5HQZ4Hw/1X4D1oBfQL+4ubQQeedXC/BzQbQB/GezvgM4jjj5Dj66AfQjzN4PFQhO8D/ltgnwLOBwFHgNeKOLc2I20IexNofoC4vgieT4L9XpDjDqStF/bzEGfnSuAAbxns54B+J3i9Efg/BO8t4PNE0Fng+ULQfAA0CcTfA9wFCP8F8M4Bv5chbAA8juL9VIRdDB0cA5+PnY90Ae8zzcgnxBOH302gWYV8+A38jiPs7aDJw+9jeH8c8S26EPpegfzA+1bAjcD5MvyvAv4jwfdK0N4GOAj8P+A9vRIyAf4MHt+GbItXAm8Z9AFYBtrHgcdr8c4h7nciHSvB52pyA7cBfBeARzPsH0WcP6P8hcynAJ8A3nNBO4N3C+J6B3AtxDF4PvIZ9hOAK8HnbvCdAO1CxHs+eJ2G//eAk4L/B+D/aNi/A/8V0N1l5wMP/tOATwP/fsA9F/wPge8y4PwR+A8Azv2XgD4EncP+q2WQYTn8LgQN8J+F94/hXh6CnmC/+CLkFWjbVyCfm/GG3zjy4IEXQ2bE8SHgPQr+H14OuRHvP6jMLAE/4LdAn/cFbAe8G+6XAs4F3gHweC/okng/Be4bweuLsG8EPJzKK95XI47mlZDvfKRrGfgA6sHnJHgvBm0dcKxmpAf+6WboncoQ7ENIw17QPhVyvAvvh8Hv11RHLkKceP8cMAEe1yHskeA9DLwXwW8d4qqF30UtwKH8As7flyONSNNmxPUp8GkDzkuAfyVwYqD9At7vg25fgPcWhC2B7FfBfSPcf6Pyg/cA/N4C/pOg/wlojyB8EmE/Av67EUcH7NfB//nNyLt7ww2+H4F7G3TyLdA8A+4LEf8lK1D+EP5k0P0I77+0QCbKb8j6JoQth/+TgHcvE/kOvwjkNoHzVfB6fwtkwXsN+PXDfghx9YD/n5G+I7BfAz5PB+0NgGdBpu8AN98MvVAewf1W4H0LOPeG3zeovUX/8mHANwE/AvwJsOjaRuM+gA7AVsAQYAKwH/AcwOsA7wJ8AnAz4JeAOwGLr2s0WgHbAHsACcABwFHAmwAfBXwLcBpQ+/RGowWwBtAF2A3YBzgMeMvTIRPgS4DfARY8o9G4CNAG2Aa4ApACXAt4BeDNgI8AvgG4DfBPwAXPhPyAQUAMMAN4AeDNgA8CvgL4HuAOQNOhRmMl4DJADyACSAKeDnjVIaQVcBPgF4C7AEsOQ5bDwAWMA44AXnMYMgC+CvgVoOlZjcb9AJsBA4CrANcCXg74EODbgJ8A7gQsub7ReCAgDHgcoAA4ej14Aj4MuAXwa0Dds5EvgHWAXsBVgKcBXgn44LPBE/BnwAVHkBbAMGAf4IYjkA1w6xHIfwQ8ntM=
*/