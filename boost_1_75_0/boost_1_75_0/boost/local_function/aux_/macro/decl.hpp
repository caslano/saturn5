
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
zT88Xtk9tcSe+4n9ufsh4a+JmbjQWpzCcS7QPsznYSzFqahVR2CUFWHMEC1UJ+wln6ptPPNK+ZVYIbwDKG/gBN8bu4VrOwj1m28LGOoYs/Xgm8t++fQl/XEJVdkkpXfk30oKG/vpSbLw88iScpSDXFrxLMvQbBmLHTaLZg50jkw+IbeaxY0LKXwvcp5LIVFXsqSVvkcuw3BL107FS4pIWPNpDY805OP43Cj15Jy8vCtm+zWgL/zXlI7uZnVMRbX/cA8MuQs8n0CJmejKuDuLlcbxfFyZHsfsyjiwKxvl2u37QfhbVVVJaiW3l3oOjuRawsKLpta1fvEPvoT8w32UW58vRmJzxdcw5HmaN7nxs8g3qSE9DT5lxQ+FTJYnHKel85Uce8nP90GOt4MT3Vp95zZ9H1ARpGgbyH4rfvALLKQum/lkbdDAyJmv49Sc4Lm2QX+9zsfE4+4eWi/IWSZbJMZF90fb/Y4bBKQgsyOXn5vIcMgxGFiFv+mp4TC2SrRVYHmdVY6w1dH5uKkSyqrfjbHVBZXj39Q7p1uZ590w3vND9NKGnAGkn04498drV3X1nfx5Qp7U4tJ1iwA2Saut/J+u+3nZPegpMN/ywfNUJIqWjFYJnb112lsn8XP0L3ahQyh7pakuusRcbe6kcaXnJBrNCFt8S7lnphZjBNyLprYOfXNRdi0uabjmB+fBE9BW5gJQklor1RXop6ND
*/