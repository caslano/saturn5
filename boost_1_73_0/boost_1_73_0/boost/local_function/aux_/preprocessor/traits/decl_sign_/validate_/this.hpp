
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_HPP_

#include <boost/local_function/detail/preprocessor/keyword/this.hpp>
#include <boost/local_function/detail/preprocessor/keyword/const.hpp>
#include <boost/local_function/detail/preprocessor/keyword/bind.hpp>
#include <boost/local_function/detail/preprocessor/keyword/const_bind.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/list/fold_left.hpp>

// PRIVATE //

#define \
BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_TYPED_EAT_(elem) \
    /* must be in separate macro to delay expansion */ \
    BOOST_PP_TUPLE_EAT(1) elem

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_TYPED_( \
        elem) \
    BOOST_PP_IIF(BOOST_PP_IS_UNARY(elem), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_TYPED_EAT_ \
    , \
        BOOST_PP_TUPLE_REM(1) \
    )(elem)

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_VAR_( \
        s, error, elem) \
    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_THIS_BACK( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_TYPED_( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_BIND_REMOVE_FRONT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_REMOVE_FRONT( \
                    elem)))), \
        ERROR_use_this_underscore_instead_of_this BOOST_PP_EMPTY \
    , \
        error \
    )

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_( \
        s, error, elem) \
    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_BIND_FRONT(elem), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_VAR_ \
    , BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_CONST_BIND_FRONT( \
            elem), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_VAR_ \
    , \
        error BOOST_PP_TUPLE_EAT(3) \
    ))(s, error, elem)

// PUBLIC //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS(sign) \
    BOOST_PP_LIST_FOLD_LEFT( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_, \
            BOOST_PP_EMPTY, sign)

#endif // #include guard


/* this.hpp
B7/U4zIK/ibtpLy1aX4T/B/0GsPvY4M0Rdblm1kTj3f5JgzqYqpRXuO1aT420Bhxw3+a2HNs4iU8gW7YsxOE95F7PUuE0amJvVevfhE7Yn93f68uji3flZ4YJtKfyOi6Ll479OR/ZtbdXSOWb+pCJsLyGgrUaObGIg6mya0VSQHXnmtLP5aOsGLhyNiO3AncuL5IZlJMXU+KTv/y01nvtC5uZ649QyD3wULEs2DhOWJm3UgRSVu6NwwjtKJEBFPoDsAdN04A4CJxA78BY0uRyGgeIwwc3vLiQFg3lutZExjISsQsScK41Wzai8gD7JtOYMdNW0+/MUvm6Uw+ARJz614EYSKSQCxiWRfYsi7mgeNO8RcIAg/DxcRz41k9wwaG8p1mEIlYeh7Cgn6ujBltKYaKPHVsJkLA2E3wJw78GIe6nQXzQkOgI0KZLiIfBgI6QCMnADLXxcJ3ZESNaeZ6CEVTIvDapcnwdUTgAzJisz0UZ8NNMbFiN66Lj2ejd/2rkfjYHgzavdEn0T8R7d4nBPb+rHcMS+/CYJGQd2EkYxg8Eu489FzpqDH/uL9m5SfXt72FI8VmEgSeGctkETZmmxV4MQXOmrq+dIyL4XF/CHL0LX3y8ax3sF8rtnrX/tA1z8/ennZ75ruaePas
*/