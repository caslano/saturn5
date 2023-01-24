// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_PROMOTE_FLOATING_POINT_HPP
#define BOOST_GEOMETRY_UTIL_PROMOTE_FLOATING_POINT_HPP


#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_integral.hpp>


namespace boost { namespace geometry
{


/*!
    \brief Meta-function converting, if necessary, to "a floating point" type
    \details
        - if input type is integer, type is double
        - else type is input type
    \ingroup utility
 */

template <typename T, typename PromoteIntegerTo = double>
struct promote_floating_point
{
    typedef typename
        boost::mpl::if_
        <
            boost::is_integral<T>,
            PromoteIntegerTo,
            T
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_PROMOTE_FLOATING_POINT_HPP

/* promote_floating_point.hpp
Td+TCNIIGo9Zk0B93gppnXKYOf6JJH5A2eg7ebHUqE1K1W3vWW0xzqO81/7cLcv6els+0JQYmDa9R99+oyx93v6pfWbg6uPE2kVS51cNlYecaRVoM899al9q9hnxs9Jd9tFk6tT2YxZ5duS+Amq2s1fVN6ShSIZGu0/aBA1uQeJyrJuGzEQ9PB0FblokOp9uDL6zpRinkJwN2hg5enOkdF8Y3BmED2NvVSa1c6ZOyntGKxJAiYcetRi0ZnplS9/Q+OAbvHtPtWdXMfsL5JafOT2R2tn0WgXYOnTy4vin3Jla0eeWEuSc2DNRSvIugvwoqQXzxf3M9LuSiCKNXeCHz/bUeqwDRUQOy+/GMljHW9t7GgNr4xhMQ7J+H36YzkIL76bLDUyKpaQhdBm6DuAaaWAuen3cMlGMpYi6QUjKukrTQshTd/gL58a0qEGhanKN+yh4tbnh6mqkRH7sGJmNKkPaBUVcYYvyOjBqyFwAWEmeY//2btbJIy457GGRtsumSN8xwab4fSOYP+uFNuKbSin9XGjisVFb7A6vHOgyOukdgtgBwismZ3kE5JW5AOFuffjbv4tkIVxt/jxn93j+YtIkjnXABPHg6DssYIi4bC5IotfqzhIqDXOGEQDJmP5oH1VDLhx2fKiYxsYFWY2KFx3pnqUGcuyVIJiez3hp0s+X5oy76CU76NSyPt8G8VWZN+HoY7nAr4/NNOWC
*/