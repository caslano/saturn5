// Boost.Geometry

// Copyright (c) 2020-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_ENVELOPE_GEOGRAPHIC_HPP
#define BOOST_GEOMETRY_STRATEGIES_ENVELOPE_GEOGRAPHIC_HPP


#include <type_traits>

#include <boost/geometry/strategy/geographic/envelope.hpp> // Not used, for backward compatibility
#include <boost/geometry/strategy/geographic/envelope_range.hpp>
#include <boost/geometry/strategy/geographic/envelope_segment.hpp>

#include <boost/geometry/strategies/envelope/spherical.hpp>
#include <boost/geometry/strategies/expand/geographic.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace envelope
{

template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic
    : public strategies::expand::geographic<FormulaPolicy, Spheroid, CalculationType>
{
    using base_t = strategies::expand::geographic<FormulaPolicy, Spheroid, CalculationType>;

public:
    geographic() = default;

    explicit geographic(Spheroid const& spheroid)
        : base_t(spheroid)
    {}

    template <typename Geometry, typename Box>
    static auto envelope(Geometry const&, Box const&,
                         util::enable_if_point_t<Geometry> * = nullptr)
    {
        return strategy::envelope::spherical_point();
    }

    template <typename Geometry, typename Box>
    static auto envelope(Geometry const&, Box const&,
                         util::enable_if_multi_point_t<Geometry> * = nullptr)
    {
        return strategy::envelope::spherical_multipoint();
    }

    template <typename Geometry, typename Box>
    static auto envelope(Geometry const&, Box const&,
                         util::enable_if_box_t<Geometry> * = nullptr)
    {
        return strategy::envelope::spherical_box();
    }

    template <typename Geometry, typename Box>
    auto envelope(Geometry const&, Box const&,
                  util::enable_if_segment_t<Geometry> * = nullptr) const
    {
        return strategy::envelope::geographic_segment
            <
                FormulaPolicy, Spheroid, CalculationType
            >(base_t::m_spheroid);
    }

    template <typename Geometry, typename Box>
    auto envelope(Geometry const&, Box const&,
                  util::enable_if_linestring_t<Geometry> * = nullptr) const
    {
        return strategy::envelope::geographic_linestring
            <
                FormulaPolicy, Spheroid, CalculationType
            >(base_t::m_spheroid);
    }

    template <typename Geometry, typename Box>
    auto envelope(Geometry const&, Box const&,
                  std::enable_if_t
                    <
                        util::is_ring<Geometry>::value
                     || util::is_polygon<Geometry>::value
                    > * = nullptr) const
    {
        return strategy::envelope::geographic_ring
            <
                FormulaPolicy, Spheroid, CalculationType
            >(base_t::m_spheroid);
    }

    template <typename Geometry, typename Box>
    auto envelope(Geometry const&, Box const&,
                  std::enable_if_t
                    <
                        util::is_multi_linestring<Geometry>::value
                     || util::is_multi_polygon<Geometry>::value
                     || util::is_geometry_collection<Geometry>::value
                    > * = nullptr) const
    {
        return strategy::envelope::spherical_boxes();
    }
};


namespace services
{

template <typename Geometry, typename Box>
struct default_strategy<Geometry, Box, geographic_tag>
{
    using type = strategies::envelope::geographic<>;
};


template <typename FP, typename S, typename CT>
struct strategy_converter<strategy::envelope::geographic_segment<FP, S, CT> >
{
    static auto get(strategy::envelope::geographic_segment<FP, S, CT> const& s)
    {
        return strategies::envelope::geographic<FP, S, CT>(s.model());
    }
};

template <typename FP, typename S, typename CT>
struct strategy_converter<strategy::envelope::geographic<FP, S, CT> >
{
    static auto get(strategy::envelope::geographic<FP, S, CT> const& s)
    {
        return strategies::envelope::geographic<FP, S, CT>(s.model());
    }
};

} // namespace services

}} // namespace strategies::envelope

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_ENVELOPE_GEOGRAPHIC_HPP

/* geographic.hpp
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
*/