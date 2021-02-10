
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
MHHWmYO4qsVMu6NJMDwfRWf9ST8Khq/XT+Bh9+uZMLz89rJmsl5q65kww3zcrTi+ceCR0O2GNkJbgCZrOIHDhxeH1HDt2FtsuIff0lZ86JD21KIU0tj3GOvPpzcS3KhLjgzEfMalWaCoBmsa8mr4YRwMJ/0/qG8v+uNWuNb/im/I+APcsbzir+fFpH11zZ4675a1W/puk5QPR/V+g2Dn/cvLycV4dPXuwjmpT6ENfQ1xawGRwCC02XQW2meu9l2MqOUS2/v5jXm+cbrcPC2fd5dK0VLVsK3xBYjO+/bxw6bavtbl1MUok0Wz1ao0UIvlmGL2n4/bLXWp9pur7gC+WfIl4a59XSIH/wBQSwMECgAAAAgALWdKUjfrblCsAgAALQYAAB4ACQBjdXJsLW1hc3Rlci9zcmMvdG9vbF9jb252ZXJ0LmhVVAUAAbZIJGCtVF9v2jAQf8+nuMELoIx0fVq3ahoCtqJVpALaCqmSZZJL483Yke1AmfjwO4cU1q0de6gRsWPf74/PzjVFplLM4GLYGwwnrH89uWSzOL5k/Xh8M5zM2EXQpHWh8F8hUef1WgAdONpY9WfUqK8QV0Z/x8Q9H83YFnY/Qt1Rf0wkggNky9pwHLKFVgVhtcq5HzN2TOjOe/OPyCPvmB/S
*/