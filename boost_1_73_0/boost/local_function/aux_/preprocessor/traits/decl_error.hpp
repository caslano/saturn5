
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand: `[ERROR_message_text] EMPTY`, EMPTY iff no pp-parsing error.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_ERROR, decl_traits)

// Expand: `[ERROR_message_text]`, EMPTY iff no pp-parsing error.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_MSG(decl_traits) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    (/* expand EMPTY */)

#endif // #include guard


/* decl_error.hpp
OfhbTvSPY6J/hRN9Dif67MREH9QTvV9P9Dfd8HfM7jMElSaHGZIcFAbu3vFPt4ZIThDk+CW0Gzn1Uvh74AQ1Lf47fPgLwBW+0SjbMCxD+OvDX79efP4e4oQ+2Y8Ak1ky/cklMxhVROUgbrAsjMmoHERJqYY5K5lVzFJdt+ra1hlcUBP1nLqgsmA5UrDsZCWzYH4WLBsFysFfP/4Gr1tlFtZ5f2fhEvvRWJFmGky74zo8e3fl
*/