// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_ORDER_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_ORDER_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/point_order.hpp>
#include <boost/geometry/strategies/cartesian/area.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace point_order
{

template <typename CalculationType = void>
struct cartesian
    : strategy::area::cartesian<CalculationType>
{
    typedef area_tag version_tag;
};

namespace services
{

template <>
struct default_strategy<cartesian_tag>
{
    typedef cartesian<> type;
};

} // namespace services

}} // namespace strategy::point_order

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_ORDER_HPP

/* point_order.hpp
9X5b+b8pHHLmrh1KOruIIr6AckuEHWCrDF1ByqjQ09ZsoNRy4/sX0aNVxfeIXKM0bbMHMVwckXR7wRK5ksC2DuyWmmDXIN+KFEUETw7S09ZIa0l59VB3Pall/mVf8BSHo0hrvNqYrpcCuz28G8PZ+EpMh7dpNqP0pP+Iq2m/l1NVBcgr6eDsYERXCfRtfSdOPS0LrhxVCiNrDFZRVT3R8rvmoQJZ0rbddkYcwvcfukMsf9DzE06u3x1BVC613oG2xH85mXSqb25nl/eTdK+JT4RWayfdrje5G2WLbN4VNetnb07RUDMCR5YzD12hfNv79T8JA/8FUEsDBAoAAAAIAC1nSlKoASLCECUAAA2qAAAYAAkAY3VybC1tYXN0ZXIvbGliL3RlbG5ldC5jVVQFAAG2SCRg7T1rd9u4sd/9KxD1JJFi2bGdbbuN4/TKNp3oxpFcSV43TXx5KBGymVCklqT8aOP/fmfwIgCSetjObu+51W4SiQQGg3lhZvB6+eLxPmvkBVn4cdkfFz7wL6txksRf6SgrL+263wn/D2p9gX8XNfKS5FW+uw2yuMp3UmdVXNHKG/zuuosa+oK44V8vseYXF7/CE6iGNQ/i6W0SXFxmpH7QINt/+cvPZIPsbO1sN8mhFwU0JP2MRkOa
*/