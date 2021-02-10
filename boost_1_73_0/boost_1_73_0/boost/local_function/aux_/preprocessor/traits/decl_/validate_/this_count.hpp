
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/set_error.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_const_binds.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_binds.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/list/append.hpp>
#include <boost/preprocessor/list/size.hpp>

// PUBLIC //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT( \
        decl_traits) \
    BOOST_PP_IIF(BOOST_PP_GREATER(BOOST_PP_LIST_SIZE(BOOST_PP_LIST_APPEND( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                    decl_traits), \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES( \
                    decl_traits))), \
            1), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SET_ERROR \
    , /* do nothing (keeping previous error, if any) */ \
        decl_traits BOOST_PP_TUPLE_EAT(2) \
    )(decl_traits, /* trailing `EMPTY` because error might not be present */ \
            ERROR_cannot_bind_object_this_multiple_times BOOST_PP_EMPTY)

#endif // #include guard


/* this_count.hpp
uCxSFaMg9AMSBRLd3II0DriyxNbyXETmU+vgZ0NT6huAjFEZqHcm0J/UYc600C343J9+Gt1O4XNnPO4Mp19gdAWd4Rdi9nt/eImhFyhMAX9MFNcoXIFYJZHgQSbzr3vatX0R+1EacKgbKSNPc5Mmx2G9Vm680xvd1oZhHH+l5UXAF2jD8Oez2j5AQRUIzCdLs89jjCSSIqGIOfSGnQ+Dnte9HQ/uvJtxfzi9qrUPKfQgUwVyHUOiRGwWjSYGI/Yp7TRs6UaJ9bitltMXpYaC7+ys+Crg83SJy4CC7jlPXGJjog86k2mhNMrIDRr2phiPnjVpEdOK5w1H/+4NBt6g/6GLWLBPFZ+ZtLpHwe6v9/b0hPac0YXtYpHRBg3rK0QhBJl86XpyOZo04c0b2MuXPO/yt483N57XbBK7qqDGY2vThIZ9bzYaj44iU/PKG/2+pRstwBMqUQiFDw9SBAQDa/Kdx5WKZeOqP+jBIb5LpakcY23AD5mCw5iteLP2Rw1Ar4Xxw4Y90IQ/cr/1Ot1ub4L7PsN4uq/zGqmzyIKas61T6QcyPjAOfmyFao3BpsLzFWdY4T/p41lcb4GVe2H5zHHn/iI3Ixc77Fz3pqPRYDT8WAivrD2jAmGZS1SpNlYISqSixWSCSMbLV0of
*/