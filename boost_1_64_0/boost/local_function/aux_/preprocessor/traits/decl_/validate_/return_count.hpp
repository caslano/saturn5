
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
wDSFQA4+8HnZuTJ7Gj0n7ABYmLI08BTMZ/z2PfWNnIsWCZfL3gvi/yCCclaDEv7wyNnjpPgF2ENQ+c8E49CwHeYn+MnKSiY9huESSSYrRXhquagYQhv8mWYOy8dgHEuLxvtuyA0luXWReQl7b3NwS+hUydH14Ja6KUbc2ZMHcZtutXK+8jfZdirPWCaosaJL30p61Qs5hVzXhAjKMmHtdcVWlA1Ds0V2B+it/ld/gnOKr8OaDZzpRuqq72zBMDwzT0bBIp1GnrSPciay4v9fzbZ6WVDHC5y5rgOaTtUhAiW6RfKnqmLrCjx9qy5mimxE8KuRzdhZrFY4kCTbESMz+XRL8gjth2kAsUe2K7JNMIsKarQG2upsT4VAqXnKUyZTz/7PgUIKUAwLTd0ww2hbnKoFKRdjmxWpFxJef1GXyUy7cKzjj+GUCnN4L1mlruW8gKcJ8/g0WidbKP1ElrQ9k73CLRXzRvagRamc5qkAZMNLMgznvvPV66GK9GmGtMmnpXnerNgcDmok0aG2huwo7u9JiQhIv1ZrV9PyPK1+uHVqA/GJM+rJP1IKmw==
*/