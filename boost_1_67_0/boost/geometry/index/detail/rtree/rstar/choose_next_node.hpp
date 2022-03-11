// Boost.Geometry Index
//
// R-tree R*-tree next node choosing algorithm implementation
//
// Copyright (c) 2011-2019 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
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