
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_AUTO_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_AUTO_HPP_

#include <boost/local_function/detail/preprocessor/keyword/facility/is.hpp>
#include <boost/local_function/detail/preprocessor/keyword/facility/add.hpp>
#include <boost/local_function/detail/preprocessor/keyword/facility/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_AUTO_IS_auto (1) /* unary */
#define auto_BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_AUTO_IS (1) /* unary */
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_AUTO_REMOVE_auto /* nothing */
#define auto_BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_AUTO_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_AUTO_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_AUTO_IS_)

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_AUTO_BACK(token) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_AUTO_IS)

// Remove.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_AUTO_REMOVE_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_AUTO_FRONT, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_AUTO_REMOVE_)

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_AUTO_REMOVE_BACK(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_AUTO_BACK, \
            _BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_AUTO_REMOVE)

// Add.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_AUTO_ADD_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_AUTO_FRONT, auto)

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_AUTO_ADD_BACK(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_AUTO_BACK, auto)

#endif // #include guard


/* auto.hpp
vueLvh8MAEuiCiNtErwDo4Pjs12N0poNIMC3FaxvjIfFBMWzjGzb0q4UN3F9oAQoRZ7MayrCSkIz27Hrr32Ncrls7ZwY/6CqRESBkqB3CrCW17668C5DAEz4dZVRhpiFXk3lt6dqvNylK5OogvGJJIl8j6loxhGA/JDiTDkeCLd00NAqonJTv3OEC9DHRQ/UHHeO813You7O1xv51DqtThOBm1heBBbODiv6ooePPbihUFSMSceJrfsCq4sYGQYk0PSeU1VkgT4a1mKWYPddmDTUIwuig6KWSypHal4v7uixsR2Jq83SYcSaVmNJJdsg2LgGZzbPnQ+jPQrZwIfIs7iwld2TFLGA3RLhCIVSnAJP9BjvYrm7bjuQEjwU2Dg3sw3B4uzHBC99iPNBODdBM4mJ+eUq48Y/NW/edGXpukBSULWNMOExWsAWunTKz0KgWAbNMbfzNVSSDQK2OKzNaUn9B8ZtmkVNPR2rGeqKYgTL04OyaFUaBtW8idP7vcNYpjXM7x+RAQlu9k894uypD9S4ttBkUpMP5MoptWPDS1Jb29hS/TLuzhub7g==
*/