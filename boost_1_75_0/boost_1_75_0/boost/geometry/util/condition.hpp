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
tAcinGARhzPdAJvAk4CTwNaXvPFX2FkXncTlqK3xa1i6ga0oDhhLKK3voHaF5H2CAYKBnQG3fehGNHVvVk4n20l7q/sAfd19vn08Ozl9nX/Fc7ji9gM1uwT7hf1OJ2Y0ILLDHTUO5SkQtQ/2AiMQNqMURilkG52BOjyWv0p4N/JnKYPRqwEa1KT9UkGy6JgQIXMXvvdErS93lWGfRTZ340X6MooSLtqI6+m3vaEAlF7uYy5UmiLNVjOJlwymqcTkn6d1AKXGQ9SHMwnh29GvxGhqREfD5XFIfhOZU5Lihk3Gcy+QE0fEUNEImlV6w1erGP7gCKv++cPpSP8QpDJAgoalSUumXoXDX1Iw8PGIK2hfkX/ConTz4Tb3d/JVwfDTxqjsOXpje2DAhy9c+14vE8pTmDwm1SRZ0z91xMzUVZSecg2PcHypfCF1V4U/+5XrPZpgWPSM9CQRBy5aYSqLj6aVb0caM8wreztBmS+xUwgemBCfDUvfxQ3W55jADBMKPPKYSU/GekN+o5v0tXGEiKe9UOTiI/sPPmob/cC3KK9/Mn9+H0VURWVxvDJW/qHORM+ZVWgWLzaaWFV5EsLBOvBOv8bAWRxvwGihNpnIznK9e/ns7LIt1I0XakVufdvSEbam470WKnR+eAiwe8rs9u6aktWNtDL4lCKIT8QjrjL26LiSLMJjywFm6ICbBsbzEnxJT6qemlJ4auHh
*/