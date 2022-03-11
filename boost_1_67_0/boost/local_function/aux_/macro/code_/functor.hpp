
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_HPP_

#include <boost/local_function/config.hpp>
#include <boost/local_function/aux_/symbol.hpp>
#include <boost/local_function/aux_/function.hpp>
#include <boost/local_function/aux_/add_pointed_const.hpp>
#include <boost/local_function/aux_/member.hpp>
#include <boost/local_function/aux_/nobind.hpp>
#include <boost/local_function/aux_/macro/decl.hpp>
#include <boost/local_function/aux_/macro/typeof.hpp>
#include <boost/local_function/aux_/macro/code_/result.hpp>
#include <boost/local_function/aux_/macro/code_/bind.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_params.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_binds.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_const_binds.hpp>
#include <boost/local_function/detail/preprocessor/keyword/auto.hpp>
#include <boost/local_function/detail/preprocessor/keyword/register.hpp>
#include <boost/local_function/detail/preprocessor/keyword/thisunderscore.hpp>
#include <boost/utility/identity_type.hpp>
#include <boost/scope_exit.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/list/size.hpp>
#include <boost/preprocessor/list/for_each_i.hpp>
#include <boost/preprocessor/list/first_n.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_CLASS_TYPE_(id) \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (functor)(id) )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_F_TYPE_ \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (function_type) )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BODY_FUNC_ \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (body) )

// Unbind parameters.

// i: 1 for 1st param, 2 for 2nd, ... (start from 1 not 0).
#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_ARG_NAME_(i) \
    /* this must be a generic parameter name because type and name */ \
    /* are not separate tokens in the macro syntax so name is not available */ \
    /* separately from its type */ \
    BOOST_PP_CAT(arg, i)

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_ARG_NAME_ENUM_( \
        r, unused, i, param_traits) \
    BOOST_PP_COMMA_IF(i) /* enumeration commas */ \
    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_ARG_NAME_(BOOST_PP_INC(i))

// i: 1 for 1st param, 2 for 2nd, ... (start from 1 not 0).
#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_ARG_TYPE_(typename01, i) \
    /* the parameter type must be accessed using function traits from */ \
    /* function type because it is not available to the macro syntax */ \
    /* separately from the parameter name */ \
    BOOST_PP_EXPR_IIF(typename01, typename) \
    ::boost::function_traits< \
        BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_F_TYPE_ \
    >::BOOST_PP_CAT(BOOST_PP_CAT(arg, i), _type) \

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_ARG_TYPEDEF_( \
        r, typename01, i, param_traits) \
    typedef \
        BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_ARG_TYPE_(typename01, \
                BOOST_PP_INC(i)) \
        /* name must follow Boost.FunctionTraits arg1_type, arg2_type, ... */ \
        BOOST_PP_CAT(BOOST_PP_CAT(arg, BOOST_PP_INC(i)), _type) \
    ;

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_ARG_DECL_( \
        r, typename01, i, param_traits) \
    BOOST_PP_EXPR_IIF(typename01, typename) \
    ::boost::call_traits< \
        BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_ARG_TYPE_(typename01, \
                BOOST_PP_INC(i)) \
    >::param_type \
    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_ARG_NAME_(BOOST_PP_INC(i))

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_ARG_DECL_ENUM_( \
        r, typename01, i, param_traits) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_ARG_DECL_(r, typename01, i, \
            param_traits)

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_PARAM_ARG_DECL_( \
        r, typename01, i, param_traits) \
    , BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_ARG_DECL_(r, typename01, i, \
            param_traits)

// Precondition: !EMPTY(DEFAULT(param_traits))
#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_DEFAULT_ASSIGNMENT_( \
        param_traits) \
    = BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_REMOVE_FRONT( \
            BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_DEFAULT(param_traits))

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_DECL_ENUM_( \
        r, default01, i, param_traits) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_AUTO_REMOVE_BACK( \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_REGISTER_REMOVE_BACK( \
        BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_DECL(param_traits) \
    )) \
    BOOST_PP_IIF(BOOST_PP_COMPL(default01), \
        BOOST_PP_TUPLE_EAT(1) /* without default */ \
    , BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_DEFAULT(param_traits)), \
        BOOST_PP_TUPLE_EAT(1) /* has no default */ \
    , /* else, with default and has default */ \
        BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_DEFAULT_ASSIGNMENT_ \
    ))(param_traits)

