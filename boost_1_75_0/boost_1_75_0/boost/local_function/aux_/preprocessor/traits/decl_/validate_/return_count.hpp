
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
EChyaJzyXPpFEki6k7W1tL6+/HchNZ0AHRcNl0zBuHKZbDJKgdSnOwGrYxTRV5gssBcXFn6T3GXApSH+yUCZr1VSoShbJqNYPXfIiIMTNXu0uvjdRyKY9ctfyNwZb+8dl6YK2uC9SORky6+uoyaKd3OSTU3I5ceXcgxWi0oFyTXxaZQiYuYsG6IH61c7gLg+LkkaZRPD4yzBm229BtKKstMVXJLErkVa6gUaXOZmOcttr2rQNz/n//G9k5Kj1f7ERGQkODQ0IDS0t7i4t3gvf28vPgV/kXWKxPlDgINbXlmZfMFo1HsSG9tTe8tDOwtB/R/quglqqrRs7O92NMjmFrLLaqrpJyfloiJVkRCoc/kSE5NsvpiYkHxgGBkZIbZtktKtVlmw4uIi5rKZs1LfKusJTMLV1oR/1TIhSUtFxfsFfc6hpfh4oNjV4UwtW9IIrX4unlP55x+A1ubmqnqn2oqK7oJrHTFH3eQyaiVjZsEpsFYqFhNn/7CL+R80xuQ9lzjGDXcji7QpA5D173daCpIdTVIVZUU8g2BKZUfguR0ewSvyfCmvNnpJNKsLg4N7wJhkaF663wlP5np7a2OFHN/e1vu/WaQLCSshvbX9Qszm6takqYEOcMupKW0BgcE6ZvzmzKVVrML6atkFGvtHCbKQR3cREV0DA9m/RD/2yxQIV7FzTOHWVCHYl5xmE7bL/igKr5ilQTxftDvm
*/