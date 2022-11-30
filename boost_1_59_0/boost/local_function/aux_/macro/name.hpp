
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_NAME_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_NAME_HPP_

#include <boost/local_function/config.hpp>
#include <boost/local_function/aux_/macro/decl.hpp>
#include <boost/local_function/aux_/macro/code_/functor.hpp>
#include <boost/local_function/detail/preprocessor/keyword/recursive.hpp>
#include <boost/local_function/detail/preprocessor/keyword/inline.hpp>
#include <boost/local_function/aux_/function.hpp>
#include <boost/local_function/aux_/symbol.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_NAME_LOCAL_TYPE_(local_function_name) \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (local_type)(local_function_name) )

#define BOOST_LOCAL_FUNCTION_AUX_NAME_INIT_RECURSION_FUNC_ \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (init_recursion) )

#define BOOST_LOCAL_FUNCTION_AUX_NAME_RECURSIVE_FUNC_( \
        is_recursive, local_function_name) \
    BOOST_PP_IIF(is_recursive, \
        local_function_name \
    , \
        BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (nonrecursive_local_function_name) ) \
    )

#define BOOST_LOCAL_FUNCTION_AUX_NAME_END_LOCAL_FUNCTOR_(typename01, \
        local_function_name, is_recursive, \
        local_functor_name, nonlocal_functor_name) \
    /* FUNCTION macro expanded to: typedef class functor ## __LINE__ { ... */ \
    BOOST_PP_EXPR_IIF(is_recursive, \
        /* member var with function name for recursive calls; it cannot be */ \
        /* `const` because it is init after construction (because */ \
        /* constructor doesn't know local function name) */ \
        /* run-time: even when optimizing, recursive calls cannot be */ \
        /* optimized (i.e., they must be via the non-local functor) */ \
        /* because this cannot be a mem ref because its name is not known */ \
        /* by the constructor so it cannot be set by the mem init list */ \
    private: \
        BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_TYPE \
                BOOST_LOCAL_FUNCTION_AUX_NAME_RECURSIVE_FUNC_(is_recursive, \
                        local_function_name); \
        /* run-time: the `init_recursion()` function cannot be called */ \
        /* by the constructor to allow for compiler optimization */ \
        /* (inlining) so it must be public to be called (see below) */ \
    public: \
        inline void BOOST_LOCAL_FUNCTION_AUX_NAME_INIT_RECURSION_FUNC_( \
                BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_TYPE& functor) { \
            local_function_name = functor; \
        } \
    ) \
    } BOOST_LOCAL_FUNCTION_AUX_NAME_LOCAL_TYPE_(local_function_name); \
    /* local functor can be passed as tparam only on C++11 (faster) */ \
    BOOST_LOCAL_FUNCTION_AUX_NAME_LOCAL_TYPE_(local_function_name) \
            local_functor_name(BOOST_LOCAL_FUNCTION_AUX_DECL_ARGS_VAR.value); \
    /* non-local functor can always be passed as tparam (but slower) */ \
    BOOST_PP_EXPR_IIF(typename01, typename) \
    BOOST_LOCAL_FUNCTION_AUX_NAME_LOCAL_TYPE_(local_function_name):: \
            BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_TYPE \
            nonlocal_functor_name; /* functor variable */ \
    /* the order of the following 2 function calls cannot be changed */ \
    /* because init_recursion uses the local_functor so the local_functor */ \
    /* must be init first */ \
    local_functor_name.BOOST_LOCAL_FUNCTION_AUX_FUNCTION_INIT_CALL_FUNC( \
            &local_functor_name, nonlocal_functor_name); \
    BOOST_PP_EXPR_IIF(is_recursive, \
        /* init recursion causes MSVC to not optimize local function not */ \
        /* even when local functor is used as template parameter so no */ \
        /* recursion unless all inlining optimizations are specified off */ \
        local_functor_name.BOOST_LOCAL_FUNCTION_AUX_NAME_INIT_RECURSION_FUNC_( \
                nonlocal_functor_name); \
    )

#define BOOST_LOCAL_FUNCTION_AUX_NAME_FUNCTOR_(local_function_name) \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (local_function_name) )

// This can always be passed as a template parameters (on all compilers).
// However, it is slower because it cannot be inlined.
// Passed at tparam: Yes (on all C++). Inlineable: No. Recursive: No.
#define BOOST_LOCAL_FUNCTION_AUX_NAME_(typename01, local_function_name) \
    BOOST_LOCAL_FUNCTION_AUX_NAME_END_LOCAL_FUNCTOR_(typename01, \
            local_function_name, \
            /* local function is not recursive (because recursion and its */ \
            /* initialization cannot be inlined even on C++11, */ \
            /* so this allows optimization at least on C++11) */ \
            0 /* not recursive */ , \
            /* local functor */ \
            BOOST_LOCAL_FUNCTION_AUX_NAME_FUNCTOR_(local_function_name), \
            /* local function declared as non-local functor -- but it can */ \
            /* be inlined only by C++11 and it cannot be recursive */ \
            local_function_name)

