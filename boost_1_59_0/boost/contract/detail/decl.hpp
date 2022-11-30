
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
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
*/