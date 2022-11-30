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
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
*/