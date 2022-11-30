// Boost.Geometry

// Copyright (c) 2021-2022, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGY_SPHERICAL_ENVELOPE_RANGE_HPP
#define BOOST_GEOMETRY_STRATEGY_SPHERICAL_ENVELOPE_RANGE_HPP

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/detail/envelope/initialize.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/strategy/spherical/envelope_point.hpp>
#include <boost/geometry/strategy/spherical/envelope_segment.hpp>
#include <boost/geometry/strategy/spherical/expand_segment.hpp>
#include <boost/geometry/views/closeable_view.hpp>

// Get rid of this dependency?
#include <boost/geometry/strategies/spherical/point_in_poly_winding.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace envelope
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Range, typename Box, typename EnvelopeStrategy, typename ExpandStrategy>
inline void spheroidal_linestring(Range const& range, Box& mbr,
                                  EnvelopeStrategy const& envelope_strategy,
                                  ExpandStrategy const& expand_strategy)
{
    auto it = boost::begin(range);
    auto const end = boost::end(range);
    if (it == end)
    {
        // initialize box (assign inverse)
        geometry::detail::envelope::initialize<Box>::apply(mbr);
        return;
    }

    auto prev = it;
    ++it;
    if (it == end)
    {
        // initialize box with the first point
        envelope::spherical_point::apply(*prev, mbr);
        return;
    }

    // initialize box with the first segment
    envelope_strategy.apply(*prev, *it, mbr);

    // consider now the remaining segments in the range (if any)
    prev = it;
    ++it;
    while (it != end)
    {
        using point_t = typename boost::range_value<Range>::type;
        geometry::model::referring_segment<point_t const> const seg(*prev, *it);
        expand_strategy.apply(mbr, seg);
        prev = it;
        ++it;
    }
}


// This strategy is intended to be used together with winding strategy to check
// if ring/polygon has a pole in its interior or exterior. It is not intended
// for checking if the pole is on the boundary.
template <typename CalculationType = void>
struct side_of_pole
{
    typedef spherical_tag cs_tag;

    template <typename P>
    static inline int apply(P const& p1, P const& p2, P const& pole)
    {
        using calc_t = typename promote_floating_point
            <
                typename select_calculation_type_alt
                    <
                        CalculationType, P
                    >::type
            >::type;

        using units_t = typename geometry::detail::cs_angular_units<P>::type;
        using constants = math::detail::constants_on_spheroid<calc_t, units_t>;

        calc_t const c0 = 0;
        calc_t const pi = constants::half_period();

        calc_t const lon1 = get<0>(p1);
        calc_t const lat1 = get<1>(p1);
        calc_t const lon2 = get<0>(p2);
        calc_t const lat2 = get<1>(p2);
        calc_t const lat_pole = get<1>(pole);

        calc_t const s_lon_diff = math::longitude_distance_signed<units_t>(lon1, lon2);
        bool const s_vertical = math::equals(s_lon_diff, c0)
                             || math::equals(s_lon_diff, pi);
        // Side of vertical segment is 0 for both poles.
        if (s_vertical)
        {
            return 0;
        }

        // This strategy shouldn't be called in this case but just in case
        // check if segment starts at a pole
        if (math::equals(lat_pole, lat1) || math::equals(lat_pole, lat2))
        {
            return 0;
        }

        // -1 is rhs
        //  1 is lhs
        if (lat_pole >= c0) // north pole
        {
            return s_lon_diff < c0 ? -1 : 1;
        }
        else // south pole
        {
            return s_lon_diff > c0 ? -1 : 1;
        }
    }
};


template <typename Point, typename Range, typename Strategy>
inline int point_in_range(Point const& point, Range const& range, Strategy const& strategy)
{
    typename Strategy::state_type state;

    auto it = boost::begin(range);
    auto const end = boost::end(range);
    for (auto previous = it++ ; it != end ; ++previous, ++it )
    {
        if (! strategy.apply(point, *previous, *it, state))
        {
            break;
        }
    }

    return strategy.result(state);
}


