
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_NIL_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_NIL_HPP_

#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_NIL \
    ( \
        /* returns: list of `return result_type` */ \
        BOOST_PP_NIL /* nil list */ \
    , \
        /* params: list of 2-tuples (param_decl, param_default) */ \
        BOOST_PP_NIL /* nil list */ \
    , \
        /* const-binds: list of 2-tuple `(var_untyped, var_typed)` */ \
        BOOST_PP_NIL /* nil list */ \
    , \
        /* const-bind this: list of 1-tuple `(type)` */ \
        BOOST_PP_NIL \
      /* number of const-bind `this` */ \
    , \
        /* binds: list of 2-tuple `(var_untyped, var_typed)` */ \
        BOOST_PP_NIL /* nil list */ \
    , \
        /* bind this: list of 1-type `(type)` */ \
        BOOST_PP_NIL \
    , \
        /* error: `[ERROR_message_text] EMPTY` */ \
        BOOST_PP_EMPTY /* no error */ \
    )

#endif // #include guard


/* nil.hpp
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
*/