// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_MULTIPOINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_MULTIPOINT_HPP

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/envelope_multipoint.hpp>
#include <boost/geometry/strategies/spherical/envelope_multipoint.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename MultiPoint>
struct envelope<MultiPoint, multi_point_tag>
{
    template <typename Box, typename Strategy>
    static inline void apply(MultiPoint const& multipoint, Box& mbr, Strategy const& )
    {
        Strategy::apply(multipoint, mbr);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_MULTIPOINT_HPP

/* multipoint.hpp
IK5HE9VWh1/zq9Mw/Tmjkfrohzdcmm1egyHxh2yu/8u28oYnJWmChOehQiqiMX+4Z0DC7LVeHs/m/MNbEBG+nYkiEJx6AxYYtWpW/3ENwyy8CWpV1YbBK0hz+L+dqNVDRq1SV6InvHV24JqEbLFUmChly/nqK1ol9kJwa2UQymHyasFbIO7UmpQsKUsIYTvWoMIg+LUKCJV4NcRrtFZ6b45WDfcmolLiJlybq+MqZcGamGHBVXoUMvV3qv+GyGcQUiKZOgYqn1OABSCcSInN5HDwtFkbXmHHDPSxg4Kg/v3bxlD8BAqapGadEi5yl4NbtKD6kFSrPghsnPgwzqMQTHROkEz7vX2xeqsiXBc7CyK/g7A3kmn40DZ0P3pHN5u90DwyH9q/jxirYXyVB11IidJtuEIYZ0ukhXKGUgpTeK2SR13ZRXAO/w0Ce9WCsuj2F0obLqPhVamwDitoeCXV4B0m9kzU/gk+EL5tbAAljQU+E9q/CTeiSkHD+r7H5b7jNzpW5/8gsgjChrGZup/2rgKjJJ1mftWk7+IOUtLp1F28iTpqbx9rnU9eHFZ8UbgX4wqxUgrLpcon8ptqofaFY4XqlyslKCSudb6N8509wBYQVyARovJQymRg1zSHA6ZtZ5uJxx5m4bEvjuVj5AZExuVkoh/k0D5EpxbaT1roUtP5gLHvqnt4Mu3BBmjvuS3HyPhzXuAqh4Yn2ESQ
*/