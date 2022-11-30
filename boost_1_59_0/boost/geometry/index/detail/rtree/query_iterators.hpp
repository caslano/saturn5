// Boost.Geometry Index
//
// R-tree query iterators
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2021.
// Modifications copyright (c) 2019-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_QUERY_ITERATORS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_QUERY_ITERATORS_HPP

#include <boost/scoped_ptr.hpp>

#include <boost/geometry/index/detail/rtree/node/node_elements.hpp>
#include <boost/geometry/index/detail/rtree/visitors/distance_query.hpp>
#include <boost/geometry/index/detail/rtree/visitors/spatial_query.hpp>

namespace boost { namespace geometry { namespace index { namespace detail { namespace rtree { namespace iterators {

template <typename Value, typename Allocators>
struct end_query_iterator
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

    end_query_iterator & operator++()
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "iterator not incrementable");
        return *this;
    }

    end_query_iterator operator++(int)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "iterator not incrementable");
        return *this;
    }

    friend bool operator==(end_query_iterator const& /*l*/, end_query_iterator const& /*r*/)
    {
        return true;
    }
};

template <typename MembersHolder, typename Predicates>
class spatial_query_iterator
{
    typedef typename MembersHolder::allocators_type allocators_type;

public:
    typedef std::forward_iterator_tag iterator_category;
    typedef typename MembersHolder::value_type value_type;
    typedef typename allocators_type::const_reference reference;
    typedef typename allocators_type::difference_type difference_type;
    typedef typename allocators_type::const_pointer pointer;

    spatial_query_iterator() = default;

    explicit spatial_query_iterator(Predicates const& pred)
        : m_impl(pred)
    {}

    spatial_query_iterator(MembersHolder const& members, Predicates const& pred)
        : m_impl(members, pred)
    {
        m_impl.initialize(members);
    }

    reference operator*() const
    {
        return m_impl.dereference();
    }

    const value_type * operator->() const
    {
        return boost::addressof(m_impl.dereference());
    }

    spatial_query_iterator & operator++()
    {
        m_impl.increment();
        return *this;
    }

    spatial_query_iterator operator++(int)
    {
        spatial_query_iterator temp = *this;
        this->operator++();
        return temp;
    }

    friend bool operator==(spatial_query_iterator const& l, spatial_query_iterator const& r)
    {
        return l.m_impl == r.m_impl;
    }

    friend bool operator==(spatial_query_iterator const& l, end_query_iterator<value_type, allocators_type> const& /*r*/)
    {
        return l.m_impl.is_end();
    }

    friend bool operator==(end_query_iterator<value_type, allocators_type> const& /*l*/, spatial_query_iterator const& r)
    {
        return r.m_impl.is_end();
    }
    
private:
    visitors::spatial_query_incremental<MembersHolder, Predicates> m_impl;
};

template <typename MembersHolder, typename Predicates>
class distance_query_iterator
{
    typedef typename MembersHolder::allocators_type allocators_type;

public:
    typedef std::forward_iterator_tag iterator_category;
    typedef typename MembersHolder::value_type value_type;
    typedef typename allocators_type::const_reference reference;
    typedef typename allocators_type::difference_type difference_type;
    typedef typename allocators_type::const_pointer pointer;

    distance_query_iterator() = default;

    explicit distance_query_iterator(Predicates const& pred)
        : m_impl(pred)
    {}

    distance_query_iterator(MembersHolder const& members, Predicates const& pred)
        : m_impl(members, pred)
    {
        m_impl.initialize(members);
    }

    reference operator*() const
    {
        return m_impl.dereference();
    }

    const value_type * operator->() const
    {
        return boost::addressof(m_impl.dereference());
    }

    distance_query_iterator & operator++()
    {
        m_impl.increment();
        return *this;
    }

    distance_query_iterator operator++(int)
    {
        distance_query_iterator temp = *this;
        this->operator++();
        return temp;
    }

    friend bool operator==(distance_query_iterator const& l, distance_query_iterator const& r)
    {
        return l.m_impl == r.m_impl;
    }

    friend bool operator==(distance_query_iterator const& l, end_query_iterator<value_type, allocators_type> const& /*r*/)
    {
        return l.m_impl.is_end();
    }

