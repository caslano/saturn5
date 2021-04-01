#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/funop.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_AS_CHILD_TYPE(Z, N, DATA)                                                   \
        typename proto::result_of::as_child<BOOST_PP_CAT(A, N), Domain>::type                       \
        /**/

    #define BOOST_PROTO_AS_CHILD(Z, N, DATA)                                                        \
        proto::as_child<Domain>(BOOST_PP_CAT(a, N))                                                 \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // funop.hpp
    // Contains definition of funop[n]\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PP_DEC(BOOST_PROTO_MAX_FUNCTION_CALL_ARITY), <boost/proto/detail/funop.hpp>))
    #include BOOST_PP_ITERATE()

    #undef BOOST_PROTO_AS_CHILD
    #undef BOOST_PROTO_AS_CHILD_TYPE

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    /// \brief A helper metafunction for computing the
    /// return type of \c proto::expr\<\>::operator().
    template<typename Expr, typename Domain BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
    struct BOOST_PP_CAT(funop, BOOST_PP_ITERATION())
    {
        typedef typename proto::base_expr<
            Domain
          , tag::function
          , BOOST_PP_CAT(list, BOOST_PP_INC(BOOST_PP_ITERATION()))<
                Expr &
                BOOST_PP_ENUM_TRAILING(BOOST_PP_ITERATION(), BOOST_PROTO_AS_CHILD_TYPE, ~)
            >
        >::type type;

        BOOST_FORCEINLINE
        static type const call(
            Expr &e
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, &a)
        )
        {
            type that = {
                e
                BOOST_PP_ENUM_TRAILING(BOOST_PP_ITERATION(), BOOST_PROTO_AS_CHILD, ~)
            };
            return that;
        }
    };

    /// \brief A helper metafunction for computing the
    /// return type of \c proto::expr\<\>::operator().
    template<typename Expr BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A), typename This, typename Domain>
    struct funop<Expr(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), This, Domain>
      : BOOST_PP_CAT(funop, BOOST_PP_ITERATION())<
            typename detail::same_cv<Expr, This>::type
          , Domain
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(
                BOOST_PP_ITERATION()
              , typename remove_reference<A
              , >::type BOOST_PP_INTERCEPT
            )
        >
    {};

#endif // BOOST_PROTO_DONT_USE_PREPROCESSED_FILES

/* funop.hpp
s1VJVIeP7GG3Wh+58xyLgAQeDxrA8YQ5LClHLaUmqUGVL/BM7Aqhkkt8VZRJXvjzcqnp3A311Tsy5LIXciyBp/G8SLBQpVzNuPOyUU9+bXLhs9SYauz88WbuAgvavOQFNpWPYvZdbMwNs2aNGaw3GGnmiPfPjKWQbT4RR2RIVvz+XqxV+SWq1J9TZB9MuqO1TvGYlTZIKXIGl/TwmwUAWt6F8Xqt9TvK+OgPcTBboRqoW9SOwT75/N9TJWGpjid/sDV0xHoHe6r7clZhF2y/yPAYUFnimwfpUjALkFdXoKFfX6fyFih6+NJHwZxXhUP1UwnmKOGuLrQEQsnq4vhtrTIZFdsrMM2G6TG4OWKm9/FzmxmknFqvwU8AkoIgn/H3ywAHV+CZiBdPEmJ9JyecX9nb5T2a/uvh6CKCl3c1urH5lA4JTNoKbxTrrPDL+x0aMsm4Y2u80Dyxtf8mVpiGfxAVq28/Kf17MzNvExsIomwKrBcGuMX37YbGllsSXfenzVa89Ejq6KbN9aHTR6VTHo8lmAR+SDQ+cgZ5YkPW+EP/XyC5gt/Tfq1DHA==
*/