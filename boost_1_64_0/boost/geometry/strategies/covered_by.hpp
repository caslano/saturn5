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
3sU3x3Mh2AEni58rYdirBPUsio4d26Nae42jWruModwS3xrVVp3CsviQj7rROvGb/1NW7/b99v32/VL5JVpJqH+PpXZk8LAV1qnKh7fSDQqQblCALz/fsoU0ggIL6GIuh0UgLMRm0YqjayOs5C1vfD89eUN/7r5rptve7CLUAJcijzDGXqfssYBwhyR2p9KntjCl0KNUqFRSVctRshTatIGsWXANhGwPVp9sMr4odq4sY4MboZ0soeGnKmOaFqrKgHe2Je9YRqldRgf8IaXxCqsVHosPdzgTH55waewblUh3ZV2nOjryd91xvlU/gaMsFZUBUUzsfMJoMy626Ndv43N78Eu0tzcqSo0mMKkWmNAnazXG/YvfT2xF/2Ly/Ga2ZMBNMc+oii7+E4BWRjIhapXKxPoV0ghSr40PejaohqC3O5Sk2kTdZQ/vjw9P2B2bmFCZ2ASJfC2xh1+Lp3aggJmbXdVs8bEQZ+aZXIecY5RJo7Qvo3kMe1RsbaD5XW4hlMqSParHaPMlrEkxzy1DMzIVPyGTWmOQh4s46HePU9B+GBTioAEUBKLX63jPCGZP0rqWaGqP0at+3x2HdUzLTk/DfirwAghEWtvGX5qR3NDR5w8g+4wjWTO0I+3ZLmEblSwAqLVWCfrXgijGYvCj8TjDVt4i2prf9xB9a/th/qrPn3ZNv/RPcnwqEePTlDqlwOp8mBHkSOfDjEqOJOZvYuYfRRysQhspdEmOCjVPMCjLDpdTpMuinK+6eCfKRyZ+XEQKWdtaW7vYzE4Pn3SgwSr+yrZDtVj9VidncQnNker6cdQdwGoSbiUMU+Bk1YWOa8rZsHnsPgiC+xjjkSkOHUCyrDNiKMv6McqyCpQsq/sh6YZ/lcVeSXTE1ezwbRmSOEGEzAjFrNpIUaMN4VNkPC2u1SheErtMwlGTxbdkSOJ8cbQZoYrUZo3anoqstYsEH0kD6AbI196ztJYiFxfRqgc1ImxuwjCdLpvJqTuSDTuQ1P+xwuPxwdNPqSd8ZGwGexV167145RtyBvoKx1p67NUYS204VBVmzkP/UVYO9t5P+E8ybRMf9Ac1CdaYzpxxJdMxPX8UmAiDDjjSIUUxpSjgFNLbyn3wX0/LV0uVieIOGe0k5PmaQyGYu6yiaFGhQ9w4iiteIGBPcIYtho1XJYM2N47DHs/+pOmiSTaFdwTHtUOIXk4zIa9Sl1DqIXoKRlDI00rKIP/8C0QpJSpfuVEKcnO5Wco4vZRSp1IwBfaCDvhDNfeFYtV6JAGVfpGFs9lgubK1HL36lyh4I8BBdVwcdInR9V9sgrlfP40r234n56sADuG6ZeyWxgJ3Q1b0wkehwStkgyfNUS3b84ElSxwimxvLFaUDTUQQWUxsBJNs06+hdJ4C6V/IF33nPrYd1DyfM/mXPkp3UUA6bxsp4utqD5DJdhDXawvAsF8tkIujsyAO4SB7zh84eUv0WyJxSSwbvo6TX8KM2igB4oAqzM0ui4XZ6egEKB87J399G4oW1hMfloV98jAt7PanNX1sP1wo1s3PiI6HQsA8zgh4fGksoG3lVv+m27Zqm7+GTdEX0w6Ew1beF49Ly8eB6F8fphQN3kkbYJu2ZY2V0jYtcb0/+TdqEYSTg7EcT1st1J03vtodJ/G1thK+00IqLyqoxC6u7XRKX+mOA22P4K+/fIQoL6INaUEmrQeOfRvXA3/E9cB4tR7oghOivbKmTqzfyb9Orh9rGywQg8XsxJrdm+tcs3O26TX7ySd2zb7FK526P2LN9sNbdxNUzfxfrGa6qSp1U0Cblp9zSs8xzvZTLbT/+xYRRfcUVm1JG/fscE3N/0ZIkVh+cIjDoZMZgV4=
*/