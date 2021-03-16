// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_ARGUMENT_SPECS_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_ARGUMENT_SPECS_HPP

#include <boost/preprocessor/tuple/elem.hpp>

// Accessor macros for the argument specs tuple.
#define BOOST_PARAMETER_FN_ARG_QUALIFIER(x) BOOST_PP_TUPLE_ELEM(4, 0, x)
#define BOOST_PARAMETER_FN_ARG_KEYWORD(x) BOOST_PP_TUPLE_ELEM(4, 1, x)
#define BOOST_PARAMETER_FN_ARG_PRED(x) BOOST_PP_TUPLE_ELEM(4, 2, x)
#define BOOST_PARAMETER_FN_ARG_DEFAULT(x) BOOST_PP_TUPLE_ELEM(4, 3, x)

#include <boost/parameter/aux_/preprocessor/qualifier.hpp>

#define BOOST_PARAMETER_FN_ARG_NAME(x)                                       \
    BOOST_PARAMETER_UNQUALIFIED(BOOST_PARAMETER_FN_ARG_KEYWORD(x))
/**/

#endif  // include guard


/* argument_specs.hpp
Nnsdtu0sb9Qoa9vws3XWB/knfy8E518ljIzHh1tvHmSStViey6lXysAeWjPNtWJyEjzzZOpRz9OHIS9MzwCYj0LeNUf7aKHy0U9CZen4/f4z5fc1Yd67OHsmeOfsSwOntBmTLx1vvjZwzEkqi+OoonlE6bR/ggsv2/z19d+G3DX8SMgbp2RtZpBd6tiv7fK4srUTxtzLs7RNn9HjvWMFTqqxP6uxDQP3ygVx5wgn+7KD3mP/osYNVTZ2OqTg1Z4=
*/