// This is faster on some compilers but not all (e.g., it is faster on GCC
// because its optimization inlines it but not on MSVC). However, it cannot be
// passed as a template parameter on non C++11 compilers.
// Passed at tparam: Only on C++11. Inlineable: Yes. Recursive: No.
#define BOOST_LOCAL_FUNCTION_AUX_NAME_INLINE_(typename01, local_function_name) \
    BOOST_LOCAL_FUNCTION_AUX_NAME_END_LOCAL_FUNCTOR_(typename01, \
            local_function_name, \
            /* inlined local function is never recursive (because recursion */ \
            /* and its initialization cannot be inlined)*/ \
            0 /* not recursive */ , \
            /* inlined local function declared as local functor (maybe */ \
            /* inlined even by non C++11 -- but it can be passed as */ \
            /* template parameter only on C++11 */ \
            local_function_name, \
            /* non-local functor */ \
            BOOST_LOCAL_FUNCTION_AUX_NAME_FUNCTOR_(local_function_name))

// This is slower on all compilers (C++11 and non) because recursion and its
// initialization can never be inlined.
// Passed at tparam: Yes. Inlineable: No. Recursive: Yes.
#define BOOST_LOCAL_FUNCTION_AUX_NAME_RECURSIVE_( \
        typename01, local_function_name) \
    BOOST_LOCAL_FUNCTION_AUX_NAME_END_LOCAL_FUNCTOR_(typename01, \
            local_function_name, \
            /* recursive local function -- but it cannot be inlined */ \
            1 /* recursive */ , \
            /* local functor */ \
            BOOST_LOCAL_FUNCTION_AUX_NAME_FUNCTOR_(local_function_name), \
            /* local function declared as non-local functor -- but it can */ \
            /* be inlined only by C++11 */ \
            local_function_name)

// Inlined local functions are specified by `..._NAME(inline name)`.
// They have more chances to be inlined for faster run-times by some compilers
// (for example by GCC but not by MSVC). C++11 compilers can always inline
// local functions even if they are not explicitly specified inline.
#define BOOST_LOCAL_FUNCTION_AUX_NAME_PARSE_INLINE_( \
        typename01, qualified_name) \
    BOOST_PP_IIF(BOOST_PP_BITOR( \
            BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_INLINE_FRONT( \
                    qualified_name)), \
        /* on C++11 always use inlining because compilers might optimize */ \
        /* it to be faster and it can also be passed as tparam */ \
        BOOST_LOCAL_FUNCTION_AUX_NAME_INLINE_ \
    , \
        /* on non C++11 don't use liniling unless explicitly specified by */ \
        /* programmers `inline name` the inlined local function cannot be */ \
        /* passed as tparam */ \
        BOOST_LOCAL_FUNCTION_AUX_NAME_ \
    )(typename01, BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_INLINE_REMOVE_FRONT( \
            qualified_name))

// Expand to 1 iff `recursive name` or `recursive inline name` or
// `inline recursive name`.
#define BOOST_LOCAL_FUNCTION_AUX_NAME_IS_RECURSIVE_(qualified_name) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_RECURSIVE_FRONT( \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_INLINE_REMOVE_FRONT( \
        qualified_name \
    ))

// Revmoes `recursive`, `inline recursive`, and `recursive inline` from front.
#define BOOST_LOCAL_FUNCTION_AUX_NAME_REMOVE_RECURSIVE_AND_INLINE_( \
        qualified_name) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_RECURSIVE_REMOVE_FRONT( \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_INLINE_REMOVE_FRONT( \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_RECURSIVE_REMOVE_FRONT( \
        qualified_name \
    )))

#define BOOST_LOCAL_FUNCTION_AUX_NAME_RECURSIVE_REMOVE_(qualified_name) \
    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_AUX_NAME_IS_RECURSIVE_(qualified_name), \
        BOOST_LOCAL_FUNCTION_AUX_NAME_REMOVE_RECURSIVE_AND_INLINE_ \
    , \
        qualified_name /* might be `name` or `inline name` */ \
        BOOST_PP_TUPLE_EAT(1) \
    )(qualified_name)

// Recursive local function are specified by `..._NAME(recursive name)`. 
// They can never be inlined for faster run-time (not even by C++11 compilers).
#define BOOST_LOCAL_FUNCTION_AUX_NAME_PARSE_RECURSIVE_( \
        typename01, qualified_name) \
    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_AUX_NAME_IS_RECURSIVE_(qualified_name), \
        /* recursion can never be inlined (not even on C++11) */ \
        BOOST_LOCAL_FUNCTION_AUX_NAME_RECURSIVE_ \
    , \
        BOOST_LOCAL_FUNCTION_AUX_NAME_PARSE_INLINE_ \
    )(typename01, \
            BOOST_LOCAL_FUNCTION_AUX_NAME_RECURSIVE_REMOVE_(qualified_name))

// PUBLIC //

#define BOOST_LOCAL_FUNCTION_AUX_NAME(typename01, qualified_name) \
    BOOST_LOCAL_FUNCTION_AUX_NAME_PARSE_RECURSIVE_(typename01, qualified_name)

#endif // #include guard


/* name.hpp
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
*/