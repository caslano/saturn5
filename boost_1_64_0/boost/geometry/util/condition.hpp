// Boost.Geometry

// Copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_CONDITION_HPP
#define BOOST_GEOMETRY_UTIL_CONDITION_HPP


#include <boost/config.hpp>


// The macro defined in this file allows to suppress the MSVC
// compiler warning C4127: conditional expression is constant

#ifdef BOOST_MSVC

// NOTE: The code commented out below contains an alternative implementation
// of a macro using a free function. It was left here in case if in the future
// version of MSVC for the code currently used in the macro implementation
// the warning was generated.

//#ifndef DOXYGEN_NO_DETAIL
//namespace boost { namespace geometry { namespace detail {
//BOOST_FORCEINLINE bool condition(bool const b) { return b; }
//}}} // boost::geometry::detail
//#endif // DOXYGEN_NO_DETAIL
//#define BOOST_GEOMETRY_CONDITION(CONDITION) boost::geometry::detail::condition(CONDITION)

#define BOOST_GEOMETRY_CONDITION(CONDITION) ((void)0, (CONDITION))

#else

#define BOOST_GEOMETRY_CONDITION(CONDITION) (CONDITION)

#endif


#endif // BOOST_GEOMETRY_UTIL_CONDITION_HPP

/* condition.hpp
HQTE/eYlFZHeeCMYDRTyvBgPLE0FPwwg2yTEpTaskXhcBQRNcbWPzQ0SGyV3fbFM1LNsXyk6zgcXYzRViVwhZP1HYI5gJKMlMrLxdUtpn5VClYiMdwnJFSzYeFB5DQU0Z+L7zZjoE/tP2MKLEqwR71I3ZRYFewr41aFx5KvJ+dbIAI0+GG0EN2MoD3g5rKqfpQwkigqBsRFpB6+5BSr0eg9YQjDv14lXvZF3B13byyMm24oVkpMK7cjTx993lCr2alUXCovv+UEVGSz6LMksqU17fx4XfzVybp5x5IjJaJ9qNQPOIjvhEcyUtG+3YPlJtA/WPiZcoLWzDXjoVaQHop3TnInW1YQvVXPojFr/Amnr4lYGPl2nkUshekR4LYYq1G95ts3HwcFaZ8/xxDDCpdKzG+3tUmTk7A1FvOv5Vzcnmp7lbo/7To7QRmn0d+6eQHbl+8qYnmFF7wqUn7PbBaWZbpK8wMkx2qUUkGPCygE3se6D1lOkQ2EvG34DE8bAvHSSl/SqnJFcDZet7KGqq7VTWOit0GAtFKXd2knK5+CyIdYqooL5yqYUZw==
*/