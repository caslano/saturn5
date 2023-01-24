
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
VbkViDi35K4qWeQlN8/tTbQRgiFSO+0it5ALXnKSjk3aH1IQ3D9g+kIlrJyPK6swbHwcjsW10z/VNx8QSe/6SN+QEZYJIRkjERBuvhBEp0mjsUXsnuU2XvcGNcSwRmS7hrb7yTAPAWQqH754nxUjjDEcesbfz4TYHdPXJcE+ZNPK2Bch6f9xLXFXtecY0J0keN9iNJo4RODUGeKdLzGK856ex3w0e58lzrfWpU6a3pXS0cea1pfLOmEoHpvnVFDI5aZbKCea7559/26ywnrYvW4u5pJ1y1T7x/nykKcB9XGQAr7fb2Owuo7AoP7+Mgf0zlxgEP6djY6qwCBMuNl4es1w6P5AWGBQztQtOjdlhcNYkXBAKD4hy+yOORMa5p2fadEZ3J7EQks0Ge9sEt0eyXYZSrdLdeO2HdUykZQqurMtg1y0ikGdRHgWp2oEyGEa0KV1usZXBvr0+5XwCnn6Eq2rMyeErxbp0MUvylHvyTxQUXrl7MwlsuUFv90TIIqyd0qz71707ersk0O/JjvRd/puIHJO40V3hRdDit/xuPz2qdWZh3OXM8tnhqaHYT1mtohEuyQF8CFMiLbrmvkph5DlLmpMJ6XrAJh4NX9BbfOjZcfnHUYmXXKk3v6VoNDD1y4JlCU8MSasOA35qYV4T19jsI7XVbSHNQKuJuNWZGeITlfSMSu+h1N2FgFykXeLuQ6qtvgLYc4BDmjM
*/