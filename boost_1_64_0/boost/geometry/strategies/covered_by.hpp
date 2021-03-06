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

#ifndef BOOST_GEOMETRY_STRATEGIES_COVERED_BY_HPP
#define BOOST_GEOMETRY_STRATEGIES_COVERED_BY_HPP

#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/tag_cast.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace covered_by
{


namespace services
{

/*!
\brief Traits class binding a covered_by determination strategy to a coordinate system
\ingroup covered_by
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


}} // namespace strategy::covered_by


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_COVERED_BY_HPP


/* covered_by.hpp
cyXicoNCnDPUCjrKDMOEOHCdfs83ICuI3e+IyiaO73HBEq45RLZaKxuL7PQ79UBkBX5emoZS7uCM73jwMu0LgYaEl0DipkG7k3UX2euqd++URBsaYqJbMRCNQRwaug0RWkbezOklKdtkokER0yrWWopGZMHx2tjcXjpGdQDh0+sWAPVep2V5Ehig0hPG6gUkKuDSUYUMIMTCXYLeQ55vFNAKoki2/6lUE+rlrs+DXWlwC0rAbOwdqTOftMGmdKoEF/vBZxVfUkfvvB659E8wxEdw7wcjBBCHQJUq+82fhHqTJxoJBAsJE7U8cl9xJG6Bog5+OirztKOeM/HXF5FTYJzRAVLrt9J6wIxuag5d3lfxLJFrvoyPouwf/NG06Eo95ua1ZrDD7ueB7tioo17tC0SaWrOUSe5KREpuumRQtrRa67V8lJ+37wrI9y2EyeSJkf4T2Aij+BrgbS1nf/1TNoMhWLQsVxs0l8+r5lmTVsZRK7RFYLMPkTgGaXJ0z958YaOSPPE/Tla5PkuVF1cyZOPUrFbBgw2xNk5+0XwKY6WnrZixouyJbkMofA==
*/