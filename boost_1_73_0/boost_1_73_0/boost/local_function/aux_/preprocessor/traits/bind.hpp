
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
dGVyL3NyYy90b29sX2NmZ2FibGUuaFVUBQABtkgkYK0aa28bN/K7fwXR4NDE50ectodr1PZOcZTYqGMbloI2hwIEtUtJrFfLLcmVrF77329myN3lPmQHhyqIpR3ODMnhvLnP1CJP5YJdTMZvJ3f8/OPdFZ/d3Fzx83fvx2+uJvzi4BmMq1w+hnJ6+Nd9Dtghe/LD6T+HD3wTxa3Rv8rEDWNz/gfz/4DqF/h+apJT1pD8wV+wp0n+YM+JhIdZvsPfnD810S+4NvxzipS/cPwJECBDynNd7Ixarhx7fv6CnX377T/ZMXv18tXZEXsrciUzNnUyn0uzPGLfpQT590o8PJxY+cMRk46J7CSwmq2UZVYv3FYYyeB3phKZW5kyYVkqbWLUHB5UztxKsoXKJDu/uf10ef3+iG1XKlkhk50umV3pMkvZSmwkMzKRauN5FMI4phdADsxTZR0wLJ3S+QnMLZmTZm2RB04vMquZ2AiViTlMJBxbOVfY16enSWkyWP1pqhN7mlTbP1m5db2TT7CItdgxXTjmNCutPGKIecTWOlUL/AaBALAo55myq6NmNTBVnp5qw6zMMuQFdEpav2zJpkE8R4jGClixcvhldW5xqu1Kr1uIIEfksihNDhOBHAAp1SDmI1aCWRlCpp1X
*/