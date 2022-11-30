// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_COVERED_BY_HPP
#define BOOST_GEOMETRY_STRATEGIES_COVERED_BY_HPP


#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/static_assert.hpp>
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
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for these types.",
        GeometryContained, GeometryContaining);
};


} // namespace services


}} // namespace strategy::covered_by


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_COVERED_BY_HPP


/* covered_by.hpp
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
*/