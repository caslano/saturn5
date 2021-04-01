
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
gQtxIQuLd7g4ga5oVkXLzvZ/hp95OYGbyVMAlkskZFrnvB/0761QlNeA4BsMEYU2c2B+pTpB8APhSQ6yCLV5Q+CGSc6j6cTIKFjlSSc2J5qWrsxjfVvsyiEPPJE1aoVcDdM9CHNHRBQaLAmTEzqElBQpTyMdOz7BcrdGQGXvpVIivZlF0P/bSdeYbbTCOAX6qYET9miRn27e8QAiq7pjXdIpajqvbErjEoj2firzHr3XqqzJr0FGtSiNswwj5ee9n1ArsPkOAD1w037xpYCtq96iIfcBDPd2kFIQGEhgtO0v/JVeIaTavS3FSjafMf26741oysZJ67wXJPbTd966/hHvw8qa+sV8X2tbWg3KVfl+4JIvikX5SaDXS3/qtV6+bfVWHYVzSz1p9ElY2CRShd9POvk6EFsovkByprpc69xoWIAxM9x7XOgz09zbhBRa84sRTa1pzGh1pws+kBXV7XJt8Axv8YeQ5bgS7/uV/wQvO1ONXo4hBiP3qsAFgX84GsEyyVYJoymtKpfVTYuQIYLmVC9jgUDUOi1kRjjStmSoxeyHLeb/U3iGMA==
*/