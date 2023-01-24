
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SET_ERROR_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SET_ERROR_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_returns.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_params.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_const_binds.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_binds.hpp>

// PUBLIC //

// error: `[ERROR_message_text] EMPTY`, no ERROR_message_text if no error.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SET_ERROR(decl_traits, error) \
    ( /* return types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    , /* params and defaults */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
    , /* const-bind names */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    , /* const-bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                decl_traits) \
    , /* bind names */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    , /* bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    , /* error message (if any) */ \
        error \
    ) 

#endif // #include guard


/* set_error.hpp
lmu/46fz22e/rZdJJ7Pz+5sPZ82/VdqrgHSWAOAjXJ/NvUd6Dh+ns9vYvs0jj3LDEBnOzyqR6H23Y6QdwZE/8gsU/HSrSntw+o5prv6fSM3sKjfYnXcV0TmVPNJ0ldwDdJW+/6mWk15yjSA7aQsO1U1lr7XcqT/Gpjl5FG9cW1x9suVP9Vs5xmzWJvnYzVm4gKhTVOPcSvHzJ4G7ncYYgshJxuDaD5G0kaNeioN1165xjyjFkEpy5szBo16px+Ygea9a1k9hPvhqjbF3vGN8Dc3TPz2OCxXZ0XzFYBo3E3UTn9oRfxv0AiIvoUYkBzV5p3lkedl5bGLtvNFsWH1r8MtjhvMyd0FdiA+B6P7ogegB6M6EMH6UK3gy+Iegt6JDYnSidGIBeWp5M3kfldnpEXBRUOCz4UKCqHiBnja49MS48AkBRmJOyqRhlzI00u9Ug758ZKEnT3oji3AoKpNnooxCj5eEOO2ctq5SEvRZ1FwsPY9ZmZseKQl1FH43KJrUbLwQ8y8IjIjJ/rJiph9xSkn/AleOoB5QLsaVpwXiUyYrJZ/tMfTlmUfI3cGwnwjSEq3K41Z+9Z0698IGHdNNaWKe5xAeoqKwBPYWbt0g52V8Weu9DyXku6B6B4LPoR/fB/5fo6mopmAtrTBKyGWjf58k1v4KeXFnu9uxjyMXLb5Lf5+aFvK7eYk/6PXN4Q+8+uplt3eo4KsQ5o3v
*/