// Bound parameters.

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAMS_ \
    bind_params /* constructor void* param */

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_VAR_(i) \
    /* named `bind0`, `bind1`, ... */ \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (bind)(i) )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BIND_MEMBER_THIS_ \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (bind_this) )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_STATIC_BIND_MEMBER_THIS_( \
        id) \
    , static_cast< BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_CLASS_TYPE_(id)* >( \
            object)->BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BIND_MEMBER_THIS_

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BIND_TYPE_( \
        id, typename01, offset, i, bind_var_without_type) \
    BOOST_PP_EXPR_IIF(typename01, typename) \
    BOOST_SCOPE_EXIT_DETAIL_PARAMS_T(id):: \
    BOOST_SCOPE_EXIT_DETAIL_PARAM_T(id, BOOST_PP_ADD(i, offset), \
            bind_var_without_type) \

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_MEMBER_BIND_ENUM_( \
        r, offset, i, bind_traits) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_VAR_( \
            BOOST_PP_ADD(offset, i))

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_TYPE_( \
        r, id_typename_offset_const, i, bind_var_without_type) \
    /* IMPORTANT: here can't use `PP_KEYWORD_IS_THISUNDERSCORE_FRONT()` */ \
    /* because some `param_name` might start with non-alphanumeric symbol */ \
    /* `&` (but that is never the case for `this`) */ \
    BOOST_PP_IIF(BOOST_PP_COMPL(BOOST_PP_TUPLE_ELEM(4, 3, \
            id_typename_offset_const)), \
        BOOST_PP_EMPTY \
    , BOOST_PP_IIF( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_THISUNDERSCORE_BACK( \
                    bind_var_without_type), \
        /* pointed obj const */ \
        BOOST_PP_EXPR_IIF(BOOST_PP_TUPLE_ELEM(4, 1, id_typename_offset_const), \
            typename \
        ) \
        BOOST_PP_IDENTITY( ::boost::local_function::aux::add_pointed_const< ) \
    , \
        BOOST_PP_EXPR_IIF(BOOST_PP_TUPLE_ELEM(4, 1, id_typename_offset_const), \
            typename \
        ) \
        BOOST_PP_IDENTITY( ::boost::add_const< ) /* outer type const */ \
    ))() \
    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BIND_TYPE_( \
            BOOST_PP_TUPLE_ELEM(4, 0, id_typename_offset_const), \
            BOOST_PP_TUPLE_ELEM(4, 1, id_typename_offset_const), \
            BOOST_PP_TUPLE_ELEM(4, 2, id_typename_offset_const), \
            i, bind_var_without_type) \
    BOOST_PP_EXPR_IIF(BOOST_PP_TUPLE_ELEM(4, 3, id_typename_offset_const), \
        >::type \
    )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_( \
        r, id_typename_offset_const, i, bind_var_without_type) \
    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_TYPE_( \
            r, id_typename_offset_const, i, bind_var_without_type) \
    BOOST_PP_IIF( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_THISUNDERSCORE_BACK( \
                    BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE( \
                            bind_var_without_type)), \
        this_ BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_PP_TUPLE_REM(1) \
    )(bind_var_without_type)

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_MAYBECONST_BIND_TYPE_( \
        r, id_typename_offset_const, i, bind_traits) \
    , BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_TYPE_( \
            r, id_typename_offset_const, i, \
            BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE( \
                    bind_traits))

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_PARAM_( \
        offset, i) \
    BOOST_PP_CAT(bind, BOOST_PP_ADD(offset, i))

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_PARAM_ENUM_( \
        r, offset, i, bind_traits) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_PARAM_(offset, i)

#define \
BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_MAYBECONST_BIND_PARAM_DECL_( \
        r, id_typename_offset_const, i, bind_traits) \
    , BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_TYPE_( \
            r, id_typename_offset_const, i, \
            BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE( \
                    bind_traits)) & \
      BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_PARAM_( \
            BOOST_PP_TUPLE_ELEM(4, 2, id_typename_offset_const), i)

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_BIND_THIS_TYPE_( \
        id, typename01) \
    , BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPE(id, typename01)
      
#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BIND_THIS_PARAM_ \
    bind_this

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_BIND_THIS_PARAM_DECL_( \
        id, typename01) \
    , BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPE(id, typename01) & \
      BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BIND_THIS_PARAM_

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_NOBIND_(z, n, unused) \
    , ::boost::local_function::aux::nobind

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_NOBIND_TYPE_(z, n, unused) \
    , ::boost::local_function::aux::nobind_t

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_NOBIND_PARAM_DECL_( \
        z, n, unused) \
    , ::boost::local_function::aux::nobind_t & \
    /* param name not needed here because no bind param not used */

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_ENUM_( \
        r, id_typename_offset_const, i, bind_traits) \
    BOOST_PP_COMMA_IF(i) /* enumeration commas */ \
    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_( \
            r, id_typename_offset_const, i, \
            BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE( \
                    bind_traits))

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_DECL_( \
        r, id_typename_offset_const, i, bind_traits) \
    BOOST_PP_EXPR_IIF(BOOST_PP_TUPLE_ELEM(4, 1, id_typename_offset_const), \
        typename \
    ) \
    ::boost::local_function::aux::member_type< \
        BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_TYPE_( \
                r, id_typename_offset_const, i, bind_var_without_type) \
    >::reference \
    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_VAR_( \
            BOOST_PP_ADD(i, BOOST_PP_TUPLE_ELEM(4, 2, \
                    id_typename_offset_const))) \
    ; /* end member variable declaration */

