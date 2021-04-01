// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_CARTESIAN_IO_HPP
#define BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_CARTESIAN_IO_HPP


#include <boost/geometry/strategies/io.hpp>

#include <boost/geometry/strategies/cartesian/point_order.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_winding.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace io
{

template <typename CalculationType = void>
struct cartesian
{
    typedef strategy::point_order::cartesian<CalculationType> point_order_strategy_type;
    
    static inline point_order_strategy_type get_point_order_strategy()
    {
        return point_order_strategy_type();
    }

    template <typename Geometry1, typename Geometry2>
    struct point_in_geometry_strategy
    {
        typedef strategy::within::cartesian_winding
            <
                typename point_type<Geometry1>::type,
                typename point_type<Geometry2>::type,
                CalculationType
            > type;
    };

    template <typename Geometry1, typename Geometry2>
    static inline typename point_in_geometry_strategy<Geometry1, Geometry2>::type
        get_point_in_geometry_strategy()
    {
        typedef typename point_in_geometry_strategy
            <
                Geometry1, Geometry2
            >::type strategy_type;
        return strategy_type();
    }
};

namespace services
{

template <>
struct default_strategy<cartesian_tag>
{
    typedef cartesian<> type;
};

} // namespace services

}} // namespace strategy::io

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_CARTESIAN_IO_HPP

/* io.hpp
DXxs3DdVqwhKOg+rWzFr32lnz3ok9E6QBjEUQvUhVYsvBfL5KQ+Z5XTsWSCVH7/diZrUSdFNORM8CSdkc+s7NhvcLcfT53voN2CRJLt9v0tPq8aDAtjpp1hbRFn1WcZup34/S6RTMeyG/Hknpg6OKtlEJ+/YMypafbzIhdLOodQp9xwEVHlx67r3WqpSBWHdkG3RM1FWtWOVTf604Q+Nfwd74jut3u5VyK4p2Gjxc+QJ9IS5cfJz0LyX2yn7iSPHQXTTRwxZsPKJOOP7gJQ8DOd0mpx05IZSAowZpjxNC5YU0lZcfmIseoJmWCfiI50AekHq6eU8nnLqHmJCfPRbZSxGiKcJdyYGjshbC4FUfpT9slTrZtdtykPrF2scuPSbYxXzRVaEqp4tYhu9uof6U7b3aSC6h6HgfP8IHjLKJaJ7X/Fd9mXf3530XPxgLY/uhNqIvMWdl6wHWBiNAJgiQXXLkPjcLHKBLVOd594TK/ah87TOlAqVmK4B08LuyBJ7dBomlt1MhhXv3USIepsMjTn37xFCdDgSJ8pkRsYakly+nYud7pmWFSz0aA==
*/