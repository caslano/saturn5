// Boost.Geometry Index
//
// R-tree query iterators
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_QUERY_ITERATORS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_QUERY_ITERATORS_HPP

#include <boost/scoped_ptr.hpp>

//#define BOOST_GEOMETRY_INDEX_DETAIL_QUERY_ITERATORS_USE_MOVE

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
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef visitors::spatial_query_incremental<MembersHolder, Predicates> visitor_type;
    typedef typename visitor_type::node_pointer node_pointer;

public:
    typedef std::forward_iterator_tag iterator_category;
    typedef typename MembersHolder::value_type value_type;
    typedef typename allocators_type::const_reference reference;
    typedef typename allocators_type::difference_type difference_type;
    typedef typename allocators_type::const_pointer pointer;

    inline spatial_query_iterator()
    {}

    inline spatial_query_iterator(parameters_type const& par, translator_type const& t, Predicates const& p)
        : m_visitor(par, t, p)
    {}

    inline spatial_query_iterator(node_pointer root, parameters_type const& par, translator_type const& t, Predicates const& p)
        : m_visitor(par, t, p)
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

    spatial_query_iterator & operator++()
    {
        m_visitor.increment();
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
        return l.m_visitor == r.m_visitor;
    }

    friend bool operator==(spatial_query_iterator const& l, end_query_iterator<value_type, allocators_type> const& /*r*/)
    {
        return l.m_visitor.is_end();
    }

    friend bool operator==(end_query_iterator<value_type, allocators_type> const& /*l*/, spatial_query_iterator const& r)
    {
        return r.m_visitor.is_end();
    }
    
private:
    visitor_type m_visitor;
};

template <typename MembersHolder, typename Predicates, unsigned NearestPredicateIndex>
class distance_query_iterator
{
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef visitors::distance_query_incremental<MembersHolder, Predicates, NearestPredicateIndex> visitor_type;
    typedef typename visitor_type::node_pointer node_pointer;

public:
    typedef std::forward_iterator_tag iterator_category;
    typedef typename MembersHolder::value_type value_type;
    typedef typename allocators_type::const_reference reference;
    typedef typename allocators_type::difference_type difference_type;
    typedef typename allocators_type::const_pointer pointer;

    inline distance_query_iterator()
    {}

    inline distance_query_iterator(parameters_type const& par, translator_type const& t, Predicates const& p)
        : m_visitor(par, t, p)
    {}

    inline distance_query_iterator(node_pointer root, parameters_type const& par, translator_type const& t, Predicates const& p)
        : m_visitor(par, t, p)
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

    distance_query_iterator & operator++()
    {
        m_visitor.increment();
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
        return l.m_visitor == r.m_visitor;
    }

    friend bool operator==(distance_query_iterator const& l, end_query_iterator<value_type, allocators_type> const& /*r*/)
    {
        return l.m_visitor.is_end();
    }

    friend bool operator==(end_query_iterator<value_type, allocators_type> const& /*l*/, distance_query_iterator const& r)
    {
        return r.m_visitor.is_end();
    }

private:
    visitor_type m_visitor;
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

    query_iterator()
    {}

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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_QUERY_ITERATORS_USE_MOVE
    query_iterator & operator=(query_iterator const& o)
    {
        if ( this != boost::addressof(o) )
        {
            m_ptr.reset(o.m_ptr.get() ? o.m_ptr->clone() : 0);
        }
        return *this;
    }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
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
#endif
#else // !BOOST_GEOMETRY_INDEX_DETAIL_QUERY_ITERATORS_USE_MOVE
private:
    BOOST_COPYABLE_AND_MOVABLE(query_iterator)
public:
    query_iterator & operator=(BOOST_COPY_ASSIGN_REF(query_iterator) o)
    {
        if ( this != boost::addressof(o) )
        {
            m_ptr.reset(o.m_ptr.get() ? o.m_ptr->clone() : 0);
        }
        return *this;
    }
    query_iterator(BOOST_RV_REF(query_iterator) o)
        : m_ptr(0)
    {
        m_ptr.swap(o.m_ptr);
    }
    query_iterator & operator=(BOOST_RV_REF(query_iterator) o)
    {
        if ( this != boost::addressof(o) )
        {
            m_ptr.swap(o.m_ptr);
            o.m_ptr.reset();
        }
        return *this;
    }
#endif // BOOST_GEOMETRY_INDEX_DETAIL_QUERY_ITERATORS_USE_MOVE

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