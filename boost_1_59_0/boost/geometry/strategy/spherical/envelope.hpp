// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2018, 2019.
// Modifications copyright (c) 2015-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_SPHERICAL_ENVELOPE_HPP
#define BOOST_GEOMETRY_STRATEGY_SPHERICAL_ENVELOPE_HPP

#include <boost/geometry/algorithms/detail/envelope/initialize.hpp>
#include <boost/geometry/algorithms/detail/envelope/range_of_boxes.hpp>

#include <boost/geometry/iterators/segment_iterator.hpp>

#include <boost/geometry/strategy/spherical/envelope_box.hpp>
#include <boost/geometry/strategy/spherical/envelope_segment.hpp>
#include <boost/geometry/strategy/spherical/expand_box.hpp>
#include <boost/geometry/strategy/spherical/expand_segment.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace envelope
{

template <typename CalculationType = void>
class spherical
{
public:
    typedef spherical_tag cs_tag;

    // Linestring, Ring, Polygon

    template <typename Range>
    static inline geometry::segment_iterator<Range const> begin(Range const& range)
    {
        return geometry::segments_begin(range);
    }

    template <typename Range>
    static inline geometry::segment_iterator<Range const> end(Range const& range)
    {
        return geometry::segments_end(range);
    }

    // MultiLinestring, MultiPolygon

    template <typename Box>
    struct multi_state
    {
        void apply(Box const& single_box)
        {
            m_boxes.push_back(single_box);
        }

        void result(Box & box)
        {
            if (!m_boxes.empty())
            {
                geometry::detail::envelope::envelope_range_of_boxes::apply(m_boxes, box);
            }
            else
            {
                geometry::detail::envelope::initialize<Box, 0, dimension<Box>::value>::apply(box);
            }
        }

    private:
        std::vector<Box> m_boxes;
    };
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename Tag, typename CalculationType>
struct default_strategy<Tag, spherical_equatorial_tag, CalculationType>
{
    typedef strategy::envelope::spherical<CalculationType> type;
};

template <typename Tag, typename CalculationType>
struct default_strategy<Tag, spherical_polar_tag, CalculationType>
{
    typedef strategy::envelope::spherical<CalculationType> type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope

}} //namepsace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGY_SPHERICAL_ENVELOPE_HPP

/* envelope.hpp
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
*/