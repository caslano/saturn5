
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
jsSgpF4o0UHtf5Wgq14P2V/i0Mup7AqPm9H1oGSrEsSesvKky3Q9KOl0CliG0bPxr1u+rPUqWxlpgrEZHImPLGYnM9CJIgdJU7hf1YMC5UgEKz9dj5YyEbPtNdHDAtX1oLRI7BsN4h5QhFqbkfJ6ReDsJGmHwNAJIaCIuyHRxb+/6J/o4v/Sn9rvjJX9Tt6Tyf3Ocd+Z9zt6S4OJZ1E/1M66wZ+cBDsFqJ3Wt8lWAIJCZQUS
*/