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

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_HPP

#include <boost/geometry/algorithms/detail/envelope/initialize.hpp>
#include <boost/geometry/algorithms/detail/envelope/range_of_boxes.hpp>

#include <boost/geometry/iterators/segment_iterator.hpp>

#include <boost/geometry/strategies/spherical/envelope_box.hpp>
#include <boost/geometry/strategies/spherical/envelope_segment.hpp>
#include <boost/geometry/strategies/spherical/expand_box.hpp>
#include <boost/geometry/strategies/spherical/expand_segment.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace envelope
{

template <typename CalculationType = void>
class spherical
{
public:
    typedef spherical_tag cs_tag;

    typedef spherical_segment<CalculationType> element_envelope_strategy_type;
    static inline element_envelope_strategy_type get_element_envelope_strategy()
    {
        return element_envelope_strategy_type();
    }

    typedef expand::spherical_segment<CalculationType> element_expand_strategy_type;
    static inline element_expand_strategy_type get_element_expand_strategy()
    {
        return element_expand_strategy_type();
    }

    typedef strategy::expand::spherical_box box_expand_strategy_type;
    static inline box_expand_strategy_type get_box_expand_strategy()
    {
        return box_expand_strategy_type();
    }

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

    // Segment

    template <typename Point1, typename Point2, typename Box>
    static inline void apply(Point1 const& point1, Point2 const& point2,
                             Box& box)
    {
        spherical_segment<CalculationType>::apply(point1, point2, box);
    }

    // Box

    template <typename BoxIn, typename Box>
    static inline void apply(BoxIn const& box_in, Box& box)
    {
        spherical_box::apply(box_in, box);
    }
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

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_HPP

/* envelope.hpp
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
*/