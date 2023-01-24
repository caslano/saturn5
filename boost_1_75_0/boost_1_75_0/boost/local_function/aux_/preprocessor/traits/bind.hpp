
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
MG/BljV8yNtxH4/i5j9/EHJEgl/5qufzJYEZgWHtzGn3wXzKwKlxzh6hD2g0XMBUwX9SdUiEFDJ+VOs5dZtupeZxRVachOnmPRKb/7uaV++kPrM0nXTJYAWZFoTD8hJtzAE54TL0MVUOTzcDzNisIisIGA7+9Siqx6A0oPvRQ60vsWsdJAqdjDm467ojHVQVkJbJpf8ppGDoC/P8n+ySA/wGNClHyIEz4Ozsxezi7+ddXQrTucRGyaFZM6UrBnfp6/zWOtsmUWv1i2bc4fm488GMw+tzC767AfpqXmZmh9d7kg8fSquylOp6mpt5sS0oyC+ihguQkWZImXnU3JcbT3qj0FOyULtMB2tfSEn+QtpVBsUVJOEQCAQI7h4I7oTgHiS4HpDg7m6Lu0Nwd4K7BffgsMDivrg7LA67x8mfqzr5cVVT9WqqXr2Z7v66p3v6VTcxa84hOsVR+vR6e2d+GZLDIQT3q/nuqvJCWd7kOhhHEMmag/R6J+JTREGXeF2wsQQH5+9MdqqmdOk0vsbBx6qAQpbMpLeJnchDTgk6zlTC01jNYR9anZTVehw+NKZMk1JmWqNHhBbrCrg9rbx0ka/fiqopjZ1lKwi1a2csez2zCDQ/ZQAQfcgU9OzFcYLan23cS+pIqEaEwxp9b5OWVrBi/2Sk7zy1GXaLpRmpuDIs9YW1BZq3bmMVLEQrTn2u+cm8Y2VKUJ38DrCX
*/