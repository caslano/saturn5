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

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_HPP

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/algorithms/detail/envelope/initialize.hpp>

#include <boost/geometry/strategies/cartesian/envelope_box.hpp>
#include <boost/geometry/strategies/cartesian/envelope_segment.hpp>
#include <boost/geometry/strategies/cartesian/expand_box.hpp>
#include <boost/geometry/strategies/cartesian/expand_segment.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace envelope
{

template <typename CalculationType = void>
class cartesian
{
public:
    typedef cartesian_tag cs_tag;

    typedef cartesian_point element_envelope_strategy_type;
    static inline element_envelope_strategy_type get_element_envelope_strategy()
    {
        return element_envelope_strategy_type();
    }

    typedef expand::cartesian_point element_expand_strategy_type;
    static inline element_expand_strategy_type get_element_expand_strategy()
    {
        return element_expand_strategy_type();
    }

    typedef expand::cartesian_box box_expand_strategy_type;
    static inline box_expand_strategy_type get_box_expand_strategy()
    {
        return box_expand_strategy_type();
    }

    // Linestring, Ring, Polygon

    template <typename Range>
    static inline typename boost::range_iterator<Range const>::type begin(Range const& range)
    {
        return boost::begin(range);
    }

    template <typename Range>
    static inline typename boost::range_iterator<Range const>::type end(Range const& range)
    {
        return boost::end(range);
    }

    // MultiLinestring, MultiPolygon

    template <typename Box>
    struct multi_state
    {
        multi_state()
            : m_initialized(false)
        {}

        void apply(Box const& single_box)
        {
            if (! m_initialized)
            {
                m_box = single_box;
                m_initialized = true;
            }
            else
            {
                box_expand_strategy_type::apply(m_box, single_box);
            }
        }

        void result(Box & box)
        {
            if (m_initialized)
            {
                box = m_box;
            }
            else
            {
                geometry::detail::envelope::initialize<Box, 0, dimension<Box>::value>::apply(box);
            }
        }

    private:
        bool m_initialized;
        Box m_box;
    };

    // Segment

    template <typename Point1, typename Point2, typename Box>
    static inline void apply(Point1 const& point1, Point2 const& point2,
                             Box& box)
    {
        cartesian_segment<CalculationType>::apply(point1, point2, box);
    }

    // Box

    template <typename BoxIn, typename Box>
    static inline void apply(BoxIn const& box_in, Box& box)
    {
        cartesian_box::apply(box_in, box);
    }
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename Tag, typename CalculationType>
struct default_strategy<Tag, cartesian_tag, CalculationType>
{
    typedef strategy::envelope::cartesian<CalculationType> type;
};

} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope

}} //namepsace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_HPP

/* envelope.hpp
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
*/