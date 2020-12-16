// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_SEGMENT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_SEGMENT_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_invalid_coordinate.hpp>
#include <boost/geometry/algorithms/dispatch/is_valid.hpp>


namespace boost { namespace geometry
{



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// A segment is a curve.
// A curve is simple if it does not pass through the same point twice,
// with the possible exception of its two endpoints
// A curve is 1-dimensional, hence we have to check is the two
// endpoints of the segment coincide, since in this case it is
// 0-dimensional.
//
// Reference: OGC 06-103r4 (6.1.6.1)
template <typename Segment>
struct is_valid<Segment, segment_tag>
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Segment const& segment, VisitPolicy& visitor, Strategy const&)
    {
        typedef typename Strategy::equals_point_point_strategy_type eq_pp_strategy_type;

        boost::ignore_unused(visitor);

        typename point_type<Segment>::type p[2];
        detail::assign_point_from_index<0>(segment, p[0]);
        detail::assign_point_from_index<1>(segment, p[1]);

        if (detail::is_valid::has_invalid_coordinate
                <
                    Segment
                >::apply(segment, visitor))
        {
            return false;
        }
        else if (! geometry::detail::equals::equals_point_point(
                        p[0], p[1], eq_pp_strategy_type()))
        {
            return visitor.template apply<no_failure>();
        }
        else
        {
            return
                visitor.template apply<failure_wrong_topological_dimension>();
        }
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_SEGMENT_HPP

/* segment.hpp
Zo9fUesw3vyzd1An/YnN1bSna498kd0l63SrxOkzyXcg/UPtMVlvHMB3av31XGDvcnRlLkNeNc9C8FwetHWaHn/O5P4S/Vyf1Z3N5mBSp4JyDHbVJr2YLa7e0FNP/U65zhR6eA3HGIx7XRNz4UKm0foc7ju8iD0ouOnp2/mS/OD8D/zmRTn7HOfPx9tGy0nxrT2ObXAdnG/Fv3GrJkvlGubYQyz5Tu7UV0+2qJ7pNPGj+h1irZr3pUflGHBymGNqwslHHlaTq6PunUWf9nmcCh+/VpvPHOBLtfEltc8B8oFGOM7LVZN7A8X3IepxcrHvjf1Nn0+AET1/EUvs4x3ZPgr/6Mdvj8CmxjinWkQ3dfo/EuqhS9jGWPU6OFN5uFwSlj3SRP32ejoYL852k/OjY82f0z8fguOLD5m/4/MF9YluwjdK6PmOwSOm418+yyt/momHj8UjJoiJx/Ud6uFNh8W8RWqzs+z/+l3dNU2uOHx+I78dxKdrqnFZ03vZ6mKf/15B/XGsWNJETQbX+6a2OuxRfZNPYGdffTA1qnzqxh3dvzNZWlT/KCv8SyMPSsN32NGlRuwbz67Ov75MK64ekwOJSVnYbz22dVEe1xkn7I2vdHsET2uMtzxI55PZ8q1sh68NvmQvnutPJ+/eI0cZIybAhXV00BcfSBTnbzlwianGqZ70p/Vcwy9WOH43fFzp5zjYXlP8SKmOJ29kN/fbV+fzRgXlBXCsCt0s8f8XyTKSPPcHdZU1zzmmsO/o+ld5U1U2WkEfr3oDewmWwsTTYl5vsSGVfcOce1Ltk6qEo+InTU/KcfKxkfVwvY96Bd3+2YP/4rjd8do5MO7MXP5dg55ywboWeMhH8GU6nSwQe9uIu3npdZ+8fDYMMaZs1/NDkvd6n5NZZF5S5LHF3CcjblPpkJxoHI7K9nKMVRM+j2vuo3exqm0/mFhCHB2ttzNC7mhP0OA9cH00OxCP+t/KN9n6bHXcZs3xZRhWgY1/4vqL4cnF1fjXcmN13NkyuE4Fc34LJ32V/6/QcxYLHysOLyrxvWTvux3cehlXFy97idlZDvAF431nhnU4zadbmq++0QNDcHc+n+Wo9T3LNkfj3Z9Zr9vpRr790gq6g0mncL68XfRn7M3JjffPx8ean8CplvBRmHquKh96OBEKb8GR76H39PTyqPVUV/2+DNxUmy+XnKsxHCOnyBnyNdlPPiFVTxk/uzghDlUeC5PG6+nm1t/8UFzri0920FMw/mED7cmiozbr8b0aOGwwfjWhz+DEQy1xl5vgMn332S020dHLegeX6HvJTtf+UD5fV82nDluwN6cIHbQcZa8CXlrmgpjVWWyCC48Ncf/kfoja4gN7HDPRutpXWL47PpUqDl5i4ym4Bz/c8JO1gDn3yiF6N5XbWru/D1JjM56CN7geKUaakhakNWlL2pNO5B5yL+lJ+pDGpBlpSVJIO9Lhf455gkwl08ks8gyZTxaQ58kSsowkOfOTZBqZ8e9j55C5/z52Gux+d6dYLE6MqI77TsOtzsGMxvINcbBAbfHkKdwsnfnxrT648U8zgrqJvQDJXv8muRGu2Uptv4ce31RxO9M1e6T1BXPMxDvPJMIvl+n6m8S/9ibkh2Pjy6u5L6JfnDDlFtiySbxmHwvY+Ifi5NPLYQQcu179sqzvi8GBQ0Phi3tWGokXjDSWB9kG7KiD13QbCVvF7c0X/b+QfKGdep49SAONecc+OPY3ub/7reDj1fKJL54F6WXtGowUy/VsR0r0GrP3SbusybekmPF2tH9HzMuTqm7Ftu52r6Ij7Ilw7Sm14Zoe5J3ife/R4lhp3Ny9llSVH+0zD/56VHysvpq9RMY=
*/