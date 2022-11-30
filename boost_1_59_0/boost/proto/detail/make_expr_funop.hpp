#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/make_expr_funop.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_expr_funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_expr_funop.hpp
    /// Contains definition of make_expr\<\>::operator() member functions.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                     \
        (3, (2, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/make_expr_funop.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    template<typename This BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct result<This(BOOST_PP_ENUM_PARAMS(N, A))>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
            >::type
        type;
    };

    /// \overload
    ///
    template<BOOST_PP_ENUM_PARAMS(N, typename A)>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
    >::type const
    operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, const A, &a)) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
        >()(BOOST_PP_ENUM_PARAMS(N, a));
    }

    #undef N

#endif

/* make_expr_funop.hpp
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
*/