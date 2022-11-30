// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_SPIKES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_SPIKES_HPP

#include <algorithm>

#include <boost/core/ignore_unused.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>

#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/point_is_spike_or_equal.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/io/dsv/write.hpp>

#include <boost/geometry/policies/is_valid/default_policy.hpp>

#include <boost/geometry/util/range.hpp>
#include <boost/geometry/util/type_traits.hpp>

#include <boost/geometry/views/closeable_view.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{


template <typename Range>
struct has_spikes
{
    template <typename Iterator, typename Strategy>
    static inline Iterator find_different_from_first(Iterator first,
                                                     Iterator last,
                                                     Strategy const& strategy)
    {
        if (first == last)
            return last;
        auto const& front = *first;
        ++first;
        return std::find_if(first, last, [&](auto const& pt) {
            return ! equals::equals_point_point(pt, front, strategy);
        });
    }

    template <typename View, typename VisitPolicy, typename Strategy>
    static inline bool apply_at_closure(View const& view, VisitPolicy& visitor,
                                        Strategy const& strategy,
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
        if (detail::is_spike_or_equal(*next, *cur, *prev, strategy.side()))
        {
            return ! visitor.template apply<failure_spikes>(is_linear, *cur);
        }
        else
        {
            return ! visitor.template apply<no_failure>();
        }
    }


    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Range const& range, VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        boost::ignore_unused(visitor);

        bool const is_linestring = util::is_linestring<Range>::value;

        detail::closed_view<Range const> const view(range);

        auto prev = boost::begin(view);
        auto const end = boost::end(view);

        auto cur = find_different_from_first(prev, boost::end(view), strategy);
        if (cur == end)
        {
            // the range has only one distinct point, so it
            // cannot have a spike
            return ! visitor.template apply<no_failure>();
        }

        auto next = find_different_from_first(cur, boost::end(view), strategy);
        if (next == end)
        {
            // the range has only two distinct points, so it
            // cannot have a spike
            return ! visitor.template apply<no_failure>();
        }

        while (next != end)
        {
            // Verify spike. TODO: this is a reverse order from expected
            // in is_spike_or_equal, but this order calls the side
            // strategy in the way to correctly detect the spikes,
            // also in geographic cases going over the pole
            if (detail::is_spike_or_equal(*next, *cur, *prev, strategy.side()))
            {
                return
                    ! visitor.template apply<failure_spikes>(is_linestring, *cur);
            }
            prev = cur;
            cur = next;
            next = find_different_from_first(cur, boost::end(view), strategy);
        }

        if (equals::equals_point_point(range::front(view), range::back(view),
                                       strategy))
        {
            return apply_at_closure(view, visitor, strategy, is_linestring);
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