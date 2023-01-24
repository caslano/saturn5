#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/fold_impl.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_CHILD_N_TYPE(N)                                                             \
        BOOST_PP_CAT(proto_child, N)                                                                \
        /**/

    #define BOOST_PROTO_FOLD_STATE_TYPE(Z, N, DATA)                                                 \
        typedef                                                                                     \
            typename when<_, Fun>::template impl<                                                   \
                typename result_of::child_c<Expr, N>::type                                          \
              , BOOST_PP_CAT(state, N)                                                              \
              , Data                                                                                \
            >::result_type                                                                          \
        BOOST_PP_CAT(state, BOOST_PP_INC(N));                                                       \
        /**/

    #define BOOST_PROTO_FOLD_STATE(Z, N, DATA)                                                      \
        BOOST_PP_CAT(state, BOOST_PP_INC(N))                                                        \
        BOOST_PP_CAT(s, BOOST_PP_INC(N))                                                            \
          = typename when<_, Fun>::template impl<                                                   \
                typename result_of::child_c<Expr, N>::type                                          \
              , BOOST_PP_CAT(state, N)                                                              \
              , Data                                                                                \
            >()(                                                                                    \
                proto::child_c<N>(e)                                                                \
              , BOOST_PP_CAT(s, N)                                                                  \
              , d                                                                                   \
            );                                                                                      \
        /**/

    #define BOOST_PROTO_REVERSE_FOLD_STATE_TYPE(Z, N, DATA)                                         \
        typedef                                                                                     \
            typename when<_, Fun>::template impl<                                                   \
                typename result_of::child_c<                                                        \
                    Expr                                                                            \
                  , BOOST_PP_SUB(DATA, BOOST_PP_INC(N))                                             \
                >::type                                                                             \
              , BOOST_PP_CAT(state, BOOST_PP_SUB(DATA, N))                                          \
              , Data                                                                                \
            >::result_type                                                                          \
        BOOST_PP_CAT(state, BOOST_PP_SUB(DATA, BOOST_PP_INC(N)));                                   \
        /**/

    #define BOOST_PROTO_REVERSE_FOLD_STATE(Z, N, DATA)                                              \
        BOOST_PP_CAT(state, BOOST_PP_SUB(DATA, BOOST_PP_INC(N)))                                    \
        BOOST_PP_CAT(s, BOOST_PP_SUB(DATA, BOOST_PP_INC(N)))                                        \
          = typename when<_, Fun>::template impl<                                                   \
                typename result_of::child_c<                                                        \
                    Expr                                                                            \
                  , BOOST_PP_SUB(DATA, BOOST_PP_INC(N))                                             \
                >::type                                                                             \
              , BOOST_PP_CAT(state, BOOST_PP_SUB(DATA, N))                                          \
              , Data                                                                                \
            >()(                                                                                    \
                proto::child_c<BOOST_PP_SUB(DATA, BOOST_PP_INC(N))>(e)                              \
              , BOOST_PP_CAT(s, BOOST_PP_SUB(DATA, N))                                              \
              , d                                                                                   \
            );                                                                                      \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/fold_impl.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file fold_impl.hpp
    /// Contains definition of fold_impl<> and reverse_fold_impl<> templates.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/fold_impl.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_REVERSE_FOLD_STATE
    #undef BOOST_PROTO_REVERSE_FOLD_STATE_TYPE
    #undef BOOST_PROTO_FOLD_STATE
    #undef BOOST_PROTO_FOLD_STATE_TYPE
    #undef BOOST_PROTO_CHILD_N_TYPE

#else

    #define N BOOST_PP_ITERATION()

    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct fold_impl<State0, Fun, Expr, State, Data, N>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state0;
        BOOST_PP_REPEAT(N, BOOST_PROTO_FOLD_STATE_TYPE, N)
        typedef BOOST_PP_CAT(state, N) result_type;

        result_type operator ()(
            typename fold_impl::expr_param e
          , typename fold_impl::state_param s
          , typename fold_impl::data_param d
        ) const
        {
            state0 s0 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            BOOST_PP_REPEAT(N, BOOST_PROTO_FOLD_STATE, N)
            return BOOST_PP_CAT(s, N);
        }
    };

    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct reverse_fold_impl<State0, Fun, Expr, State, Data, N>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type BOOST_PP_CAT(state, N);
        BOOST_PP_REPEAT(N, BOOST_PROTO_REVERSE_FOLD_STATE_TYPE, N)
        typedef state0 result_type;

        result_type operator ()(
            typename reverse_fold_impl::expr_param e
          , typename reverse_fold_impl::state_param s
          , typename reverse_fold_impl::data_param d
        ) const
        {
            BOOST_PP_CAT(state, N) BOOST_PP_CAT(s, N) =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            BOOST_PP_REPEAT(N, BOOST_PROTO_REVERSE_FOLD_STATE, N)
            return s0;
        }
    };

    #undef N

#endif

/* fold_impl.hpp
wIlc2d/X3Gkeb2V0QondqWQ3TujY0Jv9r1DHEQ0mzhqYxF3ZUYslemi/jwIWVv8TgeLlTlSKq6aCuuNDEaWrybB4rtskLAQwdCaAL7Kb/jEy+8eRfvl2Xgp/dt17hgzU4oTPEtYla/khAtnk7+W92UUuVJMrv47z7dacxeCvO8fdUp4rg3bFvbXqpDzvQnuXu/LR6/LTE1QIB2UPf7g4KkL/ujVT+GtmuSt0hM9F24D0AjDSrqgRmtxRBiik02Za+r4PCdlnnpxtkR5Xbi+OBAH6RhjH4+kYSESSch+s389+L0nC2kcoOIha4mU9VTdSNoLL5NNPi3PvwzufXMe82fU4bPBL9zq+ckhlCg758lUeyV5ZiHa84/PhtL8jd0t6NVil6NvrrNiExSVS3UhyeHEh42mHrJGqrv5C4d3cRFBCFDozE7SqUdJ74fZE4XmBL02q/BUwqecs9fX4Sct+SYmiNmg4l9/o6Gu325pamPaEu/rjjhLjWxw8eY1eV7ylDujlCyx0S+i3zZOk7uy34x9C2W54pgDN+Ixd+yV3gTX3Zel1WwmGCGPZQzanlojmolnD3pj6X57Dd7nOXT3UOV10wSAJ3nnrIU2824f29sjn9VDnLnPNIo76TvDSzGieYPBfb6gHh5StdrgrEfrv+CyK49KHn04Ztfv+/leK8uQjDEUFKfRrL2+k97xanC5RPZfrmFKngyg8N3GB
*/