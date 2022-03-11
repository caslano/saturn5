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
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
*/