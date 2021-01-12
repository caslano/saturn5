
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/list/transform.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_APPLY_( \
        d, bind_macro, bind_traits) \
    bind_macro(bind_traits)

// PUBLIC //

// Expand: pp-list of non-const bind-traits.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_BINDS, decl_traits)

// Expand: pp-list non-const bind-this-traits (size <= 1 after validation).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_BIND_THIS_TYPES, \
            decl_traits)

#endif // #include guard


/* decl_binds.hpp
kmIN5bUd5cc6TgSyvPkx/D8z3xs7Gth1YsSyS8peA6PFlcvTT0jNyUfblcsv+l5X1whXmHg3Am9ge+MQViXjP7C8vwAjH5Pv+PjURJ5DHnttbfyWl//qc9bmm1FwjaYASFnFsScCu17M3tOSXfa8UFHWMh5rz5qhp36DKTnww32karhQdYP0mBf3lZ/2Lz+XtWHIG0BMwOUk8Ks9Kfz02VE47HFN4QTB+9W/m8Akbc0fXJ6F
*/