
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
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
*/