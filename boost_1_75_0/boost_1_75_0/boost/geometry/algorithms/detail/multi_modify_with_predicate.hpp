// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_WITH_PREDICATE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_WITH_PREDICATE_HPP


#include <boost/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename MultiGeometry, typename Predicate, typename Policy>
struct multi_modify_with_predicate
{
    static inline void apply(MultiGeometry& multi, Predicate const& predicate)
    {
        typedef typename boost::range_iterator<MultiGeometry>::type iterator_type;
        for (iterator_type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, predicate);
        }
    }
};


} // namespace detail
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_WITH_PREDICATE_HPP

/* multi_modify_with_predicate.hpp
n6/HOP6sV/cbwZhREdYjvhw9okcppj/VF9RkctnyWn4CYPz/P8ReexMI9fMQCkOSTZ89tmrVwc4ruT93qpVuurTTuFUaSyp4qNx/ZuMy6XNh4zITiKFfhNAYSKXJfuRT0Np1RIdNJ2JXYsOb2OMyCJezJTwYROsOi/Mc4RDgp7necPG+51HQXUXWFmzufbyMEN4tOr9bNUCI2MdYay2fSzv4XLqsYlxcMvwL2yRaCmNgVGztQIxfhg28UJmmTtESeofR7FmJ8z0l7rFGUH87WuEpcO/07vaV+ssCZcEROHDEXRndEhmbOzonEU7oM2BhqQL2Ix6NRXbGWvJK88sKyuLbCicn4kX5iV3Fa0oSiXBhJL6jYF+kNT4Zlh6PEqCW0FE6EqgGPQAjQM/XC/S4r1AvNkqoABqhbmMaky9tMY0zIfOtL/kanP2l0/BtuEu7/n+IaVz1pW1Nnw6Zn4ry7v7SuaafwNoLzlDG3dZxl72OhyDzkijzWKc67nVp7+ByUgU83Cyzjil8kT631zH9qxDq9xUvr9dXzjqmu7QWKK8MdtIZZh1T2NjOGSViMXbybaj+yqY3mAuZpV/x8/u9nd6zU3o+6adMMV/e7YOyagyUFc9EWecyO5j/91fCRvwoEH+E9PFXZvw0B7/pwDLi8dP+bL2NaV/Te3iP4+fk5co2tUjOkypJGC2AYWRweRCLf0BjdinImC/iH9wQ
*/