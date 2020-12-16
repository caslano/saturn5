
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
EeHhGQvrh7jY8D5pRi7vl8gavNncp7zUySmfZcnns+178F804yik/EJf3XM0+M2F3y8bfp41e/2dpt3a52njc/6qzKu8Gdl5dYWZV1838+pKrZthcBZBYlxdBWOJ8gLH29VAg77/0s/4tYAG26jCO97XvRbWzi1m7by+SuNU4DxSWTIt9mdjnIrvmDlFuIynd3uw374ncptXmJXbjUZuNxm53axtFpjLxzNkt2j9wHOK6wffu9R/a5W/77l/qj+eJ9M7+Z1j2K/jGXuzbbfgzDfo26rg3Cb4ZpV/l2YfjVlvbBzOnxh57CK4yupoad/tYqPfBbRcntUVdxs48sLn/aR/boP14h6zn/h1QLl7KQ/bqXoFx+59OrfA76t4OLfurwJ7RuwXjAvy4FT1H6g8zPlAlY/wirCHJT3Hyy2b9nJpF2XSECe3zPOOIx5m6V66TPxf2i7Rt3Pzg9v1Z9PPrxnd84SRYV6ADJ8yNKzN9YyB2xg5zwLc6QMLf86UTxvb53mVJ6RxPO02/LwI8AcCvk28RHB8gyC/EN6RMn6PVwgXv9la395rZh21vsV/yFrzTEnueN5L+Rb3n4Lr1jFcl/ZVBfuoCY/1yxsER1z0UVvc/1RB2uzVXJ71EY2vlnEmcKSL4yyvGnngPh6Rh3ylKev3ewuDbb3J1WCDTZf6zdg8pFppS39NlbVEaFu56Q/XkinVUIZlcOAyb8MyPOYPXGZqtcha2mPtliJoL/KO7S1GnBG+mR9u5ItxqFC+MxCPaQXjHUF46Gu3+/kjpQ/eNcNPv6coV1fOmglneyWt9FwZ+91ijrYR4HYvPg94X1DIcNYt1maaD3g7R8Ergza+U+wP5OlYguM8/1xRLnyB1sPfSUauZ6GRpaWzCPkQGwjhSwiOtqQtX15t3k4TfVYmcSsrFS7ney28ypRfLPAFAl9uylv4ClP++uOFvthNJ5ryFl5jys8T+u8r8uF1pryFNxj4NBl7vSU+vMnAZ5XkvsfUbOpfJvD50r6TTHkLbzVwe/egzdC/ReA0FhjeYcpbeKeB27sP3Tp39Pw1fG+qkfMWa4BGTcCatZbguh7uNf7L02Suu3x8C/Hxklx7+nTCw3JnwPz4dCX/+J7WJbIXIHyeH+uUN1mLrZ9uPfD2WXPXobdaZa3rut5Bg3hh+QqDbzZmzY+Zue7KoH2xsVruqwHd+Ai+z+dKcsvGgf9nTb2bAPacgSUJJvfxuE6UkcrhszLGNusYAP9q3OjPrdDG50sox+zpzhJZEkzbpTR5TOO4mqjneITHvWYP8kHKB3yGs/8E+HT+FcSJC82zUV8GjNUPExz3ptaXfK7WId/SsI4eqeM8wPnVQsThb1mM83GopyeAj/MB7spY+Kfs2u72gsaPeKHI3MGtzH9zNPLFOFzms0B3n2nfy4LzOeDN5VnePk/wM0bfj3Z119afHGpv8nee7tgx3OM+IJZ8D/tCda4NfCmlLS9fNDbSa8a2v0xkRGXxmyXT1r3jTvobddHllMb92FcpjTx8otK8u2bgE83cuFLhTBt8A+pTqYY06gSwY5Het4ydm5J+wj78NrRB79lpDDZfFv43wzMYP5yJwXZ99VjuEfDFVpemUEXujQK+iLhH6ftjbWsg/e8cLH26Ub0k5tN/0zwCDT3r3u7zNbCBPv5l3+2m+zB0LRzfb3rYfzvb5WTe7f5+NX4347HrX6TRT2eQZWLCsv3Qa2ywm6SvXD6ukRvlrpT29d45Ol8Rf4L3Qxhfzi6zc+RHAJ8fAL9N9HCf1Kfz4Alz7+hO4ZPyhU+wNcyduVtA5+NZn7ukLkcDdf7dRucTnPF/IfjejNw5+itjL9wjacoPjHk6Yy4=
*/