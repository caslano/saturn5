// Boost.Geometry Index
//
// R-tree spatial query visitor implementation
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2021.
// Modifications copyright (c) 2019-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_SPATIAL_QUERY_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_SPATIAL_QUERY_HPP

#include <boost/geometry/index/detail/rtree/node/node_elements.hpp>
#include <boost/geometry/index/detail/predicates.hpp>
#include <boost/geometry/index/parameters.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename MembersHolder, typename Predicates, typename OutIter>
struct spatial_query
{
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename index::detail::strategy_type<parameters_type>::type strategy_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef typename allocators_type::node_pointer node_pointer;
    typedef typename allocators_type::size_type size_type;

    spatial_query(MembersHolder const& members, Predicates const& p, OutIter out_it)
        : m_tr(members.translator())
        , m_strategy(index::detail::get_strategy(members.parameters()))
        , m_pred(p)
        , m_out_iter(out_it)
        , m_found_count(0)
    {}

    size_type apply(node_pointer ptr, size_type reverse_level)
    {
        namespace id = index::detail;
        if (reverse_level > 0)
        {
            internal_node& n = rtree::get<internal_node>(*ptr);
            // traverse nodes meeting predicates
            for (auto const& p : rtree::elements(n))
            {
                // if node meets predicates (0 is dummy value)
                if (id::predicates_check<id::bounds_tag>(m_pred, 0, p.first, m_strategy))
                {
                    apply(p.second, reverse_level - 1);
                }
            }
        }
        else
        {
            leaf& n = rtree::get<leaf>(*ptr);
            // get all values meeting predicates
            for (auto const& v : rtree::elements(n))
            {
                // if value meets predicates
                if (id::predicates_check<id::value_tag>(m_pred, v, m_tr(v), m_strategy))
                {
                    *m_out_iter = v;
                    ++m_out_iter;
                    ++m_found_count;
                }
            }
        }

        return m_found_count;
    }

    size_type apply(MembersHolder const& members)
    {
        return apply(members.root, members.leafs_level);
    }

private:
    translator_type const& m_tr;
    strategy_type m_strategy;

    Predicates const& m_pred;
    OutIter m_out_iter;

    size_type m_found_count;
};

template <typename MembersHolder, typename Predicates>
class spatial_query_incremental
{
    typedef typename MembersHolder::value_type value_type;
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename index::detail::strategy_type<parameters_type>::type strategy_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef typename allocators_type::size_type size_type;
    typedef typename allocators_type::const_reference const_reference;
    typedef typename allocators_type::node_pointer node_pointer;

    typedef typename rtree::elements_type<internal_node>::type::const_iterator internal_iterator;
    typedef typename rtree::elements_type<leaf>::type leaf_elements;
    typedef typename rtree::elements_type<leaf>::type::const_iterator leaf_iterator;

    struct internal_data
    {
        internal_data(internal_iterator f, internal_iterator l, size_type rl)
            : first(f), last(l), reverse_level(rl)
        {}
        internal_iterator first;
        internal_iterator last;
        size_type reverse_level;
    };

public:
    spatial_query_incremental()
        : m_translator(nullptr)
//        , m_strategy()
//        , m_pred()
        , m_values(nullptr)
        , m_current()
    {}

    spatial_query_incremental(Predicates const& p)
        : m_translator(nullptr)
//        , m_strategy()
        , m_pred(p)
        , m_values(nullptr)
        , m_current()
    {}

    spatial_query_incremental(MembersHolder const& members, Predicates const& p)
        : m_translator(::boost::addressof(members.translator()))
        , m_strategy(index::detail::get_strategy(members.parameters()))
        , m_pred(p)
        , m_values(nullptr)
        , m_current()
    {}

    const_reference dereference() const
    {
        BOOST_GEOMETRY_INDEX_ASSERT(m_values, "not dereferencable");
        return *m_current;
    }

    void initialize(MembersHolder const& members)
    {
        apply(members.root, members.leafs_level);
        search_value();
    }

    void increment()
    {
        ++m_current;
        search_value();
    }

    bool is_end() const
    {
        return 0 == m_values;
    }

    friend bool operator==(spatial_query_incremental const& l, spatial_query_incremental const& r)
    {
        return (l.m_values == r.m_values) && (0 == l.m_values || l.m_current == r.m_current);
    }

private:
    void apply(node_pointer ptr, size_type reverse_level)
    {
        namespace id = index::detail;

        if (reverse_level > 0)
        {
            internal_node& n = rtree::get<internal_node>(*ptr);
            auto const& elements = rtree::elements(n);
            m_internal_stack.push_back(internal_data(elements.begin(), elements.end(), reverse_level - 1));
        }
        else
        {
            leaf& n = rtree::get<leaf>(*ptr);
            m_values = ::boost::addressof(rtree::elements(n));
            m_current = rtree::elements(n).begin();
        }
    }

    void search_value()
    {
        namespace id = index::detail;
        for (;;)
        {
            // if leaf is choosen, move to the next value in leaf
            if ( m_values )
            {
                if ( m_current != m_values->end() )
                {
                    // return if next value is found
                    value_type const& v = *m_current;
                    if (id::predicates_check<id::value_tag>(m_pred, v, (*m_translator)(v), m_strategy))
                    {
                        return;
                    }

                    ++m_current;
                }
                // no more values, clear current leaf
                else
                {
                    m_values = 0;
                }
            }
            // if leaf isn't choosen, move to the next leaf
            else
            {
                // return if there is no more nodes to traverse
                if (m_internal_stack.empty())
                {
                    return;
                }

                internal_data& current_data = m_internal_stack.back();

                // no more children in current node, remove it from stack                
                if (current_data.first == current_data.last)
                {
                    m_internal_stack.pop_back();
                    continue;
                }

                internal_iterator it = current_data.first;
                ++current_data.first;

                // next node is found, push it to the stack
                if (id::predicates_check<id::bounds_tag>(m_pred, 0, it->first, m_strategy))
                {
                    apply(it->second, current_data.reverse_level);
                }
            }
        }
    }
    
    const translator_type * m_translator;
    strategy_type m_strategy;

    Predicates m_pred;

    std::vector<internal_data> m_internal_stack;
    const leaf_elements * m_values;
    leaf_iterator m_current;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_SPATIAL_QUERY_HPP

/* spatial_query.hpp
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
*/