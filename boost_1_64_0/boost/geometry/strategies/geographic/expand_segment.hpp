// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_EXPAND_SEGMENT_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_EXPAND_SEGMENT_HPP

#include <cstddef>
#include <functional>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/envelope/box.hpp>
#include <boost/geometry/algorithms/detail/envelope/range_of_boxes.hpp>
#include <boost/geometry/algorithms/detail/envelope/segment.hpp>

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/strategies/expand.hpp>
#include <boost/geometry/strategies/geographic/envelope_segment.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/spherical/expand_segment.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace expand
{

template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = geometry::srs::spheroid<double>,
    typename CalculationType = void
>
class geographic_segment
{
public:
    inline geographic_segment()
        : m_envelope_strategy()
    {}

    explicit inline geographic_segment(Spheroid const& spheroid)
        : m_envelope_strategy(spheroid)
    {}

    template <typename Box, typename Segment>
    inline void apply(Box& box, Segment const& segment) const
    {
        detail::segment_on_spheroid::apply(box, segment, m_envelope_strategy);
    }

private:
    strategy::envelope::geographic_segment
        <
            FormulaPolicy, Spheroid, CalculationType
        > m_envelope_strategy;
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<segment_tag, geographic_tag, CalculationType>
{
    typedef geographic_segment
        <
            strategy::andoyer,
            geometry::srs::spheroid<double>,
            CalculationType
        > type;
};

} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::expand

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_EXPAND_SEGMENT_HPP

/* expand_segment.hpp
/3ERwOVwUL1BUsy+i+PbK93cisf1CjkaHNItIsRa7lVdt4JC1Iri0HVg7ZwwU3dq2MbypZCbFLjoZOiXVROfnXYf5DH0UyMsYvIQJhjtCYXGpzZA24U4p4R7Q4+9SsJOSEW+6yJFv4wE2TTuXvFXaJ+vgZmkxxH04NaHdEHxx4WZZBNNI4/SkbRXYcFL1MJlT5Oipm58cIqgIpPFFwTT1SPrny3agHzdOVGm/dcheiAKU8gXms4LTJ/aSo+Td6yhk+iL91w7BBcHfOG781PC8SJKyZ6qo9ygKFPq6Bx/x08ccfBQ/1wde0v35CgnIOMdCMf60qaD0l6cHScwDl+Tsn+4jYWFkgzmfu48OfJZIxG0ydkq6FBArR42/tpn2jjXSexxNESDB5ebGdSlLZ2wj81xgZCuq5D2AqMbpr2hVb5e9HUuHZZQMJNx7b0kRx+303spGsSlumX3PUwj0nwQnfwK+MXtv3a1QXR5u0/P50+CV5E85DhIKH5Un15QonqxHnChJEQ2A3VtBbizzI3yP1s1p3xAat3aVeE7I8hU4yjy7l2dvxw4M/f/mQ==
*/