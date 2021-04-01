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
1e7aI5fYrj1bccaMhHHdAI/J81H/NaeH4KT3HXkK33KZvp/AaOKAAwQeLANI5EmqqhkX6HHk6OLiGVrsogoohuD9mmH9XaAWbF7zgKpR03rdIDsG5NqgbuAV+nMRGDH9mmVeH/Q8eL3k67gNx8bEShYgDhD9Y9Uy1727yOCsgMTPg0doY1uNQrrhSoQTCXmB3TWR4NLAEmXuk3L3TPNidvf9ijAtnC97TaO/mdA+aHVVc0n36altOMhzPB1BTmwqEtgHYKlP7+ou0XHJgvsUhiq8p7i+lXuhLLSrMEFL9+L16jsoInSzN7OGcNGyt4/neTP8tTOIUahEDqSx1sIcDSRAgweKAlLqYgqaXBcYKdrV0GV4nqfmYjol9k8ZF5x3stzF1aUfD+YnsQoiLJoBeekhvHecN++FDN4R7fWabF75FeCweAbbyiakv5SNDa6lKzKoTqBg7qrdJlqdqpidVXzUDBo2wgKiJYZc0gYiPfzdmzgcTHPOhxy9qDgZF5TQe+sLn3Z/HquUjkeuT+9v6UQ88FxKSlZIUndBgN6W+YpaKchXA9MIAhozZw==
*/