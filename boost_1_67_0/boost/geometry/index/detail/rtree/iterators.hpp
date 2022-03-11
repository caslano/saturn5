// Boost.Geometry Index
//
// R-tree iterators
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_ITERATORS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_ITERATORS_HPP

namespace boost { namespace geometry { namespace index { namespace detail { namespace rtree { namespace iterators {

template <typename Value, typename Allocators>
struct end_iterator
{
    typedef std::forward_iterator_tag iterator_category;
    typedef Value value_type;
    typedef typename Allocators::const_reference reference;
    typedef typename Allocators::difference_type difference_type;
    typedef typename Allocators::const_pointer pointer;

    reference operator*() const
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "iterator not dereferencable");
        pointer p(0);
        return *p;
    }

    const value_type * operator->() const
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "iterator not dereferencable");
        const value_type * p = 0;
        return p;
    }

    end_iterator & operator++()
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "iterator not incrementable");
        return *this;
    }

    end_iterator operator++(int)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "iterator not incrementable");
        return *this;
    }

    friend bool operator==(end_iterator const& /*l*/, end_iterator const& /*r*/)
    {
        return true;
    }
};

template <typename Value, typename Options, typename Translator, typename Box, typename Allocators>
class iterator
{
    typedef visitors::iterator<Value, Options, Translator, Box, Allocators> visitor_type;
    typedef typename visitor_type::node_pointer node_pointer;

public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Value value_type;
    typedef typename Allocators::const_reference reference;
    typedef typename Allocators::difference_type difference_type;
    typedef typename Allocators::const_pointer pointer;

    inline iterator()
    {}

    inline iterator(node_pointer root)
    {
        m_visitor.initialize(root);
    }

    reference operator*() const
    {
        return m_visitor.dereference();
    }

    const value_type * operator->() const
    {
        return boost::addressof(m_visitor.dereference());
    }

    iterator & operator++()
    {
        m_visitor.increment();
        return *this;
    }

    iterator operator++(int)
    {
        iterator temp = *this;
        this->operator++();
        return temp;
    }

    friend bool operator==(iterator const& l, iterator const& r)
    {
        return l.m_visitor == r.m_visitor;
    }

    friend bool operator==(iterator const& l, end_iterator<Value, Allocators> const& /*r*/)
    {
        return l.m_visitor.is_end();
    }

    friend bool operator==(end_iterator<Value, Allocators> const& /*l*/, iterator const& r)
    {
        return r.m_visitor.is_end();
    }
    
private:
    visitor_type m_visitor;
};

}}}}}} // namespace boost::geometry::index::detail::rtree::iterators

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_ITERATORS_HPP

/* iterators.hpp
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
*/