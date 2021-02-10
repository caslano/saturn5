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
tG9v0CFeytmgw/wdOrzXFu0eLt8jQxIs2K1D2q5DuV+HX7JhhytvWEF6YeGJHtknOw/SFfTZ8zysYRPR9sWHeWTyZegeq6hCvuFRpF+M26SoGplUh3puoEqTECV8d1ZJuqyWFs7PahHJP1ROaiW32FrOgntq8JRZnwh3DJcrK51EqM6sBSRAaBKRn6SOhZCxsPS5GI9NkJemDWeXF9JBDRLUzXZAtJsAk4EtaxarMROdtcjkwXhpXsrV8GlVKSheklTK9kn5OSq4lXssgSbLwiP9igKli84ItICe3Qdo3lmBD/2lE0mURk21zs9yf4A11YueK0+yrFgkL6UQyo47HtMP9XCRsCsMkKjMZBe4/6Rv1AQY4vEeQawlAdPsARX3P5rimwl+3usMCvmc5F8h7vmt84FB7rtS03i+N51PVbW6ODEogrsPPD5DHZd+Hx75q8Z6TcfSivXmHI+xOMwLWGic5FZZ/TfQ+4BAr5Yx2RK1nNL34pKaki5MW/kwgIOvUbxmhJob6oTWKx55YLKyHTol3E/XEdkPUoo4qSKw87P3zkW70eu1XrWbOgmJPhs1PjbjzEd5lJP3+G3WeZCP3BbZV0ufbpVCFH+3jv1gembiSRxGj+Ko5xgP6Zdborp5IJf1oy02QrDeYj4z
*/