#define \
BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_MAYBECONST_STATIC_BIND_MEMBER_( \
        r, id_typename_offset_const, i, bind_traits) \
    , static_cast< BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_CLASS_TYPE_( \
            BOOST_PP_TUPLE_ELEM(4, 0, id_typename_offset_const))* >(object)-> \
      BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_VAR_( \
            BOOST_PP_ADD(i, BOOST_PP_TUPLE_ELEM(4, 2, \
            id_typename_offset_const)))

#define \
BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_INIT_ENUM_( \
        r, id_offset, i, bind_traits) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_VAR_( \
            BOOST_PP_ADD(i, BOOST_PP_TUPLE_ELEM(2, 1, id_offset))) \
    ( /* member variable initialization */ \
        static_cast< \
            BOOST_SCOPE_EXIT_DETAIL_PARAMS_T( \
                    BOOST_PP_TUPLE_ELEM(2, 0, id_offset))* \
        >(BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAMS_)-> \
        BOOST_SCOPE_EXIT_DETAIL_PARAM( \
              BOOST_PP_TUPLE_ELEM(2, 0, id_offset) \
            , BOOST_PP_ADD(i, BOOST_PP_TUPLE_ELEM(2, 1, id_offset)) \
            , BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE( \
                    bind_traits) \
        ).value \
    )

// Typeof type-definitions.

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_TYPEDEF_( \
        r, id_typename_offset_const, i, bind_traits) \
    typedef /* the type with the special typeof name */ \
        BOOST_LOCAL_FUNCTION_AUX_TYPEOF_TYPE( \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_( \
                    r, id_typename_offset_const, i, \
                    BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE( \
                            bind_traits)) \
        ) \
    ; /* end typedef */

// Expand to the function type `R (A1, ...)`.
#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_F_( \
        id, typename01, decl_traits, has_type, function_type) \
    BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPE(id, typename01) \
    BOOST_PP_EXPR_IIF(has_type, (function_type) ) \
    ( \
        BOOST_PP_LIST_FOR_EACH_I( \
                BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_DECL_ENUM_, \
                0, /* without defaults */ \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits)) \
    )

// Functor call operations.

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_CALL_BODY_(id, typename01, \
        const_bind_macro, bind_macro, const_bind_this_macro, bind_this_macro, \
        param_macro, params, \
        const_binds, has_const_bind_this, binds, has_bind_this) \
    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BODY_FUNC_( \
        BOOST_PP_LIST_FOR_EACH_I(const_bind_macro, \
                0 /* no offset */, const_binds) \
        /* pass plain binds */ \
        BOOST_PP_COMMA_IF( \
            BOOST_PP_BITAND( \
                  BOOST_PP_LIST_IS_CONS(const_binds) \
                , BOOST_PP_LIST_IS_CONS(binds) \
            ) \
        ) \
        BOOST_PP_LIST_FOR_EACH_I(bind_macro, \
                /* offset index of # const-binds (could be 0) */ \
                BOOST_PP_LIST_SIZE(const_binds), binds) \
        /* pass bind `this` */ \
        BOOST_PP_COMMA_IF( \
            BOOST_PP_BITAND( \
                  BOOST_PP_BITOR( \
                      BOOST_PP_LIST_IS_CONS(const_binds) \
                    , BOOST_PP_LIST_IS_CONS(binds) \
                  ) \
                , BOOST_PP_BITOR(has_const_bind_this, has_bind_this) \
            ) \
        ) \
        BOOST_PP_EXPR_IIF(has_const_bind_this, const_bind_this_macro) \
        BOOST_PP_EXPR_IIF(has_bind_this, bind_this_macro) \
        /* pass params */ \
        BOOST_PP_COMMA_IF( \
            BOOST_PP_BITAND( \
                  BOOST_PP_BITOR( \
                      BOOST_PP_BITOR( \
                          BOOST_PP_LIST_IS_CONS(const_binds) \
                        , BOOST_PP_LIST_IS_CONS(binds) \
                      ) \
                    , BOOST_PP_BITOR(has_const_bind_this, has_bind_this) \
                  ) \
                , BOOST_PP_LIST_IS_CONS(params) \
            ) \
        ) \
        BOOST_PP_LIST_FOR_EACH_I(param_macro, ~, params) \
    )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_CALL_(z, defaults_n, \
        id, typename01, decl_traits, params, \
        const_binds, has_const_bind_this, binds, has_bind_this) \
    inline BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPE(id, typename01) \
    operator()( \
        BOOST_PP_LIST_FOR_EACH_I( \
                BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_ARG_DECL_ENUM_, \
                typename01, params) \
    ) /* cannot be const because of binds (same as for global fctor) */ { \
        /* just forward call to member function with local func name */ \
        return BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_CALL_BODY_(id, typename01,\
  BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_MEMBER_BIND_ENUM_, \
  BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_MEMBER_BIND_ENUM_, \
                BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BIND_MEMBER_THIS_, \
                BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BIND_MEMBER_THIS_, \
                BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_ARG_NAME_ENUM_, \
                params, const_binds, has_const_bind_this, binds, \
                has_bind_this); \
    }

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_STATIC_CALL_FUNC_( \
        z, defaults_n, unused) \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (call)(defaults_n) )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_STATIC_CALL_COMMA_FUNC_ADDR_( \
        z, defaults_n, unused) \
    , &BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_STATIC_CALL_FUNC_(z, defaults_n, ~)

