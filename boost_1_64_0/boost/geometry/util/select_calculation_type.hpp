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
Mj7u33ikLkjWT9AZENatxSYBowEh1VWglFhtKBPVKB0SbprkBQqz/ojik7On01UeYJ1jfCnjs4tqBx66iaB+8XiELwk/U0lXGVszRNvQUTJ3o1Wpsx7UXXadhBe0JtlPS2rp2hbU3dwuCCYau4z1xPoHRxOXmExPxO2ws1BV8DVJhCSjThed1wTzKw+97CYncVq4jyd1eAqv9jVr9JISnrs2Bq510NrjrCaNC8kYuKsSb7SjR+ZqPr/jw0RL8/A2lhw9mo/60rQyDT3qurONQD0LIsZv23XeRdwPGdorHWzF41WQ6iQY8zq8cqXaQZ6SP7XaloMtN/SAdeOsu/nEom/LZ1MA3yj6RSE0zXXPVkVKIoxCevRJXY5i8uSrZg9DLzMdFDJXG5+8kkYNex7QUknSfpWn1BXI97IyaU7zvfkTsECWn33WhCHNAv0iKGMCiGJr9aUfGAtVGCxTLSfg2NxFwfR8PGLjLJdDa3PMDRQHOn8BGnbkbsAp+zeMLKkK0vwNS9xYPbCkm8o/84+PZfm+QD/OAiLl3qZAvRqu/8d/gsxuednDyyaA6g==
*/