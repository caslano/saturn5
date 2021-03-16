// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP
#define BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP

#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/strategies/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


// metafunction to determine is a strategy is comparable or not
template <typename Strategy>
struct is_comparable
    : boost::is_same
        <
            Strategy,
            typename strategy::distance::services::comparable_type
              <
                  Strategy
              >::type
        >
{};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP

/* is_comparable.hpp
R8E2M3sabBOz98C2MCNLyxvMCsDqmT0M9g2zPV6nVH8Fa2B2EuwQs1QsqI4w6wn2PbPBWivV2rdgPzI7DbaVWVu/ENuYhTSbD7aC2UtgjzHzBoRozc8tCHYBs4SA/FeFHv5mZUtmrcFSmKWBpTLrCNaKWQZYGrNMsHbMLgTrwKwXWEdm2WDpzHLBOjHLB+vMbABYBrMCsC7MCsG6MouAdWNWDJbFbAjYhcyGg/VkRt8BvYjZrWAXMysF68VsIlg=
*/