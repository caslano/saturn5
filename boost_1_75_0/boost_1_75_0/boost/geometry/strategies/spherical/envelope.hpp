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
GypbAxwdzf15TB2qHR2ww8yG+Kz16Z+pGQJMsrvWdHjHWNtZOkE5x+du5/bOE7w0y2nVNPvsBjnfsJiu/vhpyoBpD30Fm19YdDPJho9OqrdC75VKD7W6YfYM9XEx8maTAWNOnseHn9rXu040tXXaq2oJ6sh34wbR9165X8SSQ18xRGXkxFSW+Bb67a8vZ/QAnOkXGSoPwtru0GD9s1TvuUAoEbGqyjM4YmKLng4n91VVqL6ruOcfYJZHIlztmpp9Bx1dPe97V7/8QH2XBHi1KLNMct5pRxltQ+9eDd/+CguE71KYH8l6tUOeczk3leRFIBYmFLywGJd0vPO/3j7jq5j3ZNC3DbmeZ7d6rdqUz+sLLud2AsZY0rkDZDkTLTdp6nebytr0yleQVLPBKVZF5HRrYhe+OhzWry2K21+biJRJne8JWwZ/GxZ2phsVKkQd65esfn9jSyjZ+1FEOIjoWJPdQSvlzJmr+TIcms/hYRqpT2pGHL5saQeabBnPNXmiN2VzxP89qpDYdDdV9RWsN5doXlfUHUwpriEYSF3q8eo+vyrFxOt7KsI1n7UDx1ivwOawn+Cojw1rHrbTMwnwbb6++hgztrRKudNM9NPfjra3lZ+QNU/xoYcy9MbYxF+bFkYc+aGmjWJeiFPjxRjDgOGY53apQrkWY7KYconX7rWCTN0FfZc+7YPtiHdJ1yJ1wzTTL3o6XCmRqaXs
*/