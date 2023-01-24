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
swWa9/3BNhi3onfjY/ytrEibD2Xl7vqXNHPfv0uzEESn52nrWwE6mQk4HM+6ZSo6lRUT14kj8sD2XgzWA7i/qcaOuGB/I+SuYuJgszAAt1DK4gWKFvlb3N2tuLu7FdfiNjO4F6e4FytQ3IoM7u4+uDsDw2Cz/3qy2WQvvrsv5+Ik5+JJznk3v9lbjVTmJCYEtH3kfCdiH/nbWMfjXWFcuJ+PAV/VmmJp94nSqfR+lBd5ayge83gBLOAvo10uoVijNf48zP6i+SU21XZkWNI7HEfvZhkA++FcVTh+Dg5ei61NF98GH6wwjvSMQx7UpH4XO8GOHvyOWwfDuSb/7LqSrl3FydhrhhlDPuOOelPfzUtkSVXhk8zNCdgj7f16vyA/AkqVx3r6mWT28FbGP0IImdz/DrWpSr+3w7jTcb3TWpl9zkFpAUYLPcutcxHwLITE8HSqcS3rrWRcKO30NtQL/jZqF0o7dFboL32fnXfKQcG23SKN7DwdqJr9SRmpd4mPIDncTTvXtForP385DI+GjSj9k2iuhStJQorkn9ZPQ8t1dpwIfhkpKTcsHMlmZM3LVyy3FVLdG0fW2KEq72pDNgrToZlqRmoN4/Sll0FzMaX1+Jf1lV0Wy5HysmbsVliZa56FzSswBj1r2eOz6525jMvw6vluvjJreRL9hRtgF3EtsAT6rRa9zKD+MgiwFwRtdkszB/1GyzXBVDV6
*/