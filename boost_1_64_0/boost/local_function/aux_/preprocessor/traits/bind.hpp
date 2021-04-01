
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
IRvibTWroXbuDfY+83ieNaGdaHevAJtSn9F2a99I+akNjVCJ9y3NGFmsBa+hr2KKBGxj+KACNHncyeBMUWnXBLgYkvc0ZM+gVb1NA1/AGQNJp54x7fAuElgPWpLFfeBkuEjvBFUz9t7RtHd7K0N/Cd/1VA5QRBNLaC6N/qRlZDx2gOt4hxC76pO/QGljN3z2/dkW76nXl/E5cQaCsvIHZQgThpOdqFYz+ApoMly7hAIL8XVOS+B7KylWutwQ2OLc+H+IXX7J0rPsIDJxsQAtjOeJFAlabhDsrvbvIexTrShoGYYX9k3o051koNn33hR2n/M4Hon9IPRgD+p3CiPle/zLQ0fat3n53onfAv0ua99oWnXmEWc/oX+8iXb0+JkbfoUPilxtAK5al+R85jJDI9y5oflD+/C/KINGrzJVkSOO48OG08WVUj0z1E5GOby73jcu6aNihp05/UhW9o0gz3ItX2BkWXTuoXcX3BJO7YwzEW+5/Xvs1yKz0KQd68vgwVOmZ2BXEuo3fdIAT23rFXv6hTLgNpant5UGx7DdcpJOLkPFglOsA1y2nw==
*/