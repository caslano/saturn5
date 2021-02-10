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
q85rFAP41EDfNdAb4b6M8xL+X7k442UwK3hugRLyv8XTsrgZBf3dZZfLiQYOJMmmMWC175SpgmdTaPruMmFaMEXqAUkZD2hoh+YLgMxJzdbNklm+CJYP38bJ5ZIu8VZRxmU6Ujd5Ola4L9FkkSQ7sLrlqFRygIgF1S7+AUgWpzzIZwlRmYaYArSQqJ1k/2ofUPIy+wjkksYVLSBJiyU0oBXAwgEBAs1aAK2JVBLMD4uAsvrHEjYhVpPkVl3elQnRefMpkJf4dO2rkxyfsymQ0kAKXiYjnEOZA4k3i6dT2Bns7DIe4zDZVQGN4Ot1PJ8nGVJauGUTddHtnPz07tWr7kU06P2tq/7ofnnb62/9TvH7GVZMCzuWeS8Pdrd21RUiEbnP0SSepdO7ndYWlhAxCf9fFkyOLoAaW2QeAlDcgBBDrK6AgM9M2T51co7ERQKEa/GC/n58/Vip92n2QQH/Icd0jCfNgLtQ8xxAAe4G1b6gIQtmJHgo3HhVwBYBTXCJRLWeSjoGDJ9OUmp7oAFjmRXpVUbsSFm7Vn6R62aye93a+veWUifdn9697gwG3YvhzjVAUPBl7yX3RCWyR+bj4dbnLdpoONxzPdMSWZV9NYAbPAMw2Vnky6tr6ACvyfOnz/4AezBfTuNFWt7x
*/