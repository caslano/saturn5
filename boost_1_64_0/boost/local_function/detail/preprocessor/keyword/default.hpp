
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_HPP_

#include <boost/local_function/detail/preprocessor/keyword/facility/is.hpp>
#include <boost/local_function/detail/preprocessor/keyword/facility/add.hpp>
#include <boost/local_function/detail/preprocessor/keyword/facility/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_IS_default (1)/* unary */
#define default_BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_IS (1)/* unary */
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_REMOVE_default/*nothing*/
#define default_BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_REMOVE/*nothing*/

// PUBLIC //

// Is.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_IS_)

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_BACK(token) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_IS)

// Remove.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_REMOVE_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_FRONT, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_REMOVE_)

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_REMOVE_BACK(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_BACK, \
            _BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_REMOVE)

// Add.

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_ADD_FRONT(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_FRONT, default)

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_DEFAULT_ADD_BACK(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_BACK, default)

#endif // #include guard


/* default.hpp
NfvQk6dbuiZiBV0Tuweae0EWkQJtK/lX1T0et6FAqo9LFU0uzztx2+EiY6Ty80t69WXPRBb9DsQqY34wEePrdu2hpTeWfM2xovuaUtQm5oCZbgsgzf3LU5sxDPBOB1Av6tEtuN1kIylbZM1iGAw4+cyC3KRD9i4is+PfpIsdjOwEdM51sT0USDLJffBgeOXiROEbfRLuE/y6uS2d6jDx7UI2IVixCiUpKs/RfFG++GWDGN+RmvxaUOQI3S2bBAltN9WIyPgj0pZ74CvdqPm40syPO7dwmpP94oP1fI1U0OLdIXqvBFpV4GILZMbqyxImRgybHvzP2SWYfMhCRaUO8UXMviHuxhtybHfe5h5Y3hyBI8Tj+k5O671VzX4XwiM71Z5BaTNiY9OXv5vJrZV4HJACpaYc4hyFOpHzy8cVBKHv3GXEAhH/Rj4LMzuEp2GnmQhRhEtVq9Q7cYLVx0CCILEFrVoUFxff0UVmRDj40pZ4JDq+1gSagaN1EU82ah0rPXTPtfmzXpWtt+BmSIfFNmgTNIldMiaeftmV5iciAq8XSeXo5aZGaksy3Q==
*/