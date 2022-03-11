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
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
*/