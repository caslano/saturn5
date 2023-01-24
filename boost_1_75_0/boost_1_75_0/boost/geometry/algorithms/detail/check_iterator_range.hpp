// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CHECK_ITERATOR_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CHECK_ITERATOR_RANGE_HPP

#include <boost/core/ignore_unused.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// Check whether (each element of) an iterator range satisfies a given
// predicate.
// The predicate must be implemented as having a static apply unary
// method that returns a bool.
// By default an empty range is accepted
template <typename Predicate, bool AllowEmptyRange = true>
struct check_iterator_range
{
    template <typename InputIterator>
    static inline bool apply(InputIterator first, InputIterator beyond)
    {
        for (InputIterator it = first; it != beyond; ++it)
        {
            if (! Predicate::apply(*it))
            {
                return false;
            }
        }
        return AllowEmptyRange || first != beyond;
    }


    // version where we can pass a predicate object
    template <typename InputIterator>
    static inline bool apply(InputIterator first,
                             InputIterator beyond,
                             Predicate const& predicate)
    {
        // in case predicate's apply method is static, MSVC will
        // complain that predicate is not used
        boost::ignore_unused(predicate);

        for (InputIterator it = first; it != beyond; ++it)
        {
            if (! predicate.apply(*it))
            {
                return false;
            }
        }
        return AllowEmptyRange || first != beyond;
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CHECK_ITERATOR_RANGE_HPP

/* check_iterator_range.hpp
N94DZRVktvP26JHEiKNl1MGj1ffS52tQtt517NB71v1GtNl2IFpEXZ/8DZOnt8KQoczOSvwIvpU8/a3fiLPBB0B8Ain7WS5P/zjLlKfjZ5k8veezSXn6YFNDyuTpl1zy28QnDWFYbJnMriaDxfJk+j94KjICLuMhSZrmyUYxCpBWWhgFEj8rIWFvWw/P1bhQehz6xZtarkfLWwHFJNbDZRukvbRM1r4C6+TxZ9nHl0PR0iq8jxSnxv96tpO/yiX4gTTh8d3wO+iY7f5ekAkf422ddcw5Lp7Fb3d3fht5rNOaPO4Y8yeaDY02tptnFhzrJLddxp+Z4Xgmk/sJHBD+T8dsa91RyLwi6nqiU10HU19XWlJJF5lLh/29MyNw5qXv3cjuzqfjntpav9sLzr0qyq7qCedeyM/P6qD9EzkO/T0ELonjdOw3/I6gUmUD5j4qeve66JrjNl30PZD5n+NcF91wnOmiHz6eHH2DHLroK1Q/P5frcjrN5yPHbd9xCjJvHudtcea4sy1OSu8lfWg6lXHDXkbGb0Mo8FteRuZvnWW0YIbH4ZD//JbKf+Dyg9/Ssc/kP3UfmCHCGyRH/Mvf0viXtMxyYZvG+4P5P8PPiYfhshbSE7818X2a+ZjfbFWkejEM/LepiRFJ5aP/wm/F2HgDiA5aTqvNR59rfy1OvJr56H9ulc7EJtvTPdRHv0weqeTJRdIC0w2RtR3T
*/