// Precondition: NO_LOCAL_TYPES_AS_TEMPLATE_PARAMS.
#define \
BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_STATIC_CALL_COMMA_BIND_PARAM_DECLS_( \
        id, typename01, const_binds, has_const_bind_this, binds, has_bind_this)\
    BOOST_PP_LIST_FOR_EACH_I( \
  BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_MAYBECONST_BIND_PARAM_DECL_, \
            ( id, typename01, 0 /* no offset */, 1 /* const */ ), const_binds) \
    BOOST_PP_LIST_FOR_EACH_I( \
  BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_MAYBECONST_BIND_PARAM_DECL_, \
            /* offset of # of const-binds */ \
            ( id, typename01, BOOST_PP_LIST_SIZE(const_binds), 0 /* const */ ),\
            binds) \
    BOOST_PP_IIF(BOOST_PP_BITOR(has_bind_this, \
            has_const_bind_this), \
        BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_BIND_THIS_PARAM_DECL_ \
    , \
        BOOST_PP_TUPLE_EAT(2) \
    )(id, typename01) \
    /* fill with nobind_t (if no local-types as tparams) */ \
    BOOST_PP_REPEAT(BOOST_PP_SUB(BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX, \
            BOOST_PP_IIF(BOOST_PP_BITOR(has_bind_this, \
                    has_const_bind_this), \
                BOOST_PP_INC \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_LIST_SIZE(BOOST_PP_LIST_APPEND(const_binds, \
                    binds)))), \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_NOBIND_PARAM_DECL_, ~)

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_STATIC_CALL_OPERATOR_( \
        id, typename01, \
        params, const_binds, has_const_bind_this, binds, has_bind_this) \
    operator()( \
        BOOST_PP_LIST_FOR_EACH_I( \
                BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_ARG_NAME_ENUM_, ~, \
                params) \
    )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_STATIC_CALL_BODY_( \
        id, typename01, \
        params, const_binds, has_const_bind_this, binds, has_bind_this) \
    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_CALL_BODY_(id, typename01, \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_PARAM_ENUM_, \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_PARAM_ENUM_, \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BIND_THIS_PARAM_, \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BIND_THIS_PARAM_, \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_ARG_NAME_ENUM_, \
            params, const_binds, has_const_bind_this, binds, has_bind_this)

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_STATIC_CALL_(z, defaults_n, \
        id, typename01, decl_traits, params, \
        const_binds, has_const_bind_this, binds, has_bind_this) \
    inline static BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPE(id, typename01) \
    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_STATIC_CALL_FUNC_(z, defaults_n, ~)( \
        void* object \
        BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS, \
            BOOST_PP_TUPLE_EAT(6) \
        , \
  BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_STATIC_CALL_COMMA_BIND_PARAM_DECLS_ \
        )(id, typename01, \
                const_binds, has_const_bind_this, binds, has_bind_this) \
        BOOST_PP_LIST_FOR_EACH_I( \
                BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_PARAM_ARG_DECL_, \
                typename01, params) \
    ) { \
        /* run-time: casting object to this class type and forward call to */ \
        /* `operator()` (this performs better than doing multiple casting */ \
        /* or using a casted object local variable here to call body */ \
        /* directly from here without passing via `operator()`) */ \
        /* compliance: passing local class type to `static_cast` is fully */ \
        /* C++03 compliant because `static_cast` is not a template (even */ \
        /* if its syntax resembles a function template call) in fact even */ \
        /* in C is legal to cast to a local struct (using C-style casting) */ \
        return \
            static_cast< \
                BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_CLASS_TYPE_(id)* \
            >(object)-> \
            BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS,\
                BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_STATIC_CALL_OPERATOR_ \
            , \
                BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_STATIC_CALL_BODY_ \
            )(id, typename01, params, \
                    const_binds, has_const_bind_this, binds, has_bind_this) \
        ; \
    }
        
