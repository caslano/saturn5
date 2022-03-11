
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