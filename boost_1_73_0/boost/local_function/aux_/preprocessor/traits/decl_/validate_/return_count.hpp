
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
GNi4J7aHK75a6v+hdb6X+YoDIzZxrp6rIpWvylT1JdGiHX+fY6oKZnebgoa9vftUFUCIldcd7nRe6lQ1FstDSC6x07AkfVhp61YrwE12s/XPtSTKZ7fchg4VyemKZGOVQr9BzXYt9XaNtVeQkNzK+Ko0Kg3tPX1VUTZ6aSKpPek23lv3TtN9q7FLZYz+LnV+G30fsh4NiHkrl6LkN+5zKgzl2pMKT5TY5UUzxbM/vVTv+89E
*/