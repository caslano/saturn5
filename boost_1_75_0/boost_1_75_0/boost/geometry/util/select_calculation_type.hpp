// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_SELECT_CALCULATION_TYPE_HPP
#define BOOST_GEOMETRY_UTIL_SELECT_CALCULATION_TYPE_HPP


#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_void.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>


namespace boost { namespace geometry
{


/*!
    \brief Meta-function selecting the "calculation" type
    \details Based on two input geometry types, and an input calculation type,
        (which defaults to void in the calling function), this meta-function
        selects the most appropriate:
        - if calculation type is specified, that one is used,
        - if it is void, the most precise of the two points is used
    \ingroup utility
 */
template <typename Geometry1, typename Geometry2, typename CalculationType>
struct select_calculation_type
{
    typedef typename
        boost::mpl::if_
        <
            boost::is_void<CalculationType>,
            typename select_coordinate_type
                <
                    Geometry1,
                    Geometry2
                >::type,
            CalculationType
        >::type type;
};

// alternative version supporting more than 2 Geometries

template <typename CalculationType,
          typename Geometry1,
          typename Geometry2 = void,
          typename Geometry3 = void>
struct select_calculation_type_alt
{
    typedef typename
        boost::mpl::if_
        <
            boost::is_void<CalculationType>,
            typename select_coordinate_type
                <
                    Geometry1,
                    Geometry2,
                    Geometry3
                >::type,
            CalculationType
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_SELECT_CALCULATION_TYPE_HPP

/* select_calculation_type.hpp
MC54zq8Va2Eo6BglqKsZjDXer83xuB8Jz8mxk3Da6ZUMpV5ut/d4vLymf4rt7Lz/blTTGUoNnyLEdTw/Qr/PXXHf2quO6XLfWe8fVun2gj1a+g3tP+GIwlp+FqI13M9sAIGeuJh9VYPXlSex3+EKzpEEBRJlg5qaaVcVjO4Nrf3Lzvz383GgcLuWlYFA/CvpjOlpRlXgxuzB2wWeQ6JoNzfadpf8G9hcK9GN2jaWIIbguvaAY2hAS/9ffL5G+cRHKSq02ZPDlCRdgW/JtHTJlmG2YG1y9ZmcxJme3e2u8f20CL7KOJ0/5comLOea2huxlJIuhrW+uOx57CgOq+qGWhFh5e/ayELsKWqQC0npXLV+Nh76hFO7v+1qAbYm/c0pT3j0+b3biXF1kDJ94/p16bfj42cvYWOW+baX3+qoDXxxjlFzDSTYfakvS39mPh91d39DO8GafRkW13SjNs5QotN8JQXEgH7koMBWpUStZku4kZUztjTOqQT6kHqxy2I/QX78pfagV1wEwyM9K7isQu7pSm6L4S+hHNrQMUQopGl334ajv7W3ZiF9nKvEqWN4rBkbuAzt0HLOtJLZGr19rE3JZwu3F9kghN4PBD6WroTNSa3jngzhZL2/NS8KKXxR3yMz9DKaiqv7xPuuh2kahZWvgsVfBtv6yZ90C5P8RaZPzKX6lza7RzNJB+hzUdS3rwpitqU73+Rjfax+
*/