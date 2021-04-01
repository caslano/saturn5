
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
HBlU1pkMkyetf9v0Vya/XCKP3u3S04SjMQpDjnapVohXiDWFVhcFSi/9LinRbgWvDohbixijgG8sd04k5sFx2xLIl509oU5wnI3fTJv19kgN/VKxSDuVK+tXuG+PeHUevctahGE7efHO7Ph2Eb3cqy3S5ghX1ivZZvB0rPBb7G9Dh1SMl07+ZIkaEstvaFdyI0kx+XynnM3ZInUORZ9JwMdau1xGlYKgPRHx3rsdEQ9x36lYEbfuaiVO+45ajaIdmDU2QjG1TM4vrqXpNlH7+UTEkgh8ixcMtgMIhlcIN1iShBHwLUb4n5eK8E+05ILzPeOtAVAitBWYbotLs7yj77DzBjyXEiE9V8ssAop/3kvmopUKMVyezzWG4FBgQerqHIy+4D41Uo3CrODehNhJDVO1uXV+SqYCz0pn2O8PXAwaCjCG/PxPd+YMYZfIlDK1WH5vBhEqCc9tfnHXyN3xjxVctTIesga6QDQxM8sY5Y8Bsbuj8v+5QxFgK+OMrqqTOXERLKYyHSXQmERsWI7INSTXY6xsci53bElmm2EWgKHqeCORpj8Bu7vkVw==
*/