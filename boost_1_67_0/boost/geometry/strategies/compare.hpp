// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_STRATEGIES_COMPARE_HPP
#define BOOST_GEOMETRY_STRATEGIES_COMPARE_HPP


#include <cstddef>
#include <functional>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/min.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>

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
                boost::mpl::min
                    <
                        geometry::dimension<Point1>,
                        geometry::dimension<Point2>
                    >::type::value
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
    BOOST_MPL_ASSERT_MSG
        (
            false,
            NOT_IMPLEMENTED_FOR_THESE_TYPES,
            (types<CSTag1, CSTag2>)
        );
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