#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_CALL_FOR_DEFAULTS_(z, defaults_n, \
        op_id_typename_decl_params_constbinds_hasconstthis_binds_hasthis) \
    BOOST_PP_EXPAND( \
    BOOST_PP_TUPLE_ELEM(9, 0, \
        op_id_typename_decl_params_constbinds_hasconstthis_binds_hasthis) \
    ( z, defaults_n \
    , BOOST_PP_TUPLE_ELEM(9, 1, /* id */\
        op_id_typename_decl_params_constbinds_hasconstthis_binds_hasthis) \
    , BOOST_PP_TUPLE_ELEM(9, 2, /* typename01 */ \
        op_id_typename_decl_params_constbinds_hasconstthis_binds_hasthis) \
    , BOOST_PP_TUPLE_ELEM(9, 3, /* decl_traits */ \
        op_id_typename_decl_params_constbinds_hasconstthis_binds_hasthis) \
    , BOOST_PP_LIST_FIRST_N( /* remove last n default params */ \
          BOOST_PP_SUB(BOOST_PP_LIST_SIZE(BOOST_PP_TUPLE_ELEM(9, 4, \
            op_id_typename_decl_params_constbinds_hasconstthis_binds_hasthis)),\
            defaults_n) \
        , BOOST_PP_TUPLE_ELEM(9, 4, \
            op_id_typename_decl_params_constbinds_hasconstthis_binds_hasthis) \
      ) \
    , BOOST_PP_TUPLE_ELEM(9, 5, /* const_binds */ \
        op_id_typename_decl_params_constbinds_hasconstthis_binds_hasthis) \
    , BOOST_PP_TUPLE_ELEM(9, 6, /* has_const_bind_this */ \
        op_id_typename_decl_params_constbinds_hasconstthis_binds_hasthis) \
    , BOOST_PP_TUPLE_ELEM(9, 7, /* binds */ \
        op_id_typename_decl_params_constbinds_hasconstthis_binds_hasthis) \
    , BOOST_PP_TUPLE_ELEM(9, 8, /* has_bind_this */ \
        op_id_typename_decl_params_constbinds_hasconstthis_binds_hasthis) \
    ) /* end `op_macro(...)` */ \
    ) /* end expand */

// Functor binds.
            
// Precondition: NO_LOCAL_TYPES_AS_TEMPLATE_PARAMS.
#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_BIND_TYPES_( \
        id, typename01, const_binds, has_const_bind_this, binds, has_bind_this)\
    BOOST_PP_LIST_FOR_EACH_I( \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_MAYBECONST_BIND_TYPE_, \
            ( id, typename01, 0 /* no offset */, 1 /* const */ ), \
            const_binds) \
    BOOST_PP_LIST_FOR_EACH_I( \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_MAYBECONST_BIND_TYPE_, \
            /* offset of # of const-binds */ \
            ( id, typename01, BOOST_PP_LIST_SIZE(const_binds), 0 /* const */ ),\
            binds) \
    BOOST_PP_IIF(BOOST_PP_BITOR(has_bind_this, \
            has_const_bind_this), \
        BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_BIND_THIS_TYPE_ \
    , \
        BOOST_PP_TUPLE_EAT(2) \
    )(id, typename01) \
    /* fill with nobind_t (if no local-types as tparams) */ \
    BOOST_PP_REPEAT(BOOST_PP_SUB(BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX, \
            BOOST_PP_IIF(BOOST_PP_BITOR(has_bind_this, has_const_bind_this), \
                BOOST_PP_INC \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_LIST_SIZE(BOOST_PP_LIST_APPEND(const_binds, binds)))), \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_NOBIND_TYPE_, ~)
        
