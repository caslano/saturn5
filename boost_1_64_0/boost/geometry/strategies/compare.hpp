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
NDFt47+Wafvx4wH37JHEgdG3/mIsX035ZOlIbVW6SqbsS/4xMnE/+YsPZM5U1ufPjUjMH1IlO/0Ssi/m7Hbuv74vcvctjw3JokleKvP1Xl5+YnlX91meCeDVQGJ975D17QvfFQENX29q+M7iPFrrxFyp0qdYL++GWErlfTw8obxzZb4+15P6yoTMhA+X6/2zpP4QqODxZX3jG+d61oKX6QLK7O2CEeLb2QL4vULVj28wF+5ShoyVrkMWnhqQgcmZytNk5HMyNzpzwcVQTzv4FQgm071KjZmMfUFIpxFSACFk7Z4jhI2rhoEdHMzXttGEpDIVndY1V2gllMhBsESoV/LsezmOmXOH2bVvifg8dBvjVLb4hQNx5eRfqLrOPtDW0vvAw361RqvbdYOVkv23u+gg7AAAbRRYP5KwYcVJqQqBmnYtG72h87aEjthYjyi9XWBeMIZJw2vFZYglQyyzavBR6ag8UQJKDRhpxFgyxgRSidhQtSle1fyyQq655gWhs8ih5hdGqeYjCnj1VUm48sZD0T9ge93w0N2fy4aKJmB9uQI334ixtNCONgyNej+Ox9kFcI1J2BEOhOXppWVjpqRrx1AHuqoQS4UksgyUBl9pzvokTESVJhUiy9SeFCB6UobouLKo6bOIVMDzPk+1xXJsCx6oPgK1UILj3NBs3YH71Dlme2JodMpfZXvWokvnWsRlno83n8xsBwu7+iMdmG3Xn4jZHgODRalxQy1wQ5rkhgWDU+KG7GRK1yKFe6arTJISaekLDafVtvmM1iMlHo3mJR5J8wWgeEtlJNKcbF4QrXOJarxSJocb+oi96Ieo8cNX7xDDuUToY5nQfw04EPr77xChj8tPJHSRI6FZ7Uin9aD8lGg9IGmwJkh9kZtT9ZPijGQS0RkWX1+RBM9GZWUV48znKPHAXiGMUeAtgG305G9tEtlxvUsu9nflUUtQyt2LZEuczy1RO9yhJTLeppbYmJfYEqN7aIltvC3JTJdNsSQvpaZIIhp/eZWlD5hp35S3zsByC38RHflVKpoxCH5X1zTLOI2/pY1uSnhdfPlspc6mtY/QWdAsiZq8Q6pSsiCK7qDKovlVVSblHF1HyJUCZTHUFKUFDTbVxxXqnR1VshT5kTOkArNf8BI5Va3YnmTHAUvcckBmXx8Nx2mDdh0WEi7jEF2bPUARAT2CH3JZWd3loQATlH/xOy4jdAXP8i9RqIKFoahAAzGPJcf4n+QS4FqEl+TwlYVuYdhzxnbJOrofQPpyrgJ1wCv8yaWbQISsvNoH30S9+ACLsySbFS+2pK3zapdtYfywxEqHD3CoMK6DPnGlOpFVw+DqlT36sYEp9ehRyT26uo9ZrDo1hqN6zj1cq5VGueUYxOPo81nCOqvzIOpsjijfXDJ6cHtS2+v2ZL1s9GTvbo8Z3t0Ctnc3joKhGB+f78ZbHg0WD9+YeZ2lj0zfGMqmnRpTa6xGaCw1/GbkpNRYOQ7DL2uaq4GY56sqlHAykuaKvSlTIYn/eh606kSDNjqPWCq+DuMVDo19QksdUg/c0BIpckPT+VvvwqWPurTs7GlHW1nOdON97w+Ezx24LpEc+/4HvOncLqdmeov+GMYopeO+CJtr5gDeyATV/YxllZZbmhHqmk/ThureNdS9v4oQVXkYFh0DgE3l+XiWACyv4ceyE80fNCUbNJi2Q6rcPpOVOFYc5rwCEGBuYDDLqgap7dD8rJRYMS2RFRlLjSC+3rZGTulT3ybBpsYyVmhEmL5ny6ZUZ8tUeGng+8xL/mX3SNVWaS/Sibmufd9mLrMwcq2uuG0CeIiQF+ccNu5sgQAQxnizKlokFE6vXAa/d00UbNnWN6E=
*/