// Boost.Geometry Index
//
// R-tree strategies
//
// Copyright (c) 2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_INDEX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_INDEX_HPP


#include <boost/geometry/strategies/cartesian/box_in_box.hpp>
#include <boost/geometry/strategies/cartesian/disjoint_box_box.hpp>
//#include <boost/geometry/strategies/cartesian/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/cartesian/distance_projected_point.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras_point_box.hpp>
#include <boost/geometry/strategies/cartesian/distance_segment_box.hpp>
#include <boost/geometry/strategies/cartesian/envelope_box.hpp>
#include <boost/geometry/strategies/cartesian/envelope_point.hpp>
#include <boost/geometry/strategies/cartesian/envelope_segment.hpp>
#include <boost/geometry/strategies/cartesian/expand_box.hpp>
#include <boost/geometry/strategies/cartesian/expand_point.hpp>
#include <boost/geometry/strategies/cartesian/expand_segment.hpp>
#include <boost/geometry/strategies/cartesian/intersection.hpp>
#include <boost/geometry/strategies/cartesian/point_in_box.hpp>
#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_winding.hpp>

#include <boost/geometry/strategies/index.hpp>


namespace boost { namespace geometry { namespace strategy { namespace index
{

template
<
    typename CalculationType = void
>
struct cartesian
{
    typedef cartesian_tag cs_tag;

    typedef geometry::strategy::envelope::cartesian_point envelope_point_strategy_type;
    typedef geometry::strategy::envelope::cartesian_box envelope_box_strategy_type;
    typedef geometry::strategy::envelope::cartesian_segment
        <
            CalculationType
        > envelope_segment_strategy_type;

    static inline envelope_segment_strategy_type get_envelope_segment_strategy()
    {
        return envelope_segment_strategy_type();
    }

    typedef geometry::strategy::expand::cartesian_point expand_point_strategy_type;
    typedef geometry::strategy::expand::cartesian_box expand_box_strategy_type;
    typedef geometry::strategy::expand::cartesian_segment expand_segment_strategy_type;

    static inline expand_segment_strategy_type get_expand_segment_strategy()
    {
        return expand_segment_strategy_type();
    }

    typedef geometry::strategy::covered_by::cartesian_point_box covered_by_point_box_strategy_type;
    typedef geometry::strategy::covered_by::cartesian_box_box covered_by_box_box_strategy_type;
    typedef geometry::strategy::within::cartesian_point_point within_point_point_strategy_type;
    /*
    typedef geometry::strategy::within::cartesian_point_box within_point_box_strategy_type;
    typedef geometry::strategy::within::cartesian_box_box within_box_box_strategy_type;
    typedef geometry::strategy::within::cartesian_winding
        <
            void, void, CalculationType
        > within_point_segment_strategy_type;

    static inline within_point_segment_strategy_type get_within_point_segment_strategy()
    {
        return within_point_segment_strategy_type();
    }
    */
    
    // used in equals(Seg, Seg) but only to get_point_in_point_strategy()
    typedef geometry::strategy::intersection::cartesian_segments
        <
            CalculationType
        > relate_segment_segment_strategy_type;

    static inline relate_segment_segment_strategy_type get_relate_segment_segment_strategy()
    {
        return relate_segment_segment_strategy_type();
    }
    
    // used in intersection_content
    typedef geometry::strategy::disjoint::cartesian_box_box disjoint_box_box_strategy_type;
    
    typedef geometry::strategy::distance::comparable::pythagoras
        <
            CalculationType
        > comparable_distance_point_point_strategy_type;

    static inline comparable_distance_point_point_strategy_type get_comparable_distance_point_point_strategy()
    {
        return comparable_distance_point_point_strategy_type();
    }

    typedef geometry::strategy::distance::comparable::pythagoras_point_box
        <
            CalculationType
        > comparable_distance_point_box_strategy_type;

    static inline comparable_distance_point_box_strategy_type get_comparable_distance_point_box_strategy()
    {
        return comparable_distance_point_box_strategy_type();
    }

    // TODO: comparable version should be possible
    typedef geometry::strategy::distance::projected_point
        <
            CalculationType,
            geometry::strategy::distance::pythagoras<CalculationType>
        > comparable_distance_point_segment_strategy_type;

    static inline comparable_distance_point_segment_strategy_type get_comparable_distance_point_segment_strategy()
    {
        return comparable_distance_point_segment_strategy_type();
    }

    typedef geometry::strategy::distance::cartesian_segment_box
        <
            CalculationType,
            geometry::strategy::distance::pythagoras<CalculationType>
        > comparable_distance_segment_box_strategy_type;

    static inline comparable_distance_segment_box_strategy_type get_comparable_distance_segment_box_strategy()
    {
        return comparable_distance_segment_box_strategy_type();
    }
};


namespace services
{

template <typename Geometry>
struct default_strategy<Geometry, cartesian_tag>
{
    typedef cartesian<> type;
};


// within and relate (MPt, Mls/MPoly)
template <typename Point1, typename Point2, typename CalculationType>
struct from_strategy<within::cartesian_winding<Point1, Point2, CalculationType> >
{
    typedef strategy::index::cartesian<CalculationType> type;