#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BIND_TYPEOF_TYPEDEFS_( \
        id, typename01, const_binds, has_const_bind_this, binds, has_bind_this)\
    /* typeof types -- these types are qualified with extra eventual */ \
    /* const and/or & if their variables are bound by const and/or & */ \
    /* (this is because it is not possible to strip the eventual & */ \
    /* given that the var name is always attached to the & symbol plus */ \
    /* programmers can always remove const& using type traits) */ \
    /* const bind typeof types */ \
    BOOST_PP_LIST_FOR_EACH_I( \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_TYPEDEF_,\
            (id, typename01, 0 /* no offset */, 1 /* const-bind */ ), \
            const_binds) \
    /* bind typeof types */ \
    BOOST_PP_LIST_FOR_EACH_I( \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_TYPEDEF_, \
            /* offset index with # of preceding const-binds (if any) */ \
            ( id, typename01, BOOST_PP_LIST_SIZE(const_binds), \
              0 /* not const-bind */ ), binds) \
    /* const this... */ \
    BOOST_PP_EXPR_IIF(has_const_bind_this, \
        typedef BOOST_LOCAL_FUNCTION_AUX_TYPEOF_TYPE( \
            BOOST_PP_EXPR_IIF(typename01, typename) \
            ::boost::local_function::aux::add_pointed_const< \
                BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPE(id, typename01) \
            >::type \
            this_ \
        ) ; /* close typedef */ \
    ) \
    /* ... or, non-const this */ \
    BOOST_PP_EXPR_IIF(has_bind_this, \
        typedef BOOST_LOCAL_FUNCTION_AUX_TYPEOF_TYPE( \
            BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPE(id, typename01) \
            this_ \
        ) ; /* close typedef */ \
    )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BIND_MEMBER_DECLS_( \
        id, typename01, const_binds, has_const_bind_this, binds, has_bind_this)\
    /* run-time: it is faster if call `operator()` just accesses member */ \
    /* references to the ScopeExit struct instead of accessing the bind */ \
    /* struct at each call (these mem refs are init by the constructor) */ \
    BOOST_PP_LIST_FOR_EACH_I( /* const bind member references */ \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_DECL_,\
            ( id, typename01, 0 /* no offset */, 1 /* const */ ), \
            const_binds) \
    BOOST_PP_LIST_FOR_EACH_I( /* bind member references */ \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_DECL_,\
            /* offset index of # of const-binds (could be 0) */ \
            ( id, typename01, BOOST_PP_LIST_SIZE(const_binds), \
              0 /* no const */ ), binds) \
    /* bind this const or not (pointed-const is not added here because */ \
    /* this is a reference, it is added to the this_ body param instead */ \
    BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(has_bind_this, has_const_bind_this), \
        /* this is * so no & */ \
        BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPE(id, typename01) \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BIND_MEMBER_THIS_ \
        ; /* end member variable declaration */ \
    )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_STATIC_BINDS_( \
        id, typename01, \
        const_binds, has_const_bind_this, binds, has_bind_this) \
    BOOST_PP_LIST_FOR_EACH_I( \
  BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_MAYBECONST_STATIC_BIND_MEMBER_, \
        ( id, typename01, 0 /* no offset */, 1 /* const */ ), const_binds) \
    BOOST_PP_LIST_FOR_EACH_I( \
  BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_MAYBECONST_STATIC_BIND_MEMBER_, \
        /* offset of # of const-binds */ \
        ( id, typename01, BOOST_PP_LIST_SIZE(const_binds), 0 /* const */ ), \
        binds) \
    BOOST_PP_IIF(BOOST_PP_BITOR(has_bind_this, \
            has_const_bind_this), \
        BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_STATIC_BIND_MEMBER_THIS_ \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(id) \
    /* fill with nobind_t (if no local-types as tparams) */ \
    BOOST_PP_REPEAT(BOOST_PP_SUB(BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX, \
            BOOST_PP_IIF(BOOST_PP_BITOR(has_bind_this, has_const_bind_this), \
                BOOST_PP_INC \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )(BOOST_PP_LIST_SIZE(BOOST_PP_LIST_APPEND(const_binds, binds)))), \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_NOBIND_, ~)

// Functor inits.
        
#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MEMBER_INITS_(id, typename01, \
        const_binds, has_const_bind_this, binds, has_bind_this) \
    BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(BOOST_PP_BITOR(BOOST_PP_BITOR( \
            BOOST_PP_LIST_IS_CONS(const_binds), BOOST_PP_LIST_IS_CONS(binds)), \
            has_bind_this), has_const_bind_this), \
        : \
    ) \
    /* init const binds */ \
    BOOST_PP_LIST_FOR_EACH_I( \
  BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_INIT_ENUM_, \
            ( id, 0 /* no offset */ ), const_binds) \
    /* init plain binds */ \
    BOOST_PP_COMMA_IF( \
        BOOST_PP_BITAND( \
              BOOST_PP_LIST_IS_CONS(const_binds) \
            , BOOST_PP_LIST_IS_CONS(binds) \
        ) \
    ) \
    BOOST_PP_LIST_FOR_EACH_I( \
  BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_INIT_ENUM_, \
            /* offset index of # of const-binds (could be 0) */ \
            ( id, BOOST_PP_LIST_SIZE(const_binds) ), binds) \
    /* init `this` bind (const or not) */ \
    BOOST_PP_COMMA_IF( \
        BOOST_PP_BITAND( \
              BOOST_PP_BITOR( \
                  BOOST_PP_LIST_IS_CONS(const_binds) \
                , BOOST_PP_LIST_IS_CONS(binds) \
              ) \
            , BOOST_PP_BITOR(has_const_bind_this, has_bind_this) \
        ) \
    ) \
    BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(has_const_bind_this, has_bind_this), \
        BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BIND_MEMBER_THIS_( \
            static_cast< BOOST_SCOPE_EXIT_DETAIL_PARAMS_T(id)* >( \
                    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAMS_)-> \
                    BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_VAR \
        ) \
    )

