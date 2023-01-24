
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/local_function/aux_/preprocessor/traits/param.hpp>
#include <boost/local_function/detail/preprocessor/keyword/default.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/list/fold_left.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS_DEFAULT_OP_(s, \
        default_count, param_traits) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_DEFAULT(param_traits)), \
        BOOST_PP_TUPLE_REM(1) \
    , \
        BOOST_PP_INC \
    )(default_count)

// Precondition: params is a pp-list which is not nil.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS_DEFAULT_COUNT_(params) \
    BOOST_PP_LIST_FOLD_LEFT( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS_DEFAULT_OP_, \
            0 /* start with defaults_count to 0 */, params)

// PUBLIC //

// Expand: pp-list of param-traits (no bound variables).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_PARAMS, decl_traits)

// Expand: number of parameters with default values (0 if no default).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS_DEFAULT_COUNT( \
        decl_traits) \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits)), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS_DEFAULT_COUNT_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    )(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits))

#endif // #include guard


/* decl_params.hpp
vnUyuUVncfLmiNk4xZzCXJhHbhTYuaOc0lMiJ6B2X617F22ZetjnCqK+VzCe+0y5gPKdJ311dBeymrKpLqZ/gM3R18Ic2/6ZE4P1pcP3c7XvKpRyxJz+lChIka4wpYfseHXOkLuPJacu60WMn4/KVbLaUOvWpSpB07mD+PjP7enyvYmJ2v7RETEzGVPUAaKTCSUf5B2ZwpHdrSqy4LnTSUH7Rq/GFqol2daxVhvFuvXPWfkVS6SOWAw9asBoVh67YkYD5P3N1Bu06QLcZBi+NMijTZTg8OWLVLciRY+MS7pvUE5hySHxRGFsufuz8eeznDySz12+MlIz+r80TYKBWJcLB0qHbA5b3mqD1aQFXQE4m+YXbPbT2pI+HENsOR79bPp4ds8JURR8MR6yAxyTZYubd0kiPpIPC7nlvGY/I7/dRsjAhnw75QZ4YkvvB1Uux1EZux7g8dY7Crcy2SJl/F7sooxRjKP+fD62tE/UNiNb/EeLOBXDjgJVn/hvrGXu30RegBVyfpCr6EvF1ibZdk3tirWCqhluS64t7CoCOcwAYghZfm+qjbhubunCrUoBt6yeI4GV/Gnp3kLO/PJvJ/fSqGU+WwyFlJYXeK2wW52peaMiOYjYKezIb/mr3AvPS+7FGrktkEU9jvYeYDKPuu9M5KxcxVmyCqPI+fCccS65/rAxvhEFdy4Iha9DgXiwhXuARESrbQmm9Wcc
*/