    friend bool operator==(end_query_iterator<value_type, allocators_type> const& /*l*/, distance_query_iterator const& r)
    {
        return r.m_impl.is_end();
    }

private:
    visitors::distance_query_incremental<MembersHolder, Predicates> m_impl;
};


template <typename L, typename R>
inline bool operator!=(L const& l, R const& r)
{
    return !(l == r);
}


template <typename Value, typename Allocators>
class query_iterator_base
{
public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Value value_type;
    typedef typename Allocators::const_reference reference;
    typedef typename Allocators::difference_type difference_type;
    typedef typename Allocators::const_pointer pointer;

    virtual ~query_iterator_base() {}

    virtual query_iterator_base * clone() const = 0;
    
    virtual bool is_end() const = 0;
    virtual reference dereference() const = 0;
    virtual void increment() = 0;
    virtual bool equals(query_iterator_base const&) const = 0;
};

template <typename Value, typename Allocators, typename Iterator>
class query_iterator_wrapper
    : public query_iterator_base<Value, Allocators>
{
    typedef query_iterator_base<Value, Allocators> base_t;

public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Value value_type;
    typedef typename Allocators::const_reference reference;
    typedef typename Allocators::difference_type difference_type;
    typedef typename Allocators::const_pointer pointer;

    query_iterator_wrapper() : m_iterator() {}
    explicit query_iterator_wrapper(Iterator const& it) : m_iterator(it) {}

    virtual base_t * clone() const { return new query_iterator_wrapper(m_iterator); }

    virtual bool is_end() const { return m_iterator == end_query_iterator<Value, Allocators>(); }
    virtual reference dereference() const { return *m_iterator; }
    virtual void increment() { ++m_iterator; }
    virtual bool equals(base_t const& r) const
    {
        const query_iterator_wrapper * p = dynamic_cast<const query_iterator_wrapper *>(boost::addressof(r));
        BOOST_GEOMETRY_INDEX_ASSERT(p, "iterators can't be compared");
        return m_iterator == p->m_iterator;
    }

private:
    Iterator m_iterator;
};


template <typename Value, typename Allocators>
class query_iterator
{
    typedef query_iterator_base<Value, Allocators> iterator_base;
    typedef boost::scoped_ptr<iterator_base> iterator_ptr;

public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Value value_type;
    typedef typename Allocators::const_reference reference;
    typedef typename Allocators::difference_type difference_type;
    typedef typename Allocators::const_pointer pointer;

    query_iterator() = default;

    template <typename It>
    query_iterator(It const& it)
        : m_ptr(static_cast<iterator_base*>(
                    new query_iterator_wrapper<Value, Allocators, It>(it) ))
    {}

    query_iterator(end_query_iterator<Value, Allocators> const& /*it*/)
    {}

    query_iterator(query_iterator const& o)
        : m_ptr(o.m_ptr.get() ? o.m_ptr->clone() : 0)
    {}

    query_iterator & operator=(query_iterator const& o)
    {
        if ( this != boost::addressof(o) )
        {
            m_ptr.reset(o.m_ptr.get() ? o.m_ptr->clone() : 0);
        }
        return *this;
    }

    query_iterator(query_iterator && o)
        : m_ptr(0)
    {
        m_ptr.swap(o.m_ptr);
    }

    query_iterator & operator=(query_iterator && o)
    {
        if ( this != boost::addressof(o) )
        {
            m_ptr.swap(o.m_ptr);
            o.m_ptr.reset();
        }
        return *this;
    }

    reference operator*() const
    {
        return m_ptr->dereference();
    }

    const value_type * operator->() const
    {
        return boost::addressof(m_ptr->dereference());
    }

    query_iterator & operator++()
    {
        m_ptr->increment();
        return *this;
    }

    query_iterator operator++(int)
    {
        query_iterator temp = *this;
        this->operator++();
        return temp;
    }

    friend bool operator==(query_iterator const& l, query_iterator const& r)
    {
        if ( l.m_ptr.get() )
        {
            if ( r.m_ptr.get() )
                return l.m_ptr->equals(*r.m_ptr);
            else
                return l.m_ptr->is_end();
        }
        else
        {
            if ( r.m_ptr.get() )
                return r.m_ptr->is_end();
            else
                return true;
        }
    }

private:
    iterator_ptr m_ptr;
};

}}}}}} // namespace boost::geometry::index::detail::rtree::iterators

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_QUERY_ITERATORS_HPP

/* query_iterators.hpp
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
*/