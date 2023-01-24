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
04j6EANHOSNlekdL/yCEA8oTLkQtav3CL5hdpAlFH5R6GuWViFW580OmYJ3KwUzXcJF7ZjP+6kusUO5fGdCxn2O1v4DE56/vyXzT6kwxSA9QJD1oKGzIN5c+MPyCoFQzsFQ4cvtp4NMbODhkO2AIztJjH4g56PNnrxjhp9pgZ7cbZvAT0X6GkKJxTty7wiE7ZUCq4gyVj5GQVGCrGeTdo0V5E6leQJUnv+6Q7efg6mcDG+32GnUblsjStdIvMJb4AvLxD1U5oOrsSVcDmVfHI208Q/G9n66UK29fEpwwZiUO92Qo8osF00xrd4xqRDd+DI0HCPgMYqsxWue0zn81f//KrYp9LTN4PJV0SccAb/dRfm/jAYnh59F1mnMoWEe8ge1duNar7kkF0/CsfQGQaC3uqbl1MZUfiuyecv66DmKoGu9x8qS0kaabX7iOErVj4vpJnN6nXkKn4ZhuX+ZXqsT668hh9sdQqnOF0oYqBS4nbYB0LKWDNp/AYn5uj2NJRTlPj/jqSS2FWDhHy6RTnjzdE/ZHVcKHnW2XittX50s1bkv3aLAyYW6w9dMX4F6IG/dg1YwbGKC8tLfrQriafQosXNxrwuGsU3IkYnmUouAuGijAHGZc+FLVeOmmavEywP6u7asWNUMCGXKyy5i+9s5yyqndF8WL3BUmQzGOFTGHjsvaVATmWJuDuAIxKmpnifu/ISQc8t+uv9FK
*/