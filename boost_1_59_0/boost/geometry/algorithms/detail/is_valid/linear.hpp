// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_LINEAR_HPP

#include <cstddef>

#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>

#include <boost/geometry/algorithms/equals.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_invalid_coordinate.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_spikes.hpp>
#include <boost/geometry/algorithms/detail/num_distinct_consecutive_points.hpp>

#include <boost/geometry/algorithms/dispatch/is_valid.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/condition.hpp>


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
        // TODO: Consider checking coordinates based on coordinate system
        //       Right now they are only checked for infinity in all systems.
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
                Linestring, 3u, true
            >::apply(linestring, strategy);

        if (num_distinct < 2u)
        {
            return
                visitor.template apply<failure_wrong_topological_dimension>();
        }

        if (num_distinct == 2u)
        {
            return visitor.template apply<no_failure>();
        }

        // TODO: This algorithm iterates over the linestring until a spike is
        //   found and only then the decision about the validity is made. This
        //   is done regardless of VisitPolicy.
        //   An obvious improvement is to avoid calling the algorithm at all if
        //   spikes are allowed which is the default.
        return ! has_spikes<Linestring>::apply(linestring, visitor, strategy);
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
    template <typename VisitPolicy, typename Strategy>
    struct per_linestring
    {
        per_linestring(VisitPolicy& policy, Strategy const& strategy)
            : m_policy(policy)
            , m_strategy(strategy)
        {}

        template <typename Linestring>
        inline bool operator()(Linestring const& linestring) const
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

        using per_ls = per_linestring<VisitPolicy, Strategy>;

        return std::all_of(boost::begin(multilinestring), 
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