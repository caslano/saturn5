// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_LINEAR_HPP

#include <cstddef>

#include <boost/range.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>

#include <boost/geometry/algorithms/equals.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_invalid_coordinate.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_spikes.hpp>
#include <boost/geometry/algorithms/detail/num_distinct_consecutive_points.hpp>

#include <boost/geometry/algorithms/dispatch/is_valid.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{


template <typename Linestring>
struct is_valid_linestring
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Linestring const& linestring,
                             VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        if (has_invalid_coordinate<Linestring>::apply(linestring, visitor))
        {
            return false;
        }

        if (boost::size(linestring) < 2)
        {
            return visitor.template apply<failure_few_points>();
        }

        std::size_t num_distinct = detail::num_distinct_consecutive_points
            <
                Linestring,
                3u,
                true,
                not_equal_to
                    <
                        typename point_type<Linestring>::type,
                        typename Strategy::equals_point_point_strategy_type
                    >
            >::apply(linestring);

        if (num_distinct < 2u)
        {
            return
                visitor.template apply<failure_wrong_topological_dimension>();
        }

        if (num_distinct == 2u)
        {
            return visitor.template apply<no_failure>();
        }

        return ! has_spikes
                    <
                        Linestring, closed
                    >::apply(linestring, visitor,
                             strategy.get_side_strategy());
    }
};


}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// A linestring is a curve.
// A curve is 1-dimensional so it has to have at least two distinct
// points.
// A curve is simple if it does not pass through the same point twice,
// with the possible exception of its two endpoints
//
// There is an option here as to whether spikes are allowed for linestrings; 
// here we pass this as an additional template parameter: allow_spikes
// If allow_spikes is set to true, spikes are allowed, false otherwise.
// By default, spikes are disallowed
//
// Reference: OGC 06-103r4 (6.1.6.1)
template <typename Linestring, bool AllowEmptyMultiGeometries>
struct is_valid
    <
        Linestring, linestring_tag, AllowEmptyMultiGeometries
    > : detail::is_valid::is_valid_linestring<Linestring>
{};


// A MultiLinestring is a MultiCurve
// A MultiCurve is simple if all of its elements are simple and the
// only intersections between any two elements occur at Points that
// are on the boundaries of both elements.
//
// Reference: OGC 06-103r4 (6.1.8.1; Fig. 9)
template <typename MultiLinestring, bool AllowEmptyMultiGeometries>
class is_valid
    <
        MultiLinestring, multi_linestring_tag, AllowEmptyMultiGeometries
    >
{
private:
    template <typename VisitPolicy, typename Strategy>
    struct per_linestring
    {
        per_linestring(VisitPolicy& policy, Strategy const& strategy)
            : m_policy(policy)
            , m_strategy(strategy)
        {}

        template <typename Linestring>
        inline bool apply(Linestring const& linestring) const
        {
            return detail::is_valid::is_valid_linestring
                <
                    Linestring
                >::apply(linestring, m_policy, m_strategy);
        }

        VisitPolicy& m_policy;
        Strategy const& m_strategy;
    };

public:
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(MultiLinestring const& multilinestring,
                             VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        if (BOOST_GEOMETRY_CONDITION(
                AllowEmptyMultiGeometries && boost::empty(multilinestring)))
        {
            return visitor.template apply<no_failure>();
        }

        typedef per_linestring<VisitPolicy, Strategy> per_ls;

        return detail::check_iterator_range
            <
                per_ls,
                false // do not check for empty multilinestring (done above)
            >::apply(boost::begin(multilinestring),
                     boost::end(multilinestring),
                     per_ls(visitor, strategy));
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_LINEAR_HPP

/* linear.hpp
vhnRx3YUfhM3G2fcaC2XOVmVwHKeLdKju+Mi/XbyCPoxy5kVQOf2GIwQ8Jz5RWYaGcpJT0MnnhWYkf1VQomBVD1iDvPi86qxh6usGNXUZrylU6jmn0KPXnXDdfgyLhRr5VmKXz5kuVudbi2z9TtgiXAU2WfZinL9tgZHrn2jq81d7tmXujK9z1uIc7134cxy32n/Gpzl/xxnzc0uyPkQZ6/22TLzvUT5npD+qdZ81UbNEpM7rQ/7PPxds319YG2eP39OQWXh9qLyYE5J9fR7cNnu8oqKwnJP2dzpC0srgsGiYjyrsfIFXPXirOaimoL8/Pw8W0yS9+HK6dVZNStrX6zOr9w2TKSV1duK5sV98zXKo8q0HgtBeOlN7S52y5onU/V7s9UAlVkpJC2iTleL1Eq1Sq39BzbL1r7N9eXvBc+r4D5523CHAutQI6GtD6fQEKKbj84edofC22/rWMqZsw40JaX5bVwuVgtZ+E4pJGdDjQqVUpmt0qWWaiWL++epa6zZ0LksNN1G7qbTQg32NAwLfL7FBo/8oo3e8hbAy9kdg9S0pYvTZeOGpctW/InvtbeB5+SfIrp12uEALSzS07BuPYKtxlzC0XBRuNE6B1d6yxkEwnCpUC0FgPLcKneJqwRi5UXNty+x5Vqz1F3iLKsN0Hw3oDGpxHqJzHnro+Py1lMHM9BqKv8LnrpBci8vPXMN6JpwdQ06bjAw
*/