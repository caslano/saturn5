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
eg1Qn9ZROvjBUPPexH3k40zMfW3sZ+c5+2yACeA9v2MbCQA01BNPUzhfuuy4gcnUkCbUh6AMvrg85QOGrundAbMdl3fNu9siENRL2ybJf5pxPwiI2w5QTXEmAFo0xR3vrZG5YoU2Lapl7hysOL5K8VF9ShcJDmIEG0pocqE6r4bdC5bE54ACLwHbJBlVGSuaKeJggBZ9GMEPNvQBskizUcLbZXA3nCAfG82koatJClv7QO61gS5e3gKffibamMigPlzayVbjlctTPyakq2Rb+WqfIF17GxdkEwDdQSW7x9gIjgheNthq6nXHwjx0eoyoFI4VwJWULXOA88HgVKGilKBUXpLC6bMoBAUjeWPxQC0NSOugKxxdM92yqmIxWsTlyH2eC1nCKFmQ8jacPT+NctZoLDUGZAv4/R/LTBgUZxDYh/0sudX0WvjRRd3/R5KpUK6JuQ12nRVythLwJdzWu2nXwA0mi8s1fS2n0JutM5kuC3wN0GqhoIptNbx417U1WDsKnd0kUs7dxUXatjwQsR7CrnROh4Ofjz9UutBI8JHpwFZBVXx1DPzaMMibwXDwIWgfDIDf0OSkUVhK6pZmZcbxxa/nw7Oo825I2gEeB/XV8bK81oOJUYU+RhGe1Z8A2SyInQYa2jQeFVW8
*/