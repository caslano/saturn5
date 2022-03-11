
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_returns.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_params.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_const_binds.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_binds.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_error.hpp>
#include <boost/local_function/aux_/preprocessor/traits/param.hpp>
#include <boost/local_function/detail/preprocessor/keyword/return.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/list/append.hpp>
#include <boost/preprocessor/list/size.hpp>
#include <boost/preprocessor/list/at.hpp>
#include <boost/preprocessor/list/first_n.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_PARAM_DEFAULT_( \
        params, default_value) \
    /* `DEC` ok because precondition that unbinds are not nil-list */ \
    BOOST_PP_LIST_APPEND( \
        BOOST_PP_LIST_FIRST_N(BOOST_PP_DEC(BOOST_PP_LIST_SIZE(params)), \
                params) \
    , \
        ( /* list 2-tuple */ \
            ( /* (param_decl, default) 2-tuple */ \
                BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_DECL( \
                        BOOST_PP_LIST_AT(params, BOOST_PP_DEC( \
                                BOOST_PP_LIST_SIZE(params)))) \
            , \
                default_value BOOST_PP_EMPTY \
            ) \
        , \
            BOOST_PP_NIL \
        ) \
    )

// PUBLIC //

// return_type: `return result_type`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_RETURN( \
        decl_traits, return_type) \
    ( /* returns */ \
        BOOST_PP_LIST_APPEND( \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits), \
                ( BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_RETURN_REMOVE_FRONT( \
                  return_type), BOOST_PP_NIL ) ) \
    , /* params and defaults */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
    , /* const-bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    , /* const-bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                decl_traits) \
    , /* bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    , /* bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    , /* error message (if any) */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    )


// param_decl: `[auto | register] type_ name_`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_PARAM( \
        decl_traits, param_decl) \
    ( /* returns */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    , /* params and defaults */ \
        BOOST_PP_LIST_APPEND( \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits), \
                /* append param (with no default -- EMPTY) */ \
                ( (param_decl, BOOST_PP_EMPTY), BOOST_PP_NIL ) ) \
    , /* const-bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    , /* const-bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                decl_traits) \
    , /* bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    , /* bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    , /* error message (if any) */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    )

// default_value: a valid parameter default value (`-1`, etc).
// Precondition: already added unbinds are not nil-list.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_PARAM_DEFAULT( \
        decl_traits, default_value) \
    ( /* returns */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    , /* unbind params and defaults */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_PARAM_DEFAULT_( \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits), \
                default_value) /* append default to last added param */ \
    , /* const-bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    , /* const-bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                decl_traits) \
    , /* bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    , /* bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    , /* error message (if any) */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    )

// var_without_type: `[&] var_` (var_ != this).
// var_with_type: `PP_EMPTY | type [&] var_` (var_ != this).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_BIND( \
        decl_traits, var_without_type, var_with_type) \
    ( /* returns */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    , /* params and defaults */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
    , /* const-bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    , /* const-bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                decl_traits) \
    , /* bind vars */ \
        BOOST_PP_LIST_APPEND( \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits), \
                ( (var_without_type, var_with_type), BOOST_PP_NIL ) ) \
    , /* bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    , /* error message (if any) */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    )

// this_type: `PP_EMPTY | type`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_BIND_THIS_TYPE( \
        decl_traits, this_type) \
    ( /* returns */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    , /* params and defaults */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
    , /* const-bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    , /* const-bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                decl_traits) \
    , /* bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    , /* bind `this` types */ \
        BOOST_PP_LIST_APPEND( \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES( \
                        decl_traits), \
                ( (this_type), BOOST_PP_NIL ) ) \
    , /* error message (if any) */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    ) 

// var_without_type: `[&] var_` (var_ != this).
// var_with_type: `BOOST_PP_EMPTY | type_ [&] name_` (var_ != this).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_CONST_BIND( \
        decl_traits, var_without_type, var_with_type) \
    ( /* returns */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    , /* params and defaults */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
    , /* const-bind vars */ \
        BOOST_PP_LIST_APPEND( \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS( \
                        decl_traits), \
                ( (var_without_type, var_with_type), BOOST_PP_NIL ) ) \
    , /* const-bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                decl_traits) \
    , /* bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    , /* bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    , /* error message (if any) */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    ) 

// this_type: `PP_EMPTY | type`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_CONST_BIND_THIS_TYPE( \
        decl_traits, this_type) \
    ( /* returns */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    , /* params and defaults */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
    , /* const-bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    , /* const-bind `this` types */ \
        BOOST_PP_LIST_APPEND( \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                        decl_traits), \
                ( (this_type), BOOST_PP_NIL ) ) \
    , /* bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    , /* bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    , /* error message (if any) */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    )

#endif // #include guard


/* append.hpp
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
*/