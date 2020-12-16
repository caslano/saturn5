// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_ENVELOPE_SEGMENT_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_ENVELOPE_SEGMENT_HPP


#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/strategies/cartesian/envelope_segment.hpp>
#include <boost/geometry/strategies/envelope.hpp>
#include <boost/geometry/strategies/geographic/azimuth.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategies/spherical/envelope_segment.hpp>
#include <boost/geometry/strategies/spherical/expand_box.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace envelope
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
    typedef Spheroid model_type;

    inline geographic_segment()
        : m_spheroid()
    {}

    explicit inline geographic_segment(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    typedef strategy::expand::spherical_box box_expand_strategy_type;
    static inline box_expand_strategy_type get_box_expand_strategy()
    {
        return box_expand_strategy_type();
    }

    template <typename Point, typename Box>
    inline void apply(Point const& point1, Point const& point2, Box& box) const
    {
        Point p1_normalized, p2_normalized;
        strategy::normalize::spherical_point::apply(point1, p1_normalized);
        strategy::normalize::spherical_point::apply(point2, p2_normalized);

        geometry::strategy::azimuth::geographic
            <
                FormulaPolicy,
                Spheroid,
                CalculationType
            > azimuth_geographic(m_spheroid);

        typedef typename geometry::detail::cs_angular_units
            <
                Point
            >::type units_type;

        // first compute the envelope range for the first two coordinates
        strategy::envelope::detail::envelope_segment_impl
            <
                geographic_tag
            >::template apply<units_type>(geometry::get<0>(p1_normalized),
                                          geometry::get<1>(p1_normalized),
                                          geometry::get<0>(p2_normalized),
                                          geometry::get<1>(p2_normalized),
                                          box,
                                          azimuth_geographic);

        // now compute the envelope range for coordinates of
        // dimension 2 and higher
        strategy::envelope::detail::envelope_one_segment
            <
                2, dimension<Point>::value
            >::apply(point1, point2, box);
    }

private:
    Spheroid m_spheroid;
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<segment_tag, geographic_tag, CalculationType>
{
    typedef strategy::envelope::geographic_segment
        <
            strategy::andoyer,
            srs::spheroid<double>,
            CalculationType
        > type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope

}} //namepsace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_ENVELOPE_SEGMENT_HPP

/* envelope_segment.hpp
Jybp41zlHHeoaakWvV8PZz37lGncRWYmKnuQPp1yU/3OMCQ1Nu1Aie0q0f/2+qK/vG/FWfMHBcmbgL7DVWAo1hBXD9cA15r/EtfVTJfHnTsrk7fDOSHZQjHncC0cbNRe4pe/TS024/Oz8zWz9Mb0zpLvjZcYkb8u+b5d9EtQ+tFHZqZ6Q+lb5Ny1TbcMB908QXSra8nXTMtcWe4Q6fWsQQF5ie6X4v9CV189i/cvJynTAc7nPizl1OBm+Qa+9Ls74SzqS/ylety6ORZSJAaYyrchZY6Jh433Lz0zrHZZZqXxBWQ9vT0t987le/n1jWfcczzqnF4rvzyJ89n/SpuVMlfPk+bkh+tm4wzFlXG+PEmwfJvZnvZlkvZs6VsycdmkvaCbNe3cD0vJCmF8E/380m6tc6dE3iMi7wGcB3mu7kpe2LKsNmhU2kiczG+JuCX8J8zl2VKRZfn+dRh1PLBcMxy+f+1xsNE21/L9a1t9N94pyJ9zS3nP0iZrPTQ9I687gWW97Ra5p3MBcUEX9JIfyb0kPxzs2K0uJz+KLPkvZ4sdbNkVB7Flt80hn0ocbNnttdiyM/yyrPNOlZ9H/OyMDgjoT5JtZWXZayRuYyyruoy8JL/yKjOW9bG0J8u4J+85vvFcynmc8ZtLinqdVHFuJc6XtOf7++KcpHTOdaf6tdF+Um6db7XfYZ6j9U8D9TiyMjiS4zNXjQmyMtfzYy1tZ7XxrR+tCltkbhWZnXCNcG1xi5HpcZKpH0sOXea8Jsbamr9N7IW6X2q6zz6/pH25Pe038Wyxox7UgyRebmblhayLL/1WuVuX29O/BLmljnJz3QyU7jkR5rv08WIvPM2ix9Db7HosRY/YK3Q9eDUfO2RCQtL4YRMSRg5N8uR4wiz/9j47hmpPZ4muhxZPen52asD7kOjTSN5f68u395KVPhOGJGr1gbLIyipfD/+xofbt9rK+lbgLLHFTxmHUtUtU+qyy5jrIuk2rVxZZ5GcYstoGkXX2dnsZ3qHVJaus/LyMyGRZ56geb25gWu8wYuiAi8G1xq3Q6lC8v3zO++S7Q5bvl69BbTBcaab/DnteL9fuFvnkj09MSEoYPzZx2JBE2pP2zytHjh4WZl3uJToF9mVZd9rlf0ZBFPrk05aHjEwYMWy8biU0jDIf3dBZZqmDzM+RWeIgU09mGDLt58mkr1hhb5tf8OOUg0zVREOQ65+ubSvs6RpDHrgGOcigqZ6PvIy/y95+RjXE30Gm3ozCkKnyUvzkTqi0I6see++yt6ME9Chw0ENvTmHU3dENy29Pg0WPKSvt+bGyCXVL6TGJdYCkYZMSh43Rhye6sXDrWEeHceHFi4KPC/tX2uvF3ehUabBFpzGDrh6mNbGQ9chr5FzX4+621/XZjfC3y1NVPZS6aBnr7ranKR8ZCQ4yqOrlxl1umgrt5Tpeq192eapIQ0mTslnsUKbPuYKX6V7RpweuGa4r7h6tnjnowxtURHqUddZvU5B2mHCPvR3O0zJsiE0vvRmGU+/zGpXfDs382XSPvQ5O0Polix6q+pWrg2Vt5l573VuEoGRr3FS70NO2wJc2az2/117vriEdhVZZUuVCnyNMcNnr23F7H6LSHHufXY+J6HEgQA96+Ih0MMtzrKpX1nxYc5+9Xi1BEddQi3ytSoXV7haEUKfUGL5K7qJImet3b5tQ55UO2nu2tobNuyILAZyE5CxZ6G3vU4f8OKLyQ9peGWPPplX2Or8K/YqC6BfuPMPMh9b32+v/LQgtCSIn3LnGUlUm1vRtu99eBx8gfaeCyI1kbP3UoV30r29vF6pOPGCvl6vRKW6Ys07hzj2WhlA/LzP3F0WXAbhoXG8=
*/