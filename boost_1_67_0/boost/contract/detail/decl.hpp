
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