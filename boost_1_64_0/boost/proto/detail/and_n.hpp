#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/and_n.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/and_n.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file and_n.hpp
    /// Definitions of and_N, and_impl
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (2, BOOST_PP_MAX(BOOST_PROTO_MAX_ARITY, BOOST_PROTO_MAX_LOGICAL_ARITY), <boost/proto/detail/and_n.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    // Assymetry here between the handling of and_N and or_N because
    // and_N is used by lambda_matches up to BOOST_PROTO_MAX_ARITY,
    // regardless of how low BOOST_PROTO_MAX_LOGICAL_ARITY is.
    template<bool B, BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(N), typename P)>
    struct BOOST_PP_CAT(and_, N)
    #if 2 == N
      : mpl::bool_<P0::value>
    {};
    #else
      : BOOST_PP_CAT(and_, BOOST_PP_DEC(N))<
            P0::value BOOST_PP_COMMA_IF(BOOST_PP_SUB(N,2))
            BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_DEC(N), P)
        >
    {};
    #endif

    template<BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(N), typename P)>
    struct BOOST_PP_CAT(and_, N)<false, BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(N), P)>
      : mpl::false_
    {};

    #if N <= BOOST_PROTO_MAX_LOGICAL_ARITY

        template<BOOST_PP_ENUM_PARAMS(N, typename G), typename Expr, typename State, typename Data>
        struct _and_impl<proto::and_<BOOST_PP_ENUM_PARAMS(N, G)>, Expr, State, Data>
          : proto::transform_impl<Expr, State, Data>
        {
            #define M0(Z, N, DATA)                                                            \
            typedef                                                                           \
                typename proto::when<proto::_, BOOST_PP_CAT(G, N)>                            \
                    ::template impl<Expr, State, Data>                                        \
            BOOST_PP_CAT(Gimpl, N);                                                           \
            /**/
            BOOST_PP_REPEAT(N, M0, ~)
            #undef M0

            typedef typename BOOST_PP_CAT(Gimpl, BOOST_PP_DEC(N))::result_type result_type;

            result_type operator()(
                typename _and_impl::expr_param e
              , typename _and_impl::state_param s
              , typename _and_impl::data_param d
            ) const
            {
                // Fix: jfalcou - 12/29/2010
                // Avoid the use of comma operator here so as not to find Proto's
                // by accident.
                // expands to G0()(e,s,d); G1()(e,s,d); ... G{N-1}()(e,s,d);
                #define M0(Z,N,DATA) BOOST_PP_CAT(Gimpl,N)()(e,s,d);
                BOOST_PP_REPEAT(BOOST_PP_DEC(N),M0,~)
                return BOOST_PP_CAT(Gimpl,BOOST_PP_DEC(N))()(e,s,d);
                #undef M0
            }
        };

    #endif

    #undef N

#endif

/* and_n.hpp
MdTQiz0w+/rC8UxaiXxHf895zYMCt4G1bMf1opm5lwH9e/HHB/Gm8yYHxWjG6+Zm8r12ndvbz/h46quxfYzOZV03iXCGQmjeuuljlfg3m0uxL4VMMKpH2UEk+ZGzpw+GRo+EhYCy5eOxKa7Q+RSQTeITvO3raGts+jrTkM3W9wY2lqhSguKOZKnfPjWChys/y+v3xyk4uAaJx18HcDfDuK0nTtJpODMbZP911anw5X7Dc7zIruta/xY3+KNef4BHtgvIjPu13nQqXqjvVjEcJNLpfC6bjuft4O4ygLsNMe7b0ek4qPDAuezH8+RUvJADUlzX+9iCWglkRGgnwT7/8iuQHaCP6GDIX2hgu59pmWU2TYIMPFR6To3z6fld4vxAdLJtVRSdyTm/WPm5v0PBUrnFUEU+MhG/WrQ2kXVZmcCPlOHAkGuuj3tWScV0Rdxv3mhd5CZlbYs3UCb1995Rgddln4jfpPK865Ku0vHdYfRv+AU9v/1EvDep1Oi0rJJIz8+YHaTn97ZJA36mS5u6KId6/ojjGou74uOHR31Mhc0l7DkFP2ZC9ObF/VWU3zHWP3zF6N3hOxGfBPO2w/1bd5xRHMI5i407WC6q33Ne0DVl6jKFb0mhr7m6wedr++QgL5NKyhZux1GgnYMDyQj/Js35SC0qWekOpI//8l40Xn78HfRCpAPJUtvZBLjZdR5Unp1hz/jkIP5BlZaqqczgu/LlNJwje6ivfMlhkv0Hon/vi/wyuqeQeXLZ2oZg3hf5AXqhzB68oGUHv8E9xMEOjWEKYA/QQOLK/TvCYpljwAYq9/7GVusF2NVY+Y18edYttLC3Y7l/MwDhiuHejMoabbgeevOKAEO99thpKZR//spYjhsaapPDXenC1bGcbZNMR/6CmyAM9pj9Hbcxow0+2crcw9+jxvsPG84QSze6v1SiaGq0U+xcTBK2cTkHqRCVhK2jC5yHTNCPTLVZQnFRaPKT6nRtSq5rf+58IPajoIiTiA/tDrEbHvFiODtY3/phWfF5ZQcxGoZG1ymdM4P7W9PqDCTc8uC3R5q1Tsf+lsM0zsNhDnEvN6+A32vYVCij73R3/50m9Ox7HxzEzC5gcI2UsS+mk6hjF0pZDb/TSyJejQDln5ZlNfal/m+Z+W/+ES43aqHqwhjMWbkAA0a3OpYTtL+zBS92xuun5+OzGc55rTLTUbs4N2dVES4AQxuO9/B2zTdF0mTGaIHTFv1FJvzLL3F8KTGAGPxTVX2ci+3JFqCQAcEfttCQitmPcj4pOsyVRZFWSYgvtIV2EvDlsSluLT1ufXNzGCPoLx8Z5kLQOjNJF68lFiyot5GZJZuUD0V3gFKqVqouE3u7MI9xaq1s+jtIRjYE0fotRZ3p1KZKuzspo6QZEtTtePtJaM19/6nT1q4bOgCHPN5T13j/QQGP5NQ/PNH7J8VxTlhMwR891ePwWDIbPs7e8/0+QetuY7aHfRlpD/bfWGY9D7lsB7YP1lQyU20DL1Brfnhi8SyWIJlMOh+NeypALZ6DCPlfxvfALrn8iKjfW7sZ7SNYHr8LvcfH8FiCl2QcJ6Dpy6/ryhcSVS6VnUka9j50tSviu7cfuhD3lu8jc5gGr62aFKyLdh7tg134fIPRniOFlabLky6sCwwRNx9u8NwutHg313fgtlfVtgNf0I090mPJlO7wUT2VKBtV5lp1bg4fcwsO6EiUGjtmDd4hf8Z5nJJ5ncHVvYX68Po0kN1+/cFBfM48tyk0z9WH33y9D+K2v9Xf49bXaNeCOn0cer5eZxvTyDwvIOPzbB+7o6K3og/FezdmyyhtXcVxYecwwi5MEnR7WKPcMH7eeR11VGeVV1Y=
*/