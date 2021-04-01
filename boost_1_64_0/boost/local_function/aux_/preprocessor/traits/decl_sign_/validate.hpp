
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_sign_/validate_/defaults.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_sign_/validate_/this.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_1_(sign, error) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(error(/* expand empty */)), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS \
    , \
        error BOOST_PP_TUPLE_EAT(1) \
    )(sign)

// PUBLIC //

// Validate params before starting to parse it.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE(sign) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_1_(sign, \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS(sign))

#endif // #include guard


/* validate.hpp
UwJjuvhz50+hRNa8GsQrixc3CLheoy2NTwF7RW4CyhV1Be6D0+wU69RWP7CvEJk35/XkTzwG76w1s3vcbmDCtNe1Uj1epC7EquyRw/twfLb6SyMJVrmZzBMxtFtQCzDxuDJDAezuSXcVh1VGrdx/honFXrTOQ9dazP3R6azqVYBsQuje8dBcrqEZkvd75xcfSouhqnl9NJuHC5hrADcNXFzSZgSfgJjq8EglgHsI6DuV4K+T3qxGq4mMOJnrtdjlgzaXwdDNFLDRY4GTlmRcyaIJb6pzkhcQcep2L73zEWzx8WrZnukNuoCazrQhZQ/FJEOZrkeK5lWRM83GAfSe+va2yrwtOfMfmtTwlVXnIZC8nf0rYdk2D6PaovQULunVl1JbX31C22cJ/5zhN3YmWMfBOxSYz5EYygoRBg4/e8wRTTb4OLJzP6XQs5GdNrA5gAB8MWY+da2ZIz5Ov7VYQ720PDLILfQEFkILbHCYRSc0mKLw3vImjZ4s37qpQxaC+0hcM+09femYQ6rVHCPXqjBhGOgwcgb1ABLe58hdwaM4dpwaBmQvA9p2/Q==
*/