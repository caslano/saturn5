// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_DISPATCH_TUPLE_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_DISPATCH_TUPLE_HPP

#include <boost/preprocessor/tuple/elem.hpp>

// Accessor macros for the input tuple to the dispatch macros.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_BASE_NAME(x)                       \
    BOOST_PP_TUPLE_ELEM(5, 0, x)
/**/

#define BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)                      \
    BOOST_PP_TUPLE_ELEM(5, 1, x)
/**/

#define BOOST_PARAMETER_FUNCTION_DISPATCH_IS_MEMBER(x)                       \
    BOOST_PP_TUPLE_ELEM(5, 2, x)
/**/

#define BOOST_PARAMETER_FUNCTION_DISPATCH_IS_CONST(x)                        \
    BOOST_PP_TUPLE_ELEM(5, 3, x)
/**/

#define BOOST_PARAMETER_FUNCTION_DISPATCH_TAG_NAMESPACE(x)                   \
    BOOST_PP_TUPLE_ELEM(5, 4, x)
/**/

#endif  // include guard


/* function_dispatch_tuple.hpp
vg5P0iwq3kOMzzGe30pcTb14akzm+zgm85N1nqfqPJ92oWucb7h5EZt3SfYNjm7u2Ez76hjrQVbrszhAzep81mVZvc+6LVtkWQ5GQzIjNO7b4PBMxgvkUKSe4o0HxM8Y/9By5r8JBp9j6LBnu3GOYx6tnKGPuZKznm7N2jhDXds5Q31WSZax+T1U8G067mrOthmZEWI9m0Fx46dx1mlYjLO4YUdy1mXYes66DeuwLDGYG0iY
*/