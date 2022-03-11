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
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
*/