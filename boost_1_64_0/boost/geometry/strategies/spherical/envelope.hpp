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
tEdRyvFN/bFa9qEdatQ1oOs7dr5bP9mpbKd9G87raeI3In/758pH7Z9TK9o/75PPaRXN5d8BnlL2w5fV8E5MZ57cL41t1GK3H7vCy5+s+5o29zHoZzqelJ9F29P4pR4nv8dImrcdk21SZUf8XUPZkXUZTsFlR9ZlBcUvO7Iu2ym4bMq6bKTgsiDrMqiCykyK36+cdZlV8cuCrMusCiojun5lWdZlSsUv87Euayp+2Y512VHBZZv9quj7/7Oj+1tf+PCWs7savlxz4SZ+SLS345Q8VvLe0yXN7Tjvk7Kf+7EaRmJzjMK2OBqnYTTOxBh8DmNxGY7D7ZiIRzEJv8Nk7Ep8KTgIUzEW03AypuM8nIDPYCYexYn4I07Bn/BBvKC3N5X8VPLZ04Sq/D9ftqOCbMfteCf6Yz2shM2wCvbCO3AsVsPZGIALsAZuwkA8iDVle4LwT6yD3kTeCH2wMTbAJhiGTbELNsP7MBhTMATXY2t8G9vgVxiKX2M7vIIdULtvdJTtzfaQvBVryXG7jf9Pl+0Nk+PVBVtjV+yN3XAQdscR2AOjsRdOxN64EPviauyHH2J//B4HyHYOxCo4DO/E4ejjVXg7GBKm2r3sJOQTLlu0gTG3f7Fu92Ju7/Lf+4055y/8zmz1G/OB6/w7c3Dfov/WbLQlcW5HUrQ2JFmE7L/pt+ei/u5MOxD57fna2n4Upd1HUdt8yG/Q0tbj+v0OHWjxW/Tqv/n3aNUOgxDcivZZhKxWN39zvvl38+/v/ruh7/+JCaOvx/u/1p/83Txo6v3P66+H8uKbaq/zH03qHXXvuxVQ9/78vBtd917GuJT4wwiVCe0Je0hI5Hw9fnlhV2NAFnmcif0+Rt/e9dXn0So9s+3fq37+y6hpo22u9WltJd37Vu+tvX/Pd4xZpw/f3yu8592D9EFXizFeXbZFn/izjfECzfVkS7r3td6fdJy3SEdxx83rW1Glw1z/1dN9zMBw5g1cYBGnPnLgtcVZ2LiBVzwLGJt1wd87NqvjvB3uZT3uZ86Cax/3U42F7WU9Pmbegr93fMxIb+vxMT0W3tjxMbtI/Ock/nYSfyvCRnZ0mMRPQwhbVGrqBIaJZEckj2f4hDh+6htdlPrh1r+BuY/tw2+obm0BqklbgKfYd9kL1W9wakySiGgyzWLkVSoNpvFBosc7t8140n6cVH7l5TSuD5rSWk7qiv8oY12ewREct7AnndIan5yc6vhBVNK6qJC05rikdaXKv6ITk6QOe66Rp6VkpKixUcjTJK2S/iw1ny0lIdk+ra9x/SeAaidVS34zHhMR5TbGiYzHIuviACRPkPEczL/Thqn1jI/ixJXzz/k36mR1XXQzzxvlmLeDKS3jTGPxpMk+f7UE8+JLmMQxC16s9rl97L1rODed41ldQerLYaD4IPGEP6fisZ9+Es+hq8ZTDngGWM2yTp+Xr5I++GnH1sr+/6C+/UNbesi03JfVtGDHtHpqWptWjmmXX1LT1LJ7jGkhan3GtBaOacnGNBXHsysd01qr9WUY09T6uhnT1PoCjWnNHdN+fFFNU3EcUtNatXVMW2FMC3VMu8eY1sYxrcYKNU3Fe/cLjmktWzumBRnT1L76c7maprbtLWNac7W9alqISkuAMU2l5YdlapqK9wNjmop3uTFNxZtlTFP7dIQxTW1bG2OaSl+gMU3t0yvPO6a1MPbpUjVNrW9PjmNac7VtLxnT1LZNMaapbeuzRE1T62tuTFPpu92YpqevAtPyn3NMa6t/flt9DtWvxWMu+d5pizz6vNEGj5uHfdpldT+xqWnBzvm2jGeWSd6RTUfojYlUtsMYV0uPNybe+X450J5vjmOqljeodRw=
*/