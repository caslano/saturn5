#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/vararg_matches_impl.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/vararg_matches_impl.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file vararg_matches_impl.hpp
    /// Specializations of the vararg_matches_impl template
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (2, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/vararg_matches_impl.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    template<typename Args, typename Back, long To>
    struct vararg_matches_impl<Args, Back, N, To>
      : and_2<
            matches_<
                typename detail::expr_traits<typename Args::BOOST_PP_CAT(child, BOOST_PP_DEC(N))>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args::BOOST_PP_CAT(child, BOOST_PP_DEC(N))>::value_type::proto_grammar
              , Back
            >::value
          , vararg_matches_impl<Args, Back, N + 1, To>
        >
    {};

    template<typename Args, typename Back>
    struct vararg_matches_impl<Args, Back, N, N>
      : matches_<
            typename detail::expr_traits<typename Args::BOOST_PP_CAT(child, BOOST_PP_DEC(N))>::value_type::proto_derived_expr
          , typename detail::expr_traits<typename Args::BOOST_PP_CAT(child, BOOST_PP_DEC(N))>::value_type::proto_grammar
          , Back
        >
    {};

    #undef N

#endif

/* vararg_matches_impl.hpp
uxHiIJ8i7WthrrRRq5+Xvi4fCbJUkWJ9Oi7ZOd5Z8bfUDHfW+4fMcGPXxee6ch2ZyL8hO6tUzCXlCeCtTbBp7rC+w+VqHdW9W6WVelVwH/FwYLvXXY+/JB320etw6Hml1yJUt8NnXPb1iXSB14ZsTxfmYOqLTaFWKx195hzmsYWlXyYxl+AusFtam4p9KhR5XNoMfpRxqhC6o7Exm1PL042+e1exXv7IiMNNxTdcRX9K2mnyjoeeqxPv4tjy4N1JlNdgexFH3nJhtpBeAMsz8c6W9j0T5E0/EleCHNS0fqvi+y6XTavnX/KJTL6gBspxtQunbPAdnnE7TuENOcxAntfNJNdgoFto5oVexvTxMLHdZpzKabLND8kzWPes+LqXw7vifJbiZUx/z5/wMvi45lFaozgMVqvpY7/UOQsOjkQ7z4yH48l3Xw5t93N0UMk2wQEOFXCgkBU+SAJ5hg23tCO/6XDxOzKJY5kUKh1Ff7xgs/K9bjFWZ2Q+pfYH+uGxrH6PYSTEYQXxGikoz/STMTIW4tYMeS8MysOCHKW5xC4vXThOvzGVdMe3ts8dHRbPvFN9dWg65tv+14bypl+QGw6fyi4vqAgFfCZD+uK5NICFbEj28iAWsiDY7xvfjVTevqIvbQ1vWSx9pGVf/JnN1NbkexPn+fzf4oiRsn5iMfKjL30FXY3v872rXluJg5oLyWJ2OZMpFuaXsyeKyUQhIe6pnn5MLDO9kFtcKsDp9+xSOldYXCq+Pj9VfOmULO/NSKRfVEBiLpnu5KvdGeHzMorTxshOstEU7zd+AS7VikpYp1QsnVOPhsWLjROsQ/uWCK82IBD2qieeSHt4ir9aOtds41nuNvX7vz66PXqMI5fep0HmhZ+OmXQnhw+yNttz1djfVw4doc8cgb3BYw98/RkKhrpRZiOJk4l0Jp5tTk0fVb9S+GOc8Hw+NaXDt/nCj0xx+HY7XP3rlJC/0xcey997oCvq0Sgu6HwhXNSjrMYnQhjXIVUhyBw58A2VZi51MpUtxC0mOoSSqcJ/xOEyCMN+qMLcIAz7McSbtUNhP/Ns7P/q76sjb7Ox/vrCm7CvFtvdcrFWKknd9kUj7B3vkGGXZFjXjHfZCMN4T+/3k998CvvSUgG9Yaj3vMCiZz+FP+bTOrxQbW/UGvFh5H7qi+lPQvhMca1Xalf6lpc12DWqDvZE1b634/ZF8ZlM6ngiE8Vt88tnUFm5qPQ7lZOKSb9TGbEYgqfyUfEep9rijvo9sRQ/I5mKt4nqtz+o3+oVdeOli/997wmq5+dOzp3sh/9GhR9fTieJ/xPw/QhP77fho+rvayK7uiIOrz+GwkV1ifr+SlxfRbWHjbey6+p8pF5tH1FtheG5fng+NQ87v3pzTYd9SoRVWzUM66c7r9KdCYRdojAh84l9ma/9tMzPJP/+kffi76vdZq/20oh//7z4vS5+/5r+HX7mPH9H/l7MlrIi7FcyDLT7Z3U9veF9IgwOsDdANaT75VPfL8JBF9S/fkLhLzLCsXTqZ87v2/rhFSzfJv1+UfxeF79/mH7H8m1SGa7Q77p8XQr7NoXp8nVJ3tUPYJharjYrL42aT1Ev0b4d0n899OX4lPpYrXv0SJxnFfZMmMswbHPy5XNz9DvEeQR/X6g15nLwNaPfr/d/L23S79gfrqv+kIioKPr338e/UxNCW6CcMygn3ei+dKrQXI7/X8ab2BbHg5IY8W5yvvK9lbTSTSjbXJnvyyLfUFKSdwXl9Ugg9eN7+LvsEixrHWUlc1PdJuSO6vMq1wHkm+oTwz7DYRhEv3+E86V/h8/kH/H32dcvqP2FyNed7ZQv7mrcZr/tt9nE9MQEsJQ=
*/