// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_STREAM_INFO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_STREAM_INFO_HPP


#include <string>

#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


    static inline std::string dir(int d)
    {
        return d == 0 ? "-" : (d == 1 ? "L" : d == -1 ? "R" : "#");
    }
    static inline std::string how_str(int h)
    {
        return h == 0 ? "-" : (h == 1 ? "A" : "D");
    }

    template <typename P, typename SR, typename O, typename C>
    std::ostream& operator<<(std::ostream &os, turn_info<P, SR, O, C> const& info)
    {
        os  << "\t"
            << " src " << info.seg_id.source_index
            << " seg " << info.seg_id.segment_index
            << " (// " << info.other_id.source_index
                << "." << info.other_id.segment_index << ")"
            << " how " << info.how
                << "[" << how_str(info.arrival)
                << " " << dir(info.direction)
                << (info.opposite ? " o" : "")
                << "]"
            << " sd "
                << dir(info.sides.template get<0,0>())
                << dir(info.sides.template get<0,1>())
                << dir(info.sides.template get<1,0>())
                << dir(info.sides.template get<1,1>())
            << " nxt seg " << info.travels_to_vertex_index
            << " , ip " << info.travels_to_ip_index
            << " , or " << info.next_ip_index
            << " frac " << info.fraction
            << info.visit_state;
        if (info.flagged)
        {
            os << " FLAGGED";
        }
        return os;
    }



}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_STREAM_INFO_HPP

/* stream_info.hpp
EebQ75FHIe9h+vOfOiwvwKxspy/8wsExqke9vnAqy+446+QiE73r5wAGYaqth3GpLISgXwsD7vItXW44BvB9kD9AexH0q8+QjQQ8SgIeR8CuN/QD4HPy/PRTNwBWCkB33uDv4eOz6sr6u6yS7A/6W2zbqyUfZf8pIO9z16IXWRD66gpUIsEQqPvfoRL+YcBXJw8CqEz0m4SJrJ/G+251ciumYaB1/1f5X/i5ZP29j1/9HOVZS88FylNBzxDlWUTPIOV5ip4c5bmfnlOUZy49/ZTnZnoGKM8kevoqz2X0dFKeMfT0UJ7h9Gz/THpOp6dBeU6m52fl6U3PD8rTjZ5vlSeFni+Vh2n1zcqzlZ5NyrOFng3K8y49q5VnJT13fyI9y+CBJdh3/oyX2OzFYkL12+5EPbawZlsk0MNMMUGlmCdTPG1J0ZYpVm0R4e7tsfDODH+ROS1VOY1iTgyh57f0/FV5sul5UnlOpCeACaJvzsW/E+BCdmuEuTKAqGn2fZdkW8sw/V/zUfo/eXL+XddAe35jUMf93P/71erj7yJWnPDgo+BA805WzYOg5fRBeANkcGeGKyOdwz517Lfd6v5X5o+FLEm9KbWjLZYxaoRj7UopC/xD/+5DLl/yrnW/+fWT+eHI+bcbIGqzNMAREMK337JOiTOx4v8QkR5HVxgr1uzKQPJGoT1fQhszsdU7YfnPyfTcxwYGtBJ5h+tiToKg1Ua6SG172NBQMjVTX+cmdTimFetWtxaVZNxEEbdQXkB/9R0m7XzTDOfH/2hRfzTlv/e6gyMWEf+1ZY0TI8vsEh5w3fdUVMXGP1dZ+t8YlPaZB4Z/uiB0TFnuI3/ZEwVx0VrJwYALks+3csTw349FDkbVMzco//W+vdGyXLxze517zhGCY5R84XHI9z4f7ODbAh/YIdo3t3jN+3ZbvrMm+olPm5lmV52s3HmRB8yggsitGdaBIIzHHucmvCUoNz0vcl664TEdXoR6DY905GvD0kSVX9rssCF0nBE9wXBcajiuMRwhwzHRqMEsS81KY+7cqYbjRiO22IjNa/tAkqg3f1BylYT48a28XgkjysK2vbQKcjpt/k+FEwAPES7nAcoK3tAafjpivYQYAAB6GKFpGc8HRyMw5jwENpyPcs/pJWMfi4vNlxxef9sxR/ojY45EdazBqK6/V+MYRwHZxaz6W5pL9O2uM/ZGZXi7uPDNMjxPQyrDNDm77/J5m/Bk3amb7LZcfIfjeza+Y/G9HN/f4zsV31n4zsP3fnz/hO/z+JYj3Qp828B9GL5H4Xsivl8hbCe+H8K9HN/RmHrX4HsLvo/g68F3IL6L8bX17NnT7nAmJbdq7WqT0rZdz/Y9xaeD29OxU2e6unQ9jD8JP90SBaZ2Twx8+BFH9ljzv/LRStqB9sSqVBu5g64m66m0/3m6XE9LKnc5lDzRqAulPFFC+H5N4ReNI3zi8vnknL/tMn+kpFEVYvT3B4MNWRQc9obAZGOIZPfvvlJPq3uwW91mF8S2b8nbTHDGeya5zWURtPCbF6Aq9NeNO2VvtLwToe7KIps4xNeMUlRePZnXXLtp73sd4ba9G8sNu9pkZCVFKhjKu32Fnr+YdhasjZdj73tuGdT4fc+5NuN9z4CT+9BGh/G+5zSxzWkT8aMv/sBBN7uf5546Xq39kRne8Y6IsDlFRFcRcb98a5LA/OjXAgZ+wvCzIuyiKwDLQrZQCi+/V+tf5/DZl3CNNAK/1M5kq953CFEp/cqNwpGqzxAOrZg12soa8fXRHe8Ih0f/SlYllbGlJ6OdqK+89rwTg6cf/Z6I3iyDZjOogwzyOEV9dZuq7+PIiJV6J0NksoAZtt0kQNM=
*/