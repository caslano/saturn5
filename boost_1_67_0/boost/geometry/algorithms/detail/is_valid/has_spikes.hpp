// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_SPIKES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_SPIKES_HPP

#include <algorithm>

#include <boost/core/ignore_unused.hpp>
#include <boost/range.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/policies/is_valid/default_policy.hpp>

#include <boost/geometry/util/range.hpp>

#include <boost/geometry/views/closeable_view.hpp>

#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/point_is_spike_or_equal.hpp>
#include <boost/geometry/io/dsv/write.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{

template <typename Point, typename Strategy>
struct equal_to
{
    Point const& m_point;

    equal_to(Point const& point)
        : m_point(point)
    {}

    template <typename OtherPoint>
    inline bool operator()(OtherPoint const& other) const
    {
        return geometry::detail::equals::equals_point_point(m_point, other, Strategy());
    }
};

template <typename Point, typename Strategy>
struct not_equal_to
{
    Point const& m_point;

    not_equal_to(Point const& point)
        : m_point(point)
    {}

    template <typename OtherPoint>
    inline bool operator()(OtherPoint const& other) const
    {
        return ! geometry::detail::equals::equals_point_point(other, m_point, Strategy());
    }
};



template <typename Range, closure_selector Closure>
struct has_spikes
{
    template <typename Iterator, typename SideStrategy>
    static inline Iterator find_different_from_first(Iterator first,
                                                     Iterator last,
                                                     SideStrategy const& )
    {
        typedef not_equal_to
            <
                typename point_type<Range>::type,
                typename SideStrategy::equals_point_point_strategy_type
            > not_equal;

        BOOST_GEOMETRY_ASSERT(first != last);

        Iterator second = first;
        ++second;
        return std::find_if(second, last, not_equal(*first));
    }

    template <typename View, typename VisitPolicy, typename SideStrategy>
    static inline bool apply_at_closure(View const& view, VisitPolicy& visitor,
                                        SideStrategy const& strategy,
                                        bool is_linear)
    {
        boost::ignore_unused(visitor);

        typedef typename boost::range_iterator<View const>::type iterator;

        iterator cur = boost::begin(view);
        typename boost::range_reverse_iterator
            <
                View const
            >::type prev = find_different_from_first(boost::rbegin(view),
                                                     boost::rend(view),
                                                     strategy);

        iterator next = find_different_from_first(cur, boost::end(view),
                                                  strategy);
        if (detail::is_spike_or_equal(*next, *cur, *prev, strategy))
        {
            return
                ! visitor.template apply<failure_spikes>(is_linear, *cur);
        }
        else
        {
            return ! visitor.template apply<no_failure>();
        }
    }


    template <typename VisitPolicy, typename SideStrategy>
    static inline bool apply(Range const& range, VisitPolicy& visitor,
                             SideStrategy const& strategy)
    {
        boost::ignore_unused(visitor);

        typedef typename closeable_view<Range const, Closure>::type view_type;
        typedef typename boost::range_iterator<view_type const>::type iterator; 

        bool const is_linear
            = boost::is_same<typename tag<Range>::type, linestring_tag>::value;

        view_type const view(range);

        iterator prev = boost::begin(view);

        iterator cur = find_different_from_first(prev, boost::end(view), strategy);
        if (cur == boost::end(view))
        {
            // the range has only one distinct point, so it
            // cannot have a spike
            return ! visitor.template apply<no_failure>();
        }

        iterator next = find_different_from_first(cur, boost::end(view), strategy);
        if (next == boost::end(view))
        {
            // the range has only two distinct points, so it
            // cannot have a spike
            return ! visitor.template apply<no_failure>();
        }

        while (next != boost::end(view))
        {
            // Verify spike. TODO: this is a reverse order from expected
            // in is_spike_or_equal, but this order calls the side
            // strategy in the way to correctly detect the spikes,
            // also in geographic cases going over the pole
            if (detail::is_spike_or_equal(*next, *cur, *prev, strategy))
            {
                return
                    ! visitor.template apply<failure_spikes>(is_linear, *cur);
            }
            prev = cur;
            cur = next;
            next = find_different_from_first(cur, boost::end(view), strategy);
        }

        if (geometry::detail::equals::
                equals_point_point(range::front(view), range::back(view),
                                   strategy.get_equals_point_point_strategy()))
        {
            return apply_at_closure(view, visitor, strategy, is_linear);
        }

        return ! visitor.template apply<no_failure>();
    }
};



}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_SPIKES_HPP

/* has_spikes.hpp
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
*/