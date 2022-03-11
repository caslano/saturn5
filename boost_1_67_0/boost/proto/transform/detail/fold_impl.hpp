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