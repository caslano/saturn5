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