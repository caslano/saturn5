#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/lambda_matches.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_DEFINE_LAMBDA_MATCHES(Z, N, DATA)                                           \
        lambda_matches<                                                                             \
            BOOST_PP_CAT(Expr, N)                                                                   \
          , BOOST_PP_CAT(Grammar, N)                                                                \
        >

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/lambda_matches.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file lambda_matches.hpp
    /// Specializations of the lambda_matches template
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (2, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/lambda_matches.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_DEFINE_LAMBDA_MATCHES

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    template<
        template<BOOST_PP_ENUM_PARAMS(N, typename BOOST_PP_INTERCEPT)> class T
        BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Expr)
        BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Grammar)
    >
    struct lambda_matches<
        T<BOOST_PP_ENUM_PARAMS(N, Expr)>
      , T<BOOST_PP_ENUM_PARAMS(N, Grammar)>
        BOOST_PROTO_TEMPLATE_ARITY_PARAM(N)
    >
      : BOOST_PP_CAT(and_, N)<
            BOOST_PROTO_DEFINE_LAMBDA_MATCHES(~, 0, ~)::value,
            BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_DEFINE_LAMBDA_MATCHES, ~)
        >
    {};

    #undef N

#endif

/* lambda_matches.hpp
u7u8Hl6DSGCtbyaHfyfi8U4ZxGiA8jzfjxhy9wpCE2eXR5k+yOE/tARP2SLuYyfh4IYNuHkZP7m0jD5TLONn/mu9kaXn+YVlPAnqzg7zZYeBFoa7dXuTmLfx1/97e4TMAP/N/1w20iy+Xb69hD+tMvL97n8rBzIm8fNedlN4k4ZabV+m+vIfvhl+97oaqBf82XP4vY2ERJsiYD56ATBXwbLWwWYukDSKhWFt95gvPAYw+84fyYDgOh4ve3yg915WOswrngiYpY+0IQ7g9zhgpsPnjVC8stLp8KqefZiRuSwbC3qFl53nFh9lzh3ViM8lp0z/xNNbFQQjZm3/4D7PIr9Hos55bpyGIsYwx302V727bVNUvMk4U63d4P4ELHue5/PHO3rIQ9E8qlKqOpcpQyWI/SfgXV7F94+q0JkowNebt3RbjDwdx7Z4mYp8dEttK9BidbU+DSVEdZidoL9D8TWravBAy4VPcDZKM8Y0H43TaONqInUzT7MWpQm+l1T8ztnkgudWJAwda2B9jsftOzKMiLEPBNpQ36e/6fFRJkvyJJP/A59N4IMytWfueZn6ZoUxzFsNRZCNbqOs7FUB42VqofExLCXxRfeGPj94/tk+GrcLuhPbBr/Oae9Mnma2rpRhxBTLc/cjGA9sT8Y7StqL62h1WooK/TjGf1ZfAGfG1bWnPnE1/Op17YNfZeTL0p6MIDNF0piCLeWx+t84Xw/2PHbK8fT7/pacBxa9/fz7Tf33DdgfEXtzEqv0yaDzOv9+C49tbSL+dienc+/3S98HZM+EOKbHYATrFpEza4MZ9dP4MmcTcQbT+HUxrKN7NwOaMxjfdwvi9LrwfXaL7vv06HAlxHF6cCxvq63NRME5rj3d/W7n+Gh+Y52AbbT7nd7r/xjxUSzVmbaiqtnWrndp5vziH+8N4WqYOF4Qp3kMdfVSFdbZMT2kd/9tqtQ22dz/wvDoqo8g5UQXfjGcr7Yu4GarHcRWSEyxPcrLMp3kEuyLmJcOD6buojDcm+vABL9MNI2EWNe50KKQTF8hEhOf1HvqBZ9YIapUpL/+Z+SFMgqdmUIJ1eoltOo/fHTFLbTA4GlPq2sp87yuNzef3tM3uWtkL2KZEKbMDa9YlMgVAtkmVzDOup48bxTJFpuIF7zj88zoumBeS9U36s7wWivuQoEcRrfc9rwMtlXPjkVoURdGZGx/h9iYyGpuwgyc93fWXG3dj3X4Md11upFEFkP5cbAdgMGYCD+GRALBTw8ne2MXncDrGuAW4tsr2Od/m/I5byurpGpafbNOpBjiKzyM9jf4tzSi1ikr0U5mZwSKlxhgNDKjGV/pdMdmlE/NMt1wkxV1KDq0ZN8m5GU0zYVCuZyLVLDpaO8KCESDTmGIs0XxomZVU9ZNLsq5D5Chz2TR94ITDU22x0PgNQx7WMQrY4YXYJWeQIFRyOidr7bxOFA5aj7huveD30R8EpZKnWdcKfaU3RHaoAMvKA6uJX0/Krh+Y/+5ixrVUc2KSpm8YS6x08iaz1eOcmmK5QXL87LQeZP28sesaT88APOrovxSXsrMtnaW6OWexKbZQizKL3VZ1k2xPJwuukhEzTLiv+MVUbkVMzYTUhR58I85nDp3aLC2tTsClCKytX8XTV/Bk0+peVEzeAEcOScsfX3uDyMedQtNWfC6Cdm5trroI4b5ovfjyn+Zpr/ITaNLLUrXRiO3/+whupO1fRvxGC+lNlLXxP+ne4WbZ6XqRFdos0UMgcJ8/mPUPzbleZ2mOdggBUPYnaCHGNVTsszqopSlifWxwS8YqK3HdbzpI2gdG3BPblO3mk3Ho8GuuxVgHXEs3JHiZcGUTo3Ok7pN0Z4=
*/