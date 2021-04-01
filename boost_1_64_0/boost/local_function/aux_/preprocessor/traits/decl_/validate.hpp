
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/validate_/this_count.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_/validate_/return_count.hpp>

// PUBLIC //

// Validate params after they have been parsed.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE(decl_traits) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT( \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_RETURN_COUNT( \
        decl_traits \
    ))

#endif // #include guard


/* validate.hpp
8EM0bb3cg6UWLIgoisveK0lquN/VP6ik/aj7WiYAC/g8LXYJuyh05yixbFV+BpFfOI+mPLyLJ9PigA/EwYdwLyAyuhpAO7fFINLJ9iAYrSNlI4KuBZWywhVEZ4SwAzURh8i4/OuKbnb3/01j8k01Eh8nYb01q81wkTBu22rYq8/Zns1391Ph2BqTlFfU4HiEuCgkTKzM8wphDGV+NE2XO7+AlsfGsntuLaCBxd2IVmzKjGeh3xuNEUwrb6ibpaTrqPkfuGZlcWnJbijJf58KdjJN83K3rmI3Djo0kLZYSRqRODtCSET+nqQ/xHxcMDze4yWYVa4Gw0AbF12wpPQItVftteY8XEezwZwtLUkRRCvqCxq5NFxqgm9yp+0Ak9kuqnghTitITvfbZDwYtS5YO8VUY5CbOPQCXZfGWe4UPppzZv2cDYTx9I5MOfu/TqWxy9vIBNMhT9+NGHGo2vMpZG/V1Xzirjxws7RAzx92v4pdWOX53BhWTUccIOar8HGJ4ZwGuEnrRrZ6T1YrWPhnGvYqGxrUHMjkkpCjFkyRMmchDz5to1euNjcYtA==
*/