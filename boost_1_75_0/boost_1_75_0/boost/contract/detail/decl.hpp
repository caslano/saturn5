
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
dV6bsE0zp/ZTRIYwb8YjnpbIMc4wE6anV8lMbQiE2/f09PZSr7x/LnRlZKmZ9+OEOZvqVYetMpnvt6et03Pd3J8gmXjO7gYb+VDvSZ9H3pOfhwTCjm2jH3XBikqQ36t4MtYXPeVTEXBlKlhtNG2Z2Mkg8/1pCfJQ0fts8RajgpfSrE6Y0Lp2v9zgYLLxqi373ZZ9al45DxVESvlaWJbbuncvEMqvoRvrFzxex1t5hXSIvPDKvii3IWp634eOG/Mv2pPmp1HnhZn36REUrH9aTFIx2Ow2X1W0XqzRWtiCn5YoTuZNox0VTdrYFmML/qob0wJkOum6a90Pusgbkp3XVKLATElVMJ7OQnZxKPe/uY2908xuaGesw7vs2rL1zR98VmaZrZ2iK8wMp3Mua6iemRrVixx1XNnU/Y6QXlGN6aScZf4R9tKIDTLgy32Z8qhjaDbXx3bhLPISoabCDRFrGuPvuj7lJY0+z3H1QJbbht0qQ0S5j2gqeAvIffeT8OrRc2WVTBU6rOvbFmDbW25mwFzaPrZmtl7rUvLECa7uDXrH6qMqQyjaOWms/Zyv5PlNcE/c33KvxDFz05rEkiltpxrVw0vmPiUX39BefWtnrZwUp+3Z+5huaGLg2CxjfJ29NzvGML9zIelVD7HtA//P6ReEaTq4IbJzWxhWWvKYQoDr5MaU8g/HImL3eydkbDc/J8lL5RGh5qQ8cSYi
*/