// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISJOINT_BOX_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISJOINT_BOX_BOX_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/disjoint.hpp>


namespace boost { namespace geometry { namespace strategy { namespace disjoint
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template
<
    typename Box1, typename Box2,
    std::size_t Dimension = 0,
    std::size_t DimensionCount = dimension<Box1>::value
>
struct box_box
{
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        if (get<max_corner, Dimension>(box1) < get<min_corner, Dimension>(box2))
        {
            return true;
        }
        if (get<min_corner, Dimension>(box1) > get<max_corner, Dimension>(box2))
        {
            return true;
        }
        return box_box
            <
                Box1, Box2,
                Dimension + 1, DimensionCount
            >::apply(box1, box2);
    }
};


template <typename Box1, typename Box2, std::size_t DimensionCount>
struct box_box<Box1, Box2, DimensionCount, DimensionCount>
{
    static inline bool apply(Box1 const& , Box2 const& )
    {
        return false;
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


struct cartesian_box_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return detail::box_box<Box1, Box2>::apply(box1, box2);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


namespace services
{

template <typename Box1, typename Box2, int TopDim1, int TopDim2>
struct default_strategy<Box1, Box2, box_tag, box_tag, TopDim1, TopDim2, cartesian_tag, cartesian_tag>
{
    typedef disjoint::cartesian_box_box type;
};


} // namespace services


#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}}}} // namespace boost::geometry::strategy::disjoint


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISJOINT_BOX_BOX_HPP

/* disjoint_box_box.hpp
nMMD22r8+gVeJddzzv26487TrzuqhH7d0Q7HhX/bYasEvYL7ZTzGa4SJ6vpnqUM5UWOosipLX0nndi7rcSXXJKMpJ/Kg6ubrdJpyDXS+9jl5JiJ5f1bua1V9n6zGcSzzz7vcr5cj33KeDOjfaR4LgeejwO0beF/LfObYGyn/xDH+Y5mlnf16yzpk09PzAp65WdsAtks6VTRGf5JbSWe3JR1zbXjrnZtmw1L7j1jjT0rUfzDO/dJWN0W11VviZw8yN2Z3SqLUto/63uMj8Phq57vmkRrdN0Z6ahNjfqOBy5rHA5LHJGkfG6PSUGW93JbHXLKnEytDHgPbPgPbCq3bO3qsXniQbO9+sr13+/JgDHO7kGes1mOj7jg94z3yfoB1eKVqi7rBlw7NJXqDqDvDi3hWaN7DFBT46v32AXWYjJWpYq+PAs/hsoy+DLCt005ZpxvlvRwrCdNVu8JK+zr5HtOXvw+Uyn+Y5N+/Pm1oy7/8yS+P28bryFtLu1EEpqrjwJLH7Ly82UXGnUTZ6iRpu7GOsVc7qTE9zv6eBWO61FHW6eYyTv0i/Oopc1b/48+MXsaXm++hSPLfn6X/+k2+9WXEdLn3ZXVuz9dxuLLq2uuahhPkvUmVdJo70OiTZ0mTVo90dkizba7UZ11O7TTt7M++pLyd77WiznOvbJ7XF5rPyBiSXLb2UX3/Z1333bLudeS6piZG1+Mft/jW3WgtkhW/mHO1X98Z63nP6Ogj1y/metquK3pOlLFIsl/slXoudY0ln+5C3apilCRP+C8gr7Y24kl6xlVy7N2AM9T1wK22NKXmKf16T+5L5N1ZHi4+LWP+qpjT5P1Ztu8Amin4t93mev9Q29Z+nq4qK8d7HmNsui5zqgxjNtnfzGU9ejzNRP19lmeY/qWxvr7zZAvZl4yH5I7PwQKffUZLwTxO6EK4i5ChrgtvdypLI2NGee4tZQzZdss7JPY7lO2BgLKVfpT+72iRsgpuost1ht8zztDJLpehHCfBOJN5I9fa88/5PqssfRekDna81o/zv9a3HNv9Gur+Y65Snj9Oraemzcr3+F2fb5f1WCH9MJbK+KDiO6zrYXajM4/6spzLK4d/9Ttpv8rP9z+3B9Rpgf2kre2o+ts8Rn6lTt4mdbLnTr98Wh+ZlOFeWOVjjd/52RPwLESejwc+3/Cry9LzcmfqaZn25yZy7Nnr7NTA5yjSfh/4fEb6MEgavv022lfvGyts3q8Vmf3ZdLOErR5rNU0XwEmpx77CLHUNsd5WluV47lQ5fOsG+7ZOta6rlMcs41jyyI2KtazN/EtZ2/pJ6acC/NNvfGYBZ7mAcVfEnSt1eEnv1pF3YNnqOFlTv2Pj2LTAOmq26jt2j2M5Se0p+1yl89dTHv5OPaX3v0r2dtN1lax1kbTNVCq5PKo2kXXwO5cvm64T/bIScaj1wX78JWKjN/9yvEhDm+vCjpd1Urb+x4U8Z5R+2HrZZOt1jO0YuEr2E2ubQsDzSZluxCd1m/VY8R8LqcdXHZ/GOk/X974Fet2l7ALb4cz5i5m/GjN+vIn5A47zQpUBPVab+RYT+vG3rZt98yY6n/9sYxoTU+W9y8F63UIwRx2H95rbxzZuLXBsZpm2V+Xw/VvtzxEC+2Gb7X7ELPdL241pct9ltNb5zic78fZ61nGO1vY7RvilZacQU2Db4Vxpa7KMvXbTGiBtjbI/eOsuY94B1v5pvpl1/321TVngV1buuS1S9oH9xWV8XmC/7n0prCPLjwiiPO7Ty0vdYebZbz92q/Rt27KfeX6SbflXaSva49LXzdvvN7elPsbMB9IX03fW0kYt15CBz6kj/doprHntmS59HSrrcfw=
*/