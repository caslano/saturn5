// Boost.Geometry Index
//
// R-tree spatial query visitor implementation
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_SPATIAL_QUERY_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_SPATIAL_QUERY_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename MembersHolder, typename Predicates, typename OutIter>
struct spatial_query
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename index::detail::strategy_type<parameters_type>::type strategy_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef typename allocators_type::size_type size_type;

    static const unsigned predicates_len = index::detail::predicates_length<Predicates>::value;

    inline spatial_query(parameters_type const& par, translator_type const& t, Predicates const& p, OutIter out_it)
        : tr(t), pred(p), out_iter(out_it), found_count(0), strategy(index::detail::get_strategy(par))
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // traverse nodes meeting predicates
        for (typename elements_type::const_iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            // if node meets predicates
            // 0 - dummy value
            if ( index::detail::predicates_check
                    <
                        index::detail::bounds_tag, 0, predicates_len
                    >(pred, 0, it->first, strategy) )
            {
                rtree::apply_visitor(*this, *it->second);
            }
        }
    }

    inline void operator()(leaf const& n)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // get all values meeting predicates
        for (typename elements_type::const_iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            // if value meets predicates
            if ( index::detail::predicates_check
                    <
                        index::detail::value_tag, 0, predicates_len
                    >(pred, *it, tr(*it), strategy) )
            {
                *out_iter = *it;
                ++out_iter;

                ++found_count;
            }
        }
    }

    translator_type const& tr;

    Predicates pred;

    OutIter out_iter;
    size_type found_count;

    strategy_type strategy;
};

template <typename MembersHolder, typename Predicates>
class spatial_query_incremental
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::value_type value_type;
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename index::detail::strategy_type<parameters_type>::type strategy_type;

public:
    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef typename allocators_type::size_type size_type;
    typedef typename allocators_type::const_reference const_reference;
    typedef typename allocators_type::node_pointer node_pointer;

    typedef typename rtree::elements_type<internal_node>::type::const_iterator internal_iterator;
    typedef typename rtree::elements_type<leaf>::type leaf_elements;
    typedef typename rtree::elements_type<leaf>::type::const_iterator leaf_iterator;

    static const unsigned predicates_len = index::detail::predicates_length<Predicates>::value;

    inline spatial_query_incremental()
        : m_translator(NULL)
//        , m_pred()
        , m_values(NULL)
        , m_current()
//        , m_strategy()
    {}

    inline spatial_query_incremental(parameters_type const& params, translator_type const& t, Predicates const& p)
        : m_translator(::boost::addressof(t))
        , m_pred(p)
        , m_values(NULL)
        , m_current()
        , m_strategy(index::detail::get_strategy(params))
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        m_internal_stack.push_back(std::make_pair(elements.begin(), elements.end()));
    }

    inline void operator()(leaf const& n)
    {
        m_values = ::boost::addressof(rtree::elements(n));
        m_current = rtree::elements(n).begin();
    }

    const_reference dereference() const
    {
        BOOST_GEOMETRY_INDEX_ASSERT(m_values, "not dereferencable");
        return *m_current;
    }

    void initialize(node_pointer root)
    {
        rtree::apply_visitor(*this, *root);
        search_value();
    }

    void increment()
    {
        ++m_current;
        search_value();
    }

    void search_value()
    {
        for (;;)
        {
            // if leaf is choosen, move to the next value in leaf
            if ( m_values )
            {
                if ( m_current != m_values->end() )
                {
                    // return if next value is found
                    value_type const& v = *m_current;
                    if (index::detail::predicates_check
                            <
                               index::detail::value_tag, 0, predicates_len
                            >(m_pred, v, (*m_translator)(v), m_strategy))
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
                if ( m_internal_stack.empty() )
                    return;

                // no more children in current node, remove it from stack
                if ( m_internal_stack.back().first == m_internal_stack.back().second )
                {
                    m_internal_stack.pop_back();
                    continue;
                }

                internal_iterator it = m_internal_stack.back().first;
                ++m_internal_stack.back().first;

                // next node is found, push it to the stack
                if (index::detail::predicates_check
                        <
                            index::detail::bounds_tag, 0, predicates_len
                        >(m_pred, 0, it->first, m_strategy))
                {
                    rtree::apply_visitor(*this, *(it->second));
                }
            }
        }
    }

    bool is_end() const
    {
        return 0 == m_values;
    }

    friend bool operator==(spatial_query_incremental const& l, spatial_query_incremental const& r)
    {
        return (l.m_values == r.m_values) && (0 == l.m_values || l.m_current == r.m_current );
    }

private:

    const translator_type * m_translator;

    Predicates m_pred;

    std::vector< std::pair<internal_iterator, internal_iterator> > m_internal_stack;
    const leaf_elements * m_values;
    leaf_iterator m_current;

    strategy_type m_strategy;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_SPATIAL_QUERY_HPP

/* spatial_query.hpp
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
*/