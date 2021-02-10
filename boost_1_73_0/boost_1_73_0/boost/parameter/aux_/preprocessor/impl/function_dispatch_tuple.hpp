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
8dHxI0dn8LX+7ugMvnaPbv/1M9fo8LX+7gCIr90A26+d6MLX+rsDIL52Azw5bbsA4mv93QEQX7sBvjw6frV3kquxLF5GExC7rRK5CVElEqvIY3eR8rV0elCASosP3osq8oOZSwpKFVosqV7aA70qC0B4SeIr1EFBhWRFfefo8HBv51QD2HCzg9ZGobnd/R0XF8PXDrJ57lwlr5+7irqWPb4uLt69g8O9fCdgcdJruzSL96F/HqUBifR6vG8O9/+BGtuWkmCzvPVNGLwHHRcVZ1A9ehd+Sps+7wvA8VHEQBFw1GH8bou1LfpGjx25GdGrhz1Q9aNxJ7kIJh1Q9NBGKjcYYCLtk59Rxt0WlbdT2DAC6Oco+N3vv6MdEj+BEgKiiB4VWmp74sK/Jgg/A0HvHx3qUcih4Pa3mkiRAoRGKcjIXYsbl1rXdl75+PhRrDZXeTQ7b04OtivNZgu+krm50pTyVXX19OjoYLWGvbxCzY92XPjYm6a2CTIyVkheYj8TTILMZGZqS32YLdX4D3SbLHlDJb2zvvZAFP9AaEaQqNiCtt4nKIkxKkqTBBqVaBGw/uqjjd4N7V9knwEdEY2nqA3BDt+LPRCjE6lHTxNYW2iUSbmfQc9Q2O7zl/YwlxUKm6OgmzAiiWK9EVER
*/