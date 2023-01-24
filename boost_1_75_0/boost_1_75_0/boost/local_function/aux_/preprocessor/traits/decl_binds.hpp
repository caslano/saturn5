
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
k/eGCIoHLDYv8VTxA1p0DRADFn3cOlm/sGQWP6mWMdmGgjlLVBkfYEYyxYytns77xulHXiXPxJ6AEhpUEEy+DPH4R8wcg9qtJtX6u65jCT3zZxa9kDvbniqrl4p4zmp/GtYwdVbVpzDbbNtWlaV7o9ZJxsJs1iK0aS2PZ0+Zb+LZ5rJnKi6yuOCyW+ui+uvkBF+iLoI1IWW2IQsnm5+VzkUO+7M9k1Qyc0HeBaOtVR98rHAxvOJqpLpkO9cT93WlhSuSgMnlq6XL35UURMnvcp2iK9iEmVLkPOTYU2nrgsCc8KRqoB9v1jYS8gve7PFA3WrhlOjvw4MJDoyxoUIYME4032rRwt+zv5KeIIWyqlElSXJqpmVXf5G0kin/rA9T9Gm1s9KPz1A0fWzx9nvEtw2Veoa8ucLD/dUHCkI69qKYm6KdPfz9Tv/mm4ofKVPT1z2MabGkJjGckot357de4eTFMy6IGmuRHKezgY5kEO0vgQ9n+NoHrJcqRsO4PaguQhjVUF8AirfO10bMMk8tyhTUrLEy01+yq3lKMvfy5Hqjfftv2Ah6UkslvpRkqI3UuRpnsoM/4cN9AT6gvKjAedNg6I/35UqDCnH3a4tFCimm/ECxhrHd/jHgYuYdKP5ziFSzwQALbsZ73anXeklH0/mOp07cZLJhtBl0+CNzsDCiDQr7IBmSx4hgK+Bu4L6Vc8bn8cO9D5MrgvHZ
*/