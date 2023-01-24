
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
wFFGWdnPhzct6EGvwgfUunvB29Be3Kodh6fTUXCW3GeqwQPLhkbIYygR/uBgJHIIWp/rT0dxao9QTErYdmCdexVJiCzqrM9MTy+BQFpqMzp6evp/mVXWWp5adPd4dU7fSb4eY7GE+6degm1KT2lqPdNKaTNvxx/VThCHMN9ujvhC3uQ0Aebs6m9ZYUwPK8MHCnvDaHvhrnuc06P3906NsnWAmiq50Ne9wT5PrQRxp88oZqCVjB+K7UVjugUZvw+4+Msy2BBCfi5X08nJxHkCWiOtA5OyVs0fMm43Hpy+8orb5FdzmA0tN7qvLzcwy2Mwi0jx9pVP0Z2vDt0h/Q8vOiZOIMhnZREktNrOzdfKz4HVSSaG2R8qf3XLFv4zKNdcMq2hYBEthjK47m4Wx+RU9xvG2pzXkjpgKWXKNN3TR0tBNcFoXVg79cOr3KGmr4vZURa4sF9nWThXR69tEH79KCgUXtlZcp/YnSXDKwo9y2Yes6GD0YsB9/foKS5uByEQ57IyWYgbghjmCsfISnMCJX/0XO/09c7eM299mPF7w9CzRzWTuewfKZRgaLLpSPbNbTEQ6BlEPvR38nbMwOQTngKE7Soyt5XNYdodL/eLCU/U9q9WyQo4LGr/Gh3UUa4/tXTS8JTwcarV+XX/k59Gp6c76yjw9jC749MqiMhtDDjm43sjcVovL82DlOpaWxMB46WNNGSMpVW832XH
*/