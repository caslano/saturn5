// Boost.Geometry Index
//
// R-tree iterator visitor implementation
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_ITERATOR_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_ITERATOR_HPP

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