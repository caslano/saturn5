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
b0gkVlHztdrPEMSF2Cpof0YyLHPE58Pef51lqyF83vx4REXisDOwGUMPm4T48B02z/wLPeeA2dAdo1F2cPPxi+RSX9tFU6hbGk05s+RRwcNWr6N3g3TgEkopwND8XIynVpiDFtqYTjUIb6K67UahPiYTJuv9gZNShOo/XOEd+SqFdZYqu6WTTgjbTg3Lbi53Ce0os0ReM5ekWsPkg0N8T/zIU/eTU3hApg2aZml9hSbWxhrkQ2Dyhkr2Etcze+cA+AxOSPHzy6x5e9/kHbY/4qDHi+UueogQNwpQu9UagCJRfrm4iV9iWSsI30D/NvP9XZPQyDE/I2wUfhwfEHHucqLlLaOLxJk7e7C/p3yq45uqbH8uV5yuWwbQXRz4xG/mK1uUA0ZgjOblA+Bh9Ln/nmGDmt9lwGdYuybve6+D0jljYBB2QMD6PG1M6U+/CxQM7UwxmyYEB+RxArfD1LeBtBBo+lGaheJxiOqKfGhWmkCDAW3OZcVsBnoaF7LB7Y/NFYMNJhhhTyLLfR8KkMWK9YMTJOftOzMZYXKwNmdcdnfo40Uo1tExf/80Ww==
*/