template <typename T, typename Ring, typename PoleWithinStrategy>
inline bool pole_within(T const& lat_pole, Ring const& ring,
                        PoleWithinStrategy const& pole_within_strategy)
{
    if (boost::size(ring) < core_detail::closure::minimum_ring_size
                                <
                                    geometry::closure<Ring>::value
                                >::value)
    {
        return false;
    }

    using point_t = typename geometry::point_type<Ring>::type;
    point_t point;
    geometry::assign_zero(point);
    geometry::set<1>(point, lat_pole);
    geometry::detail::closed_clockwise_view<Ring const> view(ring);
    return point_in_range(point, view, pole_within_strategy) > 0;
}

template
<
    typename Range,
    typename Box,
    typename EnvelopeStrategy,
    typename ExpandStrategy,
    typename PoleWithinStrategy
>
inline void spheroidal_ring(Range const& range, Box& mbr,
                            EnvelopeStrategy const& envelope_strategy,
                            ExpandStrategy const& expand_strategy,
                            PoleWithinStrategy const& pole_within_strategy)
{
    geometry::detail::closed_view<Range const> closed_range(range);

    spheroidal_linestring(closed_range, mbr, envelope_strategy, expand_strategy);
    
    using coord_t = typename geometry::coordinate_type<Box>::type;
    using point_t = typename geometry::point_type<Box>::type;    
    using units_t = typename geometry::detail::cs_angular_units<point_t>::type;
    using constants_t = math::detail::constants_on_spheroid<coord_t, units_t>;
    coord_t const two_pi = constants_t::period();
    coord_t const lon_min = geometry::get<0, 0>(mbr);
    coord_t const lon_max = geometry::get<1, 0>(mbr);
    // If box covers the whole longitude range it is possible that the ring contains
    // one of the poles.
    // Technically it is possible that a reversed ring may cover more than
    // half of the globe and mbr of it's linear ring may be small and not cover the
    // longitude range. We currently don't support such rings.
    if (lon_max - lon_min >= two_pi)
    {
        coord_t const lat_n_pole = constants_t::max_latitude();
        coord_t const lat_s_pole = constants_t::min_latitude();
        coord_t lat_min = geometry::get<0, 1>(mbr);
        coord_t lat_max = geometry::get<1, 1>(mbr);
        // Normalize box latitudes, just in case
        if (math::equals(lat_min, lat_s_pole))
        {
            lat_min = lat_s_pole;
        }
        if (math::equals(lat_max, lat_n_pole))
        {
            lat_max = lat_n_pole;
        }

        if (lat_max < lat_n_pole)
        {
            if (pole_within(lat_n_pole, range, pole_within_strategy))
            {
                lat_max = lat_n_pole;
            }
        }
        if (lat_min > lat_s_pole)
        {
            if (pole_within(lat_s_pole, range, pole_within_strategy))
            {
                lat_min = lat_s_pole;
            }
        }

        geometry::set<0, 1>(mbr, lat_min);
        geometry::set<1, 1>(mbr, lat_max);
    }
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

template <typename CalculationType = void>
class spherical_linestring
{
public:
    template <typename Range, typename Box>
    static inline void apply(Range const& range, Box& mbr)
    {
        detail::spheroidal_linestring(range, mbr,
                                      envelope::spherical_segment<CalculationType>(),
                                      expand::spherical_segment<CalculationType>());
    }
};

template <typename CalculationType = void>
class spherical_ring
{
public:
    template <typename Range, typename Box>
    static inline void apply(Range const& range, Box& mbr)
    {
        detail::spheroidal_ring(range, mbr,
                                envelope::spherical_segment<CalculationType>(),
                                expand::spherical_segment<CalculationType>(),
                                within::detail::spherical_winding_base
                                    <
                                        envelope::detail::side_of_pole<CalculationType>,
                                        CalculationType
                                    >());
    }
};

}} // namespace strategy::envelope

}} //namepsace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGY_SPHERICAL_ENVELOPE_RANGE_HPP

/* envelope_range.hpp
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
*/