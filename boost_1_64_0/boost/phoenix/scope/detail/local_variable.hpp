/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2004 Daniel Wallin
    Copyright (c) 2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef PHOENIX_SCOPE_DETAIL_LOCAL_VARIABLE_HPP
#define PHOENIX_SCOPE_DETAIL_LOCAL_VARIABLE_HPP

#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/preprocessor/enum.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>

#define BOOST_PHOENIX_MAP_LOCAL_TEMPLATE_PARAM(z, n, data) \
    typename T##n = unused<n>

#define BOOST_PHOENIX_MAP_LOCAL_DISPATCH(z, n, data)  \
    typedef char(&result##n)[n+2];              \
    static result##n get(T##n*);

namespace boost { namespace phoenix
{
    template <typename Env, typename OuterEnv, typename Locals, typename Map>
    struct scoped_environment;

    namespace detail
    {
        template <typename Key>
        struct local
        {
            typedef Key key_type;
        };

        namespace result_of
        {
            template <typename Locals, typename Context>
            struct initialize_locals;
            
            template <typename Context>
            struct initialize_locals<vector0<>, Context>
            {
                typedef vector0<> type;
            };

        #define M1(Z, N, D)                                                     \
            typename boost::phoenix::result_of::eval<                           \
                BOOST_PP_CAT(A, N)                                              \
              , Context                                                         \
            >::type                                                             \
        /**/

        #define M0(Z, N, D)                                                     \
            template <BOOST_PHOENIX_typename_A(N), typename Context>            \
            struct initialize_locals<                                           \
                BOOST_PP_CAT(vector, N)<                                        \
                    BOOST_PHOENIX_A(N)                                          \
                >                                                               \
              , Context                                                         \
            >                                                                   \
            {                                                                   \
                typedef                                                         \
                    BOOST_PP_CAT(vector, N)<                                    \
                        BOOST_PP_ENUM(N, M1, _)                                 \
                    >                                                           \
                    type;                                                       \
            };                                                                  \
        /**/
            BOOST_PP_REPEAT_FROM_TO(1, BOOST_PHOENIX_LIMIT, M0, _)
        #undef M0
        }

        template <typename Context>
        vector0<>
        initialize_locals(vector0<> const &, Context const &)
        {
            vector0<> vars;
            return vars;
        }
    #define M2(Z, N, D)                                                         \
        eval(locals. BOOST_PP_CAT(a, N), ctx)                                   \
    /**/
        
    #define M0(Z, N, D)                                                         \
        template <BOOST_PHOENIX_typename_A(N), typename Context>                \
        BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM(N, M1, _)>                        \
        initialize_locals(                                                      \
            BOOST_PP_CAT(vector, N)<BOOST_PHOENIX_A(N)> const & locals          \
          , Context const & ctx                                                 \
        )                                                                       \
        {                                                                       \
            BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM(N, M1, _)> vars               \
                = {BOOST_PP_ENUM(N, M2, _)};                                    \
            return vars;                                                        \
        }                                                                       \
    /**/
        BOOST_PP_REPEAT_FROM_TO(1, BOOST_PHOENIX_LIMIT, M0, _)
        #undef M0
        #undef M1
        #undef M2

        template <int N>
        struct unused;

        template <
            BOOST_PP_ENUM(
                BOOST_PHOENIX_LOCAL_LIMIT
              , BOOST_PHOENIX_MAP_LOCAL_TEMPLATE_PARAM
              , _
            )
        >
        struct map_local_index_to_tuple
        {
            typedef char(&not_found)[1];
            static not_found get(...);

            BOOST_PP_REPEAT(BOOST_PHOENIX_LOCAL_LIMIT, BOOST_PHOENIX_MAP_LOCAL_DISPATCH, _)
        };
        
        template<typename T>
        T* generate_pointer();

        template <typename Map, typename Tag>
        struct get_index
        {
            BOOST_STATIC_CONSTANT(int,
                value = (
                    static_cast<int>((sizeof(Map::get(generate_pointer<Tag>()))) / sizeof(char)) - 2
                ));

            // if value == -1, Tag is not found
            typedef mpl::int_<value> type;
        };

        
        template <typename Local, typename Env>
        struct apply_local;

        template <typename Local, typename Env>
        struct outer_local
        {
            typedef typename
                apply_local<Local, typename Env::outer_env_type>::type
            type;
        };

        template <typename Locals, int Index>
        struct get_local_or_void
        {
            typedef typename
                mpl::eval_if_c<
                    Index < Locals::size_value
                  , fusion::result_of::at_c<Locals, Index>
                  , mpl::identity<fusion::void_>
                >::type
                type;
        };

        template <typename Local, typename Env, int Index>
        struct get_local_from_index
        {
            typedef typename
                mpl::eval_if_c<
                    Index == -1
                  , outer_local<Local, Env>
                  , get_local_or_void<typename Env::locals_type, Index>
                >::type
                type;
        };

        template <typename Local, typename Env>
        struct get_local
        {
            static const int index_value = get_index<typename Env::map_type, Local>::value;

            typedef typename
                get_local_from_index<Local, Env, index_value>::type
            type;
        };

        template <typename Local, typename Env>
        struct apply_local
        {
            // $$$ TODO: static assert that Env is a scoped_environment $$$
            typedef typename get_local<Local, Env>::type type;
        };

        template <typename Key>
        struct eval_local
        {
            template <typename RT, int Index, typename Env>
            static RT
            get(Env const& env, mpl::false_)
            {
                return RT(fusion::at_c<Index>(env.locals));
            }

            template <typename RT, int Index, typename Env>
            static RT
            get(Env const& env, mpl::true_)
            {
                static const int index_value = get_index<typename Env::outer_env_type::map_type, detail::local<Key> >::value;

                return get<RT, index_value>(
                    env.outer_env
                  , mpl::bool_<index_value == -1>());
            }

            template <typename RT, int Index, typename Env>
            static RT
            get(Env const& env)
            {
                return get<RT, Index>(
                    env
                  , mpl::bool_<Index == -1>());
            }
        };
    }
}}

#undef BOOST_PHOENIX_MAP_LOCAL_TEMPLATE_PARAM
#undef BOOST_PHOENIX_MAP_LOCAL_DISPATCH

#endif

/* local_variable.hpp
EYGpd4mESD25EMLoM45oWylCXIddb2FQll6lFfgbEoksiDWDj7bdIsSiYfPpqbg+T9iKtUW3WqW66CRSRH24Wh5eu+hnAxFtTIjFUdtCHJEVkQ4wYZ8aZipXm3g1pEoQIVRHPizp3O+ITSghCohqEGPrKeq2U+SWU7gMLRAtQy1VZxm/VipkUMqaz4HEFf7q0UjYiaOylc9iPMqZb8IkJhAYtPgxDuI97EJnIVRKNuZNVeJmKXHLEH9Rh14nqqrqVqXuZk/p3Ln4HSO9RrgN94yXAJ8hqCWRcwZerdWLdJKKjIL3qAPeoCigC7Uwf/TRRNgsUbkT0y1h4uOWMIpBQ5iVqZqoQNFu1BEyVQhiFyrajThCpioOtVjMWMICjLnPJKz5j3mEKXp3D5t/2d3DScydImEfnrWiF4+1mSPseJaH5khRt3aibuuc6V5Mt32Y0+3BnG7/JWLvJca+iz+yQ+cikRuxOvQY2zHqrZjTXPETYaUc9YByPM19PrGt1IqRyUOHK3KIt5CYFtgCUuwiut5YGykxN1HCN1DCN0+ib5z4o/bGflWHq05YZNzpVrTwcSWio4raT6nXe5E7NbF2aWLt0MTYnYm9M3OaXZloOzKxd2NOvxMTexcm9g6MehRcUloZoFzDGKbMpYNS7lRcBBP5HQpIxGvkNyiUbzToI1W4NNwYVdUQVdXQzRhNNaqi2tBNyWuoDPvSQ6XBG2bufXqf3qf36X16n96n9+l9ep/ep/f5L3o242w5CbwXnAA+DO7LDzNM0iZHcZ98KEmbCmgBMkvkB97BfQBuTlcYEvwHYMC5n4qsX7/wo8F2QDehm25CFN1BUXR3Q/cKlW52DN20oG4jA8QZlNA1wBm5B2LqWqPoHoOukXR7EG7iX5K0Jq6L9zjDTYOuWZXextOHCzMHp9HQtYr0nkbXGkU3G7o20u1BuCXQtYv0xhluFXQd3eqGllS5LunFrhvLoetU140I3dhltAa6Wep8jqkbGecW6GaLfI4abuzy3QHdctLtQZwPQHe+CDdqnGPncyd0F5BuD9Kb+k6StkqUb5zpzYDuQqEbZ5yd0G0JlRFXzI4R58TE8HCLoXuPWjc9tm5SUrc6Cd17Kc49CHcNdO8j3R6Euxm694vyPU241ijh7ofur9S66bF0I8M9Bt0HRRnFGW7yX5O0DwndOMPNgG5Lm6qMsqPrjo4Srgm696h1G0+vqw43B7r3QjehB+HOhu59pNuDcAPQbVXFGX/PONwV0P1lmG7CGYfbDN37Kc49CHczdH9Fuj0Idzd0N0I3mapUnPl8ELoPCN048/kYdB+ELpPiDzexA/WZ68Yf7ijobhJxjjOfddB9WOjGmc850H2Exzn+cGdD91GuG3+4Aehuhi6Jk+PM5yboPiZ048znzdDdInTjTO9e6D4udONM72HoaoSuah4rncE8lr2bpO2n0s0WumcwnxwF3RSVbqPQPYO5mRW6Wq4Lc5xxLoTuEKEbZ5yroCsL3TjjvAq6Q4O6iXHGuQW6aUJXHeczmHtvhe4IoauO8xnMY3dD98Ju5as9wznDYehmdCvf9DOcMyS+l6S9hHTPYD7ZPdx06I4WunGG64TuZSLOcc6R5kB3rNCNc460ArpXkG4P5maboKsj3R7MzfZTnFmwf45zDXsIupeTSyl+3U7ojoOz7B6snRPfT9KuEXGOcw07Cro/FbpxrgdN0G3i6Y0/3ELo/pzrxh9uFXSbKa96sGZfBd07SbcH69+N0N0k8irOOtkG3YeFbpx18hB0H+F5FX+4p6D7KNeNP9xRhzHuU171oA06ofsY6fagDc6G7pZu9Vl7huNRA3Qf71af08N0Y4fbDN2t3do=
*/