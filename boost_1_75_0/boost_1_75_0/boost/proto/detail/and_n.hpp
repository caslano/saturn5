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
de7Z3VywBZOcs9m91o/p6mbCEheo0TR3oHzS51TEO1K4LdSqnD3Y1cAdDtHfsKzS77+/Tcu5fbFjLZ69n7BGTds1PpiCuTWC2UY+6K7Jp26jGDJYz3hGm1N90exZmXxF1bl5JScizbgpqG78gY1Y02BrzvvFWiiWU7s70OQPeJ2+RtSiTfgC/ZJzrxItXY1uLQ/yTMiMqvNW2apKjDosVC66zzjbt+a4UfhDru3kN8vtHpebm5H+rShHq/2TenrZuMXfrmbpcxc4WtkVhagIrJFXWFrAjFdk+qFcr+RySsNG5ZOn7s9BvNag230/nQfGKxjR+WAdvDJTD88Aaqa5kaQNW93etW1NTejZW3n2FM/6bYLxfHk7My9Moz0kJ3r6A75yv328utPyWtPxL7/MfdGZd6v8zvFNi4o4ISHn/1hIBV35+dS7pB9BW/fZXR66OmS84ev1/fcjSr9wFeX8HKddUaVfskY/fUbpLTb99CNK33X7HN8PUHptnX76caXfV6mfPqv0mRr99BSW+gd36ac3Kf3uZv30FqWfaNZPb1V6q0c/fZnSmzX99Halpw799PW58r+jn15T+jf36qfvUvrIgTn6X+n3Rufof6U/0TtH/+fKT+unP6b0+zL66ceVfvmP9NNnlb7i7/TTU6cq/wX99Galp7+fo/+UvnhEP32F0qde1E9fr/SL/kk/vab0u1/TT9+l9JFf6KeP
*/