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
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
*/