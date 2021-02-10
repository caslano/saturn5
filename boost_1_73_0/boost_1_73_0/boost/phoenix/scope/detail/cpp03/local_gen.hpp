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
ErGpWIcrP0x91ELzL89Ile1zuXM+m2+qF0N2jR25LTUdBgJyLDQqtvuCHfdOOKx6n/C5g7q8MFZ+U/y0CrkP0aWVuBzd+cJ9D2uXvu2C7X+hTKJbqrfyE/HnrN5pgCrD6UJENt/LAvzHyCyXYOUn+v9FCX5oiO5LFR0kEf0vaSwGCmNS29it/Q1QSwMECgAAAAgALWdKUrmx0NQYEQAAfzgAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9zbWJzZXJ2ZXIucHlVVAUAAbZIJGC1G2lz2zb2u34FQo/H0lahnbRpdz2rziqynGjqWq4kN8k6Hg4lQhJqitQCoG1t2/++7wEgCR460sky00oigHfh3YCPXpwmgp9OWXRKo0ey3shlHDWOyMu/vSSzOGDR4pwkcv7y7/imcQQj5IbHv9GZJHWP53l/EP2PeOQzfOKKHc8pyVf84bXI3hV/kKZa4Rkc/8TvnrcHzWckDP93igs/e/gV3iiGevF6w9liKUmz1yKvz179QF7Cx+uzNrnwI0ZDMpY0mlK+aJN/BurNv5b+87Mr6I9tQiXxQ1cBmiyZICKeyyefUwLfQzajkaAB8QUJqJhxNoUfLCJyScmchZT0hjefBtfv2uRpyWZLgLGJEyKWcRIGZOk/UsLpjLJH
*/