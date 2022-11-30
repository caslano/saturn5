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
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
*/