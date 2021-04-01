
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
wLhlNo5gF2v1kqaI2zOQu0FlanOsY0j0ZmlG2kHra7BLjgR+KlGIBgk7KoIkRG3zQRzVx23+WwPYRpJglNsNvUiTq8Qj4XY9xVNiQgxWuB36+DH4hAOQYDpThw74Gpy7LHgQEYulxykpg0qfj6Gh5bjWkfQJns3EUZnRBcBnwx36Z2E2qXs+ji+r+jSqFiJCwxiD+UMdJo17hCrkH0edG+2bJwAmUx8oeRncw4BLlquLWV8F4A0kH7321TCd/nBKRANcsko67GPPkHbqkIys+2TBEGW5xTVv9NzrhlQKHgLb1TPuXAZKol9Y4/ti3Jp13PtFzJeD/MH/QH2l4c73ScUXfezTndqnQrqWeutF9vnh/rSn8LeV678xmGVFMPli0/nniE4zEjLsoVmx0ancK71SCm6fRi4PWNe2FbsszKYRT93wymAiJk02dWkm+HclnLPJiPciuWUPEY9A1Fr3izJZFZOEqN09+XXw1PAeq7eQ+k3jmj0Jtpqu9BbbaimAgO5HUmNWPYXZkS6v6b+/uT+tJKKRLv9BilvoMKb6EtgHjDH0gkYpbNUaTg==
*/