// Functor class.

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_( \
        id, typename01, decl_traits, params, \
        default_count, const_binds, has_const_bind_this, binds, has_bind_this) \
    typedef class BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_CLASS_TYPE_(id) \
    /* run-time: do not use base class to allow for compiler optimizations */ \
    { \
        /* function type */ \
    private: \
        typedef \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_F_(id, typename01, \
                    decl_traits, 1 /* has type */, \
                    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_F_TYPE_) \
        ; \
        /* functor type -- this type cannot have ID postfix because it is */ \
        /* used the `NAME` macro (this symbol is within functor class so */ \
        /* it does not have to have ID postfix), must be public so it */ \
        /* can be accessed by `NAME` macro from outside this class */ \
    public: \
        typedef BOOST_PP_EXPR_IIF(typename01, typename) \
            BOOST_IDENTITY_TYPE(( /* IDENTITY for template param comma */ \
                ::boost::local_function::aux::function< \
                      BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_F_TYPE_ \
                    , default_count \
                    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS,\
                        BOOST_PP_TUPLE_EAT(6) \
                    , \
                        BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_BIND_TYPES_\
                    )(id, typename01, const_binds, has_const_bind_this, \
                            binds, has_bind_this) \
                > \
            )) \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_TYPE \
        ; \
    private: \
        BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BIND_TYPEOF_TYPEDEFS_( \
                id, typename01, \
                const_binds, has_const_bind_this, binds, has_bind_this) \
    public: \
        /* public trait interface following Boost.FunctionTraits names */ \
        /* (traits must be defined in both this and the global functor) */ \
        enum { arity = ::boost::function_traits< /* can't use static data */ \
                BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_F_TYPE_ >::arity }; \
        typedef BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPE(id, typename01) \
                result_type; \
        BOOST_PP_LIST_FOR_EACH_I( \
                BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_ARG_TYPEDEF_, \
                typename01, params) \
        /* constructor */ \
        inline explicit BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_CLASS_TYPE_(id)( \
                void* BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAMS_) \
            /* NOTE: there is no way to wrap member initializer commas */ \
            /* within paren so you must handle these commas manually if */ \
            /* expanding this macro within another macro */ \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MEMBER_INITS_(id, typename01,\
                    const_binds, has_const_bind_this, binds, has_bind_this) \
        { /* do nothing */ } \
        /* run-time: implement `operator()` (and for all default params) so */ \
        /* this obj can be used directly as a functor for C++03 extensions */ \
        /* and optimized macros */ \
        BOOST_PP_REPEAT( \
                /* PP_INC to handle no dflt (EXPAND for MVSC) */ \
                BOOST_PP_EXPAND(BOOST_PP_INC(default_count)), \
                BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_CALL_FOR_DEFAULTS_,\
                ( BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_CALL_, id, typename01 \
                , decl_traits, params, const_binds, has_const_bind_this, binds \
                , has_bind_this ) ) \
        /* compliance: trick to pass this local class as a template param */ \
        /* on pure C++03 without non C++03 extension */ \
        /* performance: this trick introduced _one_ indirect function call */ \
        /* via a function pointer that is usually not inlined by compliers */ \
        /* thus increasing run-time (also another trick using a base */ \
        /* interface class was investigated but virtual calls also cannot */ \
        /* inlined plus they require virtual table lookups to the "virtual */ \
        /* call trick" measured longer run-times than this "static call */ \
        /* trick") */ \
        BOOST_PP_REPEAT( \
                /* PP_INC to handle no dflt (EXPAND for MVSC) */ \
                BOOST_PP_EXPAND(BOOST_PP_INC(default_count)), \
                BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_CALL_FOR_DEFAULTS_,\
                ( BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_STATIC_CALL_, id \
                , typename01, decl_traits, params, const_binds \
                , has_const_bind_this, binds, has_bind_this ) ) \
        inline static void BOOST_LOCAL_FUNCTION_AUX_FUNCTION_INIT_CALL_FUNC( \
              void* object \
            , BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_TYPE& functor \
        ) { \
            functor.BOOST_LOCAL_FUNCTION_AUX_FUNCTION_INIT_CALL_FUNC( \
                    object \
                    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS,\
                        BOOST_PP_TUPLE_EAT(6) \
                    , \
  BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_COMMA_STATIC_BINDS_ \
                    )(id, typename01, const_binds, has_const_bind_this, \
                            binds, has_bind_this) \
                BOOST_PP_REPEAT( /* INC to handle no dflt (EXPAND for MVSC) */ \
                        BOOST_PP_EXPAND(BOOST_PP_INC(default_count)), \
  BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_STATIC_CALL_COMMA_FUNC_ADDR_, \
                        ~) \
            ); \
        } \
    private: \
        BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BIND_MEMBER_DECLS_(id, \
                typename01, const_binds, has_const_bind_this, binds, \
                has_bind_this) \
        /* this decl allows for nesting (local functions, etc) as */ \
        /* it makes the args variable visible within the body code (which */ \
        /* cannot be static); this is for compilation only as the args */ \
        /* variable is actually declared by the 1st enclosing local func */ \
        boost::scope_exit::detail::undeclared \
                BOOST_LOCAL_FUNCTION_AUX_DECL_ARGS_VAR; \
        /* body function (unfortunately, cannot be static to allow access */ \
        /* to member var with local function name for recursion but doing */ \
        /* so also allows the body to misuse `this` instead of `this_`) */ \
        inline BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPE(id, typename01) \
        BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_BODY_FUNC_( \
                /* const binds */ \
                BOOST_PP_LIST_FOR_EACH_I( \
  BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_ENUM_, \
                        ( id, typename01, 0 /* no offset */, 1 /* const */ ), \
                        const_binds) \
                /* plain binds */ \
                BOOST_PP_COMMA_IF( \
                    BOOST_PP_BITAND( \
                          BOOST_PP_LIST_IS_CONS(const_binds) \
                        , BOOST_PP_LIST_IS_CONS(binds) \
                    ) \
                ) \
                BOOST_PP_LIST_FOR_EACH_I( \
  BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_ENUM_, \
                        /* offset index of # of const-binds (could be 0) */ \
                        ( id, typename01, BOOST_PP_LIST_SIZE(const_binds), \
                          0 /* not const-bind */ ), binds) \
                /* `this` bind */ \
                BOOST_PP_COMMA_IF( \
                    BOOST_PP_BITAND( \
                          BOOST_PP_BITOR( \
                              BOOST_PP_LIST_IS_CONS(const_binds) \
                            , BOOST_PP_LIST_IS_CONS(binds) \
                          ) \
                        , BOOST_PP_BITOR(has_const_bind_this, has_bind_this) \
                    ) \
                ) \
                /* const pointer to const object */ \
                BOOST_PP_EXPR_IIF(has_const_bind_this, \
                    BOOST_PP_EXPR_IIF(typename01, typename) \
                    ::boost::local_function::aux::add_pointed_const< \
                        BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPE(id, \
                                typename01) \
                    >::type \
                    const this_ /* special name to access object this */ \
                ) \
                /* const pointer to non-const object */ \
                BOOST_PP_EXPR_IIF(has_bind_this, \
                    BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPE(id, \
                            typename01) \
                    const this_ /* special name to access object this */ \
                ) \
                /* params (last because they can have defaults) */ \
                BOOST_PP_COMMA_IF( \
                    BOOST_PP_BITAND( \
                          BOOST_PP_BITOR( \
                              BOOST_PP_BITOR( \
                                  BOOST_PP_LIST_IS_CONS(const_binds) \
                                , BOOST_PP_LIST_IS_CONS(binds) \
                              ) \
                            , BOOST_PP_BITOR(has_const_bind_this, \
                                    has_bind_this) \
                          ) \
                        , BOOST_PP_LIST_IS_CONS(params) \
                    ) \
                ) \
                BOOST_PP_LIST_FOR_EACH_I( \
  BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_PARAM_DECL_ENUM_, \
                        1 /* with defaults */, params) \
            ) /* end body function params */ \
            /* cannot be const because recursive functor is non const member */\
    /* user local function definition `{ ... }` will follow here */ \
    /* `END` macro will close function class decl `};` here */ 

// PUBLIC //

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_TYPE \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (functor_type) )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR(id, typename01, decl_traits) \
    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_(id, typename01, decl_traits \
        /* params (might have defaults) */ \
        , BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
        , BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS_DEFAULT_COUNT( \
                decl_traits) \
        /* const bind vars (`this` excluded) */ \
        , BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
        /* if const bind `this` is present */ \
        , BOOST_PP_LIST_IS_CONS( \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                decl_traits)) \
        /* bind (non-const) vars (`this` excluded) */ \
        , BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
        /* if (non-const) bind `this` is present */ \
        , BOOST_PP_LIST_IS_CONS( \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES( \
                decl_traits)) \
    )

#endif // #include guard


/* functor.hpp
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
*/