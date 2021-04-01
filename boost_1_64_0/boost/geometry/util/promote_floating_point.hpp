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
q+XgjqQKGTZYbXeKUY/uafE8ApI3IXCltUWJQF7ntNOZoeqFFcazmxgE/ov35/XWOyUazRmrM3AKvK/n7x9vDDmYiQEwIPbV7F3ipLko8biGlrSB0xie7W/MSppllJwLgTAv3OZIdQc0jiHS5W8kKcxb6BgloU3UL18ZJrNf91pcpfDGRGOmkd+P+q40q4vwTuGXygMxKz7UXLmgNvWUGfX8Yzbzef6hirsQxlLvFm8CCCFgxB4CCkYbQujQjr1o0kirbbR/pdlAW9DJe4N+Yk8gcim/zuN6DopaCgC13BzZe1L1Dnmiz9X4u62C7jNpZ2xhMAjJbGy9m4sk9trB9k0newV8io03RFPbUYa3p/OleF3ExGa5WLvaQPhkolV1zqPx8UNV7ZV4PBVQBK9B7KGw4YMYBgwCh0QMQsG3DznMRFbyvRmbbzBkJyerfivnoC4jE1ZQ5jlydt3guHIUchS4qJXcXF+BSnmEgF2lU+QT1Pfhj4UHDIAvGS2mtuytiVeAZnYaFBSmaLPcpDoMEbCt9BZw/ShOGaApVv6U1Mf2h3L7/iS9Xkk+Fw==
*/