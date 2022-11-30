
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_HPP_

#include <boost/local_function/aux_/symbol.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_returns.hpp>
#include <boost/scope_exit.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/cat.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_FUNC_(id) \
    /* symbol (not internal) also gives error if missing result type */ \
    BOOST_PP_CAT( \
  ERROR_missing_result_type_before_the_local_function_parameter_macro_id, \
            id)

#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_PARAMS_(id) \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (deduce_result_params)(id) )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPE_(id) \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (result_type)(id) )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_INDEX_ \
    /* this does not have to be an integral index because ScopeExit uses */ \
    /* just as a symbol to concatenate go generate unique symbols (but */ \
    /* if it'd ever needed to became integral, the number of function */ \
    /* params + 1 as in the macro CONFIG_ARITY_MAX could be used) */ \
    result

// User did not explicitly specified result type, deduce it (using Typeof).
#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_DEDUCE_( \
        id, typename01, decl_traits) \
    /* user specified result type here */ \
    BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_DECL(id) \
    /* tagging, wrapping, etc as from ScopeExit type deduction are */ \
    /* necessary within templates (at least on GCC) to work around an */ \
    /* compiler internal errors) */ \
    BOOST_SCOPE_EXIT_DETAIL_TAG_DECL(0, /* no recursive step r */ \
            id, BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_INDEX_, \
            BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_FUNC_(id)) \
    BOOST_SCOPE_EXIT_DETAIL_CAPTURE_DECL(0, /* no recursive step r */ \
            ( id, BOOST_PP_EXPR_IIF(typename01, typename) ), \
            BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_INDEX_, \
            BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_FUNC_(id)) \
    /* extra struct to workaround GCC and other compiler's issues */ \
    struct BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_PARAMS_(id) { \
        typedef \
            BOOST_PP_EXPR_IIF(typename01, typename) \
            ::boost::function_traits< \
                BOOST_PP_EXPR_IIF(typename01, typename) \
                ::boost::remove_pointer< \
                    BOOST_SCOPE_EXIT_DETAIL_CAPTURE_T(id, \
                            BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_INDEX_, \
                            BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_FUNC_(id)) \
                >::type \
            >::result_type \
            BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPE_(id) \
        ; \
    };

// Use result type as explicitly specified by user (no type deduction needed).
// Precondition: RETURNS(decl_traits) != NIL
#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPED_( \
        id, typename01, decl_traits) \
    /* user specified result type here */ \
    struct BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_PARAMS_(id) { \
        typedef \
            BOOST_PP_LIST_FIRST( \
                    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS( \
                            decl_traits)) \
            BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPE_(id) \
        ; \
    };

// PUBLIC //

#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPE(id, typename01) \
    BOOST_PP_EXPR_IIF(typename01, typename) \
    BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_PARAMS_(id) :: \
    BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPE_(id)

#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_DECL(id) \
    /* result type here */ (*BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_FUNC_(id))();

#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT(id, typename01, decl_traits) \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits)), \
        BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPED_ \
    , \
        BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_DEDUCE_ \
    )(id, typename01, decl_traits)

#endif // #include guard


/* result.hpp
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
*/