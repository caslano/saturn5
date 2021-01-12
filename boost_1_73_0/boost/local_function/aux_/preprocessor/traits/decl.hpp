
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_sign_/sign.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_/nil.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/list/adt.hpp>

// PUBLIC //

// Expand: decl_traits (see DECL_TRAITS macros to inspect these traits).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS(declarations) \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_NIL(declarations), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_NIL \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN \
    )(declarations)

#endif // #include guard


/* decl.hpp
q/vf8vJa38r4vtsCa+MHm5cNkxv9by5PfyUwJr5P/N9aHtjT3D+wyx7BzzuX/RFRmRswC50cFt9nsJzHy/DHTn+x/paX10RXxh87vTZe+4dVb9vrNojHK8T9BfH4p4nr0eUjY/XAnLOnJQd5lLY8sso3/unAA3sPNe+LNY6P6wyfdGT41TPk+OnuOX71YLPKsB9SI5l8PLJ8aLf8xu8dvVflF/FWPr3SZ3LaBehSEOCopDul
*/