// Boost.Geometry Index
//
// R-tree R*-tree next node choosing algorithm implementation
//
// Copyright (c) 2011-2019 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2021.
// Modifications copyright (c) 2019-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_RSTAR_CHOOSE_NEXT_NODE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_RSTAR_CHOOSE_NEXT_NODE_HPP

#include <algorithm>

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/algorithms/expand.hpp>

#include <boost/geometry/index/detail/algorithms/content.hpp>
#include <boost/geometry/index/detail/algorithms/intersection_content.hpp>
#include <boost/geometry/index/detail/algorithms/nth_element.hpp>
#include <boost/geometry/index/detail/algorithms/union_content.hpp>

#include <boost/geometry/index/detail/rtree/node/node.hpp>
#include <boost/geometry/index/detail/rtree/options.hpp>
#include <boost/geometry/index/detail/rtree/visitors/insert.hpp>
#include <boost/geometry/index/detail/rtree/visitors/is_leaf.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

template <typename MembersHolder>
class choose_next_node<MembersHolder, choose_by_overlap_diff_tag>
{
    typedef typename MembersHolder::box_type box_type;
    typedef typename MembersHolder::parameters_type parameters_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef typename rtree::elements_type<internal_node>::type children_type;
    typedef typename children_type::value_type child_type;

    typedef typename index::detail::default_content_result<box_type>::type content_type;

public:
    template <typename Indexable>
    static inline size_t apply(internal_node & n,
                               Indexable const& indexable,
                               parameters_type const& parameters,
                               size_t node_relative_level)
    {
        ::boost::ignore_unused(parameters);

        children_type & children = rtree::elements(n);
        
        // children are leafs
        if ( node_relative_level <= 1 )
        {
            return choose_by_minimum_overlap_cost(children, indexable,
                                                  parameters.get_overlap_cost_threshold(),
                                                  index::detail::get_strategy(parameters));
        }
        // children are internal nodes
        else
        {
            return choose_by_minimum_content_cost(children, indexable,
                                                  index::detail::get_strategy(parameters));
        }
    }

private:
    struct child_contents
    {
        content_type content_diff;
        content_type content;
        size_t i;

        void set(size_t i_, content_type const& content_, content_type const& content_diff_)
        {
            i = i_;
            content = content_;
            content_diff = content_diff_;
        }
    };

    template <typename Indexable, typename Strategy>
    static inline size_t choose_by_minimum_overlap_cost(children_type const& children,
                                                        Indexable const& indexable,
                                                        size_t overlap_cost_threshold,
                                                        Strategy const& strategy)
    {
        const size_t children_count = children.size();

        content_type min_content_diff = (std::numeric_limits<content_type>::max)();
        content_type min_content = (std::numeric_limits<content_type>::max)();
        size_t choosen_index = 0;

        // create container of children sorted by content enlargement needed to include the new value
        typename rtree::container_from_elements_type<children_type, child_contents>::type
            children_contents(children_count);

        for ( size_t i = 0 ; i < children_count ; ++i )
        {
            child_type const& ch_i = children[i];

            // expanded child node's box
            box_type box_exp(ch_i.first);
            index::detail::expand(box_exp, indexable, strategy);

            // areas difference
            content_type content = index::detail::content(box_exp);
            content_type content_diff = content - index::detail::content(ch_i.first);

            children_contents[i].set(i, content, content_diff);

            if ( content_diff < min_content_diff ||
                 (content_diff == min_content_diff && content < min_content) )
            {
                min_content_diff = content_diff;
                min_content = content;
                choosen_index = i;
            }
        }

        // is this assumption ok? if min_content_diff == 0 there is no overlap increase?

        if ( min_content_diff < -std::numeric_limits<double>::epsilon() || std::numeric_limits<double>::epsilon() < min_content_diff )
        {
            size_t first_n_children_count = children_count;
            if ( 0 < overlap_cost_threshold && overlap_cost_threshold < children.size() )
            {
                first_n_children_count = overlap_cost_threshold;
                // rearrange by content_diff
                // in order to calculate nearly minimum overlap cost
                index::detail::nth_element(children_contents.begin(), children_contents.begin() + first_n_children_count, children_contents.end(), content_diff_less);
            }

            // calculate minimum or nearly minimum overlap cost
            choosen_index = choose_by_minimum_overlap_cost_first_n(children, indexable,
                                                                   first_n_children_count,
                                                                   children_count,
                                                                   children_contents,
                                                                   strategy);
        }

        return choosen_index;
    }

