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
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
*/