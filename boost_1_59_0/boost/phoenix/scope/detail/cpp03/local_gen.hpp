#if !BOOST_PHOENIX_IS_ITERATING
/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/phoenix/support/iterate.hpp>

#define BOOST_PHOENIX_EXTRACT_LOCAL_TYPE(Z, N, D)                               \
    typename proto::detail::uncvref<                                            \
        typename proto::result_of::child_c<                                     \
            BOOST_PP_CAT(A, N)                                                  \
          , 1                                                                   \
        >::type                                                                 \
    >::type
/**/

#define BOOST_PHOENIX_EXTRACT_LOCAL(Z, N, D)                                    \
        proto::child_c<1>(BOOST_PP_CAT(a, N))                                   \
/**/

#define BOOST_PHOENIX_EXTRACT_LOCAL_KEY(Z, N, D)                                \
    typename proto::detail::uncvref<                                            \
        typename proto::result_of::value<                                       \
            typename proto::result_of::child_c<                                 \
                BOOST_PP_CAT(A, N)                                              \
              , 0                                                               \
            >::type                                                             \
        >::type                                                                 \
    >::type
/**/

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_LOCAL_LIMIT,                                          \
    <boost/phoenix/scope/detail/cpp03/local_gen.hpp>))
#include BOOST_PHOENIX_ITERATE()

#else

        template <BOOST_PHOENIX_typename_A>
        BOOST_PHOENIX_SCOPE_ACTOR_GEN_NAME<
            BOOST_PP_CAT(vector, BOOST_PHOENIX_ITERATION)<BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_EXTRACT_LOCAL_TYPE, _)>
          , detail::map_local_index_to_tuple<BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_EXTRACT_LOCAL_KEY, _)>
        >
        BOOST_PHOENIX_SCOPE_ACTOR_GEN_FUNCTION (BOOST_PHOENIX_A_const_ref_a) BOOST_PHOENIX_SCOPE_ACTOR_GEN_CONST
        {
            typedef
                BOOST_PP_CAT(vector, BOOST_PHOENIX_ITERATION)<BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_EXTRACT_LOCAL_TYPE, _)>
                locals_type;

            locals_type locals = {BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_EXTRACT_LOCAL, _)};

            return
                BOOST_PHOENIX_SCOPE_ACTOR_GEN_NAME<
                    locals_type
                  , detail::map_local_index_to_tuple<
                        BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_EXTRACT_LOCAL_KEY, _)
                    >
                >(locals);
        }

#endif


/* local_gen.hpp
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
*/