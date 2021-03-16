
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/bind.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/list/transform.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_APPLY_( \
        d, bind_macro, bind_traits) \
    bind_macro(bind_traits)

// PUBLIC //

// Expand: pp-list of const bind-traits.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_CONST_BINDS, \
            decl_traits)

// Expand: pp-list of const bind-this-traits (size <= 1 after validation).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM( \
          BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX \
        , BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_CONST_BIND_THIS_TYPES \
        , decl_traits \
    )

#endif // #include guard


/* decl_const_binds.hpp
xWirp1OZ6ESULuJJ0o2vjXXfuQHago3XynLvw9Yoz4lKr6p0EQpc23dU3zvQu7W1zDDttno62bWlXql3b1LKmV8rDL6TlorluygPV7slli8TW+LRTm0PVjpb4on9lf/O3rWAN1Vl651HKw8d2kIREcfAFCiCWGgpBVHSNpUWQ1v7gALV0KYpjfQRmhbKQzlYQJgAouMDcXxdUVHwquCVCoq9igLKCOrI6Mw4gowoU+bqRWT4hJFZa+1zTvZJTto=
*/