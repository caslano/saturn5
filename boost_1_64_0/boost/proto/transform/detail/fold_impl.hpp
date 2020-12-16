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
2jhTLFdLOddWPmRg+q2bfKEC3+HCrzHwgr5Hjz43HRA1/Vqz5nVSNa9XModeVkkPr9SFJ30QlL6QyrvS8Chuq5rlDofvRwyPIbWS1ss+6lsv64/1Rbo2rRuA/0ZE5lZuDBRldPjWIIeWkNwo26Q7eF9AeqlOL6d6fNzIMLIl1TMQ7TJ+c6g6OrrL1GUMFGXpvnsV67vXMTv9pLDT6xvwEXb6KbLTT4v1t2K9f/3ts0T3OaKr4XOhb6/tLYC1/edFWTeKtb6bqKwvuHsXgWV5A0FPejQ3ssstUYB5uTeLcr8kyv0ylXtLjXKpjk6zYxzs9nqKgLP+8lVbLr7btrpVyPN1kudrtL54G8nzjZrjyyCejKuOulJ4KZTdU2s8Al225BsfxyC47m5ndbid1eEOUYdvUx32UB2+Q3X4rqCrE/b1faK7k+iC5147oWNXXP3d6vgHlK9j/DYrZbe5eVma8v9w4vyZ0ogvP9I2/49qrPU7+dcv1etEPTTTt5wkxvL8MfG8hI+nNDbq9N3GV+TK5SoaLJMtuXtDgMNflatmEHEQBn6P3t/y4Kg+0d8LeINCdSj9E6Rb1NBgajRb2QKY68vmAeaubc2A8/gp84/z1falGENRXGWnqZhNGhsK8hfkw6PMX1gAs72f1xz7wt2R/nSpsouz4TCrz1+6fKY4+oSPw1+xUqI6/gJ4JpOy41Jpc+aEjg4DRP0tfCiaMEA+Lu1ctngxuSCC3+jQ5kpQO14+83jfZ+DZoZwnq2K89fMkhdJonLboInr/Xe9ql5hcOdfZKTumlbLDuXIlW8oO6TVvRltUTwp58j58+jgFvOWDcTF4vJ2Lcer+SY63h3HbZXHfAzTWrqCx9le+sXZVOBqOh/r03NnzrwIG3qtrzyP8QzOfRUgc2cdvXD/rjxEKI7nMLncP+LdGbh02mLYom7Gb6vBgQLwwNlawcUInL4f6cXdBv/bSb8rUvF18vdtvfQSIc6nshwLKTq3Fshxm3Lx8DoUMwWOcp3/MK7GWzJuAg3kffVj490fE2PoH8u9/nDh+SI8MF0pukRZi+/FjNXlktxdT5jdOPR4+CMVMj7MxbC/xW+9rD7PfjoMq1mb/ZNrBCJOrbBl1+yH0nc1nUnYO84Txs06Jug17aB7zJJ/H0Disc1JJdhwWCD5Pq1NW7r8InT9FOl9IOv8r6fxptj9ZrLff3y3y/53yP0Nj9z8o/z8F3TOibZ8lOtVYK24qZMrFVCGf1QNPNVv2qivhtp2nNnrl4rutdz2+c3mmNZI8+FdTTdd40M1orDVuQLmbUznn4IIrC4dZW5nFyp7daOPrA/Cdx9dzkMbHF18fSLIcJGS+Uuiwgega8W/tOEJvakR6NmH9NR5aa7uJQPC+2WzLxndbl1YhUxvJ3kJ6bCeZ5jXade2icta1pyu1l6eLSLv9x2RX5XJqswnBTT85BMCpKpUCtJgeWmJgzdpXOTDz8LHr7w4FbYNH26E6qf/MZ1dZd6tyIbM1jdEPNS2U0sPZ1M6iUUUAfDw/t488jvb2stdioVmvYHf1DXSHaV/IwLDa7cBWYl1sKq2LvbAROQb6MIkGhV6fNbtHtHcegEBRRreHNTq63Q3dnoGy7RxyeLPzmODmdIZ8E2ihS8CHS4VqkdZWALtQwzbDokHn5r9YwzBLKJcyph0OB92lGlYeycGe9Hhm9sAXMn03TDGMUziZhHKNkjjA808fZn71CGFfLyb7uob8y5FkXy9prOXPKZDUsWhhyBTsg5CveKko62ikef86hso6luhWj++jylgyQfdHWFXE5qznGwJwzEcsYv3q5cxHLBY+YgnSS4SP6CDZlrJ++gGmx+NE3ZZT/is=
*/