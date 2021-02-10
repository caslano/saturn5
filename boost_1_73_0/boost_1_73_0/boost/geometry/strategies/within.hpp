// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_WITHIN_HPP
#define BOOST_GEOMETRY_STRATEGIES_WITHIN_HPP

#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/tag_cast.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace within
{


namespace services
{

/*!
\brief Traits class binding a within determination strategy to a coordinate system
\ingroup within
\tparam GeometryContained geometry-type of input (possibly) contained type
\tparam GeometryContaining geometry-type of input (possibly) containing type
\tparam TagContained casted tag of (possibly) contained type
\tparam TagContaining casted tag of (possibly) containing type
\tparam CsTagContained tag of coordinate system of (possibly) contained type
\tparam CsTagContaining tag of coordinate system of (possibly) containing type
*/
template
<
    typename GeometryContained,
    typename GeometryContaining,
    typename TagContained = typename tag<GeometryContained>::type,
    typename TagContaining = typename tag<GeometryContaining>::type,
    typename CastedTagContained = typename tag_cast
                                    <
                                        typename tag<GeometryContained>::type,
                                        pointlike_tag, linear_tag, polygonal_tag, areal_tag
                                    >::type,
    typename CastedTagContaining = typename tag_cast
                                    <
                                        typename tag<GeometryContaining>::type,
                                        pointlike_tag, linear_tag, polygonal_tag, areal_tag
                                    >::type,
    typename CsTagContained = typename tag_cast
                                <
                                    typename cs_tag<typename point_type<GeometryContained>::type>::type,
                                    spherical_tag
                                >::type,
    typename CsTagContaining = typename tag_cast
                                <
                                    typename cs_tag<typename point_type<GeometryContaining>::type>::type,
                                    spherical_tag
                                >::type
>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THESE_TYPES
            , (types<GeometryContained, GeometryContaining>)
        );
};


} // namespace services


}} // namespace strategy::within


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_WITHIN_HPP


/* within.hpp
JGafj08+YuglCstBrBa5MCg8BzlfZFKkXubfdw07nZ+kSrIiFfCCojc2whaLwexF/YFZZPGa14aVyfM4yTWGYI6pg0GwSw1KI/WNWBuQHINr/syRY67MW+8vUOIqtph3cBtnhXiLcREKN5AX53GWsd/RaddM/KdAIeVVJxZ/FHGGa5aeO+KFNpI5M1WdOIsxp3KoOA87P6ViKpUIFvRkdN2HD+wCMtcvkzW9nuxHvet+P9h/RgSYulJdcVogEYrpcaG55M75S2kLExGq0uZCDPpcTsZiueFuYpZrpEIV7YDVwtwpEAhZEdoBu5VOPf+QAmXlHDlHnUfxaZOZ7Xe+d7Y8OIlgN8O/HP/Wow6SyGnPwvv3cPL111/7LMYFEuwI704GIVhIMfDudcT0OMPfdP/yhHlNdd4bjfrwnflkGv1G/kWCyvtg9w7Qkf0R06B0pngH+2GbU2nvoBRc142uSS7im1FF2+TttzkhTb4Aa1Slohk94tIhRczGCEZBDwxaeFjXDtZ7B84vo0pMWCJx1bIl6ur2CTNbht7777wu2z5mgjcjk+pm04iGarbplk4lT2RGlEE62AxSMPOvxcjt8iE62Boi79LnBMjr0IxP6f91yy4fn7oPHw/QQyY+EJ+sEfvnRadtQbYlOPUc
*/