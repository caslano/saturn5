
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_THIS_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_THIS_HPP_

#include <boost/local_function/detail/preprocessor/keyword/facility/is.hpp>
#include <boost/local_function/detail/preprocessor/keyword/facility/add.hpp>
#include <boost/local_function/detail/preprocessor/keyword/facility/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_THIS_IS_this (1) /* unary */
#define this_BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_THIS_IS (1) /* unary */
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_THIS_REMOVE_this /* nothing */
#define this_BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_THIS_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_THIS_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_THIS_IS_)

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_THIS_BACK(token) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_THIS_IS)

// Remove.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_THIS_REMOVE_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_THIS_FRONT, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_THIS_REMOVE_)

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_THIS_REMOVE_BACK(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_THIS_BACK, \
            _BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_THIS_REMOVE)

// Add.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_THIS_ADD_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_THIS_FRONT, this)

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_THIS_ADD_BACK(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_THIS_BACK, this)

#endif // #include guard


/* this.hpp
Nc6qNS42KzUuMys1ciBVTampal4TpOootdystPK6mcdbmVlf2PyBlLouCp0jTCHkL69bA6lGSi1U856N4rG0ZrZdzfsSUosodUrNM4P7cTul8FUo3u9ASC2l1Eg1b3I0h/c1MyekllEKL0J5K/dA6k5KPQapX1PqRUitodQutRyqM3T3/sgQPH1SLBP+PpH7eh9obaqaLb414AHvF78eiotZyXT/MmLZL1iU0mwCnFRYLxYbuw4+jI9jLM9Q7oE=
*/