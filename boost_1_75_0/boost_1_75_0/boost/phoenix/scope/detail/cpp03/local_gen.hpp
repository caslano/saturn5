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
HCDyzSHBeh0kDzF8QWOYaW7h9ur2DR7jufyQaL1JYwbJetlTzHHqGd4ng5KkAY78ssduL0QUcyJBqWP3V5oTPPslJBSZb49nNbWQN/ehCSFWMgUlwXbojmkiAH7YE5DVlIUlhhi2qTgpf2LGQ6WiBClUNfKzPZEq3LPqj3uEbRpi3y60R4aan+421gYz3jyuvfjzRcyMLDLq4BbbA1MirnTvN332tn39ZNjFCs1/7GA8ke2Hq1TNRe3tDj90iy9B03UrjKaPhBUVSbkaFEsqwAFmFOKc9ntooQ6w3toqWO91xuJGiDMs8ygXDtjjj2Ax8Or57An4QS76FqPs172lBFIBlL4i+aa/xXd/qlkQnxNfIOF807IQDH3A36zKFzhGpyqumVs5MRktFrnDftZ5Znql8I3sNkopBUuDT2UO9YPaXo6dTkh2qmiK4cFOcASyWoyLkeOV4CuO5YXS+5NTw/up08yhTneFGRK1woWukI/c0aSSYrv0nSZ+Dunsh5ZLjjdcOakfRm6N8gD0xH+MWiByReYc8AhZOXVbZhyJTbI3OntHcM/4GPPbj/3chKYnHxnEK9RA33kdHhoDpkictp+FQrIjDyNQshW8C3URhjY+NznS6vyp8yFQ3IZ1y+ADMS1Pfb27kZXzZKeaKNGU02jkzYm9sZwPfUaPM71P4egWBa0Bl8f71Ck53ykbAhix1b42m/bse9nv5FcI
*/