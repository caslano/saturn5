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
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
*/