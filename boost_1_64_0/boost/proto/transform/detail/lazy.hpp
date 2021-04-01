#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/lazy.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/lazy.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file lazy.hpp
    /// Contains definition of the lazy<> transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/lazy.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    /// \brief A PrimitiveTransform that uses <tt>make\<\></tt> to build
    /// a CallableTransform, and then uses <tt>call\<\></tt> to apply it.
    ///
    /// <tt>lazy\<\></tt> is useful as a higher-order transform, when the
    /// transform to be applied depends on the current state of the
    /// transformation. The invocation of the <tt>make\<\></tt> transform
    /// evaluates any nested transforms, and the resulting type is treated
    /// as a CallableTransform, which is evaluated with <tt>call\<\></tt>.
    template<typename Object BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct lazy<Object(BOOST_PP_ENUM_PARAMS(N, A))>
      : transform<lazy<Object(BOOST_PP_ENUM_PARAMS(N, A))> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename make<Object>::template impl<Expr, State, Data>::result_type
                (BOOST_PP_ENUM_PARAMS(N, A))
            >::template impl<Expr, State, Data>
        {};
    };

    #if N > 0
    template<typename Object BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct lazy<Object(BOOST_PP_ENUM_PARAMS(N, A)...)>
      : transform<lazy<Object(BOOST_PP_ENUM_PARAMS(N, A)...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : lazy<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , BOOST_PP_CAT(A, BOOST_PP_DEC(N))
                  , detail::BOOST_PP_CAT(expand_pattern_rest_, BOOST_PP_DEC(N))<
                        Object
                        BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_DEC(N), A)
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    #endif

    #undef N

#endif

/* lazy.hpp
sKL7rGHayZ7uEH/5Yze1RZXJQivLee4cKxtS+8Pgg8o4vbtNcjnsGYOGM6dWUDAMt9ifc88Zg9KoSIi5nITaPS4msBIJXMZdodqomvv6fbT2Ll/TY54uqyi+a7Xa4//XXk+3VziiNMhe14bduWfy+eBX21MVJTHpf7Sy69hdIDWmHsvOVtoIVo6RXJQLQEM18EsyuYX+QLDEAL+lgpnZj2xJxN6/RCR7YHVxidXrwnSCUIERyf6Fxl6RnPLWMaijvYFDLgwa7fD24bBTSV9uIkXCboeYPfOW8FR1foY5pWzHa6KpS3r2AguDnigNTuA9Dk7XQ7EVmPiy962cQkuHvR/mSp0OPNGcs4t0bv6NCf6NzQ64wtpBsc1lQS53P99xddc6Z/IOz1mmj9ClaDieZB9QuySZDOYZg9E6UciHO57bFUcND6AGuZ5IivGvJVfaoSzDYWJkrC71OP7nURLDWidllilFLXrUJw62sRlRv+jsCn+fiWDl+2LBlXCybhJyQJKKosrXiASemjT/Sz6EwD+j+Nb7IQcwmQoc+jkL7boBXJilW+c5Unm9jQ==
*/