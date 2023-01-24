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
RlAk+TnLs1DwAVfkWRSzrujR3fPox+jEpMGzpgLYxcY83y43T+8bKJo0HhGNooON8A4RKJ/h67f8xqLIqJccUqn6S+SFD/yPdryeM18ZMu+4avFEsGI1/bvAnoLNLWo9MwHoy5UAAttGRgjGxIUgwVeUVxZIBjuUBwJNGjHs4GU++mg2i1bQGGtJqBXq/FRYd8C4XE2TAVN8HORL27k4Btz6AYtWySHh4C2L1u7NmSgT1PkYP0LTT6jHohrDhyDrWwv1ixGDIxHgoDZZI7H4jMAprkuruyzPtDn22FuXh1jmwiuHk6OaOR6e1J+Ppapug3pbEjH1lreGqQyOoRGoaEELHqcXZSVtTuQrK+yta+JYyiKij8Xw4AJCA7rFOMrdfk45Fmp0zvKGg7JHVlhpQUObIIVDxTeKI64B6hZC9YO3DP4Q4PW9pkMKp71pCe563i0EXSpmsWV04wrkKR+2JGoyuZ4YoQBHfyM+Myz/WUPkjjxQ/VNznHqinvCg3WvPByoEH5hXobkUNLRe5hJtPzt9pHNwBiE68Ru9Vfyigf6lRViprLA7r8skZugJm08crwRJ/N0SaFsEPqAdb3yiAzRi1HiEGEYD0Em+qxJSPtU9GEGO72I65hbbyvvHKxxD6KjgN5txjZ1NAvXLvI3qOkczA9IFEOGcRUW0dg5OUdUWIT3DiUbb3PbO4439VnAx/U85D1maI23FWTux
*/