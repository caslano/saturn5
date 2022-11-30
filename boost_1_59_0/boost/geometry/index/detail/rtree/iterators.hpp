// Boost.Geometry Index
//
// R-tree iterators
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_ITERATORS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_ITERATORS_HPP

#include <iterator>

#include <boost/geometry/index/detail/rtree/visitors/iterator.hpp>

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