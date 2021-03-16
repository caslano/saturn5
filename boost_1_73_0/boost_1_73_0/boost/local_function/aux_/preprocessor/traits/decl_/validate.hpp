
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/validate_/this_count.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_/validate_/return_count.hpp>

// PUBLIC //

// Validate params after they have been parsed.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE(decl_traits) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT( \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_RETURN_COUNT( \
        decl_traits \
    ))

#endif // #include guard


/* validate.hpp
jdckyPmdCuOQJ4CruE2PBYVzzrFAxSJIx8sBvo7m7PHuFBokbQ2HcRf2Bp2CbPAu4QBFstgWShblBnHWokzL1wp+gcalelCZHD+iU6UROpU0jpze1QbVrNRhBbU7tNuB/qZwtSUOVas81RZ6i7shwqDbVDtT4Z7t4sct1IhGYYkUjSjPA83bjYHncbUnlC7lggI0FYpwrdIx6DTK2EqykukXFjSAdHugdVX9upT0kFVkZTpTwL7R1FAguHMrK4Y=
*/