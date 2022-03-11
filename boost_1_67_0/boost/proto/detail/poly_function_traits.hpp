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