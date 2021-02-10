// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_DO_REVERSE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_DO_REVERSE_HPP

#include <boost/geometry/core/point_order.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

// Metafunction helper for intersection and union
template <order_selector Selector, bool Reverse = false>
struct do_reverse {};

template <>
struct do_reverse<clockwise, false> : boost::false_type {};

template <>
struct do_reverse<clockwise, true> : boost::true_type {};

template <>
struct do_reverse<counterclockwise, false> : boost::true_type {};

template <>
struct do_reverse<counterclockwise, true> : boost::false_type {};


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_DO_REVERSE_HPP

/* do_reverse.hpp
hrPmZnsopXKvY8yXr2Mjia5I3MmHRjo07pd2p3c05NAf6OAMdQ73ZHElJ1eDvJb3vxM3ugBrTaMPhrR3xtkKlH1YVXr1k4dc4ibdIAs0HG1HxOQ2WyUfvl2IHP/RsXuqLbW+Uchwsmfk/pM4xvxKCTlrkLkYp4EK2uGT+8bDWoaWoveqTCqFfzj3Eo/WTWQg5Fsr3lP/fp+t53NNCPtzki8frTe0KVeNSKV/0qHBTNA545MuWYjCb3/OMKkS6/7oiqt9AXDEcniwcjv7HNot33zQsd76RUkwqATNLYOjLa3MkafLakfr+2Y48hOO3QxJZ5hS0VvspJALDdHb9kczZJgwPeID8deSHDQmglD81dLSJU3NxyLp9E8Ssp88BzAgeGEwCrLwRmg3kkpPEAtMRWMtWHeflQBLjhcyBvMIIN59VgQ558VShHnhbLb6J5udXvlklkBZltVHtuFk9Sl19imFzSIE5IV04dGFWxUOKwugeymelwCHDPAAQHveMDvfhJVbG1+Y+16QemOPF0G2725RJDrP9/PIi/Hiz62SFBedWjsSiaDHGdJQiKoanJ1MRPbvuF6NfaSFQ/wkhycBaIonOBQr9wDFhXMLuFPl6snithOE5cdlBQj+dmAmgMtpkqSmwaGbdvh2tShk
*/