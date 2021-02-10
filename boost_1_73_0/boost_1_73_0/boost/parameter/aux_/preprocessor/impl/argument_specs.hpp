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
2xpFOUxnghlQfn6YdPj+iuos1RDFT6lbQ0dT2sb8K36kgQOyZEDtTCHg9c89kouBBXcoLSkVxvUEKbKEie+YkKPSMRWgAtU8AUG33VKpAs2oYl9H7o7d6WYxm9E5ozTpBuqNZZppqClAuQxWKOCUe+fQiHPDGdHUCu+fPHljzvGgsWWP/JkP2uxPQmzV/+NxM6c7rcI3P6Cx+nEi9ik6Ph+lR7pe6g+HfpOtwtU6aQC5+75Z5DUUj6ldNuHg7Gdv3w5N891zULEiSHCha13vBArCWOC0+ib5ruAxGXcebZnrtr3fos4oz2MzD1aanRNH5daPAD/NfTqhhqBrOJp1ylwRt6SpZ5AKitu21OWosk+qZC/7iVhW1tHuVARL9M0KZUrNqAafydQf5C0MlGz+DzEWSZcIooqpgxQHBunR+YU7i9yZ8JqLYkUMFPIsTaSU5abRtomIeL6gw9hWDPjkOLpQalxG0SDy5IJ2Do1xGsygRA4pTGpLdLLTKiabfXyEoRSmWkIkX024Ypp9P7nTL+RLZ5u899w2IkdUufEnb1JJmliWK++EjzSsyXMM8AhxEZX6AX4BJxH+dZxfpIEZOeUIG484rEeF1iLNb1HC9YWOAlRjURtMxWjCEyHN9oIlwJeFQnMKuzij9xpg
*/