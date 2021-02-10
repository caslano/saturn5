
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
bsEDx19lXK0wDCZeeBkGe1tH0izZVJL+z+npoKxM1crpsg6qDFwBvCbzc8btYqooUxL6y1jS3dv36UoY8Bivgzb8do5gFj6NwnFCaRZVXE84br2GDm0cnVIVuTtFVccG3r2x9psn+Pz97UmTbialYW7mJ8Bw4729t1QWe3f9ybTZrBTtzvUiH7aeABPY7YyfxwiTXm88Ho1LGjd4kWOW3PZLupBHUialnc55P6pQDAVgnLkWVNttYDsKPdPdakVzc7pe4PT3f1BLAwQKAAAACAAtZ0pSOAU9ZjQCAADEBAAAHQAJAGN1cmwtbWFzdGVyL3NyYy90b29sX2RpcmhpZS5oVVQFAAG2SCRgrVRda9swFH33rzgkL23w4q5P61bGQpIuYSUpSUoJFIRiXVcajmUkuW2gP75XbroyWJeXytiSpXs+dITdNUWlqMBkPBiNF2J4vbgUq/n8Uoymi8l0LCZJl5dNRf+pyHof1xL0cLCJ9hbcuG8RV87+pjz8u1qIJ7xcjLrl/pBIhjfIkzjGYcgTjlqI2Kucx7EQh4Ruo7f4yCLyVsQhzzAsIoe23jlzpwOOhsf4fHb2BZ9wenJ6kmIkK0MlloGqDbm7FOeqnfmh5eNj39P3FBQgy/6eaqWNh7dFeJCOwOPS5FR5
*/