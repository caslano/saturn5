
#ifndef BOOST_CONTRACT_DETAIL_DECL_HPP_
#define BOOST_CONTRACT_DETAIL_DECL_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Cannot include core/*.hpp other than config.hpp here (avoid circular incl).
#include <boost/contract/detail/tvariadic.hpp>
#if !BOOST_CONTRACT_DETAIL_TVARIADIC
    #include <boost/contract/core/config.hpp>
    #include <boost/preprocessor/repetition/repeat.hpp>
    #include <boost/preprocessor/tuple/elem.hpp>
    #include <boost/preprocessor/arithmetic/inc.hpp>
#endif
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

/* PUBLIC */

#define BOOST_CONTRACT_DETAIL_DECL_OVERRIDING_PUBLIC_FUNCTION_Z(z, \
    arity, is_friend, has_result, \
    O, VR, F, C, Args, \
    v, r, f, obj, args \
) \
    template< \
        class O \
        BOOST_PP_COMMA_IF(has_result) \
        BOOST_PP_EXPR_IIF(has_result, typename VR) \
        , typename F \
        , class C \
        BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
        BOOST_CONTRACT_DETAIL_TVARIADIC_TPARAMS_Z(z, arity, Args) \
    > \
    BOOST_PP_EXPR_IIF(is_friend, friend) \
    boost::contract::specify_precondition_old_postcondition_except< \
            BOOST_PP_EXPR_IIF(has_result, VR)> \
    /* no boost::contract:: here for friends (otherwise need fwd decl) */ \
    public_function( \
        boost::contract::virtual_* v \
        BOOST_PP_COMMA_IF(has_result) \
        BOOST_PP_EXPR_IIF(has_result, VR& r) \
        , F f \
        , C* obj \
        BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
        BOOST_CONTRACT_DETAIL_TVARIADIC_FPARAMS_Z(z, arity, Args, &, args) \
    )

#if BOOST_CONTRACT_DETAIL_TVARIADIC
    #define BOOST_CONTRACT_DETAIL_DECL_FRIEND_OVERRIDING_PUBLIC_FUNCTIONS_Z(z, \
        O, VR, F, C, Args, \
        v, r, f, obj, args \
    ) \
        BOOST_CONTRACT_DETAIL_DECL_OVERRIDING_PUBLIC_FUNCTION_Z(z, \
            ~, /* is_friend = */ 1, /* has_result = */ 0, \
            O, VR, F, C, Args, v, r, f, obj, args \
        ); \
        BOOST_CONTRACT_DETAIL_DECL_OVERRIDING_PUBLIC_FUNCTION_Z(z, \
            ~, /* is_friend = */ 1, /* has_result = */ 1, \
            O, VR, F, C, Args, v, r, f, obj, args \
        );
#else
    /* PRIVATE */
    #define BOOST_CONTRACT_DETAIL_DECL_FRIEND_OVERRIDING_PUBLIC_FUNCTION_( \
            z, n, result_O_R_F_C_Args_v_r_f_obj_args) \
        BOOST_CONTRACT_DETAIL_DECL_OVERRIDING_PUBLIC_FUNCTION_Z(z, \
            /* arity = */ n, \
            /* is_friend = */ 1, \
            BOOST_PP_TUPLE_ELEM(11, 0, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 1, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 2, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 3, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 4, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 5, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 6, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 7, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 8, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 9, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 10, result_O_R_F_C_Args_v_r_f_obj_args) \
        );

    /* PUBLIC */
    #define BOOST_CONTRACT_DETAIL_DECL_FRIEND_OVERRIDING_PUBLIC_FUNCTIONS_Z(z, \
        O, VR, F, C, Args, \
        v, r, f, obj, args \
    ) \
        BOOST_PP_REPEAT_ ## z( \
            BOOST_PP_INC(BOOST_CONTRACT_MAX_ARGS), \
            BOOST_CONTRACT_DETAIL_DECL_FRIEND_OVERRIDING_PUBLIC_FUNCTION_, \
            (/* has_result = */ 0, O, VR, F, C, Args, v, r, f, obj, args) \
        ) \
        BOOST_PP_REPEAT_ ## z( \
            BOOST_PP_INC(BOOST_CONTRACT_MAX_ARGS), \
            BOOST_CONTRACT_DETAIL_DECL_FRIEND_OVERRIDING_PUBLIC_FUNCTION_, \
            (/* has_result = */ 1, O, VR, F, C, Args, v, r, f, obj, args) \
        )
#endif

#define BOOST_CONTRACT_DETAIL_DECL_DETAIL_COND_SUBCONTRACTING_Z( \
        z, is_friend, O, VR, F, C, Args) \
    template< \
        class O, typename VR, typename F, class C \
        BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(BOOST_CONTRACT_MAX_ARGS) \
        BOOST_CONTRACT_DETAIL_TVARIADIC_TPARAMS_Z(z, \
                BOOST_CONTRACT_MAX_ARGS, Args) \
    > \
    BOOST_PP_IIF(is_friend, \
        friend class boost::contract::detail:: \
    , \
        class \
    ) \
    cond_subcontracting

/* CODE */

namespace boost {
    namespace contract {
        class virtual_;

        template<typename VR = void>
        class specify_precondition_old_postcondition_except;
    }
}
    
#endif // #include guard


/* decl.hpp
o48D9O1dspeJzl9u8eNgtCgJgND1PAF2aMPSokpiTWvRwupsem95csxwA1/90CN1pAoFssVz364+XlLbuZnP48YnD6lEDJTVoystAj6t0VpOvVMSWCpbQrX2z5iaJD+7RE6growPyu+M74HKQOL/7AE319Sjmck84i+E/7qqjPGEX6kcuXKyWi1Feh5tpxuSAp2LG5QN4VxrqWnrfd/AxgCxYkUxi4pIaa8+wo2pX+5Nmgd55Tj+3cP2uUd8mL915w30ejD+RbmLrOJkw81fLUyYxG613Vq1u7J74aT6scEosvWUM4g7q4XjsLJz9UEaXJ3565HT3YCdJPXP3eGNfqh8vPcC6CaXotOCUS7F9eeRFdzs90ejkrokqGAM4E6mUI3Lz2rqYPJpA+hELkZXc6qZdH5GNbaitYw6+rllPB6Ig84pmY0wDGVcjtYZP4Z3Ev8MWF4DkfGlOfwgJuvk/Fun92zDx+kYFqJggZnIwDKlOu3551tUtrLrh6FJgCT014VsnQtKbFYqoX7rcftmiBk+Q5/2M1Ipg3VeJ9wItma0lbVqepc3jhtSPQ==
*/