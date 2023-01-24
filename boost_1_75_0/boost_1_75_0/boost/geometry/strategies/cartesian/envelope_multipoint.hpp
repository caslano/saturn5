// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_MULTIPOINT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_MULTIPOINT_HPP

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/envelope/range.hpp>

#include <boost/geometry/strategies/cartesian/envelope.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace envelope
{

class cartesian_multipoint
{
public:
    template <typename MultiPoint, typename Box>
    static inline void apply(MultiPoint const& multipoint, Box& mbr)
    {
        geometry::detail::envelope::envelope_range::apply(multipoint, mbr, cartesian<>());
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<multi_point_tag, cartesian_tag, CalculationType>
{
    typedef strategy::envelope::cartesian_multipoint type;
};


} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_MULTIPOINT_HPP

/* envelope_multipoint.hpp
Ldhj+z3SQOhvA47Pf6PGWgDI/Kkdug+3KOKUEy6pYO4okO235wf/PEX84ucGot27P1lp+K31O4odY7TS+jNeC71b6U5Zfl7ZbP+B+ZDw9bIvIE25GRyQG0zzgML5Gz6X4Elb7P+fllzkv1rynAE6pZwBpbkmpdSfXsmC3hyDbjmidC0c+OFD0VTZTX+IHqx21LswnGRVVgqrKyUpYLB/VJkTeKn/Dc+RnOrGbhTvS5Gx4PLQkCC5ofnL5SwiQfIJfWCelEL5fS6h8VjFmQEtKPFgq2uq0uP8wR84uXRBu1EbbD3TSNfdts1L8s34o3St9ZidugmtDoc0SUFEYDBn9sR+QyMYb+njPYV+fxun1o5+zPeEB6NLcVeKNmojtBrMKRxuTS98GQFYhrrWbeXlGAVBIpb7b5WzNzJf5hS3dD846csXn2cdwPd6KpSTQEqkkbCTRRdww5HCle13nKP0Yt7a1A4WqbC3xr83MTjjJRkNd4WtGGiy5ZHYs/o9AL6ZTPaFHyOeKvfGnYzV2Rh/3spcy6FjowfRjzTz6DwYQz+lpoA7HwZbSqCDt5/HSi3O7kIu3M8g3QFtAErxjpNo6P7n+x94t3BAEfmDUOhBGulvl57Z4LnTXTInIKFpdkoKKgT6OL3fKxMS21cdklYNcVzTTCUdMwNC2B8kRHQeOqPWPQSYUUMtRX3sZ8yrsSnqHwH4T2vwXTg8WwMr
*/