#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #if BOOST_WORKAROUND(__GNUC__, == 3) || (BOOST_WORKAROUND(__GNUC__, == 4) && __GNUC_MINOR__ == 0)
        #include <boost/proto/transform/detail/preprocessed/make_gcc_workaround.hpp>
    #endif

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_EXPR_MAKE_ARG(Z, M, DATA)                                                   \
        detail::as_lvalue(                                                                          \
            typename when<_, BOOST_PP_CAT(A, M)>::template impl<Expr, State, Data>()(e, s, d)       \
        )                                                                                           \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_gcc_workaround.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_gcc_workaround.hpp
    /// Special workaround code to make the make\<\> transform work on certain
    /// versions of gcc.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #if BOOST_WORKAROUND(__GNUC__, == 3) || (BOOST_WORKAROUND(__GNUC__, == 4) && __GNUC_MINOR__ == 0) || \
        (defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES))

        #define BOOST_PP_ITERATION_PARAMS_1                                                         \
            (3, (0, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/make_gcc_workaround.hpp>))
        #include BOOST_PP_ITERATE()

    #endif

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_EXPR_MAKE_ARG

#else

    #define N BOOST_PP_ITERATION()

    // work around GCC bug
    template<typename Tag, typename Args, long Arity BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct make<proto::expr<Tag, Args, Arity>(BOOST_PP_ENUM_PARAMS(N, A))>
      : transform<make<proto::expr<Tag, Args, Arity>(BOOST_PP_ENUM_PARAMS(N, A))> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::expr<Tag, Args, Arity> result_type;

            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param   e
              , typename impl::state_param  s
              , typename impl::data_param   d
            ) const
            {
                return proto::expr<Tag, Args, Arity>::make(
                    BOOST_PP_ENUM(N, BOOST_PROTO_EXPR_MAKE_ARG, DATA)
                );
            }
        };
    };

    template<typename Tag, typename Args, long Arity BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct make<proto::basic_expr<Tag, Args, Arity>(BOOST_PP_ENUM_PARAMS(N, A))>
      : transform<make<proto::basic_expr<Tag, Args, Arity>(BOOST_PP_ENUM_PARAMS(N, A))> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::basic_expr<Tag, Args, Arity> result_type;

            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param   e
              , typename impl::state_param  s
              , typename impl::data_param   d
            ) const
            {
                return proto::basic_expr<Tag, Args, Arity>::make(
                    BOOST_PP_ENUM(N, BOOST_PROTO_EXPR_MAKE_ARG, DATA)
                );
            }
        };
    };

    #undef N

#endif

/* make_gcc_workaround.hpp
5kcWkHxbXj2U1g/K5EGGEcCUbai1Xa8xjgPPg0fyPfQZkLtkxkqqcr+T1hg902fV7bQhExokRi01HVTuUyBS63BcoSmHC8e4194tSE+7/kNW0KKA+0Pad4retPfD8YC2b/RGonFtT4ULRhWZs/UpsfSVpV/s26WfRoOkdeQMzwbBwgJd3gHoB5Xhk/M97sy2T9iT3xQrzcXmjjShB+tDSfov6X99tW/qvRcXqHuubZpSvFLakDW8kkvZwLWr6maC0xIGLV7pngqSNhIxFXnxTijazDZdVu0M4EbCwYQ5Ti/z4Vhtgf1mATngE1L747XfYCKZD8dqV8patlHg3+LRz/TlNyO0v8WTnF4fc9arlt2MgD5Bf9d8sk3QxwLQPL7On6KTYSZGxON65T7GfLLNTAsXX+pgnxczvxGIzup+OCOTsw6MHR5/zZEC0ixlkfFVzjG6bt3LSxl61UDjIYBdNPHVQ9A+/qoupaYLE6b/XCRmUfYSsHEkdKPc54a+2XKNUbqmersrMIeuu1Y3d4etR7gyVVatwdpxz4kcuVTeTUj+fLDrdIRSkEP4DvL4r4OD8B2NTv3xcBBHqziSpNdP3RfOlfOUqAc19sNXfxka93oxoEcjOXTrF7d0nQKCTEMFm3KbEuBGvkmgR4kcwqEH1bWqh3d1Y7SM1MWPvtTecPH2hxhhnA8pXa5EHWPsbhwOzxNNTYDsaucKhJTU
*/