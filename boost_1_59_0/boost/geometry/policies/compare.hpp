// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2019.
// Modifications copyright (c) 2017, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_COMPARE_HPP
#define BOOST_GEOMETRY_POLICIES_COMPARE_HPP


#include <cstddef>

#include <boost/geometry/strategies/compare.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{


/*!
\brief Less functor, to sort points in ascending order.
\ingroup compare
\details This functor compares points and orders them on x,
    then on y, then on z coordinate.
\tparam Point the geometry
\tparam Dimension the dimension to sort on, defaults to -1,
    indicating ALL dimensions. That's to say, first on x,
    on equal x-es then on y, etc.
    If a dimension is specified, only that dimension is considered
*/
template
<
    typename Point = void,
    int Dimension = -1,
    typename CSTag = void
>
struct less
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    inline bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::less,
                Point, Point,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension, typename CSTag>
struct less<void, Dimension, CSTag>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    inline bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::less,
                Point1, Point2,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <typename Point, int Dimension>
struct less<Point, Dimension, void>
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    inline bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::less,
                Point, Point,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension>
struct less<void, Dimension, void>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    inline bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::less,
                Point1, Point2,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};


/*!
\brief Greater functor
\ingroup compare
\details Can be used to sort points in reverse order
\see Less functor
*/
template
<
    typename Point = void,
    int Dimension = -1,
    typename CSTag = void
>
struct greater
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::greater,
                Point, Point,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension, typename CSTag>
struct greater<void, Dimension, CSTag>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::greater,
                Point1, Point2,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <typename Point, int Dimension>
struct greater<Point, Dimension, void>
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::greater,
                Point, Point,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension>
struct greater<void, Dimension, void>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::greater,
                Point1, Point2,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};


/*!
\brief Equal To functor, to compare if points are equal
\ingroup compare
\tparam Geometry the geometry
\tparam Dimension the dimension to compare on, defaults to -1,
    indicating ALL dimensions.
    If a dimension is specified, only that dimension is considered
*/
template
<
    typename Point,
    int Dimension = -1,
    typename CSTag = void
>
struct equal_to
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::equal_to,
                Point, Point,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension, typename CSTag>
struct equal_to<void, Dimension, CSTag>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::equal_to,
                Point1, Point2,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <typename Point, int Dimension>
struct equal_to<Point, Dimension, void>
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::equal_to,
                Point, Point,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension>
struct equal_to<void, Dimension, void>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::equal_to,
                Point1, Point2,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_POLICIES_COMPARE_HPP

/* compare.hpp
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
*/