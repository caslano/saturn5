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
ky/wCY6Pjo9SOBdWo4FFQLtGf5/CqWwj35V4ehoSnqWAAYQZdlRLpQnIleFReAReG12gJZQgCCRS4fWaN9pCUAilNgjj2fVqMv2ZwqPShYokz64BUq4xEpR4QPBYoH7YcNTCB3Alw5lcagpM2ATt7JC1EQL6iiJHlBeGHIgHoY1Ys5AIoEKo6WuWFY037D6TrqCs2B5/qEL1epIVm6jEM7g6QHDQEKYQM1OonNRlnLkgHKybtdGk0p0blrIycx4IjYlcjNNIG9sIi648aUyDmh3rECdylqLUo3LVm0SuY2QpG29ZiOvASdJxmVNo+K/k2+T25FuJrqZtgf97NTu/EpxlM9AbLWCy6MFakKYUbifLy9nNEm5H8/loulzB7AeMpqtIdjWZnvPVaxbzgE+1R2JxD7qqjUbZaX7cyJK+toVpJEIvXl5OGJp6qHq7+CkFyd1jqM4SDnY9ZvT7Yts/5kmhhIfBuIUHH9zf3B9sYhTv1lKAzVai0VXabQZGUDj89tqatlB4Q5T00RC+ceO1vY9u+mj5hUm6GbLBu90N+Iz/AFBLAwQKAAAACAAtZ0pSnGllLkcJAAChFgAAGwAJAGN1cmwtbWFzdGVyL2xpYi9zdHJ0b29mZnQuY1VUBQABtkgkYK1YWXPayBZ+
*/