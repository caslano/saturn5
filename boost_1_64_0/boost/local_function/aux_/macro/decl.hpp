
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_DECL_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_DECL_HPP_

#include <boost/local_function/aux_/macro/code_/result.hpp>
#include <boost/local_function/aux_/macro/code_/bind.hpp>
#include <boost/local_function/aux_/macro/code_/functor.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_error.hpp>
#include <boost/scope_exit.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_DECL_OK_(id, typename01, decl_traits) \
    BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT(id, typename01, decl_traits) \
    BOOST_LOCAL_FUNCTION_AUX_CODE_BIND(id, typename01, decl_traits) \
    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR(id, typename01, decl_traits) 

#define BOOST_LOCAL_FUNCTION_AUX_DECL_ERROR_(id, typename01, decl_traits) \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits)), \
        /* return specified, so no result type before this macro expansion */ \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        /* even if error, must declare result type to prevent additional */ \
        /* error due to result type appearing before this macro expansion */ \
        BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_DECL \
    )(id) \
    ; /* close eventual previous statements, otherwise it has no effect */ \
    BOOST_MPL_ASSERT_MSG(false, /* always fails (there's an error) */ \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_MSG(decl_traits), ())\
    ; /* must close ASSERT macro for eventual use within class scope */

// PUBLIC //

#define BOOST_LOCAL_FUNCTION_AUX_DECL_ARGS_VAR \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (args) )

// Undefine local function bound args global variable. Actual declaration of
// this variable is made using SFINAE mechanisms by each local function macro.
extern boost::scope_exit::detail::undeclared
        BOOST_LOCAL_FUNCTION_AUX_DECL_ARGS_VAR;

// sign_params: parsed parenthesized params.
#define BOOST_LOCAL_FUNCTION_AUX_DECL(id, typename01, decl_traits) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_MSG(decl_traits)), \
        BOOST_LOCAL_FUNCTION_AUX_DECL_OK_ \
    , \
        BOOST_LOCAL_FUNCTION_AUX_DECL_ERROR_ \
    )(id, typename01, decl_traits)

#endif // #include guard


/* decl.hpp
9vKE88/UXj6sXtH8r1db6ynkf73aWv/C3Xq4u/X//J9NYDo7QM3ZxMFgJHOdWuZ2ZB4pzrxOLeszXqb1mUjYBVaC3WBlY71I5ixgSQnHWC+SdRs7q8MSsIbJXxvx52vhb574mw8LwwUmfz1z8Lda/N0v/taY/MXl4G+2+LtT/N1l8peUg78V4m+l+LvX5G9uDv6miL+p4m+ayV9aDv7uFn9LxN9S03riFvFXU/yZ1xODxF8wDIIlYQgMgWVhKIyEpWANGGbSBzgr4QZJuOb1xD4SbgwsCvvCQNjP5F875N7/ePGfKP4niP+JJv8ROfjvKv67if/u4r+HyX8bs39366HiP0r8NzL5j8vB/wjxnyD+R4r/USb/c83+3elTiP9m4r+5yf+WHPy3Ff+3i/924r+9yX+GW/9Q/NcR/3XFfz1z/efgf7D4HyL+h4r/YZC9PF33WDH2V0lyv6dKrvupWOylYrWHSk77p+R57xTWGM17pfzhfVLc75HitD+K694oai0uibW01chB5BziX5O9UZBEZDVyArmIlK7lq7VBEpHVyAnkKhJRm71IanvW4zyX5/Jcnstz/X9ft+D7/xGx8YmJCQX0/f+/ymnGHOoG0bf8RfJyDXk7kDHKQTWnIImMjU9IsKcgVu1DoM6ZTGUsxTpHBdx/RHgfIxdKZvI0A4CzYrY0yDBT8omYf4qYzT+T+5ahmTwn9+eFnwu/EH6pmPtatmOe4KDN3fcJ7sbT7sbBf933CZ3UPMSwUt1/T1+woNGS9J9Wb7haLqngvk+49qHdPDZ96raEUxMPR4W/sfjg2281cfddwZ//PUN+v0/4q75DsJ5/KrjvE9TZRpo8k/KsZsj8yG7EMQ63syQsCkvBUFga1oRlYCNYFraB5WAMDIdjYAWYAiPhXbASvB9Who/CqnC/zL8cgdXhK7AGfAfWgmdhXXgB1oPXYAM45A/o1bqO8QbM93GnV/un6NRm6dP+cV3a2fN9/lR92i3zfQpMp/aP6tO60aX9j9ej/V/RoY2u4xmHey7P5bk8l+fyXH/FdavG/yMKaPz/tWn8X93HcYZlJstA+/i/5x6r8b9oYcn4P8CbvRl01uoI7wJyUfiNsJ+wr/Bb4XfC74WXhJeFPwgdcwNXXO5/lPufXMx/lvurLubXXO5/Md0PLpP5/1/F7LrwN2F/4e/CGy5haeGZ97rQJvSCZnfecj9A/PvIfSFhYaGv4S+7+IldbwmjiNwXtfDjL2Z9xG0xuQ9wE35xMQ8U9hB/QXIfLCwhLCkMEYYKSwlLC8uY4gtzibus3JcT9pQ4w+W+vLCCMEJYURgprCSsbAq/iktcVeW+mrCXxFVd7msIawprCWsL6wjrCusJ65viaeASZ0O5v00YJWwkbCxsIowWNhU2EzZ3CbeF3LcUthK2FrYR/s3FX1u5v13YTthe2EHY0cXfHXLfSdhZ2EXYVfH/ay5uppqL21e00OJnjgZffGBoqp50+JXanrm4/4e5uNPe8vsov5sZcC3ymrfzXFwILApDIaKVghVhaVgbloFNYBhsC8vCbjAcDoDl4QhYAU6EFeEMGAlXwEpwG6wC98Kq8EWZo3sPVoefwhrwG1gT6jp9GwyBdWAlWBfWhfVgW1gf9oMNYDxsCKfA2+BSGAVXw0bwMdgUHoDN4FHYAr4G/wbfg23hp/B2+A1sB6/C9tDfRr8DI2BnWAt2gY1hV9gOdoM9YHc4AvaA02AfOB/GwBWwL1wL+8GHYX+4Bw6Az8CB8BQcBM/BwfAqHAL9ef6HwggYD2vB4bAxHAH/BhNgDzgSjoCj4DQ4Gt4Dx8M1MBFuhRPgbjgR/h1Ogm/AJPgpnAx/gsmwiDc=
*/