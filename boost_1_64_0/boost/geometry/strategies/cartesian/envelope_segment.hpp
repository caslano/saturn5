// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_SEGMENT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_SEGMENT_HPP

#include <cstddef>

#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/cartesian/envelope_point.hpp>
#include <boost/geometry/strategies/cartesian/expand_point.hpp>
#include <boost/geometry/strategies/envelope.hpp>

namespace boost { namespace geometry { namespace strategy { namespace envelope
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <std::size_t Dimension, std::size_t DimensionCount>
struct envelope_one_segment
{
    template<typename Point, typename Box>
    static inline void apply(Point const& p1,
                             Point const& p2,
                             Box& mbr)
    {
        geometry::detail::envelope::envelope_one_point
            <
                Dimension, DimensionCount
            >::apply(p1, mbr);

        strategy::expand::detail::point_loop
            <
                Dimension, DimensionCount
            >::apply(mbr, p2);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template
<
    typename CalculationType = void
>
class cartesian_segment
{
public:
    template <typename Point, typename Box>
    static inline void apply(Point const& point1, Point const& point2, Box& box)
    {
        strategy::envelope::detail::envelope_one_segment
            <
                0,
                dimension<Point>::value
            >::apply(point1, point2, box);        
    }

};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<segment_tag, cartesian_tag, CalculationType>
{
    typedef strategy::envelope::cartesian_segment<CalculationType> type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope

}} //namepsace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_SEGMENT_HPP

/* envelope_segment.hpp
bpczwetO5t/MHMtElWlUclsb7CtHVIQVA5LcOE6audMdsxbjIGnZ+hb8BfBi5YPh+13c7ADghSP3/rI6kGo8IzD+KRueE3H/TL1FyJnkTs0zgZIlzgt2UnEhAr81AyfUz+lAbY2sNZhl18V+m4lULYmd9oHdQuGkEQYaZQhXk9wCjN9kjD3sDk9nKAmUBDr4iGO/C60kT+9L70Zuan8c6SewCqIf7bQm15qKjCjCCElclhMS8frrEPtIX639RaSh6tnXoxo30hLZhMdJXRTA7BJyLLHjM6C3NPXZujjq8V9OA2QIAmUWLBvnTh6zCqhP9GJ2pbBIPDSVxdFrFitlaxBFUChtiUwNbztVcSUUupDMw12jKNeypEBCjmrJgtfg2Coz3ByjPsrHgfYsa7JIyrwcI2XvwF/vJZ8Xa75aihJGIiuCvJuxQaMhwLJ1II6Kq3KIPqNs9mY/lq/DT0TbwI91Qik+uHBPb7LHagghIeyvdfp/z+2NTuTmI1DlbEmeoXeXXyLwjaRAPashIg2tj9NWFmlBrnMm27I6+NjPyM7+J8K7HKDmbskaMA==
*/