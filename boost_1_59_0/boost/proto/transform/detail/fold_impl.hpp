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
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
*/