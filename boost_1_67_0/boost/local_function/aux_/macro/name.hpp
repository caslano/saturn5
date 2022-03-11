
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