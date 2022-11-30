// Boost.Geometry Index
//
// R-tree iterator visitor implementation
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2021.
// Modifications copyright (c) 2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_ITERATOR_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_ITERATOR_HPP

#include <boost/geometry/index/detail/rtree/node/concept.hpp>
#include <boost/geometry/index/detail/rtree/node/node_elements.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename Value, typename Options, typename Translator, typename Box, typename Allocators>
class iterator
    : public rtree::visitor<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag, true>::type
{
public:
    typedef typename rtree::node<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type node;
    typedef typename rtree::internal_node<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type internal_node;
    typedef typename rtree::leaf<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type leaf;

    typedef typename Allocators::size_type size_type;
    typedef typename Allocators::const_reference const_reference;
    typedef typename Allocators::node_pointer node_pointer;

    typedef typename rtree::elements_type<internal_node>::type::const_iterator internal_iterator;
    typedef typename rtree::elements_type<leaf>::type leaf_elements;
    typedef typename rtree::elements_type<leaf>::type::const_iterator leaf_iterator;

    inline iterator()
        : m_values(NULL)
        , m_current()
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
                // there are more values in the current leaf
                if ( m_current != m_values->end() )
                {
                    return;
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

                // push the next node to the stack
                rtree::apply_visitor(*this, *(it->second));
            }
        }
    }

    bool is_end() const
    {
        return 0 == m_values;
    }

    friend bool operator==(iterator const& l, iterator const& r)
    {
        return (l.m_values == r.m_values) && (0 == l.m_values || l.m_current == r.m_current );
    }

private:

    std::vector< std::pair<internal_iterator, internal_iterator> > m_internal_stack;
    const leaf_elements * m_values;
    leaf_iterator m_current;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_ITERATOR_HPP

/* iterator.hpp
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
*/