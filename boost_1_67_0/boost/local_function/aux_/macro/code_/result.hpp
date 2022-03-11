
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