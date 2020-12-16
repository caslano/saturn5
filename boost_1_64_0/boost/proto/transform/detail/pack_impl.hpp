#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/pack_impl.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/pack_impl.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file pack_impl.hpp
    /// Contains helpers for pseudo-pack expansion.
    //
    //  Copyright 2012 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY), <boost/proto/transform/detail/pack_impl.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else
    #if BOOST_PP_ITERATION_DEPTH() == 1
        #define N BOOST_PP_ITERATION()
        #define M BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY, N)
        #define M0(Z, X, D)  typename expand_pattern_helper<proto::_child_c<X>, Fun>::type

        template<typename Fun, typename Cont>
        struct expand_pattern<BOOST_PP_INC(N), Fun, Cont>
          : Cont::template cat<BOOST_PP_ENUM(BOOST_PP_INC(N), M0, ~)>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };

        template<typename Ret BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct BOOST_PP_CAT(expand_pattern_rest_, N)
        {
            template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PP_INC(M), typename C, void)>
            struct cat;

            #define BOOST_PP_ITERATION_PARAMS_2                                                     \
                (3, (1, M, <boost/proto/transform/detail/pack_impl.hpp>))
            #include BOOST_PP_ITERATE()
        };
        #undef M0
        #undef M
        #undef N
    #else
        #define I BOOST_PP_ITERATION()
        #define J BOOST_PP_RELATIVE_ITERATION(1)
            template<BOOST_PP_ENUM_PARAMS(I, typename C)>
            struct cat<BOOST_PP_ENUM_PARAMS(I, C)>
            {
                typedef msvc_fun_workaround<Ret(BOOST_PP_ENUM_PARAMS(J, A) BOOST_PP_COMMA_IF(J) BOOST_PP_ENUM_PARAMS(I, C))> type;
            };
        #undef J
        #undef I
    #endif
#endif

/* pack_impl.hpp
wUe01cuIxyJhF7OErhcT3RJW1i1C10uJ978odlpGeY6jPD1c188jvnb1fTzTd5T0fUKgviUzn8IlktYOxVzAnhnwiynhrL3qRFz0CtLHSUyHl7H2Wina65QWfER7nUo8QkR7ms+v2P2SJkXjZRkO0oPReGlgbI4FWHmr8tINdIe4h873djGdtjynd+7w9qiII8JUr51kKz1Ur1XWDhtuZnPcSIvV02qhpzUt+Ag99RG/tS0TvxUy2bPK5h6XlQ/f2duOov/ESZ7+FtpPIXmSgm6d6GfriW4Ds5E9Yo1lE/GeRTHYaZTnlSzP10SeVwHHy3k15UmxPK8VbXQO2W+a6jBIeTKiDv2Cd5boNjPe1wtfsYXynEV+OUd5zmB5IqKcEcrzJcozSnnyRLd6Evd7Qkl09M6BpO+OhMRRWxeJ783P61w9nTZMj3gxxzbwnaPS1coWc7nco20gWjqGz2MUOrfl4DmfeYibLCe6H2neZnXeeu2he7Il1ocXPIffWlnBffc++kPXX1eYv+4kf13l/vo5nNe/Vdj5DrKRV5HN7iQb2cXs6pds7n2W8CWvbcFH+JKzicc5wh7vFvPU3UR3LtEtnyDuGRvz+OOdg4VveAPxPz9oPH0e9wfc9rkgYDy9sHb80lUrgCGkNwaczca6Nwu9X9SCj9D7xVTft7C2W8fGgbcKHpe24CN4vI14vN3OTwPOo6bcM6jLl5mqsDTZ2YjwjZdROU+RD34XlXO5sJG08I3vIbr3snFkFVsrvELkfz/l76Vx8gOU/0qmkyuYTq4WOvlgCz5CJx8iHh9mPC5sEGvvlGeY6vcRyvNRlucFoizN/+OirE9QvutEvYaFbV9PdJ/Cv/z8SBH/qxDvOvF79J+hPDeIseVzJMOdJPsNRPd5LoOUFXQ3tdj9wbPoPp4Sb7F8kfKg73t5+H39TY0kO+MBnN03I9lvabFyNBGui3h8VciBsmBHfjlu5Wkam/k7K4OWB/JbHXIe33RkaPgoW/u/nXS0EHlnOHkxntj8e4CnvVPGa4a6o8XaAfKgzuK+AfCOXognfeSZoO8JPijbx+dOUW/om9ODHztfCfq7Bb8mJdZmgT8M+OnKOdd0N+n7HnzuJX623aarexk/0EMXDA9+P7H1BM7eaQFPXz1/xtuH6rlHtPEvyG5fP7n4JmBOOQ6OfNr9bmwMOeaC031IQ1bIoWWycj1A8IpyP9YGrh7ThnPVr6geyEtt5NhZJ/NzvxW+Q9M+KHzH7yiNfkpn2axuNew+knOwya/bh5lupZ05MRz25Vg7fpz48HZ8VOAXKj/+Twy/MUD2vcLuUK4P/6S1E97+0LW/Ln8R48dNZBPfku9PK3F3CmX8zeoBftTBV6keVbKxvxM/yMfOR1id/ZPKf7rFof8Xq5eGVUV/Uq1OW3+Lzd2mtjKfztqkrhX8RX3rW+W9aNkH6xD1WN/5tNDPzNYJ39Qz5yhj5oeJbScRCC9mmd1qx7tjm8f+BgWK3MvvT56q7Lt0aEvo3a+fua0Or8fFmf1GwOXZ8qZWJ/2Aa/+EBy2lbf4DALtS5G+j/AcweugNdbJtczC+8zHxEKS5fz3U0TXktXleIPIcJvK8sJXkIn4VxX8XBG9KMfxhhOd2+yIq8342v35xq19fR7J8Rcr3Es8ugBcyvZT0jiZErGTpjiG6ZqI7Fmmu06ZGf79f1Opvs7uE31jMZHhA2GaHxSGvH7eM0vBpY9pWwz6JDy/neNZP6P1DvEnofz/gRKYD4kl4m+b9XdtvRZyHOpnVF3uioGN+FHKcYvHAjW3rEMMvNP1ZnDMmGee0SvqA81nA91A77pHjB2h7geO0EabvZ8Ra3Bqihd4CdVE=
*/