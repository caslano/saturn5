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
XgAm2CkEnwZgIIJpmF1yA0yQP+4SXfg4PY+RJxxXI33H7PDjsaANpIpbEWCvZFkgTEaWSsVPb+LeS+i0k8b+l4wnnhbOMf9AD4jbY8x7OS7euBGHncexoc3Frd8ez8tOZYcgdT1130rSwNYncB4o3FWSXgFehcCBq8zXgGLv/sQart5SQT18NPxwaMHvmuSuvLshiX5xJw9vigMPu5L0FGU4TrdiXW3OnN6mZZGQcH2cBk7StxHhn3hxPsfiRVm4yCKZ4R0wbHc9oMBVI6e4ZY/ghAkuA35A/6h/gdtUrdHahotL0F4AI/GaniZEpUvOVy4gfsXjdDAnl2xFd1Ppt4+V4Hh3E0AzytgH5655sOnX4aJri1MOK9lbdLpCTycXEy8VNZiE7DWRrW3amKHO2pIXgSrEFijv1WdL1FjI7iqaw7u9RHahQ6IAFbfMmOCQHidZi3oTcyq86IdpkrWApNvaeP8dWAJ6F/kEJECwwjV1DujbFXUmgQ7tcNFK7e5bl6+UeWWETtd1Hp5d1dqnd8QReKOiVMjNYUxW3pho8m8X9EFJ2Yzgddw3ybJx5RGqKwqs7ybXr9avMzu7FA4rTk+OiYntnR9wcKmc9UWUi3R1ughAdqdS+yReIlJO2fqzC469mWOxrYuxFx+kacQV6SdJBAg9d39qr/++OW/I20y7eRVBDjj4K3NyKvFU9S/vYpycPJy7rpjBv9Iq
*/