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
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
*/