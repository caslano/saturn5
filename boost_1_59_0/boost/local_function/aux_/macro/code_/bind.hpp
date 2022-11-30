
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_HPP_

#include <boost/local_function/aux_/symbol.hpp>
#include <boost/local_function/aux_/macro/decl.hpp>
#include <boost/local_function/aux_/preprocessor/traits/bind.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_binds.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_const_binds.hpp>
#include <boost/utility/identity_type.hpp>
#include <boost/scope_exit.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/list/for_each_i.hpp>
#include <boost/preprocessor/list/append.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_PARAMS_VAR_(id) \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (params)(id) )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_TAG_DECL_(r, id, i, bind_traits) \
    BOOST_SCOPE_EXIT_DETAIL_TAG_DECL(r, id, i, \
            BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE( \
                    bind_traits))

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_CAPTURE_DECL_TYPED_( \
        r, id, typename01, i, bind_traits) \
    typedef BOOST_PP_EXPR_IIF(typename01, typename) \
        /* remove ref because typed var can have & prefix */ \
        ::boost::remove_reference< BOOST_PP_EXPR_IIF(typename01, typename) \
            ::boost::function_traits< \
                /* instead of using Boost.Typeof, get bind type as 1st */ \
                /* argument type of func type `void (type_ [&] var_)` */ \
                void ( BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITH_TYPE( \
                        bind_traits) ) \
            >::arg1_type \
        >::type \
        BOOST_SCOPE_EXIT_DETAIL_CAPTURE_T(id, i, \
                BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE( \
                        bind_traits)) \
    ; /* close typedef */

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_CAPTURE_DECL_DEDUCED_( \
        r, id, typename01, i, bind_traits) \
    BOOST_SCOPE_EXIT_DETAIL_CAPTURE_DECL(r, \
            ( \
                id \
            , \
                /* ScopeExit expects typename or EMPTY() here */ \
                BOOST_PP_EXPR_IIF(typename01, typename) \
            ), \
            i, BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE( \
                    bind_traits))

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_CAPTURE_DECL_( \
        r, id_typename, i, bind_traits) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
  BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITH_TYPE(bind_traits)), \
        BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_CAPTURE_DECL_DEDUCED_ \
    , \
        BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_CAPTURE_DECL_TYPED_ \
    )(r, BOOST_PP_TUPLE_ELEM(2, 0, id_typename), \
            BOOST_PP_TUPLE_ELEM(2, 1, id_typename), i, bind_traits)

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_PARAM_DECL_( \
        r, id_typename, i, bind_traits) \
    BOOST_SCOPE_EXIT_DETAIL_PARAM_DECL(r, \
            ( \
                BOOST_PP_TUPLE_ELEM(2, 0, id_typename) \
            , \
                /* ScopeExit expects typename or EMPTY() here */ \
                BOOST_PP_EXPR_IIF(BOOST_PP_TUPLE_ELEM(2, 1, id_typename), \
                    typename \
                ) \
            ), \
            i, BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE( \
                    bind_traits))

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_MEMBER_DECL_VAR_( \
        r, id, typename01, i, var) \
    BOOST_PP_EXPR_IIF(typename01, typename) \
    BOOST_IDENTITY_TYPE(( /* must use IDENTITY because of tparam comma */ \
        ::boost::scope_exit::detail::member< \
              BOOST_SCOPE_EXIT_DETAIL_PARAM_T(id, i, var) \
            , BOOST_SCOPE_EXIT_DETAIL_TAG(id, i) \
        > \
    )) \
    BOOST_SCOPE_EXIT_DETAIL_PARAM(id, i, var);

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_MEMBER_DECL_( \
        r, id_typename, i, bind_traits) \
    BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_MEMBER_DECL_VAR_(r, \
            BOOST_PP_TUPLE_ELEM(2, 0, id_typename), \
            BOOST_PP_TUPLE_ELEM(2, 1, id_typename), \
            i, BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE( \
                    bind_traits))

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_PARAM_INIT_(r, id, i, bind_traits) \
    BOOST_SCOPE_EXIT_DETAIL_PARAM_INIT(r, id, i, \
            BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE( \
                    bind_traits))

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_CAPTURE_TYPE_(id) \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (this_capture_type)(id) )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPE_(id) \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (this_type)(id) )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPEDEF_DEDUCED_( \
        id, typename01, all_bind_this_types) \
    BOOST_SCOPE_EXIT_DETAIL_TYPEDEF_TYPEOF_THIS(id, \
            BOOST_PP_EXPR_IIF(typename01, typename), /* otherwise EMPTY() */ \
            BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_CAPTURE_TYPE_(id))

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPEDEF_TYPED_( \
        id, typename01, all_bind_this_types) \
    typedef \
        BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_THIS_TYPE(BOOST_PP_LIST_FIRST( \
                all_bind_this_types)) \
        BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_CAPTURE_TYPE_(id) \
    ;
    
