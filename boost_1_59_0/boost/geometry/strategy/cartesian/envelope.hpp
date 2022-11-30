// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2020.
// Modifications copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_CARTESIAN_ENVELOPE_HPP
#define BOOST_GEOMETRY_STRATEGY_CARTESIAN_ENVELOPE_HPP

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/algorithms/detail/envelope/initialize.hpp>

#include <boost/geometry/strategy/cartesian/envelope_box.hpp>
#include <boost/geometry/strategy/cartesian/envelope_segment.hpp>
#include <boost/geometry/strategy/cartesian/expand_box.hpp>
#include <boost/geometry/strategy/cartesian/expand_segment.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace envelope
{

template <typename CalculationType = void>
class cartesian
{
public:
    typedef cartesian_tag cs_tag;

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
                strategy::expand::cartesian_box::apply(m_box, single_box);
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

#endif // BOOST_GEOMETRY_STRATEGY_CARTESIAN_ENVELOPE_HPP

/* envelope.hpp
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
*/