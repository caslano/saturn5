
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_VOID_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_VOID_HPP_

#include <boost/local_function/detail/preprocessor/keyword/facility/is.hpp>
#include <boost/local_function/detail/preprocessor/keyword/facility/add.hpp>
#include <boost/local_function/detail/preprocessor/keyword/facility/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_VOID_IS_void (1) /* unary */
#define void_BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_VOID_IS (1) /* unary */
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_VOID_REMOVE_void /* nothing */
#define void_BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_VOID_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_VOID_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_VOID_IS_)

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_VOID_BACK(token) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_VOID_IS)

// Remove.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_VOID_REMOVE_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_VOID_FRONT, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_VOID_REMOVE_)

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_VOID_REMOVE_BACK(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_VOID_BACK, \
            _BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_VOID_REMOVE)

// Add.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_VOID_ADD_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_VOID_FRONT, void)

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_VOID_ADD_BACK(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_VOID_BACK, void)

#endif // #include guard


/* void.hpp
suCRrmwzRxiG7Rdog/hlk1vL8JVOuKBi3E2T6fiNlkdwXjOR4ZPYgDe1XPC6anZoMhr+uGdyKKKJT7WOur+htElvflRXRFqQBZzaUjQA+O1L/Qwq+BK5HTbQHfVzz8tLZAwPy/JyTOMUUXdEy73NM4qznE/IZQwbweTMnV+QdLj4uEzUUkv2hBoKSQHJyjQoXjwKa+Rax8YhjyYlcGVs+leGTKFF1W+xraCM2ftnFI5KnWSBhuu1mZqEappqPqMFNU8EcZMFOZJ27rSBPwvtoTFnjnBGREvZ8ichVohto9czw1rhsSx9AsE1w1NWyZAHaVkMgEm5mphNbRBdsWbnnBWu4iZUjtjdBbCMaLMuZjD3GQU8i2n+A/zoh2S7N2KcEFITkwBl7i6EkVeUI1aaOtANFluan8sNGiGI5RsBPjUbcemyHm8L28istkq+O3qHtUYYfdkKEyYfoy0gQQJvuiE3EBaeeTYnmYRsVY/dqdndd6T6jrqlHvdstwbl7QgUC9N4H8ynPhsodnepi3jnTDMxY9T1fBvPXun9Wjj7EoaCjr3o3CGYeAoxHw==
*/