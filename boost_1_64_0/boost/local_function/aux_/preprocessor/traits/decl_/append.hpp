
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
PIeWM2iZj4U3eDb8mJeV82cDz55dwP3FUOuE9udqMyYiO3xq8pEFtJ5De4XlLNql59Mu8LeeP1u7Xxfmdckb9zeCS7m3GvodYp434PxZOXtW5n4Dz6DNxy1n0DIfbD2HFsSdcHSC5Rza0HliYzJ5uZB8EW4ilIF7OBQ8d1zEveAzaFeDwfPJ6yfLnHIRbQnynzE7H2rVnC8r883qbNm1UPC8s3EUsoNDQTlLljlo8yxZNRc9D0PrOci+AFoBrYNSihOMXKgImlMcnfP9J65/bvxfOsvtVQBs5vg/U8b/hm/8D1NRAHD5dQBpGh3A/RYdwByNDqCZF5THHaIDGDmuoGMdgMcd2fhKpwNYr9cBYExuqwNAtk3XASy00QE0uvU6ABLTjtkWutsds8EvojFbhzqAYhsdwBq3vQ4A2bU6gHXuNh3AIspjKLwf2EI6gDyNDuBM5M4vD9EBIG7HY0zimTqAZwYTTj0LaoCuP58lQj1VsA6ANHCbaQTUyUYbHYArMG/BbVfbntzl7bYneEbUnjrUASyw0QE0ltvpABA9DB1AY3nn6gBSbHQATeXt6QCQ9X+oA/hNjblXehIrth3QuvXohvKcuFdOnx7VAUR1AJHrAB7Q6AA87k3TAdS5N00H0OjuXB3AGnfn6ADyyzdPB+Aq71wdQGP5pukAmsq3jA5gIWOQpuKoDiCqA4jqALaUDmA1z1crlFVCm4UqofnQUuiDkqgOYEtf/9j43zPDO27wagA2a/y/jYz/fy/x9vOeGeUnq/GIXwmgxvoP9jfMca5Lxrn5/vc7lLMT79DS4HG1ycv6bW/uJ7ZWhe+tzimPMyQ+qWxtJFu/+7kfvN8fGghQNyazhh3Sz3K2nqTxi/IfovyP8p3zO8u6R+YXyj9V3JwIMU1kZDy7WuwKHlL7bhqGdX/2upSOxwFBY5HA/egkT6kSBtm5J7Jzdu7PSi7DQOaA8wfTNOft70Bd5E6zrQunrwEZweWpG3MJH0dEOpGgM9FD9mpfEhuqK5pLvgrtZa42wrAbKZzW4Xh8rE5nZD0PplnG3cUyHpwiuhDXNDtdiFVIvV1ElYo7Ru2zvJS8zyeNhynH2HTOPNkZvUhmnHXsreqlyhvRW3bVql7U2c1yBgYX5zw6lZ/5LJ2v0thG3JyPqdzxtjqWODsdi7S386bZtLd4CQg5oJGil1ijLR9d2YhuQsrmMxVvBKfdOKQfEF6kkGFsZ61fue8ILh/z2W5V/tsb7ZVTa1A59S1T575Yyz/s/Q3N51jcyIRb0qMMf7KUobWNFXfVl2F+mZ1ux1qM+nIcXRZSjvDTliP32y/HorKOy5EwAeV4amTlOCqScjyyzCzHgH4kNyFU/3c2YRqDytFafuHYmhDf3MuONPk1XW8DVNZhf6PLp7l3HbxxTw94vj5I0OvOmsr0ujNL1jrMV1NZ5+jP/OVfkegLWCp9pVNkXVNm0Z9ZBJTtLa1ymvtrf6fiFErbFR5wzjb2tuaB+/bnVySpMfyulnc/H0iGtv/0zFDNq+3863gVN4+0/M+EGcR8LuJUmH3N8lum6UuTw2jjXlnU+13kS7e2e2u6tP0Yt9n2lXugO6hPEV3mmkS9LtPlttdlWqrmf6fPzD3Swf35xueTfvgtZ98nHhhSfeq23WKj+syoPjN8faZ//5uHLfrMh+T3JEj2rJExhRrvhOxZc5Dowg4Gu4JjwSzwcDAbLAQHgYeA+4KHgfvLfdG18Y1tr6MbKfxHgb3AAyzxCqfZ61wnSrxJIteR1j1fJF6xRtc5RHR624Pp4A7gWHFPAXNAs1yEzyhNuWSKzrQvmAz2B/uC24ADwAHg3mA2uA+4HThS3MKf7xR7/js=
*/