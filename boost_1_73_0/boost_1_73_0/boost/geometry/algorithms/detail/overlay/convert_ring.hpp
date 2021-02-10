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
YsSkHK0qHH9n0SjbfYJCKVfAdu7lHnh+H37Mwi2wtMT8mnlpej1WB0F0gGcZq7AsHZhS/CwWBeGldOxUQlJEHody8KJYCvQJgGYBbdYzbeNZszwosKchA6PNMkXC1z1ruAcoCjmMse2N9xF05nnCSl75ANiGI4+FkwShxJgK5axA8GFNhbYq4AKAxddNMfFA9SN8ZZBLCvIHUzTHNFxsWo3ncx0QoB+ntSYD+CP/80LUalXoIyH8UT1gWYZnkvh+HevTSOiXXIHVGBHB80dwISfqILdlI9fMqWbYQyMqWqVo0TnGF/CY9iMjsD6tpsbQgalgQpJS4Qr7/H9DbMgKFIe0ugbCq3VIVdvyNlF7onTh9NoUPOSkRWXptnGaVbuHZkBYcS7GpLMqZHfsX3beyBtQv/DeKQ/ZcTcPYb1jKiZUQ9cMLxr5YUgvF6D//7C4oGUmqRKhz6wXDWfmrriSy2YzWHdaaoldX48gYiyiWlXOaZD5pRbxFIPfYFWbZot5MxjrLMEqhAuU3qOCCBJnC5GiXnggM6DR0MhK8iDLk2eS2I7RqfH0Eo+4dLqQCz+7Roc9izTj/mJryO2I7f0jMRfj25cwe6CFQsXSC/XgSmQgPSnXRntnjUW3h9/wTJM8Nf0onl9e8a7NSWk8
*/