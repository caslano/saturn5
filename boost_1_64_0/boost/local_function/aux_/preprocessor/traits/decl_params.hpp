
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
a1uLnl0SF6bTiTgfuyRpIXXEP3yaKB6frwp6LxDM9ru9qzezwUDTqfQeMASi8PX22HqdH2bU4MMPwAUTJ60h2u84iiFFYqPXIp6co7hANpjvHxbcNrDjaHi+RDsP3aLBvrmVZS8UvoBzeF0qboRjbJZovtpwRaSd4rH8J4JPXYGibXa+I/+rlBm/RcFsccx4NOaaVQK6pjHfo2+nxzg559WTYhvtUT3tA+kl9vBc627T6cx3uJcK9o/TeGhFbOTTuYazRiPNwj7rd2fla67jvJL82hH+mCGWj2r8ZVZ8arSho630HwKspZTWLtJAYd735VN/qY6sSCRt9OsoXYuLeicQEPqbiLY+Dx/5KUL1Z7rGunG2r+hb6LwhxAvEv9V8m/Y++u1D52RC1Fn3KFA21qkj/7Y31pif9o8no0uykYs8qS52HV63Db9qcSe0ZJ7qUEXqYV72ck2L0MUVLWf1nsvRYX/fnkUKuvB6FIP4kFcurIOOpQzL/BVNKlgZ1IL1rNJUTu7QA7lnRRpkUYzIJd1GEKgohIsCe4iLknx7Z+zzzGgfQyHdmcNrZQ==
*/