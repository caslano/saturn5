// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CONVERT_RING_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CONVERT_RING_HPP

#include <boost/mpl/assert.hpp>
#include <boost/range/algorithm/reverse.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/num_points.hpp>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template<typename Tag>
struct convert_ring
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_OR_NOT_YET_IMPLEMENTED_FOR_THIS_GEOMETRY_TAG
            , (types<Tag>)
        );
};

template<>
struct convert_ring<ring_tag>
{
    template<typename Destination, typename Source>
    static inline void apply(Destination& destination, Source const& source,
                bool append, bool reverse)
    {
        if (! append)
        {
            geometry::convert(source, destination);
            if (reverse)
            {
                boost::reverse(destination);
            }
        }
    }
};


template<>
struct convert_ring<polygon_tag>
{
    template<typename Destination, typename Source>
    static inline void apply(Destination& destination, Source const& source,
                bool append, bool reverse)
    {
        if (! append)
        {
            geometry::convert(source, exterior_ring(destination));
            if (reverse)
            {
                boost::reverse(exterior_ring(destination));
            }
        }
        else
        {
            // Avoid adding interior rings which are invalid
            // because of its number of points:
            std::size_t const min_num_points
                    = core_detail::closure::minimum_ring_size
                            <
                                geometry::closure<Destination>::value
                            >::value;

            if (geometry::num_points(source) >= min_num_points)
            {
                interior_rings(destination).resize(
                            interior_rings(destination).size() + 1);
                geometry::convert(source, interior_rings(destination).back());
                if (reverse)
                {
                    boost::reverse(interior_rings(destination).back());
                }
            }
        }
    }
};


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CONVERT_RING_HPP

/* convert_ring.hpp
ox3L4HILL4BnMIPwAIkthrpc8l9J/4PWVWbAFoR0SKZZ9FLoIPw/0+gENHr1qJClLqlSyTHS0zof/kmi2w5xL/3KgRbscaAfPe0k0ws9A/6XDGEj74x8Q+o5cq8DZYFr4HEAj0cl4H7Kwz8Cf43hPQn/2PA+0SUiV2AUcoWhhUOj60i6UFV0F8Tp3OdA/wPxCKRyl1W4krxLJOcP6QhpcX+234HGHQDKHeISaJJMSCqBuieaUGIDkeMk5U6ie75J0u2QJjsSkKPBNkg5uTl6em887ECJfQ70llZGhwR9qUI/jkKODawftbj5EG8+uMRjTgpNI8xoRAlbo5PpeUOSkdcX+W4vxD0NruUYy8Nos6B3ghctJfvTU+B5YQLbn45PoPvTRohvxxJ2MvyajslBeNX6EfmDb0JYorYBc8j6SHTQE2F9FCtNKQnQ30/A/nSI0jhMRozYOk1Ao6wjiXgV/ZkoH0cCPABc9QjABUTCwwkB/TzZBW1gJ/ygK7l2BKSz64+sPm++4EDjX2R+AotJnVwycp1LQq4uBblg/XPB2gX9TG2EbczkdN8O8PRlcvwvk9aRHrCZhckY345MDhNyHEVDIa2blezNIdP44W0JUBkpK6vb5bUMpn7Pi2J/ZPzXwfO1cd45/sSe/R1+NAyu+o7oOATHL4sTb2NMPPILxYl3OiYeEdbJh7IMVyZjfXqHeb85Jh8hThzSXxeG
*/