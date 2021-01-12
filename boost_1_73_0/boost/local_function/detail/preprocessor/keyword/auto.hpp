
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
T8++J/hsYvfwwTCu6uPvjs+W/DYs8reXJt3Ju+TtKN6eDm6ldhN76R6sIymrUZMXf4s6tjebh//eoPKeVipvIhY7ErGExDu6NGWh49NVak/EZ+S9W8kweqPQ7kN4hldJ5bjrtcD9NKPeNk2t04F4dBn8R0q7VoH//MzHtasIQWkTG8hpPDnlB26H9J/QuGHeaf3VM6jm6o0teM+k8M3T1EXJSzN5+PR7Y1Ga2y+mjtpH0XiI
*/