    static inline bool content_diff_less(child_contents const& p1, child_contents const& p2)
    {
        return p1.content_diff < p2.content_diff
            || (p1.content_diff == p2.content_diff && (p1.content) < (p2.content));
    }

    template <typename Indexable, typename ChildrenContents, typename Strategy>
    static inline size_t choose_by_minimum_overlap_cost_first_n(children_type const& children,
                                                                Indexable const& indexable,
                                                                size_t const first_n_children_count,
                                                                size_t const children_count,
                                                                ChildrenContents const& children_contents,
                                                                Strategy const& strategy)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(first_n_children_count <= children_count, "unexpected value");
        BOOST_GEOMETRY_INDEX_ASSERT(children_contents.size() == children_count, "unexpected number of elements");

        // choose index with smallest overlap change value, or content change or smallest content
        size_t choosen_index = 0;
        content_type smallest_overlap_diff = (std::numeric_limits<content_type>::max)();
        content_type smallest_content_diff = (std::numeric_limits<content_type>::max)();
        content_type smallest_content = (std::numeric_limits<content_type>::max)();

        // for each child node
        for (size_t first_i = 0 ; first_i < first_n_children_count ; ++first_i)
        {
            size_t i = children_contents[first_i].i;
            content_type const& content = children_contents[first_i].content;
            content_type const& content_diff = children_contents[first_i].content_diff;

            child_type const& ch_i = children[i];

            box_type box_exp(ch_i.first);
            // calculate expanded box of child node ch_i
            index::detail::expand(box_exp, indexable, strategy);

            content_type overlap_diff = 0;

            // calculate overlap
            for ( size_t j = 0 ; j < children_count ; ++j )
            {
                if ( i != j )
                {
                    child_type const& ch_j = children[j];

                    content_type overlap_exp = index::detail::intersection_content(box_exp, ch_j.first, strategy);
                    if ( overlap_exp < -std::numeric_limits<content_type>::epsilon() || std::numeric_limits<content_type>::epsilon() < overlap_exp )
                    {
                        overlap_diff += overlap_exp - index::detail::intersection_content(ch_i.first, ch_j.first, strategy);
                    }
                }
            }

            // update result
            if ( overlap_diff < smallest_overlap_diff ||
                ( overlap_diff == smallest_overlap_diff && ( content_diff < smallest_content_diff ||
                ( content_diff == smallest_content_diff && content < smallest_content ) )
                ) )
            {
                smallest_overlap_diff = overlap_diff;
                smallest_content_diff = content_diff;
                smallest_content = content;
                choosen_index = i;
            }
        }

        return choosen_index;
    }

    template <typename Indexable, typename Strategy>
    static inline size_t choose_by_minimum_content_cost(children_type const& children,
                                                        Indexable const& indexable,
                                                        Strategy const& strategy)
    {
        size_t children_count = children.size();

        // choose index with smallest content change or smallest content
        size_t choosen_index = 0;
        content_type smallest_content_diff = (std::numeric_limits<content_type>::max)();
        content_type smallest_content = (std::numeric_limits<content_type>::max)();

        // choose the child which requires smallest box expansion to store the indexable
        for ( size_t i = 0 ; i < children_count ; ++i )
        {
            child_type const& ch_i = children[i];

            // expanded child node's box
            box_type box_exp(ch_i.first);
            index::detail::expand(box_exp, indexable, strategy);

            // areas difference
            content_type content = index::detail::content(box_exp);
            content_type content_diff = content - index::detail::content(ch_i.first);

            // update the result
            if ( content_diff < smallest_content_diff ||
                ( content_diff == smallest_content_diff && content < smallest_content ) )
            {
                smallest_content_diff = content_diff;
                smallest_content = content;
                choosen_index = i;
            }
        }

        return choosen_index;
    }
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_RSTAR_CHOOSE_NEXT_NODE_HPP

/* choose_next_node.hpp
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
*/