
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_RETURN_COUNT_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_RETURN_COUNT_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/set_error.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_returns.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/list/size.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_RETURN_COUNT( \
        decl_traits) \
    BOOST_PP_IIF(BOOST_PP_GREATER(BOOST_PP_LIST_SIZE( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits)), 1), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SET_ERROR \
    , /* else do nothing (keeping previous error, if any) */ \
        decl_traits BOOST_PP_TUPLE_EAT(2) \
    )(decl_traits, /* trailing `EMPTY` because error might not be present */ \
            ERROR_cannot_specify_more_than_one_return_type BOOST_PP_EMPTY)

#endif // #include guard


/* return_count.hpp
z4ZRVdoeQg722vuK/eem2tD3HpUumHVLV/t4sskXa7w39QtQSwMECgAAAAgALWdKUg00Tc4QCAAANBMAAB0ACQBjdXJsLW1hc3Rlci9zcmMvdG9vbF9kaXJoaWUuY1VUBQABtkgkYK1XbXMaORL+zq9o49oYfNjY3krdrZ1sHcE4YReDD/DFqZCaEjOC0XkYzUkaY26T/37d0rzB2mV/2EnFzEitfu+nW+3Dv+6pwSG8+Hj2v4cP/toTN0r+h/vmaWrP+w7uH56a4e9LQtpQHvnuNeHlI9+hYY94mZR39O55LwmakW70p00nZx694goeo5NdmWyUWIYGGt0mnP7yyz/gCM5Ozk5acMliwSOYGB7PuVq24F1gV/4ZssfHY81/bQE3wKLjjNU0FBq0XJg1UxzwPRI+jzUPgGkIuPaVmOOHiMGEHBYi4tAd3XzpDz+2YB0KPyQmG5mCDmUaBRCyBw6K+1w8OB4JUwbkAo8j80BogwxTI2R8jLI5GK5WmniQeBZpCeyBiYjNURAzEBqT6PN2209VhNq3A+nrtp+bfxyaVWHJF1RixTYgEwNGQqp5C4iyBSsZiAX9okNwMUnnkdBhq9QGRcVBWyrQPIqIF54TXDu1OUwy97SIDBLUWBj60TLWJGodytUWIfqR
*/