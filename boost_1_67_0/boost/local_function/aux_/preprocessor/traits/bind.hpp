
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_HPP_

#include <boost/preprocessor/tuple/elem.hpp>

// PRIVATE //

// Non-this bind is 2-tuple `(name_without_type, name_with_type)`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_INDEX_WITHOUT_TYPE_ 0
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_INDEX_WITH_TYPE_    1
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_INDEX_MAX_          2

// This bind is 1-typle `([type_] EMPTY)`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_THIS_TRAITS_INDEX_TYPE_    0
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_THIS_TRAITS_INDEX_MAX_     1

// PUBLIC //

// Expand: `[&] var_`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE(bind_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_INDEX_MAX_, \
            BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_INDEX_WITHOUT_TYPE_, \
            bind_traits)

// Expand: `[type_ [&] var_]` (EMPTY if no type_ specified).
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_VAR_WITH_TYPE(bind_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_INDEX_MAX_, \
            BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_INDEX_WITH_TYPE_, \
            bind_traits)(/* expand EMPTY */)

// Expand: `[type_]` (EMPTY if no type_ specified).
#define BOOST_LOCAL_FUNCTION_AUX_PP_BIND_TRAITS_THIS_TYPE(bind_this_traits) \
    BOOST_PP_TUPLE_ELEM( \
            BOOST_LOCAL_FUNCTION_AUX_PP_BIND_THIS_TRAITS_INDEX_MAX_, \
            BOOST_LOCAL_FUNCTION_AUX_PP_BIND_THIS_TRAITS_INDEX_TYPE_, \
            bind_this_traits)(/* expand EMPTY */)

#endif // #include guard


/* bind.hpp
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
*/