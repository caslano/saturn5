// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IS_NULLARY_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IS_NULLARY_HPP

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
// From Paul Mensonides
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/detail/split.hpp>
#define BOOST_PARAMETER_IS_NULLARY(x) \
    BOOST_PP_SPLIT(1, BOOST_PARAMETER_IS_NULLARY_C x BOOST_PP_COMMA() 0)
/**/
#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#define BOOST_PARAMETER_IS_NULLARY_C() \
    ~, 1 BOOST_PP_RPAREN() \
    BOOST_PP_TUPLE_EAT(2) BOOST_PP_LPAREN() ~
/**/
#else
#include <boost/preprocessor/detail/is_nullary.hpp>
#define BOOST_PARAMETER_IS_NULLARY(x) BOOST_PP_IS_NULLARY(x)
/**/
#endif

#endif  // include guard


/* is_nullary.hpp
snyFpXxhpQxgLL0BB4faZ+eaeqhnOm6WKE4Meq1z0r6Nk2FYTnY+FhAz7b7/+UqKMKsza3CS5MfBtLWOQYXff7DKNhhwG4x27f8hW/woXnj3NV7sUEq+YSXKbJjRDjs8hG/CAAg12iavjicuVg/TQ4UgZbYyJPRePVsZxfyt8eZoBhNWIR3VSJNtXcoHBit9ZqrdrFDf/8xzS/Q4euSQ4rKdOTbJsPsDCARreY/sGw0RT9RLax8eudtXme+Z7XEIvaeKfu+Wyv3bPLJkJ29GO127a+e9P08U6nHyUz+LcJiHxjI3M6+Mj0jqrOJQjZ+vcB2OWJeWFRnPiOwMtPMaavrTAzTC3O3Wei37n8f1/q8iI3jn3+w6rqU51GfaSiK7T9grv2Voln17ZxY+pPf0n8ji+nhBgG7dRVtU66w0Pt4ZG58O8iu1zg6PROXv0sIqRWWJaWuHgWDYrN5xzMOzicLPNO/dqFqw9bByIKnYlKeOcXo1WJ7CSohamvpDtHeSuHBe6glad0ZAs9GZuBWS/kr7/izqlMcQjSoQKbOzhJYpHm3DioKYcvZ3Bg==
*/