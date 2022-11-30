#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/poly_function_traits.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/poly_function_traits.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // poly_function_traits.hpp
    // Contains specializations of poly_function_traits and as_mono_function
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/poly_function_traits.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename PolyFun BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct poly_function_traits<PolyFun, PolyFun(BOOST_PP_ENUM_PARAMS(N, A)), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<BOOST_PP_ENUM_PARAMS(N, const A)> function_type;
        typedef typename function_type::result_type result_type;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename PolyFun BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct as_mono_function_impl<PolyFun(BOOST_PP_ENUM_PARAMS(N, A)), true>
    {
        typedef typename PolyFun::template impl<BOOST_PP_ENUM_PARAMS(N, const A)> type;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename PolyFun BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct as_mono_function_impl<PolyFun(BOOST_PP_ENUM_PARAMS(N, A)), false>
    {
        typedef PolyFun type;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename PolyFun BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct as_mono_function<PolyFun(BOOST_PP_ENUM_PARAMS(N, A))>
      : as_mono_function_impl<PolyFun(BOOST_PP_ENUM_PARAMS(N, A)), is_poly_function<PolyFun>::value>
    {};

    #undef N

#endif // BOOST_PROTO_DONT_USE_PREPROCESSED_FILES

/* poly_function_traits.hpp
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
*/