#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPEDEF_( \
        id, typename01, all_bind_this_types) \
    /* typedef type_ */ \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            /* all_bind_this_type is list with 1 elem (possibly PP_EMPTY), */ \
            /* otherwise got a pp-parsing error before getting here */ \
            BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_THIS_TYPE( \
                    BOOST_PP_LIST_FIRST(all_bind_this_types))), \
        BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPEDEF_DEDUCED_ \
    , \
        BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPEDEF_TYPED_ \
    )(id, typename01, all_bind_this_types)

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_ALL_( \
        all_binds, all_bind_this_types, id, typename01) \
    /* binding tags */ \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS(all_bind_this_types), \
        BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPEDEF_ \
    , \
        BOOST_PP_TUPLE_EAT(3) \
    )(id, typename01, all_bind_this_types) \
    BOOST_PP_LIST_FOR_EACH_I(BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_TAG_DECL_, id, \
            all_binds) \
    BOOST_PP_LIST_FOR_EACH_I(BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_CAPTURE_DECL_, \
            (id, typename01), all_binds) \
    /* binding class */ \
    struct BOOST_SCOPE_EXIT_DETAIL_PARAMS_T(id) { \
        /* interim capture types to workaround internal error on old GCC */ \
        BOOST_PP_EXPR_IIF(BOOST_PP_LIST_IS_CONS(all_bind_this_types), \
            typedef BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_CAPTURE_TYPE_(id) \
                    BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPE_(id) ; \
        ) \
        BOOST_PP_EXPR_IIF(BOOST_PP_LIST_IS_CONS(all_bind_this_types), \
            BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPE_(id) \
            BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_VAR; \
        ) \
        BOOST_PP_LIST_FOR_EACH_I( \
                BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_PARAM_DECL_, \
                (id, typename01), all_binds) \
        BOOST_PP_LIST_FOR_EACH_I( \
                BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_MEMBER_DECL_, \
                (id, typename01), all_binds) \
    } BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_PARAMS_VAR_(id) = \
    /* NOTE: there is no way to wrap member initializer commas within */ \
    /* parenthesis so you must handle these commas manually if expanding */ \
    /* this macro within another macro */ \
    { \
        /* initialize the struct with param values to bind */ \
        BOOST_PP_EXPR_IIF(BOOST_PP_LIST_IS_CONS(all_bind_this_types), \
                this) /* here name `this` access object at enclosing scope */ \
        BOOST_PP_COMMA_IF(BOOST_PP_BITAND( \
              BOOST_PP_LIST_IS_CONS(all_bind_this_types) \
            , BOOST_PP_LIST_IS_CONS(all_binds) \
        )) \
        BOOST_PP_LIST_FOR_EACH_I( \
                BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_PARAM_INIT_, id, all_binds) \
    };

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_(id, typename01, decl_traits) \
    /* IMPORTANT: the order of these appends is important, it must follow */ \
    /* the indexing order used by the functor code which starts */ \
    /* enumerating const binds and then non-const binds */ \
    BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_ALL_( \
            BOOST_PP_LIST_APPEND( \
                    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS( \
                            decl_traits),\
                    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS( \
                            decl_traits)), \
            BOOST_PP_LIST_APPEND( \
  BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES(decl_traits), \
                    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES( \
                            decl_traits)), \
            id, typename01)

// PUBLIC //

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPE(id, typename01) \
    BOOST_PP_EXPR_IIF(typename01, typename) \
    BOOST_SCOPE_EXIT_DETAIL_PARAMS_T(id):: \
            BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_TYPE_(id)

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_THIS_VAR \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (this_var) )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_BIND(id, typename01, decl_traits) \
    /* the binding data structures must be declared and initialized (to */ \
    /* empty structs, so hopefully the compiler will optimize away the */ \
    /* no-op code) even when there is no bound param because these structs */ \
    /* are used to init `...args.value` which is always used by the `END` */ \
    /* macro later because this macro does not know if there are bound */ \
    /* params or not */ \
    BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_(id, typename01, decl_traits) \
    /* this code takes advantage of the template argument list/comparison */ \
    /* operator ambiguity to declare a variable iff it hasn't already been */ \
    /* declared in that scope; the second occurrence is parsed as: */ \
    /*  (declared<(resolve<sizeof(boost_local_auxXargs)>::cmp1<0)>::cmp2> */ \
    /*      ...Xargs); */ \
    /* which is a no-op */ \
    ::boost::scope_exit::detail::declared< boost::scope_exit::detail::resolve< \
        /* cannot prefix with `::` as in `sizeof(:: ...` because the name */ \
        /* must refer to the local variable name to allow multiple local */ \
        /* functions (and exits) within the same scope (however this */ \
        /* does not allow for nesting because local variables cannot be */ \
        /* used in nested code blocks) */ \
        sizeof(BOOST_LOCAL_FUNCTION_AUX_DECL_ARGS_VAR) \
    >::cmp1<0>::cmp2 > BOOST_LOCAL_FUNCTION_AUX_DECL_ARGS_VAR; \
    /* stores bound types/values into `...args` variable (args variable */ \
    /* can be accessed by `NAME` macro because doesn't use __LINE__ id) */ \
    BOOST_LOCAL_FUNCTION_AUX_DECL_ARGS_VAR.value = \
            &BOOST_LOCAL_FUNCTION_AUX_CODE_BIND_PARAMS_VAR_(id);

#endif // #include guard


/* bind.hpp
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
*/