    static inline type get(within::cartesian_winding<Point1, Point2, CalculationType> const&)
    {
        return type();
    }
};

// distance (MPt, MPt)
template <typename CalculationType>
struct from_strategy<distance::comparable::pythagoras<CalculationType> >
{
    typedef strategy::index::cartesian<CalculationType> type;

    static inline type get(distance::comparable::pythagoras<CalculationType> const&)
    {
        return type();
    }
};

// distance (MPt, Linear/Areal)
template <typename CalculationType, typename PPStrategy>
struct from_strategy<distance::projected_point<CalculationType, PPStrategy> >
{
    typedef strategy::index::cartesian<CalculationType> type;

    static inline type get(distance::projected_point<CalculationType, PPStrategy> const&)
    {
        return type();
    }
};


} // namespace services


}}}} // namespace boost::geometry::strategy::index

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_INDEX_HPP

/* index.hpp
/XpP3qHHERbXez2U8o09sTsG4XDsZTiPr5bpn5PjqPE8vg3LaYb9cQsOwG14GW7HYOP1/iXqfObLfIzn8Z/LefwX2B9/xFT0lvsJPujAZjK/QC95Nx0vUcuvWufK/CKausYrbOB4lTJeQD3jHW/g/NR3r8mbesaLkvH61bcePete7nXG9XCfn/V4bGzX/KLcxhvv5RovOEjmV894dhkvwGK8eC/DemjLrWe8Shmvfz3jefVq2HhhvRq2XLuM1+9nxotqIu9lqu9rUp7V+07hqPzc3tIrryfe/Q/27gVMqzGBA/h0lZSuShephLTdkWpFNxqpFEWb6DbTTZdpZlIRyq2oiEIsSdKmootoSlLpToR2RS5FKXSTlpDs75vvnWm+aXZlb8/us+t5/n7NN2e+c8573vOe853vPe/hhRzLrryPybyfD3M8p/EBzuJErudD3MtHeJiTGDnv/j0L83GewifYgJPZgk+yDaeyM5/mUE7j/ZzDeZzLNziPmzifn/IF7uSLzGNdFrIYX2IVLuFgLuUdfJWzuIyruJyfcAW3cyW/4iqWy+P4xopcwwSuYzLXcwg38FG+yxe5iQv5Hj/iB9zLLSye13kbK/JjnsmtvIjb2Iw72Iu7OZR7+Dj3cSb3cw4PcAG/5UF+x8M8xCK27/c8lz+wCX9kMx5hPH9mJ/owOqI3c3Esc/M+5uNk5uczLMA5PJHzWJDR5xGF+0f5sGzM9jyi0+2/pVmRp7Myq7EKr+ZZTORv2J/VOZQ1eBNrchzr8AHW5QGOjgv3hPLWcN56sn8PD/OtFylvNubZbMIObMpObM7b2YJTeRnLeJ/LeRFbM4Ft2JNt2Z9XcQjbcxg70PI4mIV7PMO9n5Yn/XpNajhvef6E6PLMYzm+yFpcyF5czFS+zHu5hFP4Cl/kUr7KZdzKFfySrzFfLvWVJbia9biWN3Mdx3M9p3ADZ/BNvsS3uJxv812+wy18lzu5iUWsyx9ZmX9iXb7HvtzM+/g+J3AL1/FDnpxHfedp/Jg1+AkbcSub8jMO5Xa+ws/5BXeysHLcxSL8ilW5h7W4jxdyPy/i14x+jg73dHJgDp+j64XrLRfwXNbnNWzAbmzIRDZiX16UcfzJk3mPpns3o+8bmb5keDbDvSdpbziGNTiW9TiOF3MCr+ajTOJkjuSTvI9T+BCncgGf5hJO4zo+w42cwQ/4LLdzJg9yFk+1cLN5GufwbM5lc87jZXyJV3MhBzKNQ7iIw7mYo7mEk/gKn+VSvsBXmcblXMEV/CNf4ydcye1czb3cyFrKahPP45/YnVs4lB9xEbdyJbcx8p37p2zJz5jGHUyvH9zEnfyYu7iLX/AAv+L33M0j3MNC6sdeFuM+VuDXrMUDbM5veBkPcgS/5V38jkv4A5fzR+5g3kL2g/zqFhvzRLZmQSbyJKawMMfxZE5lUa5hMb7B4tzGEvyeJXmEp7CEiluaF/NUNmcZdmFZJrA8B/A0DmUFjuTpvJeV+BSr8H2exRPV37PZnlU5gufwdlbjo6zOKazJhazF5azN11mHm1mXH/BchusJ4R5TdTOH62g3Kr/iHMZKvInn8Ga25nBew1t4LUdwAEfyQd7Ox3kHp/BuPsNRjF7nDPeU8qkcrnNWyx+d/29Yj9XZiTWYwJrszTq8hXU5jufyEV7Ax1mf6e1Nrox7R617+Lx6dqS9Ce3+hnzR+b3NstzE6nyP1/N9DucHfJxbuZzb+Ba/YYFc6iPL8RBr8nuezx/4O/7IHjzMvjzCO/gzZzDO8r7CPPyYefkNC/LEyDGbFVmYLVmUHVmMw1mcd7MEx7E0l/BUbmQZHmRZHmE55lYep7MUK/JCVmJXVmZfnsE=
*/