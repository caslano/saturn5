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
S9iw9lpxk++mcQCEjT/7smUi331TjOfML0XoOEjiuqW5/FEZhO34xO4Kfgds8zgSCdJshCf99DwgP4mNFa2KccjnAu7YpBrI7XjJdlcLiPg6yhzddisqIivYxch4zfSJ2TIEY8O2I2U6hFB0cMlNOjV+7vlUmqvfGFy4v5WaChTZV8cJ32r1kfEK38wEondnAC6jXm4BIx4Y73zPByophkZB/Xd3ElCrbDIL6lmuZAleBZ0WVlJ5rxiW+VDGnce6MgmsithLv8clxcH7TcY1+FuL73MDxn4widQpixQHWj6EG/GyuqagmY2dY8wtTBqI8/o3Wa/5sjj0xXLhfADJ9yvp3IuzkJjdaQXVZSxxJ951/0FrEzDfWkwCkZvNHa3o22BOML9A3EKobhRXM+YiohdjdrxZYCcd2qW8iwvpZsevj7j3Hy2pmoruASl7C6fiYxMaVAtAa+n3BvVz07JyQEw8Z2tf4s2KAVJa07hQiTvOk7CsABnK0/dXwYKsB8TBXEvWFDDbpAkbqbwIgSAtV9lt/5GedD/ofU0VGeEaJ8PVMbGY3KQ3VSIm3w==
*/