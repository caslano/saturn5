// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_STRATEGIES_COMPARE_HPP
#define BOOST_GEOMETRY_STRATEGIES_COMPARE_HPP


#include <algorithm>
#include <cstddef>
#include <functional>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace compare
{


struct less
{
    template <typename T1, typename T2>
    static inline bool apply(T1 const& l, T2 const& r)
    {
        return l < r;
    }
};

struct greater
{
    template <typename T1, typename T2>
    static inline bool apply(T1 const& l, T2 const& r)
    {
        return l > r;
    }
};

struct equal_to
{
    template <typename T1, typename T2>
    static inline bool apply(T1 const& , T2 const& )
    {
        return false;
    }
};


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template
<
    typename ComparePolicy,
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct compare_loop
{
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& left, Point2 const& right)
    {
        typename geometry::coordinate_type<Point1>::type const&
            cleft = geometry::get<Dimension>(left);
        typename geometry::coordinate_type<Point2>::type const&
            cright = geometry::get<Dimension>(right);

        if (math::equals(cleft, cright))
        {
            return compare_loop
                <
                    ComparePolicy,
                    Dimension + 1, DimensionCount
                >::apply(left, right);
        }
        else
        {
            return ComparePolicy::apply(cleft, cright);
        }
    }
};

template
<
    typename ComparePolicy,
    std::size_t DimensionCount
>
struct compare_loop<ComparePolicy, DimensionCount, DimensionCount>
{
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& , Point2 const& )
    {
        // On coming here, points are equal.
        // Return false for less/greater.
        return false;
    }
};

template
<
    std::size_t DimensionCount
>
struct compare_loop<strategy::compare::equal_to, DimensionCount, DimensionCount>
{
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& , Point2 const& )
    {
        // On coming here, points are equal.
        // Return true for equal_to.
        return true;
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template
<
    typename ComparePolicy,
    int Dimension = -1
>
struct cartesian
{
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& left, Point2 const& right)
    {
        return compare::detail::compare_loop
            <
                ComparePolicy, Dimension, Dimension + 1
            >::apply(left, right);
    }
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
template
<
    typename ComparePolicy
>
struct cartesian<ComparePolicy, -1>
{
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& left, Point2 const& right)
    {
        return compare::detail::compare_loop
            <
                ComparePolicy,
                0,
                ((std::min)(geometry::dimension<Point1>::value,
                            geometry::dimension<Point2>::value))
            >::apply(left, right);
    }
};
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{


template
<
    typename ComparePolicy,
    typename Point1,
    typename Point2 = Point1,
    int Dimension = -1,
    typename CSTag1 = typename cs_tag<Point1>::type,
    typename CSTag2 = typename cs_tag<Point2>::type
>
struct default_strategy
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for these types.",
        CSTag1, CSTag2);
};


template <typename ComparePolicy, typename Point1, typename Point2, int Dimension>
struct default_strategy<ComparePolicy, Point1, Point2, Dimension, cartesian_tag, cartesian_tag>
{
    typedef compare::cartesian<ComparePolicy, Dimension> type;
};


} // namespace services


}} // namespace strategy compare


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_COMPARE_HPP

/* compare.hpp
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
*/